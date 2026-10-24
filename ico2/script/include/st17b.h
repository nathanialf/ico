/*
 * ico2/script/include/st17b.h
 *
 * The declarations of what st17b.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST17B_H
#define ST17B_H

#include "typedef.h"

struct SqEntry;

/* st17b.o's .sdata globals */
extern struct SqEntry *lightning2;
void actSt17bCheckChk(GObj *volatile self);
#ifdef VERSION_NTSC
void actSt17bIntroChk(GObj *volatile self);
#endif

#endif /* ST17B_H */
