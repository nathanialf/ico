#include "common.h"


extern int func_0017B230(int a0);
extern void AddWayPointTop();
extern void stage_KillPlayBgAnimation();
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aInit);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoor);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoorUpChk);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoorDownChk);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02WaterFallBoySplashCheck);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWaterFallChk);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaUp);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaDown);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aBox);

void actSt02aGondola(void) {}

void actSt02aFence(int x) {
    volatile int local = x;
}

void actSt02aWaterFall(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aBoxEvent2);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aEne);

void actSt02aEnemy1(void)
{
    if (func_0017B230(0x69) == 0) {
        AddWayPointTop(0x1A, 0);
        stage_KillPlayBgAnimation(0x55, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x55, 0, -1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aEnemy2);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aSekizo);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWay);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aTakiWay);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aSecretItem);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoorEvent);

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoorUpEffect);

