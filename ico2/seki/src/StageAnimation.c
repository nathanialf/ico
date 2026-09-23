#include "common.h"
#include "DObj.h"
#include "debug.h"
#include "debug_exception.h"
#include "memory.h"
#include "gobj.h"
#include "gobj_dl.h"
#include "gobj_process.h"
#include "Basic.h"
#include "Light.h"
#include "Matrix.h"
#include "RegistPacket.h"
#include "quaternion.h"

typedef union {
    int i;
    float f;
} AnimWord;

typedef union {
    long l;
    short h;
} PlayWord;

typedef struct {
    char _b[8];
} Blob8;

struct B8 {
    char _b[8];
};

typedef struct AnimNode {
    long field0; /* 0x00 */
    char _pad[0x14 - 0x8];
    struct AnimNode *next; /* 0x14 */
} AnimNode;

/* RECONSTRUCTION: the 0x290-byte animation record D_0067D098 holds, laid out
   from the offsets this TU reads (kind, object and data tables, the three
   entry pointers, the packed count/mode word). stage_SetScale and
   stage_SetAnimation read the object table as a member of this record:
   expand_expr forces the member's address `e + 0x80` into its own register
   before the index is added, which is the ROM's addiu/addu pair (and in
   stage_SetScale the k-loop test's own copy of it). */
typedef struct {
    short kind[64]; /* 0x000 */
    char *obj[64];  /* 0x080 */
    int *data[64];  /* 0x180 */
    int *entry1;    /* 0x280 */
    int *entry2;    /* 0x284 */
    int *entry3;    /* 0x288 */
    AnimWord flags; /* 0x28C */
} StageAnim;

/* RECONSTRUCTION: the play node stage_MakePlayBgAnimation links into
   D_0063C15C and stage_DispBgAnimation walks. The ROM reads its first word as
   int bit-fields in a doubleword unit (ld, then andi 0xFFFF/sll 18/sra 18 for
   the 14-bit animation number, andi 0x8000 for the kill flag, and 0xFFFFBFFF
   for the play flag), which is what gcc 2.9 emits for int bit-fields in a
   16-byte aligned record; the names are this repository's. */
typedef struct {
    int no : 14; /* 0x00 */
    int play : 1;
    int kill : 1;
    short num;   /* 0x02 */
    float frame; /* 0x04 */
    float speed; /* 0x08 */
    float scale; /* 0x0C */
    void *next;  /* 0x10 */
    void *prev;  /* 0x14 */
    int _18[2];
    float pos[4] __attribute__((aligned(16))); /* 0x20 */
    float rot[4];                              /* 0x30 */
} BgaPlayNode;

extern int D_0028F4D4[];
/* kept local: this TU's uses of bga_ResetAnimation do not fit the prototype in BgAnimation.h */
extern void bga_ResetAnimation();
extern int *D_0063C15C;
/* kept local: this TU's uses of bga_SetCameraForceOff do not fit the prototype in BgAnimation.h */
extern void bga_SetCameraForceOff();
extern int D_0063C158;
extern StageAnim D_0067D098[];
extern char D_005501A8[];
extern char D_005501E0[];
extern char D_00550028[];
extern char D_0063A1A8[];
extern void __assert(char *file, int line, char *expr);
/* kept local: this TU's uses of bga_CheckAnimationFinish do not fit the prototype in BgAnimation.h */
extern int bga_CheckAnimationFinish(int a0);
/* kept local: this TU's uses of bga_CheckSdfCameraFinish do not fit the prototype in BgAnimation.h */
extern int bga_CheckSdfCameraFinish(int a0);
/* kept local: this TU's uses of bga_CheckAnimationFrame do not fit the prototype in BgAnimation.h */
extern int bga_CheckAnimationFrame(int a0, int a1, int a2);
/* kept local: this TU's uses of bga_CheckSdfCameraFrame do not fit the prototype in BgAnimation.h */
extern int bga_CheckSdfCameraFrame(int a0, int a1, int a2);
extern char D_00550210[];
extern int D_0063B13C;
extern int ScreenHeight;
/* kept local: this TU's uses of bga_CalcSdfCamera do not fit the prototype in BgAnimation.h */
extern void bga_CalcSdfCamera(char *p, int a1);
extern char D_005F5E70[];
extern char D_002C2DC8[];
extern char D_002BC6E0[];
extern char D_00602FA0[];
extern char D_0063A1B0[];
extern char D_0063A1B8[];
extern char D_00550068[];
extern int stage_no;
extern int strcmp(const char *a, const char *b);
extern int strncmp(const char *a, const char *b, int n);
/* kept local: this TU's uses of bga_InitData do not fit the prototype in BgAnimation.h */
extern int bga_InitData(char *data);
/* kept local: this TU's uses of bga_SetFrame do not fit the prototype in BgAnimation.h */
extern void bga_SetFrame();
/* kept local: this TU's uses of bga_SetCamFrame do not fit the prototype in BgAnimation.h */
extern void bga_SetCamFrame();
extern int graphics_ready;
extern int D_0028F4C0[];
/* kept local: this TU's uses of bga_SetUniqAnimationFlag do not fit the prototype in BgAnimation.h */
extern void bga_SetUniqAnimationFlag(int val);
/* kept local: this TU's uses of bga_CalcAnimation do not fit the prototype in BgAnimation.h */
extern void bga_CalcAnimation(void *a0, int a1, int a2);
extern char D_00550230[];
extern char D_00550278[];
extern IosMemPart *D_0063A44C;
/* kept local: this TU's uses of bga_DispLightning do not fit the prototype in BgAnimation.h */
extern void bga_DispLightning(void);
/* kept local: this TU's uses of bga_CheckAnimationFrameIn do not fit the prototype in BgAnimation.h */
extern int bga_CheckAnimationFrameIn(int a0, int a1, int a2);
/* kept local: this TU's uses of bga_CheckSdfCameraFrameIn do not fit the prototype in BgAnimation.h */
extern int bga_CheckSdfCameraFrameIn(int a0, int a1, int a2);

typedef struct {
    long long w[8];
} StageGObjInit;

