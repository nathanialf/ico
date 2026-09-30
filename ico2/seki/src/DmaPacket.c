#include "DmaPacket.h"

/* the double-buffered packet area every packet builder writes into (MAIN.MAP
   global); each consumer keeps its own view of the record */
DpkCtl PacketBufferStruct = {0};

extern int D_0063A43C;

/* the DMA memory use debug's meter draws (MAIN.MAP global, the TU's .sdata) */
int used_dma_memory = 0;

void dpk_Init(void)
{
    PacketBufferStruct.cur = 0;
    PacketBufferStruct.buf[0] =
        (int *)((int)iosMallocDebug(D_0063A43C, 0x80000, "src/DmaPacket.c", 134) | 0x30000000);
    PacketBufferStruct.buf[1] =
        (int *)((int)iosMallocDebug(D_0063A43C, 0x80000, "src/DmaPacket.c", 135) | 0x30000000);
    PacketBufferStruct.ptr = PacketBufferStruct.buf[PacketBufferStruct.cur];
}

void dpk_SwapBuffer(void)
{
    int i = PacketBufferStruct.cur ^ 1;
    PacketBufferStruct.cur = i;
    PacketBufferStruct.ptr = PacketBufferStruct.buf[i];
    PacketBufferStruct._14 = 0;
    PacketBufferStruct._18 = 0;
    PacketBufferStruct._1C = 0;
}

int dpk_CheckBufferSize(void)
{
    int idx = ((int *)&PacketBufferStruct)[0];
    int adj_cur = ((int *)&PacketBufferStruct)[4] - 0x80000;
    int end_off = ((int *)&PacketBufferStruct + idx)[1];
    return (end_off - adj_cur) >> 4;
}
