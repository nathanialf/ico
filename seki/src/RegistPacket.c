#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_setShape);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_dispBoxLine);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_clipPacketBoundingBox);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_transMicroCode);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_chooseMicroCode);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_chooseSpecularMicroCode);

extern int pac_makeClusterStrip(int a0);

void reg_chooseReflectionMicroCode(char *a0) {
    if (*(signed char *)(*(char **)(a0 + 0x810) + 0x2F) != 0) {
        pac_makeClusterStrip(3);
        return;
    }
    if (*(int *)(*(char **)(a0 + 0x834) + 0xF0) == 0) {
        pac_makeClusterStrip(1);
        return;
    }
    pac_makeClusterStrip(2);
}

void func_0011F1C8(void *a0, int a1, int a2) {
    long long v = *(long long *)((char *)a0 + 0x60);
    pac_getWeight(*(int *)((char *)a0 + 0x60) & 1, (int)(v >> 5) & 3, 0, a1, a2);
}

extern void pac_getWeight(int a0, int a1, int a2, int a3, int a4);

void func_0011F1F0(int a0, int a1, int a2) {
    pac_getWeight(a0, 1, 1, a1, a2);
}

void reg_setNMatrixPacket(int a0, int a1, int a2) {
    pac_getWeight(a0, 1, 2, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_setMMatrixPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_setCMatrixPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_transMaterialPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_setDissolve);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_resetDissolve);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_dispNObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_dispMObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_dispSObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_dispCObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_dispPoint);

extern void dpk_SwapBuffer(void);
extern void dpk_Init(int a0, void *a1, int a2);
extern int dl_GetPri(void);
extern char D_0054FBE0[];

/* CRUTCH (zero-byte asm) — ACCEPTED EXCEPTION FOR NOW, pending a clean shape.
 * The $5/$6 pins + barrier force p and n to load before the call so the a0=2
 * li lands last (jal delay), the one arg order this binary never emits for
 * all-const args from clean C. Two 30-stall fires + permuter shots found no
 * clean shape (tough_nuts/reg_dispLine/). This crutch is knowingly retained
 * as a temporary exception until a suitable clean-C solution is found; it is
 * a standing candidate for the crutch-strip workstream. */
void reg_dispLine(void) {
    register void *p __asm__("$5");
    register int n __asm__("$6");
    dpk_SwapBuffer();
    p = D_0054FBE0;
    n = 4;
    __asm__ volatile("" : : "r"(p), "r"(n));
    dpk_Init(2, p, n);
    dl_GetPri();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_dispPointLineObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_setNMatrixPacketNoLightCalc);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_DispAccessoryWithShadow);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_RenderReflection);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_setEMatrixPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/RegistPacket", reg_DispEnemy);
