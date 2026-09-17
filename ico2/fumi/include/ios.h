/*
 * ico2/fumi/include/ios.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what ios.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef IOS_H
#define IOS_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order ios.c's inline tail has. */
int iosSifAllocIopHeapDebug(int size, char *file, int line);

void iosInitialize(void);
void ios_init_plus(void);

#endif /* IOS_H */
