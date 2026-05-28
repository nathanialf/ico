/* Packet.c -- typed sdata / lit4 definitions for this TU.
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


const char D_00554EE0[48] = "IN %s\n%s:NoTexture Polygon(s) exist(s).\n";

const char D_00554F10[48] = "IN %s\n%s:NoNormal Cluster Model exists.\n";

const char D_00554F40[48] = "IN %s\n%s:Abnormal Weight Data exist(s).\n";

const char D_00554F70[56] = "IN %s\n%s:Too Much Weight (>=4) Vertex exist(s).\n";

const char D_00554FA8[40] = "IN %s\n%s:No Weight Vertex exist(s).\n";

const char D_00554FD0[16] = "src/Packet.c";

const char D_00555038[24] = "pac_makeNormalStrip";

const char D_00555050[24] = "pac_getWeight(0)";

const char D_00555068[24] = "pac_getWeight(1)";

const char D_00555080[24] = "pac_getWeight(2)";

const char D_00555098[56] = "vertex has 3 cluster-weights %d(%f) %d(%f) %d(%f)\n";

const char D_005550D0[40] = "warning:weight total %f VtxIdx:%d\n";

const char D_00555138[24] = "pac_makeClusterStrip";

const char D_00555150[32] = "over 60 skeltons exist.\n";

const char D_00555170[32] = "color table not exists.\n";

const char D_00555190[16] = "DMAOPEN   :%p\n";

const char D_005551A0[32] = "VIFUNPACK :%08x %08x (%p:%d)\n";

unsigned int D_005551C0[8] = { 0x00008000, 0x20004000, 0x00000051, 0x00000000, 0x00008000, 0x30004000, 0x00000512, 0x00000000 };

const char D_005551E0[16] = "GIFTAG    :";

const char D_005551F0[40] = "pac_continueTag:Packet too small. %d\n";

const char D_00555218[40] = "Original Strip Too Long. Size %d\n";

const char D_00555240[24] = "size(0x%x) strips(%d)\n";

const char D_00555258[16] = "--- cut ---\n\n";

const char D_00555268[56] = "gif over! cut! %d/%d polys:%d/%d fchain:%d vif+gif:%d\n";

const char D_005552A0[24] = "chain too long! cut!\n";

const char D_005552B8[48] = "pac_copyStrip:No Enough Memory for Packet.\n";

const char D_005552E8[32] = "ALL:src:%p => dst:%p (size:%x)\n";

const char D_00555308[32] = "pac_countOneVertexPacketSize";

const char D_00555328[40] = "pac_makeStrip:No Memory To Convert.\n";

const char D_00555350[40] = "pac_makeStrip:No Tex Poly Exists.%s\n";

const char D_00555398[88] = "IN OBJECT \"%s\"\nHUGE PACKET (SIZE:0x%x) APPEARED\nMAYBE INFLATE MEMORY AREA WAS BROKEN.\n";

const char D_005553F0[48] = "pac_makeTextureTable:\n\tTexture not Found. %s\n";

const char D_00555420[56] = "pac_makePacket:Material Table Not Found. (%s:%s)\n";

const char D_00555458[24] = "illegal size = %d\n";

const char D_00555470[32] = "illegal vertex num %d\n";

const char D_005554A0[16] = "\000\200\000\000\000@\0000\022\005";

unsigned int D_005554D0[4] = { 0x00000000, 0x50004000, 0x00052521, 0x00000000 };

const char D_00631CD8[8] = "%02x";

const char D_00631CE0[8] = " ";

const char D_00631CE8[8] = "%12f ";

unsigned int D_00631CF0[2] = { 0x0000000A, 0x00000000 };

const char D_00631D00[8] = " (%d)\n";

const char D_00631D08[8] = "e";

const char D_00631D10[8] = "%s";

const char D_00631D18[8] = "%s_l";

const char D_00631D20[8] = "%s_ref";

const char D_00631D28[8] = "0";

const char D_00631D30[8] = "%s";

const char D_00631D38[8] = "FALSE";

unsigned char D_00631D40[8] = { 0 };

const char D_00631D48[8] = "0";

unsigned int D_00631D50 = 0x00000000;

unsigned int D_00631D54 = 0x00000000;

unsigned char D_00631D58 = 0x00;

unsigned char D_00631D59 = 0x00;

unsigned char D_00631D5A = 0x00;

unsigned int D_00631D60[2] = { 0x00000053, 0xFFFFFFFF };

const char D_00631D68[8] = "On";

char D_00631D70[4] = "Off";

unsigned int D_00631D74 = 0x00000000;

const char D_00631D78[8] = "%s : %s";

const char D_00631D80[8] = "%s : %d";

const char D_00631D88[8] = "0";

const char D_00631D90[8] = "BGA";

const char D_00631D98[8] = "e";

const char D_00631DA0[8] = "PSMT8";

const char D_00631DA8[8] = "PSMT4";

const char D_00631DB0[8] = "PSMCT32";

const char D_00631DB8[8] = "PSMCT24";

const char D_00631DC0[8] = "PSMCT16";

const char D_00631DC8[8] = "NONE";

const char D_00631DD0[8] = "0";

const char D_00631DD8[8] = "FALSE";

const char D_00631DE0[8] = "ICO";

const char D_00631DE8[8] = "e";

const char D_00631DF0[8] = "%s";

const char D_00631DF8[8] = "1:%s\n";

const char D_00631E00[8] = "%s.tm2";

/* Inlined data (Phase 3e) — migrated from Packet_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* misaligned arrays (scalar head + aligned tail) */
unsigned char D_00631D5B = 0x00;
unsigned int D_00631D5C = 0x00000000;

