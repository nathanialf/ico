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
void actSt06aBallDeleteChk(GObj *volatile a0);
void actSt06aBox2Chk(GObj *volatile a0);
void actSt06aBox3Chk(GObj *volatile a0);
void actSt06aBoxChk(GObj *volatile a0);
void actSt06aBoxEvent2InChk(GObj *volatile a0);
void actSt06aBoxEvent2OutChk(GObj *volatile a0);
void actSt06aDoorDownChk(GObj *volatile a0);
void actSt06aDoorDownEffect(GObj *volatile a0);
void actSt06aDoorUpChk(GObj *volatile a0);
void actSt06aDoorUpEffect(GObj *volatile a0);
void actSt06aExitChk(GObj *volatile a0);
void actSt06aHeadChk(GObj *volatile a0);
void actSt06aShutterMain(GObj *volatile a0);
void actSt06aShutterOpen(GObj *volatile a0);
void actSt06aShutterSwitch(GObj *volatile a0);
void actSt06aStatueChk(GObj *volatile a0);
void actSt06aSuimonChk(GObj *volatile a0);
void actSt06aSuimonEffect(GObj *volatile a0);
void actSt06aSuimonFlagOn(GObj *volatile a0);
void actSt06aTreeChk(GObj *volatile a0);
void actSt06aWallWay2OffChk(GObj *volatile a0);
void actSt06aWallWay2OnChk(GObj *volatile a0);
void actSt06aWallWayOffChk(GObj *volatile a0);
void actSt06aWallWayOnChk(GObj *volatile a0);
void actSt06aWayOffChk(GObj *volatile a0);
void actSt06aWayOnChk(GObj *volatile a0);

#endif /* ST06A_H */
