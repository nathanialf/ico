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

void actSt06aBallDeleteChk(volatile int a0);
void actSt06aBox2Chk(volatile int a0);
void actSt06aBox3Chk(volatile int a0);
void actSt06aBoxChk(volatile int a0);
void actSt06aBoxEvent2InChk(volatile int a0);
void actSt06aBoxEvent2OutChk(volatile int a0);
void actSt06aBoxSub(volatile int a0);
void actSt06aDoorDownChk(volatile int a0);
void actSt06aDoorDownEffect(volatile int a0);
void actSt06aDoorUpChk(volatile int a0);
void actSt06aDoorUpEffect(volatile int a0);
void actSt06aExitChk(volatile int a0);
void actSt06aExitGirlChk(volatile int a0);
void actSt06aHeadChk(volatile int a0);
void actSt06aJumpMain(volatile int a0);
void actSt06aJumpMove(volatile int a0);
void actSt06aJumpSub(volatile int a0);
void actSt06aJumpSwitch(volatile int a0);
void actSt06aKyomiOffChk(volatile int a0);
void actSt06aKyomiOnChk(volatile int a0);
void actSt06aPistonFlagOnChk(volatile int a0);
void actSt06aPistonRideOnChk(volatile int a0);
void actSt06aShutterMain(volatile int a0);
void actSt06aShutterOpen(volatile int a0);
void actSt06aShutterOpenSub(volatile int a0);
void actSt06aShutterSwitch(volatile int a0);
void actSt06aStatueChk(volatile int a0);
void actSt06aSuimonChk(volatile int a0);
void actSt06aSuimonEffect(volatile int a0);
void actSt06aSuimonFlagOn(volatile int a0);
void actSt06aSuimonSub(volatile int a0);
void actSt06aTreeChk(volatile int a0);
void actSt06aWallWay2OffChk(volatile int a0);
void actSt06aWallWay2OnChk(volatile int a0);
void actSt06aWallWayOffChk(volatile int a0);
void actSt06aWallWayOnChk(volatile int a0);
void actSt06aWayOffChk(volatile int a0);
void actSt06aWayOnChk(volatile int a0);

#endif /* ST06A_H */