/* Inlined data (Phase 3e) — migrated from Packet_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* Inlined data (Phase 3e) — migrated from Packet_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

#include "include_asm.h"
#include "matching.h"

extern int D_00672F90[];
extern int D_00633C3C;

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00118AB8);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00118B18);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00118C68);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00118E88);

void func_00118F58(void)
{
    int *p = D_00672F90;
    int i = 0xC;
    D_00633C3C = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

INCLUDE_ASM_NOP_PAD(func_00118F94);

void func_00118F98(void)
{
    int *p = D_00672F90;
    int i = 0xC;
    D_00633C3C = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

INCLUDE_ASM_NOP_PAD(func_00118FD4);

extern void func_001A6E28(const char *fmt, ...);
extern int func_00263FB0(float);
extern const char D_00554DD0[];
extern const char D_00554DE8[];
/* Reference the in-TU format strings as incomplete-array externs so ee-gcc
 * addresses them with %hi/%lo (hoisted into callee-saved regs across the
 * loop) instead of gp_rel — they are 8-byte small-data objects defined just
 * above, which -G8 would otherwise make gp-relative. */
extern const char D_00631CD8_a[] __asm__("D_00631CD8");
extern const char D_00631CE0_a[] __asm__("D_00631CE0");
extern const char D_00631CE8_a[] __asm__("D_00631CE8");
extern const char D_00631CF0_a[] __asm__("D_00631CF0");

void func_00118FD8(unsigned char *arg, int slot_size) {
    int is_float = 0;
    int row;

    switch (slot_size) {
    case 0:
        is_float = 1;
        slot_size = 4;
        func_001A6E28(D_00554DD0, arg);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        func_001A6E28(D_00554DE8, arg, slot_size);
        break;
    default:
        return;
    }

    for (row = 0; row < 0x10 / slot_size; row++) {
        if (!is_float) {
            int col;
            for (col = 0x10 / (0x10 / slot_size) - 1; col >= 0; col--) {
                func_001A6E28(D_00631CD8_a, arg[row * slot_size + col]);
            }
            func_001A6E28(D_00631CE0_a);
        } else {
            func_001A6E28(D_00631CE8_a, func_00263FB0(((float *)arg)[row]));
        }
    }
    func_001A6E28(D_00631CF0_a);
}

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_001191C0);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00119350);

