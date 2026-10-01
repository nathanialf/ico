#include "debug.h"
#include "memory.h"
#include "obj_manager.h"
#include "act-game.h"
#include "commonact.h"
#include "mail-add-data.h"
#include "motionOrientManager.h"
#include "GifPacket.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "isys.h"
#include "geometryManager.h"
#include "thread.h"
#include "lineManager.h"
#include "pad.h"
#include "gobj_process.h"
#include "main.h"

/* one zero word that nothing reads */
static int actUnusedWord = 0; /* derived name */

#include "act.h"
#include "enemy_act.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"
#include "ios.h"
#include "fieldCollision.h"
#include "gamesys.h"

inline void ActSetStartBrainStatus(GObj *self, int status)
{
    Act *brain = GOBJ_ACT(self);
    if (brain != 0) {
        brain->brainStatus = status;
    }
}

void actChangeActBrain(GObj *a0, void (*a1)(), GProc **a2)
{
    GProc *old = *a2;
    GProc *n = actCreateSubThread(a1, 20);
    *a2 = n;
    if (old != 0) {
        debug_StdPrintfDummy("--b-- %p:act brain del %p\n", a0, n);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--b-- %p:act brain NULL %p\n", a0, n);
    }
}

void actChangeActMain(GObj *a0, void (*a1)(), GProc **a2)
{
    unsigned short fld = objLayout[a0->labelId].procPri;
    GProc *old = *a2;
    GProc *ret;
    if (((long long)fld << 10) == 0) {
        ret = isysGObjProcAdd(a0, a1, 0, 0x13);
    } else {
        ret = isysGObjProcAddS(a0, a1, 0, 0x13, (long long)fld << 10);
    }
    *a2 = ret;
    if (old != 0) {
        debug_StdPrintfDummy("--m-- %p:act main del %p\n", a0, ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--m-- %p:act main NULL %p\n", a0, ret);
    }
}

void actCreateMotionThread(void (*a0)(), int a1, GProc **a2)
{
    GProc *old = *a2;
    GProc *ret = isysGObjProcAdd(isysCurrentGObj, a0, 0, a1);
    *a2 = ret;
    if (old != 0) {
        debug_StdPrintfDummy("--t-- %p:act mot del %p\n", *(int *)((char *)old + 4), ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--t-- %p:act mot NULL %p\n", ret, ret);
    }
}

GProc *actCreateSubThread(void (*a0)(), int a1)
{
    unsigned short fld;
    GProc *p;

    if (debug_act_sub_thread) {
        Act *lval = GOBJ_ACT(isysCurrentGObj);
        debug_StdPrintfDummy("acst[%p]\n", isysCurrentGObj);
        debug_StdPrintfDummy("    [%d]\n", isysCurrentGObj->labelId);
        debug_StdPrintfDummy("    [%d]\n", isysCurrentGObj->kind);
        if (lval != 0) {
            debug_StdPrintfDummy("lval[%p]\n", lval);
            debug_StdPrintfDummy("    [%d]\n", lval->actMode);
        }
    }
    fld = objLayout[isysCurrentGObj->labelId].procPri;
    if (((long long)fld << 10) == 0) {
        p = isysGObjProcAdd(isysCurrentGObj, a0, 0, a1);
    } else {
        p = isysGObjProcAddS(isysCurrentGObj, a0, 0, a1, (long long)fld << 10);
    }
    p->thread.sleeping = 1;
    return p;
}

inline GProc *actCreateSubThreadGOppArg(void (*a0)(), int a1)
{
    GProc *p = isysGObjProcAddGOppArg(isysCurrentGObj, a0, 0, a1);

    p->thread.sleeping = 1;
    return p;
}

inline void actSetInterrupt(char *self, int val)
{
    *(int *)(self + 0x0) = val;
}

inline void ConvertStickToAbsCoord(void *a0, float *a1)
{
    Vec4 v = {{a1[3], 0.0f, -a1[4], 0.0f}};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)((int)matrixptr + 0x80));
    sceVu0ApplyMatrix(a0, m, &v);
}

inline void _ACTRun(int n)
{
    int i;
    if (n == 0) {
        for (;;) {
            iosThreadSleep();
        }
    }
    for (i = 0; i < n; i++) {
        iosThreadSleep();
    }
}

