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
void actSt02aDoorDownChk(GObj *volatile self);
void actSt02aDoorDownEffect(GObj *volatile self);
void actSt02aDoorUpChk(GObj *volatile self);
void actSt02aDoorUpEffect(GObj *volatile self);
void actSt02aEneChk(GObj *volatile self);
void actSt02aFenceMain(GObj *volatile self);
void actSt02aFenceOpen(GObj *volatile self);
void actSt02aGondolaDown(GObj *volatile self);
void actSt02aGondolaMain(GObj *volatile self);
void actSt02aGondolaUp(GObj *volatile self);
void actSt02aSecretItemChk(GObj *volatile self);
void actSt02aTakiWayOffChk(GObj *volatile self);
void actSt02aTakiWayOnChk(GObj *volatile self);
void actSt02aWaterFallChk(GObj *volatile self);
void actSt02aWaterFallReflactionEffect(GObj *volatile self);
void actSt02aWayOffChk(GObj *volatile self);
void actSt02aWayOnChk(GObj *volatile self);

#endif /* ST02A_H */
