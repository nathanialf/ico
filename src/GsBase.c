#include "common.h"

typedef struct { int a, b, c, d; } GsAlphaEnt;
typedef struct { unsigned char pad[0x10]; unsigned long long *cur; } GsBaseRed;

extern GsBaseRed D_004C7710;
extern GsAlphaEnt D_00554430[];

void gif_SetAlpha(long long a0, long long a1, long long a2) {
    unsigned long long *p, *q;
    unsigned long long v;
    int idx;

    idx = (int)a1;
    p = D_004C7710.cur;
    *(volatile unsigned long long *)p = (a0 == 0);
    p++;
    *(unsigned long long * volatile *)&D_004C7710.cur = p;
    *(volatile unsigned long long *)p = 0x49;
    *(unsigned long long * volatile *)&D_004C7710.cur = p + 1;
    a1 = 0x42;
    v = (unsigned long long)D_00554430[idx].a | ((unsigned long long)a2 << 32);
    v |= ((unsigned long long)D_00554430[idx].c << 4)
       | ((unsigned long long)D_00554430[idx].b << 2);
    v |= (unsigned long long)D_00554430[idx].d << 6;
    *(volatile unsigned long long *)(p + 1) = v;
    *(unsigned long long * volatile *)&D_004C7710.cur = p + 2;
    q = p + 3;
    *(volatile unsigned long long *)(p + 2) = a1;
    D_004C7710.cur = q;
}

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gif_MoveImage);

void gif_SetZTest(int a0) {
    int new_var;
    unsigned long long *p, *q;
    if (a0) {
        a0 = 0x50000;
        new_var = 0; do { } while (new_var);
    } else {
        a0 = 0x30000;
    }
    p = D_004C7710.cur;
    *(volatile unsigned long long *)p = a0;
    p++;
    *(unsigned long long * volatile *)&D_004C7710.cur = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x47;
    D_004C7710.cur = q;
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
    p = D_004C7710.cur;
    *(volatile unsigned long long *)p = tag;
    p++;
    *(unsigned long long * volatile *)&D_004C7710.cur = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x4E;
    D_004C7710.cur = q;
}

extern int D_00631C5C;
extern int D_00631C60;

void gsb_fade(int a0, int a1) {
    unsigned long long *p, *q;
    long long v;
    int x, y;

    x = (0x800 - D_00631C5C / 2) << 4;
    y = (0x800 - D_00631C60 / 2) << 4;
    if (a0 == 0) a1 = 0;
    v = (long long)x | ((long long)(a1 ? y + 8 : y) << 32);

    p = D_004C7710.cur;
    *(volatile unsigned long long *)p = v;
    p++;
    *(unsigned long long * volatile *)&D_004C7710.cur = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x18;
    D_004C7710.cur = q;
}

int _IsInScreen(volatile int *a0) {
    if (a0[2] < 0) return 0;
    if (a0[2] > 0x0FFFFFF0) return 0;
    if (a0[0] < 0) return 0;
    if (a0[0] > 0xFFF0) return 0;
    if (a0[1] < 0) return 0;
    return a0[1] <= 0xFFF0;
}

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetFrame);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_antiAlias);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_setNormalReg);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_setSemitransReg);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_setSpecularReg);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_setParticleReg);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_controlBrightness);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetGsDefault);

extern int dpk_CheckBufferSize(void);
extern void dpk_SwapBuffer();
extern void gif_EndPacketPath1(void);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_SpriteSensitiveOffset(int a0);

void gsb_PostEffect(void) {
    dpk_SwapBuffer();
    gif_SpriteSensitiveOffset(dpk_CheckBufferSize());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

void gsb_InitGSSystem(void) {
    dpk_SwapBuffer();
    gif_SpriteSensitiveOffset(dpk_CheckBufferSize());
    gif_SetGsReg(0x47, 0x5140D);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x810000807FLL);
    gif_EndPacketPath1();
}

void gsb_UpdateGSSystem(void) {
    dpk_SwapBuffer();
    gif_SpriteSensitiveOffset(dpk_CheckBufferSize());
    gif_SetGsReg(0x47, 0x5C000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

void gsb_ResetGSSystem(void) {
    dpk_SwapBuffer();
    gif_SpriteSensitiveOffset(dpk_CheckBufferSize());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_MakeCommonMatrix);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetVSMatrix);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_ClipBox);

extern void debug_StdPrintfDummy(const char *fmt, ...);
extern int D_00631C14, D_00631A60, D_00631A50, D_00631BBC;
extern char D_00554740[], D_00554750[], D_00554760[], D_00554770[], D_00274EF0[];
extern void sceGsResetPath(void);
extern void sceVpu0Reset(void);
extern void matrix_init(void);
extern void malloc_MemCpy(void);
extern void tex_Init(void);
extern void sceGsSyncV(int a0);
extern void gsb_antiAlias(void *a0);
extern void dl_PopPriority(void);
extern void mallocsekistage(void);
extern void prim_InitFan2D(void);
extern void shadow_DispCancel(void);
extern void stage_SetScale(void);

void gsb_StageSettingTool(void) {
    D_00631A60 = 0;
    D_00631A50 = 0;
    if (D_00631C14 != 0) {
        sceGsResetPath();
        sceVpu0Reset();
        debug_StdPrintfDummy(D_00554740);
        matrix_init();
        debug_StdPrintfDummy(D_00554750);
        malloc_MemCpy();
        debug_StdPrintfDummy(D_00554760);
        tex_Init();
        debug_StdPrintfDummy(D_00554770);
        sceGsSyncV(0);
        gsb_antiAlias(D_00274EF0);
        sceGsSyncV(0);
        dl_PopPriority();
        D_00631C14 = 0;
    } else {
        debug_StdPrintfDummy(D_00554740);
        matrix_init();
        debug_StdPrintfDummy(D_00554760);
        tex_Init();
    }
    mallocsekistage();
    prim_InitFan2D();
    shadow_DispCancel();
    stage_SetScale();
    D_00631BBC = 1;
}

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_StageSetting);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_SetBGColor);

INCLUDE_ASM("asm/nonmatchings/src/GsBase", gsb_GetBGColor);

