/*
 * ico2/common/include/debug_exception.h
 *
 * The declarations of what debug_exception.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DEBUG_EXCEPTION_H
#define DEBUG_EXCEPTION_H

#include <libgraph.h>

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order debug_exception.c's inline tail has. */
void debugExceptionInit(void *workBuf);
void debugIOPExceptionInit(void);
void debug_assertMessage(char *file, int line, char *mes);
void debug_assert(char *file, int line);
void RestoreNormalDrawEnvironment(sceGsDBuff *db, int a1, int a2);
void SetDrawEnvironment(int mode);
void debugEEExceptionMain();
void drawSprite(int r, int g, int b, int a, int x0, int y0, int x1, int y1, int tex);

#endif /* DEBUG_EXCEPTION_H */