inline void _ACTWait(int a0)
{
    int count = (a0 * ((0x3C - systemStatus[0] * 0xA) / systemStatus[1])) / 0x3C;
    if (a0 != 0) {
        if (count == 0) {
            count = 1;
        }
    }
    _ACTRun(count);
}

inline void actWaitCondition(int a0, int a1)
{
    int t = a0 & a1;
    if (t == 0) {
        do {
            int count = (0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 0x3C;
            int n = 1;
            if (count != 0) {
                n = count;
            }
            if (n == 0) {
                for (;;) {
                    iosThreadSleep();
                }
            }
            if (n > 0) {
                int i = n;
                do {
                    iosThreadSleep();
                    i--;
                } while (i != 0);
            }
        } while (t == 0);
    }
}

void after_func_exec(void *self, int oldst, int newst)
{
    Act *g = GOBJ_ACT(self);

    if (actModeTbl[oldst].ent[g->actKind].word4 != actModeTbl[newst].ent[g->actKind].word4) {
        if (g->after != 0) {
            (*(void (**)(char *))((char *)g + 0x14))(self);
            g->after = 0;
        }
    }
    if (actModeTbl[oldst].onChain != actModeTbl[newst].onChain) {
        if (g->after != 0) {
            (*(void (**)(char *))((char *)g + 0x14))(self);
            g->after = 0;
        }
    }
    if (actModeTbl[oldst].ent[g->actKind].word4 == 0 &&
        actModeTbl[newst].ent[g->actKind].word4 == 0 && actModeTbl[oldst].onChain == 0 &&
        actModeTbl[newst].onChain == 0) {
        if (g->after != 0) {
            (*(void (**)(char *))((char *)g + 0x14))(self);
            g->after = 0;
        }
    }
}

inline void actInitialize_geo(void *self) {}

void actInitialize_ext_charcter(GObj *self)
{
    Act *g = GOBJ_ACT(self);
    char *p = (char *)iosMallocDebug(ios_partition_seki, 0x400, __FILE__, 885);

    memset(p, 0, 0x400);
    *(char **)((char *)g + 0x680) = p;
    *(float *)(*(char **)((int)GOBJ_ACT(self) + 0x680) + 0x58) = 1.0f;
    GOBJ_ACT(self)->enemy->stonePair = -1;
    *(int *)(*(char **)((int)GOBJ_ACT(self) + 0x680) + 0x2A4) = -1;
    *(int *)(*(char **)((int)GOBJ_ACT(self) + 0x680) + 0x2A8) = -1;
    *(int *)(*(char **)((int)GOBJ_ACT(self) + 0x680) + 0x2AC) = -1;
    *(int *)(*(char **)((int)GOBJ_ACT(self) + 0x680) + 0x2B0) = -1;
    InitMailAdditionalData(self, *(char **)((int)GOBJ_ACT(self) + 0x680));
}

/* The actor object: only the work pointer at +0x164 matters here. */
typedef struct { /* field names derived */
    char pad0[356];
    int work;
} ActSelf; /* derived name */

typedef union { /* field names derived */
    float f;
    int i;
} ActFWord; /* derived name */

/* The extended work block hung off the work block at +0x688; the three
   ten-entry histories at 0x900, 0x928 and 0x950 are read back in BeforeFunc. */
typedef struct { /* field names derived */
    char pad0[2304];
    int a900[10];
    int a928[10];
    int a950[10];
} ActExt; /* derived name */

void actInitialize_only_charcter(char *self)
{
    Act *g = GOBJ_ACT(self);
    char *p = (char *)iosMallocDebug(ios_partition_seki, 0x980, __FILE__, 907);
    Vec4 *q;
    int i;

    memset(p, 0, 0x980);
    g->work = (int)p;
    q = (Vec4 *)*(char **)(*(char **)(self + 0x164) + 0x688);
    ((Vec4 *)((char *)q + 0x320))->f[0] = GOBJ_SUB(self)->root.ikRate0;
    ((Vec4 *)((char *)q + 0x320))->f[1] = GOBJ_SUB(self)->root.ikRate1;
    ((Vec4 *)((char *)q + 0x320))->f[2] = GOBJ_SUB(self)->root.ikRate2;
    ((ActFWord *)((char *)q + 0x330))->f = -1.0f;
    ((ActFWord *)((char *)q + 0x334))->f = 1.0f;
    ((ActFWord *)((char *)q + 0x348))->f = 3.0f;
    *(int *)((char *)q + 0x800) = 0;
    for (i = 0; i < 10; i++) {
        ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a900[i] = 0;
        ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a928[i] = 0;
        ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a950[i] = 0x1A2;
    }
}

Act *actInitialize(GObj *self)
{
    char *w = (char *)iosMallocDebug(ios_partition_seki, 0x850, __FILE__, 934);

    *(char **)((char *)self + 0x164) = w;
    memset(w, 0, 0x850);

    *(void **)(w + 0x4) = isysCurrentGObjProcess;
    *(int *)(w + 0x0) = 0;
    *(int *)(w + 0x8) = 0;
    *(int *)(w + 0xC) = 0;
    *(int *)(w + 0x14) = 0;
    *(int *)(w + 0x18) = 0;
    *(int *)(w + 0x680) = 0;
    *(int *)(w + 0x688) = 0;
    *(int *)(w + 0x10) = 0;

    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 32;
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 33;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 39);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 40);
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 43;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 44);
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 46;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 47);
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 48;
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 49;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 51);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 52);

    *(int *)(w + 0x28) = 0;
    *(int *)(w + 0x34) = 0;
    *(int *)(w + 0x38) = 0;
    *(int *)(w + 0x4C) = 0;
    *(int *)(w + 0x350) = 0;
    *(int *)(w + 0x38C) = 0;
    *(int *)(w + 0x3D4) = 0;
    *(int *)(w + 0x48) = -1;
    *(int *)(w + 0xD0) = 0;
    *(int *)(w + 0xD4) = 0;
    *(int *)(w + 0x130) = 0;
    *(int *)(w + 0x13C) = 0;
    *(int *)(w + 0x148) = 0;
    *(int *)(w + 0x14C) = 0;
    *(int *)(w + 0x150) = 0;
    *(int *)(w + 0x154) = 0;
    *(int *)(w + 0x440) = 0;
    *(int *)(w + 0x444) = 0;
    *(int *)(w + 0x448) = 0;
    *(int *)(w + 0x44C) = 0;
    *(int *)(w + 0x54) = 0;

    ((ActStatusWord *)(w + 0x20))->q |= 0x800000;
    ((ActStatusWord *)(w + 0x20))->q &= ~0x3000000;
    ((ActStatusWord *)(w + 0x20))->q |= 0x20000000;
    ((ActStatusWord *)(w + 0x20))->q |= 1LL << 43;
    ((ActStatusWord *)(w + 0x20))->q |= 1LL << 46;

    *(int *)(w + 0x3A4) = 0;
    *(int *)(w + 0x3C4) = -1;
    {
        /* the chase is read as `int` */
        Act *p = GOBJ_ACT(self);
        p->attacker = 0;
        p->hit = 0;
    }
    ((Act *)w)->padConf = iosPadConfDefault;

    memset(w + 0x170, 0, 0x20);
    memset(w + 0x134, 0, 0x8);
    memset(w + 0x190, 0, 0x20);
    memset(w + 0x47C, 0, 0x10);
    memset(w + 0x48C, 0, 0x10);
    memset(w + 0x49C, 0, 0x10);
    memset(w + 0x4B0, 0x0, 0x1D0);
    memset(w + 0x2D8, 0, 0x60);
    memset(w + 0x338, 0, 0x18);

    return (Act *)w;
}

