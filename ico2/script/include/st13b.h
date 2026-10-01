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
void actConte10c(GObj *volatile a0);
void actSt13bBossAfterChk(GObj *volatile a0);
void actSt13bBossChk(GObj *volatile a0);
void actSt13bConte02(GObj *volatile a0);
void actSt13bConte02Jimaku(GObj *volatile a0);
void actSt13bDoorMain(GObj *volatile a0);
void actSt13bDoorSwitch(GObj *volatile a0);
void actSt13bDoorUp(GObj *volatile a0);
void actSt13bDoorUpSub(GObj *volatile a0);
void actSt13bElev2CharaChk(GObj *volatile a0);
void actSt13bElev2Chk(GObj *volatile a0);
void actSt13bElevDown(GObj *volatile a0);
void actSt13bElevDownSub(GObj *volatile a0);
void actSt13bElevMain(GObj *volatile a0);
void actSt13bElevSwitch(GObj *volatile a0);
void actSt13bElevUpChk(GObj *volatile a0);
void actSt13bElevUpSub(GObj *volatile a0);
void actSt13bFloorChk(GObj *volatile a0);
void actSt13bMeetAgainChk(GObj *volatile a0);
void actSt13bMeetAgainSub(GObj *volatile a0);
void actSt13bSekizo2Chk(GObj *volatile a0);
void actSt13bSekizoChk(GObj *volatile a0);

#endif /* ST13B_H */