extern StageGObjInit D_0054FFA0;
extern char D_0054FFE0[];
extern char D_00550000[];
extern char D_00550040[];

#include "StageAnimation.h"
#include <stdio.h>

void stage_MakeGObj(int *dat, int no)
{
    StageGObjInit init = D_0054FFA0;
    int i;
    char *g;
    char *d;
    int w;
    int kind = dat[0];
    int aux = dat[1];
    char *e = (char *)D_0067D098 + no * 0x290;

    for (i = 0; i < ((*(int *)(e + 0x28C) << 22) >> 22); i++) {
        if (((short *)e)[i] == kind) {
            debug_StdPrintfDummy(D_0054FFE0, kind, kind, no);
            return;
        }
    }
    g = (char *)isysGObjAdd(0, 0, 0);
    if (g == 0) {
        debug_StdPrintfDummy(D_00550000, no);
        debug_assert(D_00550028, 0x21D);
        __assert(D_00550028, 0x21D, D_0063A1A8);
    }
    *(short *)(e + (((*(int *)(e + 0x28C) << 22) >> 22) << 1)) = kind;
    *(int *)(g + 0x4) = 1;
    *(int *)(g + 0x8) = 0;
    isysGObjKindTableAdd(g, aux);
    isysGObjProcAdd(g, 0, 1, 0x16);
    isysGObjProcAdd(g, 0, 1, 0x17);
    isysGObjProcAdd(g, 0, 1, 0x18);
    isysGObjLinkObjDL(g, 0, 0, 7, 0xFFFFFFFF);
    *(int *)(g + 0x24) = 0;
    *(char **)(e + (((*(int *)(e + 0x28C) << 22) >> 22) << 2) + 0x80) = g;
    d = CSVSYSTEM_InitDObj(kind, &init);
    *(int *)(g + 0x15C) = (int)d;
    *(int *)(d + 0x80) = 1;
    *(int *)(e + (((*(int *)(e + 0x28C) << 22) >> 22) << 2) + 0x180) = (int)dat;
    w = (*(int *)(e + 0x28C) & ~0x3FF) | ((((*(int *)(e + 0x28C) << 22) >> 22) + 1) & 0x3FF);
    *(int *)(e + 0x28C) = w;
    if (((w << 22) >> 22) >= 64) {
        debug_Assert(D_00550040);
        debug_assert(D_00550028, 0x232);
        __assert(D_00550028, 0x232, D_0063A1A8);
    }
}

void stage_ApplyData(char *name, char *data)
{
    char *tbl[2] = {D_005F5E70 + stage_no * 0x194, D_005F5E70 + 8 + stage_no * 0x194};
    char buf[0x400];
    int m;
    int i;
    int j;
    int n;
    int id;
    char *rec;
    char *ent;
    char *obj;

    for (m = 0; m < 2; m++) {
        for (i = ((int *)tbl[m])[0]; i < ((int *)tbl[m])[1]; i++) {
            rec = D_002C2DC8 + i * 0x4C;
            n = *(int *)(rec + 0x34);
            if (n != 0) {
                ent = D_002BC6E0 + n * 0x14;
                for (j = 0; j < 2; j++) {
                    id = ((int *)ent)[j];
                    obj = D_00602FA0 + id * 0x5C;
                    if (id != 0x3CC) {
                        if (strcmp(name, obj) == 0) {
                            if (strncmp(data, D_0063A1B0, 3) == 0) {
                                *(int *)(obj + 0x54) = bga_InitData(data);
                            } else {
                                *(int *)(obj + 0x54) = (int)data;
                            }
                            return;
                        }
                    }
                }
            }
        }
    }
    sprintf(buf, D_00550068, name);
    debug_assertMessage(D_00550028, 0x269, buf);
    __assert(D_00550028, 0x269, D_0063A1B8);
}

typedef struct {
    short kinds[64]; /* 0x000 */
    char *objs[64];  /* 0x080 */
    int *dats[64];   /* 0x180 */
    char *p280;      /* 0x280 */
    char *p284;      /* 0x284 */
    char *p288;      /* 0x288 */
    AnimWord flags;  /* 0x28C: count 0 to 9, node count 10 to 19, play 20 to 29, mode 30 to 31 */
} StageEnt;

#define STG ((StageEnt *)D_0067D098)

typedef struct {
    int kind; /* 0x00 */
    int aux;  /* 0x04 */
} StgObjDat;

typedef struct {
    int id[2]; /* 0x00 */
    int _8[3];
} StgBgaSet;

extern const StageGObjInit D_00550150;
extern StgObjDat D_00600498[];
extern char D_002C1270[];
extern char D_00550098[];
extern char D_005500C8[];
extern char D_005500F8[];
extern char D_00550128[];
extern void bga_InitBGA(void);
extern void bga_ResetCamera(void);
extern void bga_ApplyDObject(char *a0, char **a1, int a2, int a3);

#define STG_DAT(o) ((char *)((AnimWord *)((char *)(o) + 0x15C))->i)
#define STG_NODE(o, t) ((char *)((AnimWord *)(STG_DAT(o) + 0x870))->i + (t) * 0x50)

/* Compiled-out debug hook (our name), the construct main.c's mainDebugBar,
   icoMisc.c's partitionBarDebugDisp and weapon.c's dynGeoDebugHook carry: it
   inlines to nothing and emits no byte, but each call leaves one
   (use (const_int 0)) insn that loop.c counts and flow never deletes.
   WHAT THE BYTES PIN: the ROM keeps the m loop's `li 80` and the
   `li -1` of the entry2 store inside the second loop, and loop.c's
   move_movables (threshold 64 with a call in the loop) hoists both into
   two more callee-saved registers (frame 0xC0 against the ROM's 0xA0)
   unless that loop counts at least 65 real insns at both loop passes. Its
   statements give 63 and 62, so three or more insns that emit no byte sat
   in the loop after the m loop: three or four hooks are byte-identical, two
   let the second pass hoist the stride, and one between d and the m loop
   changes five words. The January listing has the gp display counter
   (lw, lw, addu, sw) at line 1453 and no code at 1452, 1454 and 1455, and the
   retail .sbss has no counter word. WHAT THEY CANNOT PIN: that the
   developer's code was this construct, its lines, or the count beyond three.
   The same hook at stage_PlayBgAnimation's counter (listing line 1380)
   changes six words there, so these are not that counter's remnant.
   stage_Init's uses carry their own pinned/not-pinned comments; the
   definition sits above stage_Init because gcc 2.9 inlines only a body it
   has already read. */
