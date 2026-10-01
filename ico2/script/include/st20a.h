/*
 * ico2/script/include/st20a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st20a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST20A_H
#define ST20A_H

#include "typedef.h"

/* st20a.o's .sdata globals (MAIN.MAP) */
extern char *brg20a;
extern char *gondola_up;
extern char *gondola_down;
extern unsigned int st20a_yure;
extern unsigned char st20a_yure_vol;
void actSt20aBridgeDown(GObj *volatile a0);
void actSt20aBridgeDownSub(GObj *volatile a0);
void actSt20aBridgeMain(GObj *volatile a0);
void actSt20aBridgeSwitch(GObj *volatile a0);
void actSt20aEneChk(GObj *volatile a0);
void actSt20aExitChk(GObj *volatile a0);
void actSt20aFenceDownChk(GObj *volatile a0);
void actSt20aFenceDownChk2(GObj *volatile a0);
void actSt20aFenceUpChk(GObj *volatile a0);
void actSt20aFenceUpChk2(GObj *volatile a0);
void actSt20aGirlPosChk(GObj *volatile a0);
void actSt20aGondolaDown(GObj *volatile a0);
void actSt20aGondolaMain(GObj *volatile a0);
void actSt20aGondolaSwitch(GObj *volatile a0);
void actSt20aGondolaUp(GObj *volatile a0);
void actSt20aHint1Chk(GObj *volatile a0);

#endif /* ST20A_H */
