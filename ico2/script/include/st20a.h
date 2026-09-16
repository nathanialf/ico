/*
 * ico2/script/include/st20a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st20a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST20A_H
#define ST20A_H

extern void actSt20aBridgeDown(volatile int a0);
extern void actSt20aBridgeDownSub(volatile int a0);
extern void actSt20aBridgeMain(volatile int a0);
extern void actSt20aBridgeSwitch(volatile int a0);
extern void actSt20aEneChk(volatile int a0);
extern void actSt20aExitChk(volatile int a0);
extern void actSt20aFenceDownChk(volatile int a0);
extern void actSt20aFenceDownChk2(volatile int a0);
extern void actSt20aFenceUpChk(volatile int a0);
extern void actSt20aFenceUpChk2(volatile int a0);
extern void actSt20aGirlPosChk(volatile int a0);
extern void actSt20aGondolaDown(volatile int a0);
extern void actSt20aGondolaMain(volatile int a0);
extern void actSt20aGondolaSwitch(volatile int a0);
extern void actSt20aGondolaUp(volatile int a0);
extern void actSt20aHint1Chk(volatile int a0);

#endif /* ST20A_H */
