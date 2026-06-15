#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoorUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoorDownChk);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
void actSt02WaterFallBoySplashCheck(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x73); Generator_Call(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
void actSt02aWaterFallChk(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x7D); Generator_Call(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
void actSt02aGondolaUp(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x6E); Generator_Call(a0);
}

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

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt02aEnemy1(void) {
    if (func_00178DB0(0x69) == 0) {
        AddWayPointTop(0x1A, 0);
        stage_KillPlayBgAnimation(0x54, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x54, 0, -1);
    }
}

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
