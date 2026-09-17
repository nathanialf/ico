/*
 * sce/libpad/libpad.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libpad.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBPAD_LIBPAD_H
#define SCE_LIBPAD_LIBPAD_H

int scePadGetButtonMask(int a0, int a1);                               /* definition in sce/ */
int scePadGetModVersion(void);                                         /* definition in sce/ */
int scePadInit2(int a0);                                               /* definition in sce/ */
int scePadRead(int a0, int a1, int a2);                                /* definition in sce/ */
int scePadSetActDirect(int a0, int a1, unsigned char *a2);             /* definition in sce/ */

#endif /* SCE_LIBPAD_LIBPAD_H */
