/*
 * ico2/script/include/st13c.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st13c.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST13C_H
#define ST13C_H

extern void actSt13cBmg1Chk(volatile int a0);
extern void actSt13cBukiChk(volatile int a0);
extern void actSt13cCage1stDown(volatile int a0);
extern void actSt13cCage1stDownDemo(volatile int a0);
extern void actSt13cCage1stDownDemoCancel(volatile int a0);
extern void actSt13cCageDownMain(volatile int a0);
extern void actSt13cCageDownSwitch(volatile int a0);
extern void actSt13cCageFallChk(volatile int a0);
extern void actSt13cCageFallEffect(volatile int a0);
extern void actSt13cCageFallReadyChk(volatile int a0);
extern void actSt13cConte04(volatile int a0);
extern void actSt13cConte04Jimaku(volatile int a0);
extern void actSt13cConte05(volatile int a0);
extern void actSt13cConte05Jimaku(volatile int a0);
extern void actSt13cGirlCarryAgainChk(volatile int a0);
extern void actSt13cGirlCarryChk(volatile int a0);
extern void actSt13cHandChk(volatile int a0);
extern void actSt13cHandJimaku(volatile int a0);
extern void actSt13cHandSub(volatile int a0);
extern void actSt13cRescueChk(volatile int a0);
extern void actSt13cSekizoChk(volatile int a0);
extern void actSt13cSekizoJimakuChk(volatile int a0);
extern void actSt13cSekizoJimakuEff(volatile int a0);
extern void actSt13cSleepChk(volatile int a0);

#endif /* ST13C_H */
