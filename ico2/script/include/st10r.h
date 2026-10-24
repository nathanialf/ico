/*
 * ico2/script/include/st10r.h
 *
 * The declarations of what st10r.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST10R_H
#define ST10R_H

#include "typedef.h"

struct SqEntry;

/* st10r.o's .sdata globals */
extern struct SqEntry *st10r_floor;

#ifndef VERSION_JUN26
extern struct SqEntry *cage10r;
extern struct SqEntry *chain10r;
#endif

void actSt10rCageMain(GObj *volatile self);
void actSt10rChainMain(GObj *volatile self);
void actSt10rChainMove(GObj *volatile self);
void actSt10rChainSwitch(GObj *volatile self);

#ifndef VERSION_JUN26
void actSt10rEneChk(GObj *volatile self);
#endif

void actSt10rExitChk(GObj *volatile self);
void actSt10rFenceDownChk(GObj *volatile self);
void actSt10rFenceDownChk2(GObj *volatile self);
void actSt10rFenceUpChk(GObj *volatile self);
void actSt10rFenceUpChk2(GObj *volatile self);
void actSt10rFloorChk(GObj *volatile self);

#ifdef VERSION_JUN26
void actSt10rTowerChk(GObj *volatile self);
#else
void actSt10rGirlWay(volatile unsigned int self);
void actSt10rTowerChk(GObj *volatile self);
void actSt10rTowerConte(GObj *volatile self);
#endif

#endif /* ST10R_H */
