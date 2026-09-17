/*
 * ico2/script/include/st08b.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st08b.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST08B_H
#define ST08B_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order st08b.c's inline tail has. */
void actSt08bKuren(volatile int a0);
void actSt08bEne(volatile int a0);
void actSt08bEnemy1(volatile int a0);
void actSt08bEnemy2(volatile int a0);
void actSt08bKurenMain(volatile int a0);
void actSt08aGirlYoro(volatile int a0);
void actSt08bDoorEvent(int x);
void actSt08bDoorUpEffect(volatile int a0);
void actSt08bDoorDownEffect(volatile int a0);
void actSt08bEneChk(volatile int a0);

void actSt08bKurenSwitch(volatile int a0);

#endif /* ST08B_H */