static __inline__ void stageAnimDebugHook(void) {}

int stage_Init(void)
{
    StgObjDat *p = 0;
    char *tbl[2] = {D_005F5E70 + stage_no * 0x194, D_005F5E70 + 8 + stage_no * 0x194};
    StageGObjInit arg;
    int max = 0;
    int m;
    int i;
    int k;
    int t;
    int u;
    int n;
    int id;
    int no;
    StgObjDat *q;
    char *rec;
    char *tbl2;
    char *obj;
    char *g;
    char *a;
    char *r;
    int (*fn)(char *, StageGObjInit *);
    StageEnt *e;

    bga_InitBGA();
    for (i = 0; i < 87; i++) {
        for (k = 0; k < 64; k++) {
            STG[i].kinds[k] = -1;
        }
    }
    D_0063C158 = 0;
    for (i = 0; i < 87; i++) {
        STG[i].flags.i &= ~0x3FF;
    }
    /* Compiled-out debug hooks (see stageAnimDebugHook). The January listing
       zeroes a gp counter at line 650 (rows 649 and 651 to 654 code-free) and
       the retail build has neither that code nor the .sbss word. WHAT THE
       BYTES PIN: stage_Init reaches gcse with 656 to 659 insns, six to nine
       more than its statements give, so the expression table has 329 buckets
       and puts e + 0x180 ahead of m + 1, which is the ROM's spill slot order
       (dats base 0x78, m + 1 at 0x7C); at 325 buckets the two slots swap.
       WHAT THEY CANNOT PIN: how many of those insns sat here and how many at
       the code-free rows 679, 692 and 697 below, or the statements' text. */
    stageAnimDebugHook();
    stageAnimDebugHook();
    stageAnimDebugHook();
    D_0063C15C = 0;
    bga_ResetCamera();
    for (m = 0; m < 2; m++) {
        for (i = ((int *)tbl[m])[0]; i < ((int *)tbl[m])[1]; i++) {
            rec = D_002C2DC8 + i * 0x4C;
            n = *(int *)(rec + 0x34);
            if (n != 0) {
                char *ent = D_002BC6E0 + n * 0x14;

                for (k = 0; k < 2; k++) {
                    id = ((StgBgaSet *)ent)->id[k];
                    obj = D_00602FA0 + id * 0x5C;
                    if (id != 972) {
                        if (strncmp(*(char **)(obj + 0x54), D_0063A1B0, 3) == 0) {
                            /* Listing row 679, code-free. WHAT THE BYTES PIN: one
                           insn between the D_0063C158 load and the 0x284 store
                           at local-alloc, gone by final; without it the flags
                           address takes $4 and the 0x284 address $3, the
                           ROM's are the other way round. WHAT THEY CANNOT
                           PIN: the statement's text. */
                            stageAnimDebugHook();
                            STG[D_0063C158].flags.i &= 0x3FFFFFFF;
                            *(int *)((char *)D_0067D098 + D_0063C158 * 0x290 + 0x284) =
                                (int)*(char **)(obj + 0x54);
                            *(int *)(*(char **)(obj + 0x54) + 0x4) = *(int *)(obj + 0x48);
                            (*(char **)(obj + 0x54))[0xB] = obj[0x4C];
                            *(char *)(*(int *)((char *)D_0067D098 + D_0063C158 * 0x290 + 0x284) +
                                      0xA) = -1;
                            *(int *)((char *)D_0067D098 + D_0063C158 * 0x290 + 0x280) = (int)obj;
                            STG[D_0063C158].flags.i &= 0xC00FFFFF;
                            p = &D_00600498[*(int *)(obj + 0x40)];
                            q = &D_00600498[*(int *)(obj + 0x44)];
                            for (; p != q; p++) {
                                stage_MakeGObj((int *)p, D_0063C158);
                            }
                        } else {
                            /* listing row 692, code-free: counted in the gcse
                           window above */
                            stageAnimDebugHook();
                            STG[D_0063C158].flags.i =
                                (STG[D_0063C158].flags.i & 0x3FFFFFFF) | 0x40000000;
                            D_0067D098[D_0063C158].entry3 = *(int **)(obj + 0x54);
                            *(int *)((char *)D_0067D098 + D_0063C158 * 0x290 + 0x280) = (int)obj;
                        }
                        /* listing row 697, code-free: counted in the gcse window
                       above */
                        stageAnimDebugHook();
                        D_0063C158++;
                        if (D_0063C158 >= 88) {
                            debug_StdPrintfDummy(D_00550098, D_0063C158, 87);
                            debug_StdPrintfDummy(D_005500C8);
                            debug_assert(D_00550028, 0x2BE);
                            __assert(D_00550028, 0x2BE, D_0063A1A8);
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < D_0063C158; i++) {
        if (((STG[i].flags.i << 22) >> 22) >= 64) {
            debug_StdPrintfDummy(D_005500F8, ((STG[i].flags.i << 22) >> 22), 64);
            debug_assert(D_00550028, 0x2C8);
            __assert(D_00550028, 0x2C8, D_0063A1A8);
        }
        max = max < ((STG[i].flags.i << 22) >> 22) ? ((STG[i].flags.i << 22) >> 22) : max;
    }
    debug_StdPrintfDummy(D_00550128, D_0063C158, max);
    if (p != 0) {
        e = STG;
        for (i = 0; i < D_0063C158; i++, e++) {
            if ((e->flags.i >> 30) == 1) {
                continue;
            }
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
                if (STG_DAT(e->objs[k]) != 0) {
                    *(int *)(STG_DAT(e->objs[k]) + 0x8) = 0;
                }
            }
            k = 0;
            for (;;) {
                a = ((char **)*(int *)(e->p284 + 0x10))[k++];
                if (a == 0) {
                    break;
                }
                r = e->p280;
                no = -1;
                if (r != 0) {
                    no = (r - D_00602FA0) / 0x5CU;
                }
                bga_ApplyDObject(a, e->objs, ((e->flags.i << 22) >> 22), no);
            }
            e->flags.i &= 0xFFF003FF;
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
                if (*(int *)(STG_DAT(e->objs[k]) + 0xC) != 0) {
                    iosFree((void *)(*(int *)(STG_DAT(e->objs[k]) + 0xC) & 0x0FFFFFFF));
                }
                if (*(int *)(STG_DAT(e->objs[k]) + 0x10) != 0) {
                    iosFree((void *)(*(int *)(STG_DAT(e->objs[k]) + 0x10) & 0x0FFFFFFF));
                }
                *(int *)(STG_DAT(e->objs[k]) + 0xC) = 0;
                *(int *)(STG_DAT(e->objs[k]) + 0x10) = 0;
                *(int *)(STG_DAT(e->objs[k]) + 0xC) = (int)iosMallocDebug(
                    D_0063A44C, *(int *)(STG_DAT(e->objs[k]) + 0x8) << 6, D_00550028, 0x2F9);
                *(int *)(STG_DAT(e->objs[k]) + 0x10) = (int)iosMallocDebug(
                    D_0063A44C, *(int *)(STG_DAT(e->objs[k]) + 0x8) << 4, D_00550028, 0x2F9);
                /* The reallocation block's own count line (`X->8 = N;`, as
                   chain.c, boy.c and box.c spell the same block), here passed
                   the count field itself (listing 762; all three allocations
                   pass line 761, one macro invocation). reload_cse deletes it
                   as a no-op and turns the 0x870 test's load into the ROM's
                   register copy. */
                *(int *)(STG_DAT(e->objs[k]) + 0x8) = *(int *)(STG_DAT(e->objs[k]) + 0x8);
                if (*(int *)(STG_DAT(e->objs[k]) + 0x870) != 0) {
                    iosFree((void *)(*(int *)(STG_DAT(e->objs[k]) + 0x870) & 0x0FFFFFFF));
                }
                *(int *)(STG_DAT(e->objs[k]) + 0x870) = (int)iosMallocDebug(
                    D_0063A44C, *(int *)(STG_DAT(e->objs[k]) + 0x8) * 0x50, D_00550028, 0x2F9);
                for (t = 0; t < *(int *)(STG_DAT(e->objs[k]) + 0x8); t++) {
                    ((PlayWord *)(STG_NODE(e->objs[k], t) + 0x38))->l &= ~1;
                    ((PlayWord *)(STG_NODE(e->objs[k], t) + 0x38))->l &= ~2;
                    *(int *)(STG_NODE(e->objs[k], t) + 0x40) = 0;
                    *(int *)(STG_NODE(e->objs[k], t) + 0x44) = 0;
                    *(int *)(STG_NODE(e->objs[k], t) + 0x48) = 0;
                    *(float *)(STG_NODE(e->objs[k], t) + 0x4C) = 1.0f;
                    ((PlayWord *)(STG_NODE(e->objs[k], t) + 0x38))->l &= ~4;
                    *(int *)(STG_NODE(e->objs[k], t) + 0x30) = 0;
                    *(float *)(STG_NODE(e->objs[k], t) + 0x34) = 1.0f;
                    *(short *)(STG_NODE(e->objs[k], t) + 0x3A) = 0;
                    *(float *)(STG_NODE(e->objs[k], t) + 0x20) = 1.0f;
                    *(float *)(STG_NODE(e->objs[k], t) + 0x24) = 1.0f;
                    *(float *)(STG_NODE(e->objs[k], t) + 0x28) = 1.0f;
                }
                *(short *)(STG_DAT(e->objs[k]) + 0x84C) = 2;
                e->flags.i =
                    (e->flags.i & 0xFFF003FF) |
                    ((((e->flags.i << 12) >> 22) + *(int *)(STG_DAT(e->objs[k]) + 0x8)) & 0x3FF)
                        << 10;
                for (u = 0; u < *(int *)(STG_DAT(e->objs[k]) + 0x8); u++) {
                    _UnitMatrix((void *)(*(int *)(STG_DAT(e->objs[k]) + 0xC) + u * 64));
                    SetIdentityQuaternion((void *)(*(int *)(STG_DAT(e->objs[k]) + 0x10) + u * 16));
                }
            }
        }
        e = STG;
        for (i = 0; i < D_0063C158; i++, e++) {
            if ((e->flags.i >> 30) == 1) {
                continue;
            }
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
                g = e->objs[k];
                arg = D_00550150;
                tbl2 = D_002C1270 + *(int *)((char *)e->dats[k] + 4) * 100;
                fn = *(int (**)(char *, StageGObjInit *))(tbl2 + 0x58);
                if (fn != 0) {
                    *(int *)(STG_DAT(e->objs[k]) + 0x830) = fn(g, &arg);
                }
                isysGObjProcAdd(g, *(int *)(tbl2 + 0x5C), 1, 0x16);
                isysGObjProcAdd(g, *(int *)(tbl2 + 0x50), 1, 0x17);
                isysGObjProcAdd(g, *(int *)(tbl2 + 0x4C), 1, 0x18);
                isysGObjLinkObjDL(g, 0, 0, 7, 0xFFFFFFFF);
                *(int *)(g + 0x16C) = 1;
                *(int *)(STG_DAT(e->objs[k]) + 0x74) = 0;
            }
        }
    }
    e = STG;
    for (i = 0; i < D_0063C158; i++, e++) {
        if (*(int *)(e->p280 + 0x50) != 0) {
            stage_SetAnimation(*(int *)(e->p280 + 0x58), 1, 0);
        }
    }
    return D_0063C158;
}

void stage_SetAnimation(int key, int p1, int p2)
{
    int uid = -1;
    int i;
    int k;
    int dbg = 0; /* local debug switch, see the test in case 0 below */
    StageAnim *e;

    for (i = 0, e = (StageAnim *)D_0067D098; i < D_0063C158; i++, e++) {
        if (key != e->entry1[0x58 / 4]) {
            continue;
        }
        switch (e->flags.i >> 30) {
        case 0:
            uid = e->entry2[1];
            /* Local debug switch, off. What the bytes pin: the ROM's .rodata
               keeps "Illegal Group No. %d\n" at 0x550190 with no reference
               anywhere in the ROM, between stage_Init's data and
               stage_CheckAnimationFinish's string, so a print of it stood in
               this function and the optimizer deleted it; and the ROM's
               allocation needs gcse to see a count outside 96 to 99 insns here
               (106 with this block, 97 without, whose expression table of 49
               buckets puts the flags word's PRE register ahead of the object
               table's and rotates $7/$8/$9). A switch set
               to 0 outside the loop does both: cse cannot carry the constant
               across the loop label, gcse's last constant propagation folds
               the test and the next jump pass deletes the call. The listing
               leaves rows 847 to 852 code-free around the group number read.
               What the bytes cannot pin: the switch's name, the test's exact
               form and which value the line printed. */
            if (dbg) {
                debug_StdPrintfDummy("Illegal Group No. %d\n", uid);
            }
            bga_SetFrame(e->entry2, p2, p1, e->entry1[0x50 / 4]);
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
                *(int *)(*(char **)(e->obj[k] + 0x15C) + 0x74) = 1;
            }
            break;
        case 1:
            bga_SetCamFrame(e->entry3, p2, p1, e->entry1[0x50 / 4]);
            break;
        }
        break;
    }

    if (uid != -1) {
        for (i = 0, e = (StageAnim *)D_0067D098; i < D_0063C158; i++, e++) {
            if ((e->flags.i >> 30) != 0) {
                continue;
            }
            if (uid != e->entry2[1] || key == e->entry1[0x58 / 4]) {
                continue;
            }
            for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
                if (*(char **)(e->obj[k] + 0x15C) != 0) {
                    *(int *)(*(char **)(e->obj[k] + 0x15C) + 0x74) = 0;
                }
            }
        }
    }
}

