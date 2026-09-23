#include "common.h"
#include "debug.h"
#include "memory.h"
#include "obj_manager.h"
#include "act-game.h"
#include "commonact.h"
#include "mail-add-data.h"
#include "motionOrientManager.h"

extern char D_002C2DC8[];
/* kept local: this TU's uses of isysGObjProcAdd do not fit the prototype in gobj_process.h */
extern int isysGObjProcAdd(void *a0, void *a1, int a2, void *a3);
/* kept local: this TU's uses of isysGObjProcAddS do not fit the prototype in gobj_process.h */
extern int isysGObjProcAddS(void *a0, void *a1, int a2, void *a3, long long a4);
/* kept local: this TU's uses of isysGObjProcRemove do not fit the prototype in gobj_process.h */
extern void isysGObjProcRemove();
extern int D_0063B208;

/* One 0x50-byte record per act status, indexed by the actor status index; the
   six 12-byte entries at +4 are indexed by the work block's mode at +0x48.
   The flags word at 0x4C is a bitfield: the ROM keeps 0x4C as the load
   displacement at every site, which only a bitfield reference produces (an
   explicit `(x >> 2) & 1` on an `unsigned int` member folds the offset onto
   the symbol instead).  src/act-game.c reads bits 13 and 14 of the same
   word. */
typedef struct {
    struct {
        int f0;
        int f4;
        int f8;
    } ent[6];

    int f48;

    unsigned int _b0 : 2;
    unsigned int b2 : 1;
    unsigned int _b3 : 7;
    unsigned int b10 : 1;
    unsigned int b11 : 1;
    unsigned int b12 : 1;
    unsigned int _b13 : 19;
} StatusAttrAct;

extern const StatusAttrAct D_005577D0[];
extern char *D_0063A61C;
/* kept local: this TU's uses of iosThreadSleep do not fit the prototype in thread.h */
extern void iosThreadSleep(void);
extern int D_0028F4C0[];
/* kept local: this TU's uses of isysGObjProcAddGOppArg do not fit the prototype in gobj_process.h */
extern int isysGObjProcAddGOppArg();
extern int matrixptr;

#include "act.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"

inline void ActSetStartBrainStatus(char *self, int status)
{
    Act *brain = GOBJ_ACT(self);
    if (brain != 0) {
        *(int *)((char *)brain + 0x448) = status;
    }
}

void actChangeActBrain(int a0, int a1, int *a2)
{
    int old = *a2;
    int n = actCreateSubThread(a1, 20);
    *a2 = n;
    if (old != 0) {
        debug_StdPrintfDummy("--b-- %p:act brain del %p\n", a0, n);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--b-- %p:act brain NULL %p\n", a0, n);
    }
}

void actChangeActMain(void *a0, void *a1, void **a2)
{
    char *e = D_002C2DC8 + *(int *)((char *)a0 + 8) * 0x4C;
    unsigned short fld = *(unsigned short *)(e + 0x40);
    void *old = *a2;
    int ret;
    if (((long long)fld << 10) == 0) {
        ret = isysGObjProcAdd(a0, a1, 0, (void *)0x13);
    } else {
        ret = isysGObjProcAddS(a0, a1, 0, (void *)0x13, (long long)fld << 10);
    }
    *a2 = (void *)ret;
    if (old != 0) {
        debug_StdPrintfDummy("--m-- %p:act main del %p\n", a0, ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--m-- %p:act main NULL %p\n", a0, ret);
    }
}

void actCreateMotionThread(void *a0, void *a1, void **a2)
{
    void *old = *a2;
    int ret = isysGObjProcAdd(D_0063A61C, a0, 0, a1);
    *a2 = (void *)ret;
    if (old != 0) {
        debug_StdPrintfDummy("--t-- %p:act mot del %p\n", *(int *)((char *)old + 4), ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--t-- %p:act mot NULL %p\n", ret, ret);
    }
}

int actCreateSubThread(void *a0, void *a1)
{
    char *e;
    unsigned short fld;
    char *p;

    if (D_0063B208) {
        Act *lval = GOBJ_ACT(D_0063A61C);
        debug_StdPrintfDummy("acst[%p]\n", D_0063A61C);
        debug_StdPrintfDummy("    [%d]\n", *(int *)(D_0063A61C + 8));
        debug_StdPrintfDummy("    [%d]\n", *(int *)(D_0063A61C + 0xC));
        if (lval != 0) {
            debug_StdPrintfDummy("lval[%p]\n", lval);
            debug_StdPrintfDummy("    [%d]\n", lval->unk34);
        }
    }
    e = D_002C2DC8 + *(int *)(D_0063A61C + 8) * 0x4C;
    fld = *(unsigned short *)(e + 0x40);
    if (((long long)fld << 10) == 0) {
        p = (char *)isysGObjProcAdd(D_0063A61C, a0, 0, a1);
    } else {
        p = (char *)isysGObjProcAddS(D_0063A61C, a0, 0, a1, (long long)fld << 10);
    }
    *(int *)(p + 0x64) = 1;
    return (int)p;
}

inline void actCreateSubThreadGOppArg(int a0, int a1)
{
    *(int *)((char *)isysGObjProcAddGOppArg(D_0063A61C, a0, 0, a1) + 0x64) = 1;
}

inline void actSetInterrupt(char *self, int val)
{
    *(int *)(self + 0x0) = val;
}

inline void ConvertStickToAbsCoord(void *a0, float *a1)
{
    Vec4 v = {{a1[3], 0.0f, -a1[4], 0.0f}};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 0x80));
    sceVu0ApplyMatrix(a0, m, &v);
}

