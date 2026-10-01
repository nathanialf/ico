/*
 * sce/libc/libc_internal.h  (derived name: the file name is ours)
 *
 * newlib's declarations that are not in its public headers (its own
 * stdio/local.h, stdlib/mprec.h and malloc internals): the stream
 * primitives the stdio members share, the big-integer helpers dtoa and
 * strtod share with mprec, and the malloc arena state.  Each declaration is
 * the definition's in sce/libc where that is C, else the spelling its callers
 * carry.  The record types are left incomplete here: each member still types
 * the ones it reaches.
 */
#ifndef SCE_LIBC_LIBC_INTERNAL_H
#define SCE_LIBC_LIBC_INTERNAL_H

#include <reent.h>

struct _Bigint;

struct __suio;

struct malloc_chunk;

struct mallinfo;

int __sread(Fil *a0, int a1, int a2);                              /* definition in sce/ */
long __swrite(Fil *a0, int a1, int a2);                            /* definition in sce/ */
long __sseek(Fil *a0, int a1, int a2);                             /* definition in sce/ */
int __sclose(Fil *a0);                                             /* definition in sce/ */
void __sinit(Reent *s);                                            /* definition in sce/ */
void __smakebuf(Fil *fp);                                          /* definition in sce/ */
int __srefill(Fil *fp);                                            /* definition in sce/ */
int __swsetup(Fil *fp);                                            /* definition in sce/ */
int __sfvwrite(Fil *fp, struct __suio *uio);                       /* definition in sce/ */
int __submore(Fil *fp);                                            /* definition in sce/ */
char *__sccl(char *tab, char *fmt);                                /* definition in sce/ */
int _fwalk(Reent *ptr, int (*function)());                         /* definition in sce/ */
void _cleanup_r(Reent *ptr);                                       /* definition in sce/ */
void std(Fil *fp, int flags, int file, Reent *data);               /* definition in sce/ */
int _vfiprintf_r(void *data, Fil *fp, const char *fmt0, char *ap); /* definition in sce/ */
int _vfprintf_r(int *self, int subj, int b, void *args); /* dominant spelling at 1 of 2 sites */
int *_Balloc(void *ptr, int k);                          /* definition in sce/ */
void _Bfree(char *a0, int *a1);                          /* definition in sce/ */
int *_d2b(void *ptr, double dd, int *e, int *bits);      /* definition in sce/ */
void *_i2b(void *a0, int a1);                            /* definition in sce/ */
int *_pow5mult(void *ptr, struct _Bigint *b, int k);     /* definition in sce/ */
int *_multiply(void *ptr, struct _Bigint *a, struct _Bigint *b); /* definition in sce/ */
int *_lshift(void *ptr, struct _Bigint *b, int k);               /* definition in sce/ */
int *__mdiff(void *ptr, struct _Bigint *a, struct _Bigint *b);   /* definition in sce/ */
int *_multadd(void *ptr, struct _Bigint *b, int m, int a);       /* definition in sce/ */
int _hi0bits(unsigned int a0);                                   /* definition in sce/ */
int __mcmp(unsigned int *a, unsigned int *b);                    /* definition in sce/ */
double _b2d(struct _Bigint *a, int *e);                          /* definition in sce/ */
double _ulp(double xx);                                          /* definition in sce/ */
double _ratio(struct _Bigint *a, struct _Bigint *b);             /* definition in sce/ */
int _s2b(void *a0, char *a1, int a2, int a3, int a4);            /* definition in sce/ */
extern struct malloc_chunk *__malloc_av_[];       /* definition in sce/ (stdlib/mallocr.c) */
extern unsigned long __malloc_trim_threshold;     /* definition in sce/ (stdlib/mallocr.c) */
extern unsigned long __malloc_top_pad;            /* definition in sce/ (stdlib/mallocr.c) */
extern char *__malloc_sbrk_base;                  /* definition in sce/ (stdlib/mallocr.c) */
extern struct mallinfo __malloc_current_mallinfo; /* definition in sce/ (stdlib/mallocr.c) */
void __malloc_lock(void);                         /* definition in sce/ */
void __malloc_unlock();                           /* definition in sce/ */
int _malloc_trim_r(int *self, unsigned int a1);   /* definition in sce/ */

#endif /* SCE_LIBC_LIBC_INTERNAL_H */
