/*
 * sce/libc/stdlib.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called stdlib.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_STDLIB_H
#define SCE_LIBC_STDLIB_H

struct _reent;

double atof(const char *ascii);                        /* definition in sce/ */
int atoi(void *a0);                                    /* definition in sce/ */
void qsort(void *base, unsigned int n, unsigned int size, int (*cmp)()); /* definition in sce/ */
int rand(void);                                        /* definition in sce/ */
double strtod(const char *s00, char **se);             /* definition in sce/ */
long long strtol(void *a0, int a1, int a2);            /* definition in sce/ */
extern int __mb_cur_max;                               /* definition in sce/ (locale.c) */

#define MB_CUR_MAX __mb_cur_max

/* mprec.o's power-of-ten tables (newlib mprec.h names them tens, bigtens and
   tinytens; MAIN.MAP lists the three globals). */
extern const double __mprec_tens[];
extern const double __mprec_bigtens[];
extern const double __mprec_tinytens[];
void abort(void);                                                    /* definition in sce/ */
long long strtoul(void *a0, int a1, int a2);                         /* definition in sce/ */
void *_malloc_r(void *reent_ptr, int bytes);                         /* definition in sce/ */
void _free_r(int *self, void *mem);                                  /* definition in sce/ */
void *_realloc_r(void *reent_ptr, void *oldmem, unsigned int bytes); /* definition in sce/ */
void *_calloc_r(void *rptr, unsigned int n, unsigned int elem_size); /* definition in sce/ */

unsigned long _strtoul_r(struct _reent *rptr, const char *nptr, char **endptr,
                         int base); /* definition in sce/ */

#endif /* SCE_LIBC_STDLIB_H */
