/*
 * sce/libvu0/libvu0_internal.h  (derived name: the file name is ours)
 *
 * libvu0's declarations that are not public SDK API: the byte-clearing
 * helper libvu0.o defines and libdma.o's sceDmaReset calls.  Each prototype
 * is the signature of the member that defines it in sce/, which includes
 * this header.
 */
#ifndef SCE_LIBVU0_LIBVU0_INTERNAL_H
#define SCE_LIBVU0_LIBVU0_INTERNAL_H

void memclr(void *p, int n); /* definition in sce/libvu0/libvu0.c */

#endif /* SCE_LIBVU0_LIBVU0_INTERNAL_H */
