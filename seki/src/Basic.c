#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", dma_init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", matrix_init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", malloc_MemCpy);

extern void func_002604B8(void);

void malloc_SetPartition(void) {
    func_002604B8();
}

extern int D_0062BA60;

void malloc_GetPartition(int a0) {
    D_0062BA60 = a0;
}

int mallocseki(void) {
    return D_0062BA60;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", freeseki);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", resetmallocseki);

void mallocsekistage(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", reallocseki);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", func_001F3DF0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", func_001F3E18);
