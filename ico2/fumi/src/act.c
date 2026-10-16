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

void actChangeActBrain(GObj *self, void (*func)(), GProc **proc)
{
    GProc *old = *proc;
    GProc *n = actCreateSubThread(func, 20);
    *proc = n;
    if (old != 0) {
        debug_StdPrintfDummy("--b-- %p:act brain del %p\n", self, n);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--b-- %p:act brain NULL %p\n", self, n);
    }
}

void actChangeActMain(GObj *self, void (*func)(), GProc **proc)
{
    unsigned short fld = objLayout[self->labelId].procPri;
    GProc *old = *proc;
    GProc *ret;
    if (((long long)fld << 10) == 0) {
        ret = isysGObjProcAdd(self, func, 0, 0x13);
    } else {
        ret = isysGObjProcAddS(self, func, 0, 0x13, (long long)fld << 10);
    }
    *proc = ret;
    if (old != 0) {
        debug_StdPrintfDummy("--m-- %p:act main del %p\n", self, ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--m-- %p:act main NULL %p\n", self, ret);
    }
}

void actCreateMotionThread(void (*func)(), int pri, GProc **proc)
{
    GProc *old = *proc;
    GProc *ret = isysGObjProcAdd(isysCurrentGObj, func, 0, pri);
    *proc = ret;
    if (old != 0) {
        debug_StdPrintfDummy("--t-- %p:act mot del %p\n", *(int *)((char *)old + 4), ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--t-- %p:act mot NULL %p\n", ret, ret);
    }
}

inline GProc *actCreateSubThread(void (*func)(), int pri)
{
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
    p = isysGObjProcAdd(isysCurrentGObj, func, 0, pri);
    p->thread.sleeping = 1;
    return p;
}

inline GProc *actCreateSubThreadGOppArg(void (*func)(), int pri)
{
    GProc *p = isysGObjProcAddGOppArg(isysCurrentGObj, func, 0, pri);

    p->thread.sleeping = 1;
    return p;
}

inline void actSetInterrupt(char *self, int val)
{
    *(int *)(self + 0x0) = val;
}

inline void ConvertStickToAbsCoord(void *out, IosPadStick *stick)
{
    Vec4 v = {{stick->dx, 0.0f, -stick->dz, 0.0f}};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)((int)matrixptr + 0x80));
    sceVu0ApplyMatrix(out, m, &v);
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

inline void _ACTWait(int frames)
{
    int count = (frames * ((60 - systemStatus[0] * 10) / systemStatus[1])) / 60;
    if (frames != 0) {
        if (count == 0) {
            count = 1;
        }
    }
    _ACTRun(count);
}

inline void actWaitCondition(int value, int mask)
{
    int t = value & mask;
    if (t == 0) {
        do {
            int count = (60 - systemStatus[0] * 10) / systemStatus[1] / 60;
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

static void after_func_exec(void *self, int oldst, int newst)
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
    char *p = (char *)iosMallocDebug(ios_partition_seki, 0x400, __FILE__, 850);

    memset(p, 0, 0x400);
    *(char **)((char *)g + 0x670) = p;
    *(float *)(*(char **)((int)GOBJ_ACT(self) + 0x670) + 0x58) = 1.0f;
    GOBJ_ACT(self)->enemy->stonePair = -1;
    *(int *)(*(char **)((int)GOBJ_ACT(self) + 0x670) + 0x2A4) = -1;
    *(int *)(*(char **)((int)GOBJ_ACT(self) + 0x670) + 0x2A8) = -1;
    *(int *)(*(char **)((int)GOBJ_ACT(self) + 0x670) + 0x2AC) = -1;
    *(int *)(*(char **)((int)GOBJ_ACT(self) + 0x670) + 0x2B0) = -1;
    InitMailAdditionalData(self, *(char **)((int)GOBJ_ACT(self) + 0x670));
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

/* The extended work block hung off the work block at +0x678; the three
   ten-entry histories at 0x830, 0x858 and 0x880 are read back in BeforeFunc. */
typedef struct { /* field names derived */
    char pad0[2096];
    int a900[10];
    int a928[10];
    int a950[10];
} ActExt; /* derived name */

inline void actInitialize_only_charcter(char *self)
{
    Act *g = GOBJ_ACT(self);
    char *p = (char *)iosMallocDebug(ios_partition_seki, 0x8B0, __FILE__, 872);
    Vec4 *q;
    int i;

    memset(p, 0, 0x8B0);
    g->work = (int)p;
    q = (Vec4 *)*(char **)(*(char **)(self + 0x164) + 0x678);
    ((Vec4 *)((char *)q + 0x320))->f[0] = GOBJ_SUB(self)->root.ikRate0;
    ((Vec4 *)((char *)q + 0x320))->f[1] = GOBJ_SUB(self)->root.ikRate1;
    ((Vec4 *)((char *)q + 0x320))->f[2] = GOBJ_SUB(self)->root.ikRate2;
    ((ActFWord *)((char *)q + 0x330))->f = -1.0f;
    ((ActFWord *)((char *)q + 0x334))->f = 1.0f;
    *(int *)((char *)q + 0x730) = 0;
    for (i = 0; i < 10; i++) {
        ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a900[i] = 0;
        ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a928[i] = 0;
        ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a950[i] = 388;
    }
}

Act *actInitialize(GObj *self)
{
    char *w = (char *)iosMallocDebug(ios_partition_seki, 0x840, __FILE__, 898);

    *(char **)((char *)self + 0x164) = w;
    memset(w, 0, 0x840);

    *(void **)(w + 0x4) = isysCurrentGObjProcess;
    *(int *)(w + 0x0) = 0;
    *(int *)(w + 0x8) = 0;
    *(int *)(w + 0xC) = 0;
    *(int *)(w + 0x14) = 0;
    *(int *)(w + 0x18) = 0;
    *(int *)(w + 0x670) = 0;
    *(int *)(w + 0x678) = 0;
    *(int *)(w + 0x10) = 0;

    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 32;
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 33;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 35);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 36);
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 38;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 39);
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 41;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 42);
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 43;
    ((ActStatusWord *)(w + 0x18))->q |= 1LL << 44;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 46);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 47);

    *(int *)(w + 0x24) = 0;
    *(int *)(w + 0x30) = 0;
    *(int *)(w + 0x34) = 0;
    *(int *)(w + 0x48) = 0;
    *(int *)(w + 0x340) = 0;
    *(int *)(w + 0x37C) = 0;
    *(int *)(w + 0x3C4) = 0;
    *(int *)(w + 0x44) = -1;
    *(int *)(w + 0xC0) = 0;
    *(int *)(w + 0xC4) = 0;
    *(int *)(w + 0x120) = 0;
    *(int *)(w + 0x12C) = 0;
    *(int *)(w + 0x138) = 0;
    *(int *)(w + 0x13C) = 0;
    *(int *)(w + 0x140) = 0;
    *(int *)(w + 0x144) = 0;
    *(int *)(w + 0x430) = 0;
    *(int *)(w + 0x434) = 0;
    *(int *)(w + 0x438) = 0;
    *(int *)(w + 0x43C) = 0;
    *(int *)(w + 0x50) = 0;

    ((ActStatusWord *)(w + 0x20))->q |= 0x1000;
    ((ActStatusWord *)(w + 0x20))->q &= ~0x2000;
    ((ActStatusWord *)(w + 0x20))->q |= 0x10000;
    ((ActStatusWord *)(w + 0x20))->q |= 0x4000000;

    *(int *)(w + 0x394) = 0;
    *(int *)(w + 0x3B4) = -1;
    {
        /* the chase is read as `int` */
        Act *p = GOBJ_ACT(self);
        p->attacker = 0;
        p->hit = 0;
    }
    ((Act *)w)->padConf = iosPadConfDefault;

    memset(w + 0x160, 0, 0x20);
    memset(w + 0x124, 0, 0x8);
    memset(w + 0x180, 0, 0x20);
    memset(w + 0x46C, 0, 0x10);
    memset(w + 0x47C, 0, 0x10);
    memset(w + 0x48C, 0, 0x10);
    memset(w + 0x4A0, 0x0, 0x1D0);
    memset(w + 0x2C8, 0, 0x60);
    memset(w + 0x328, 0, 0x18);

    return (Act *)w;
}

