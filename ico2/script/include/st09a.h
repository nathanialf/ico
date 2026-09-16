/*
 * ico2/script/include/st09a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st09a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST09A_H
#define ST09A_H

void actSt09aBrgDown(volatile int a0);
void actSt09aBrgDownSub(volatile int a0);
void actSt09aBrgMain(volatile int a0);
void actSt09aBrgSwitch(volatile int a0);
void actSt09aElvDown(volatile int a0);
void actSt09aElvMain(volatile int a0);
void actSt09aElvSwitch(volatile int a0);
void actSt09aElvUp(volatile int a0);
void actSt09aHint1Chk(volatile int a0);
void actSt09aHint2Chk(volatile int a0);
void actSt09aIntroChk(volatile int a0);

#endif /* ST09A_H */
