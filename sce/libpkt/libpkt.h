/*
 * sce/libpkt/libpkt.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (libpkt.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBPKT_LIBPKT_H
#define SCE_LIBPKT_LIBPKT_H

void sceVif1PkAddGsData(int **a0, long long a1); /* definition in sce/ */
void sceVif1PkAlign(int *a0, int a1, int a2);    /* definition in sce/ */
int sceVif1PkCloseDirectCode(void *a0);          /* definition in sce/ */
void sceVif1PkCloseGifTag(void *a0);             /* definition in sce/ */
void sceVif1PkCnt(void *a0, int a1);             /* definition in sce/ */
void sceVif1PkEnd(int **a0, int a1);             /* definition in sce/ */
void sceVif1PkInit(int *a0, int a1);             /* definition in sce/ */
void sceVif1PkOpenDirectCode(void *a0, int a1);  /* definition in sce/ */
int sceVif1PkReset(int *a0);                     /* definition in sce/ */
int *sceVif1PkTerminate(int **a0);               /* definition in sce/ */

#endif /* SCE_LIBPKT_LIBPKT_H */
