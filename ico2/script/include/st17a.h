/*
 * ico2/script/include/st17a.h
 *
 * The declarations of what st17a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST17A_H
#define ST17A_H

#include "typedef.h"

struct SqEntry;

/* st17a.o's .sdata globals */
extern struct SqEntry *cam;

#ifdef VERSION_JUN26
/* The stage's object entry points; st17a.c defines the last four inline,
   and gcc outputs them at the end of the file in this order. */
void actSt17aDoor(GObj *volatile self);
void actLinkTest(GObj *volatile self);
void actSt17aSekizo(GObj *volatile self);
void actSt17aHasi(GObj *volatile self);
void actSt17aIntro(GObj *volatile self);
#else
void actLinkTestChk(GObj *volatile self);
void actSt17aDoorDownChk(GObj *volatile self);
void actSt17aDoorDownEffect(GObj *volatile self);
void actSt17aDoorUpChk(GObj *volatile self);
void actSt17aDoorUpEffect(GObj *volatile self);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt17aGirlWay(GObj *volatile self);
void actSt17aHasiChk(GObj *volatile self);
void actSt17aHasiEffect(GObj *volatile self);
void actSt17aIntro(GObj *volatile self);
#else
void actSt17aHasiChk(GObj *volatile self);
void actSt17aHasiEffect(GObj *volatile self);
#endif

void actSt17aIntroChk(GObj *volatile self);
#endif

#endif /* ST17A_H */
