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

int fstat(void *a0, void *a1); /* definition in sce/ */

#endif /* SCE_LIBC_SYS_STAT_H */
