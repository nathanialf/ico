#include "common.h"




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

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_DispVU1Multi);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_DispVU1MultiDefault);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_DispVU1);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_DispVU1Default);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_TransMicroProgram);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", p2o_SetDefaultEnviroment);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010E9A0);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010E9F8);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010EAD0);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010EB60);

INCLUDE_ASM("asm/nonmatchings/src/DisplayP2O", func_0010EC08);

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

