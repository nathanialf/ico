/*
 * ico2/ito/include/stage_orient.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what stage_orient.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STAGE_ORIENT_H
#define STAGE_ORIENT_H

#include "typedef.h"   /* VECTOR */

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order stage_orient.c's inline tail has. */
void StageOrientInit(void);
int StageOrientGet(VECTOR *ret, int stA, int stB);

int OtherStagePositionGet(VECTOR *ret, int stA, int stB, VECTOR *pos);

#endif /* STAGE_ORIENT_H */
