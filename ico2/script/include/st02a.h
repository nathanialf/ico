/*
 * ico2/script/include/st02a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st02a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST02A_H
#define ST02A_H

extern void actSt02aDoorDownChk(volatile int a0);
extern void actSt02aDoorDownEffect(volatile int a0);
extern void actSt02aDoorUpChk(volatile int a0);
extern void actSt02aDoorUpEffect(volatile int a0);
extern void actSt02aEneChk(volatile int a0);
extern void actSt02aFenceMain(volatile int a0);
extern void actSt02aFenceOpen(volatile int a0);
extern void actSt02aFenceOpenSub(volatile int a0);
extern void actSt02aGondolaDown(volatile int a0);
extern void actSt02aGondolaMain(volatile int a0);
extern void actSt02aGondolaUp(volatile int a0);
extern void actSt02aSecretItemChk(volatile int a0);
extern void actSt02aTakiWayOffChk(volatile int a0);
extern void actSt02aTakiWayOnChk(volatile int a0);
extern void actSt02aWaterFallChk(volatile int a0);
extern void actSt02aWaterFallReflactionEffect(volatile int a0);
extern void actSt02aWayOffChk(volatile int a0);
extern void actSt02aWayOnChk(volatile int a0);

#endif /* ST02A_H */
