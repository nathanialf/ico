/*
 * ico2/script/include/st06a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st06a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST06A_H
#define ST06A_H

#include "typedef.h"

/* st06a.o's .sdata globals (MAIN.MAP) */
extern char *suimon;
extern char *shutter;
extern char *toge;
void actSt06aBallDeleteChk(GObj *volatile a0);
void actSt06aBox2Chk(GObj *volatile a0);
void actSt06aBox3Chk(GObj *volatile a0);
void actSt06aBoxChk(GObj *volatile a0);
void actSt06aBoxEvent2InChk(GObj *volatile a0);
void actSt06aBoxEvent2OutChk(GObj *volatile a0);
void actSt06aBoxSub(GObj *volatile a0);
void actSt06aDoorDownChk(GObj *volatile a0);
void actSt06aDoorDownEffect(GObj *volatile a0);
void actSt06aDoorUpChk(GObj *volatile a0);
void actSt06aDoorUpEffect(GObj *volatile a0);
void actSt06aExitChk(GObj *volatile a0);
void actSt06aExitGirlChk(GObj *volatile a0);
void actSt06aHeadChk(GObj *volatile a0);
void actSt06aJumpMain(GObj *volatile a0);
void actSt06aJumpMove(GObj *volatile a0);
void actSt06aJumpSub(GObj *volatile a0);
void actSt06aJumpSwitch(GObj *volatile a0);
void actSt06aKyomiOffChk(GObj *volatile a0);
void actSt06aKyomiOnChk(GObj *volatile a0);
void actSt06aPistonFlagOnChk(GObj *volatile a0);
void actSt06aPistonRideOnChk(GObj *volatile a0);
void actSt06aShutterMain(GObj *volatile a0);
void actSt06aShutterOpen(GObj *volatile a0);
void actSt06aShutterOpenSub(GObj *volatile a0);
void actSt06aShutterSwitch(GObj *volatile a0);
void actSt06aStatueChk(GObj *volatile a0);
void actSt06aSuimonChk(GObj *volatile a0);
void actSt06aSuimonEffect(GObj *volatile a0);
void actSt06aSuimonFlagOn(GObj *volatile a0);
void actSt06aSuimonSub(GObj *volatile a0);
void actSt06aTreeChk(GObj *volatile a0);
void actSt06aWallWay2OffChk(GObj *volatile a0);
void actSt06aWallWay2OnChk(GObj *volatile a0);
void actSt06aWallWayOffChk(GObj *volatile a0);
void actSt06aWallWayOnChk(GObj *volatile a0);
void actSt06aWayOffChk(GObj *volatile a0);
void actSt06aWayOnChk(GObj *volatile a0);

#endif /* ST06A_H */