inline void _ACTRun(int n)
{
    int i;
    int id;
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
    int count = (a0 * ((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1])) / 0x3C;
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
            int count = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] / 0x3C;
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

void after_func_exec(char *self, int oldst, int newst)
{
    Act *g = GOBJ_ACT(self);

    if (D_005577D0[oldst].ent[*(int *)((char *)g + 0x48)].f4 !=
        D_005577D0[newst].ent[*(int *)((char *)g + 0x48)].f4) {
        if (g->f_14 != 0) {
            (*(void (**)(char *))((char *)g + 0x14))(self);
            g->f_14 = 0;
        }
    }
    if (D_005577D0[oldst].b2 != D_005577D0[newst].b2) {
        if (g->f_14 != 0) {
            (*(void (**)(char *))((char *)g + 0x14))(self);
            g->f_14 = 0;
        }
    }
    if (D_005577D0[oldst].ent[*(int *)((char *)g + 0x48)].f4 == 0 &&
        D_005577D0[newst].ent[*(int *)((char *)g + 0x48)].f4 == 0 && D_005577D0[oldst].b2 == 0 &&
        D_005577D0[newst].b2 == 0) {
        if (g->f_14 != 0) {
            (*(void (**)(char *))((char *)g + 0x14))(self);
            g->f_14 = 0;
        }
    }
}

inline void actInitialize_geo(void *self) {}

/* The pad configuration template copied into the work block at +0x1E8. */
typedef struct {
    int w[60];
} PadConf;

extern PadConf iosPadConfDefault;
extern int D_0063A44C;
extern void *D_0063A620;

void actInitialize_ext_charcter(char *self)
{
    Act *g = GOBJ_ACT(self);
    char *p = (char *)iosMallocDebug(D_0063A44C, 0x400, __FILE__, 885);

    memset(p, 0, 0x400);
    *(char **)((char *)g + 0x680) = p;
    *(float *)(*(char **)(*(int *)(self + 0x164) + 0x680) + 0x58) = 1.0f;
    *(int *)(*(char **)(*(int *)(self + 0x164) + 0x680) + 0x2A0) = -1;
    *(int *)(*(char **)(*(int *)(self + 0x164) + 0x680) + 0x2A4) = -1;
    *(int *)(*(char **)(*(int *)(self + 0x164) + 0x680) + 0x2A8) = -1;
    *(int *)(*(char **)(*(int *)(self + 0x164) + 0x680) + 0x2AC) = -1;
    *(int *)(*(char **)(*(int *)(self + 0x164) + 0x680) + 0x2B0) = -1;
    InitMailAdditionalData(self, *(char **)(*(int *)(self + 0x164) + 0x680));
}

/* The actor object: only the work pointer at +0x164 matters here. */
typedef struct {
    char _0[0x164];
    int work;
} ActSelf;

typedef union {
    float f;
    int i;
} ActFWord;

/* The extended work block hung off the work block at +0x688; the three
   ten-entry histories at 0x900, 0x928 and 0x950 are read back in BeforeFunc. */
typedef struct {
    char _0[0x900];
    int a900[10];
    int a928[10];
    int a950[10];
} ActExt;