inline int stage_CheckAnimationFinish(int a0)
{
    int i;
    char *e = (char *)D_0067D098;
    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
            case 0:
                return bga_CheckAnimationFinish(*(int *)(e + 0x284));
            case 1:
                return bga_CheckSdfCameraFinish(*(int *)(e + 0x288));
            }
        }
    }
    debug_StdPrintfDummy(D_005501A8);
    debug_assert(D_00550028, 0x38D);
    __assert(D_00550028, 0x38D, D_0063A1A8);
    return 0;
}

int stage_ContinueAnimation(int a0, int a1)
{
    int i;
    char *e = (char *)D_0067D098;
    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
            case 0:
                if (bga_CheckAnimationFinish(*(int *)(e + 0x284)) != 0) {
                    stage_SetAnimation(a0, 0, -1);
                    stage_SetAnimation(a1, 1, 0);
                    return 1;
                }
                return 0;
            case 1:
                if (bga_CheckSdfCameraFinish(*(int *)(e + 0x288)) == 0) {
                    return 0;
                }
                stage_SetAnimation(a0, 0, -1);
                stage_SetAnimation(a1, 1, 0);
                return 1;
            }
        }
    }
    debug_StdPrintfDummy(D_005501E0);
    debug_assert(D_00550028, 0x3BA);
    __assert(D_00550028, 0x3BA, D_0063A1A8);
    return 0;
}

