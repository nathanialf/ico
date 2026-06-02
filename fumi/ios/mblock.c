#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", new_mblock_node);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", reuse_mblock1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", init_mblock);

void new_segment(int *a0) {
    a0[0] = 0;
    a0[1] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", reuse_mblock);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", strdup_mblock);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", func_00135EA0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", func_00135F88);
