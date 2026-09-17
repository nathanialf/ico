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

typedef struct MBlockNode {
    char *buf;
    unsigned int size;
    unsigned int used;
    struct MBlockNode *next;
} MBlockNode;

typedef struct MBlock {
    MBlockNode *head;
    unsigned int total;
} MBlock;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order mblock.c's inline tail has. */
void init_mblock(int *a0);
void *new_segment(MBlock *mb, unsigned int len);
void reuse_mblock(int *a0);
char *strdup_mblock(MBlock *mb, const char *str);

#endif /* MBLOCK_H */
