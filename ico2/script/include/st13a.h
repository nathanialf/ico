/*
 * ico2/script/include/st13a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st13a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST13A_H
#define ST13A_H

extern void actSt13aChainNG(volatile int a0);
extern void actSt13aChainOK(volatile int a0);
extern void actSt13aCheckChk(volatile int a0);
extern void actSt13aElevMain(volatile int a0);
extern void actSt13aElevSwitch(volatile int a0);
extern void actSt13aElevUp(volatile int a0);
extern void actSt13aSekizoChk(volatile int a0);

#endif /* ST13A_H */
