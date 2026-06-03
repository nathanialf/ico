#include "common.h"

typedef struct { int w[6]; } AssertRec;
extern AssertRec D_006DE110[];

int debug_Assert(int a0) {
    return D_006DE110[a0].w[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_openLog);

extern int D_0062ACCC;

void debug_LogPrintf(void) {
    char buf[0x100];
    D_0062ACCC = -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_SaveDebugOptionFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_GetDebugOption);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_SetDmaCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_VariableInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_Load);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_MakeFont);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_makeBackImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_PrintCharacter);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_PrintFont);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_FlushFontWindow);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_FlushFont);

extern void debug_FlushFont(void);

void draw_batsu(void) {
    debug_FlushFont();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", draw_shikaku);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_brainBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_MakeBarString);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DrawBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DispBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_ResizeSnapShot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_WriteBMP);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_SnapShot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DispQW);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    char               f_C;  /* 0x0C */
    char               f_D;  /* 0x0D */
    char               f_E;  /* 0x0E */
    char               f_F;  /* 0x0F */
    unsigned int       f_10;  /* 0x10 */
    short              f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
} S_006EB6D0;  /* stride 0x1C */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060D910;  /* stride 0x4 */

/* end struct shapes */
