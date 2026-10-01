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

typedef struct _Bigint _Bigint;

struct __suio;

typedef unsigned int INTERNAL_SIZE_T;

struct malloc_chunk {
    INTERNAL_SIZE_T prev_size;
    INTERNAL_SIZE_T size;
    struct malloc_chunk *fd;
    struct malloc_chunk *bk;
};

typedef struct malloc_chunk *mchunkptr;

/* newlib's mallinfo record; mallocr keeps the arena total in it */
struct mallinfo {
    int arena;
    int ordblks;
    int smblks;
    int hblks;
    int hblkhd;
    int usmblks;
    int fsmblks;
    int uordblks;
    int fordblks;
    int keepcost;
};

int __sread(void *cookie, char *buf, int n);                       /* definition in sce/ */
int __swrite(void *cookie, char *buf, int n);                      /* definition in sce/ */
long __sseek(void *cookie, long offset, int whence);               /* definition in sce/ */
int __sclose(void *cookie);                                        /* definition in sce/ */
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
int _vfprintf_r(int *self, int subj, int b, void *args);
_Bigint *_Balloc(Reent *ptr, int k);                                        /* definition in sce/ */
void _Bfree(Reent *ptr, _Bigint *v);                                        /* definition in sce/ */
_Bigint *_multadd(Reent *ptr, _Bigint *b, int m, int a);                    /* definition in sce/ */
_Bigint *_s2b(Reent *ptr, const char *s, int nd0, int nd, unsigned int y9); /* definition in sce/ */
int _hi0bits(unsigned int x);                                               /* definition in sce/ */
int _lo0bits(unsigned int *y);                                              /* definition in sce/ */
_Bigint *_i2b(Reent *ptr, int i);                                           /* definition in sce/ */
_Bigint *_multiply(Reent *ptr, _Bigint *a, _Bigint *b);                     /* definition in sce/ */
_Bigint *_pow5mult(Reent *ptr, _Bigint *b, int k);                          /* definition in sce/ */
_Bigint *_lshift(Reent *ptr, _Bigint *b, int k);                            /* definition in sce/ */
int __mcmp(_Bigint *a, _Bigint *b);                                         /* definition in sce/ */
_Bigint *__mdiff(Reent *ptr, _Bigint *a, _Bigint *b);                       /* definition in sce/ */
double _ulp(double x);                                                      /* definition in sce/ */
double _b2d(_Bigint *a, int *e);                                            /* definition in sce/ */
_Bigint *_d2b(Reent *ptr, double d, int *e, int *bits);                     /* definition in sce/ */
double _ratio(_Bigint *a, _Bigint *b);                                      /* definition in sce/ */
extern struct malloc_chunk *__malloc_av_[];             /* definition in sce/ (stdlib/mallocr.c) */
extern unsigned long __malloc_trim_threshold;           /* definition in sce/ (stdlib/mallocr.c) */
extern unsigned long __malloc_top_pad;                  /* definition in sce/ (stdlib/mallocr.c) */
extern char *__malloc_sbrk_base;                        /* definition in sce/ (stdlib/mallocr.c) */
extern struct mallinfo __malloc_current_mallinfo;       /* definition in sce/ (stdlib/mallocr.c) */
void __malloc_lock(Reent *ptr);                         /* definition in sce/ */
void __malloc_unlock(Reent *ptr);                       /* definition in sce/ */
int _malloc_trim_r(Reent *reent_ptr, unsigned int pad); /* definition in sce/ */

#endif /* SCE_LIBC_LIBC_INTERNAL_H */
