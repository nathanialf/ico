/* DisplayList.c -- typed sdata / lit4 definitions for this TU.
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


const char D_0061AB88[24] = "src/DisplayList.c";

/* String rodata migrated from DisplayList_data.c */
const char D_0061ABA0[40] = "dl_PushPriority:Stack Overflow.\n";
const char D_0061ABC8[40] = "dl_PopPriority:Stack Underflow.\n";

/* String-pool rodata migrated from DisplayList_data.c */
const char D_0061ABF0[80] = "dldma %d\n\000\000\000\000\000\000\000dl_CheckDLOverflow:Display List Buffer [%d] Full.\n\000\000\000\000\000\000\000\000\000\000\000\000\000";

#include "include_asm.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB4C4);
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB4C8);
extern int D_00633F6C;
extern int D_00633F70;
extern int D_00710F18[];
extern int D_00710D10[];
extern void func_001FBBE0(void);
extern void func_001118B0(void);
extern void func_00118F58(void);
void func_001FB5E0(void)
{
    int flag = D_00633F6C ^ 1;
    int *src = (int *)((char *)D_00710F18 + flag * 0x34);
    char *dst = (char *)D_00710D10;
    int i;
    D_00633F6C = flag;
    D_00633F70 = 0;
    for (i = 0xC; i >= 0; i--) {
        int v = *src;
        *(int *)dst = 0;
        src++;
        *(int *)(dst + 0x24) = v;
        *(int *)(dst + 0x20) = v;
        dst += 0x28;
    }
    func_001FBBE0();
    func_001118B0();
    func_00118F58();
}
/* Original 4-byte nop pad that 8-aligns func_001FB658 (func_001FB658.s
 * carries no .align of its own). */
TRAILING_PAD_NOP();
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB658);
extern int D_00633810;
extern int D_00633818[] __asm__("D_00633818");
extern int D_00710F80[];
extern void func_001A6E28(const char *s);
extern void func_001AD768(const char *s, int n);
extern void func_00263FF0(const char *s, int n, void *buf);

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB768);
/* Original 4-byte nop pad that 8-aligns func_001FB7F8 (dropped on C
 * conversion; func_001FB768.s carried it inline). */

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB7F8);
