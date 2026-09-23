/*
 * ico2/seki/include/Basic.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Basic.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BASIC_H
#define BASIC_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order Basic.c's inline tail has. */
void malloc_SetPartition(int val);
int malloc_GetPartition(void);
int mallocseki(int size);
int freeseki(void *a0);
void resetmallocseki(void);
int mallocsekistage(int size);
int reallocseki(int size, int align);

void dma_init(void);
void matrix_init(void);

/* RECONSTRUCTION: seki's float absolute value and sign, one macro each
 * (names ours).  Rung: ROM bytes.  Texture.c's tex_scrollClut takes the
 * sign of an int through them (the ROM's cvt.s.w pairs) and
 * BgAnimation.c's _RotTransCurrentMatrixYXZ derives each sine as
 * SIGNF(angle) * sqrt(1 - cos^2) on one listing row (BgAnimation.c:2135 to
 * 2137): fold pushes the product into the three arms, the neg.s, the plain
 * value and the times-zero the ROM carries.  Light.c's LIGHT_ABS is the
 * same text as ABSF. */
#define ABSF(x) ((x) < 0.0f ? -(x) : (x))
#define SIGNF(x) ((x) < 0.0f ? -1.0f : ((x) > 0.0f ? 1.0f : 0.0f))

#endif /* BASIC_H */
