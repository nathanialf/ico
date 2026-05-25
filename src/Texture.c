/* Texture.c -- typed sdata / lit4 definitions for this TU.
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


const char D_00555EA0[56] = "tex_loadImage:\310\275\312\314\244\307\244\255\244\312\244\244\245\306\245\257\245\271\245\301\245\343\245\325\245\251\241\274\245\336\245\303\245\310\244\307\244\271.\n";

const char D_00555ED8[16] = "src/Texture.c";

const char D_00555EE8[56] = "tex_loadImage:\245\306\245\257\245\271\245\301\245\343\244\316\245\265\245\244\245\272\244\254\302\347\244\255\244\271\244\256\244\336\244\271.\n";

const char D_00556010[64] = "DIRECT\244\307\244\342CLUT\244\307\244\342\244\312\244\244\245\306\245\257\245\271\245\301\245\343\245\277\245\244\245\327\244\254\273\330\304\352\244\265\244\354\244\336\244\267\244\277.\n";

const char D_00556050[56] = "tex_transTM2:\245\337\245\303\245\327\245\336\245\303\245\327\245\306\245\257\245\271\245\301\245\343\244\316\313\347\277\364\244\254\302\277\244\271\244\256\244\336\244\271.\n";

const char D_00556088[72] = "\245\306\245\257\245\271\245\301\245\343\244\254\262\365\244\354\244\306\244\244\244\336\244\271.\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n";

const char D_005563A0[80] = "tex_makeTexturePacket:\245\306\245\257\245\271\245\301\245\343\244\316\245\346\241\274\245\266\241\274\245\271\245\332\241\274\245\271\245\325\245\251\241\274\245\336\245\303\245\310\244\254\260\333\276\357\244\307\244\271.'%s'\n";

const char D_005563F0[64] = "TEXTURE BROKEN. \"%s\"\n    I:%d C:%d iadr:%p cadr:%p hadr:%p\n";

const char D_00556430[56] = "\033[31m\245\321\245\271\244\316\260\343\244\246\306\261\314\276\244\316\245\306\245\257\245\271\245\301\245\343\244\362\306\311\244\337\271\376\244\342\244\246\244\310\244\267\244\336\244\267\244\277.\n";

const char D_00556478[64] = "\245\306\245\257\245\271\245\301\245\343\244\254\302\277\244\271\244\256\244\336\244\271.\245\306\245\257\245\271\245\301\245\343\245\352\245\271\245\310\316\316\260\350\244\362\301\375\244\344\244\267\244\306\244\257\244\300\244\265\244\244\n";

const char D_005564B8[40] = "\245\306\245\257\245\271\245\301\245\343 \"%s\" \244\254\244\337\244\304\244\253\244\352\244\336\244\273\244\363.\n";

const char D_005564E0[48] = "tex_TransTexture:INVALID TEXTURE ID. %d/%d\n";

const char D_00556510[56] = "tex_TransTexture:\245\306\245\257\245\271\245\301\245\343\244\316\305\276\301\367\244\313\274\272\307\324\244\267\244\336\244\267\244\277. %d\n";

const char D_00556548[56] = "tex_TransTexture:\245\306\245\257\245\271\245\301\245\343\244\316\305\276\301\367\244\313\274\272\307\324\244\267\244\336\244\267\244\277. %d:%s\n";

const char D_00556580[72] = "illegal user space data [%s] Clut Scroll (color:%d start:%d end:%d)\n";

const char D_005565C8[24] = "%8s:SIZE=%3dX%3d";

const char D_005565E0[24] = "/%d Name:%s x:x%d";

const char D_00556620[48] = "No.              Name   Size MIP IMG CL US";

const char D_00556650[32] = "%03d%18s%7d:%1d/%1d:%s:%s:%s";

const char D_00556670[16] = "   %17s %7d ";

const char D_00556680[24] = "TotalTextureSize";

const char D_00556728[16] = " Fog Strength ";

const char D_00556738[16] = " Fog Far      ";

const char D_00556748[16] = " Fog Near     ";

const char D_00556758[16] = " Fog Offset A ";

const char D_00556768[16] = " Fog Color A  ";

const char D_00556778[16] = " Fog Color B  ";

const char D_00556788[16] = " Fog Color G  ";

const char D_00556798[16] = " Fog Color R  ";

const char D_005567A8[16] = " Fog On/Off   ";

const char D_005567C0[16] = "Fog Tool";

const char D_005567D0[16] = "Fog %s => %s\n";

const char D_005567E0[16] = "Fog %s => %d\n";

#include "matching.h"
/* Inlined data (Phase 3e) — migrated from Texture_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_00275204 = 0x00000000;
unsigned char D_00275208[12] = { 0 };
unsigned int D_00276268[18] = { 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00000004, 0x00000004, 0x00000001, 0x00000003, 0x00000002, 0x00000000, 0x00000002, 0x00000002, 0x00000014, 0x00000001, 0x00000001, 0x00000013, 0x00000002, 0x00000001 };
const char D_005565F8[40] = "Texture List [%d] PUSH '\200' TO EDIT US.";
unsigned int D_00631E10[2] = { 0x80808080, 0x00000000 };
const char D_00631E18[8] = "SELTEX";
const char D_00631E20[8] = "SCRL-U";
const char D_00631E28[8] = "SCRL-V";
const char D_00631E30[8] = "AMP-U ";
const char D_00631E38[8] = "AMP-V ";
const char D_00631E40[8] = "CS-BGN";
const char D_00631E48[8] = "CS-END";
const char D_00631E50[8] = "CS-SPD";
const char D_00631E58[8] = "CS-STP";
const char D_00631E60[8] = "SHINE ";
const char D_00631E68[8] = "SMPMAG";
const char D_00631E70[8] = "SMPMIN";
const char D_00631E78[8] = "TEXFNC";
const char D_00631E80[8] = "ALPTST";
const char D_00631E88[8] = "ALPFAI";
const char D_00631E90[8] = "MIPMAPK";
const char D_00631E98[8] = "MIPMAPL";
unsigned int D_00631EA0[2] = { 0x00000001, 0x00000000 };
unsigned int D_00631EA8[2] = { 0xFFFFFF00, 0xFFC0C000 };
const char D_00631EB0[8] = "%s:%d";
const char D_00631EB8[8] = "%s:%f";
const char D_00631EC0[8] = "C-8";
const char D_00631EC8[8] = "C-4";
const char D_00631ED0[8] = "D32";
const char D_00631ED8[8] = "D24";
const char D_00631EE0[8] = "D16";
const char D_00631EE8[8] = "NON";
const char D_00631EF0[8] = "32";
const char D_00631EF8[8] = "24";
const char D_00631F00[8] = "16";
const char D_00631F08[8] = "--";
unsigned int D_00631F10[2] = { 0x00000080, 0x00000000 };
unsigned int D_00631F18 = 0x00000020;
unsigned int D_00631F1C = 0x00000000;
unsigned char D_00631F20[8] = { 0 };

/* Inlined data (Phase 3e) — migrated from Texture_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* Inlined data (Phase 3e) — migrated from Texture_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_00630A78 = 0x40490FDB;
unsigned int D_00630A7C = 0x4622F983;
unsigned int D_00630A80 = 0x40490FDB;
unsigned int D_00630A84 = 0x4622F983;
unsigned int D_00630A88 = 0x3727C5AC;
unsigned int D_00630A8C = 0x3C23D70A;
unsigned int D_00630A90 = 0xC4FFE000;

/* Inlined data (Phase 3e) — migrated from Texture_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* pointer / address tables */
void *D_002762B0[6] = { (void *)0x00631DC8, (void *)0x00631DC0, (void *)0x00631DB8, (void *)0x00631DB0, (void *)0x00631DA8, (void *)0x00631DA0 };
void *D_002762C8[6] = { (void *)0x00631EE8, (void *)0x00631EE0, (void *)0x00631ED8, (void *)0x00631ED0, (void *)0x00631EC8, (void *)0x00631EC0 };
void *D_002762E0[4] = { (void *)0x00631F08, (void *)0x00631F00, (void *)0x00631EF8, (void *)0x00631EF0 };
void *D_002762F0[2] = { (void *)0x00631F18, (void *)0x00631F10 };

