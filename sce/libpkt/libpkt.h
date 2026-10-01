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

/* The VIF1 packet every libpkt call builds in place: the next word to write,
   the buffer start, and the DMA tag, DIRECT code and GIF tag the open calls
   leave for the close calls to patch with their counts. */
typedef struct {                /* field names derived */
    unsigned int *cur;          /* 0x00, the next word to write */
    unsigned int *base;         /* 0x04, where sceVif1PkReset rewinds to */
    unsigned int *dmaTag;       /* 0x08, the open DMA tag */
    unsigned int *vifCode;      /* 0x0C, the open DIRECT code */
    char pad10[4];              /* 0x10 */
    unsigned int *gifTag;       /* 0x14, the open GIF tag */
} sceVif1Packet;

typedef unsigned int u_long128 __attribute__((mode(TI)));

void sceVif1PkAddGsData(sceVif1Packet *pkt, long long data);           /* definition in sce/ */
void sceVif1PkAlign(sceVif1Packet *pkt, int bit, int pos);             /* definition in sce/ */
int sceVif1PkCloseDirectCode(sceVif1Packet *pkt);                      /* definition in sce/ */
void sceVif1PkCloseGifTag(sceVif1Packet *pkt);                         /* definition in sce/ */
void sceVif1PkCnt(sceVif1Packet *pkt, int code);                       /* definition in sce/ */
void sceVif1PkEnd(sceVif1Packet *pkt, int code);                       /* definition in sce/ */
void sceVif1PkInit(sceVif1Packet *pkt, unsigned int *buf);             /* definition in sce/ */
void sceVif1PkOpenDirectCode(sceVif1Packet *pkt, int irq);             /* definition in sce/ */
void sceVif1PkOpenGifTag(sceVif1Packet *pkt, u_long128 tag);           /* definition in sce/ */
unsigned int *sceVif1PkReset(sceVif1Packet *pkt);                      /* definition in sce/ */
unsigned int *sceVif1PkTerminate(sceVif1Packet *pkt);                  /* definition in sce/ */

#endif /* SCE_LIBPKT_LIBPKT_H */
