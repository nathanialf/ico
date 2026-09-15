/* Vendor SCE library run.  The archive attribution (libdma.a) comes from
 * MAIN.MAP's symbol table.  The January link carried a different revision of
 * this archive, so its member spans do not tile this run: the per-member
 * partition is NOT verified, and this file is the whole run. */
#include "common.h"

extern int D_0054A320[];

int sceDmaGetChan(unsigned int a0)
{
    if (a0 < 0xA) {
        return D_0054A320[a0];
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaReset);

extern int D_0054A348[];

int sceDmaDebug(int a0)
{
    int old = D_0054A348[0];
    D_0054A348[0] = a0;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaPutEnv);

typedef struct {
    int w[5];
} DmaEnv;

extern DmaEnv D_0054A3B8;

DmaEnv *sceDmaGetEnv(DmaEnv *a0)
{
    *a0 = D_0054A3B8;
    return a0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaPutStallAddr);
INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaSend);
INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaSendN);
INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaSendI);
INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaRecv);
INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaRecvN);
INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaRecvI);
INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaSync);
INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaWatch);

int sceDmaPause(void *a0)
{
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}

int sceDmaRestart(void *a0)
{
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}
