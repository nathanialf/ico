/* box.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x006186A0"))) const char D_006186A0[16] = "src/box.c";

__attribute__((section(".rodata.0x00618818"))) const char D_00618818[16] = "b_mantle";
__attribute__((section(".rodata.0x00618828"))) const char D_00618828[16] = "tape_boro";

/* String rodata migrated from box_data.c */
__attribute__((section(".rodata.0x00618640"))) const char D_00618640[40] = "height: %f   dist: %f  ofs: %f %x \n";
__attribute__((section(".rodata.0x006186B0"))) const char D_006186B0[24] = "front pos: %f, %f, %f\n";
__attribute__((section(".rodata.0x006186C8"))) const char D_006186C8[24] = "rear  pos: %f, %f, %f\n";
__attribute__((section(".rodata.0x00618708"))) const char D_00618708[24] = "box die!!!\n";
__attribute__((section(".rodata.0x00618740"))) const char D_00618740[32] = "near wall to %f, %f, %f\n";
__attribute__((section(".rodata.0x00618760"))) const char D_00618760[16] = "BOXREINIT\n";
__attribute__((section(".rodata.0x00618808"))) const char D_00618808[16] = "%f, %f, %f\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "この地形はおかしいです(100cmに区切られていません)
" */
__attribute__((section(".rodata.0x00618668"))) const char D_00618668[56] = "\244\263\244\316\303\317\267\301\244\317\244\252\244\253\244\267\244\244\244\307\244\271(100cm\244\313\266\350\300\332\244\351\244\354\244\306\244\244\244\336\244\273\244\363)\n";
/* EUC-JP: "[36m箱が地面の無いところに初期配置されています。
動作が保証できません(コリジョン定義より前に箱がありませんか?)[m
" */
__attribute__((section(".rodata.0x00618770"))) const char D_00618770[120] = "\033[36m\310\242\244\254\303\317\314\314\244\316\314\265\244\244\244\310\244\263\244\355\244\313\275\351\264\374\307\333\303\326\244\265\244\354\244\306\244\244\244\336\244\271\241\243\n\306\260\272\356\244\254\312\335\276\332\244\307\244\255\244\336\244\273\244\363(\245\263\245\352\245\270\245\347\245\363\304\352\265\301\244\350\244\352\301\260\244\313\310\242\244\254\244\242\244\352\244\336\244\273\244\363\244\253?)\033[m\n";
/* EUC-JP: "箱初期水底配置
" */
__attribute__((section(".rodata.0x006187E8"))) const char D_006187E8[16] = "\310\242\275\351\264\374\277\345\304\354\307\333\303\326\n";
/* EUC-JP: "箱初期通常配置
" */
__attribute__((section(".rodata.0x006187F8"))) const char D_006187F8[16] = "\310\242\275\351\264\374\304\314\276\357\307\333\303\326\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BCAF0);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BCC18);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD138);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD278);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD408);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD668);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD770);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BDA70);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BDC58);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BE120);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BE250);
extern unsigned int D_00631168[];
void func_00104508(void *buf, void *self);
void func_00105F00(void *dst, void *src);
int func_001684C8(void *struct_arg);
void func_00103C48(void *arg, void *self, int flag, float v, float maxv, float scale, float zero);
void func_00102858(void *arg);

void func_001BE558(int arg, int *self) {
    int local[50];
    int rc;
    float v;
    int *p_15C = (int *)self[0x15C/4];
    float val_3D8 = *(float *)&p_15C[0x3D8/4];
    float clamped = val_3D8;
    if (!(30.0f < val_3D8)) clamped = 30.0f;

    *(float *)((char *)local + 0x70) = clamped;
    func_00104508((char *)local + 0xC0, self);

    {
        float val_270 = *(float *)&((int *)self[0x15C/4])[0x270/4];
        float val_C4 = *(float *)((char *)local + 0xC4);
        val_270 += 10.0f;
        val_C4 += val_270;
        *(float *)((char *)local + 0xC4) = val_C4;
        func_00105F00((char *)local, (char *)local + 0xC0);
    }
    func_00105F00((char *)local + 0x10, (char *)local + 0xC0);

    *(int *)((char *)local + 0x74) = arg;
    *(int *)((char *)local + 0x78) = -1;
    *(int *)((char *)local + 0x7C) = 0;
    func_001684C8((char *)local);
    if (*(int *)((char *)local + 0x88) == 0) return;

    {
        int *p2 = (int *)self[0x15C/4];
        int state = p2[0x4D8/4];
        if ((unsigned)(state - 7) >= 10) goto def;
        switch (state) {
        case 7: case 8: case 10: case 15: case 16:
            rc = (p2[0x180/4] == arg);
            goto done;
        default: ;
        }
    def:
        rc = 1;
    done:
        if (rc == 0) return;
    }

    v = *(float *)((char *)local + 0x70);
    v += 50.0f;
    v *= *(float *)D_00631168;
    func_00103C48((void *)arg, self, 1, v, 100.0f, 0.5f, 0.0f);
    func_00102858((void *)arg);
}
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BE6A8);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BEC30);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BED00);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BEE60);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BEF58);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF148);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF2C8);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF460);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF6A0);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF7F8);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF918);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BFFE8);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001C00C0);