extern void func_001A2D78(const char *fmt, char *arg, char *ctx);
extern void func_001AD768(const char *str, int len);
extern void func_00263FF0(const char *str, int len, char *ctx);
extern char D_00672FD0[];
extern char D_00631CF8[];

void func_00119470(char *self, int idx) {
    switch (idx) {
        case 5: func_001A2D78(D_00554EE0, D_00672FD0, self); break;
        case 1: func_001A2D78(D_00554F10, D_00672FD0, self); break;
        case 2: func_001A2D78(D_00554F40, D_00672FD0, self); break;
        case 3: func_001A2D78(D_00554F70, D_00672FD0, self); break;
        case 4: func_001A2D78(D_00554FA8, D_00672FD0, self); break;
    }
    func_001AD768(D_00554FD0, 0x2AC);
    func_00263FF0(D_00554FD0, 0x2AC, D_00631CF8);
}

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00119540);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_001199A0);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00119CA0);
extern char D_00672FD0[];
extern float D_00630A40;
extern float D_00630A44;
void func_0011A238(int a0)
{
    register int mask REG("$4") = 0x0FFFFFFF;
    char *ctx = D_00672FD0;
    float f0 = D_00630A40;
    float f1 = D_00630A44;
    *(int *)(ctx + 0x20) = a0 & mask;
    *(int *)(ctx + 0x24) = (a0 + 0x8) & mask;
    *(int *)(ctx + 0x28) = (a0 + 0x10) & mask;
    *(int *)(ctx + 0x2C) = a0 + 0x20;
    *(float *)(ctx + 0x48) = f0;
    *(float *)(ctx + 0x44) = f0;
    *(float *)(ctx + 0x40) = f0;
    *(float *)(ctx + 0x58) = f1;
    *(float *)(ctx + 0x54) = f1;
    *(float *)(ctx + 0x50) = f1;
    func_001A6E28(D_00555190, a0 & mask);
}
extern void func_001A6E28(const char *fmt, ...);

void func_0011A2A8(int a0)
{
    register char *base REG("$6") = D_00672FD0;
    (*(volatile int * volatile *)(base + 0x24))[0] = 0;
    (*(volatile int * volatile *)(base + 0x24))[1] = (a0 << 16) | 0x6C008000;
    {
        volatile int *p = *(volatile int * volatile *)(base + 0x24);
        func_001A6E28(D_005551A0, p[0], p[1], (int *)p, a0);
    }
}
void func_0011A2F0(void)
{
    register char *base REG("$3") = D_00672FD0;
    volatile int * volatile *curp = (volatile int * volatile *)(base + 0x2C);
    volatile int *p = *curp;
    *p++ = 0x17000000;
    *curp = p;
    p[0] = 0;
    *curp = p + 1;
    p[1] = 0;
    *curp = p + 2;
    p[2] = 0;
    *curp = p + 3;
    func_001A6E28((const char *)(p + 3));
}
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A338);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A410);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A520);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A668);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A7F8);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A990);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011ACF8);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011AE78);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011B040);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011B1F0);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011B360);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011B6D8);

void func_0011BF40(int a0)
{
    int v = *(int *)(a0 + 0x820);
    int p = *(int *)(a0 + 0x844);
    func_0011B6D8(v, *(int *)(p + 0xF0), *(signed char *)(v + 0x2F) > 0);
}

/* ASCII debug strings — re-derived from EE rodata bytes. */
/* ASCII preview: "<ESC>[31msorce normal model data broken! %f %f %f %f [%d]<ESC>[0m<LF>" */
const char D_00554FF8[64] = "\033[31msorce normal model data broken! %f %f %f %f [%d]\033[0m\n";
/* ASCII preview: "<ESC>[31msorce cluster model data broken! %f %f %f %f [%d]<ESC>[0m<LF>" */
const char D_005550F8[64] = "\033[31msorce cluster model data broken! %f %f %f %f [%d]\033[0m\n";
/* ASCII preview: "<ESC>[31mMaxPacketSize = %d<ESC>[0m<LF>" */
const char D_00555378[32] = "\033[31mMaxPacketSize = %d\033[0m\n";
