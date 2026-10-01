#include "gobj_cam_dl.h"
#include "gobj_dl.h"
#include "main.h"
#include "isys.h"
#include "gobj.h"
#include "obj_manager.h"
#include "gobj_process.h"
#include "thread.h"

/* A debug frame-rate selector that nothing reads any more: the selected entry
   (.sdata), each entry's wait and its name (.data). */
static int omSpeedSel = 0; /* derived name */

static int omSpeedWait[8] = {9999, 60, 30, 20, 12, 8, 4, 2}; /* derived name */

static char omSpeedName[8][8] = {"STOP", "1/1",   "1/2",  "1/3",
                                 "1/5",  "1/7.5", "1/15", "1/30"}; /* derived name */

void iosOmInit(void)
{
    isysGObjInit(320);
    isysGObjProcessInit(1280);
    isysGObjDlInit();
    return isysGObjCameraDlInit();
}

inline void iosOmGetGObjStatus(int *total, int *used)
{
    *total = 320;
    *used = isysGetNbAllocedGObjs();
}

inline void iosOmExeEachGObj(int idx, void (*fn)(int *, int), int arg)
{
    int *node = gobj_link_head[idx];
    if (node != 0) {
        do {
            fn(node, arg);
            node = (int *)node[0x10 / 4];
        } while (node != 0);
    }
}

inline void iosOmExeEachGObjAll(void (*fn)(int *, int), int arg)
{
    int i = 0;
    do {
        int *node = gobj_link_head[i];
        if (node != 0) {
            do {
                fn(node, arg);
                node = (int *)node[0x10 / 4];
            } while (node != 0);
        }
        i++;
    } while (i < 8);
}

inline int iosOmReturnExeEachGObj(int a0, int (*fn)(int *, int), int arg, int flag)
{
    int *node = gobj_link_head[a0];
    int ret = 0;
    if (node != 0) {
        do {
            ret = fn(node, arg);
            if (flag != 0) {
                if (flag == 1) {
                    if (ret != 0)
                        return ret;
                }
            }
        } while (node != 0);
    }
    return ret;
}

inline int *iosOmSearchGObjId(int idx, int target)
{
    int *p = gobj_link_head[idx];
    if (p != 0) {
        do {
            if (p[0] == target) {
                return p;
            }
            p = (int *)p[0x10 / 4];
        } while (p != 0);
    }
    return 0;
}

inline int *iosOmSearchGObjIdAll(int a0)
{
    int i;
    for (i = 0; i < 8; i++) {
        int *p = gobj_link_head[i];
        int *found;
        if (p != 0) {
            do {
                if (p[0] == a0) {
                    found = p;
                    goto check;
                }
                p = (int *)p[4];
            } while (p != 0);
        }
        found = 0;
    check:
        if (found != 0)
            return found;
    }
    return 0;
}

inline void iosOmBeforeFuncStandard(void) {}

inline int iosOmSendMail(GObj *g, int type, void *arg)
{
    IosMailBox *mb = (IosMailBox *)&g->mailQueue;
    int count = mb->num;
    if (count == 32)
        return -1;
    g->mail[count].type = type;
    {
        int c2 = mb->num;
        mb->num = c2 + 1;
        g->mail[c2].arg = arg;
    }
    return 0;
}

inline int iosOmSendMailLink(int a0, int val5, int val6)
{
    int *node = gobj_link_head[a0];
    int ret = 0;
    if (node != 0) {
        do {
            int full;
            int *p = (int *)((char *)node + 0x54);
            int count = p[1];

            if (count == 0x20) {
                full = -1;
            } else {
                char *addr;
                addr = (char *)node + count * 8;
                full = 0;
                *(int *)(addr + 0x5C) = val5;
                {
                    int c2 = p[1];
                    char *addr2;
                    p[1] = c2 + 1;
                    addr2 = (char *)node + c2 * 8;
                    *(int *)(addr2 + 0x60) = val6;
                }
            }
            node = (int *)node[0x10 / 4];
            if (full != 0)
                ret = -1;
        } while (node != 0);
    }
    return ret;
}

