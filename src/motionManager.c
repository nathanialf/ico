/* motionManager.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */


__attribute__((section(".rodata.0x006192E0"))) const char D_006192E0[24] = "src/motionManager.c";

/* String rodata migrated from motionManager_data.c */
__attribute__((section(".rodata.0x006194D8"))) const char D_006194D8[88] = "MAY BE MOTION ORIENT DATA WAS BROKEN\n(MOTIONNAME:\"%s\" ID:%d: rootUpdateMode:%d)\n";

/* Float rodata migrated from motionManager_data.c */
__attribute__((section(".rodata.0x00619588"))) const float D_00619588[4] = { 0.0f, 5.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00619598"))) const float D_00619598[4] = { 0.0f, 0.0f, 5.0f, 0.0f };
__attribute__((section(".rodata.0x006195A8"))) const float D_006195A8[6] = { 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00619600"))) const float D_00619600[4] = { 1e+01f, 0.0f, 0.0f, 0.0f };

/* String-pool rodata migrated from motionManager_data.c */
__attribute__((section(".rodata.0x006192F8"))) const char D_006192F8[48] = "NOT ENTRY WCL\n\000\000regular height: %f (%f)\n\000\000\000\000\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "壁の角度が急なので落下
" */
__attribute__((section(".rodata.0x006193A0"))) const char D_006193A0[24] = "\312\311\244\316\263\321\305\331\244\254\265\336\244\312\244\316\244\307\315\356\262\274\n";
/* EUC-JP: "壁属性により落下
" */
__attribute__((section(".rodata.0x006193B8"))) const char D_006193B8[24] = "\312\311\302\260\300\255\244\313\244\350\244\352\315\356\262\274\n";
/* EUC-JP: "壁がなくて落下
" */
__attribute__((section(".rodata.0x006193D0"))) const char D_006193D0[16] = "\312\311\244\254\244\312\244\257\244\306\315\356\262\274\n";
/* EUC-JP: "壁のつかまり先がなくて落下 (段差:%f)
" */
__attribute__((section(".rodata.0x006193E0"))) const char D_006193E0[40] = "\312\311\244\316\244\304\244\253\244\336\244\352\300\350\244\254\244\312\244\257\244\306\315\356\262\274 (\303\312\272\271:%f)\n";
/* EUC-JP: "強制落下の壁に当たったので落下
" */
__attribute__((section(".rodata.0x00619408"))) const char D_00619408[32] = "\266\257\300\251\315\356\262\274\244\316\312\311\244\313\305\366\244\277\244\303\244\277\244\316\244\307\315\356\262\274\n";
/* EUC-JP: "下にDWATERの水底がないです。このメッセージが連続で
出てるなら、泳ぎから遷移していない状態です

" */
__attribute__((section(".rodata.0x00619428"))) const char D_00619428[96] = "\262\274\244\313DWATER\244\316\277\345\304\354\244\254\244\312\244\244\244\307\244\271\241\243\244\263\244\316\245\341\245\303\245\273\241\274\245\270\244\254\317\242\302\263\244\307\n\275\320\244\306\244\353\244\312\244\351\241\242\261\313\244\256\244\253\244\351\301\253\260\334\244\267\244\306\244\244\244\312\244\244\276\365\302\326\244\307\244\271\n\n";
/* EUC-JP: "拡張壁に当たった
" */
__attribute__((section(".rodata.0x00619498"))) const char D_00619498[24] = "\263\310\304\245\312\311\244\313\305\366\244\277\244\303\244\277\n";

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"

extern int D_0063347C;
extern int D_00633F3C;
extern void func_0013FF88(int a0, int a1, int a2);
extern void func_00105F00(int a0, int a1);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001D8E40);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001D92E0);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001D9890);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001D9BB8);
extern int func_00105278(void);
extern int func_00118678(int);
extern void func_00105308(float, float, float);
extern void func_0010DF70(char *p);
extern void func_001D9890(void);

void func_001D9C58(void)
{
    int v = func_00105278();
    func_00118678(v);
    {
        register float *p REG("$2") = (float *)D_00633F3C;
        func_00105308(p[0], p[1] + p[0x1D0 / 4] + 10.0f, p[2]);
    }
    func_0010DF70((char *)D_00633F3C + 0x30);
    func_001D9890();
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001D9CB0);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001D9E10);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001D9E90);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DA360);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DA4B8);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DA610);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DADF0);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DAF30);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DB000);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DC0E8);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DC558);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DC720);

void func_001DC8D8(void)
{
    func_0013FF88(D_0063347C, 0x18, D_0063347C);
    func_00105F00(D_00633F3C + 0x150, D_00633F3C);
}


void func_001DC908(void)
{
    func_0013FF88(D_0063347C, 0xF3, D_0063347C);
    func_00105F00(D_00633F3C + 0x150, D_00633F3C);
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DC938);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DC998);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DCAC8);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DD1F0);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DD668);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DD7A8);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE250);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE338);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE428);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE588);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE6B8);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE8D0);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DED10);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DEF20);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DF150);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DF368);
