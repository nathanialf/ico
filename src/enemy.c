/* enemy.c -- typed sdata / lit4 definitions for this TU.
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


unsigned int D_004C09D8[226] = { 0x00618B20, 0x00000080, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000003, 0x00618B10, 0x00000084, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000003, 0x00618B00, 0x00000004, 0x004C09C0, 0x00000000, 0x00000001, 0x00000000, 0x00000001, 0x00618AF0, 0x00000008, 0x004C09C8, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00618AE0, 0x0000000C, 0x00000000, 0x00000003, 0x00000000, 0x00000000, 0x00000168, 0x00618AD0, 0x00000090, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x0000000A, 0x00618AC0, 0x00000010, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000064, 0x00618AB0, 0x00000014, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x00618AA0, 0x00000018, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000002, 0x00618A90, 0x0000001C, 0x00000000, 0x00000001, 0x00000000, 0xFFFFFFF6, 0x0000000A, 0x00618A80, 0x00000088, 0x00000000, 0x00000002, 0x00000000, 0xFFFFFF4C, 0x000000B4, 0x00618A70, 0x0000008C, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x00618A60, 0x00000020, 0x00000000, 0x00000002, 0x00000000, 0xFFFFFF4C, 0x000000B4, 0x00618A50, 0x00000024, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x00618A40, 0x00000028, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000002, 0x00618A30, 0x0000002C, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000032, 0x00618A20, 0x00000030, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x00618A10, 0x00000034, 0x00000000, 0x00000001, 0x00000000, 0xFFFFFFCE, 0x00000032, 0x00618A00, 0x00000038, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x006189F0, 0x0000003C, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x006189E0, 0x00000040, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000050, 0x006189D0, 0x00000044, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000003E8, 0x006189C0, 0x00000048, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x006189B0, 0x0000004C, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000064, 0x006189A0, 0x00000050, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x00618990, 0x00000054, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x00618980, 0x00000058, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000003E8, 0x00618970, 0x0000005C, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0x00633360, 0x00000070, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00633358, 0x00000074, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00633350, 0x00000078, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

unsigned int D_004C0D60[4] = { 0x00000000, 0x000000C0, 0x000000FF, 0x0000001C };

unsigned int D_004C0D70[4] = { 0x00000000, 0x00000020, 0x000000FF, 0x0000001C };

unsigned int D_004C0D80[4] = { 0x000000FF, 0x00000000, 0x00000020, 0x0000001C };

unsigned int D_004C0D90[4] = { 0x00000000, 0x000000FF, 0x00000020, 0x0000001C };

unsigned int D_004C0DA0[16] = { 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000 };

unsigned int D_004C0DE0[16] = { 0x00000002, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000001, 0x00000005, 0x00000000, 0x00000000 };

unsigned char D_004C0E20[96] = { 0 };

const char D_004C0E80[16] = "2\000\000\000b\000\000\000\200\000\000\000\200";

const char D_004C0E90[16] = "\232\231\231>333?\000\000\200?";

const char D_00618CB8[56] = "Effect Tools: PUSH 2-CON'\202' TO SAVE SELECTED DATA";

const char D_00618CF0[16] = "src/enemy.c";

const char D_00618D00[16] = "enemy_sprite";

const char D_00618D10[48] = "\305\250\312\274\244\316\245\321\241\274\245\306\245\243\245\257\245\353\244\316\245\341\245\342\245\352\244\362\263\316\312\335\244\307\244\255\244\336\244\273\244\363\n";

const char D_00618D40[40] = "CAN'T ALLOCATE ENEMY'S PARTICLE MEMORY\n";

const char D_00618E00[88] = "SE \033[33m\"%s\"\033[m CALLED with GROUP:\033[33m%d\033[m\n\000\000\000\244\252\244\253\244\267\244\312ID(%d)\244\316SE\244\254\245\263\241\274\245\353\244\265\244\354\244\336\244\267\244\277\n";

const char D_0061DA78[104] = "+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000\000\000\000";

unsigned int D_00623468[48] = { 0x00000000, 0xC0A00000, 0xC1000000, 0x00000007, 0x00000005, 0x00000000, 0x40C00000, 0x3F800000, 0x00000000, 0xC0A00000, 0xC1000000, 0x00000007, 0x00000005, 0x00000001, 0x40C00000, 0x00000000, 0x00000000, 0xC0A00000, 0xC1000000, 0x00000007, 0x00000005, 0x00000001, 0x40C00000, 0x00000000, 0x00000000, 0xC0A00000, 0xC1000000, 0x00000007, 0x00000003, 0x00000000, 0x40C00000, 0x3F800000, 0x00000000, 0xC0A00000, 0xC1000000, 0x00000007, 0x00000009, 0x00000000, 0x40C00000, 0x3F800000, 0x00000000, 0xC0A00000, 0xC1000000, 0x00000007, 0x00000009, 0x00000001, 0x40C00000, 0x00000000 };

unsigned int D_0063339C = 0x00000000;

unsigned int D_006333A0 = 0xFFFFFFFF;

unsigned int D_006333A4 = 0x00000000;

unsigned int D_006333A8 = 0x00000000;

unsigned char D_006333B0[8] = { 0 };

unsigned char D_006333C0[8] = { 0 };

const char D_006333C8[8] = "e";

unsigned int D_006333D0 = 0x000A7025;

unsigned int D_006333D4 = 0x00000000;

unsigned int D_006333D8 = 0x00000000;

unsigned int D_006333DC = 0x00000000;

unsigned int D_006333E0 = 0x00000000;

unsigned int D_006333E4 = 0x00000000;

unsigned int D_006333E8 = 0x00000000;

unsigned int D_006333EC = 0x00000000;

unsigned int D_006333F0 = 0x3F800000;

unsigned int D_006333F4 = 0x00000000;

const char D_006333F8[8] = "fuku03";

const char D_00633400[8] = "g_hair9";

const char D_00633408[8] = "STONE";

const char D_00633410[8] = "DEVIL";

unsigned char D_00633418[8] = { 0 };

unsigned int D_00633420 = 0x00000030;

unsigned int D_00633424 = 0x00000142;

unsigned int D_00633428 = 0x00000189;

unsigned int D_0063342C = 0x0000018A;

unsigned char D_00633430[8] = { 0 };

unsigned int D_00633438 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from enemy_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_00631230 = 0x3A83126F;
unsigned int D_00631234 = 0x3EAAAA3B;
unsigned int D_00631238 = 0x461C4000;
unsigned int D_0063123C = 0x451C4000;
unsigned int D_00631240 = 0x461C4000;
unsigned int D_00631244 = 0x3727C5AC;
unsigned int D_00631248 = 0x3F666666;
unsigned int D_0063124C = 0x3D4CCCCD;
unsigned int D_00631250 = 0x47C35000;
unsigned int D_00631254 = 0x47C35000;
unsigned int D_00631258 = 0x3F733333;
unsigned int D_0063125C = 0x37800080;
unsigned int D_00631260 = 0x3F7FFF58;
unsigned int D_00631264 = 0x3C23D70A;
unsigned int D_00631268 = 0x37800080;
unsigned int D_0063126C = 0x3727C5AC;
unsigned int D_00631270 = 0x3F7AE148;
unsigned int D_00631274 = 0x3F7AE148;
unsigned int D_00631278 = 0x3F7AE148;
unsigned int D_0063127C = 0x3F7AE148;
unsigned int D_00631280 = 0x3E99999A;
unsigned int D_00631284 = 0x3DCCCCCD;
unsigned int D_00631288 = 0x3DA3D70A;
unsigned int D_0063128C = 0x3F99999A;
unsigned int D_00631290 = 0x3F99999A;
unsigned int D_00631294 = 0x3F6B851F;
unsigned int D_00631298 = 0x3F4CCCCD;
unsigned int D_0063129C = 0x3E99999A;
unsigned int D_006312A0 = 0x3F4CCCCD;
unsigned int D_006312A4 = 0x3F333333;
unsigned int D_006312A8 = 0x44026136;
unsigned int D_006312AC = 0x3D4CCCCD;
unsigned int D_006312B0 = 0x461C4000;

#include "include_asm.h"

extern unsigned short D_00633398;
extern unsigned short D_0063339A;
extern int D_00633394;
extern int D_006333AC;
extern int D_006325B4;
extern char D_006333B8[];
extern void func_0010D530(int *self);
extern void func_0010E158(int *self, short y);
extern void func_0010E0B8(int *self, short y);
extern void func_001E8AB8(int x);
extern void func_0018CAA8(int x, int y, int z);
extern void func_001A6E28(char *p);

INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CBE88);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CC048);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CC470);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CC838);

void func_001CCA70(int *self)
{
    func_0010D530(self);
    func_0010E158(self, -D_00633398);
    func_0010E0B8(self, -D_0063339A);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CCAC0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CCD98);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CCFD0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD0B8);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD2B0);

void func_001CD490(void)
{
    func_001E8AB8(D_00633394);
    D_00633394 = -1;
    func_0018CAA8(D_006333AC, 0, 3);
    D_006325B4 = 0;
    func_001A6E28(D_006333B8);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD4D8);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD5C0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD9B0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CDB28);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CDE30);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CE028);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CE220);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CE3C0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CE5F8);
extern int func_00165F88(int *self);
extern void func_001BB7E0(void);
extern void func_001CE5F8(int *self);

void func_001CE690(int *self)
{
    char *sub = *(char **)((char *)self + 0x164);
    unsigned long long flag = *(unsigned long long *)(sub + 0x18);
    if (((flag >> 33) & 1) == 0) return;
    func_001BB7E0();
    if (func_00165F88(self) != 0) return;
    func_001CE5F8(self);
}

/* ASCII debug strings — re-derived from EE rodata bytes. */
/* ASCII preview: "Save effect file [<ESC>[36m%s<ESC>[m](%s:%dbytes) <LF>" */
const char D_00618C38[48] = "Save effect file [\033[36m%s\033[m](%s:%dbytes) \n";
/* ASCII preview: "<ESC>[36mRANDOMIZE COUNT: %d > RID: %d<ESC>[m<LF>" */
const char D_00618D68[40] = "\033[36mRANDOMIZE COUNT: %d > RID: %d\033[m\n";
/* ASCII preview: "<ESC>[36mENEMY DESIGN ID: %d<ESC>[m<LF>" */
const char D_00618D90[32] = "\033[36mENEMY DESIGN ID: %d\033[m\n";
/* ASCII preview: "<ESC>[36mRequested by program... <ESC>[m" */
const char D_00618EA0[40] = "\033[36mRequested by program... \033[m";
