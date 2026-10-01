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
void actSt10rCageMain(GObj *volatile self);
void actSt10rChainMain(GObj *volatile self);
void actSt10rChainMove(GObj *volatile self);
void actSt10rChainSwitch(GObj *volatile self);
void actSt10rEneChk(GObj *volatile self);
void actSt10rExitChk(GObj *volatile self);
void actSt10rFenceDownChk(GObj *volatile self);
void actSt10rFenceDownChk2(GObj *volatile self);
void actSt10rFenceUpChk(GObj *volatile self);
void actSt10rFenceUpChk2(GObj *volatile self);
void actSt10rFloorChk(GObj *volatile self);
void actSt10rGirlWay(volatile unsigned int self);
void actSt10rTowerChk(GObj *volatile self);
void actSt10rTowerConte(GObj *volatile self);

#endif /* ST10R_H */
