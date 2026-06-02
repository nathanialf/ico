#include "common.h"

int free_buf(int a0) {
    return *(int *)(a0 + 0xB8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoDecCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoDecBeginPut);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoDecEndPut);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoDecFlush);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", decBitStrm0);
