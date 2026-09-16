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

extern void iosInitialize(void);
extern int iosSifAllocIopHeapDebug(int size, char *file, int line);
extern void ios_init_plus(void);

#endif /* IOS_H */
