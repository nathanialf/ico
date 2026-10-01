/*
 * ico2/sugipon/include/delayFreeManager.h
 *
 * The declarations of what delayFreeManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DELAYFREEMANAGER_H
#define DELAYFREEMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order delayFreeManager.c's inline tail has. */
void InitDelayFree(void);
void ExecDelayFree(void);

void EntryDelayFree(void *p);

#endif /* DELAYFREEMANAGER_H */
