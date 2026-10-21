/*
 * ico2/script/include/st19a.h
 *
 * The declarations of what st19a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST19A_H
#define ST19A_H

#include "typedef.h"

struct SqEntry;

/* The stage's object entry points; st19a.c defines all but actSt19aHaguruma
   inline, and gcc outputs them at the end of the file in this order. */
void actSt19aOri(GObj *volatile self);
void actSt19aOriXL(GObj *volatile self);
void actSt19aPipe(GObj *volatile self);
void actSt19aPipeXL(GObj *volatile self);
void actSt19aChain(GObj *volatile self);
void actSt19aHaguruma(GObj *volatile self);

#endif /* ST19A_H */
