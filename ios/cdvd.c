/* cdvd.c -- typed sdata / lit4 definitions for this TU.
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

const char D_005524E0[4] = "P*U";
const char D_005567F0[16] = "SCUS_971.13";
const char D_00556800[24] = "wait insert ico disk\n";
const char D_00556818[16] = "ios/cdvd.c";
const char D_00556828[56] = "iosCdvdMgrSearchFile: warning filename length over\n";
const char D_00556860[96] = "iosCdvdMgrSearchFile: warning iosCdvdSrhBuff over\n\000\000\000\000\000\000\nCan't alloc cd stream buff %d \n\000\000\000\000\000\000\000";
const char D_005568C0[24] = "file %s not found\n";
const char D_005568D8[16] = "read done\n";
const char D_005568E8[40] = "temp_loadfunc::%s  (size:%d)(segid=%d)\n";
const char D_00556910[16] = "try load %s\n";
const char D_00556920[64] = "------------------------------------------------files %d -----\n";
const char D_00556960[32] = "file id %s %d time %f read %d \n";
const char D_00556980[24] = "inflate time %f\n";
const char D_00556998[24] = "load time %d %f Sec\n";
const char D_005569B0[16] = "skip !!!!";
const char D_005569C0[16] = "RING %d\n";
const char D_005569D0[40] = "iosCdvdHandlerReadInflate size %d\n";
const char D_005569F8[24] = "Decompression error\n";
const char D_00556A10[16] = "DFDATAS/%s";
const char D_00556A20[16] = "DFDATAS/DATA.DF";
const char D_00556A30[24] = "CD MANAGER START";
const char D_00556A48[40] = "iosMcManager: recv command %d error.";
const char D_00556A70[16] = "** %d %s %p\n";
const char D_00556A80[24] = "%s lsn:%d handler:%p\n";
const char D_00556A98[40] = "lsn %d cnt %d size %d buf %p %s\n";
const char D_00556AC0[40] = "lsn %d cnt %d size %d iopbuf %p %s\n";
const char D_00556AE8[24] = "cd read error %d\n";
const char D_0062EA90[40] = "libpad: Module version mismatch ";
const char D_0062EB40[8] = "ERROR";
const char D_0062EB48[8] = "STABLE";
const char D_0062EB50[8] = "EXECCMD";
const char D_0062EB58[16] = "FINDCTP1";
const char D_0062EB70[16] = "DISCONNECT";
const char D_0062EB80[8] = "BUSY";
const char D_0062EB88[8] = "FAILED";
const char D_0062EB90[16] = "COMPLETE";
const char D_0062EC40[40] = "The size of work area is too small";
const char D_0062EC68[32] = "work area size is too small";
const char D_0062EC88[72] = "image buffer needs to be aligned to 64byte boundary(0x%08x)";
const char D_0062ECE8[32] = "the second field is missing";
const char D_0062ED18[24] = "vertical size > 2800";
const char D_0062ED30[40] = "_chroma_format needs to be 1: 420";
const char D_0062ED58[32] = "Unsupported profile/level";
const char D_0062ED78[48] = "_sequenceScalableExtension() is not implemented";
const char D_0062EDA8[24] = "Unknown Extension";
const char D_0062EDC0[56] = "_pictureSpatialScalableExtension is not supported";
const char D_0062EDF8[56] = "_pictureTemporalScalableExtension is not supported";
const char D_0062EE30[40] = "Invalid modion type -- ignored(%d)";
const char D_0062EE58[32] = "(a) invalid motion_type(%d)-0";
const char D_0062EE78[32] = "(b) invalid motion_type(%d)-1";
const char D_0062EE98[32] = "(c) invalid motion_type(%d)-2";
const char D_0062EEB8[24] = "intra && skip MB";
const char D_0062EED0[32] = "Error code detected(BDEC)";
const char D_0062EEF0[56] = "Invalid macroblock_address_increment code(0x%08x)";
const char D_0062EF28[32] = "= Skip to the next picture =";
const char D_0062EF48[40] = "slice_start_code(0x%08x) out of range";
const char D_0062EF70[32] = "_sliceA0(): error happens";
const char D_0062EF90[32] = "Too many macroblocks in picture";
const char D_0062EFB0[48] = "skiped macroblock in I picure is not allowed";
const char D_0062EFE0[32] = "Invalid macroblock_type code: 0";
const char D_0062F000[40] = "load_chroma_intra_quantizer_matrix == 1";
const char D_0062F028[48] = "load_chroma_non_intra_quantizer_matrix == 1";
const char D_0062F058[32] = "odd number of field pictures";
const char D_0062F078[32] = "unknown picture sutructure";
const char D_0062F2C0[8] = "acosf";
const char D_0062F2C8[8] = "asinf";
const char D_0062F2D0[8] = "atan2f";
const char D_0062F2D8[8] = "fmodf";
const char D_0062FD80[16] = "C";
const char D_0062FDB0[24] = "0123456789abcdef";
const char D_0062FDC8[8] = "(null)";
const char D_0062FDD0[24] = "0123456789ABCDEF";
const char D_0062FDE8[40] = "bug in vfprintf: bad base";
const char D_0062FFA0[8] = "Inf";
const char D_0062FFA8[8] = "NaN";
const char D_0062FFB0[24] = "0123456789abcdef";
const char D_0062FFC8[8] = "(null)";
const char D_0062FFD0[24] = "0123456789ABCDEF";
const char D_00630000[8] = "e";
const char D_00630008[8] = "0";
const char D_00630010[16] = ".";
const char D_00630600[16] = "Infinity";
const char D_00630610[8] = "NaN";
const char D_00630618[8] = "0";
const char D_00630690[8] = ".";
const char D_00630698[8] = "C";
const float D_00630890[2] = { 1.3105224e-06f, 1.75f };

/* Cross-TU symbols referenced by the migrated pointer tables below. */
extern unsigned char D_00556C20[];   /* in ios/mblock.c */
extern unsigned char D_00556C30[];   /* in ios/mblock.c */
extern unsigned char D_00556C40[];   /* in ios/mblock.c */
extern void func_00138260(int *a0);
extern void func_00138390(int *a0);
extern void func_001383D8(int *a0);
extern void func_001383F8(int *a0);
extern void func_00138510(int *a0);
extern void func_00138618(int *a0);

