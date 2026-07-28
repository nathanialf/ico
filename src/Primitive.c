#include "common.h"



extern void func_00102558(int a0);
extern int D_00633C50;
void prim_InitFan2D(void) {
    D_00633C50 = 0;
}

extern void pac_setVifEndCode(void *p, void *a2);

void prim_SetFan2D(int idx, int n, void *a2) {
    char *p = (char *)0x1100C000 + (idx << 4);
    int i;
    for (i = 0; i < n; i++) {
        char *q = p;
        p += 0x10;
        pac_setVifEndCode(q, a2);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispFan2D);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_makePacketMesh3D);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_InitMesh3D);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_makeNormal);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_UpdateMesh3D);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", setMatrix);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", setLight);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", clearUVOffset);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispMesh3D);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_InitParticle);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispParticle);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DeleteParticle);

INCLUDE_ASM("asm/nonmatchings/src/Primitive", drawDisc);

void prim_DispWireYCylinder(int a0)
{
    func_00102558(*(int *)(a0 + 0x18C));
    func_00102558(*(int *)(a0 + 0x188));
    func_00102558(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispWireSphere);

