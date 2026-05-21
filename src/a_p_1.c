/* a_p_1.c -- typed sdata / lit4 definitions for this TU.
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

extern const char D_00633210[8];
extern const char D_00633218[8];
extern const char D_00633220[8];
extern const char D_00633228[8];
extern const char D_00633230[8];
extern const char D_00633238[8];
extern const char D_00633240[8];
extern const char D_00633248[8];
extern const char D_00633250[8];
extern const char D_00633258[8];
extern const char D_00633260[8];
extern const char D_00633268[8];
extern const char D_00633270[8];
extern const char D_00633278[8];

const char D_00618550[16] = "src/a_p_1.c";

/* String rodata migrated from a_p_1_data.c */
const char D_00618560[32] = "--- WARNING!! ----\n";

/* Float rodata migrated from a_p_1_data.c */
const float D_00618580[4] = { 5e+01f, 0.0f, 0.0f, 1.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "蜘蛛の抜けによる落下死リクエスト
" */
const char D_00618590[40] = "\303\330\351\341\244\316\310\264\244\261\244\313\244\350\244\353\315\356\262\274\273\340\245\352\245\257\245\250\245\271\245\310\n";
/* EUC-JP: "既に死んでいるので起こしません
" */
const char D_006185B8[32] = "\264\373\244\313\273\340\244\363\244\307\244\244\244\353\244\316\244\307\265\257\244\263\244\267\244\336\244\273\244\363\n";
/* EUC-JP: "強制死亡
" */
const char D_006185D8[16] = "\266\257\300\251\273\340\313\264\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B8720);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B8CE0);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B8DC8);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B8EB0);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B94B0);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B9638);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B99B0);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001BA090);

extern void func_00104508(int p, int *self);
extern void func_00102850(int p, int *self);
extern void func_001CFA20(int x);
extern int D_004BEE60[];
extern void func_001B7FE8(int a, int b, int c, int d, int e, int f, int g, int h);
extern int D_00623468[];

void func_001BA2E0(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    func_00104508((int)((char *)p + 0x1E0), self);
    func_00102850((int)((char *)p + 0x1D0), self);
    func_001CFA20(p[0x19C / 4]);
}

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001BA330);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001BA530);

int func_001BA5C0(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(int *)(p + 0x0);
}

void func_001BA5D0(char *self, int val) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(int *)(p + 0x278) = val;
}

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001BA5E0);

int func_001BA668(int *self, int a1)
{
    void (*fn)(int *);
    int *p;
    fn = (void (*)(int *))D_004BEE60[a1 * 2];
    p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    p[0x8 / 4] = a1;
    if (fn != 0) {
        fn(self);
    }
    return 1;
}

int func_001BA6B0(int *self)
{
    int x = ((int *)((int *)self[0x15C/4])[0x800/4])[0x8/4];
    if (x < 6) {
        if (x >= 2) {
            return 0;
        }
    }
    ((int (*)())func_001BA668)();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001BA6F0);

void func_001BA770(int *self)
{
  int *entry = (int *) (((char *) D_00623468) - (-(self[0x30 / 4] * 32)));
  func_001B7FE8(0x3D, entry[0xC / 4], -1, 0, (int) self, -1, 7, 1);
  asm __volatile__("" : : : "memory");
}
