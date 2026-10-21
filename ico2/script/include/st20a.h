/*
 * ico2/script/include/st20a.h
 *
 * The declarations of what st20a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST20A_H
#define ST20A_H

#include "typedef.h"

struct SqEntry;

/* st20a.o's .sdata globals */
extern struct SqEntry *gondola_up;
extern struct SqEntry *gondola_down;
extern unsigned int st20a_yure;
extern unsigned char st20a_yure_vol;
/* The stage's object entry points; st20a.c defines them inline, and gcc
   outputs them at the end of the file in this order. */
void actSt20aBridge(GObj *volatile self);
void actSt20aGondola(GObj *volatile self);
void actSt20aExit(GObj *volatile self);
void actSt20aElv(GObj *volatile self);
void actSt20aEne(GObj *volatile self);
void actSt20aEnemy1(GObj *volatile self);
void actSt20aEnemy2(GObj *volatile self);

#endif /* ST20A_H */
