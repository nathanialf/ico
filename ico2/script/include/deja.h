/*
 * ico2/script/include/deja.h
 *
 * The declarations of what deja.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DEJA_H
#define DEJA_H

#include "typedef.h"

struct SqEntry;

/* deja.o's .sdata global */
extern struct SqEntry *deja;
/* deja.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void actDeja(GObj *volatile self);
void actEnemySleep(GObj *volatile self);
void actDejaChk(GObj *volatile self);

#endif /* DEJA_H */
