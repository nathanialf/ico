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

#endif /* BASIC_H */
