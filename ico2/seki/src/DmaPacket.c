#include "DmaPacket.h"
#include "ios.h"

/* the double-buffered packet area every packet builder writes into (MAIN.MAP
   global); each consumer keeps its own view of the record */
DpkCtl PacketBufferStruct = {0};

/* the DMA memory use debug's meter draws (MAIN.MAP global, the TU's .sdata) */
int used_dma_memory = 0;

void dpk_Init(void)
{
    PacketBufferStruct.cur = 0;
    PacketBufferStruct.buf[0] =
        (int *)((int)iosMallocDebug(ios_partition_common, 0x80000, "src/DmaPacket.c", 134) |
                0x30000000);
    PacketBufferStruct.buf[1] =
        (int *)((int)iosMallocDebug(ios_partition_common, 0x80000, "src/DmaPacket.c", 135) |
                0x30000000);
    PacketBufferStruct.ptr.i = PacketBufferStruct.buf[PacketBufferStruct.cur];
}

void dpk_SwapBuffer(void)
{
    int i = PacketBufferStruct.cur ^ 1;
    PacketBufferStruct.cur = i;
    PacketBufferStruct.ptr.i = PacketBufferStruct.buf[i];
    PacketBufferStruct.tail.c = 0;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.end.c = 0;
}

unsigned int dpk_CheckBufferSize(void)
{
    int idx = PacketBufferStruct.cur;
    int adj_cur = (int)PacketBufferStruct.ptr.c - 0x80000;
    int end_off = (int)PacketBufferStruct.buf[idx];
    return (end_off - adj_cur) >> 4;
}
