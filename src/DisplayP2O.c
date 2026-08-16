#include "common.h"





#include "vu0.h"
extern int D_00632CE0;
extern void display();
extern int D_00631B84;
extern char D_00553E90[];
#include "ico/types.h"
extern void func_00123C00();
extern void func_0011BF40();
INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_MakePacket);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_DispShadowVolume);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_HideDispVU1);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_DispVU1DObj);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_DispVU1DObjMulti);

extern int func_00117C20(float arg);

int p2o_DispVU1Multi(void *a0) {
    register float arg __asm__("$f12");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0($4)\n"
        "lqc2 $vf15, 0x0($4)\n"
        "vmul.xyzw $vf15, $vf14, $vf15\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "qmfc2.ni $2, $vf15\n"
        "mtc1 $2, $f12\n"
        ".set reorder\n"
        : "=f"(arg) :: "$2");
    return func_00117C20(arg);
}

extern void _InverseCurrentMatrix(void *a0, void *a1, float a2);

void p2o_DispVU1MultiDefault(void *a0, void *a1, float angle) {
    float first, second;
    first = ((float (*)(float))func_00117C20)((angle + 1.0f) * 0.5f);
    second = ((float (*)(float))func_00117C20)((1.0f - angle) * 0.5f);
    _InverseCurrentMatrix(a0, a1, second);
    *(float *)((char *)a0 + 0xC) = first;
}

extern void _SetCurrentMatrix(void *buf);

void p2o_DispVU1(void *a0, float angle) {
    float buf[4];
    float first, second;
    _SetCurrentMatrix(buf);
    first = ((float (*)(float))func_00117C20)((angle + 1.0f) * 0.5f);
    second = ((float (*)(float))func_00117C20)((1.0f - angle) * 0.5f);
    _InverseCurrentMatrix(a0, buf, second);
    *(float *)((char *)a0 + 0xC) = first;
}

void p2o_DispVU1Default(void *a0, float *a1, void *a2) {
    float buf[4];
    float first, second;
    first = ((float (*)(float))func_00117C20)((a1[0] + 1.0f) * 0.5f);
    second = ((float (*)(float))func_00117C20)((1.0f - a1[0]) * 0.5f);
    ((void (*)(void *, void *))_SetCurrentMatrix)(buf, a2);
    *(float *)((char *)a0 + 0xC) = first;
    *(float *)((char *)a0 + 0x0) = buf[0] * second;
    *(float *)((char *)a0 + 0x4) = buf[1] * second;
    *(float *)((char *)a0 + 0x8) = buf[2] * second;
}

void p2o_TransMicroProgram(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 14, 0x0, a0);
    VU0_LSV(lqc2, 15, 0x0, a1);
    VU0_V3OP(vmul.xyzw, 15, 14, 15);
    VU0_V3OP_BC(vaddy.x, 15, 15, 15, y);
    VU0_V3OP_BC(vaddz.x, 15, 15, 15, z);
    VU0_V3OP_BC(vaddw.x, 15, 15, 15, w);
    VU0_QMFC2_NI(v0, 15);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}

extern float D_00660E40[];

float p2o_SetDefaultEnviroment(short a0) {
    int idx = __builtin_abs(a0);
    int s;
    float v;
    s = (unsigned int) a0 >> 0x1F;
    if (idx >= 0x4000) {
        idx = 0x8000 - idx;
    }
    v = D_00660E40[idx];
    if (s == 0) goto done;
    v = -v;
done:
    return v;
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010E9A0);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010E9F8);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010EAD0);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010EB60);

extern short func_0010EB60(float c);

short func_0010EC08(float s, float c)
{
    if (s < 0.0f) {
        return -func_0010EB60(c);
    }
    return func_0010EB60(c);
}

void func_0010EC50(int a0)
{
    *(int *)(*(int *)(a0 + 0x820) + 0x28) = a0;
    func_0011BF40(a0);
}

void func_0010EC60(int a0)
{
    func_00123C00((int)((GObj *)(a0))->p_15C);
}

void func_0010EC68(int a0)
{
    D_00631B84 = a0;
    if (D_00632CE0 != 0) {
        display(0xCCCCCC00, D_00553E90, a0);
    }
}

