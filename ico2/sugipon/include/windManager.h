/*
 * ico2/sugipon/include/windManager.h
 *
 * The declarations of what windManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WINDMANAGER_H
#define WINDMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order windManager.c's inline tail has. */
void ReinitWindManager(void);
void SetWindManager(float a, float b, float c, float d, float e, float f, float g, float h);
void InitWindManager(int no);
float GetRegularizedWindSpeed(void *pos);

#endif /* WINDMANAGER_H */
