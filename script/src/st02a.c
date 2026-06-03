#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoorUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoorDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02WaterFallBoySplashCheck);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aWaterFallChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aGondolaUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aGondolaDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aBox);

void actSt02aGondola(void) {
}

void actSt02aFence(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt02aWaterFall(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aBoxEvent2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aWay);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aTakiWay);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aSecretItem);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoorEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoorUpEffect);


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_006145D0;

/* end struct shapes */
