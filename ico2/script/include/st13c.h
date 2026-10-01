/*
 * ico2/script/include/st13c.h
 *
 * The declarations of what st13c.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST13C_H
#define ST13C_H

#include "typedef.h"

struct SqEntry;

/* st13c.o's .sdata globals */
extern struct SqEntry *bmg;
extern struct SqEntry *hand;
void actSt13cBmg1Chk(GObj *volatile self);
void actSt13cBukiChk(GObj *volatile self);
void actSt13cCage1stDown(GObj *volatile self);
void actSt13cCage1stDownDemo(GObj *volatile self);
void actSt13cCage1stDownDemoCancel(GObj *volatile self);
void actSt13cCageDownMain(GObj *volatile self);
void actSt13cCageDownSwitch(GObj *volatile self);
void actSt13cCageFallChk(GObj *volatile self);
void actSt13cCageFallEffect(GObj *volatile self);
void actSt13cCageFallReadyChk(GObj *volatile self);
void actSt13cConte04(GObj *volatile self);
void actSt13cConte04Jimaku(GObj *volatile self);
void actSt13cConte05(GObj *volatile self);
void actSt13cConte05Jimaku(GObj *volatile self);
void actSt13cGirlCarryAgainChk(GObj *volatile self);
void actSt13cGirlCarryChk(GObj *volatile self);
void actSt13cHandChk(GObj *volatile self);
void actSt13cHandJimaku(GObj *volatile self);
void actSt13cRescueChk(GObj *volatile self);
void actSt13cSekizoJimakuChk(GObj *volatile self);
void actSt13cSekizoJimakuEff(GObj *volatile self);
void actSt13cSleepChk(GObj *volatile self);

#endif /* ST13C_H */