/* misaligned arrays (scalar head + aligned tail) */
unsigned int D_0027525C = 0x00000000;
unsigned char D_00275260[76] = { 0 };

#include "include_asm.h"

extern void func_001FBAA8(int a0, int a1, int a2);
extern void func_001FB8B8(void);
extern void func_0012CEF8(void);

INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012AED0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012AFC0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012B1C0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012B850);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012BA68);

void func_0012BBE8(int a0)
{
    func_001FBAA8(2, a0 + 0x58, 5);
    func_001FB8B8();
}

INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012BC0C);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012BC10);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012BEB0);
#if 0

void func_0012BEB0(unsigned char *_a0, unsigned char *_a1) {
    register unsigned char *a0 __asm__("$10") = _a0;
    register unsigned char *a1 __asm__("$11") = _a1;
    int fmt_idx;
    unsigned char *table;
    unsigned int *entry;
    MATERIALIZE(a0);
    MATERIALIZE(a1);
    fmt_idx = (a0[0x12] & 0x3F) * 12;
    table = (unsigned char *)D_00276268;
    entry = (unsigned int *)(table + fmt_idx);
    if (entry[1] == 0) __asm__ volatile ("break 0,7");

    *(short *)((char *)a1 + 0xEA) = 8;

    {
        int idx2 = a0[0x12] & 0x3F;
        unsigned int *entry2 = (unsigned int *)(table + idx2 * 12);
        unsigned int fmt0 = entry2[0];
        unsigned short width = *(unsigned short *)(a0 + 0x14);
        int blk;
        if (fmt0 >= 0x3B) {
            blk = 0;
        } else {
            switch (fmt0) {
            case 0: case 1: case 2: case 10: case 27: case 35: case 43: case 47: case 48: case 49: case 57: {
                int w = (int)width + 0x3F;
                blk = (int)((unsigned)w >> 6);
                break;
            }
            case 19: case 20: {
                int w = (int)width + 0x3F;
                int x = (int)((unsigned)w >> 6);
                blk = (x & 1) + x;
                break;
            }
            default:
                blk = 0;
                break;
            }
        }
        *(short *)((char *)a1 + 0xE8) = (short)blk;
    }

    {
        unsigned short n_levels = *(unsigned short *)(a1 + 0xE0);
        if (n_levels != 0) {
            int level = 0;
            unsigned char lbu13 = a0[0x13];
            do {
                int s_off = level * 0x24;
                int blk_size = lbu13 * 0xC;
                unsigned short tw = *(unsigned short *)(a0 + 0x14);
                unsigned short th = *(unsigned short *)(a0 + 0x16);
                unsigned int *p = (unsigned int *)(table + blk_size);
                char *out_base = (char *)a1 + s_off;
                int w_shr = (int)tw >> level;
                int h_shr = (int)th >> level;
                int wh = w_shr * h_shr;
                if (p[1] == 0) __asm__ volatile ("break 0,7");
                {
                    int q = wh / (int)p[1];
                    int q_pos = (unsigned)q >> 31;
                    int q_avg = (q + q_pos) >> 1;
                    int by_p2 = q_avg * (int)p[2];
                    *(short *)(out_base + 0x10E) = (short)(by_p2 >> 6);
                }
                {
                    unsigned char lbu13_in = a0[0x13];
                    unsigned short tw_in = *(unsigned short *)((char *)a0 + 0x14);
                    unsigned int *p2 = (unsigned int *)(table + lbu13_in * 0xC);
                    int w_shr_in = (int)tw_in >> level;
                    unsigned int fmt = p2[0];
                    int v;
                    if (fmt >= 0x3B) {
                        v = 0;
                    } else {
                        switch (fmt) {
                        case 0: case 1: case 2: case 10: case 27: case 35: case 43: case 47: case 48: case 49: case 57: {
                            int w = w_shr_in + 0x3F;
                            v = (int)((unsigned)w >> 6);
                            break;
                        }
                        case 19: case 20: {
                            int w = w_shr_in + 0x3F;
                            int x = (int)((unsigned)w >> 6);
                            v = (x & 1) + x;
                            break;
                        }
                        default:
                            v = 0;
                            break;
                        }
                    }
                    *(short *)(out_base + 0x10C) = (short)v;
                }
                level++;
            } while (level < (int)n_levels);
        }
    }
}
#endif
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C050);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C3D0);
#if 0
extern const char D_00556088[];
extern const char D_00631DD8[];
void func_0012C050(unsigned char *a0, unsigned char *a1);

