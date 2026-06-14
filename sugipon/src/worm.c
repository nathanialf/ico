#include "common.h"

/* Worm 0x7F0 view (local) */
typedef struct { char _0[8]; float f_8; } WormGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", outerProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", simulate);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", getAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", disp);

extern void func_00240008(void *a0, void *a1);
extern void func_0023FE98(void *a0, void *a1);
extern void func_00240038(void *a0, void *a1, float a2);

void GetWormRoute(void *a0, char *a1, float f12) {
    func_00240008(a0, (void *)(*(int *)(a1 + 0x15C) + 0x50));
    func_0023FE98(a0, a0);
    func_00240038(a0, a0, f12);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", InitWormGeo);

extern void simulate(void);

void GetWormCaptureVector(void) {
    simulate();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/worm", WormGeo);

void WormDL(void *a0, float a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WormGeo *q = *(WormGeo **)((char *)p + 0x7F0);
    q->f_8 = a1;
}
