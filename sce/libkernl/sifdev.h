/*
 * sce/libkernl/sifdev.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called sifdev.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBKERNL_SIFDEV_H
#define SCE_LIBKERNL_SIFDEV_H

int sceClose(unsigned int fd);                     /* definition in sce/ */
int sceLseek(unsigned int fd, int offset, int whence); /* definition in sce/ */
int sceOpen(unsigned char *name, int flags, ...);  /* definition in sce/ */
int sceRead(int fd, void *buf, int nbyte);         /* definition in sce/ */
int sceWrite(int fd, void *buf, int nbyte);        /* definition in sce/ */

#endif /* SCE_LIBKERNL_SIFDEV_H */