inline int stage_CheckAnimationFrame(int a0, int a1, int a2)
{
    int i;
    char *e = (char *)D_0067D098;
    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
            case 0:
                return bga_CheckAnimationFrame(*(int *)(e + 0x284), a1, a2);
            case 1:
                return bga_CheckSdfCameraFrame(*(int *)(e + 0x288), a1, a2);
            }
        }
    }
    return -1;
}

inline int stage_CheckAnimationFrameIn(int a0, int a1, int a2)
{
    int i;
    char *e = (char *)D_0067D098;
    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
            case 0:
                return bga_CheckAnimationFrameIn(*(int *)(e + 0x284), a1, a2);
            case 1:
                return bga_CheckSdfCameraFrameIn(*(int *)(e + 0x288), a1, a2);
            }
        }
    }
    return -1;
}

void stage_ResetAnimation(void)
{
    bga_ResetAnimation();
    if (D_0028F4D4[0] != 0)
        return;
    light_KillAllFixLight();
}

void stage_CalcAnimationNoParent(void)
{
    int i;
    char *e;

    if (graphics_ready != 0) {
        return;
    }
    if (D_0063C158 == 0) {
        return;
    }
    bga_SetUniqAnimationFlag(1);
    _InitCurrentMatrix();
    e = (char *)D_0067D098;
    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        switch (*(int *)(e + 0x28C) >> 30) {
        case 0: {
            char *entry2 = *(char **)(e + 0x284);
            signed char lock = *(signed char *)(entry2 + 0xB);

            if (lock == 0) {
                if (*(int *)(*(char **)(entry2 + 0x24) + 0x20) != 0) {
                    continue;
                }
            }
            if (D_0028F4C0[0x14 / 4] != 0) {
                continue;
            }
            switch (*(signed char *)(entry2 + 0xA)) {
            case -1: {
                int k;

                for (k = 0; k < ((*(int *)(e + 0x28C) << 22) >> 22); k++) {
                    char *objs = e + 0x80;
                    char *o = *(char **)(objs + (k << 2));

                    ((int *)*(int *)(o + 0x15C))[0x74 / 4] = 0;
                    if (((int *)*(int *)(o + 0x15C))[0x8 / 4] != 0) {
                        *(int *)((int *)*(int *)(o + 0x15C))[0xC / 4] = 0;
                    }
                }
                break;
            }
            case 0:
                break;
            case 1:
                if (lock != 0) {
                    if (D_0063B13C & 1) {
                        debug_Printf(0, ScreenHeight / 2 - 28, 0xCCCCCC00, D_00550210,
                                     *(int *)(e + 0x280));
                    }
                }
                _InitCurrentMatrix();
                bga_CalcAnimation(*(char **)(e + 0x284), *(int *)(*(char **)(e + 0x280) + 0x50), 0);
                break;
            }
            break;
        }
        case 1:
            if (D_0028F4C0[0x14 / 4] != 0) {
                continue;
            }
            if (*(int *)(*(char **)(e + 0x288) + 0xC) != 1) {
                continue;
            }
            _InitCurrentMatrix();
            bga_CalcSdfCamera(*(char **)(e + 0x288), *(int *)(*(char **)(e + 0x280) + 0x50));
            break;
        }
    }
    bga_SetUniqAnimationFlag(0);
}

