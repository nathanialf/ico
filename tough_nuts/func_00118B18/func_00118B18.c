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


__attribute__((section(".rodata.0x00554FD0"))) const char D_00554FD0[16] = "src/Packet.c";

__attribute__((section(".rodata.0x00555038"))) const char D_00555038[24] = "pac_makeNormalStrip";
__attribute__((section(".rodata.0x00555050"))) const char D_00555050[24] = "pac_getWeight(0)";
__attribute__((section(".rodata.0x00555068"))) const char D_00555068[24] = "pac_getWeight(1)";
__attribute__((section(".rodata.0x00555080"))) const char D_00555080[24] = "pac_getWeight(2)";
__attribute__((section(".rodata.0x00555138"))) const char D_00555138[24] = "pac_makeClusterStrip";
__attribute__((section(".rodata.0x005551E0"))) const char D_005551E0[16] = "GIFTAG    :";
__attribute__((section(".rodata.0x00555308"))) const char D_00555308[32] = "pac_countOneVertexPacketSize";

/* String rodata migrated from Packet_data.c */
__attribute__((section(".rodata.0x00554EE0"))) const char D_00554EE0[48] = "IN %s\n%s:NoTexture Polygon(s) exist(s).\n";
__attribute__((section(".rodata.0x00554F10"))) const char D_00554F10[48] = "IN %s\n%s:NoNormal Cluster Model exists.\n";
__attribute__((section(".rodata.0x00554F40"))) const char D_00554F40[48] = "IN %s\n%s:Abnormal Weight Data exist(s).\n";
__attribute__((section(".rodata.0x00554F70"))) const char D_00554F70[56] = "IN %s\n%s:Too Much Weight (>=4) Vertex exist(s).\n";
__attribute__((section(".rodata.0x00554FA8"))) const char D_00554FA8[40] = "IN %s\n%s:No Weight Vertex exist(s).\n";
__attribute__((section(".rodata.0x00555098"))) const char D_00555098[56] = "vertex has 3 cluster-weights %d(%f) %d(%f) %d(%f)\n";
__attribute__((section(".rodata.0x005550D0"))) const char D_005550D0[40] = "warning:weight total %f VtxIdx:%d\n";
__attribute__((section(".rodata.0x00555150"))) const char D_00555150[32] = "over 60 skeltons exist.\n";
__attribute__((section(".rodata.0x00555170"))) const char D_00555170[32] = "color table not exists.\n";
__attribute__((section(".rodata.0x00555190"))) const char D_00555190[16] = "DMAOPEN   :%p\n";
__attribute__((section(".rodata.0x005551A0"))) const char D_005551A0[32] = "VIFUNPACK :%08x %08x (%p:%d)\n";
__attribute__((section(".rodata.0x005551F0"))) const char D_005551F0[40] = "pac_continueTag:Packet too small. %d\n";
__attribute__((section(".rodata.0x00555218"))) const char D_00555218[40] = "Original Strip Too Long. Size %d\n";
__attribute__((section(".rodata.0x00555240"))) const char D_00555240[24] = "size(0x%x) strips(%d)\n";
__attribute__((section(".rodata.0x00555258"))) const char D_00555258[16] = "--- cut ---\n\n";
__attribute__((section(".rodata.0x00555268"))) const char D_00555268[56] = "gif over! cut! %d/%d polys:%d/%d fchain:%d vif+gif:%d\n";
__attribute__((section(".rodata.0x005552A0"))) const char D_005552A0[24] = "chain too long! cut!\n";
__attribute__((section(".rodata.0x005552B8"))) const char D_005552B8[48] = "pac_copyStrip:No Enough Memory for Packet.\n";
__attribute__((section(".rodata.0x005552E8"))) const char D_005552E8[32] = "ALL:src:%p => dst:%p (size:%x)\n";
__attribute__((section(".rodata.0x00555328"))) const char D_00555328[40] = "pac_makeStrip:No Memory To Convert.\n";
__attribute__((section(".rodata.0x00555350"))) const char D_00555350[40] = "pac_makeStrip:No Tex Poly Exists.%s\n";
__attribute__((section(".rodata.0x00555398"))) const char D_00555398[88] = "IN OBJECT \"%s\"\nHUGE PACKET (SIZE:0x%x) APPEARED\nMAYBE INFLATE MEMORY AREA WAS BROKEN.\n";
__attribute__((section(".rodata.0x005553F0"))) const char D_005553F0[48] = "pac_makeTextureTable:\n\tTexture not Found. %s\n";
__attribute__((section(".rodata.0x00555420"))) const char D_00555420[56] = "pac_makePacket:Material Table Not Found. (%s:%s)\n";
__attribute__((section(".rodata.0x00555458"))) const char D_00555458[24] = "illegal size = %d\n";
__attribute__((section(".rodata.0x00555470"))) const char D_00555470[32] = "illegal vertex num %d\n";

