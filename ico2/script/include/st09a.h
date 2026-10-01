/*
 * ico2/script/include/st09a.h
 *
 * The declarations of what st09a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST09A_H
#define ST09A_H

#include "typedef.h"

/* st09a.o's .sdata globals */
extern char *st09a_brg;
void actSt09aBrgDown(GObj *volatile a0);
void actSt09aBrgDownSub(GObj *volatile a0);
void actSt09aBrgMain(GObj *volatile a0);
void actSt09aBrgSwitch(GObj *volatile a0);
void actSt09aElvDown(GObj *volatile a0);
void actSt09aElvMain(GObj *volatile a0);
void actSt09aElvSwitch(GObj *volatile a0);
void actSt09aElvUp(GObj *volatile a0);
void actSt09aHint1Chk(GObj *volatile a0);
void actSt09aHint2Chk(GObj *volatile a0);
void actSt09aIntroChk(GObj *volatile a0);

#endif /* ST09A_H */
