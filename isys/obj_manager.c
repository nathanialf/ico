#include "common.h"

extern void isysGObjCameraDlInit(void);
extern void isysGObjDlInit();
extern void isysGObjInit();
extern void isysGObjProcessInit();
extern void _iosOmMain();
extern int *D_0029C4F0[];
extern int isysGetNbAllocedGObjs();
extern char *D_0063A61C;
extern void isysGObjRemove(char *g);
extern void isysGObjProcPauseAll(char *g);
extern void isysGObjProcActiveAll(char *g);

typedef struct {
    int type;
    int arg;
} IosMail;

typedef struct {
    int unk0;
    int num;
    IosMail mail[32];
} IosMailBox;

/* prototypes: their order is the inline tail's emission order */
void iosOmExeEachGObj(int idx, void (*fn)(int *, int), int arg);
void iosOmExeEachGObjAll(void (*fn)(int *, int), int arg);
int iosOmReturnExeEachGObj(int a0, int (*fn)(int *, int), int arg, int flag);
void iosOmGetGObjStatus(int a0, int a1);
int *iosOmSearchGObjId(int idx, int target);
int *iosOmSearchGObjIdAll(int a0);
void iosOmBeforeFuncStandard(void);
int iosOmSendMail(char *self_arg, int val5, int val6);
int iosOmSendMailLink(int a0, int val5, int val6);
int iosOmExeMail(void (*func)(IosMail));

void iosOmInit(void)
{
    isysGObjInit(0x140);
    isysGObjProcessInit(0x500);
    isysGObjDlInit();
    return isysGObjCameraDlInit();
}

inline void iosOmGetGObjStatus(int a0, int a1)
{
    *(int *)a0 = 0x140;
    *(int *)a1 = isysGetNbAllocedGObjs(a0);
}

inline void iosOmExeEachGObj(int idx, void (*fn)(int *, int), int arg)
{
    int *node = D_0029C4F0[idx];
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
        int *node = D_0029C4F0[i];
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
    int *node = D_0029C4F0[a0];
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
    int *p = D_0029C4F0[idx];
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
        int *p = D_0029C4F0[i];
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

inline int iosOmSendMail(char *self_arg, int val5, int val6)
{
    register char *self = self_arg;
    int *p = (int *)(self + 0x54);
    int count = p[1];
    register int idx;
    register char *addr;
    if (count == 0x20)
        return -1;
    idx = count * 8;
    __asm__("addu %0, %1, %2" : "=r"(addr) : "r"(self), "0"(idx));
    *(int *)(addr + 0x5C) = val5;
    {
        int c2 = p[1];
        register int idx2;
        register char *addr2;
        p[1] = c2 + 1;
        idx2 = c2 * 8;
        __asm__("addu %0, %1, %2" : "=r"(addr2) : "r"(self), "0"(idx2));
        *(int *)(addr2 + 0x60) = val6;
    }
    return 0;
}

inline int iosOmSendMailLink(int a0, int val5, int val6)
{
    int *node = D_0029C4F0[a0];
    int ret = 0;
    if (node != 0) {
        do {
            int full;
            int *p = (int *)((char *)node + 0x54);
            int count = p[1];

            if (count == 0x20) {
                full = -1;
            } else {
                register int idx;
                register char *addr;
                idx = count * 8;
                __asm__("addu %0, %1, %2" : "=r"(addr) : "r"(node), "0"(idx));
                full = 0;
                *(int *)(addr + 0x5C) = val5;
                {
                    int c2 = p[1];
                    register int idx2;
                    register char *addr2;
                    p[1] = c2 + 1;
                    idx2 = c2 * 8;
                    __asm__("addu %0, %1, %2" : "=r"(addr2) : "r"(node), "0"(idx2));
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
    char *g = D_0063A61C;
    IosMailBox *mb = (IosMailBox *)(g + 0x54);
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

INCLUDE_ASM("asm/nonmatchings/isys/obj_manager", _iosOmMain);

void iosOmMain(int a0, int a1, int a2, int a3)
{
    _iosOmMain(a0, a1, a2, a3);
}

/* the camera list node the DL walk hangs off (D_0063A614) and the per-kind
   GObj list heads (D_0029C530) */
typedef struct OmCam {
    char _p0[0x34];
    struct OmCam *next; /* 0x34 */
    char _p38[0x48 - 0x38];
    void (*dl)(struct OmCam *); /* 0x48 */
    int kindMask;               /* 0x4C */
    int drawMask;               /* 0x50 */
} OmCam;

typedef struct OmObj {
    char _p0[0x34];
    struct OmObj *next; /* 0x34 */
    char _p38[0x48 - 0x38];
    void (*dl)(struct OmObj *); /* 0x48 */
    char _p4C[0x4];
    int drawMask; /* 0x50 */
    char _p54[0x16C - 0x54];
    int active; /* 0x16C */
} OmObj;

extern OmCam *D_0063A614;
extern int D_0063A60C;
extern OmObj *D_0029C530[];

void iosOmCreateDL(void)
{
    OmCam *c;
    OmObj *g;
    int i;

    for (c = D_0063A614; c != 0; c = c->next) {
        if (D_0063A60C & 1) {
            if (c->dl != 0) {
                c->dl(c);
            }
        }
        for (i = 0; i < 0x20; i++) {
            if ((D_0063A60C >> i) & 1) {
                if ((c->kindMask >> i) & 1) {
                    for (g = D_0029C530[i]; g != 0; g = g->next) {
                        if (g->active != 0 && (c->drawMask & g->drawMask) != 0 && g->dl != 0) {
                            g->dl(g);
                        }
                    }
                }
            }
        }
    }
}
