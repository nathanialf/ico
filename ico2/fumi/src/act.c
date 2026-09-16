#include "common.h"

typedef union {
    float f[4];
    long long ll[2];
} Vec4;

extern char D_00621BB0[];
extern char D_00621BD0[];
extern char D_002C2DC8[];
extern char D_00621BF0[];
extern char D_00621C10[];
extern void debug_StdPrintfDummy();
extern int isysGObjProcAdd(void *a0, void *a1, int a2, void *a3);
extern int isysGObjProcAddS(void *a0, void *a1, int a2, void *a3, long long a4);
extern void isysGObjProcRemove();
extern char D_00621C30[];
extern char D_00621C50[];
extern char D_00621C70[];
extern char D_00621C80[];
extern char D_00621C90[];
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
} StatusAttr;

extern StatusAttr D_005577D0[];
extern char *D_0063A61C;
extern void iosOmSendMail(void *a0, int a1, void *a2);
extern void iosThreadSleep(void);
extern int D_0028F4C0[];
extern int isysGObjProcAddGOppArg();
extern int matrixptr;
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0TransposeMatrix(void *a0, void *a1);
/* prototypes: their order is the inline tail's emission order */
void actInitialize_geo(void);
int ACTReserveTarget(char *self, void *a1, int a2);
void _ACTRun(int n);
void _ACTWait(int a0);
void actCreateSubThreadGOppArg(int a0, int a1);
void actSetInterrupt(char *self, int val);
void ConvertStickToAbsCoord(void *a0, float *a1);
void ActSetStartBrainStatus(char *self, int status);
void actWaitCondition(int a0, int a1);

inline void ActSetStartBrainStatus(char *self, int status)
{
    char *brain = *(char **)(self + 0x164);
    if (brain != 0) {
        *(int *)(brain + 0x448) = status;
    }
}

