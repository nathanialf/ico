/*
 * ico2/script/include/st10r.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st10r.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST10R_H
#define ST10R_H

extern void actSt10rCageMain(volatile int a0);
extern void actSt10rCageSub(volatile int a0);
extern void actSt10rChainMain(volatile int a0);
extern void actSt10rChainMove(volatile int a0);
extern void actSt10rChainMoveSub(volatile int a0);
extern void actSt10rChainSwitch(volatile int a0);
extern void actSt10rEneChk(volatile int a0);
extern void actSt10rExitChk(volatile int a0);
extern void actSt10rFenceDownChk(volatile int a0);
extern void actSt10rFenceDownChk2(volatile int a0);
extern void actSt10rFenceUpChk(volatile int a0);
extern void actSt10rFenceUpChk2(volatile int a0);
extern void actSt10rFloorChk(volatile int a0);
extern void actSt10rFloorHitChk(volatile int a0);
extern void actSt10rFloorSub(volatile int a0);
extern void actSt10rGirlWay(volatile unsigned int a0);
extern void actSt10rTowerChk(volatile int a0);
extern void actSt10rTowerConte(volatile int a0);
extern void actSt10rTowerResqueChk(volatile int a0);
extern void actSt10rWayOffChk(volatile int a0);
extern void actSt10rWayOnChk(volatile int a0);

#endif /* ST10R_H */
