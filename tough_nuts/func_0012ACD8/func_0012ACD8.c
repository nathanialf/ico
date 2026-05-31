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


const char D_00276230[16] = "\000\000\000E\000\000\000E";

unsigned int D_00276248[8] = { 0x00000000, 0x00000000, 0x00000020, 0x00000020, 0x00000020, 0x00000030, 0x00000030, 0x00000030 };

unsigned int D_00555938[22] = { 0x00000000, 0x00000001, 0x00000003, 0x00000004, 0x00000005, 0x00000001, 0x00000002, 0x00000000, 0x00000005, 0x00000003, 0x00000003, 0x00000004, 0x00000000, 0x00000001, 0x00000002, 0x00000004, 0x00000005, 0x00000003, 0x00000002, 0x00000000, 0x00000000, 0x00000000 };

unsigned int D_005559F0 = 0x00000000;

unsigned int D_00555B28[2] = { 0xFFFFFF00, 0xFF000000 };

const float D_00555B70[16] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };

const char D_00555BB0[32] = "Bga Object Already %d %d %d\n";

const char D_00555BD0[40] = "stage_MakeGObj:can't alloc gobj %d\n";

const char D_00555BF8[24] = "src/StageAnimation.c";

const char D_00555C10[40] = "Too much Stage Animation Objects.\n";

const char D_00555C38[48] = "stage_ApplyData:Data is not registered. \n\n%s\n";

/* EUC-JP: "stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n" */
const char D_00555C68[48] = "stgBgas \244\254%d\315\255\244\352 MAX_ANIM_KIND %d\244\362\261\333\244\250\244\336\244\267\244\277\n";

/* EUC-JP: "1ステージ中の BgAnimation の種類が多すぎます\n" */
const char D_00555C98[48] = "1\245\271\245\306\241\274\245\270\303\346\244\316 BgAnimation \244\316\274\357\316\340\244\254\302\277\244\271\244\256\244\336\244\271\n";

/* EUC-JP: "stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました\n" */
const char D_00555CC8[48] = "stgBgas \244\254%d\315\255\244\352 MAX_ANIM_GOBJ %d\244\362\261\333\244\250\244\336\244\267\244\277\n";

const char D_00555CF8[40] = "Max Bga = %d // Max DObj %d\n";

unsigned int D_00555D20[22] = { 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x656C6C49, 0x206C6167, 0x756F7247, 0x6F4E2070, 0x6425202E, 0x0000000A };

const char D_00555D78[56] = "stage_CheckAnimationFinish:illegal Animation No.\n";

const char D_00555DB0[48] = "stage_ContinueAnimation:illegal Animation No.\n";

/* EUC-JP: "指定したIDが存在しないか、アニメーションが読み込まれていません.\n" */
const char D_00555DE0[72] = "\273\330\304\352\244\267\244\277ID\244\254\302\270\272\337\244\267\244\312\244\244\244\253\241\242\245\242\245\313\245\341\241\274\245\267\245\347\245\363\244\254\306\311\244\337\271\376\244\336\244\354\244\306\244\244\244\336\244\273\244\363.\n";

/* EUC-JP: "ステージセグメントにメモリが確保できません.(ヒープメモリ不足)\n" */
const char D_00555E28[72] = "\245\271\245\306\241\274\245\270\245\273\245\260\245\341\245\363\245\310\244\313\245\341\245\342\245\352\244\254\263\316\312\335\244\307\244\255\244\336\244\273\244\363.(\245\322\241\274\245\327\245\341\245\342\245\352\311\324\302\255)\n";

unsigned int D_00555E70[12] = { 0x00000000, 0x00000000, 0x00000000, 0x50000002, 0x00008001, 0x10000000, 0x0000000E, 0x00000000, 0x00000001, 0x00000000, 0x0000003F, 0x00000000 };

const char D_00612348[48] = "object/sdf/demo/conte06/d6.smb";

const char D_00612378[48] = "object/sdf/demo/conte09/d9.smb";

const char D_006123A8[48] = "object/sdf/demo/conte09a/d9a.smb";

const char D_006123D8[96] = "object/sdf/demo/conte09a/d9b.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000object/sdf/demo/conte12/d12.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";

const char D_00612438[96] = "object/sdf/demo/conte12x/d12x.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000object/sdf/demo/conte12x/d12y.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000";

const char D_00612498[48] = "object/sdf/demo/conte13/d13.smb";

const char D_006124C8[48] = "object/sdf/demo/conte06/e3d6.smb";

/* Inlined data (Phase 3e) — migrated from StageAnimation_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* Inlined data (Phase 3e) — migrated from StageAnimation_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00630A70 = 1.4142135f;
float D_00630A74 = 1.4142135f;

/* Inlined data (Phase 3e) — migrated from StageAnimation_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* pointer / address tables */
void *D_00276240[2] = { (void *)0x00631D70, (void *)0x00631D68 };
void *D_005559E8[2] = { (void *)0x00555B10, (void *)0x002751CC };

