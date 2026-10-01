/*
 * ico2/sugipon/include/waySystemManager.h
 *
 * The declarations of what waySystemManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WAYSYSTEMMANAGER_H
#define WAYSYSTEMMANAGER_H

struct GObj;
struct GProc;
struct WayRequest;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order waySystemManager.c's inline tail has. */
struct GProc *RequestGetWayBegin(struct WayRequest *req);

struct GObj *CreateWaySystemManagerGObj(void);

#endif /* WAYSYSTEMMANAGER_H */
