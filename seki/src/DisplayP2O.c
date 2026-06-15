#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_MakePacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispShadowVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_HideDispVU1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispVU1DObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispVU1DObjMulti);

extern int func_00118048(float arg);

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
    return func_00118048(arg);
}

extern void _InverseCurrentMatrix(void *a0, void *a1, float a2);

void p2o_DispVU1MultiDefault(void *a0, void *a1, float angle) {
    float first, second;
    first = ((float (*)(float))func_00118048)((angle + 1.0f) * 0.5f);
    second = ((float (*)(float))func_00118048)((1.0f - angle) * 0.5f);
    _InverseCurrentMatrix(a0, a1, second);
    *(float *)((char *)a0 + 0xC) = first;
}

extern void _SetCurrentMatrix(void *buf);
extern void _InverseCurrentMatrix(void *a0, void *buf, float a2);

void p2o_DispVU1(void *a0, float angle) {
    float buf[4];
    float first, second;
    _SetCurrentMatrix(buf);
    first = ((float (*)(float))func_00118048)((angle + 1.0f) * 0.5f);
    second = ((float (*)(float))func_00118048)((1.0f - angle) * 0.5f);
    _InverseCurrentMatrix(a0, buf, second);
    *(float *)((char *)a0 + 0xC) = first;
}

extern void _SetCurrentMatrix(void *buf);

void p2o_DispVU1Default(void *a0, float *a1, void *a2) {
    float buf[4];
    float first, second;
    first = ((float (*)(float))func_00118048)((a1[0] + 1.0f) * 0.5f);
    second = ((float (*)(float))func_00118048)((1.0f - a1[0]) * 0.5f);
    ((void (*)(void *, void *))_SetCurrentMatrix)(buf, a2);
    *(float *)((char *)a0 + 0xC) = first;
    *(float *)((char *)a0 + 0x0) = buf[0] * second;
    *(float *)((char *)a0 + 0x4) = buf[1] * second;
    *(float *)((char *)a0 + 0x8) = buf[2] * second;
}

float p2o_TransMicroProgram(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0($4)\n"
        "lqc2 $vf15, 0x0($5)\n"
        "vmul.xyzw $vf15, $vf14, $vf15\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "qmfc2.ni $2, $vf15\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_SetDefaultEnviroment);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", func_0010ED30);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", func_0010ED88);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", func_0010EE60);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", func_0010EEF0);

extern int func_0010EEF0(float x);

int func_0010EF98(float f12, float f13)
{
    if (f12 < 0.0f) {
        int r = func_0010EEF0(f13);
        return (short)(-r);
    }
    return func_0010EEF0(f13);
}

extern void func_0011C308(void *a0);

void func_0010EFE0(void *a0) {
    void *p = *(void **)((char *)a0 + 0x810);
    *(void **)((char *)p + 0x28) = a0;
    func_0011C308(a0);
}

extern void func_00123AA8(void *a0);

void func_0010EFF0(int a0) {
    func_00123AA8(*(void **)(a0 + 0x15C));
}

extern int D_0062AFA8;
extern int D_00629E84;
extern char D_0054E240[];
extern void display(int a0, void *a1, int a2);

void func_0010EFF8(int a0) {
    D_00629E84 = a0;
    if (D_0062AFA8) {
        display(0xCCCCCC00, D_0054E240, a0);
    }
}


/* recovered struct shapes */
typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_0066A9D0;  /* stride 0x2 */

/* end struct shapes */
