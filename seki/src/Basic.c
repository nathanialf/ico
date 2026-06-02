#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", dma_init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", matrix_init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", malloc_MemCpy);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", malloc_SetPartition);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", malloc_GetPartition);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", mallocseki);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", freeseki);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", resetmallocseki);

void mallocsekistage(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", reallocseki);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", func_001F3DF0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", func_001F3E18);