inline int ACTReserveTarget(GObj *self, void *a1, int a2)
{
    Act *g = GOBJ_ACT(self);
    if (g->reserved == 0) {
        *(char **)((char *)g + 0x13C) = self;
        g->reservedMail = a2;
        iosOmSendMail(self, a2, a1);
        return 1;
    }
    return 0;
}

/* The interrupt list lives at self+0x54: a count at +4 and 8-byte entries
   from +8. */
typedef struct { /* field names derived */
    int id;
    void *f4;
} IntrEnt; /* derived name */

typedef struct { /* field names derived */
    int f0;
    int n;
    IntrEnt ent[1];
} IntrList; /* derived name */

typedef struct { /* field names derived */
    int w[8];
} IntrOrient; /* derived name */

IntrMail *act_check_intr_list(void *self, IntrMail *m, void **out)
{
    IntrList *k = (IntrList *)(self + 0x54);
    Act *w = GOBJ_ACT(self);
    IntrOrient buf;
    int i;

    if (m != 0) {
        while ((short)m->kind != 429) {
            if ((m->flags >> 18) & 1) {
                for (i = 0; i < k->n; i++) {
                    int mot;
                    char *p;
                    if (w->reserved != 0 && w->reservedMail != k->ent[i].id) {
                        continue;
                    }
                    if (k->ent[i].id != (short)m->kind) {
                        continue;
                    }
                    mot = ACTGetOrientFromIntrK(self, k->ent[i].id, &buf, i);
                    p = SetMotionRequest(self, mot, *(MotOriReq *)&buf);
                    *(char **)((char *)w + 0x130) = p;
                    if (*(int *)(p + 0xC) == 0 &&
                        (*(unsigned short *)((char *)m + 0x16) & 1) == 0 &&
                        (w->actMode != 0 || m->mode == 0)) {
                        continue;
                    }
                    w->intrMot = mot;
                    *(void **)((char *)w + 0x2C) = k->ent[i].f4;
                    *(char **)((char *)w + 0x30) = GetMailAdditionalData(self, i);
                    *(IntrOrient *)(*(char **)((int)GOBJ_ACT(self) + 0x688) + 0x8B0) = buf;
                    *out = &k->ent[i];
                    return m;
                }
            }
            m++;
        }
    }
    return 0;
}

