#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aInit);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aEnd);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanEffect);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aTsuroChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aTsuroEffect);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aSekizoChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aEne);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aGene1);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChan);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanReady);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanChain);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aTsuro);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aIntro);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aSekizo);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aGene2);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aGene3);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aEne2);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aGene2_1);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aGene2_2);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aGene2_3);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanReadyChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanChainChk);
void actSt07ChanEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanFall);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanMot);
extern long long D_00622C70[];
extern int D_00639EA8;
extern void _ACTWait();
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);

void actSt07aChanWay1(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C70[0];
    buf[1] = D_00622C70[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}
extern long long D_00622C80[];

void actSt07aChanWay2(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C80[0];
    buf[1] = D_00622C80[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}
void actSt07TsuroEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aTsuroConte);
extern long long D_00622C90[];

void actSt07aGirlWay(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C90[0];
    buf[1] = D_00622C90[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}
void actSt07aCamera2(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aIntroChk);
void actSt07aSekizoEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aEne2Chk);