void stage_CalcAnimationParent(void)
{
    int i;
    char *e;
    char *entry2;

    if (graphics_ready != 0) {
        return;
    }
    if (D_0063C158 == 0) {
        return;
    }
    bga_SetUniqAnimationFlag(1);
    e = (char *)D_0067D098;
    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        if ((*(int *)(e + 0x28C) >> 30) != 0) {
            continue;
        }
        entry2 = *(char **)(e + 0x284);
        if (*(signed char *)(entry2 + 0xB) != 0) {
            continue;
        }
        if (*(int *)(*(char **)(entry2 + 0x24) + 0x20) == 0) {
            continue;
        }
        if (D_0028F4C0[0x14 / 4] != 0) {
            continue;
        }
        switch (*(signed char *)(entry2 + 0xA)) {
        case -1: {
            int k;

            for (k = 0; k < ((*(int *)(e + 0x28C) << 22) >> 22); k++) {
                char *objs = e + 0x80;
                char *o = *(char **)(objs + (k << 2));
                ((int *)*(int *)(o + 0x15C))[0x74 / 4] = 0;
                if (((int *)*(int *)(o + 0x15C))[0x8 / 4] != 0) {
                    *(int *)((int *)*(int *)(o + 0x15C))[0xC / 4] = 0;
                }
            }
            break;
        }
        case 1:
            _InitCurrentMatrix();
            bga_CalcAnimation(*(char **)(e + 0x284), *(int *)(*(char **)(e + 0x280) + 0x50), 0);
            break;
        case 0:
            _InitCurrentMatrix();
            bga_CalcAnimation(*(char **)(e + 0x284), *(int *)(*(char **)(e + 0x280) + 0x50), 1);
            break;
        }
    }
    bga_SetUniqAnimationFlag(0);
}

void stage_DispAnimation(void)
{
    int i;
    char *e;

    if (D_0063C158 == 0) {
        return;
    }

    e = (char *)D_0067D098;
    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        signed char lv;
        int k;

        if (entry1[0x58 / 4] == 0x42) {
            continue;
        }
        if ((*(int *)(e + 0x28C) >> 30) != 0) {
            continue;
        }
        lv = *(signed char *)(*(int *)(e + 0x284) + 0xA);
        if (lv == -1) {
            continue;
        }
        if (lv < -1) {
            continue;
        }
        if (lv >= 2) {
            continue;
        }
        for (k = 0; k < ((*(int *)(e + 0x28C) << 22) >> 22); k++) {
            char *objs = e + 0x80;
            char *d = *(char **)(*(char **)(objs + (k << 2)) + 0x15C);

            if (*(int *)(d + 0x74) != 0) {
                reg_DispObj(d);
            }
        }
    }
    bga_DispLightning();
}

inline void stage_SetLoopFlag(int key, int a1)
{
    int count = *(volatile int *)&D_0063C158;
    int i;
    char *e = (char *)D_0067D098;
    for (i = 0; i < count; i++, e += 0x290) {
        int *p = *(int **)(e + 0x280);
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = a1;
            p = &(*((volatile int *)(&D_0063C158)));
            count = *p;
        }
    }
}

inline void stage_SetFrameStep(int target, int val)
{
    int n = D_0063C158;
    char *p = (char *)D_0067D098;
    int i;
    if (n <= 0)
        return;
    i = n;
    do {
        int *entry1 = *(int **)(p + 0x280);
        if (target == entry1[0x58 / 4]) {
            int *entry2 = *(int **)(p + 0x284);
            *(float *)((char *)entry2 + 0x1C) = (float)val;
        }
        p += 0x290;
    } while (--i);
}

inline void stage_SetParentOfGObj(int a0, void *a1)
{
    int i;
    int one = 1;
    char *e = D_0067D098;
    for (i = 0; i < D_0063C158; i++) {
        if (a0 == *(int *)(*(char **)(e + 0x280) + 0x58)) {
            *(struct B8 *)(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x20) = *(struct B8 *)a1;
            *(int *)(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x28) = one;
        }
        e += 0x290;
    }
}

inline void stage_SetParentOfGObjWithLocalRotationFlag(int a0, void *a1, int a2)
{
    int i;
    char *e = D_0067D098;
    for (i = 0; i < D_0063C158; i++) {
        if (a0 == *(int *)(*(char **)(e + 0x280) + 0x58)) {
            *(Blob8 *)(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x20) = *(Blob8 *)a1;
            *(int *)(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x28) = a2;
        }
        e += 0x290;
    }
}

inline void stage_SetLocalizeGeometry(int key, int arg1, int arg2)
{
    int count = *(volatile int *)&D_0063C158;
    int i = 0;
    char *e = (char *)D_0067D098;
    if (count <= 0)
        return;
    do {
        int *entry1 = *(int **)(e + 0x280);
        if (key == entry1[0x58 / 4]) {
            int *entry2;
            char *target;
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            _CopyVector(target, arg1);
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            CopyQuaternion(target + 0x10, arg2);
            count = *(volatile int *)&D_0063C158;
        }
        i++;
        e += 0x290;
    } while (i < count);
}

