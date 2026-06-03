#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", display_texture);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", iosCdvdBackGroundReadJimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrNext);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrJump);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuNext);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuJump);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuDisp);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuManager);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuUndisp);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173D00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173D48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173D68);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173DB0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173F48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173FA8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_001741B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_001743B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00174580);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00174650);

extern int D_00286810[];
extern void iosMsgSend(void *a0, void *a1, int a2);

void func_00174698(void *a0) {
    *(int *)a0 = 0;
    iosMsgSend(D_00286810, a0, 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_001746B8);
