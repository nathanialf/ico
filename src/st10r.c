#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rInit);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rEnd);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFloorChk);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rCageMain);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rTowerChk);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rTowerConte);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rChainMove);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFence);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFenceDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFenceUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFenceDownChk2);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFenceUpChk2);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFloor);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFloorHit);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rCage);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rTower);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rTowerResque);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rExit);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rChain);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rSekizo);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rEne);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rElv);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rGateXL);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rWay);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFloorSub);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rCageSub);
extern long long D_00622DF0[];
extern int D_00639EA8;
extern void _ACTWait();
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);

void actSt10rGirlWay(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622DF0[0];
    buf[1] = D_00622DF0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rExitChk);
INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00246330);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rChainMoveSub);
void actSt10rSekizoEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rWayOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rTowerResqueChk);