/* Data migrated from cdvd_data.c. */

/* .data — zero buffers and typed tables. D_002751CC and its
 * 32-byte trailing zero pad are NOT migrated here — the symbol's
 * VMA is 4-aligned but ee-gcc forces `.align 3` (8-byte) on every
 * typed def under -mips3, so any tracked def would pad +4 and break
 * SHA-1. The legacy sidecar handles the 4-aligned scalar via its
 * own non-C asm-style emission path. */
unsigned char D_00275120[16] = { 0 };
unsigned char D_00275130[32] = { 0 };
unsigned char D_00275150[48] = { 0 };
unsigned char D_00275180[76] = { 0 };
/* D_002751CC = 0  --  stays in sidecar (4-aligned VMA, see above). */

/* Pointers to the "On"/"Off" sdata labels further down in this TU. */
extern const char D_00631F30[8];  /* "On"  (forward, defined below) */
extern const char D_00631F38[4];  /* "Off" (forward, defined below) */
const char *D_002762F8[2] = { D_00631F38, D_00631F30 };

unsigned char D_00276300[33216] = { 0 };
int           D_0027E4C0[12] = { 0 };
unsigned char D_0027E4F0[48] = { 0 };
unsigned char D_0027E520[8]  = { 0 };
unsigned char D_0027E528[6872] = { 0 };
unsigned char D_00280000[136] = { 0 };
unsigned char D_00280088[2584] = { 0 };

/* Bit-counts/lookup ladder (u16 LE, last 3 slots are alignment pad). */
unsigned short D_00280AA0[32] = {
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
    0x0B, 0x0D, 0x0F, 0x11, 0x13, 0x17, 0x1B, 0x1F,
    0x23, 0x2B, 0x33, 0x3B, 0x43, 0x53, 0x63, 0x73,
    0x83, 0xA3, 0xC3, 0xE3, 0x0102, 0, 0, 0,
};

/* Paired (idx,idx) table — 16 pairs as u16[32]. */
unsigned short D_00280AE0[32] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 4,
    5, 5, 5, 5, 0, 0x63, 0x63, 0,
};

/* Companion ladder + pair table (u16 LE, alignment pad in last 2). */
unsigned short D_00280B20[32] = {
    0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0007, 0x0009, 0x000D,
    0x0011, 0x0019, 0x0021, 0x0031, 0x0041, 0x0061, 0x0081, 0x00C1,
    0x0101, 0x0181, 0x0201, 0x0301, 0x0401, 0x0601, 0x0801, 0x0C01,
    0x1001, 0x1801, 0x2001, 0x3001, 0x4001, 0x6001, 0, 0,
};
unsigned short D_00280B60[32] = {
    0, 0, 0, 0,
    1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
    7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12,
    13, 13, 0, 0,
};

