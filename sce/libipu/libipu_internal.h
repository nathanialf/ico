/*
 * sce/libipu/libipu_internal.h  (derived name: the file name is ours)
 *
 * libipu's declarations that are not public SDK API: the two DMA channel
 * control helpers libipu.o calls.  Each prototype is the signature of the
 * member that defines it in sce/, which includes this header.
 */
#ifndef SCE_LIBIPU_LIBIPU_INTERNAL_H
#define SCE_LIBIPU_LIBIPU_INTERNAL_H

void setD3_CHCR(int chcr); /* definition in sce/libmpeg/bit.c (libipu.o's run) */
void setD4_CHCR(int chcr); /* definition in sce/libmpeg/bit.c (libipu.o's run) */

#endif /* SCE_LIBIPU_LIBIPU_INTERNAL_H */
