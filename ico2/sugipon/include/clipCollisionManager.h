/*
 * ico2/sugipon/include/clipCollisionManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what clipCollisionManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CLIPCOLLISIONMANAGER_H
#define CLIPCOLLISIONMANAGER_H

extern int CreateClipCollisionManagerGObj(void);
extern void *RequestClipCollision(int *a0);
extern void actClipCollisionCore(volatile unsigned int self);

#endif /* CLIPCOLLISIONMANAGER_H */
