#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_MakePacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispShadowVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_HideDispVU1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispVU1DObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispVU1DObjMulti);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispVU1Multi);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispVU1MultiDefault);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispVU1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_DispVU1Default);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", func_0010EF98);

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
