/*
 * sce/libkernl/sifdev.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (sifdev.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBKERNL_SIFDEV_H
#define SCE_LIBKERNL_SIFDEV_H

int sceClose(unsigned int fd);                         /* definition in sce/ */
int sceLseek(unsigned int fd, int offset, int whence); /* definition in sce/ */
int sceOpen(unsigned char *name, int flags, ...);      /* definition in sce/ */
int sceRead(int fd, void *buf, int nbyte);             /* definition in sce/ */
int sceWrite(int fd, void *buf, int nbyte);            /* definition in sce/ */

#endif /* SCE_LIBKERNL_SIFDEV_H */
