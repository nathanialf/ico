#include "common.h"
#include "ico/types.h"

union ENVIF {
    int i;
    float f;
};

/* .data — carved VMA 0x4F1D60..0x4F1E10: the per-stage ditch-distance
   tables getDitchDistTbl selects between (the first six are ranges
   terminated by -1.0f, the rest position/orientation vectors).  Values are
   the shortest decimals that round-trip through binary32; every byte
   verified against baserom/pal/baseelf.rom. */
float D_004F1D60[4] = {150.0f, 215.0f, 315.0f, -1.0f};

float D_004F1D70[4] = {150.0f, 235.0f, 315.0f, -1.0f};

float D_004F1D80[4] = {315.0f, 330.0f, 350.0f, -1.0f};

float D_004F1D90[4] = {150.0f, 215.0f, 315.0f, -1.0f};

float D_004F1DA0[4] = {150.0f, 215.0f, 315.0f, -1.0f};

float D_004F1DB0[4] = {-1.0f, 0.0f, 0.0f, 0.0f};

float D_004F1DC0[4] = {226.0f, -2328.0f, 343.0f, 1.0f};

float D_004F1DD0[4] = {0.642799f, 0.0f, -0.765893f, 0.0f};

float D_004F1DE0[4] = {602.0f, -3775.0f, 2480.0f, 1.0f};

float D_004F1DF0[4] = {749.0f, -3775.0f, 2650.0f, 1.0f};

float D_004F1E00[4] = {559.0f, -3775.0f, 2503.0f, 1.0f};

extern int ACTGame_FLAG_TETSUNAGI(void);

typedef struct {
    float x, y, z, w;
} Vec4 __attribute__((aligned(16)));

/* {30, 0, -50, 0}: the sofa seat offset in the room's local space.  Lives in
   act-env's own .rodata run at 0x621A00 (only this TU's code references
   0x621A00..0x621A3F); extern until that run is carved. */
extern Vec4 D_00621A00;
extern char *D_00639EA4;
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0AddVector(float *a0, float *a1, float *a2);
extern void sceVu0ScaleVector(float *a0, float *a1, float a2);
extern int CheckPureWallAttribute();
extern int CheckWallAttribute();
extern int stage_no;
extern int CheckPureWallAttribute__pn(int a0, int a1) __asm__("CheckPureWallAttribute");
extern int CheckWallAttribute__pn(int a0, int a1) __asm__("CheckWallAttribute");
/* prototypes: their order is the inline tail's emission order */
void ACTSetEnvAllmighty(char *a0);
void GetSofaPosition(char *a0, char *a1);
void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2);
int CheckWallAttributeEdegWall(int a0);

inline void GetSofaPosition(char *a0, char *a1)
{
    char *w = *(char **)(a0 + 0x164);
    Vec4 v = D_00621A00;
    *(float *)(w + 0x560) = *(float *)(w + 0x4B0);
    *(float *)(w + 0x564) = *(float *)(w + 0x4B4);
    *(float *)(w + 0x568) = *(float *)(w + 0x4B8);
    if (a0 == D_00639EA4) {
        v.x = -v.x;
    }
    v.w = 1.0f;
    sceVu0ApplyMatrix(w + 0x5B0, *(void **)(*(char **)(a1 + 0x15C) + 0xC), &v);
}

extern char *D_00639EA8;
extern float D_006397E8;
extern float D_006397EC;
extern Vec4 D_00621A10;
extern float *test_CURRENTROOT(void *a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern float _GetDirection(void *orient);
extern void _ApplyRyGV(void *v, float ry);
extern void _OrientXZGV(void *out, void *a, void *b);

static inline int getDitchCarryMode(void)
{
    void *a;
    void *b;

    if (D_00639EA4 != 0 && D_00639EA8 != 0) {
        a = *(void **)*(char **)(D_00639EA4 + 0x15C);
        b = *(void **)*(char **)(D_00639EA8 + 0x15C);

        if (a != 0 && *(int *)((char *)a + 0xC) == 0x2C)
            return 1;
        if (b != 0 && *(int *)((char *)b + 0xC) == 0x2C)
            return 2;
    }
    return 0;
}

static inline int getDitchCarryModeStage8(void)
{
    if (stage_no == 8) {
        return getDitchCarryMode();
    }
    return 0;
}

void getDitchDistTbl(float **tbl, float *range, int *sofa, float *pos, void *obj, int *carry)
{
    Vec4 v;
    int mode;

    *tbl = D_004F1D60;

    *sofa = 0;
    *carry = 0;
    *range = 0.0f;
    if (stage_no == 26) {
        *tbl = D_004F1D70;
        if (getDitchCarryMode()) {
            *range = 50.0f;
        }
    }
    mode = getDitchCarryModeStage8();
    if (mode) {
        if (D_006397E8 < test_CURRENTROOT(D_00639EA4)[1]) {
            *tbl = D_004F1D80;
            if (mode == 1) {
                v.x = test_CURRENTROOT(D_00639EA4)[0];
                v.y = test_CURRENTROOT(D_00639EA4)[1];
                v.z = test_CURRENTROOT(D_00639EA4)[2];
                sceVu0SubVector(&v, &v, D_004F1DC0);
                _ApplyRyGV(&v, (float)(int)(_GetDirection(D_004F1DD0) / D_006397EC * 180.0f) *
                                   D_006397EC / 180.0f);
                if (v.z < -150.0f) {
                    *tbl = D_004F1DB0;
                }
            }
            if (mode == 2) {
                v.x = test_CURRENTROOT(D_00639EA4)[0];
                v.y = test_CURRENTROOT(D_00639EA4)[1];
                v.z = test_CURRENTROOT(D_00639EA4)[2];

                if (520.0f < v.x) {
                    *tbl = D_004F1DB0;
                }
            }
        } else {
            if (mode == 1) {
                v = D_00621A10;

                *tbl = D_004F1D90;
                pos[0] = v.x;
                pos[1] = v.y;
                pos[2] = v.z;
                _OrientXZGV(obj, D_004F1DE0, &v);

                *carry = mode;
            } else {
                *tbl = D_004F1DA0;
                pos[0] = D_004F1E00[0];
                pos[1] = D_004F1E00[1];
                pos[2] = D_004F1E00[2];
                _OrientXZGV(obj, D_004F1DF0, D_004F1E00);
            }
            *sofa = 1;
        }
    }
}

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
    char _98[0x28];
} ClipWork;

