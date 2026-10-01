/*
 * ico2/sugipon/include/clipCollisionManager.h
 *
 * The declarations of what clipCollisionManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CLIPCOLLISIONMANAGER_H
#define CLIPCOLLISIONMANAGER_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order clipCollisionManager.c's inline tail has. */
void *RequestClipCollision(int *req);

struct GObj *CreateClipCollisionManagerGObj(void);

#endif /* CLIPCOLLISIONMANAGER_H */
