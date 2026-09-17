/*
 * ico2/sugipon/include/cage.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what cage.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CAGE_H
#define CAGE_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order cage.c's inline tail has. */
int GetCageChainPoint(char *a0, char *a1, char *a2);
void SetCageVelocityFriction(char *a0, float a1);
void StabilizeAllLayoutedCage(void);
void SetCageChainHangableFlag(char *a0, int a1);

void HotInitCageGeo(char *self);

#endif /* CAGE_H */
