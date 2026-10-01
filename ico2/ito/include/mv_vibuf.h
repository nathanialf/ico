/*
 * ico2/ito/include/mv_vibuf.h
 *
 * The declarations of what mv_vibuf.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MV_VIBUF_H
#define MV_VIBUF_H

#include "typedef.h"

/* The video-input ring: a run of 2048-byte sectors that the CD DMA fills and
   the MPEG demuxer drains.  Byte counts are (sector << 11) + a partial
   offset into the sector the writer is part way through. */
typedef struct ViBuf {   /* field names derived */
    char *data;          /* 0x00 ring buffer, 2048 bytes per sector */
    char *dmaTag;        /* 0x04 uncached-accel DMA tag list over the ring */
    int nSector;         /* 0x08 ring size in sectors */
    int rdSector;        /* 0x0C sector the reader is on */
    int nReady;          /* 0x10 whole sectors written but not yet read */
    int wOffset;         /* 0x14 bytes written into the sector after those */
    int size;            /* 0x18 ring size in bytes (nSector << 11) */
    int inMadr;          /* 0x1C, the IPU input channel's MADR, TADR, QWC and
                            CHCR viBufStopDMA saves */
    int inTadr;          /* 0x20 */
    int inQwc;           /* 0x24 */
    int inChcr;          /* 0x28 */
    int outMadr;         /* 0x2C, the IPU output channel's MADR, QWC and CHCR */
    int outQwc;          /* 0x30 */
    int outChcr;         /* 0x34 */
    unsigned int bitPos; /* 0x38 IPU_BP saved by viBufStopDMA */
    int ipuCtrl;         /* 0x3C, IPU_CTRL saved by viBufStopDMA */
    int sema;            /* 0x40 */
    int running;         /* 0x44 the ring's DMA chain is armed */
    long long total;     /* 0x48 bytes handed to the ring since the last reset */
    ViTs *ts;            /* 0x50 timestamp ring */
    int tsMax;           /* 0x54 timestamp ring capacity */
    int tsCount;         /* 0x58 timestamps live in it */
    int tsWr;            /* 0x5C index the next timestamp goes to */
    char created;        /* 0x60 */
} ViBuf; /* derived name */

int viBufAddDMA(ViBuf *self);
void viBufBeginPut(ViBuf *self, void **addr1, int *size1, void **addr2, int *size2);
int viBufCount(ViBuf *self);
int viBufCreate(ViBuf *self);
int viBufDelete(ViBuf *self);
void viBufEndPut(ViBuf *self, int n);
void viBufFlush(ViBuf *self);
int viBufGetTs(ViBuf *self, ViTs *out);
int viBufPutTs(ViBuf *self, ViTs *ts);
int viBufReset(ViBuf *self);
int viBufRestartDMA(ViBuf *self);
int viBufStopDMA(ViBuf *self);

#endif /* MV_VIBUF_H */
