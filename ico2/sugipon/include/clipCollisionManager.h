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

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order clipCollisionManager.c's inline tail has. */
void *RequestClipCollision(int *a0);

int CreateClipCollisionManagerGObj(void);
void actClipCollisionCore(volatile unsigned int self);

#endif /* CLIPCOLLISIONMANAGER_H */
