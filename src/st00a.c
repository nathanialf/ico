#include "common.h"


extern int func_0017B230(int a0);
extern void func_0017B258(int bit_idx);
extern void *D_00631AE8;
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aInit);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnd);

INCLUDE_ASM("asm/nonmatchings/src/st00a", func_0020D850);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aStairChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2UpChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2DownChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1UpChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1DownChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEne);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnemy1);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnemy2);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aStair);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aAtr2);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aAtr2Chk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2Event);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2UpEffect);

void actSt00aDoor2DownEffect(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x27) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1Event);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1UpEffect);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1DownEffect);

