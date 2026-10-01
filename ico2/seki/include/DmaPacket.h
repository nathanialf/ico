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

/* a DMA tag and the two VIF codes that ride in its upper half */
typedef struct { /* field names derived */
    long long tag;
    int vif[2];
} DpkTag; /* derived name */

/* the head of a packet the VIF passes to the GIF (DIRECT) or unpacks into VU
   memory (UNPACK): four VIF codes, the last the DIRECT or the UNPACK, then
   the GIF tag */
typedef struct { /* field names derived */
    int vif[4];
    long long tag[2];
} DpkHead; /* derived name */

/* one A+D register write of a GIF packet: the value, then the register
   address */
typedef struct { /* field names derived */
    long long data;
    long long addr;
} DpkRegAD; /* derived name */

extern DpkCtl PacketBufferStruct;
extern int used_dma_memory;
void dpk_Init(void);
void dpk_SwapBuffer(void);
unsigned int dpk_CheckBufferSize(void);

#endif /* DMAPACKET_H */
