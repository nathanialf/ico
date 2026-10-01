/*
 * ico2/script/include/st18a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st18a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST18A_H
#define ST18A_H

#include "typedef.h"

void actSt18aDoorChk(GObj *volatile a0);
void actSt18aDoorChkSub(GObj *volatile a0);
void actSt18aDoorDownChk(GObj *volatile a0);
void actSt18aEne2Chk(GObj *volatile a0);
void actSt18aEneChk(GObj *volatile a0);
void actSt18aIntroChk(GObj *volatile a0);
void actSt18aSwitchLChk(GObj *volatile a0);
void actSt18aSwitchLUpChk(GObj *volatile a0);
void actSt18aSwitchRChk(GObj *volatile a0);
void actSt18aSwitchRUpChk(GObj *volatile a0);

#endif /* ST18A_H */
