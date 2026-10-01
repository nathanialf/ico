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

#include "typedef.h"

void actSt03tEneChk(GObj *volatile a0);
void actSt03tGirlCamEndChk(GObj *volatile a0);
void actSt03tGirlCamStartChk(GObj *volatile a0);
void actSt03tGirlPosChk(GObj *volatile a0);
void actSt03tGirlUpChk(GObj *volatile a0);
void actSt03tHint1OffChk(GObj *volatile a0);
void actSt03tHint1OnChk(GObj *volatile a0);
void actSt03tSwitchLChk(GObj *volatile a0);
void actSt03tSwitchLUpChk(GObj *volatile a0);
void actSt03tSwitchRChk(GObj *volatile a0);
void actSt03tSwitchRUpChk(GObj *volatile a0);
void actSt03tWayOffChk(GObj *volatile a0);
void actSt03tWayOnChk(GObj *volatile a0);

#endif /* ST03T_H */