inline int ACTReserveTarget(GObj *self, void *arg, int mail)
{
    Act *g = GOBJ_ACT(self);
    if (g->reserved == 0) {
        *(char **)((char *)g + 0x12C) = self;
        g->reservedMail = mail;
        iosOmSendMail(self, mail, arg);
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

static IntrMail *act_check_intr_list(void *self, IntrMail *m, void **out)
{
    IntrList *k = (IntrList *)(self + 0x54);
    Act *w = GOBJ_ACT(self);
    MotOriReq buf;
    int i;

    if (m != 0) {
        while ((short)m->kind != 396) {
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
                    p = SetMotionRequest(self, mot, buf);
                    *(char **)((char *)w + 0x120) = p;
                    if (*(int *)(p + 0xC) == 0 &&
                        (*(unsigned short *)((char *)m + 0x16) & 1) == 0 &&
                        (w->actMode != 0 || m->mode == 0)) {
                        continue;
                    }
                    w->intrMot = mot;
                    *(void **)((char *)w + 0x28) = k->ent[i].f4;
                    *(char **)((char *)w + 0x2C) = GetMailAdditionalData(self, i);
                    *(MotOriReq *)(*(char **)((int)GOBJ_ACT(self) + 0x678) + 0x7E0) = buf;
                    *out = &k->ent[i];
                    return m;
                }
            }
            m++;
        }
    }
    return 0;
}

