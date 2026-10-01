/*
 * ico2/fumi/include/mblock.h
 *
 * The declarations of what mblock.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MBLOCK_H
#define MBLOCK_H

typedef struct MBlockNode { /* field names derived */
    char *buf;
    unsigned int size;
    unsigned int used;
    struct MBlockNode *next;
} MBlockNode; /* derived name */

typedef struct MBlock { /* field names derived */
    MBlockNode *head;
    unsigned int total;
} MBlock; /* derived name */

/* mblock.o's .sdata global: the free node list */
extern int free_mblock_list;

/* mblock.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void init_mblock(int *a0);
void *new_segment(MBlock *mb, unsigned int len);
void reuse_mblock(int *a0);
char *strdup_mblock(MBlock *mb, const char *str);

MBlockNode *new_mblock_node(unsigned int size);

#endif /* MBLOCK_H */
