/*
 * ico2/fumi/include/memory.h
 *
 * The declarations of what memory.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MEMORY_H
#define MEMORY_H

typedef struct IosMemPart {    /* field names derived */
    char tag[16];              /* 0x00 */
    char name[16];             /* 0x10 */
    struct IosMemPart *prev;   /* 0x20 */
    struct IosMemPart *next;   /* 0x24 */
    struct IosMemPart *parent; /* 0x28 */
    int nused;                 /* 0x2C */
    char *top;                 /* 0x30 */
    int free;                  /* 0x34 */
    char *start;               /* 0x38 */
    char *end;                 /* 0x3C */
    int total;                 /* 0x40 */
    struct IosMemNode *head;   /* 0x44 */
} IosMemPart; /* derived name */

/* one block of a partition, allocated or on its free list */
typedef struct IosMemNode {       /* field names derived */
    char tag[16];                 /* 0x00 */
    char name[16];                /* 0x10 */
    struct IosMemNode *prev;      /* 0x20 */
    struct IosMemNode *next;      /* 0x24 */
    struct IosMemNode *free_prev; /* 0x28 */
    struct IosMemNode *free_next; /* 0x2C */
    struct IosMemPart *part;      /* 0x30 */
    int size;                     /* 0x34 */
    int line;                     /* 0x38 */
    int pad3C;                    /* 0x3C */
    struct IosMemNode *pad40;     /* 0x40 (partition header view) */
    struct IosMemNode *head;      /* 0x44 (partition header view: free-list head) */
} IosMemNode; /* derived name */

/* memory.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
IosMemPart *iosMallocInitPartition(unsigned int start, unsigned int end);
void *iosMallocDebug(IosMemPart *part, int size, const char *file, int line);
void *_iosMallocDebug();
void *iosFree(void *ptr);
void iosMallocCheckLeak(IosMemPart *part);
/* unprototyped: ios/memory.c defines it as `(void)` while seki/src/Primitive.c
   and sugipon/src/particleEffect.c call it with four arguments. */
IosMemPart *iosMallocResetPartition(IosMemPart *part);
IosMemPart *iosMallocSetPartition(IosMemPart *part, int size, int align);
int iosMallocSetPartitionName(IosMemPart *part, char *name);
void *iosReallocDebug(void *ptr, unsigned int size);

#endif /* MEMORY_H */
