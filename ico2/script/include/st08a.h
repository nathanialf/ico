/*
 * ico2/script/include/st08a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st08a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST08A_H
#define ST08A_H

extern void actSt08aDoorMain(volatile int a0);
extern void actSt08aDoorSwitch(volatile int a0);
extern void actSt08aDoorUp(volatile int a0);
extern void actSt08aDoorUpSub(volatile int a0);
extern void actSt08aEne1Chk(volatile int a0);
extern void actSt08aEne2Chk(volatile int a0);
extern void actSt08aGirlPosChk(volatile int a0);
extern void actSt08aHasiMain(volatile int a0);
extern void actSt08aHasiSwitch(volatile int a0);
extern void actSt08aHasiUp(volatile int a0);
extern void actSt08aHasiUpSub(volatile int a0);
extern void actSt08aHint1Chk(volatile int a0);
extern void actSt08aIntroChk(volatile int a0);
extern void actSt08aTorchOffChk(volatile int a0);
extern void actSt08aTorchOnChk(volatile int a0);

#endif /* ST08A_H */