extern void ClipFloor(void *a0);

int GetDitchPosition(float *out, float *org, float *dir, float d0, float d1, float h)
{
    ClipWork work;
    float tmp[4];
    /* The ROM frame is 0x1F0 = 0xC0 (work) + 0x10 (tmp) + 0xD0 more of
       aggregate locals under the register saves, and act-env.c:1175-1195 emit
       no instructions anywhere in the listing: the dev's second probe was
       disabled while its locals stayed declared.  Their sizes are what the
       frame proves. */
    ClipWork work2;
    float tmp2[4];

    sceVu0ScaleVector(tmp, dir, d0 + d1);
    sceVu0AddVector(work.a, org, tmp);
    work.b[0] = work.a[0];
    work.b[1] = work.a[1];
    work.b[2] = work.a[2];
    work.a[1] -= 100.0f;
    work.b[1] += h + 100.0f;
    ClipFloor(&work);
    if (work.f_94 != 0) {
        out[0] = work.pos[0];
        out[1] = work.pos[1];
        out[2] = work.pos[2];
        return 1;
    }
    return 0;
}

inline void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2)
{
    float acc[4] __attribute__((aligned(16)));
    char *w;
    int i;
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    i = 3;
    w = (char *)a2;
    do {
        sceVu0AddVector(acc, acc, (float *)w);
        w += 0x10;
        i--;
    } while (i >= 0);
    sceVu0ScaleVector((float *)a0, acc, 0.25f);
    if (a1 != 0) {
        ((union ENVIF *)((char *)a0 + 0xC))->f = 1.0f;
        sceVu0ApplyMatrix(a0, (void *)*(int *)(*(char **)((char *)a1 + 0x15C) + 0xC), a0);
    }
}

extern char D_00621A20[];
extern char D_00621A30[];
extern char D_00621A40[];
extern char D_00621A50[];
extern char D_00621A60[];
extern char D_00621A70[];
extern char D_00621A80[];
extern char D_00621A90[];
extern char D_00621AA0[];
extern char D_00621AB0[];
extern char D_00621AC0[];
extern char D_00621AD0[];
extern char D_00621AE0[];
extern char D_00621AF0[];
extern char D_00621B00[];
extern char D_0063BD40[];
extern char D_0063BD48[];
extern int D_0063B13C;
extern void debug_Printf(int x, int y, unsigned int color, char *fmt, ...);

typedef struct {
    int on;
    char *name;
} OrientFlagRow;

void DebugActOrientFlag(unsigned int *f)
{
    OrientFlagRow tbl[16] = {
        {(f[1] >> 18) & 1, D_00621A20}, {(f[1] >> 19) & 1, D_00621A30},
        {(f[1] >> 20) & 1, D_00621A40}, {(f[1] >> 21) & 1, D_00621A50},
        {(f[2] >> 4) & 1, D_00621A60},  {(f[2] >> 13) & 1, D_00621A70},
        {(f[2] >> 14) & 1, D_00621A80}, {(f[2] >> 24) & 1, D_00621A90},
        {(f[2] >> 25) & 1, D_00621AA0}, {(f[3] >> 1) & 1, D_00621AB0},
        {(f[3] >> 3) & 1, D_00621AC0},  {(f[3] >> 5) & 1, D_00621AD0},
        {(f[3] >> 6) & 1, D_00621AE0},  {(f[3] >> 7) & 1, D_00621AF0},
        {(f[3] >> 8) & 1, D_00621B00},  {-1},
    };
    int y = 40;
    int i;

    for (i = 0; tbl[i].on != -1; i++) {
        if (tbl[i].on) {
            if (D_0063B13C & 1) {
                debug_Printf(10, y += 8, 0x0FFFFFFF, D_0063BD40, tbl[i].name);
            }
        } else {
            if (D_0063B13C & 1) {
                debug_Printf(10, y += 8, 0x0FFFFFFF, D_0063BD48, tbl[i].name);
            }
        }
    }
}

inline void ACTSetEnvAllmighty(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 38);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 39);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 40);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 41);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 44);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 45);
    if (ACTGame_FLAG_TETSUNAGI()) {
        *(unsigned long long *)(s + 0x18) &= ~(1ULL << 43);
        *(int *)(s + 0x28) = 0;
    } else {
        if ((int)(*(unsigned long long *)(s + 0x18) >> 43) & 1)
            *(unsigned long long *)(s + 0x478) |= (1ULL << 46);
        *(int *)(s + 0x28) += 1;
    }
    *(unsigned long long *)(s + 0x478) |= (1ULL << 50);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 51);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 52);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 53);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 49);
    *(unsigned long long *)(s + 0x480) |= (1ULL << 43);
}

inline int CheckWallAttributeEdegWall(int a0)
{
    if (stage_no == 4) {
        return (unsigned char)CheckPureWallAttribute__pn(a0, 0x1000);
    }
    return (unsigned char)CheckWallAttribute__pn(a0, 0x1000);
}

INCLUDE_ASM("asm/nonmatchings/src/act-env", ACTGetEnvironment);
