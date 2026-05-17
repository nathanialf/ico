/* message.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00557540"))) const char D_00557540[16] = "ios/message.c";
__attribute__((section(".rodata.0x005575D0"))) const char D_005575D0[16] = "FINDCTP1";
__attribute__((section(".rodata.0x005575E0"))) const char D_005575E0[16] = "DISCONNECT";

/* String rodata migrated from message_data.c */
__attribute__((section(".rodata.0x00557550"))) const char D_00557550[16] = "sema[%d] = %p\n";
__attribute__((section(".rodata.0x00557560"))) const char D_00557560[24] = "msg:null message queue\n";
__attribute__((section(".rodata.0x00557578"))) const char D_00557578[16] = "MSG NO SEND\n";
__attribute__((section(".rodata.0x00557588"))) const char D_00557588[24] = "evt:null message queue\n";
__attribute__((section(".rodata.0x005575A0"))) const char D_005575A0[16] = "where is here\n";
__attribute__((section(".rodata.0x005575B0"))) const char D_005575B0[32] = "evt:signal added\n";

#include "include_asm.h"

extern int D_006A6990[];

INCLUDE_ASM_NOP_PAD(func_0013A248);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A250);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A2F8);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A380);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A498);

void func_0013A580(void)
{
    int *p = D_006A6990;
    int i;
    p += 0xFF;
    for (i = 0xFF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}

INCLUDE_ASM_NOP_PAD(func_0013A5B4);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A5B8);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A6C0);
