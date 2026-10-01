/*
 * sce/libc/reent.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header.  This
 * file carries the record shapes that this archive's members all carried a
 * private copy of; its name is the public one the archive's own sources use.
 * The shapes are read back from the ROM's loads and stores, not copied from
 * any SDK header.
 */
#ifndef SCE_LIBC_REENT_H
#define SCE_LIBC_REENT_H

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 56 TUs. */
typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct {
    unsigned char *base; /* 0x0 */
    int size;            /* 0x4 */
} Sbuf;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 56 TUs. */
typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: the reentrancy record every member
 * of this archive reaches through the stream record's data field, defined after
 * the stream record it holds three of. */
struct Reent;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: the chain of stream record blocks
 * the reentrancy record heads. */
typedef struct Glue {
    struct Glue *next; /* 0x0 */
    int niobs;         /* 0x4 */
    struct Fil *iobs;  /* 0x8 */
} Glue;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for the archive's stream
 * members, which carried six divergent local copies of it. */
typedef struct Fil {
    unsigned char *p; /* 0x00 */
    int r;            /* 0x04 */
    int w;            /* 0x08 */
    short flags;      /* 0x0C */
    short file;       /* 0x0E */
    Sbuf bf;          /* 0x10 */
    int lbfsize;      /* 0x18 */
    void *cookie;     /* 0x1C, the argument the four stream calls below take */
    int (*read)(void *cookie, char *buf, int n);    /* 0x20 */
    int (*write)(void *cookie, char *buf, int n);   /* 0x24 */
    int (*seek)(void *cookie, int off, int whence); /* 0x28 */
    int (*close)(void *cookie);                     /* 0x2C */
    Sbuf ub;                                        /* 0x30 */
    unsigned char *up;                              /* 0x38 */
    int ur;                                         /* 0x3C */
    unsigned char ubuf[3];                          /* 0x40 */
    unsigned char nbuf[1];                          /* 0x43 */
    Sbuf lb;                                        /* 0x44 */
    int blksize;                                    /* 0x4C */
    int offset;                                     /* 0x50 */
    struct Reent *data;                             /* 0x54 */
} Fil;

/* The reentrancy record, newlib's struct _reent: impure.c's _REENT_INIT sets
 * the three standard stream pointers, the locale name and the rand seed; the
 * members read the errno, the init flag, the cleanup hook and the glue. */
typedef struct Reent {
    int err;                    /* 0x000, the errno this reentrancy record carries */
    Fil *in, *out, *errs;       /* 0x004, the standard streams, &sf[0..2] */
    int inc;                    /* 0x010 */
    char emergency[25];         /* 0x014 */
    int current_category;       /* 0x030 */
    const char *current_locale; /* 0x034 */
    int sdidinit;               /* 0x038 */
    void *cleanup;              /* 0x03C */
    char pad040[0x18];          /* 0x040 */
    unsigned int rand_next;     /* 0x058 */
    char *strtok_last;          /* 0x05C */
    char pad060[0x178];         /* 0x060 */
    Glue glue;                  /* 0x1D8 */
    Fil sf[3];                  /* 0x1E4 */
} Reent;

extern Reent *_impure_ptr;                       /* definition in sce/ (reent/impure.c) */
int _close_r(int *self, int a1);                 /* definition in sce/ */
int _read_r(int *self, int a1, int a2, int a3);  /* definition in sce/ */
int _write_r(int *self, int a1, int a2, int a3); /* definition in sce/ */
int _lseek_r(int *self, int a1, int a2, int a3); /* definition in sce/ */
int _sbrk_r(int *self, int a1);                  /* definition in sce/ */

#endif /* SCE_LIBC_REENT_H */
