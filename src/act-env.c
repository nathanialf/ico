/* src/act-env.c — __FILE__ anchor at .rodata 0x0061AE10 */

#include "include_asm.h"

extern float D_0063144C;
extern float D_00631450;
extern float D_00631454;
extern float D_00631458;
extern float D_0063145C;
extern float D_00631460;
extern float D_00631464;
extern float D_00631468;
extern float D_0063146C;
extern float D_00631470;
extern float D_00631474;
extern float D_00631478;
extern float D_0063147C;
extern float D_00631480;
extern int D_00631990;
extern char D_006319A0[16];
extern char D_006319B0[16];
extern const char D_00633840[8];
extern const char D_00633848[8];
extern unsigned int D_00633850;
extern int D_0063385C;
extern int D_00633860;
extern int D_00633864;
extern unsigned int D_00633868;

const float D_0061AD10[4] = { 3e+01f, 0.0f, -5e+01f, 0.0f };
const char D_0061AD20[16] = "climb_50  ";
const char D_0061AD30[16] = "climb_100 ";
const char D_0061AD40[16] = "climb_200 ";
const char D_0061AD50[16] = "climb_300 ";
const char D_0061AD60[16] = "hold_box  ";
const char D_0061AD70[16] = "hang_hand ";
const char D_0061AD80[16] = "hang_breas";
const char D_0061AD90[16] = "ladder_up ";
const char D_0061ADA0[16] = "ladder_dow";
const char D_0061ADB0[16] = "down_cliff";
const char D_0061ADC0[16] = "walk_wall";
const char D_0061ADD0[16] = "walk_stair";
const char D_0061ADE0[16] = "pulledup_50 ";
const char D_0061ADF0[16] = "pulledup_100";
const char D_0061AE00[16] = "pulledup_200";
const char D_0061AE10[16] = "src/act-env.c";
const char D_0061AE20[16] = "enter water\n";
const char D_0061AE30[32] = "exit water\n\000\000\000\000\000WBP <<begin>>\n\000";
const char D_0061AEB0[32] = "--b-- %p:act brain del %p\n";
const char D_0061AED0[32] = "--b-- %p:act brain NULL %p\n";
const char D_0061AEF0[32] = "--m-- %p:act main del %p\n";
const char D_0061AF10[32] = "--m-- %p:act main NULL %p\n";
const char D_0061AF30[32] = "--t-- %p:act mot del %p\n";
const char D_0061AF50[32] = "--t-- %p:act mot NULL %p\n";
const char D_0061AF70[16] = "acst[%p]\n";
const char D_0061AF80[16] = "    [%d]\n";
const char D_0061AF90[16] = "lval[%p]\n";

extern int func_0010A088(int a0, int a1);
extern int func_0010A068(int a0, int a1);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC520);
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC6C8);
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC780);
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FCA20);
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_00200848);
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_00200970);
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_002009F0);

int func_00200A98(int a0)
{
    unsigned char v0;
    if (D_00631990 == 4) {
        v0 = func_0010A088(a0, 0x1000);
    } else {
        v0 = func_0010A068(a0, 0x1000);
    }
    return v0 & 0xFF;
}
