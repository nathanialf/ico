/*
 * sce/libpkt/libpkt.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libpkt.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBPKT_LIBPKT_H
#define SCE_LIBPKT_LIBPKT_H

void sceVif1PkAddGsData(int **a0, long long a1);                       /* definition in sce/ */
void sceVif1PkAlign(int *a0, int a1, int a2);                          /* definition in sce/ */
void sceVif1PkCloseDirectCode();                                       /* dominant spelling at 1 sites */
void sceVif1PkCloseGifTag(void *a0);                                   /* definition in sce/ */
void sceVif1PkCnt(void *a0, int a1);                                   /* definition in sce/ */
void sceVif1PkEnd(int **a0, int a1);                                   /* definition in sce/ */
void sceVif1PkInit(int *a0, int a1);                                   /* definition in sce/ */
void sceVif1PkOpenDirectCode(void *a0, int a1);                        /* definition in sce/ */
int sceVif1PkReset(int *a0);                                           /* definition in sce/ */
int *sceVif1PkTerminate(int **a0);                                     /* definition in sce/ */

#endif /* SCE_LIBPKT_LIBPKT_H */
