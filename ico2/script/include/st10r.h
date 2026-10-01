/*
 * ico2/script/include/st10r.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st10r.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST10R_H
#define ST10R_H

#include "typedef.h"

/* st10r.o's .sdata globals (MAIN.MAP) */
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
