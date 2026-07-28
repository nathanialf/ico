#include "common.h"



extern int D_006333EC;
extern int checkHit(char *self);
extern void WeaponGeo(int *self);
extern int D_00631AEC;
extern void iosPadDevRead();
int func_001D1440(int a0)
{
    iosPadDevRead(D_00631AEC, a0);
    return 1;
}

int func_001D1468(void)
{
    int *p;
    int *q;
    p = (int *)((int *)D_006333EC)[0x15C/4];
    q = (int *)p[0x630/4];
    if (q != 0) {
        if (checkHit(q) == 1) {
            int *r = (int *)((int *)D_006333EC)[0x15C/4];
            WeaponGeo((int *)r[0x630/4]);
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/girl", InitGirlGeo);

INCLUDE_ASM("asm/nonmatchings/src/girl", GirlGeo);

INCLUDE_ASM("asm/nonmatchings/src/girl", debugWireStringGirl);

INCLUDE_ASM("asm/nonmatchings/src/girl", GirlDL);

INCLUDE_ASM("asm/nonmatchings/src/girl", GirlAI);

extern int GirlAI(int a0);
extern void GirlGeo(int a0);
extern void func_0010ECB8(int a0);
extern void func_0010ECD8(int a0);

void SetGirlClothDispSwitch(int a0)
{
    func_0010ECD8(a0);
    func_0010ECB8(a0);
    GirlGeo(a0);
    return GirlAI(a0);
}

