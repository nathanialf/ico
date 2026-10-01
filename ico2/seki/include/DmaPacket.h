/*
 * ico2/seki/include/DmaPacket.h
 *
 * The declarations of what DmaPacket.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DMAPACKET_H
#define DMAPACKET_H

/* a packet address: the builders write doublewords through it and do their
   address arithmetic in bytes */
typedef union { /* field names derived */
    unsigned long long *d;
    char *c;
    int *i;
} DpkPtr; /* derived name */

/* the packet buffer control record: the current bank, the two banks, the
   open DMA tag, the write pointer, the open tail tag, the open GIF tag and the
   packet end */
typedef struct { /* field names derived */
    int cur;
    int *buf[2];
    DpkPtr dma;
    DpkPtr ptr;
    DpkPtr tail;
    DpkPtr gif;
    DpkPtr end;
} DpkCtl; /* derived name */

extern DpkCtl PacketBufferStruct;
extern int used_dma_memory;
void dpk_Init(void);
void dpk_SwapBuffer(void);
unsigned int dpk_CheckBufferSize(void);

#endif /* DMAPACKET_H */
