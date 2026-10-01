/*
 * ico2/script/include/st02a.h
 *
 * The declarations of what st02a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST02A_H
#define ST02A_H

#include "typedef.h"

/* st02a.o's .sdata globals */
extern char *st02a_fence;
extern char *gondola;
extern char *gondola_test;
void actSt02aDoorDownChk(GObj *volatile a0);
void actSt02aDoorDownEffect(GObj *volatile a0);
void actSt02aDoorUpChk(GObj *volatile a0);
void actSt02aDoorUpEffect(GObj *volatile a0);
void actSt02aEneChk(GObj *volatile a0);
void actSt02aFenceMain(GObj *volatile a0);
void actSt02aFenceOpen(GObj *volatile a0);
void actSt02aFenceOpenSub(GObj *volatile a0);
void actSt02aGondolaDown(GObj *volatile a0);
void actSt02aGondolaMain(GObj *volatile a0);
void actSt02aGondolaUp(GObj *volatile a0);
void actSt02aSecretItemChk(GObj *volatile a0);
void actSt02aTakiWayOffChk(GObj *volatile a0);
void actSt02aTakiWayOnChk(GObj *volatile a0);
void actSt02aWaterFallChk(GObj *volatile a0);
void actSt02aWaterFallReflactionEffect(GObj *volatile a0);
void actSt02aWayOffChk(GObj *volatile a0);
void actSt02aWayOnChk(GObj *volatile a0);

#endif /* ST02A_H */
