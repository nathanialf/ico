/*
 * ico2/script/include/st10l.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st10l.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST10L_H
#define ST10L_H

extern void actSt10lBoxAChk(volatile int a0);
extern void actSt10lBoxBChk(volatile int a0);
extern void actSt10lBoxChk(volatile int a0);
extern void actSt10lChainMain(volatile int a0);
extern void actSt10lChainMove(volatile int a0);
extern void actSt10lChainSwitch(volatile int a0);
extern void actSt10lEneCam1Chk(volatile int a0);
extern void actSt10lEneCam2Chk(volatile int a0);
extern void actSt10lEneCam3Chk(volatile int a0);
extern void actSt10lEneKillChk(volatile int a0);
extern void actSt10lFloorLeft(volatile int a0);
extern void actSt10lFloorMain(volatile int a0);
extern void actSt10lFloorRight(volatile int a0);
extern void actSt10lFloorSwitch(volatile int a0);
extern void actSt10lGondolaDown(volatile int a0);
extern void actSt10lGondolaMain(volatile int a0);
extern void actSt10lGondolaSwitch(volatile int a0);
extern void actSt10lGondolaUp(volatile int a0);

#endif /* ST10L_H */
