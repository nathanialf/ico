/*
 * ico2/script/include/st13b.h
 *
 * The declarations of what st13b.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST13B_H
#define ST13B_H

#include "typedef.h"

/* st13b.o's .sdata globals */
extern char *sekizo13b;
extern char *sekizo13b2;
extern char *meets_again;
extern char *boss;
extern char *sd;
extern char *boss_dead;
extern char *st13b_up;
extern char *st13b_down;
extern char *sekizo_13b;
extern char *sekizo_13b_vol;
extern int st13b_yure;
extern unsigned char st13b_yure_vol;
void actConte10c(GObj *volatile self);
void actSt13bBossAfterChk(GObj *volatile self);
void actSt13bBossChk(GObj *volatile self);
void actSt13bConte02(GObj *volatile self);
void actSt13bConte02Jimaku(GObj *volatile self);
void actSt13bDoorMain(GObj *volatile self);
void actSt13bDoorSwitch(GObj *volatile self);
void actSt13bDoorUp(GObj *volatile self);
void actSt13bElevDown(GObj *volatile self);
void actSt13bElevMain(GObj *volatile self);
void actSt13bElevSwitch(GObj *volatile self);
void actSt13bElevUpChk(GObj *volatile self);
void actSt13bFloorChk(GObj *volatile self);
void actSt13bMeetAgainChk(GObj *volatile self);
void actSt13bSekizo2Chk(GObj *volatile self);
void actSt13bSekizoChk(GObj *volatile self);

#endif /* ST13B_H */
