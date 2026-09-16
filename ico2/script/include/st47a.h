/*
 * ico2/script/include/st47a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st47a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST47A_H
#define ST47A_H

extern void actSt47aBarricadeChk(volatile int a0);
extern void actSt47aEneChk(volatile int a0);
extern void actSt47aExit2Chk(volatile int a0);
extern void actSt47aExitChk(volatile int a0);
extern void actSt47aGirlWay(volatile int a0);
extern void actSt47aHane1Down(volatile int a0);
extern void actSt47aHane1Main(volatile int a0);
extern void actSt47aHane1Switch(volatile int a0);
extern void actSt47aHane1Up(volatile int a0);
extern void actSt47aHane1_1Girl(volatile int a0);
extern void actSt47aHane1_2Girl(volatile int a0);
extern void actSt47aHane2Down(volatile int a0);
extern void actSt47aHane2Girl(volatile int a0);
extern void actSt47aHane2Main(volatile int a0);
extern void actSt47aHane2Switch(volatile int a0);
extern void actSt47aHane2Up(volatile int a0);
extern void actSt47aHint2OnChk(volatile int a0);
extern void actSt47aRopeChk(volatile int a0);
extern void actSt47aRopeSub(volatile int a0);
extern void actSt47aSekizo1Chk(volatile int a0);

#endif /* ST47A_H */