void stage_SetScale(int key, float scale)
{
    int i;
    int j;
    int k;
    StageAnim *e = (StageAnim *)D_0067D098;

    for (i = 0; i < D_0063C158; i++, e++) {
        if (key == e->entry1[0x58 / 4]) {
            if ((e->flags.i >> 30) == 0) {
                for (j = 0; j < ((e->flags.i << 22) >> 22); j++) {
                    for (k = 0; k < *(int *)((char *)((AnimWord *)(e->obj[j] + 0x15C))->i + 0x8);
                         k++) {
                        *(float *)(*(char **)((char *)((AnimWord *)(e->obj[j] + 0x15C))->i +
                                              0x870) +
                                   k * 0x50 + 0x20) =
                            *(float *)(*(char **)((char *)((AnimWord *)(e->obj[j] + 0x15C))->i +
                                                  0x870) +
                                       k * 0x50 + 0x24) =
                                *(float *)(*(char **)((char *)((AnimWord *)(e->obj[j] + 0x15C))->i +
                                                      0x870) +
                                           k * 0x50 + 0x28) = scale;
                    }
                }
            }
        }
    }
}

float stage_PlayBgAnimation(int key, float t, void *v, void *q)
{
    int i;
    int k;
    int n = D_0063C158;
    float r = t;
    float f;
    char *e;

    if (n == 0) {
        return 0.0f;
    }
    e = (char *)D_0067D098;
    for (i = 0; i < n; i++, e += 0x290) {
        char *entry2;

        if (key != *(int *)(*(char **)(e + 0x280) + 0x58)) {
            continue;
        }
        if ((*(int *)(e + 0x28C) >> 30) != 0) {
            continue;
        }
        _CopyVector(*(void **)(*(char **)(e + 0x284) + 0x24), v);
        CopyQuaternion(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x10, q);
        bga_SetFrame(*(int *)(e + 0x284), (int)r, 1, *(int *)(*(char **)(e + 0x280) + 0x50));
        for (k = 0; k < ((*(int *)(e + 0x28C) << 22) >> 22); k++) {
            char *objs = e + 0x80;

            *(int *)(*(int *)(*(char **)(objs + (k << 2)) + 0x15C) + 0x74) = 1;
        }
        if (D_0028F4C0[0x14 / 4] != 0) {
            break;
        }
        f = *(float *)(*(char **)(e + 0x284) + 0x1C);
        if (D_0028F4C0[0] != 0) {
            r = t + f * 1.2075409f;
        } else {
            r = t + f;
        }
        if (*(float *)(*(char **)(e + 0x284) + 0x18) <= r) {
            r = *(int *)(*(char **)(e + 0x280) + 0x50) != 0
                    ? *(float *)(*(char **)(e + 0x284) + 0x14)
                    : -1.0f;
        }
        break;
    }
    e = (char *)D_0067D098;
    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        if (key != *(int *)(*(char **)(e + 0x280) + 0x58)) {
            continue;
        }
        if ((*(int *)(e + 0x28C) >> 30) != 0) {
            continue;
        }
        for (k = 0; k < ((*(int *)(e + 0x28C) << 22) >> 22); k++) {
            char *objs = e + 0x80;
            char *d = *(char **)(*(char **)(objs + (k << 2)) + 0x15C);

            reg_DispObj(d);
            *(int *)(d + 0x74) = 0;
        }
        *(signed char *)(*(char **)(e + 0x284) + 0xA) = -1;
    }
    return r;
}

/* This TU's .lit4 holds 1.2075409f twice, one word per owner and no
   deduplication: stage_PlayBgAnimation's literal above is the first, and
   this function's own is the second. */
float stage_PlayBgAnimationDissolve(int key, void *v, void *q, float t, float dv)
{
    int i;
    int k;
    int m;
    float r = t;
    float f;
    StageAnim *e;

    if (D_0063C158 == 0) {
        return 0.0f;
    }
    for (i = 0, e = (StageAnim *)D_0067D098; i < D_0063C158; i++, e++) {
        if (key != e->entry1[0x58 / 4]) {
            continue;
        }
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        _CopyVector(*(void **)((char *)e->entry2 + 0x24), v);
        CopyQuaternion(*(char **)((char *)e->entry2 + 0x24) + 0x10, q);
        bga_SetFrame(e->entry2, (int)r, 1, e->entry1[0x50 / 4]);
        for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
            *(int *)(*(char **)(e->obj[k] + 0x15C) + 0x74) = 1;
        }
        if (D_0028F4C0[0x14 / 4] != 0) {
            break;
        }
        f = *(float *)((char *)e->entry2 + 0x1C);
        if (D_0028F4C0[0] != 0) {
            r = t + f * 1.2075409f;
        } else {
            r = t + f;
        }
        if (*(float *)((char *)e->entry2 + 0x18) <= r) {
            r = e->entry1[0x50 / 4] != 0 ? *(float *)((char *)e->entry2 + 0x14) : -1.0f;
        }
        break;
    }
    for (i = 0, e = (StageAnim *)D_0067D098; i < D_0063C158; i++, e++) {
        if (key != e->entry1[0x58 / 4]) {
            continue;
        }
        if ((e->flags.i >> 30) != 0) {
            continue;
        }
        for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
            char *d = *(char **)(e->obj[k] + 0x15C);

            for (m = 0; m < *(int *)(d + 0x8); m++) {
                *(float *)(*(int *)(d + 0x870) + m * 80 + 0x34) = dv;
            }
            reg_DispObj(d);
            *(int *)(d + 0x74) = 0;
            stageAnimDebugHook();
            stageAnimDebugHook();
        }
        stageAnimDebugHook();
        *(signed char *)((char *)e->entry2 + 0xA) = -1;
    }
    return r;
}

