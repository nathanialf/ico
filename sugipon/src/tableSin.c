#include "common.h"
#include "vu0.h"

extern int D_00629E7C;
extern int D_0065A5B0[];

void *GetTableSin(void) {
    return &D_0065A5B0[D_00629E7C * 4];
}

extern char D_0054E1B0[];
extern char D_0054E1D8[];
extern void debug_assertMessage(char *p);
extern void SetIdentityQuaternion(void);

void GetTableCos(void)
{
    int v = D_00629E7C;
    if (v < 0) {
        debug_assertMessage(D_0054E1B0);
        SetIdentityQuaternion();
        v = D_00629E7C;
    }
    v++;
    D_00629E7C = v;
    if (v >= 0x40) {
        debug_assertMessage(D_0054E1D8);
        v = 0x3F;
        D_00629E7C = v;
    }
}

extern unsigned char D_0054E1F8[];

void InitTableSin(void) {
    if (--D_00629E7C < 0) {
        debug_assertMessage(D_0054E1F8);
        D_00629E7C = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", GetTableArcSin);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", GetTableArcCos);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", GetTableArcTan2);

extern void _SetCurrentMatrix(void *out, int *p);
extern float p2o_SetDefaultEnviroment(int x);
extern float _InverseCurrentMatrix(int *self, void *p, float arg);
extern float func_0010ED30(int x);

void func_0010E088(int *self, int a1, int *p)
{
    char buf[0x10];
    int half_pre = a1 << 16;
    int half;
    float f;
    _SetCurrentMatrix(buf, p);
    half = half_pre >> 17;
    f = p2o_SetDefaultEnviroment(half);
    _InverseCurrentMatrix(self, buf, f);
    *(float *)((char *)self + 0xC) = func_0010ED30(half);
}


void func_0010E0E8(int *self, int a1, int *param)
{
    int half = ((int)(short)a1) >> 1;
    float f = p2o_SetDefaultEnviroment(half);
    _InverseCurrentMatrix(self, param, f);
    *(float *)((char *)self + 0xC) = func_0010ED30(half);
}

void func_0010E148(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 11, 0x0, a1);
    VU0_LSV(lqc2, 12, 0x0, a2);
    VU0_V3OP(vmul.xyzw, 13, 11, 12);
    VU0_V3OP_BC(vaddy.x, 13, 13, 13, y);
    VU0_V3OP_BC(vaddz.x, 13, 13, 13, z);
    VU0_V3OP_BC(vsubx.w, 13, 13, 13, x);
    VU0_V3OP_BC(vmulw.xyz, 14, 12, 11, w);
    VU0_V3OP_BC(vmulw.xyz, 15, 11, 12, w);
    VU0_V3OP_ACC(vopmula.xyz, 12, 11);
    VU0_V3OP(vopmsub.xyz, 16, 11, 12);
    VU0_V3OP(vadd.xyz, 13, 14, 15);
    VU0_V3OP(vadd.xyz, 13, 13, 16);
    VU0_LSV(sqc2, 13, 0x0, a0);
    VU0_NOP();
}

extern void RegularizeQuaternion(void *a0, void *a1);

void func_0010E188(void *a0, void *a1, void *a2)
{
    char buf[0x10];
    RegularizeQuaternion(buf, a2);
    ((void (*)(void *, void *, void *))func_0010E148)(a0, buf, a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E250);

extern void getQuaternionFromMatrix(void *dst, void *src);
extern void *func_00105078(void);
extern void func_001189F8(void *a0, void *a1, void *a2);

void func_0010E300(void *a0)
{
    char buf[0x40];
    void *r1, *r2;
    getQuaternionFromMatrix(buf, a0);
    r1 = func_00105078();
    r2 = func_00105078();
    func_001189F8(r1, r2, buf);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E348);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E448);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E4E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E588);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E628);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054E220;  /* stride 0x4 */

/* end struct shapes */
