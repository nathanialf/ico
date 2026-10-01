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

/* the packet buffer control record: the current bank, the two banks, the
   write pointer and three words dpk_SwapBuffer clears */
typedef struct {
    int cur;     /* 0x00 */
    int *buf[2]; /* 0x04 0x08 */
    int _0C;
    int *ptr; /* 0x10 */
    int *_14;
    int *_18;
    int *_1C;
} DpkCtl;

extern DpkCtl PacketBufferStruct;
extern int used_dma_memory;
void dpk_Init(void);
void dpk_SwapBuffer(void);
int dpk_CheckBufferSize(void);

#endif /* DMAPACKET_H */
