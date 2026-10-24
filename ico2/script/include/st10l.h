/*
 * ico2/script/include/st10l.h
 *
 * The declarations of what st10l.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST10L_H
#define ST10L_H

#include "typedef.h"

struct SqEntry;

/* st10l.o's .sdata globals */
#ifdef VERSION_JUN26
extern struct SqEntry *st10l_gondola_up;
extern struct SqEntry *st10l_gondola_down;
#else
extern struct SqEntry *floor10l;
extern struct SqEntry *st10l_gondola_up;
extern struct SqEntry *st10l_gondola_down;
extern struct SqEntry *chain10l;
#endif

void actSt10lBoxAChk(GObj *volatile self);
void actSt10lBoxBChk(GObj *volatile self);
void actSt10lBoxChk(GObj *volatile self);
void actSt10lChainMain(GObj *volatile self);
void actSt10lChainMove(GObj *volatile self);
void actSt10lChainSwitch(GObj *volatile self);

#ifndef VERSION_JUN26
void actSt10lEneCam1Chk(GObj *volatile self);
#endif

void actSt10lEneCam2Chk(GObj *volatile self);
void actSt10lEneCam3Chk(GObj *volatile self);
void actSt10lFloorLeft(GObj *volatile self);
void actSt10lFloorMain(GObj *volatile self);
void actSt10lFloorRight(GObj *volatile self);
void actSt10lFloorSwitch(GObj *volatile self);
void actSt10lGondolaDown(GObj *volatile self);
void actSt10lGondolaMain(GObj *volatile self);
void actSt10lGondolaSwitch(GObj *volatile self);
void actSt10lGondolaUp(GObj *volatile self);

#endif /* ST10L_H */
