/*
 * ico2/sugipon/include/particleLayout.h
 *
 * The declarations of what particleLayout.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef PARTICLELAYOUT_H
#define PARTICLELAYOUT_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order particleLayout.c's inline tail has. */
int *InitParticleLayoutGeo(struct GObj *self, int *layout);
void ParticleLayoutDL(void);
void DeleteParticleLayout(struct GObj *self);

struct GObj;

void ParticleLayoutGeo(struct GObj *self);

#endif /* PARTICLELAYOUT_H */
