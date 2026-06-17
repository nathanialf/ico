#include "common.h"
#include "ico/types.h"

void InitRopeGeo(void) {
}

typedef struct { long long a, b; } Blk10;
typedef struct { long long w[10]; } Blk50;
typedef struct { Blk50 m0, m1; } TwoBlk;
typedef struct { char c[8]; } Blk8;

typedef struct RopeNode_s {
    char _0[0x20];
    float f20, f24, f28;     /* 0x20, 0x24, 0x28 */
    char _2c[0x4];
    int f30;                 /* 0x30 */
    float f34;               /* 0x34 */
    long long f38;           /* 0x38 — flags qword */
    int f40, f44, f48;       /* 0x40, 0x44, 0x48 */
    float f4C;               /* 0x4C */
} RopeNode;                  /* 0x50 */

typedef struct {
    char _0[0x8];
    int f8;                  /* 0x8 */
    int fC;                  /* 0xC — alloc handle */
    int f10;                 /* 0x10 — alloc handle */
    char _14[0x7F4];
    short f808;              /* 0x808 */
    char _80a[0x26];
    struct RopeNode_s *nodes; /* 0x830 — node array */
} RopeSub;

typedef struct {
    int f0;                  /* 0x0 */
    int f4;                  /* 0x4 */
    int f8;                  /* 0x8 */
    int fC;                  /* 0xC */
    int f10;                 /* 0x10 */
} RopeFix;                   /* 0x14 */

extern char D_004C20F0[];
extern char D_004C20F0_2d[][0x50] __asm__("D_004C20F0");
extern char D_006128D0[];
extern char D_006128E0[];
extern char D_00612920[];
extern char D_00612930[];
extern char D_00612940[];
extern char D_0062D720[];
extern float D_006296A0;
extern int D_0062A310;
extern int D_0062A324;

extern void *iosFree(int a0, int a1, char *a2, int a3);
extern void iosMallocCheckLeak2(int a0);
extern void debug_assertMessage(char *a0, ...);
extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, char *a2);
extern int func_00105078(void);
extern void func_002400F8(int a0);
extern void func_00105108(float a0, float a1, float a2);
extern void func_00104DC0(int a0);
extern void func_0023FDD8(void *a0, void *a1, void *a2);
extern int ClipWallBoxStop(void *a0);
extern int bind2(void *a0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", SetRopeFixPoint);


extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void HoldRope(void *a0, void *a1) {
    Obj7F0 *q = GOBJ_SUB(a0)->p_7F0;
    int *r = *(int **)q;
    int *s = *(int **)r;
    MatrixDrive_TurnObjectMatrix((int)((char *)s + 0x20), a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", ropeGeo);

extern int func_00105078(void);
extern void func_002400F8(int a0);
extern void func_0023FE08(int a0, int a1, int a2);
extern void func_001C1560(int a0, int a1, int a2);

void RopeDL(char *a0)
{
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    func_002400F8(func_00105078());
    {
        char *p = *(char **)(a0 + 0x15C);
        if (*(int *)p != 0) {
            int r1 = func_00105078();
            char *p2 = *(char **)(a0 + 0x15C);
            char *sub = *(char **)(*(int *)p2 + 0x15C);
            int addr = *(int *)(sub + 0xC) + *(int *)(p2 + 4) * 0x40;
            func_0023FE08(r1, addr, func_00105078());
        }
    }
    func_001C1560(*(int *)q, 0, func_00105078());
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", CheckRopeUpperWallClimbable);

int ReleaseRope(int a0, void *a1) {
    return GOBJ_SUB(a1)->p_7F0->f_4;
}
