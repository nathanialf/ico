#include "common.h"

typedef struct { int x, y, w, h; } FR;




extern int func_001AA688();
extern void func_00100250();
extern int func_00100230();
extern void func_00100B40();
extern unsigned int D_00632A0C;
extern void func_00268DA0();
extern int func_0026527C();
extern void func_00247C30();
extern int D_00632A04;
typedef struct { int f_0; char _4[0x14]; } DbgSlot;
extern DbgSlot D_006E4890[];

int debug_Assert(int i) {
    return D_006E4890[i].f_0;
}

extern char D_006149A8[];
extern char D_006329F8[];
extern char D_00632A00[];
extern void func_001AD748(char *a0, int a1, char *a2);
extern void func_001AD768(char *a0, int a1);
extern void func_00263FF0(char *a0, int a1, char *a2);
extern void func_00268DA0(char *buf, const char *fmt, void *va);

void debug_openLog(const char *fmt, ...) {
    char buf[0x100];
    func_00268DA0(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    func_001AD748(D_006149A8, 0x503, buf);
    func_00263FF0(D_006149A8, 0x503, D_006329F8);
    func_001AD768(D_006149A8, 0x504);
    func_00263FF0(D_006149A8, 0x504, D_00632A00);
}

void debug_LogPrintf(void) {
    volatile char buf[256];
    D_00632A04 = -1;

}

void func_001A2E28(const char *fmt, ...) {
    char buf[0x100];
    void *info;
    func_00268DA0(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    info = func_0026527C(buf);
    func_00247C30(D_00632A04, buf, info);
}

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A2E80);

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A2FA0);

void debug_VariableInit(void)
{
    if ((int)D_00632A0C != -1) {
        func_00100250(1, D_00632A0C);
    }
    D_00632A0C = func_00100230(1, (int)func_001AA688, -1);
    func_00100B40(1);
}

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3208);

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3340);

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3398);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_makeBackImage);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintCharacter);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintFont);

extern int D_00632A30;
extern int D_00632CBC;
extern void debug_PrintFont(char *str, int x, int y, int r, int g, int b, int sz);
extern void func_0010F630(void);
extern void func_001101E0(void *a0, unsigned int a1, int a2, void *a3, int a4);
extern void gif_SpriteOffset(int a0);
extern int gif_SpriteSensitiveOrg(void);
extern void gsb_KeepFrameBuffer(int a0);
extern void gsb_Reduction(int a0);
extern void gsb_SetFrame(int a0, int a1, int a2);

void debug_FlushFontWindow(int a0, int a1, int a2, char *a3) {
    FR buf[2];
    int r;

    buf[1].x = a0 - 0x142;
    buf[1].y = a1 - 0x71;
    r = func_0026527C(a3);
    buf[1].h = 9;
    buf[1].w = r * 0xC + 4;
    buf[0] = buf[1];

    if (gif_SpriteSensitiveOrg() != 0) {
        return;
    }
    if (D_00632CBC & 2) {
        gif_SpriteOffset(0xB);
        gsb_Reduction(0);
        gsb_KeepFrameBuffer(0);
        gsb_SetFrame(1, 2, 0x80);
        func_001101E0(&buf[0], 0xFFFFFFFDU, 0, &D_00632A30, 1);
        func_0010F630();
    } else {
        gif_SpriteOffset(0xB);
        gsb_Reduction(0);
        gsb_SetFrame(1, 2, 0x80);
        func_0010F630();
    }
    debug_PrintFont(a3, a0, a1, (unsigned) a2 >> 24, ((unsigned) a2 >> 16) & 0xFF, ((unsigned) a2 >> 8) & 0xFF, 0x70);
}

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_FlushFont);

extern void debug_FlushFont(void);

void draw_batsu(void) {
    debug_FlushFont();
}

INCLUDE_ASM("asm/nonmatchings/src/debug", draw_shikaku);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_brainBar);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MakeBarString);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DrawBar);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBar);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_ResizeSnapShot);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_WriteBMP);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SnapShot);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispQW);


/* .data — carved VMA 0X4B30F8..0X4B3108 (1 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_004B30F8[4] = {
    0x00008000, 0x20004000, 0x00000051, 0x00000000,
};

/* .sdata — carved VMA 0X632A18..0X632A30 (4 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_00632A18[2] = {
    0x0A732523, 0x00000000,
};
unsigned int D_00632A20 = 0x000A6425;
unsigned int D_00632A24 = 0x7F7FFFFF;
unsigned int D_00632A28[2] = {
    0x7EFFFFFF, 0x00000000,
};
