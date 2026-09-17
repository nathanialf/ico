/*
 * ico2/common/include/charFileManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what charFileManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CHARFILEMANAGER_H
#define CHARFILEMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order charFileManager.c's inline tail has. */
void ReadSoundSqFile(void *h, int a1, int size, int a3, int kind, int a5, int a6);
void ReadSoundAdpcmFile(void *h, int a1, int size, int a3, int a4, int a5, int a6);


#endif /* CHARFILEMANAGER_H */
