/*
 * sce/libdma/libdma.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libdma.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBDMA_LIBDMA_H
#define SCE_LIBDMA_LIBDMA_H

/* The channel-environment record sceDmaPutEnv writes to D_CTRL, D_RBOR
   and D_RBSR. */
typedef struct {
    unsigned char chan; /* 0x00 channel number */
    unsigned char b01;  /* 0x01 */
    unsigned char b02;  /* 0x02 */
    unsigned char b03;  /* 0x03 release level, 0 = off */
    unsigned short h04; /* 0x04 */
    unsigned short h06; /* 0x06 */
    unsigned short h08; /* 0x08 */
    unsigned short h0A; /* 0x0A */
    void *rbadr;        /* 0x0C ring buffer address, to D_RBOR */
    int rbsize;         /* 0x10 ring buffer size, to D_RBSR */
} DmaEnv;

/* A channel's register block, CHCR to TADR. */
typedef struct DmaChan {
    volatile int chcr; /* 0x00 */
    int pad0[3];
    int madr; /* 0x10 */
    int pad1[3];
    int qwc; /* 0x20 */
    int pad2[3];
    int tadr; /* 0x30 */
} DmaChan;

int sceDmaGetChan(unsigned int a0);              /* definition in sce/ */
int sceDmaReset(int mode);                       /* definition in sce/ */
int sceDmaPutEnv(DmaEnv *env);                   /* definition in sce/ */
void sceDmaSend(DmaChan *ch, unsigned int addr); /* definition in sce/ */
int sceDmaSync(DmaChan *ch, int mode, int n);    /* definition in sce/ */

#endif /* SCE_LIBDMA_LIBDMA_H */