void actChangeActBrain(int a0, int a1, int *a2)
{
    int old = *a2;
    int n = actCreateSubThread(a1, 0x14);
    *a2 = n;
    if (old != 0) {
        debug_StdPrintfDummy(D_00621BB0, a0, n);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy(D_00621BD0, a0, n);
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
        debug_StdPrintfDummy(D_00621BF0, a0, ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy(D_00621C10, a0, ret);
    }
}

void actCreateMotionThread(void *a0, void *a1, void **a2)
{
    void *old = *a2;
    int ret = isysGObjProcAdd(D_0063A61C, a0, 0, a1);
    *a2 = (void *)ret;
    if (old != 0) {
        debug_StdPrintfDummy(D_00621C30, *(int *)((char *)old + 4), ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy(D_00621C50, ret, ret);
    }
}

int actCreateSubThread(void *a0, void *a1)
{
    char *e;
    unsigned short fld;
    char *p;

    if (D_0063B208) {
        char *lval = *(char **)(D_0063A61C + 0x164);
        debug_StdPrintfDummy(D_00621C70, D_0063A61C);
        debug_StdPrintfDummy(D_00621C80, *(int *)(D_0063A61C + 8));
        debug_StdPrintfDummy(D_00621C80, *(int *)(D_0063A61C + 0xC));
        if (lval != 0) {
            debug_StdPrintfDummy(D_00621C90, lval);
            debug_StdPrintfDummy(D_00621C80, *(int *)(lval + 0x34));
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
    if (n > 0) {
        i = n;
        do {
            iosThreadSleep();
            i--;
        } while (i != 0);
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
    if (count == 0) {
        for (;;) {
            iosThreadSleep();
        }
    }
    if (count > 0) {
        int i = count;
        do {
            iosThreadSleep();
            i--;
        } while (i != 0);
    }
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
    char *g = *(char **)(self + 0x164);

    if (D_005577D0[oldst].ent[*(int *)(g + 0x48)].f4 !=
        D_005577D0[newst].ent[*(int *)(g + 0x48)].f4) {
        if (*(int *)(g + 0x14) != 0) {
            (*(void (**)(char *))(g + 0x14))(self);
            *(int *)(g + 0x14) = 0;
        }
    }
    if (D_005577D0[oldst].b2 != D_005577D0[newst].b2) {
        if (*(int *)(g + 0x14) != 0) {
            (*(void (**)(char *))(g + 0x14))(self);
            *(int *)(g + 0x14) = 0;
        }
    }
    if (D_005577D0[oldst].ent[*(int *)(g + 0x48)].f4 == 0 &&
        D_005577D0[newst].ent[*(int *)(g + 0x48)].f4 == 0 && D_005577D0[oldst].b2 == 0 &&
        D_005577D0[newst].b2 == 0) {
        if (*(int *)(g + 0x14) != 0) {
            (*(void (**)(char *))(g + 0x14))(self);
            *(int *)(g + 0x14) = 0;
        }
    }
}

inline void actInitialize_geo(void) {}

typedef union {
    unsigned long long q;
    unsigned int w[2];
} ActStatusWord;

/* The pad configuration template copied into the work block at +0x1E8. */
typedef struct {
    int w[60];
} PadConf;

extern PadConf iosPadConfDefault;
extern char D_00621CA0[];
extern int D_0063A44C;
extern void *D_0063A620;
extern void *iosMallocDebug(int heap, int size, char *file, int line);
extern void *memset(void *p, int c, int n);
extern void InitMailAdditionalData(char *self, void *p);

void actInitialize_ext_charcter(char *self)
{
    char *g = *(char **)(self + 0x164);
    char *p = (char *)iosMallocDebug(D_0063A44C, 0x400, D_00621CA0, 0x375);

    memset(p, 0, 0x400);
    *(char **)(g + 0x680) = p;
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
    char *p = (char *)iosMallocDebug(D_0063A44C, 0x980, D_00621CA0, 0x38B);
    Vec4 *q;
    int i;

    memset(p, 0, 0x980);
    *(int *)(g + 0x688) = (int)p;
    q = (Vec4 *)*(char **)(*(char **)(self + 0x164) + 0x688);
    ((Vec4 *)((char *)q + 0x320))->f[0] = *(float *)(*(int *)(self + 0x15C) + 0x45C);
    ((Vec4 *)((char *)q + 0x320))->f[1] = *(float *)(*(int *)(self + 0x15C) + 0x464);
    ((Vec4 *)((char *)q + 0x320))->f[2] = *(float *)(*(int *)(self + 0x15C) + 0x468);
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
    char *w = (char *)iosMallocDebug(D_0063A44C, 0x850, D_00621CA0, 934);

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
    char *g = *(char **)(self + 0x164);
    if (*(int *)(g + 0x13C) == 0) {
        *(char **)(g + 0x13C) = self;
        *(int *)(g + 0x140) = a2;
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

extern char D_00621CB0[];

typedef struct {
    int w[8];
} IntrOrient;

extern int ACTGetOrientFromIntrK(char *self, int kind, void *buf, int i);
extern char *SetMotionRequest(char *self, int mot, void *buf);
extern char *GetMailAdditionalData(char *self, int mail);

IntrMail *act_check_intr_list(char *self, IntrMail *m, void **out)
{
    IntrList *k = (IntrList *)(self + 0x54);
    char *w = *(char **)(self + 0x164);
    IntrOrient buf;
    int i;

    if (m != 0) {
        while ((short)m->kind != 429) {
            if ((m->f14 >> 18) & 1) {
                for (i = 0; i < k->n; i++) {
                    int mot;
                    char *p;
                    if (*(int *)(w + 0x13C) != 0 && *(int *)(w + 0x140) != k->ent[i].id) {
                        continue;
                    }
                    if (k->ent[i].id != (short)m->kind) {
                        continue;
                    }
                    mot = ACTGetOrientFromIntrK(self, k->ent[i].id, &buf, i);
                    p = SetMotionRequest(self, mot, &buf);
                    *(char **)(w + 0x130) = p;
                    if (*(int *)(p + 0xC) == 0 &&
                        (*(unsigned short *)((char *)m + 0x16) & 1) == 0 &&
                        (*(int *)(w + 0x34) != 0 || m->f12 == 0)) {
                        continue;
                    }
                    *(int *)(w + 0x3C) = mot;
                    *(void **)(w + 0x2C) = k->ent[i].f4;
                    *(char **)(w + 0x30) = GetMailAdditionalData(self, i);
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
    char *w = *(char **)(self + 0x164);
    int i;
    int id;

    if (m == 0) {
        debug_StdPrintfDummy(D_00621CB0);
        return;
    }
    for (i = 0; i < k->n; i++) {
        id = k->ent[i].id;
        switch (id) {
        case 0x10D:
            ((ActStatusWord *)(w + 0x20))->q |= 0x100;
            break;
        case 0x1F:
            ((ActStatusWord *)(w + 0x20))->q |= 0x10;
            break;
        case 0x20:
            ((ActStatusWord *)(w + 0x20))->q |= 0x20;
            break;
        case 0x3D:
            ((ActStatusWord *)(w + 0x18))->q |= 0x8000LL << 47;
            break;
        case 0x1A9:
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x2B0) = 0;
            break;
        case 0xF:
            ((ActStatusWord *)(w + 0x20))->q |= 1;
            break;
        case 0x10:
            ((ActStatusWord *)(w + 0x18))->q |= 0x8000LL << 48;
            break;
        case 0x7:
            ((ActStatusWord *)(w + 0x20))->q |= 0x400000;
            break;
        case 0x22:
            ((ActStatusWord *)(w + 0x20))->q |= 0x40;
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
extern char *D_00639EA4;
extern char D_00621CC8[];
extern int D_0063A800;
extern void ACTSendMailCorrect(char *self, int a1);
extern int _ACTCorrectMsg(char *self, int msg, void *arg);
extern void ACTRunIntrCorrect(char *self, void *a1, void *a2);
extern void ACTAcceptMail(char *self, int kind);
extern void ClearMailAdditionalData(char *self);
extern void ACTGame_BeforeFunc(char *self);

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/act", BeforeFunc);
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/act", ACTDebugMove);