static void act_check_mail(void *self, IntrMail *m)
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
        case 253:
            w->flags18.ll |= 0x8000LL << 48;
            break;
        case 0x1F:
            w->flags18.ll |= 0x8000LL << 44;
            break;
        case 0x20:
            w->flags18.ll |= 0x8000LL << 45;
            break;
        case 58:
            w->flags18.ll |= 0x8000LL << 38;
            break;
        case 395:
            GOBJ_ACT(self)->enemy->word2B0 = 0;
            break;
        case 0xF:
            w->flags18.ll |= 0x8000LL << 40;
            break;
        case 0x10:
            w->flags18.ll |= 0x8000LL << 39;
            break;
        case 0x7:
            w->flags20.ll |= 0x800;
            break;
        case 0x22:
            w->flags18.ll |= 0x8000LL << 46;
            break;
        }
    }
    while ((short)m->kind != 396) {
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
    *(char **)((char *)w + 0x2C) = 0;
    w->modeFrame += 1;
    w->frame += 1;
    w->flags18.ll &= ~(1LL << 47);
    w->flags18.ll &= ~(1LL << 53);
    w->flags18.ll &= ~(1LL << 54);
    w->flags18.ll &= ~(1LL << 55);
    w->flags18.ll &= ~(1LL << 56);
    w->flags18.ll &= ~(1LL << 57);
    w->flags18.ll &= ~(1LL << 58);
    w->flags18.ll &= ~(1LL << 59);
    w->flags18.ll &= ~(1LL << 60);
    w->flags18.ll &= ~(1LL << 63);
    w->flags20.ll &= ~(1LL << 1);
    w->flags20.ll &= ~(1LL << 7);
    w->flags20.ll &= ~(1LL << 11);
    w->flags20.ll &= ~(1LL << 21);
    w->flags20.ll &= ~(1LL << 27);
    w->flags20.ll &= ~(1LL << 28);
    w->flags20.ll &= ~(1LL << 3);
    w->flags20.ll &= ~(1LL << 18);
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
    *(char **)((char *)w + 0x3C) = *(char **)(g + 0x540);
    if ((((&motionKind[*(int *)(*(char **)((char *)self + 0x15C) + 0x4A0)])->flags.word >> 3) &
         1) != 0 &&
        GOBJ_SUB(self)->ctrl.animFrame < 3.0f) {
        w->flags20.ll |= 1LL << 7;
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
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a900[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a900[i - 1];
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a928[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a928[i - 1];
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a950[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a950[i - 1];
            }
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a900[0] = w->actMode;
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a928[0] = w->frame;
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x678))->a950[0] = old;
            w->actMode = intr->mode;
            w->flags18.ll = (w->flags18.ll & ~(1LL << 35)) |
                            ((unsigned long long)actModeTbl[w->actMode].attractWait << 35);
            w->flags18.ll = (w->flags18.ll & ~(1LL << 45)) |
                            ((unsigned long long)actModeTbl[intr->mode].bit1 << 45);
            w->flags20.ll &= ~(1LL << 2);
            *(IntrMail **)((char *)w + 0xC4) = &actIntrList[actModeTbl[w->actMode].intrList];
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
    }
    ((ActStatusWord *)((char *)w + 0x128))->q &= ~(1LL << 0);
    w->reserved = 0;
    *(int *)(mb + 4) = 0;
    ClearMailAdditionalData(self);
    ACTGame_BeforeFunc(self);
    entesty = 100;
}

/* this TU passes the packet priority that the prototype in
   seki/include/GifPacket.h leaves out */

