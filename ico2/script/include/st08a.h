/*
 * ico2/script/include/st08a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st08a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST08A_H
#define ST08A_H

#include "typedef.h"

void actSt08aDoorMain(GObj *volatile a0);
void actSt08aDoorSwitch(GObj *volatile a0);
void actSt08aDoorUp(GObj *volatile a0);
void actSt08aDoorUpSub(GObj *volatile a0);
void actSt08aEne1Chk(GObj *volatile a0);
void actSt08aEne2Chk(GObj *volatile a0);
void actSt08aGirlPosChk(GObj *volatile a0);
void actSt08aHasiMain(GObj *volatile a0);
void actSt08aHasiSwitch(GObj *volatile a0);
void actSt08aHasiUp(GObj *volatile a0);
void actSt08aHasiUpSub(GObj *volatile a0);
void actSt08aHint1Chk(GObj *volatile a0);
void actSt08aIntroChk(GObj *volatile a0);
void actSt08aTorchOffChk(GObj *volatile a0);
void actSt08aTorchOnChk(GObj *volatile a0);

#endif /* ST08A_H */
