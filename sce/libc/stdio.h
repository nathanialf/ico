/*
 * sce/libc/stdio.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (stdio.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_STDIO_H
#define SCE_LIBC_STDIO_H

struct Fil; /* sce/libc/reent.h's stream record */

int printf(const char *fmt, ...);    /* definition in sce/ */
int sprintf(char *str, const char *fmt, ...);  /* definition in sce/ */
int sscanf(const char *str, const char *fmt, ...); /* definition in sce/ */
int vfprintf();
int vsprintf(void *out, void *a1, void *a2);              /* definition in sce/ */
int fflush(struct Fil *fp);                               /* definition in sce/ */
int fiprintf(void *fp, void *fmt, ...);                   /* definition in sce/ */
int vfiprintf(char *fp, char *fmt0, void *ap);            /* definition in sce/ */
int fread(char *dst, int size, int count, struct Fil *s); /* definition in sce/ */
int ungetc(int c, struct Fil *fp);                        /* definition in sce/ */

#endif /* SCE_LIBC_STDIO_H */
