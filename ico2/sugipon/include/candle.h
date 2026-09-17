/*
 * ico2/sugipon/include/candle.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what candle.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CANDLE_H
#define CANDLE_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order candle.c's inline tail has. */
void DeleteLayoutedCandleParticleEffect(void);
void _deleteLayoutedCandleParticleEffect(void *gobj);

#endif /* CANDLE_H */
