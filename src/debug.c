#include "common.h"




extern int func_001AA688();
extern void func_00100250();
extern int func_00100230();
extern void func_00100B40();
extern unsigned int D_00632A0C;
extern void func_00268DA0();
extern int func_0026527C();
extern void func_00247C30();
extern int D_00632A04;
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Assert);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_openLog);

void debug_LogPrintf(void) {
    volatile char buf[256];
    D_00632A04 = -1;

}

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A2E24);

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

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3204);

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3208);

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3340);

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3394);

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3398);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_makeBackImage);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintCharacter);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintFont);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_FlushFontWindow);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_FlushFont);

INCLUDE_ASM("asm/nonmatchings/src/debug", draw_batsu);

INCLUDE_ASM("asm/nonmatchings/src/debug", draw_shikaku);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_brainBar);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MakeBarString);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DrawBar);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBar);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_ResizeSnapShot);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_WriteBMP);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SnapShot);

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispQW);

