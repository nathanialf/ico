/*
 * ico2/script/include/st10l.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st10l.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST10L_H
#define ST10L_H

#include "typedef.h"

/* st10l.o's .sdata globals (MAIN.MAP) */
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
