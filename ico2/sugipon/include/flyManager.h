/*
 * ico2/sugipon/include/flyManager.h
 *
 * The declarations of what flyManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef FLYMANAGER_H
#define FLYMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order flyManager.c's inline tail has. */
int InitFlyInfo(int *self);
void InitFlyManager(void);
int GetFlyLimitHeight(FlyLimitInfo *info, void *pos);
int GetFlyLimitClearance(void *pos);

#endif /* FLYMANAGER_H */
