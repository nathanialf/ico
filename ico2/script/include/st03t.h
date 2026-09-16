/*
 * ico2/script/include/st03t.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st03t.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST03T_H
#define ST03T_H

void actSt03tEneChk(volatile int a0);
void actSt03tGirlCamEndChk(volatile int a0);
void actSt03tGirlCamStartChk(volatile int a0);
void actSt03tGirlPosChk(volatile int a0);
void actSt03tGirlUpChk(volatile int a0);
void actSt03tHint1OffChk(volatile int a0);
void actSt03tHint1OnChk(volatile int a0);
void actSt03tSwitchLChk(volatile int a0);
void actSt03tSwitchLUpChk(volatile int a0);
void actSt03tSwitchRChk(volatile int a0);
void actSt03tSwitchRUpChk(volatile int a0);
void actSt03tWayOffChk(volatile int a0);
void actSt03tWayOnChk(volatile int a0);

#endif /* ST03T_H */
