/*
 * ico2/script/include/st47a.h
 *
 * The declarations of what st47a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST47A_H
#define ST47A_H

#include "typedef.h"

struct SqEntry;

/* st47a.o's .sdata globals */
extern int sekizo_47a;
extern unsigned char sekizo_47a_vol;
/* The stage's object entry points; st47a.c defines them inline, and gcc
   outputs them at the end of the file in this order. */
void actSt47aSekizo1(GObj *volatile self);
void actSt47aSekizo2(GObj *volatile self);
void actSt47aSekizo3(GObj *volatile self);
void actSt47aSekizo4(GObj *volatile self);
void actSt47aHane1(GObj *volatile self);
void actSt47aHane2(GObj *volatile self);
void actSt47aRope(GObj *volatile self);
void actSt47aRopeSwing(GObj *volatile self); /* derived name */
void actSt47aBarricade(GObj *volatile self);
void actSt47aExit(GObj *volatile self);
void actSt47aExit2(GObj *volatile self);
void actSt47aEne(GObj *volatile self);
void actSt47aEnemy2(GObj *volatile self);

#endif /* ST47A_H */
