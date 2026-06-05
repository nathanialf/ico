#include "common.h"

extern int D_0062BF50;

void prim_InitFan2D(void) {
    D_0062BF50 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_SetFan2D);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_DispFan2D);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_makePacketMesh3D);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_InitMesh3D);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_makeNormal);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_UpdateMesh3D);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", setMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", setLight);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", clearUVOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_DispMesh3D);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_InitParticle);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_DispParticle);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_DeleteParticle);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", drawDisc);

extern void func_00102528(void *a0);

void prim_DispWireYCylinder(void *a0) {
    func_00102528(*(void **)((char *)a0 + 0x18C));
    func_00102528(*(void **)((char *)a0 + 0x188));
    func_00102528(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Primitive", prim_DispWireSphere);
