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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", p2o_TransMicroProgram);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", func_0010EFF8);


/* recovered struct shapes */
typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_0066A9D0;  /* stride 0x2 */

/* end struct shapes */
