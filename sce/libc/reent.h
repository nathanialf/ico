/*
 * sce/libc/reent.h
 *
 * The record shapes this archive's members share, under the public name the
 * archive's own sources use for this header.  The shapes follow the members'
 * loads and stores; nothing here is copied from an SDK header.
 */
#ifndef SCE_LIBC_REENT_H
#define SCE_LIBC_REENT_H

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

typedef struct {
    unsigned char *base; /* 0x0 */
    int size;            /* 0x4 */
} Sbuf;

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

/* The reentrancy record every member
 * of this archive reaches through the stream record's data field, defined after
 * the stream record it holds three of. */
struct Reent;

/* The chain of stream record blocks
 * the reentrancy record heads. */
typedef struct Glue {
    struct Glue *next; /* 0x0 */
    int niobs;         /* 0x4 */
    struct Fil *iobs;  /* 0x8 */
} Glue;

/* The stream record the archive's stdio members share. */
typedef struct Fil {
    unsigned char *p; /* 0x00 */
    int r;            /* 0x04 */
    int w;            /* 0x08 */
    short flags;      /* 0x0C */
    short file;       /* 0x0E */
    Sbuf bf;          /* 0x10 */
    int lbfsize;      /* 0x18 */
    void *cookie;     /* 0x1C, the argument the four stream calls below take */
    int (*read)(void *cookie, char *buf, int n);        /* 0x20 */
    int (*write)(void *cookie, const char *buf, int n); /* 0x24 */
    long (*seek)(void *cookie, long off, int whence);   /* 0x28 */
    int (*close)(void *cookie);                         /* 0x2C */
    Sbuf ub;                                            /* 0x30 */
    unsigned char *up;                                  /* 0x38 */
    int ur;                                             /* 0x3C */
    unsigned char ubuf[3];                              /* 0x40 */
    unsigned char nbuf[1];                              /* 0x43 */
    Sbuf lb;                                            /* 0x44 */
    int blksize;                                        /* 0x4C */
    int offset;                                         /* 0x50 */
    struct Reent *data;                                 /* 0x54 */
} Fil;

/* newlib's big integer (sys/reent.h): mprec's Balloc keeps a free list of
 * them per size k in the reentrancy record, dtoa caches its result string in
 * one. */
struct _Bigint {
    struct _Bigint *_next; /* 0x00 */
    int _k;                /* 0x04 */
    int _maxwds;           /* 0x08 */
    int _sign;             /* 0x0C */
    int _wds;              /* 0x10 */
    unsigned int _x[1];    /* 0x14 */
};

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
    struct _Bigint *result;     /* 0x040, dtoa's cached result */
    int result_k;               /* 0x044 */
    struct _Bigint *p5s;        /* 0x048, mprec's powers of 5 */
    struct _Bigint **freelist;  /* 0x04C, Balloc's lists by k */
    int cvtlen;                 /* 0x050 */
    char *cvtbuf;               /* 0x054 */
    unsigned int rand_next;     /* 0x058 */
    char *strtok_last;          /* 0x05C */
    char pad060[0x178];         /* 0x060 */
    Glue glue;                  /* 0x1D8 */
    Fil sf[3];                  /* 0x1E4 */
} Reent;

extern Reent *_impure_ptr;                            /* definition in sce/ (reent/impure.c) */
int _close_r(Reent *ptr, int fd);                     /* definition in sce/ */
long _read_r(Reent *ptr, int fd, void *buf, int cnt); /* definition in sce/ */
long _write_r(Reent *ptr, int fd, const void *buf, int cnt); /* definition in sce/ */
long _lseek_r(Reent *ptr, int fd, long pos, int whence);     /* definition in sce/ */

struct stat;

int _fstat_r(Reent *ptr, int fd, struct stat *pstat); /* definition in sce/ */
int _sbrk_r(Reent *ptr, int incr);                    /* definition in sce/ */
int _kill_r(Reent *ptr, int pid, int sig);            /* definition in sce/ */
int _getpid_r(Reent *ptr);                            /* definition in sce/ */

#endif /* SCE_LIBC_REENT_H */
