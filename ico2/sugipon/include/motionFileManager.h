/*
 * ico2/sugipon/include/motionFileManager.h
 *
 * The declarations of what motionFileManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MOTIONFILEMANAGER_H
#define MOTIONFILEMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order motionFileManager.c's inline tail has. */
void ResetDynamicMotionManager(void);
void ResetStatic2MotionManager(int seg);
int CheckMotionIncludeFacialData(unsigned int *self);
int AddMotionMemorySize(int size, int seg);
int GetMotionMemorySize(int seg);
void InitMotionFile(void *buf, char *name);
extern int *motionTable[];
void InitMotionMemorySize(void);

#endif /* MOTIONFILEMANAGER_H */