#include "include_asm.h"
#include "matching.h"

extern int D_00672F90[];
extern int D_00633C3C;
extern int D_004C7710[];

void func_001FBA80(int v);
void func_001FBAA8(int a, void *p, int zero);
void func_001FB8B8(void);

INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00118AB8);

void func_00118B18(int count, int arg) {
    int *p;
    int v, a;

    p = (int *)D_004C7710[4];
    D_004C7710[6] = 0;
    D_004C7710[3] = (int)p;
    D_004C7710[7] = 0;
    D_004C7710[5] = (int)p;
    *(long long *)p = 0x10000000LL;
    D_004C7710[4] = (int)(p + 2);

    if ((unsigned)(count - 1) < 5) {
        int *cp;
        cp = 0;
        switch (count - 1) {
        case 0:
        case 1:
            cp = (int *)D_004C7710[4];
            *cp = 0x03000100;
            a = 0x02000180;
            break;
        case 2:
            cp = (int *)D_004C7710[4];
            *cp = 0x03000100;
            a = 0x02000180;
            MATERIALIZE(cp);
            break;
        case 3:
            cp = (int *)D_004C7710[4];
            *cp = 0x03000010;
            a = 0x020001F8;
            break;
        case 4:
            cp = (int *)D_004C7710[4];
            *cp = 0x03000010;
            a = 0x0200016A;
            break;
        }
        cp += 1;
        D_004C7710[4] = (int)cp;
        *cp = a;
        D_004C7710[4] = (int)(cp + 1);
    }

    {
        int *q = (int *)D_004C7710[4];
        D_004C7710[5] = (int)q;
        *(long long *)q = 0x60000000LL;
        D_004C7710[4] = (int)(q + 2);
        q[2] = 0;
        D_004C7710[4] = (int)(q + 3);
        q[3] = 0;
        D_004C7710[4] = (int)(q + 4);
    }
    func_001FBA80(arg);
    func_001FBAA8(5, (void *)D_004C7710[3], 0);
    func_001FB8B8();
}
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
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_00118FD8);
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
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A238);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A2A8);
INCLUDE_ASM("asm/nonmatchings/src/Packet", func_0011A2F0);
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
__attribute__((section(".rodata.0x00554FF8"))) const char D_00554FF8[64] = "\033[31msorce normal model data broken! %f %f %f %f [%d]\033[0m\n";
/* ASCII preview: "<ESC>[31msorce cluster model data broken! %f %f %f %f [%d]<ESC>[0m<LF>" */
__attribute__((section(".rodata.0x005550F8"))) const char D_005550F8[64] = "\033[31msorce cluster model data broken! %f %f %f %f [%d]\033[0m\n";
/* ASCII preview: "<ESC>[31mMaxPacketSize = %d<ESC>[0m<LF>" */
__attribute__((section(".rodata.0x00555378"))) const char D_00555378[32] = "\033[31mMaxPacketSize = %d\033[0m\n";