/* misaligned arrays (scalar head + aligned tail) */
unsigned int D_005559F4 = 0x00000080;
unsigned int D_005559F8[28] = { 0x00555AF8, 0x002751E0, 0x00000000, 0x000000FF, 0x00555AE0, 0x002751E4, 0x00000000, 0x000000FF, 0x00555AC8, 0x002751E8, 0x00000000, 0x000000FF, 0x00555AB0, 0x002751D0, 0x00000000, 0x00000080, 0x00555A98, 0x002751D4, 0x00000000, 0x00000080, 0x00555A80, 0x002751D8, 0x00000000, 0x00000080, 0x00555A68, 0x002751DC, 0x00000000, 0x00000080 };

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

extern int func_001FA6D8(int);
extern int func_001FA898(int);
extern void func_001A6E28(const char *);
extern void func_001AD768(const char *file, int line);
extern void func_00263FF0(const char *file, int line, const char *fmt);
extern const char D_00555D78[];
extern const char D_00555BF8[];
extern const char D_00631D88[];

int func_0012AA80(int key)
{
    int count = *(volatile int *)&D_00633C54;
    int i = 0;
    char *e = (char *)D_00674058;
    if (count > 0) {
        do {
            int *entry1 = *(int **)(e + 0x280);
            if (key == entry1[0x58 / 4]) {
                int v = *(int *)(e + 0x28C) >> 30;
                switch (v) {
                case 0: return func_001FA6D8(*(int *)(e + 0x284));
                case 1: return func_001FA898(*(int *)(e + 0x288));
                }
            }
            i++;
            e += 0x290;
        } while (i < count);
    }
    func_001A6E28(D_00555D78);
    func_001AD768(D_00555BF8, 0x360);
    func_00263FF0(D_00555BF8, 0x360, D_00631D88);
    return 0;
}
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

typedef struct { long long w; } __attribute__((packed)) _packed64_sa;

void func_0012AC70(int key, char *src)
{
    register int count REG("$8");
    int one = 1;
    int i;
    char *e = (char *)D_00674058;
    count = *(volatile int *)&D_00633C54;
    i = 0;
    if (count <= 0) return;
    do {
        register int *entry1 REG("$2") = *(int **)(e + 0x280);
        i++;
        if (key == entry1[0x58 / 4]) {
            int *entry2;
            register char *target REG("$3");
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            *(_packed64_sa *)(target + 0x20) = *(_packed64_sa *)src;
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            *(int *)(target + 0x28) = one;
            count = *(volatile int *)&D_00633C54;
        }
        e += 0x290;
    } while (i < count);
}
/* CLEAN rc10 seed (no REG pins). TWIN of func_0012AC70 (this is the same loop
 * with a `value` arg stored at target[0x28] instead of the constant 1). The
 * `for (i=0;i<count;)` form fixes the count/i swap REG("$9") pinned; the rc10
 * residual is the IDENTICAL entry1/target v0/v1 deref tie as AC70 (func_00175C18
 * class, old REG($2)entry1 + REG($3)target). ~30 distinct clean shapes here +
 * ~30 on AC70 all plateau at rc10. volatile read + _packed64_sa are
 * TU-consistent dev idioms. Crack AC70's deref tie and this one falls too. */
void func_0012ACD8(int key, char *src, int value)
{
    int count = *(volatile int *)&D_00633C54;
    int i;
    char *e = (char *)D_00674058;
    for (i = 0; i < count; ) {
        int *entry1 = *(int **)(e + 0x280);
        i++;
        if (key == entry1[0x58 / 4]) {
            int *entry2 = *(int **)(e + 0x284);
            char *target = *(char **)((char *)entry2 + 0x24);
            *(_packed64_sa *)(target + 0x20) = *(_packed64_sa *)src;
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            *(int *)(target + 0x28) = value;
            count = *(volatile int *)&D_00633C54;
        }
        e += 0x290;
    }
}
extern void func_00118460(char *target, int arg1);
extern void func_0010D830(char *target, int arg2);

void func_0012AD40(int key, int arg1, int arg2)
{
    int count = *(volatile int *)&D_00633C54;
    int i = 0;
    char *e = (char *)D_00674058;
    if (count <= 0) return;
    do {
        int *entry1 = *(int **)(e + 0x280);
        if (key == entry1[0x58 / 4]) {
            int *entry2;
            char *target;
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            func_00118460(target, arg1);
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            func_0010D830(target + 0x10, arg2);
            count = *(volatile int *)&D_00633C54;
        }
        i++;
        e += 0x290;
    } while (i < count);
}
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012ADE8);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AE40);

/* ASCII debug strings — re-derived from EE rodata bytes. */
/* ASCII preview: "2:%s<ESC>[0m<LF>" */
const char D_00556468[16] = "2:%s\033[0m\n";
