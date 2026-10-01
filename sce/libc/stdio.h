/*
 * sce/libc/stdio.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called stdio.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_STDIO_H
#define SCE_LIBC_STDIO_H

struct Fil; /* sce/libc/reent.h's stream record */

int printf(const char *fmt, ...);                         /* definition in sce/ */
int sprintf(void *a0, int a1, ...);                       /* definition in sce/ */
int sscanf(void *a0, void *a1, ...);                      /* definition in sce/ */
int vfprintf();                                           /* dominant spelling at 4 sites */
int vsprintf(void *out, void *a1, void *a2);              /* definition in sce/ */
int fflush(struct Fil *fp);                               /* definition in sce/ */
int fiprintf(void *fp, void *fmt, ...);                   /* definition in sce/ */
int vfiprintf(char *fp, char *fmt0, void *ap);            /* definition in sce/ */
int fread(char *dst, int size, int count, struct Fil *s); /* definition in sce/ */
int ungetc(int c, struct Fil *fp);                        /* definition in sce/ */

#endif /* SCE_LIBC_STDIO_H */