void ACTDebugMove(GObj *self, int a1)
{
    float dir[4];
    float pos[4];
    IosPadStick st;
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
    while (((ext->pad.now & 1) != 0 || mode == 1) && self == CurrentTargetGObj) {
        _ACTWait(1);
        iosPadRead(&ext->pad);
        iosPadGetStick(&ext->pad, &ext->stick, 0, 2, 2, 0);
        iosPadGetStick(&ext->pad, &st, 1, 2, 2, 0);
        if (0.001f < ext->stick.mag) {
            ConvertStickToAbsCoord(dir, &ext->stick);
        }
        GetRootPosition(pos, self);
        pos[0] += dir[0] * ext->stick.mag * 32.0f;
        pos[2] += dir[2] * ext->stick.mag * 32.0f;
        if (0.001f < st.mag) {
            mode = 1;
        }
        switch (mode) {
        case 0: {
            ClipWork w;

            if ((ext->pad.trg & 0x200) != 0) {
                sceVu0CopyVector(w.pt[0], pos);
                sceVu0CopyVector(w.pt[1], pos);
                w.pt[1][1] -= 10000.0f;
                ClipFloorR(&w);
                if (w.floor.elem != 0) {
                    pos[1] = w.pt[2][1] - h;
                    break;
                }
            }
            sceVu0CopyVector(w.pt[0], pos);
            sceVu0CopyVector(w.pt[1], pos);
            w.pt[0][1] -= 10.0f;
            w.pt[1][1] += 10000.0f;
            ClipFloor(&w);
            if (w.floor.elem == 0) {
                sceVu0CopyVector(w.pt[0], pos);
                sceVu0CopyVector(w.pt[1], pos);
                w.pt[1][1] -= 10000.0f;
                ClipFloorR(&w);
                if (w.floor.elem == 0) {
                    break;
                }
            }
            pos[1] = w.pt[2][1] - h;
            break;
        }
        case 1:
            if ((ext->pad.trg & 0x200) != 0) {
                SetRootUpdateMode(self, 1);
                mode = 0;
            } else {
                pos[1] += st.dz * st.mag * 32.0f;
            }
            break;
        }
        SetDirectRootPositionNoFitting(self, pos);
        {
            ClipWork w;

            GetLowerPlaneCollision(&w, pos);
            if (w.floor.elem != 0 && CompareAttribute(w.attr, 0x800) == 0 &&
                CompareAttribute(w.attr, 0x900) == 0) {
                ClipWork w2;

                sceVu0CopyVector(w2.pt[0], pos);
                sceVu0CopyVector(w2.pt[1], pos);
                w2.pt[1][1] += 10000.0f;
                ClipFloor(&w2);
                if (w2.floor.elem != 0) {
                    sceVu0IVECTOR col = {32, 32, 255, 128};

                    w2.pt[0][1] += 200.0f;
                    gif_StartPacketPri(11);
                    MatrixDrive_PushMatrix();
                    gif_SetAlpha(1, 5, 128);
                    gif_SetZWrite(0);
                    gif_SetZTest(1);
                    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
                    DrawLineG(w2.pt[0], col, w2.pt[2], col, 0);
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
            ClipWork w3;

            sceVu0CopyVector(w3.pt[0], pos);
            sceVu0CopyVector(w3.pt[1], pos);
            w3.pt[0][1] -= 200.0f;
            w3.pt[1][1] += 200.0f;
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
                DrawLineG(w3.pt[0], col2, w3.pt[1], col2, 0);
                DrawLineG(q1, col2, q2, col2, 0);
                DrawLineG(q3, col2, q4, col2, 0);
            }
            MatrixDrive_PopMatrix();
            gif_EndPacket();
            /* a local debug switch, off: draw the five clip lines in blue */
            if (dbg) {
                ClipWork w4;
                sceVu0IVECTOR col = {0, 64, 255, 128};
                Vec4 pt[5];
                int i;

                for (i = 0; i < 5; i++) {
                    DrawLineG(w4.pt[0], col, pt[i].f, col, 0);
                }
            }
        }
    }
    {
        ClipWork w3;

        sceVu0CopyVector(w3.pt[0], pos);
        sceVu0CopyVector(w3.pt[1], pos);
        w3.pt[0][1] -= 10.0f;
        w3.pt[1][1] += 10000.0f;
        ClipFloor(&w3);
        if (w3.floor.elem != 0 && CompareAttribute(w3.attr, 0x800) == 0 &&
            CompareAttribute(w3.attr, 0x900) == 0) {
            pos[1] = w3.pt[2][1] - h;
            SetDirectRootPositionNoFitting(self, pos);
            EnableChangeRootUpdateMode(self);
            AdjustMotionHeightToNearestField(self);
        }
    }
    EnableChangeRootUpdateMode(self);
}
