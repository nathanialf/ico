/*
 * sce/libipu/libipu.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (libipu.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBIPU_LIBIPU_H
#define SCE_LIBIPU_LIBIPU_H

void sceIpuStopDMA(void *a0);    /* definition in sce/ */
void sceIpuInit(void);           /* definition in sce/ */
void sceIpuRestartDMA(void *a0); /* definition in sce/ */
int sceIpuSync(int a0);          /* definition in sce/ */

#endif /* SCE_LIBIPU_LIBIPU_H */