/* Index permutation table; tail three slots are pointers to mblock
 * shared-buffer label `D_00556C20`. */
unsigned int D_00280BA0[24] = {
    0x10, 0x11, 0x12, 0x00,
    0x08, 0x07, 0x09, 0x06,
    0x0A, 0x05, 0x0B, 0x04,
    0x0C, 0x03, 0x0D, 0x02,
    0x0E, 0x01, 0x0F, 0x00,
    (unsigned int)D_00556C20, (unsigned int)D_00556C20,
    (unsigned int)D_00556C20, 0,
};

/* Forward decl for the sdata symbol referenced by D_00280C00 below. */
extern unsigned char D_00632058[8];

/* Pointer table — five buffer labels in `ios/mblock.c` + one sdata
 * scratch label in this TU. */
unsigned char *D_00280C00[6] = {
    D_00556C40, D_00556C30, D_00556C20, D_00556C20, D_00556C20, D_00632058,
};

/* D_00280C18: 6 entries of (id, fn_ptr, fn_ptr). Entries 0..3 have
 * the first fn_ptr == NULL. Struct type is VMA-derived. */
typedef void (*T_00280C18_fn)(int *);
typedef struct { unsigned int id; T_00280C18_fn f1; T_00280C18_fn f2; } T_00280C18_rec;
T_00280C18_rec D_00280C18[6] = {
    { 1, 0,             func_00138510 },
    { 2, 0,             func_00138618 },
    { 3, 0,             func_00138618 },
    { 4, 0,             func_00138618 },
    { 0, func_00138390, func_00138260 },
    { 5, func_001383F8, func_001383D8 },
};
unsigned char D_00280F88[56] = { 0 };

/* .rodata — typed pointer/mask tables + a couple of in-place
 * structures whose original sidecar typing split the head and tail
 * into D_X + `_pad_X`. We absorb the full extent into one array.
 *
 * D_00556698[2] holds two pointers that fall *inside* arrays owned
 * by this TU rather than at typed-symbol boundaries:
 *   0x005567A8 → inside D_005566A4's follow-on table below
 *   0x002751A0 → `&D_00275180[0x20]` (offset 0x20 into the 76-byte
 *               zero buffer above)
 * The mid-array offsets can't be expressed as `&D_X`, so we keep
 * them as integer literals. */
const unsigned int D_00556698[2] = { 0x005567A8, 0x002751A0 };
const unsigned char D_005566A0[4] = { 0 };
/* D_005566A4 and D_00564A6C are 4-aligned VMAs — stay in the sidecar
 * (same align-3-forced-by-ee-gcc issue as D_002751CC). */
const unsigned int D_005567B8[2] = { 0xFFFFFF00, 0xFF000000 };  /* byte masks */

/* .sdata — small mutable scratch buffers + format strings. */
unsigned char D_00631E08[8] = { 0 };
const char D_00631F28[8] = "Z";
const char D_00631F30[8] = "On";
const char D_00631F38[4] = "Off";
unsigned int D_00631F3C = 0;
const char D_00631F40[8] = "%s : %s";
const char D_00631F48[8] = "%s : %d";
const char D_00632080[8] = "done 1\n";
unsigned char D_006320B0[8] = { 0 };
const char D_006320B8[8] = "e";
const char D_006320C0[8] = "0";
const char D_006320C8[8] = "align";
const char D_006320D0[8] = "ALLOC ";
const char D_006320D8[8] = "%c";
unsigned int D_006320E0[2] = { 0x0000000A, 0x00000000 };
const char D_006320E8[8] = "0";
const char D_006320F0[8] = "%p\n";
const char D_006320F8[8] = "%d %d\n";
const char D_00632100[8] = "evt:%d\n";
unsigned char D_00632108[8] = { 0 };

