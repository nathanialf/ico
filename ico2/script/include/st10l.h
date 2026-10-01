/*
 * ico2/script/include/st10l.h
 *
 * The declarations of what st10l.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST10L_H
#define ST10L_H

#include "typedef.h"

/* st10l.o's .sdata globals */
extern char *floor10l;
extern char *st10l_gondola_up;
extern char *st10l_gondola_down;
extern char *chain10l;
void actSt10lBoxAChk(GObj *volatile a0);
void actSt10lBoxBChk(GObj *volatile a0);
void actSt10lBoxChk(GObj *volatile a0);
void actSt10lChainMain(GObj *volatile a0);
void actSt10lChainMove(GObj *volatile a0);
void actSt10lChainSwitch(GObj *volatile a0);
void actSt10lEneCam1Chk(GObj *volatile a0);
void actSt10lEneCam2Chk(GObj *volatile a0);
void actSt10lEneCam3Chk(GObj *volatile a0);
void actSt10lEneKillChk(GObj *volatile a0);
void actSt10lFloorLeft(GObj *volatile a0);
void actSt10lFloorMain(GObj *volatile a0);
void actSt10lFloorRight(GObj *volatile a0);
void actSt10lFloorSwitch(GObj *volatile a0);
void actSt10lGondolaDown(GObj *volatile a0);
void actSt10lGondolaMain(GObj *volatile a0);
void actSt10lGondolaSwitch(GObj *volatile a0);
void actSt10lGondolaUp(GObj *volatile a0);

#endif /* ST10L_H */