inline int iosOmExeMail(void (*func)(IosMail))
{
    GObj *g = isysCurrentGObj;
    IosMailBox *mb = (IosMailBox *)&g->mailQueue;
    int i;
    for (i = 0; i < mb->num; i++) {
        switch (mb->mail[i].type) {
        case 0:
            isysGObjRemove(g);
            break;
        case 1:
            isysGObjProcPauseAll(g);
            break;
        case 2:
            isysGObjProcActiveAll(g);
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            func(mb->mail[i]);
        }
    }
    return 0;
}

static void _iosOmMain(void)
{
    GObj *g;
    GObj *g2;
    GProc *p;
    int k;
    int pri;

    for (k = 0; k < 8; k++) {
        g = gobj_link_head[k];
        if ((active_gobj_link >> k) & 1) {
            for (; g != 0; g = g->next) {
                isysCurrentGObj = g;
                if (systemStatus[5] == 0 || g->pauseExempt != 0) {
                    if (g->active != 0) {
                        if (g->fn != 0) {
                            g->fn(g);
                        }
                    }
                }
            }
        }
    }
    for (k = 0; k < 8; k++) {
        g2 = gobj_link_head[k];
        if ((active_gobj_link >> k) & 1) {
            for (; g2 != 0; g2 = g2->next) {
                isysCurrentGObj = g2;
                if (systemStatus[5] == 0 || g2->pauseExempt != 0) {
                    if (g2->active != 0) {
                        for (pri = 0x13; pri < 27; pri++) {
                            p = g2->procHead;
                            while (p != 0) {
                                if (p->priority == pri) {
                                    if (p->active != 0) {
                                        isysCurrentGObjProcess = p;
                                        if (p->noThread == 0) {
                                            if (iosThreadGetPri(&p->thread) != 0x22) {
                                                iosThreadWakeup(&p->thread);
                                            } else {
                                                isysGObjProcRemove(p);
                                            }
                                            isysCurrentGObjProcess = 0;
                                        } else {
                                            if (p->func != 0) {
                                                p->func(g2);
                                            }
                                            isysCurrentGObjProcess = 0;
                                        }
                                    }
                                }
                                p = p->prev;
                            }
                        }
                    }
                }
            }
        }
    }
}

void iosOmMain(void)
{
    _iosOmMain();
}

/* the camera list node the DL walk hangs off (gobj_camera_dl_link_head) and the per-kind
   GObj list heads (gobj_dl_link_head) */
typedef struct OmCam { /* field names derived */
    char pad0[52];
    struct OmCam *next; /* 0x34 */
    char _p38[0x48 - 0x38];
    void (*dl)(struct OmCam *); /* 0x48 */
    int kindMask;               /* 0x4C */
    int drawMask;               /* 0x50 */
} OmCam;                        /* derived name */

typedef struct OmObj { /* field names derived */
    char pad0[52];
    struct OmObj *next; /* 0x34 */
    char _p38[0x48 - 0x38];
    void (*dl)(struct OmObj *); /* 0x48 */
    char pad4C[4];
    int drawMask; /* 0x50 */
    char _p54[0x16C - 0x54];
    int active; /* 0x16C */
} OmObj;        /* derived name */

void iosOmCreateDL(void)
{
    OmCam *c;
    OmObj *g;
    int i;

    for (c = gobj_camera_dl_link_head; c != 0; c = c->next) {
        if (active_gobj_link & 1) {
            if (c->dl != 0) {
                c->dl(c);
            }
        }
        for (i = 0; i < 32; i++) {
            if ((active_gobj_link >> i) & 1) {
                if ((c->kindMask >> i) & 1) {
                    for (g = gobj_dl_link_head[i]; g != 0; g = g->next) {
                        if (g->active != 0 && (c->drawMask & g->drawMask) != 0 && g->dl != 0) {
                            g->dl(g);
                        }
                    }
                }
            }
        }
    }
}
