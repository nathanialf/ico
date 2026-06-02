#include "common.h"

void func_0023B4D0(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufReset);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufBeginPut);

extern int D_0062BE90;
extern int D_0062C2DC;

void viBufEndPut(void) {
    D_0062BE90 = 0;
    D_0062C2DC = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufAddDMA);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufStopDMA);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufRestartDMA);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufFlush);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufModifyPts);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufGetTs);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufDelete);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufCount);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufPutTs);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023B920);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023B970);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023B9D0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023BA60);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023BAB8);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023BAF0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023BB20);
