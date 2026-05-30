/* item.c -- typed sdata / lit4 definitions for this TU.
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


/* EUC-JP: "小樽を見失ったのにつかもうとしてます。\n" */
const char D_00618F40[40] = "\276\256\303\256\244\362\270\253\274\272\244\303\244\277\244\316\244\313\244\304\244\253\244\342\244\246\244\310\244\267\244\306\244\336\244\271\241\243\n";

const char D_00618F68[16] = "src/item.c";

/* EUC-JP: "緊急停止2(%f←%f)\n" */
const char D_00618F78[24] = "\266\333\265\336\304\344\273\3372(%f\242\253%f)\n";

/* EUC-JP: "緊急停止3\n" */
const char D_00618F90[16] = "\266\333\265\336\304\344\273\3373\n";

/* EUC-JP: "振動睡眠\n" */
const char D_00618FA0[16] = "\277\266\306\260\277\347\314\262\n";

/* EUC-JP: "爆発アニメーション停止処理予定\n" */
const char D_00618FC8[32] = "\307\372\310\257\245\242\245\313\245\341\241\274\245\267\245\347\245\363\304\344\273\337\275\350\315\375\315\275\304\352\n";

const char D_00618FE8[16] = "GAMEMODE LOW0";

const char D_00618FF8[16] = "GAMEMODE LOW";

const char D_00619008[16] = "GAMEMODE HIGH";

const char D_00619018[16] = "DEMO MODE";

#include "include_asm.h"
#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/item", func_001D2550);
extern unsigned char D_004C4740[16];
extern float D_004C4760[48];
extern void func_00104508(void *buf, int v);
extern void func_001683C8(int arg);
extern void func_00104360(void *self, char *spill);
extern void func_00105F00(void *p, int arg);
extern void func_0010D530(void *p);

void func_001D2650(void *self, int arg)
{
    char *p;
    if (arg == 0)
        return;
    p = (char *)D_004C4760;
    func_00104508(p, arg);
    func_00104508(p + 0x10, (int)self);
    func_001683C8((int)p);
    if (*(int *)(p + 0x88) == 0)
        return;
    func_00104360(self, p + 0x20);
}

void func_001D26C8(void *self)
{
    Obj800 *s0 = GOBJ_SUB(self)->p_800;
    func_001D2650(self, s0->f_14);
    s0->f_10 = 0;
    s0->f_C = 0;
    s0->f_14 = 0;
    s0->f_8 = 1;
    GOBJ_SUB(self)->f_74 = 1;
    func_00105F00((char *)GOBJ_SUB(self) + 0x130, (int)D_004C4740);
    func_0010D530((char *)GOBJ_SUB(self) + 0x150);
}

void func_001D2738(void *self, int a1)
{
    Obj800 *s0 = GOBJ_SUB(self)->p_800;
    func_001D2650(self, s0->f_14);
    s0->f_C = 0;
    s0->f_8 = 1;
    s0->f_10 = 1;
    func_00105F00((char *)GOBJ_SUB(self) + 0x130, a1);
    func_0010D530((char *)GOBJ_SUB(self) + 0x150);
}

INCLUDE_ASM("asm/nonmatchings/src/item", func_001D27A8);
