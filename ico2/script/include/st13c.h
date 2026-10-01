/*
 * ico2/script/include/st13c.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st13c.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST13C_H
#define ST13C_H

#include "typedef.h"

/* st13c.o's .sdata globals (MAIN.MAP) */
extern char *bmg;
extern char *hand;
void actSt13cBmg1Chk(GObj *volatile a0);
void actSt13cBukiChk(GObj *volatile a0);
void actSt13cCage1stDown(GObj *volatile a0);
void actSt13cCage1stDownDemo(GObj *volatile a0);
void actSt13cCage1stDownDemoCancel(GObj *volatile a0);
void actSt13cCageDownMain(GObj *volatile a0);
void actSt13cCageDownSwitch(GObj *volatile a0);
void actSt13cCageFallChk(GObj *volatile a0);
void actSt13cCageFallEffect(GObj *volatile a0);
void actSt13cCageFallReadyChk(GObj *volatile a0);
void actSt13cConte04(GObj *volatile a0);
void actSt13cConte04Jimaku(GObj *volatile a0);
void actSt13cConte05(GObj *volatile a0);
void actSt13cConte05Jimaku(GObj *volatile a0);
void actSt13cGirlCarryAgainChk(GObj *volatile a0);
void actSt13cGirlCarryChk(GObj *volatile a0);
void actSt13cHandChk(GObj *volatile a0);
void actSt13cHandJimaku(GObj *volatile a0);
void actSt13cHandSub(GObj *volatile a0);
void actSt13cRescueChk(GObj *volatile a0);
void actSt13cSekizoChk(GObj *volatile a0);
void actSt13cSekizoJimakuChk(GObj *volatile a0);
void actSt13cSekizoJimakuEff(GObj *volatile a0);
void actSt13cSleepChk(GObj *volatile a0);

#endif /* ST13C_H */
