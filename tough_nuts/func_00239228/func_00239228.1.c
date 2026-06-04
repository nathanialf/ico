#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_002388F0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecEndPut);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", sendToIOP2area);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecSendToIOP);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", pcmCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecDelete);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecReset);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecIsPreset);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecStart);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecPause);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecResume);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00238FB0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_002390F0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239188);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_002391E8);

extern float D_00629B34, D_00629B38;

int func_00239228(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float a = -133.0f;
    float b = D_00629B34;
    float c = D_00629B38;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239250);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239290);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239348);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_002393A8);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239438);
