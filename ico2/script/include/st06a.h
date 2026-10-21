/*
 * ico2/script/include/st06a.h
 *
 * The declarations of what st06a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST06A_H
#define ST06A_H

#include "typedef.h"

struct SqEntry;

/* st06a.o's .sdata globals */
void actSt06aBoxChk(GObj *volatile self);
void actSt06aDoorDownChk(GObj *volatile self);
void actSt06aDoorUpChk(GObj *volatile self);
void actSt06aHeadChk(GObj *volatile self);
void actSt06aShutterOpen(GObj *volatile self);
void actSt06aStatueChk(GObj *volatile self);
void actSt06aSuimonChk(GObj *volatile self);

#endif /* ST06A_H */
