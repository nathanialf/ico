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

void dma_init(void);
int freeseki(void *a0);
void malloc_SetPartition(int val);
int mallocseki(int size);
void matrix_init(void);
void resetmallocseki(void);

#endif /* BASIC_H */
