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

/* what sceIpuStopDMA saves and sceIpuRestartDMA puts back: the IPU's input
 * channel (D4) and output channel (D3) registers, the bit position and the
 * control word; the fields are named after the registers they hold */
typedef struct { /* field names derived */
    unsigned int d4madr;
    unsigned int d4tadr;
    unsigned int d4qwc;
    unsigned int d4chcr;
    unsigned int d3madr;
    unsigned int d3qwc;
    unsigned int d3chcr;
    unsigned int ipubp;
    unsigned int ipuctrl;
} sceIpuDmaEnv;

void sceIpuStopDMA(sceIpuDmaEnv *env);          /* definition in sce/ */
void sceIpuInit(void);                          /* definition in sce/ */
void sceIpuRestartDMA(sceIpuDmaEnv *env);       /* definition in sce/ */
int sceIpuSync(int a0, unsigned short timeout); /* definition in sce/ */

#endif /* SCE_LIBIPU_LIBIPU_H */