void act_check_mail(void *self, IntrMail *m)
{
    IntrList *k = (IntrList *)(self + 0x54);
    Act *w = GOBJ_ACT(self);
    int i;
    int id;

    if (m == 0) {
        debug_StdPrintfDummy("intr list is null\n");
        return;
    }
    for (i = 0; i < k->n; i++) {
        id = k->ent[i].id;
        switch (id) {
        case 0x10D:
            w->flags20.ll |= 0x100;
            break;
        case 0x1F:
            w->flags20.ll |= 0x10;
            break;
        case 0x20:
            w->flags20.ll |= 0x20;
            break;
        case 0x3D:
            w->flags18.ll |= 0x8000LL << 47;
            break;
        case 0x1A9:
            GOBJ_ACT(self)->enemy->word2B0 = 0;
            break;
        case 0xF:
            w->flags20.ll |= 1;
            break;
        case 0x10:
            w->flags18.ll |= 0x8000LL << 48;
            break;
        case 0x7:
            w->flags20.ll |= 0x400000;
            break;
        case 0x22:
            w->flags20.ll |= 0x40;
            break;
        }
    }
    while ((short)m->kind != 429) {
        if ((m->flags >> 18) & 1) {
            for (i = 0; i < k->n; i++) {
                id = k->ent[i].id;
                if (id == (short)m->kind) {
                    if (m->handler != 0) {
                        m->handler(self, id, k->ent[i].f4);
                    }
                }
            }
        }
        m++;
    }
}

typedef union { /* field names derived */
    float f;
    int i;
} ActFloat; /* derived name */

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* one flag per mail list: a list whose flag is set is not checked for an
   interrupt while the status record's b11 is set */
typedef struct { /* field names derived */
    unsigned int w[4];
} IntrSkip; /* derived name */

