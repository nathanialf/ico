/*
 * sce/libc/stdlib.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (stdlib.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_STDLIB_H
#define SCE_LIBC_STDLIB_H

struct _reent;

double atof(const char *ascii);                                          /* definition in sce/ */
int atoi(void *str);                                                     /* definition in sce/ */
void qsort(void *base, unsigned int n, unsigned int size, int (*cmp)()); /* definition in sce/ */
int rand(void);                                                          /* definition in sce/ */
double strtod(const char *s00, char **se);                               /* definition in sce/ */
long strtol(const char *s, char **ptr, int base);                        /* definition in sce/ */
extern int __mb_cur_max; /* definition in sce/ (locale.c) */

#define MB_CUR_MAX __mb_cur_max

/* mprec.o's power-of-ten tables (newlib mprec.h names them tens, bigtens and
   tinytens). */
extern const double __mprec_tens[];
extern const double __mprec_bigtens[];
extern const double __mprec_tinytens[];
void abort(void);                                           /* definition in sce/ */
unsigned long strtoul(const char *s, char **ptr, int base); /* definition in sce/ */

struct Reent;

void *_malloc_r(struct Reent *reent_ptr, int bytes); /* definition in sce/ */
void _free_r(struct Reent *reent_ptr, void *mem);    /* definition in sce/ */

void *_realloc_r(struct Reent *reent_ptr, void *oldmem,
                 unsigned int bytes); /* definition in sce/ */

void *_calloc_r(struct Reent *reent_ptr, unsigned int n,
                unsigned int elem_size); /* definition in sce/ */

int _mbtowc_r(struct Reent *r, int *pwc, const char *s, int n, int *state); /* definition in sce/ */

unsigned long _strtoul_r(struct _reent *rptr, const char *nptr, char **endptr,
                         int base); /* definition in sce/ */

#endif /* SCE_LIBC_STDLIB_H */
