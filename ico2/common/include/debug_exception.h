/*
 * ico2/common/include/debug_exception.h
 *
 * The declarations of what debug_exception.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DEBUG_EXCEPTION_H
#define DEBUG_EXCEPTION_H

#include <libgraph.h>

/* debug_exception.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void debugExceptionInit(void *workBuf);
void debugIOPExceptionInit(void);
void debug_assertMessage(char *file, int line, char *mes);
void debug_assert(char *file, int line);
void RestoreNormalDrawEnvironment(sceGsDBuff *db, int a1, int a2);
void SetDrawEnvironment(int mode);

#endif /* DEBUG_EXCEPTION_H */
