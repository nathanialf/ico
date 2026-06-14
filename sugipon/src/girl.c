#include "common.h"

extern int iosPadDevRead(int a0, void *a1);
extern int D_00629DEC;

int func_001CE7D8(void *a0) {
    iosPadDevRead(D_00629DEC, a0);
    return 1;
}

extern int checkHit();
extern void WeaponGeo();
extern char *D_0062B6B0;

int func_001CE800(void) {
    char *p = *(char **)(D_0062B6B0 + 0x15C);
    int v = *(int *)(p + 0x620);
    if (v != 0 && checkHit(v) == 1) {
        char *q = *(char **)(D_0062B6B0 + 0x15C);
        WeaponGeo(*(int *)(q + 0x620));
    }
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", InitGirlGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", GirlGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", debugWireStringGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", GirlDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", GirlAI);

extern void func_0010F068(int a0);
extern void func_0010F048(int a0);
extern void GirlGeo(int a0);
extern int GirlAI(int a0);

void SetGirlClothDispSwitch(int a0)
{
    func_0010F068(a0);
    func_0010F048(a0);
    GirlGeo(a0);
    return GirlAI(a0);
}
