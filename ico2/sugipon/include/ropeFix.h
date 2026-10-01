/*
 * ico2/sugipon/include/ropeFix.h
 *
 * The declarations of what ropeFix.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ROPEFIX_H
#define ROPEFIX_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order ropeFix.c's inline tail has. */
int InitRopeFixGeo(void);

struct GObj;

void RopeFixGeo(struct GObj *fix);
void RopeFixDL(struct GObj *fix);

#endif /* ROPEFIX_H */
