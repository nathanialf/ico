/*
 * ico2/fumi/include/memory.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what memory.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MEMORY_H
#define MEMORY_H

typedef struct IosMemPart {
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
} IosMemPart;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order memory.c's inline tail has. */
IosMemPart *iosMallocInitPartition(unsigned int start, unsigned int end);
void *iosMallocDebug(IosMemPart *part, int size, char *file, int line);
void *_iosMallocDebug();
void *iosFree(void *ptr);
void iosMallocCheckLeak(IosMemPart *part);
/* unprototyped: ios/memory.c matches it as `(void)` while seki/src/Primitive.c
   and sugipon/src/particleEffect.c call it with the four arguments the ROM
   passes, so the header cannot commit to either spelling. */
IosMemPart *iosMallocResetPartition(IosMemPart *part);
IosMemPart *iosMallocSetPartition(IosMemPart *part, int size, int align);
int iosMallocSetPartitionName(int *a0, int a1);
void *iosReallocDebug(void *ptr, unsigned int size);

#endif /* MEMORY_H */
