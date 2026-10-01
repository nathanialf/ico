/*
 * sce/libc/sys/stat.h
 *
 * PUBLIC NEWLIB NAMING RUNG, as sce/libc/stdio.h: newlib's header of this
 * name declares fstat, which libkernl's glue.c supplies.
 * Each declaration is the definition's in sce/ where that is C, else the
 * spelling its callers carry.  Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_SYS_STAT_H
#define SCE_LIBC_SYS_STAT_H

/* newlib's struct stat for this target (eabi: the spare and block fields
   follow the times; off_t, time_t and long are 64-bit) */
struct stat {
    short st_dev;          /* 0x00 */
    unsigned short st_ino; /* 0x02 */
    unsigned int st_mode;  /* 0x04 */
    unsigned short st_nlink;
    unsigned short st_uid;
    unsigned short st_gid;
    short st_rdev;
    long st_size;          /* 0x10 */
    long st_atime;
    long st_spare1;
    long st_mtime;
    long st_spare2;
    long st_ctime;
    long st_spare3;
    long st_blksize;       /* 0x48 */
    long st_blocks;
    long st_spare4[2];
};

#define S_IFMT 0xF000
#define S_IFCHR 0x2000
#define S_IFREG 0x8000

int fstat(int fd, struct stat *st); /* definition in sce/ */

#endif /* SCE_LIBC_SYS_STAT_H */
