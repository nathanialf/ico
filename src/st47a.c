#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aInit);
extern int D_00639EA8;
void actSt47aEnd(void) {
    if (D_00639EA8 != 0) {
        if (gflagChk(0x34) == 0) {
            gflagOn(0x187);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo1Chk);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1Down);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1Up);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2Down);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2Up);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aRope);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aRopeChk);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aBarricadeChk);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aTorch);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo1);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo2);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aBarricade);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aExit);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aExit2);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEne);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEnemy3);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEnemy4);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHint2On);
void actSt47aSekizo1Event(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aGirlWay);
void actSt47aSekizo2Event(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1Main);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1Switch);
extern long long D_006230C0[];
extern int D_00639EA8;
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);

void actSt47aHane1_1Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = D_006230C0[0];
    buf[1] = D_006230C0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}
extern long long D_006230D0[];

void actSt47aHane1_2Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = D_006230D0[0];
    buf[1] = D_006230D0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2Main);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2Switch);
extern long long D_006230E0[];

void actSt47aHane2Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = D_006230E0[0];
    buf[1] = D_006230E0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aRopeSub);
void actSt47aBarricadeEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aExitChk);
void actSt47aExit2Chk(volatile int a0) {
    *(int *)(scpSearchGobj(0x1E0) + 0x16C) = 1;
    *(int *)(scpSearchGobj(0x1E1) + 0x16C) = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHint2OnChk);
