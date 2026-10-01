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

#include "typedef.h"

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order st08b.c's inline tail has. */
void actSt08bKuren(GObj *volatile a0);
void actSt08bEne(GObj *volatile a0);
void actSt08bEnemy1(GObj *volatile a0);
void actSt08bEnemy2(GObj *volatile a0);
void actSt08bKurenMain(GObj *volatile a0);
void actSt08aGirlYoro(GObj *volatile a0);
void actSt08bDoorEvent(int x);
void actSt08bDoorUpEffect(GObj *volatile a0);
void actSt08bDoorDownEffect(GObj *volatile a0);
void actSt08bEneChk(GObj *volatile a0);
void actSt08bKurenSwitch(GObj *volatile a0);

#endif /* ST08B_H */