void actInitialize_only_charcter(char *self)
{
    char *g = (char *)*(int *)(self + 0x164);
    char *p = (char *)iosMallocDebug(D_0063A44C, 0x980, __FILE__, 907);
    Vec4 *q;
    int i;

    memset(p, 0, 0x980);
    *(int *)(g + 0x688) = (int)p;
    q = (Vec4 *)*(char **)(*(char **)(self + 0x164) + 0x688);
    ((Vec4 *)((char *)q + 0x320))->f[0] = GOBJ_SUB(self)->f_45C;
    ((Vec4 *)((char *)q + 0x320))->f[1] = GOBJ_SUB(self)->f_464;
    ((Vec4 *)((char *)q + 0x320))->f[2] = GOBJ_SUB(self)->f_468;
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

char *actInitialize(char *self)
{
    char *w = (char *)iosMallocDebug(D_0063A44C, 0x850, __FILE__, 934);

    *(char **)(self + 0x164) = w;
    memset(w, 0, 0x850);

    *(void **)(w + 0x4) = D_0063A620;
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
        /* The chase is read as `int`: the ROM issues it right after the last
           of the preceding int stores, which only an int-typed load (and its
           flow dependence on them) produces. ee-gcc then reverses the
           adjacent pair of independent stores below, so the emitted order is
           the byte store first with the word store in the alignment test's
           delay slot. */
        char *p = (char *)*(int *)(self + 0x164);
        *(int *)(p + 0x1B0) = 0;
        *(char *)(p + 0x1DA) = 0;
    }
    *(PadConf *)(w + 0x1E8) = iosPadConfDefault;

    memset(w + 0x170, 0, 0x20);
    memset(w + 0x134, 0, 0x8);
    memset(w + 0x190, 0, 0x20);
    memset(w + 0x47C, 0, 0x10);
    memset(w + 0x48C, 0, 0x10);
    memset(w + 0x49C, 0, 0x10);
    memset(w + 0x4B0, 0x0, 0x1D0);
    memset(w + 0x2D8, 0, 0x60);
    memset(w + 0x338, 0, 0x18);

    return w;
}

inline int ACTReserveTarget(char *self, void *a1, int a2)
{
    Act *g = GOBJ_ACT(self);
    if (*(int *)((char *)g + 0x13C) == 0) {
        *(char **)((char *)g + 0x13C) = self;
        *(int *)((char *)g + 0x140) = a2;
        iosOmSendMail(self, a2, a1);
        return 1;
    }
    return 0;
}

/* The interrupt list lives at self+0x54: a count at +4 and 8-byte entries
   from +8. */
typedef struct {
    int id;
    void *f4;
} IntrEnt;

typedef struct {
    int f0;
    int n;
    IntrEnt ent[1];
} IntrList;

/* One 0x18-byte entry of the actor's mail list. */
typedef struct {
    void *f0;                                       /* 0x00 */
    void *f4;                                       /* 0x04 */
    void (*handler)(char *self, int id, void *arg); /* 0x08 */
    void (*f0C)(char *self, int id, void *arg);     /* 0x0C */
    unsigned short kind;                            /* 0x10 */
    short f12;                                      /* 0x12 */
    unsigned int f14;                               /* 0x14 */
} IntrMail;

typedef struct {
    int w[8];
} IntrOrient;

IntrMail *act_check_intr_list(char *self, IntrMail *m, void **out)
{
    IntrList *k = (IntrList *)(self + 0x54);
    Act *w = GOBJ_ACT(self);
    IntrOrient buf;
    int i;

    if (m != 0) {
        while ((short)m->kind != 429) {
            if ((m->f14 >> 18) & 1) {
                for (i = 0; i < k->n; i++) {
                    int mot;
                    char *p;
                    if (*(int *)((char *)w + 0x13C) != 0 &&
                        *(int *)((char *)w + 0x140) != k->ent[i].id) {
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
                        (w->unk34 != 0 || m->f12 == 0)) {
                        continue;
                    }
                    *(int *)((char *)w + 0x3C) = mot;
                    *(void **)((char *)w + 0x2C) = k->ent[i].f4;
                    *(char **)((char *)w + 0x30) = GetMailAdditionalData(self, i);
                    *(IntrOrient *)(*(char **)(*(int *)(self + 0x164) + 0x688) + 0x8B0) = buf;
                    *out = &k->ent[i];
                    return m;
                }
            }
            m++;
        }
    }
    return 0;
}

