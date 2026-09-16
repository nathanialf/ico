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

void *_iosMallocDebug();
void *iosFree(void *ptr);
void iosMallocCheckLeak(void *a0);
void *iosMallocDebug(int heap, int size, char *file, int line);
/* unprototyped: ios/memory.c matches it as `(void)` while seki/src/Primitive.c
   and sugipon/src/particleEffect.c call it with the four arguments the ROM
   passes, so the header cannot commit to either spelling. */
void *iosMallocDebugNoAssert();
int iosMallocInitPartition(int base, int size);
void iosMallocResetPartition(void *part);
int iosMallocSetPartition(int part, int size, int align);
int iosMallocSetPartitionName(int *a0, int a1);
void *iosReallocDebug(void *ptr, unsigned int size);

#endif /* MEMORY_H */
