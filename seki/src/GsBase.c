#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_Init);

typedef struct { unsigned char pad[0x10]; unsigned long long *cur; } GsBaseRed;
extern GsBaseRed D_004C3850;

void gsb_Reduction(int a0) {
    int new_var;
    unsigned long long *p, *q;
    if (a0) {
        a0 = 0x50000;
        new_var = 0; do { } while (new_var);
    } else {
        a0 = 0x30000;
    }
    p = D_004C3850.cur;
    *(volatile unsigned long long *)p = a0;
    p++;
    *(unsigned long long * volatile *)&D_004C3850.cur = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x47;
    D_004C3850.cur = q;
}

void gsb_KeepFrameBuffer(int a0) {
    unsigned long long *p, *q;
    int new_var;
    unsigned long long tag;
    if (a0) {
        tag = 0x300000C0;
        new_var = 0; do { } while (new_var);
    } else {
        tag = 0x1300000C0;
    }
    p = D_004C3850.cur;
    *(volatile unsigned long long *)p = tag;
    p++;
    *(unsigned long long * volatile *)&D_004C3850.cur = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x4E;
    D_004C3850.cur = q;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_fade);

int gsb_scissorOnDemo(volatile int *a0) {
    if (a0[2] < 0) return 0;
    if (a0[2] > 0x0FFFFFF0) return 0;
    if (a0[0] < 0) return 0;
    if (a0[0] > 0xFFF0) return 0;
    if (a0[1] < 0) return 0;
    return a0[1] <= 0xFFF0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_controlBrightness);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_antiAlias);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_setNormalReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_setSemitransReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_setSpecularReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_setParticleReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_MakeCommonMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetGsDefault);

extern int dpk_CheckBufferSize(void);
extern void gif_SpriteSensitiveOffset(int a0);
extern void gif_SpriteOrg(int a0, long long a1);
extern void func_0010FB08(void);

void gsb_PostEffect(void) {
    dpk_SwapBuffer();
    gif_SpriteSensitiveOffset(dpk_CheckBufferSize());
    gif_SpriteOrg(0x47, 0x50000);
    gif_SpriteOrg(0x4E, 0x300000C0);
    gif_SpriteOrg(0x4A, 0);
    gif_SpriteOrg(0x3B, 0x8000000080LL);
    func_0010FB08();
}

void gsb_InitGSSystem(void) {
    dpk_SwapBuffer();
    gif_SpriteSensitiveOffset(dpk_CheckBufferSize());
    gif_SpriteOrg(0x47, 0x5140D);
    gif_SpriteOrg(0x4E, 0x300000C0);
    gif_SpriteOrg(0x4A, 0);
    gif_SpriteOrg(0x3B, 0x810000807FLL);
    func_0010FB08();
}

void gsb_UpdateGSSystem(void) {
    dpk_SwapBuffer();
    gif_SpriteSensitiveOffset(dpk_CheckBufferSize());
    gif_SpriteOrg(0x47, 0x5C000);
    gif_SpriteOrg(0x4E, 0x1300000C0LL);
    gif_SpriteOrg(0x4A, 0);
    gif_SpriteOrg(0x3B, 0x8000000080LL);
    func_0010FB08();
}

void gsb_ResetGSSystem(void) {
    dpk_SwapBuffer();
    gif_SpriteSensitiveOffset(dpk_CheckBufferSize());
    gif_SpriteOrg(0x47, 0x50000);
    gif_SpriteOrg(0x4E, 0x1300000C0LL);
    gif_SpriteOrg(0x4A, 0);
    gif_SpriteOrg(0x3B, 0x8000000080LL);
    func_0010FB08();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetVSMatrixSub);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetVSMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_ClipBox);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_StageSettingTool);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_StageSetting);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetBGColor);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_GetBGColor);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0054E7E0;  /* stride 0x10 */

/* end struct shapes */