void act_check_mail(char *self, IntrMail *m)
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
            ((ActStatusWord *)((char *)w + 0x20))->q |= 0x100;
            break;
        case 0x1F:
            ((ActStatusWord *)((char *)w + 0x20))->q |= 0x10;
            break;
        case 0x20:
            ((ActStatusWord *)((char *)w + 0x20))->q |= 0x20;
            break;
        case 0x3D:
            ((ActStatusWord *)((char *)w + 0x18))->q |= 0x8000LL << 47;
            break;
        case 0x1A9:
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x2B0) = 0;
            break;
        case 0xF:
            ((ActStatusWord *)((char *)w + 0x20))->q |= 1;
            break;
        case 0x10:
            ((ActStatusWord *)((char *)w + 0x18))->q |= 0x8000LL << 48;
            break;
        case 0x7:
            ((ActStatusWord *)((char *)w + 0x20))->q |= 0x400000;
            break;
        case 0x22:
            ((ActStatusWord *)((char *)w + 0x20))->q |= 0x40;
            break;
        }
    }
    while ((short)m->kind != 429) {
        if ((m->f14 >> 18) & 1) {
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

typedef union {
    float f;
    int i;
} ActFloat;

/* Motion record table, 0x194 bytes per entry (only the flags word is used
   here); src/act-game.c carries the full layout as MotionRec. */
typedef struct {
    char _0[0x18C];
    unsigned int f18C;
    unsigned int f190;
} ActMotionRec;

extern ActMotionRec D_0055FE58[];
extern IntrMail D_002A7E08[];
/* the boy object, typed as the work block object pointers it is compared and
   exchanged with (ActObjRefs below; void * as in boyact.c and chain.c) */
extern void *D_00639EA4;
extern int D_0063A800;

/* one flag per mail list: a list whose flag is set is not checked for an
   interrupt while the status record's b11 is set */
typedef struct {
    unsigned int w[4];
} IntrSkip;

/* The work block's object pointers: +0x2C takes a mail entry's object
   (act_check_mail), +0x80 and +0x84 are the targets src/act-game.c reads
   beside D_00639EA4.  Reconstruction, rung: ROM bytes (BeforeFunc's clears
   are record-field stores in the load's alias set: the sw 0x2C and sw 0x80
   follow the D_00639EA4 load at sched2). */
typedef struct {
    char _0[0x2C];
    void *f_2C;
    char _30[0x50];
    void *f_80;
    void *f_84;
} ActObjRefs;

void BeforeFunc(char *self)
{
    char *w = (char *)((ActSelf *)self)->work;
    char *mb = self + 0x54;
    IntrMail *intr;
    char *g;
    void *act;
    IntrEnt *ent;
    int i;
    int old;

    ((ActObjRefs *)w)->f_2C = 0;
    *(char **)(w + 0x30) = 0;
    *(int *)(w + 0x4C) += 1;
    *(int *)(w + 0x10) += 1;
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 52);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 62);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 63);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 0);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 1);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 2);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 3);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 4);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 5);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 8);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 10);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 18);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 22);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 37);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 44);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 45);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 12);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 31);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 36);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 37);
    ((ActStatusWord *)(w + 0x18))->q &= ~(1LL << 38);
    ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 35);
    ((ActObjRefs *)w)->f_80 = 0;
    ((ActObjRefs *)w)->f_84 = 0;
    if (self == D_00639EA4) {
        char *p = *(char **)(*(char **)(self + 0x164) + 0x688);

        ((ActFloat *)(*(char **)(self + 0x15C) + 0x45C))->f = *(float *)(p + 0x320);
        ((ActFloat *)(*(char **)(self + 0x15C) + 0x464))->f = *(float *)(p + 0x324);
        ((ActFloat *)(*(char **)(self + 0x15C) + 0x468))->f = *(float *)(p + 0x328);
    }
    if (*(int *)(w + 0x50) != 0) {
        *(int *)(w + 0x50) -= 1;
    }
    {
        IntrMail *mails[5] = {&D_002A7E08[0], &D_002A7E08[3], *(IntrMail **)(w + 0xD4),
                              *(IntrMail **)(w + 0xD0), (IntrMail *)0xFFFFFFFF};
        IntrSkip skip = {{0, 1, 0, 1}};

        ACTSendMailCorrect(self, D_005577D0[*(int *)(w + 0x34)].f48);
        for (i = 0; i < *(int *)(mb + 4); i++) {
            ((IntrList *)mb)->ent[i].id =
                _ACTCorrectMsg(self, *(int *)(mb + 8 + i * 8), *(void **)(mb + 0xC + i * 8));
        }
        ACTRunIntrCorrect(self, (struct IntrRec *)mails[1], (struct IntrRec *)mails[2]);
        for (i = 0; mails[i] != (IntrMail *)0xFFFFFFFF; i++) {
            act_check_mail(self, mails[i]);
        }
        intr = 0;
        for (i = 0; mails[i] != (IntrMail *)0xFFFFFFFF; i++) {
            if (skip.w[i] == 0 || D_005577D0[*(int *)(w + 0x34)].b11 == 0) {
                intr = act_check_intr_list(self, mails[i], (void **)&ent);
                if (intr != 0) {
                    break;
                }
            }
        }
    }
    g = *(char **)(self + 0x15C);
    *(char **)(w + 0x40) = *(char **)(g + 0x540);
    if ((((&D_0055FE58[*(int *)(*(char **)(self + 0x15C) + 0x4A0)])->f18C >> 1) & 1) != 0 &&
        *(float *)(*(char **)(self + 0x15C) + 0x4AC) < 3.0f) {
        ((ActStatusWord *)(w + 0x20))->q |= 1LL << 18;
    }
    if (intr != 0) {
        old = *(int *)(w + 0xD8);
        *(int *)(w + 0xD8) = (short)intr->kind;
        act = (void *)D_005577D0[intr->f12].ent[*(int *)(w + 0x48)].f0;
        if (act != 0) {
            after_func_exec(self, *(int *)(w + 0x34), intr->f12);
            if (*(int *)(w + 0x18) != 0) {
                (*(void (**)(char *))(w + 0x18))(self);
                *(int *)(w + 0x18) = 0;
            }
            *(int *)(w + 0x4C) = 0;
            for (i = 9; i > 0; i--) {
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a900[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a900[i - 1];
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a928[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a928[i - 1];
                ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a950[i] =
                    ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a950[i - 1];
            }
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a900[0] = *(int *)(w + 0x34);
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a928[0] = *(int *)(w + 0x10);
            ((ActExt *)*(int *)(((ActSelf *)self)->work + 0x688))->a950[0] = old;
            *(int *)(w + 0x34) = intr->f12;
            ((ActStatusWord *)(w + 0x18))->q =
                (((ActStatusWord *)(w + 0x18))->q & ~(1LL << 39)) |
                ((unsigned long long)D_005577D0[*(int *)(w + 0x34)].b10 << 39);
            ((ActStatusWord *)(w + 0x18))->q =
                (((ActStatusWord *)(w + 0x18))->q & ~(1LL << 50)) |
                ((unsigned long long)D_005577D0[intr->f12].b12 << 50);
            ((ActStatusWord *)(w + 0x20))->q &= ~(1LL << 11);
            *(IntrMail **)(w + 0xD4) = &D_002A7E08[D_005577D0[*(int *)(w + 0x34)].ent[5].f8];
            actChangeActMain(D_0063A61C, act, (void **)(w + 4));
        }
        if (intr->f0 != 0) {
            *(int *)(w + 0x38) = 0;
            actCreateMotionThread(intr->f0, (void *)21, (void **)(w + 8));
        }
        if (intr->f4 != 0) {
            actCreateMotionThread(intr->f4, (void *)22, (void **)(w + 0xC));
        }
        if (intr->f0C != 0) {
            intr->f0C(self, ent->id, ent->f4);
        }
        ACTAcceptMail(self, (short)intr->kind);
    }
    ((ActStatusWord *)(w + 0x138))->q &= ~(1LL << 0);
    *(int *)(w + 0x13C) = 0;
    *(int *)(mb + 4) = 0;
    ClearMailAdditionalData(self);
    ACTGame_BeforeFunc(self);
    D_0063A800 = 100;
}

/* The floor/wall collision work block: the 0xC0-byte record src/act-env.c
   and src/girl_act.c carry, with the attribute word at +0x98 that the ROM
   hands to CompareAttribute. */
typedef struct {
    float a[4];   /* 0x00 start point   */
    float b[4];   /* 0x10 end point     */
    float pos[4]; /* 0x20 clipped point */
    char _30[0x40];
    float f_70;
    char _74[0x14];
    int f_88;
    char _8c[0x08];
    int f_94;
    int f_98;
    char _9c[0x24];
} ActClipWork;

/* The stick reading iosPadGetStick fills in: the 0x20-byte record
   omori/src/camera-ico2.c carries, read here through its two direction
   words and its magnitude. */
typedef struct {
    int x; /* 0x00 */
    int y; /* 0x04 */
    char _08[0x04];
    float dx;  /* 0x0C */
    float dz;  /* 0x10 */
    float mag; /* 0x14 */
    char _18[0x08];
} ActPadStick;

extern char *D_00639EC0;
extern void sceVu0CopyVector(void *dst, void *src);
extern void sceVu0UnitMatrix(void *m);
extern void GetRootPosition(void *out, char *self);
extern void SetDirectRootPositionNoFitting(char *self, void *v);
extern void GetLowerPlaneCollision(void *work, void *pos);
extern void ClipFloor(void *work);
extern void ClipFloorR(void *work);
extern int CompareAttribute(unsigned int a, unsigned int b);
extern void SetSimplePlane(float *plane, float a, float b, float c, float d);
extern void CopyVector(void *dst, void *src);
extern void DrawLineG(void *a, void *ca, void *b, void *cb, int flag);
/* kept local: this TU passes the packet priority that the prototype in
   seki/include/GifPacket.h leaves out */
extern void gif_StartPacketPri(int pri);
extern void gif_SetAlpha(long long a0, long long a1, long long a2);
extern void gif_SetZWrite(int on);
extern void gif_SetZTest(int on);
extern void gif_EndPacket(void);
extern void MatrixDrive_PushMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void iosPadRead(void *pad);
extern int iosPadGetStick(void *dev, void *out, int mode, int a3, int a4, int a5);
extern void DisableChangeRootUpdateMode(char *self);
extern void EnableChangeRootUpdateMode(char *self);
extern void SetRootUpdateMode(char *self, int val);
extern int AdjustMotionHeightToNearestField(char *self);

void ACTDebugMove(int a0, int a1)
{
    char *self = (char *)a0;
    float dir[4];
    float pos[4];
    ActPadStick st;
    char *ext;
    char *p;
    float h;
    int mode = 1;
    int dbg = 0; /* local debug switch, see the test at the end of the loop */

    ext = *(char **)(self + 0x164);
    p = *(char **)(*(char **)(self + 0x15C) + 0x8C);
    h = (p != 0) ? *(float *)(p + 0x14) : 0.0f;
    DisableChangeRootUpdateMode(self);
    SetRootUpdateMode(self, 0);
    while (((*(int *)(ext + 0x2E0) & 1) != 0 || mode == 1) && self == D_00639EC0) {
        _ACTWait(1);
        iosPadRead(ext + 0x2D8);
        iosPadGetStick(ext + 0x2D8, ext + 0x338, 0, 2, 2, 0);
        iosPadGetStick(ext + 0x2D8, &st, 1, 2, 2, 0);
        if (0.001f < *(float *)(ext + 0x34C)) {
            ConvertStickToAbsCoord(dir, (float *)(ext + 0x338));
        }
        GetRootPosition(pos, self);
        pos[0] += dir[0] * *(float *)(ext + 0x34C) * 32.0f;
        pos[2] += dir[2] * *(float *)(ext + 0x34C) * 32.0f;
        if (0.001f < st.mag) {
            mode = 1;
        }
        switch (mode) {
        case 0: {
            ActClipWork w;

            if ((*(int *)(ext + 0x2E4) & 0x200) != 0) {
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
            if ((*(int *)(ext + 0x2E4) & 0x200) != 0) {
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
                SetSimplePlane((float *)(*(char **)(self + 0x15C) + 0x1D0), 0.0f, -1.0f, 0.0f,
                               pos[1] + h);
                CopyVector(*(char **)(self + 0x15C) + 0x250, pos);
                *(float *)(*(char **)(self + 0x15C) + 0x254) += h;
            }
        }
        debug_PrintfDummy(10, 185, 0xFFFFFF00u, (int)"LW's coord:");
        debug_PrintfDummy(20, 195, 0xFFFFFF00u, (int)"POS X:%8.2f Y:%8.2f Z:%8.2f", -pos[0],
                          -pos[1], -pos[2]);
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
            /* Local debug switch, off. What the bytes pin: ACTDebugMove reached
               gcse with 448..451, 456..459 or 464..479 real insns (476 with
               this arm, 455 without it): the expression table size orders
               PRE's reaching registers, whose order is the order of the seven
               spill slots at 0x334..0x34C. Also pinned: a loop inside this
               window (the loop test's label is aligned), the arm's block
               locals (0x120 bytes of the frame) and an expanded colour
               initializer {0, 64, 255, 128} the ROM keeps unreferenced at
               0x621D30. cse cannot carry dbg's 0 across the loop label, gcse's
               constant propagation folds the test and the next jump pass
               deletes the arm; the listing leaves rows 1599 to 1692 code-free.
               What the bytes cannot pin: the arm's text. */
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
