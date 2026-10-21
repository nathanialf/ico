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

/* The stage's object entry points; st17a.c defines the last four inline,
   and gcc outputs them at the end of the file in this order. */
void actSt17aDoor(GObj *volatile self);
void actLinkTest(GObj *volatile self);
void actSt17aSekizo(GObj *volatile self);
void actSt17aHasi(GObj *volatile self);
void actSt17aIntro(GObj *volatile self);

#endif /* ST17A_H */
