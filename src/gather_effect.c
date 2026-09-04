#include "common.h"

#include "ico/types.h"
struct GEl { int f0; char _4[0x6C]; };
struct GGeo { char _0[0x24]; struct GEl *f24; char _28[8]; int f30; };

INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_SetGoal);

INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_Proc);

extern void *InitParticleLayoutGeo(void *a0);

int GatherEffect_Set(int a0) {
    int acc = 0;
    if (a0 >= 0) {
        struct GGeo *geo = (struct GGeo *)InitParticleLayoutGeo((void *)a0);
        if (geo == 0) {
            return 1;
        }
        {
            int n = geo->f30;
            int i;
            for (i = 0; i < n; i++) {
                acc |= geo->f24[i].f0;
            }
        }
    }
    return acc == 0;
}

extern char D_006D35F0[];
extern void GetInverseQuaternion(int a0, int a1);
extern void pbga_start(int *a0, int a1);
extern void *isysGObjSearchFromObjLayoutID(int id);
extern void mc_TransMicroCode(int a0, int a1);
extern void ExecuteSEPackage(int a0, int a1);

void GatherEffect_InqEnd(void *self) {
    void *o = isysGObjSearchFromObjLayoutID(0x40);
    if (o != 0) {
        void *g = InitParticleLayoutGeo(self);
        int index = *(int *)((char *)g + 0x60);
        char *entry = D_006D35F0 + index * 0x40;
        pbga_start((int *)entry, 0x1E1);
        mc_TransMicroCode(*(int *)entry + 0x20, (int)(entry + 0x20));
        GetInverseQuaternion(*(int *)entry + 0x30, (int)(entry + 0x10));
        entry[4] = 2;
        ExecuteSEPackage(0, 0x60);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/gather_effect", func_001978B0);

INCLUDE_ASM("asm/nonmatchings/src/gather_effect", func_00197A38);

INCLUDE_ASM("asm/nonmatchings/src/gather_effect", func_00197B30);

extern signed char D_006D35E0[];
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);

void func_00197FC8(void) {
    if (D_006D35E0[0] == 0) goto dispon;
    scpActivateAllWithKind();
    return;
dispon:
    scpDispOnAllWithKind();
}

