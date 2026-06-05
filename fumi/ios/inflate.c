#include "common.h"

void huft_build(int *a0, int a1) {
    a0[68] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_codes);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_stored);

extern int D_0062BF84;

int inflate_fixed(void) {
    return D_0062BF84;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_dynamic);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_start);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", close_inflate_handler);

typedef struct { char f0; char pad[0x12B]; } InfEntry;
extern InfEntry D_0069F800[];

void inflate(void) {
    int i;
    for (i = 6; i >= 0; i--) {
        D_0069F800[i].f0 = 0;
    }
    D_0062BF84 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", open_inflate_handler);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", fill_inbuf);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", huft_free);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00134550);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001347B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001350C8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00135118);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001351E0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001356A8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00135738);
