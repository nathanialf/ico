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
/* deja.c's poster, its `inline` sleeper (out of line at the end of the
 * object) and the handler the poster installs. */
void actDeja(GObj *volatile self);
void actEnemySleep(GObj *volatile self);
void actDejaChk(GObj *volatile self);

#endif /* DEJA_H */