void BeforeFunc(GObj *self)
{
    Act *w = GOBJ_ACT(self);
    char *mb = (char *)self + 0x54;
    IntrMail *intr;
    char *g;
    void *act;
    IntrEnt *ent;
    int i;
    int old;

    ((Act *)(char *)w)->intrArg = 0;
    *(char **)((char *)w + 0x30) = 0;
    w->modeFrame += 1;
    w->frame += 1;
    w->flags18.ll &= ~(1LL << 52);
    w->flags18.ll &= ~(1LL << 62);
    w->flags18.ll &= ~(1LL << 63);
    w->flags20.ll &= ~(1LL << 0);
    w->flags20.ll &= ~(1LL << 1);
    w->flags20.ll &= ~(1LL << 2);
    w->flags20.ll &= ~(1LL << 3);
    w->flags20.ll &= ~(1LL << 4);
    w->flags20.ll &= ~(1LL << 5);
    w->flags20.ll &= ~(1LL << 8);
    w->flags20.ll &= ~(1LL << 10);
    w->flags20.ll &= ~(1LL << 18);
    w->flags20.ll &= ~(1LL << 22);
    w->flags20.ll &= ~(1LL << 37);
    w->flags20.ll &= ~(1LL << 44);
    w->flags20.ll &= ~(1LL << 45);
    w->flags20.ll &= ~(1LL << 12);
    w->flags20.ll &= ~(1LL << 31);
    w->flags18.ll &= ~(1LL << 36);
    w->flags18.ll &= ~(1LL << 37);
    w->flags18.ll &= ~(1LL << 38);
    w->flags20.ll &= ~(1LL << 35);
    ((Act *)(char *)w)->gobj80 = 0;
    ((Act *)(char *)w)->gobj84 = 0;
    if (self == (void *)boyGObj) {
        ActWork *p = GOBJ_WORK(self);

        ((ActFloat *)((char *)GOBJ_SUB(self) + 0x45C))->f = p->defIkRate0;
        ((ActFloat *)((char *)GOBJ_SUB(self) + 0x464))->f = p->defIkRate1;
        ((ActFloat *)((char *)GOBJ_SUB(self) + 0x468))->f = p->defIkRate2;
    }
    if (w->msgBlockTimer != 0) {
        w->msgBlockTimer -= 1;
    }
    {
        IntrMail *mails[5] = {&actIntrList[0], &actIntrList[3], (IntrMail *)w->mail,
                              (IntrMail *)w->mainMail, (IntrMail *)0xFFFFFFFF};
        IntrSkip skip = {{0, 1, 0, 1}};

        ACTSendMailCorrect(self, actModeTbl[w->actMode].mail);
        for (i = 0; i < *(int *)(mb + 4); i++) {
            ((IntrList *)mb)->ent[i].id =
                _ACTCorrectMsg(self, *(int *)(mb + 8 + i * 8), *(void **)(mb + 0xC + i * 8));
        }
        ACTRunIntrCorrect(self, mails[1], mails[2]);
        for (i = 0; mails[i] != (IntrMail *)0xFFFFFFFF; i++) {
            act_check_mail(self, mails[i]);
        }
        intr = 0;
        for (i = 0; mails[i] != (IntrMail *)0xFFFFFFFF; i++) {
            if (skip.w[i] == 0 || actModeTbl[w->actMode].skipMarked == 0) {
                intr = act_check_intr_list(self, mails[i], (void **)&ent);
                if (intr != 0) {
                    break;
                }
            }
        }
    }
    g = *(char **)((char *)self + 0x15C);
    *(char **)((char *)w + 0x40) = *(char **)(g + 0x540);
    if ((((&motionKind[*(int *)(*(char **)((char *)self + 0x15C) + 0x4A0)])->flags.word >> 1) &
         1) != 0 &&
        GOBJ_SUB(self)->ctrl.animFrame < 3.0f) {
        w->flags20.ll |= 1LL << 18;
    }
    if (intr != 0) {
        old = w->intrKind;
        w->intrKind = (short)intr->kind;
        act = (void *)actModeTbl[intr->mode].ent[w->actKind].act;
        if (act != 0) {
            after_func_exec(self, w->actMode, intr->mode);
            if (*(int *)((char *)w + 0x18) != 0) {
                (*(void (**)(char *))((char *)w + 0x18))(self);
                *(int *)((char *)w + 0x18) = 0;
            }
            w->modeFrame = 0;
            for (i = 9; i > 0; i--) {
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a900[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a900[i - 1];
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a928[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a928[i - 1];
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a950[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a950[i - 1];
            }
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a900[0] = w->actMode;
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a928[0] = w->frame;
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a950[0] = old;
            w->actMode = intr->mode;
            w->flags18.ll = (w->flags18.ll & ~(1LL << 39)) |
                            ((unsigned long long)actModeTbl[w->actMode].bit10 << 39);
            w->flags18.ll = (w->flags18.ll & ~(1LL << 50)) |
                            ((unsigned long long)actModeTbl[intr->mode].bit12 << 50);
            w->flags20.ll &= ~(1LL << 11);
            *(IntrMail **)((char *)w + 0xD4) = &actIntrList[actModeTbl[w->actMode].intrList];
            actChangeActMain(isysCurrentGObj, act, &w->actProc);
        }
        if (intr->motion != 0) {
            w->pushDir = 0;
            actCreateMotionThread(intr->motion, 21, &w->motProc);
        }
        if (intr->extra != 0) {
            actCreateMotionThread(intr->extra, 22, &w->motProc2);
        }
        if (intr->accept != 0) {
            intr->accept(self, ent->id, ent->f4);
        }
        ACTAcceptMail(self, (short)intr->kind);
    }
    ((ActStatusWord *)((char *)w + 0x138))->q &= ~(1LL << 0);
    w->reserved = 0;
    *(int *)(mb + 4) = 0;
    ClearMailAdditionalData(self);
    ACTGame_BeforeFunc(self);
    entesty = 100;
}

/* The floor/wall collision work block: the 0xC0-byte record src/act-env.c
   and src/girl_act.c carry, with the attribute word at +0x98 that
   CompareAttribute takes. */
typedef struct {  /* field names derived */
    float a[4];   /* 0x00 start point   */
    float b[4];   /* 0x10 end point     */
    float pos[4]; /* 0x20 clipped point */
    char pad30[64];
    float f_70;
    char pad74[20];
    int f_88;
    char pad8C[8];
    int f_94;
    int f_98;
    char pad9C[36];
} ActClipWork; /* derived name */

/* The stick reading iosPadGetStick fills in: the 0x20-byte record
   omori/src/camera-ico2.c carries, read here through its two direction
   words and its magnitude. */
typedef struct { /* field names derived */
    int x;       /* 0x00 */
    int y;       /* 0x04 */
    char pad8[4];
    float dx;  /* 0x0C */
    float dz;  /* 0x10 */
    float mag; /* 0x14 */
    char pad18[8];
} ActPadStick; /* derived name */

extern void GetLowerPlaneCollision(void *work, void *pos);

/* this TU passes the packet priority that the prototype in
   seki/include/GifPacket.h leaves out */

void ACTDebugMove(GObj *a0, int a1)
{
    GObj *self = (char *)a0;
    float dir[4];
    float pos[4];
    ActPadStick st;
    Act *ext;
    SkelNode *p;
    float h;
    int mode = 1;
    int dbg = 0; /* local debug switch, see the test at the end of the loop */

    ext = GOBJ_ACT(self);
    p = GOBJ_SUB(self)->skel;
    h = (p != 0) ? p->pos[1] : 0.0f;
    DisableChangeRootUpdateMode(self);
    SetRootUpdateMode(self, 0);
    while (((ext->padNow & 1) != 0 || mode == 1) && self == (char *)CurrentTargetGObj) {
        _ACTWait(1);
        iosPadRead((char *)ext + 0x2D8);
        iosPadGetStick((char *)ext + 0x2D8, (char *)ext + 0x338, 0, 2, 2, 0);
        iosPadGetStick((char *)ext + 0x2D8, &st, 1, 2, 2, 0);
        if (0.001f < ext->stickMag) {
            ConvertStickToAbsCoord(dir, (float *)((char *)ext + 0x338));
        }
        GetRootPosition(pos, self);
        pos[0] += dir[0] * ext->stickMag * 32.0f;
        pos[2] += dir[2] * ext->stickMag * 32.0f;
        if (0.001f < st.mag) {
            mode = 1;
        }
        switch (mode) {
        case 0: {
            ActClipWork w;

            if ((ext->padTrg & 0x200) != 0) {
                sceVu0CopyVector(w.a, pos);
                sceVu0CopyVector(w.b, pos);
                w.b[1] -= 10000.0f;
                ClipFloorR(&w);
                if (w.f_94 != 0) {
                    pos[1] = w.pos[1] - h;
                    break;
                }
            }
            sceVu0CopyVector(w.a, pos);
            sceVu0CopyVector(w.b, pos);
            w.a[1] -= 10.0f;
            w.b[1] += 10000.0f;
            ClipFloor(&w);
            if (w.f_94 == 0) {
                sceVu0CopyVector(w.a, pos);
                sceVu0CopyVector(w.b, pos);
                w.b[1] -= 10000.0f;
                ClipFloorR(&w);
                if (w.f_94 == 0) {
                    break;
                }
            }
            pos[1] = w.pos[1] - h;
            break;
        }
        case 1:
            if ((ext->padTrg & 0x200) != 0) {
                SetRootUpdateMode(self, 1);
                mode = 0;
            } else {
                pos[1] += st.dz * st.mag * 32.0f;
            }
            break;
        }
        SetDirectRootPositionNoFitting(self, pos);
        {
            ActClipWork w;

            GetLowerPlaneCollision(&w, pos);
            if (w.f_94 != 0 && CompareAttribute(w.f_98, 0x800) == 0 &&
                CompareAttribute(w.f_98, 0x900) == 0) {
                ActClipWork w2;

                sceVu0CopyVector(w2.a, pos);
                sceVu0CopyVector(w2.b, pos);
                w2.b[1] += 10000.0f;
                ClipFloor(&w2);
                if (w2.f_94 != 0) {
                    sceVu0IVECTOR col = {32, 32, 255, 128};

                    w2.a[1] += 200.0f;
                    gif_StartPacketPri(11);
                    MatrixDrive_PushMatrix();
                    gif_SetAlpha(1, 5, 128);
                    gif_SetZWrite(0);
                    gif_SetZTest(1);
                    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
                    DrawLineG(w2.a, col, w2.pos, col, 0);
                    MatrixDrive_PopMatrix();
                    gif_EndPacket();
                }
            } else {
                SetSimplePlane((float *)((char *)GOBJ_SUB(self) + 0x1D0), 0.0f, -1.0f, 0.0f,
                               pos[1] + h);
                CopyVector((char *)GOBJ_SUB(self) + 0x250, pos);
                GOBJ_SUB(self)->root.footPos[1] += h;
            }
        }
        debug_PrintfDummy(10, 185, 0xFFFFFF00u, "LW's coord:");
        debug_PrintfDummy(20, 195, 0xFFFFFF00u, "POS X:%8.2f Y:%8.2f Z:%8.2f", -pos[0], -pos[1],
                          -pos[2]);
        {
            ActClipWork w3;

            sceVu0CopyVector(w3.a, pos);
            sceVu0CopyVector(w3.b, pos);
            w3.a[1] -= 200.0f;
            w3.b[1] += 200.0f;
            ClipFloor(&w3);
            gif_StartPacketPri(11);
            gif_SetAlpha(1, 5, 128);
            gif_SetZWrite(0);
            gif_SetZTest(1);
            MatrixDrive_PushMatrix();
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            {
                sceVu0IVECTOR col2 = {128, 128, 128, 128};
                float q1[4];
                float q2[4];
                float q3[4];
                float q4[4];

                CopyVector(q1, pos);
                CopyVector(q2, pos);
                CopyVector(q3, pos);
                CopyVector(q4, pos);
                q1[0] -= 200.0f;
                q2[0] += 200.0f;
                q3[2] -= 200.0f;
                q4[2] += 200.0f;
                DrawLineG(w3.a, col2, w3.b, col2, 0);
                DrawLineG(q1, col2, q2, col2, 0);
                DrawLineG(q3, col2, q4, col2, 0);
            }
            MatrixDrive_PopMatrix();
            gif_EndPacket();
            /* a local debug switch, off: draw the five clip lines in blue */
            if (dbg) {
                ActClipWork w4;
                sceVu0IVECTOR col = {0, 64, 255, 128};
                Vec4 pt[5];
                int i;

                for (i = 0; i < 5; i++) {
                    DrawLineG(w4.a, col, pt[i].f, col, 0);
                }
            }
        }
    }
    {
        ActClipWork w3;

        sceVu0CopyVector(w3.a, pos);
        sceVu0CopyVector(w3.b, pos);
        w3.a[1] -= 10.0f;
        w3.b[1] += 10000.0f;
        ClipFloor(&w3);
        if (w3.f_94 != 0 && CompareAttribute(w3.f_98, 0x800) == 0 &&
            CompareAttribute(w3.f_98, 0x900) == 0) {
            pos[1] = w3.pos[1] - h;
            SetDirectRootPositionNoFitting(self, pos);
            EnableChangeRootUpdateMode(self);
            AdjustMotionHeightToNearestField(self);
        }
    }
    EnableChangeRootUpdateMode(self);
}
