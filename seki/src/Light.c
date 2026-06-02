#include "common.h"
#include "vu0.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_killLinkLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_killLinkAmbient);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_AddLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_getNearLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_getAmbientLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_MakeLightMatrix);

extern float D_00629EC0;
extern float D_00629EC8;

void light_DispVolume(float a0, float a1) {
    D_00629EC0 = a0;
    D_00629EC8 = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_GetColorAnalog);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_DrawCursor);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_Tool);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_InitLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_KillAllFixLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_KillAllAmbient);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_AddAmbientObject);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", light_resetFlatLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00115CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00116308);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001163E8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001169D8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00116CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117038);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117B80);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117B90);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117BF0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117C48);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00117D78);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00118048);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00118068);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00118088);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001180A8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001180C0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001180D8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_001180F8);

void func_00118108(void) {
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_NOP();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Light", func_00118118);
