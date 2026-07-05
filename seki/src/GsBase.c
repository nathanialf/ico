#include "common.h"

typedef struct { unsigned char pad[0x10]; unsigned long long *cur; } GsBaseRed;
extern GsBaseRed D_004C3850;

typedef struct { int a, b, c, d; } GsAlphaEnt;
extern GsAlphaEnt D_0054E7E0[];

typedef union { unsigned long long *ptr; unsigned long long ull; } GsCurU;
typedef union { unsigned long long ul; unsigned long long *ptr; } GsQW;

void gsb_SetFrame(long long a0, long long a1, long long a2) {
    unsigned long long *p, *q;
    unsigned long long v;
    int idx;

    idx = (int)a1;
    p = D_004C3850.cur;
    *(volatile unsigned long long *)p = (a0 == 0);
    p++;
    *(unsigned long long * volatile *)&D_004C3850.cur = p;
    *(volatile unsigned long long *)p = 0x49;
    *(unsigned long long * volatile *)&D_004C3850.cur = p + 1;
    a1 = 0x42;
    v = (unsigned long long)D_0054E7E0[idx].a | ((unsigned long long)a2 << 32);
    v |= ((unsigned long long)D_0054E7E0[idx].c << 4)
       | ((unsigned long long)D_0054E7E0[idx].b << 2);
    v |= (unsigned long long)D_0054E7E0[idx].d << 6;
    *(volatile unsigned long long *)(p + 1) = v;
    *(unsigned long long * volatile *)&D_004C3850.cur = p + 2;
    q = p + 3;
    *(volatile unsigned long long *)(p + 2) = a1;
    D_004C3850.cur = q;
}


INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_Init);

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

extern void debug_assertMessage(const char *fmt, ...);
extern int D_00629F14, D_00629D60, D_00629D50, D_00629EBC;
extern char D_0054EAF0[], D_0054EB00[], D_0054EB10[], D_0054EB20[], D_00271270[];
extern void func_0023E168(void);
extern void func_00240AB8(void);
extern void matrix_init(void);
extern void malloc_MemCpy(void);
extern void func_00130000(void);
extern void func_0023EAC8(int a0);
extern void gsb_antiAlias(void *a0);
extern void dl_PopPriority(void);
extern void mallocsekistage(void);
extern void prim_InitFan2D(void);
extern void shadow_DispCancel(void);

void gsb_StageSettingTool(void) {
    D_00629D60 = 0;
    D_00629D50 = 0;
    if (D_00629F14 != 0) {
        func_0023E168();
        func_00240AB8();
        debug_assertMessage(D_0054EAF0);
        matrix_init();
        debug_assertMessage(D_0054EB00);
        malloc_MemCpy();
        debug_assertMessage(D_0054EB10);
        func_00130000();
        debug_assertMessage(D_0054EB20);
        func_0023EAC8(0);
        gsb_antiAlias(D_00271270);
        func_0023EAC8(0);
        dl_PopPriority();
        D_00629F14 = 0;
    } else {
        debug_assertMessage(D_0054EAF0);
        matrix_init();
        debug_assertMessage(D_0054EB10);
        func_00130000();
    }
    mallocsekistage();
    prim_InitFan2D();
    shadow_DispCancel();
    D_00629EBC = 1;
}

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
