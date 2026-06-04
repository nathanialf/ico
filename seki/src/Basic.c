#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", dma_init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", matrix_init);

extern void *D_00629C70;
extern void func_00118AA0(void *a0);

void malloc_MemCpy(void) {
    D_00629C70 = (void *)0x70000000;
    func_00118AA0((void *)0x70000000);
}

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

extern int iosMallocCheckLeak2(int a0);
int resetmallocseki(int a0) {
    if (a0) {
        return iosMallocCheckLeak2(a0);
    }
}

void mallocsekistage(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", reallocseki);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", func_001F3DF0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Basic", func_001F3E18);
