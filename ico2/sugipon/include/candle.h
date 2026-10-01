/*
 * ico2/sugipon/include/candle.h
 *
 * The declarations of what candle.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CANDLE_H
#define CANDLE_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order candle.c's inline tail has. */
void DeleteLayoutedCandleParticleEffect(void);
void _deleteLayoutedCandleParticleEffect(void *gobj);

#endif /* CANDLE_H */
