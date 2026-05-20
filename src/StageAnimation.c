/* StageAnimation.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00555BF8"))) const char D_00555BF8[24] = "src/StageAnimation.c";

__attribute__((section(".rodata.0x00612348"))) const char D_00612348[48] = "object/sdf/demo/conte06/d6.smb";
__attribute__((section(".rodata.0x00612378"))) const char D_00612378[48] = "object/sdf/demo/conte09/d9.smb";
__attribute__((section(".rodata.0x006123A8"))) const char D_006123A8[48] = "object/sdf/demo/conte09a/d9a.smb";
__attribute__((section(".rodata.0x00612498"))) const char D_00612498[48] = "object/sdf/demo/conte13/d13.smb";
__attribute__((section(".rodata.0x006124C8"))) const char D_006124C8[48] = "object/sdf/demo/conte06/e3d6.smb";

/* String rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x00555BB0"))) const char D_00555BB0[32] = "Bga Object Already %d %d %d\n";
__attribute__((section(".rodata.0x00555BD0"))) const char D_00555BD0[40] = "stage_MakeGObj:can't alloc gobj %d\n";
__attribute__((section(".rodata.0x00555C10"))) const char D_00555C10[40] = "Too much Stage Animation Objects.\n";
__attribute__((section(".rodata.0x00555C38"))) const char D_00555C38[48] = "stage_ApplyData:Data is not registered. \n\n%s\n";
__attribute__((section(".rodata.0x00555CF8"))) const char D_00555CF8[40] = "Max Bga = %d // Max DObj %d\n";
__attribute__((section(".rodata.0x00555D78"))) const char D_00555D78[56] = "stage_CheckAnimationFinish:illegal Animation No.\n";
__attribute__((section(".rodata.0x00555DB0"))) const char D_00555DB0[48] = "stage_ContinueAnimation:illegal Animation No.\n";

/* Float rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x00555B70"))) const float D_00555B70[16] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };

/* String-pool rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x006123D8"))) const char D_006123D8[96] = "object/sdf/demo/conte09a/d9b.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000object/sdf/demo/conte12/d12.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
__attribute__((section(".rodata.0x00612438"))) const char D_00612438[96] = "object/sdf/demo/conte12x/d12x.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000object/sdf/demo/conte12x/d12y.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "stgBgas が%d有り MAX_ANIM_KIND %dを越えました
" */
__attribute__((section(".rodata.0x00555C68"))) const char D_00555C68[48] = "stgBgas \244\254%d\315\255\244\352 MAX_ANIM_KIND %d\244\362\261\333\244\250\244\336\244\267\244\277\n";
/* EUC-JP: "1ステージ中の BgAnimation の種類が多すぎます
" */
__attribute__((section(".rodata.0x00555C98"))) const char D_00555C98[48] = "1\245\271\245\306\241\274\245\270\303\346\244\316 BgAnimation \244\316\274\357\316\340\244\254\302\277\244\271\244\256\244\336\244\271\n";
/* EUC-JP: "stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました
" */
__attribute__((section(".rodata.0x00555CC8"))) const char D_00555CC8[48] = "stgBgas \244\254%d\315\255\244\352 MAX_ANIM_GOBJ %d\244\362\261\333\244\250\244\336\244\267\244\277\n";
/* EUC-JP: "指定したIDが存在しないか、アニメーションが読み込まれていません.
" */
__attribute__((section(".rodata.0x00555DE0"))) const char D_00555DE0[72] = "\273\330\304\352\244\267\244\277ID\244\254\302\270\272\337\244\267\244\312\244\244\244\253\241\242\245\242\245\313\245\341\241\274\245\267\245\347\245\363\244\254\306\311\244\337\271\376\244\336\244\354\244\306\244\244\244\336\244\273\244\363.\n";
/* EUC-JP: "ステージセグメントにメモリが確保できません.(ヒープメモリ不足)
" */
__attribute__((section(".rodata.0x00555E28"))) const char D_00555E28[72] = "\245\271\245\306\241\274\245\270\245\273\245\260\245\341\245\363\245\310\244\313\245\341\245\342\245\352\244\254\263\316\312\335\244\307\244\255\244\336\244\273\244\363.(\245\322\241\274\245\327\245\341\245\342\245\352\311\324\302\255)\n";

#include "include_asm.h"
#include "regpin.h"

extern void func_001FAA58(void);
extern int D_00274ED4[];
extern void func_00117768(void);
extern void func_001FAA30(int a0, int a1, int a2, int a3);
extern int D_00633C54;
extern char D_00674058[];

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_00128868);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_00128AF0);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_00128CD0);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_001297A0);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_00129970);

void func_00129A78(void)
{
    func_001FAA58();
    if (D_00274ED4[0] != 0) return;
    func_00117768();
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_00129AA8);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_00129C90);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_00129E28);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_00129F58);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012A060);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012A318);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012A618);
extern int D_00633C58;
extern void func_001F6D90(int *node);
void func_0012A7A0(int **self)
{
    int *node = *self;
    int *next;
    int *prev;
    if (node == 0) return;
    next = (int *)node[0x10 / 4];
    if (next != 0) {
        next[0x14 / 4] = node[0x14 / 4];
    } else {
        D_00633C58 = node[0x14 / 4];
        __asm__ __volatile__("" ::: "memory");
        node = *(int * volatile *)self;
    }
    prev = (int *)node[0x14 / 4];
    if (prev != 0) {
        prev[0x10 / 4] = node[0x10 / 4];
    }
    if (D_00633C58 != 0) {
        ((int *)D_00633C58)[0x10 / 4] = 0;
    }
    func_001F6D90(*self);
}
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012A7F8);

void func_0012AA78(int a0, int a1, int a2, int a3)
{
    func_001FAA30(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AA80);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AB50);
void func_0012ABE0(int key, int new_val)
{
    register int count REG("$7");
    int i = 0;
    char *e = (char *)D_00674058;
    count = *(volatile int *)&D_00633C54;
    if (count <= 0) return;
    do {
        int *p = *(int **)(e + 0x280);
        i++;
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = new_val;
            count = *(volatile int *)&D_00633C54;
        }
        e += 0x290;
    } while (i < count);
}

void func_0012AC28(int target, int val)
{
    int n = D_00633C54;
    char *p = (char *)D_00674058;
    int i;
    if (n <= 0) return;
    i = n;
    do {
        int *entry1 = *(int **)(p + 0x280);
        if (target == entry1[0x58 / 4]) {
            int *entry2 = *(int **)(p + 0x284);
            *(float *)((char *)entry2 + 0x1C) = (float)val;
        }
        p += 0x290;
    } while (--i);
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AC70);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012ACD8);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AD40);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012ADE8);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AE40);
