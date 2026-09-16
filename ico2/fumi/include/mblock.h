/*
 * ico2/fumi/include/mblock.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mblock.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MBLOCK_H
#define MBLOCK_H

extern void init_mblock(int *a0);
extern void *new_segment(void *mb, int size);
extern void reuse_mblock(int *a0);

#endif /* MBLOCK_H */
