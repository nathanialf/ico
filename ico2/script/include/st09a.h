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
void actSt09aBrgDown(GObj *volatile self);
void actSt09aBrgMain(GObj *volatile self);
void actSt09aBrgSwitch(GObj *volatile self);
void actSt09aElvDown(GObj *volatile self);
void actSt09aElvMain(GObj *volatile self);
void actSt09aElvSwitch(GObj *volatile self);
void actSt09aElvUp(GObj *volatile self);
void actSt09aIntroChk(GObj *volatile self);

#endif /* ST09A_H */
