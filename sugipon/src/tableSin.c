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

extern float p2o_SetDefaultEnviroment(int x);
extern float _InverseCurrentMatrix(int *self, void *p, float arg);
extern float func_0010ED30(int x);

void GetTableArcCos(int *self, int a1, float x, float y, float z) {
    char buf[0x10];
    int half = (a1 << 16) >> 17;
    float f;
    *(float *)(buf + 0) = x;
    *(float *)(buf + 4) = y;
    *(float *)(buf + 8) = z;
    *(int *)(buf + 0xC) = 0;
    f = p2o_SetDefaultEnviroment(half);
    _InverseCurrentMatrix(self, buf, f);
    *(float *)((char *)self + 0xC) = func_0010ED30(half);
}

extern float func_00118048(float t);
extern void _SetCurrentMatrix(void *out, int *p);

void GetTableArcTan2(float *out, float *in, float x, float y, float z) {
    float v[4];
    float r[4];
    float s1, s2;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
    s1 = func_00118048((in[0] + 1.0f) * 0.5f);
    s2 = func_00118048((1.0f - in[0]) * 0.5f);
    _SetCurrentMatrix(r, (int *)v);
    out[0] = r[0] * s2;
    out[1] = r[1] * s2;
    out[2] = r[2] * s2;
    out[3] = s1;
}

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

extern char D_002724C0[];

void func_0010E1D0(void *a0, void *a1)
{
    __asm__ __volatile__(
        "lqc2 $vf11, 0x0($5)\n"
        "lqc2 $vf12, 0x0(%0)\n"
        "vmr32.w $vf14, $vf0\n"
        "vmr32.w $vf15, $vf0\n"
        "vmr32.w $vf16, $vf0\n"
        "vopmula.xyz $ACC, $vf11, $vf12\n"
        "vmadd.xyz $vf11, $vf0, $vf0\n"
        "vmulw.xyzw $vf11, $vf11, $vf12w\n"
        "vmul.xyz $vf13, $vf11, $vf11\n"
        "vopmula.xyz $ACC, $vf11, $vf11\n"
        "vmaddw.xyz $vf15, $vf11, $vf11w\n"
        "vmsubw.xyz $vf16, $vf11, $vf11w\n"
        "vopmula.xyz $ACC, $vf13, $vf12\n"
        "vmadd.xyz $vf17, $vf13, $vf12\n"
        "vopmula.xyz $ACC, $vf15, $vf12\n"
        "vmadd.xyz $vf15, $vf0, $vf0\n"
        "vsub.xyz $vf14, $vf12, $vf17\n"
        "vmove.y $vf17, $vf14\n"
        "vmove.y $vf14, $vf16\n"
        "vmove.y $vf16, $vf15\n"
        "vmove.y $vf15, $vf17\n"
        "vmove.z $vf17, $vf14\n"
        "vmove.z $vf14, $vf15\n"
        "vmove.z $vf15, $vf16\n"
        "vmove.z $vf16, $vf17\n"
        "sqc2 $vf14, 0x0($4)\n"
        "sqc2 $vf15, 0x10($4)\n"
        "sqc2 $vf16, 0x20($4)\n"
        : : "r"(D_002724C0) : "memory");
    VU0_NOP();
}

extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);

void func_0010E250(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(
        "lqc2 $vf11, 0x0(%2)\n"
        "lqc2 $vf12, 0x0(%1)\n"
        "vmr32.w $vf14, $vf0\n"
        "vmr32.w $vf15, $vf0\n"
        "vmr32.w $vf16, $vf0\n"
        "vopmula.xyz $ACC, $vf11, $vf12\n"
        "vmadd.xyz $vf11, $vf0, $vf0\n"
        "vmulw.xyzw $vf11, $vf11, $vf12w\n"
        "vmul.xyz $vf13, $vf11, $vf11\n"
        "vopmula.xyz $ACC, $vf11, $vf11\n"
        "vmaddw.xyz $vf15, $vf11, $vf11w\n"
        "vmsubw.xyz $vf16, $vf11, $vf11w\n"
        "vopmula.xyz $ACC, $vf13, $vf12\n"
        "vmadd.xyz $vf17, $vf13, $vf12\n"
        "vopmula.xyz $ACC, $vf15, $vf12\n"
        "vmadd.xyz $vf15, $vf0, $vf0\n"
        "vsub.xyz $vf14, $vf12, $vf17\n"
        "vmove.y $vf17, $vf14\n"
        "vmove.y $vf14, $vf16\n"
        "vmove.y $vf16, $vf15\n"
        "vmove.y $vf15, $vf17\n"
        "vmove.z $vf17, $vf14\n"
        "vmove.z $vf14, $vf15\n"
        "vmove.z $vf15, $vf16\n"
        "vmove.z $vf16, $vf17\n"
        "sqc2 $vf14, 0x0(%0)\n"
        "sqc2 $vf15, 0x10(%0)\n"
        "sqc2 $vf16, 0x20(%0)\n"
        : : "r"(a0), "r"(D_002724C0), "r"(a1) : "memory");
    MatrixDrive_TurnObjectMatrix((char *)a0 + 0x30, a2);
    *(float *)((char *)a0 + 0x3C) = 1.0f;
}

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
