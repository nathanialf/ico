/*
 * sce/libc/errno.h
 *
 * newlib's system-call layer keeps its error code in the global errno
 * (sce/libc/reent/sbrkr.c defines it) and hands out its address through
 * __errno.  The declarations are the definitions' in sce/.  Only what this
 * tree uses is declared.
 */
#ifndef SCE_LIBC_ERRNO_H
#define SCE_LIBC_ERRNO_H

extern int errno;   /* definition in sce/ (reent/sbrkr.c) */
int *__errno(void); /* definition in sce/ (errno/errno.c) */

#endif /* SCE_LIBC_ERRNO_H */
