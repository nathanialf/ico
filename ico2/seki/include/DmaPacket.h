/*
 * ico2/seki/include/DmaPacket.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what DmaPacket.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DMAPACKET_H
#define DMAPACKET_H

/* a packet address: the builders write doublewords through it and do their
   address arithmetic in bytes */
typedef union {
    unsigned long long *d;
    char *c;
    int *i;
} DpkPtr;

/* the packet buffer control record: the current bank, the two banks, the
   open DMA tag, the write pointer, the open tail tag, the open GIF tag and the
   packet end */
typedef struct {
    int cur;
    int *buf[2];
    DpkPtr dma;
    DpkPtr ptr;
    DpkPtr tail;
    DpkPtr gif;
    DpkPtr end;
} DpkCtl;

extern DpkCtl PacketBufferStruct;
extern int used_dma_memory;
void dpk_Init(void);
void dpk_SwapBuffer(void);
unsigned int dpk_CheckBufferSize(void);

#endif /* DMAPACKET_H */