void func_0012C3D0(unsigned char *a0, unsigned char *a1) {
    int row;
    int lbu13;

    for (row = 0; row < 7; row++) {
        int col;
        unsigned char *p = a1 + 0x110 + row * 0x24;
        for (col = 12; col >= 0; col--) {
            *(short *)(p - col * 2) = 0;
        }
    }
    *(short *)(a1 + 0xE8) = 0;
    {
        int col;
        unsigned char *p = a1 + 0xEC + 0x18;
        for (col = 12; col >= 0; col--) {
            *(short *)(p - col * 2) = 0;
        }
    }

    lbu13 = a0[0x13];
    if (lbu13 == 0) goto tail;
    if (lbu13 < 4) {
        unsigned short n_levels = *(unsigned short *)(a1 + 0xE0);
        int level = 0;
        if (n_levels == 0) goto tail;
        do {
            unsigned int *entry = (unsigned int *)((unsigned char *)D_00276268 + lbu13 * 0xC);
            int w = (int)*(unsigned short *)(a0 + 0x14) >> level;
            int h = (int)*(unsigned short *)(a0 + 0x16) >> level;
            int wh = w * h;
            unsigned char *out = a1 + level * 0x24;
            if (entry[1] == 0) __asm__ volatile("break 0,7");
            {
                int q = wh / (int)entry[1];
                int q_avg = (q + ((unsigned)q >> 31)) >> 1;
                *(short *)(out + 0x10E) = (short)((q_avg * (int)entry[2]) >> 6);
            }
            {
                unsigned int *p2 = (unsigned int *)((unsigned char *)D_00276268 + a0[0x13] * 0xC);
                int ws = (int)*(unsigned short *)(a0 + 0x14) >> level;
                unsigned int fmt = p2[0];
                int v;
                if (fmt >= 0x3B) {
                    v = 0;
                } else {
                    switch (fmt) {
                    case 0: case 1: case 2: case 10: case 27: case 35: case 43: case 47: case 48: case 49: case 57:
                        v = (int)((unsigned)(ws + 0x3F) >> 6);
                        break;
                    case 19: case 20: {
                        int x = (int)((unsigned)(ws + 0x3F) >> 6);
                        v = (x & 1) + x;
                        break;
                    }
                    default:
                        v = 0;
                        break;
                    }
                }
                *(short *)(out + 0x10C) = (short)v;
            }
            level++;
        } while (level < (int)n_levels);
        goto tail;
    }
    if (lbu13 < 6) {
        func_0012BEB0(a0, a1);
        goto tail;
    }
    func_001A6E28(D_00556088, a1, a0[0x12], *(int *)(a1 + 0x108), *(int *)(a1 + 0xE4), a1);
    func_001AD768((const char *)D_00555ED8, 0x443);
    func_00263FF0((const char *)D_00555ED8, D_00631DD8, 0x443);
tail:
    func_0012C050(a0, a1);
}
#endif
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C610);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C6F0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C8F8);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012CB70);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012CEF8);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012D218);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012D370);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012D4A0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012DA48);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012DE00);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012DE80);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012DF98);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012E0D8);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012E528);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012E940);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012F818);
int func_0012FCE0(int a0)
{
    int one_outer = 1;
    int ret = -1;
    int v1 = 0;
    if (!(one_outer < a0)) {
        ret = 0;
        goto exit;
    }
    do {
        v1++;
        if (!(v1 < 11)) goto exit;
        {
            int one_inner = 1;
            MATERIALIZE(one_inner);
            if (!((one_inner << v1) < a0)) {
                ret = v1;
                goto exit;
            }
        }
    } while (1);
exit:
    return ret;
}

void func_0012FD30(void) {
    func_0012CEF8();
    DEFEAT_TCO();
}
