/*
 * ico2/sugipon/include/worm.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what worm.c.inc defines, in the order the
 * coalescing TU's prototype block carried them; every type here is read from
 * the ROM's calling convention at the call sites.
 */

#ifndef WORM_H
#define WORM_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order worm.c's inline tail has. */
void SetDirectWormTargetPos(struct GObj *act, void *pos);
void SetWormReduceRatio(struct GObj *a0, float f12);
void TraceWormRoute(struct GObj *act, float t);

#endif /* WORM_H */
