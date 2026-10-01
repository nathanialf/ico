/*
 * ico2/script/include/st13c.h
 *
 * The declarations of what st13c.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST13C_H
#define ST13C_H

#include "typedef.h"

/* st13c.o's .sdata globals */
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
void actSt13cRescueChk(GObj *volatile a0);
void actSt13cSekizoJimakuChk(GObj *volatile a0);
void actSt13cSekizoJimakuEff(GObj *volatile a0);
void actSt13cSleepChk(GObj *volatile a0);

#endif /* ST13C_H */
