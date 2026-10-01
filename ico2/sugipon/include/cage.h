/*
 * ico2/sugipon/include/cage.h
 *
 * The declarations of what cage.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CAGE_H
#define CAGE_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order cage.c's inline tail has. */
int GetCageChainPoint(char *a0, char *a1, struct GObj *a2);
void SetCageVelocityFriction(struct GObj *a0, float a1);
void StabilizeAllLayoutedCage(void);
void SetCageChainHangableFlag(struct GObj *a0, int a1);
void HotInitCageGeo(struct GObj *self);

#endif /* CAGE_H */