int *stage_MakePlayBgAnimation(int key)
{
    int i;
    int found = -1;
    float f = 1.0f;
    short num = 0;
    char *e = (char *)D_0067D098;
    int *p;

    for (i = 0; i < D_0063C158; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);

        if (key == entry1[0x58 / 4]) {
            found = i;
            {
                int w = *(int *)(e + 0x28C);

                int t = (w << 2) >> 22;

                *(int *)(e + 0x28C) = (w & 0xC00FFFFF) | (((t + 1) & 0x3FF) << 20);
                num = (short)t;
            }
            f = ((AnimWord *)(*(int *)(e + 0x284) + 0x14))->f;
            break;
        }
    }

    if (found == -1) {
        debug_StdPrintfDummy(D_00550230);
        return 0;
    }

    p = (int *)iosMallocDebug(D_0063A44C, 0x40, D_00550028, 0x5D6);
    if (p == 0) {
        debug_StdPrintfDummy(D_00550278);
        return 0;
    }

    ((PlayWord *)p)->l = ((((PlayWord *)p)->l & ~0x3FFF) | (key & 0x3FFF) | 0x4000) & ~0x8000;
    ((PlayWord *)((char *)p + 2))->h = num;
    *(float *)((char *)p + 4) = f;
    *(float *)((char *)p + 8) = 1.0f;
    *(float *)((char *)p + 0xC) = 1.0f;
    if (D_0063C15C != 0) {
        D_0063C15C[0x10 / 4] = (int)p;
    }
    p[0x10 / 4] = 0;
    p[0x14 / 4] = (int)D_0063C15C;
    D_0063C15C = p;
    return p;
}

void stage_KillPlayBgAnimation(int **self)
{
    int *node = *self;
    int *next;
    int *prev;
    if (node == 0)
        return;
    next = (int *)node[0x10 / 4];
    if (next != 0) {
        next[0x14 / 4] = node[0x14 / 4];
    } else {
        D_0063C15C = (int *)node[0x14 / 4];
        node = *self;
    }
    prev = (int *)node[0x14 / 4];
    if (prev != 0) {
        prev[0x10 / 4] = node[0x10 / 4];
    }
    if (D_0063C15C != 0) {
        D_0063C15C[0x10 / 4] = 0;
    }
    freeseki(*self);
}

inline void stage_KillPlayBgAnimationIfOverMaxCount(int a0, int a1)
{
    AnimNode *p = (AnimNode *)D_0063C15C;
    int count = 0;
    while (p != 0) {
        long v = p->field0;
        if ((((unsigned short)v << 18) >> 18) == a0) {
            if (!(v & 0x8000)) {
                count++;
                if (a1 < count) {
                    p->field0 = v | 0x8000;
                }
            }
        }
        p = p->next;
    }
}

/* File-static helper the January listing shows at src/StageAnimation.c:1588-1592,
 * inlined twice in stage_DispBgAnimation and twice in stage_DispBgAnimationNoFinish.
 * It has no symbol in MAIN.MAP and no census row: INTERIM, the name below is
 * ours, not the developer's. */
static inline void stage_SetBgAnimationPlayNode(BgaPlayNode *node, int key)
{
    int i;
    int k;
    StageAnim *e;

    for (i = 0, e = (StageAnim *)D_0067D098; i < D_0063C158; i++, e++) {
        if (key == e->entry1[0x58 / 4]) {
            if ((e->flags.i >> 30) == 0) {
                for (k = 0; k < ((e->flags.i << 22) >> 22); k++) {
                    *(void **)(*(char **)(e->obj[k] + 0x15C) + 0x850) = node;
                }
            }
        }
    }
}

int stage_DispBgAnimation(void *p)
{
    BgaPlayNode **self = (BgaPlayNode **)p;

    if (*self == 0) {
        return -1;
    }
    if ((*self)->kill) {
        stage_KillPlayBgAnimation((int **)self);
        *self = 0;
        return -1;
    }
    if ((*self)->scale != 1.0f) {
        stage_SetScale((*self)->no, (*self)->scale);
    }
    if ((*self)->speed == 1.0f) {
        stage_SetBgAnimationPlayNode(*self, (*self)->no);
        (*self)->frame =
            stage_PlayBgAnimation((*self)->no, (*self)->frame, (*self)->pos, (*self)->rot);
    } else {
        stage_SetBgAnimationPlayNode(*self, (*self)->no);
        (*self)->frame = stage_PlayBgAnimationDissolve((*self)->no, (*self)->pos, (*self)->rot,
                                                       (*self)->frame, (*self)->speed);
    }
    (*self)->play = 0;
    if ((*self)->frame == -1.0f) {
        stage_KillPlayBgAnimation((int **)self);
        *self = 0;
        return -1;
    }
    return 0;
}

int stage_DispBgAnimationNoFinish(char **slot)
{
    BgaPlayNode **self = (BgaPlayNode **)slot;
    int i;
    StageAnim *e;

    if (*self == 0) {
        return -1;
    }
    if ((*self)->kill) {
        stage_KillPlayBgAnimation((int **)self);
        *self = 0;
        return -1;
    }
    if ((*self)->scale != 1.0f) {
        stage_SetScale((*self)->no, (*self)->scale);
    }
    if ((*self)->speed == 1.0f) {
        stage_SetBgAnimationPlayNode(*self, (*self)->no);
        (*self)->frame =
            stage_PlayBgAnimation((*self)->no, (*self)->frame, (*self)->pos, (*self)->rot);
    } else {
        stage_SetBgAnimationPlayNode(*self, (*self)->no);
        (*self)->frame = stage_PlayBgAnimationDissolve((*self)->no, (*self)->pos, (*self)->rot,
                                                       (*self)->frame, (*self)->speed);
    }
    (*self)->play = 0;
    if ((*self)->frame == -1.0f) {
        for (i = 0, e = (StageAnim *)D_0067D098; i < D_0063C158; i++, e++) {
            if ((*self)->no == e->entry1[0x58 / 4]) {
                if ((e->flags.i >> 30) == 0) {
                    /* A jump to the function's exit, the way Light.c leaves
                       its loops (goto found): the ROM keeps this store in a
                       block loop.c moved out of the loop, with the key and
                       the bound hoisted, and jumps to the shared `return 0`.
                       A break (the loop's own exit label) is rolled into the
                       loop's exit test by stmt.c's expand_end_loop, which
                       jump then duplicates into a second loop entry; a
                       return gets its own $2 = 0 before the store. The bytes
                       pin the target, not the label's name. */
                    (*self)->frame = *(float *)((char *)e->entry2 + 0x18);
                    goto end;
                }
            }
        }
    }
end:
    return 0;
}

void stage_SetCameraForceOff(int a0, int a1, int a2, int a3)
{
    bga_SetCameraForceOff(a0, a1, a2, a3);
}
