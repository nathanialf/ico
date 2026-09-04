#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_InitFan2D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_SetFan2D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispFan2D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_makePacketMesh3D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_InitMesh3D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_makeNormal);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_UpdateMesh3D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", setMatrix);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", setLight);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", clearUVOffset);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispMesh3D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_InitParticleByPartition);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispParticle);
extern void EntryDelayFree(int a0);

void prim_DeleteParticle(int a0)
{
    EntryDelayFree(*(int *)(a0 + 0x18C));
    EntryDelayFree(*(int *)(a0 + 0x188));
    EntryDelayFree(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/Primitive", drawDisc);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispWireYCylinder);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispWireSphere);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispWireBox);
extern int D_0063A450;
extern int prim_InitParticleByPartition();

int prim_InitParticle(int a0, int a1, int a2, int a3)
{
    return prim_InitParticleByPartition(a0, a1, a2, a3, D_0063A450);
}