/* Inlined data (Phase 3e) — migrated from cdvd_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* Inlined data (Phase 3e) — migrated from cdvd_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* misaligned arrays (scalar head + aligned tail) */
unsigned int D_002751CC = 0x00000000;
unsigned char D_002751D0[32] = { 0 };
unsigned int D_005566A4 = 0x00000001;
unsigned int D_005566A8[32] = { 0x00556798, 0x002751B0, 0x00000000, 0x000000FF, 0x00556788, 0x002751B4, 0x00000000, 0x000000FF, 0x00556778, 0x002751B8, 0x00000000, 0x000000FF, 0x00556768, 0x002751BC, 0x00000000, 0x000000FF, 0x00556758, 0x002751C0, 0x00000000, 0x000000FF, 0x00556748, 0x002751C4, 0x00000000, 0x000000FF, 0x00556738, 0x002751C8, 0x00000000, 0x000000FF, 0x00556728, 0x00275240, 0x00000000, 0x000000FF };
unsigned int D_00564A6C = 0x6E6F6369;
unsigned int D_00564A70[36] = { 0x6F63692F, 0x79732E6E, 0x00000073, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000003C4, 0x6E6F6369, 0x796F622F, 0x6B6C625F, 0x6F63692E, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00017588, 0x6E6F6369, 0x796F622F, 0x6B6C625F, 0x6F63692E, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00017588, 0x6E6F6369, 0x796F622F, 0x6B6C625F, 0x6F63692E, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00017588, 0x00000000 };

#include "matching.h"
#include "include_asm.h"

extern void func_0013A5B8(int *a0, int a1, int a2);
extern int func_0024DA80(int a0);
extern int func_0024D7B0(void);
extern void func_0024A1E0(int a0);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001312F0);
extern int D_00632870;
extern int D_00633C78;
extern int D_0063286C;
extern int func_00135EB8(int a0, const char *fmt, int line);
extern void func_0024D9B8(int a0, int a1, int a2);
extern int func_0024D9E8(int a0, int a1);
extern int func_00135A48(int a0, int a1);
extern void func_00133570(void);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131480);
extern void func_001354B8(int a0);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131560);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001315A8);
extern int D_00632024;
extern void *func_0013A0F8(int a0, int a1, const char *fmt, int line);
extern void func_00139598(void *p);
extern void func_001A6E28();

void func_00131780(int a0, char *a1, int a2, int a3, int a4, int a5, int a6)
{
    void *s1 = func_0013A0F8(D_00632024, a2, D_00556818, 0x33C);
    func_001320E8((int *) a0, s1, a2);
    func_001A6E28(D_005568E8, a1, a2, a6);
    func_00139598(s1);
}
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131818);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131C90);
extern int func_00135580(int a0, void *buf, int n);

void func_00132038(int *a0, void *buf, int n)
{
    char *p = (char *) buf;
    long long ret;
    for (;;)
    {
        ret = func_00135580(a0[0x15C / 4], p, n);
        if (ret <= 0)
        {
            break;
        }
        p += ret;
        n -= ret;
    }
    func_001A6E28(D_005569D0, a0[0x24 / 4]);
    if (ret < 0)
    {
        func_001A6E28(D_005569F8);
    }
}
extern void func_00132038(int *a0, void *buf, int n);
extern void func_00131C90(int *a0, void *buf, int n);
extern unsigned char D_006A64B8[];

void func_001320E8(int *a0, void *a1, int a2)
{
    if (a1 != 0)
    {
        if ((*(long long *) a0 & 1) == 1)
        {
            func_00132038(a0, a1, a2);
        }
        else
        {
            func_00131C90(a0, a1, a2);
        }
        return;
    }
    while (a2 > 0)
    {
        int n = (a2 < 0x401) ? a2 : 0x400;
        void *buf = D_006A64B8;
        if ((*(long long *) a0 & 1) == 1)
        {
            func_00132038(a0, buf, n);
        }
        else
        {
            func_00131C90(a0, buf, n);
        }
        a2 -= n;
    }
}
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001321C8);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132388);
union U001325D8
{
    long long ll;
    int i[2];
};

void func_001325D8(int a0, int a1)
{
    union U001325D8 *p = (union U001325D8 *) a0;
    p->i[1] = 1;
    p->ll = (p->ll & ~1LL) | (a1 & 1);
    func_0013A5B8(D_0027E4C0, a0, 0);
}

void func_00132610(int a0)
{
    *(int *)(a0 + 0x4) = 2;
    func_0013A5B8(D_0027E4C0, a0, 0);
}

INCLUDE_ASM_NOP_PAD(func_0013262C);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132630);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132930);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132B90);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132DC0);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132FF0);

void func_001331D8(int a0)
{
    int *s0 = (int *) a0;
    int v0;
    do { s0[0xC / 4] = 0; } while (0);
    v0 = func_0024DA80(a0);
    if (v0 == 0)
    {
        s0[0xC / 4] = func_0024D7B0();
    }
    return func_0024A1E0(s0[0x160 / 4]);
}

extern void func_00264DF8(unsigned char *buf, const char *fmt, int a0);
extern int func_00265168(int a0, unsigned char *buf);
extern char D_0062FC79[];
extern char D_00631F70[];

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00133218);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001332B8);
