/* streamMotionManager.c -- typed sdata / lit4 definitions for this TU.
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

extern int D_00633720;
extern int D_00633724;
extern int D_00633728;
extern int D_0063372C;
extern int D_00633730;
extern int D_00633734;
extern int D_00633738;
extern unsigned int D_0063373C;
extern const char D_00633740[8];
extern int D_00633748;
extern unsigned int D_0063374C;
extern unsigned int D_00633750;
extern int D_00633754;
extern unsigned int D_00633758;
extern int D_0063375C;
extern int D_00633760;
extern int D_00633764;
extern int D_00633768;
extern int D_0063376C;
extern int D_00633770;
extern int D_00633774;
extern int D_00633778;
extern int D_0063377C;
extern unsigned int D_00633780;
extern int D_00633784;
extern unsigned int D_00633788;

__attribute__((section(".rodata.0x0061A668"))) const char D_0061A668[32] = "src/streamMotionManager.c";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "ストリーム用のバッファメモリが確保できませんでした
" */
__attribute__((section(".rodata.0x0061A688"))) const char D_0061A688[56] = "\245\271\245\310\245\352\241\274\245\340\315\321\244\316\245\320\245\303\245\325\245\241\245\341\245\342\245\352\244\254\263\316\312\335\244\307\244\255\244\336\244\273\244\363\244\307\244\267\244\277\n";

#include "include_asm.h"

extern int D_00632010;
extern int D_00633708;
extern int D_0063370C;
extern unsigned int D_0063373C;
extern int D_0061A578[];
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern void func_001A6E28();

struct Slot {
    int pad[4];
    int self_ptr;
    int pad2[1];
};
extern struct Slot D_0070D4D8[];

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", func_001F08D8);

void func_001F0A28(void)
{
    D_0063373C = 0;
    func_001A6E28(D_0061A578);
}

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", func_001F0A38);
extern void func_00264128(char *dst, char *src, int n);

void func_001F0B20(int *idx_p, char *dst, int size, char *src, int amt)
{
    int old_idx = *idx_p;
    int new_idx = old_idx + amt;
    *idx_p = new_idx;
    if (new_idx >= size) {
        int overflow = new_idx - size;
        int first_chunk = amt - overflow;
        *idx_p = overflow;
        func_00264128(dst + old_idx, src, first_chunk);
        func_00264128(dst, src + first_chunk, *idx_p);
        return;
    }
    func_00264128(dst + old_idx, src, amt);
}
INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", func_001F0BC8);

void func_001F0DA8(void)
{
    D_00633720 = func_0013A0F8(D_00632010, 0x28000, D_0061A668, 0x1F6);
    D_00633728 = func_0013A0F8(D_00632010, 0x28040, D_0061A668, 0x1F8);
    D_00633724 = (D_00633728 + 0x3F) & 0xFFFFFFC0u;
    if (D_00633720 == 0 || D_00633724 == 0) {
        func_001A6E28(D_0061A688);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", func_001F0E40);

void func_001F0F90(void) {
    D_0063370C = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/streamMotionManager", func_001F0F98);

int func_001F1058(volatile int *self)
{
    int slot = D_00633708;
    D_0070D4D8[slot].self_ptr = (int)self;
    ((int *)self[0x57])[0x11C] = slot;
    ((int *)self[0x57])[0x13C] = 0;
    ((int *)self[0x57])[0x13B] = 0;
    ((int *)self[0x57])[0x154] = 0;
    D_00633708 = slot + 1;
    return slot;
}
