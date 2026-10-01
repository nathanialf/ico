/*
 * sce/libc/unistd.h
 *
 * PUBLIC NEWLIB NAMING RUNG, as sce/libc/stdio.h: newlib's header of this
 * name declares the system-call entry points libkernl's glue.c supplies to newlib (close, lseek, read, write, isatty, getpid, sbrk, _exit).
 * Each declaration is the definition's in sce/ where that is C, else the
 * spelling its callers carry.  Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_UNISTD_H
#define SCE_LIBC_UNISTD_H

int close(int a1);                           /* definition in sce/ */
long lseek(int fd, long offset, int whence); /* definition in sce/ */
int read(int fd, void *buf, int size);       /* definition in sce/ */
int write(int fd, void *buf, int size);      /* definition in sce/ */
int isatty(int fd);                          /* definition in sce/ */
int getpid(void);                            /* definition in sce/ */
unsigned int sbrk(int a0);                   /* the spelling at 1 site, asm definition in sce/ */
void _exit(int a0);                          /* the spelling at 1 site */

#endif /* SCE_LIBC_UNISTD_H */
