/*
 * ico2/script/include/st10r.h
 *
 * The declarations of what st10r.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST10R_H
#define ST10R_H

#include "typedef.h"

/* st10r.o's .sdata globals */
extern char *st10r_floor;
extern char *cage10r;
extern char *chain10r;
void actSt10rCageMain(GObj *volatile a0);
void actSt10rCageSub(GObj *volatile a0);
void actSt10rChainMain(GObj *volatile a0);
void actSt10rChainMove(GObj *volatile a0);
void actSt10rChainMoveSub(GObj *volatile a0);
void actSt10rChainSwitch(GObj *volatile a0);
void actSt10rEneChk(GObj *volatile a0);
void actSt10rExitChk(GObj *volatile a0);
void actSt10rFenceDownChk(GObj *volatile a0);
void actSt10rFenceDownChk2(GObj *volatile a0);
void actSt10rFenceUpChk(GObj *volatile a0);
void actSt10rFenceUpChk2(GObj *volatile a0);
void actSt10rFloorChk(GObj *volatile a0);
void actSt10rFloorHitChk(GObj *volatile a0);
void actSt10rFloorSub(GObj *volatile a0);
void actSt10rGirlWay(volatile unsigned int a0);
void actSt10rTowerChk(GObj *volatile a0);
void actSt10rTowerConte(GObj *volatile a0);
void actSt10rTowerResqueChk(GObj *volatile a0);
void actSt10rWayOffChk(GObj *volatile a0);
void actSt10rWayOnChk(GObj *volatile a0);

#endif /* ST10R_H */
