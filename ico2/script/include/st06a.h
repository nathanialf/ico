/*
 * ico2/script/include/st06a.h
 *
 * The declarations of what st06a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST06A_H
#define ST06A_H

#include "typedef.h"

/* st06a.o's .sdata globals */
extern char *suimon;
extern char *shutter;
extern char *toge;
void actSt06aBallDeleteChk(GObj *volatile self);
void actSt06aBox2Chk(GObj *volatile self);
void actSt06aBox3Chk(GObj *volatile self);
void actSt06aBoxChk(GObj *volatile self);
void actSt06aBoxEvent2InChk(GObj *volatile self);
void actSt06aBoxEvent2OutChk(GObj *volatile self);
void actSt06aDoorDownChk(GObj *volatile self);
void actSt06aDoorDownEffect(GObj *volatile self);
void actSt06aDoorUpChk(GObj *volatile self);
void actSt06aDoorUpEffect(GObj *volatile self);
void actSt06aExitChk(GObj *volatile self);
void actSt06aHeadChk(GObj *volatile self);
void actSt06aShutterMain(GObj *volatile self);
void actSt06aShutterOpen(GObj *volatile self);
void actSt06aShutterSwitch(GObj *volatile self);
void actSt06aStatueChk(GObj *volatile self);
void actSt06aSuimonChk(GObj *volatile self);
void actSt06aSuimonEffect(GObj *volatile self);
void actSt06aSuimonFlagOn(GObj *volatile self);
void actSt06aTreeChk(GObj *volatile self);
void actSt06aWallWay2OffChk(GObj *volatile self);
void actSt06aWallWay2OnChk(GObj *volatile self);
void actSt06aWallWayOffChk(GObj *volatile self);
void actSt06aWallWayOnChk(GObj *volatile self);
void actSt06aWayOffChk(GObj *volatile self);
void actSt06aWayOnChk(GObj *volatile self);

#endif /* ST06A_H */
