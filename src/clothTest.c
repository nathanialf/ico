/* src/clothTest.c — __FILE__ anchor at .rodata 0x00618960
 *
 * TU range: single function at 0x001C92D8 (size 0x4C).
 * The 4-byte gap before the next TU (cod/0C9324 at 0x001C9324) is
 * alignment padding supplied by the linker --gap-fill.
 */

const char D_00618960[16] = "src/clothTest.c";

extern int   D_00632010;
extern char  D_004C0960[];
extern int  *func_0013A0F8(int handle, int size, char *file, int line);
extern int   func_001C5BA0(char *p);

/* Inlined data (Phase 3e) — migrated from clothTest_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_004C09B0[4] = { 0x00000000, 0x00000000, 0x00000000, 0x3F800000 };
unsigned int D_006332C0 = 0x00000000;
unsigned int D_006332C4 = 0x00000000;
unsigned char D_006332C8[8] = { 0 };
const char D_006332D0[8] = "D\001";
unsigned char D_006332D8 = 0x00;
unsigned char D_006332D9 = 0x00;
unsigned char D_006332DA = 0x00;
unsigned int D_006332E0[2] = { 0x80FFFFFF, 0x00000000 };
unsigned char D_006332E8 = 0x00;
unsigned char D_006332E9 = 0x00;
unsigned char D_006332EA = 0x00;
unsigned char D_006332F0 = 0x00;
unsigned char D_006332F1 = 0x00;
unsigned char D_006332F2 = 0x00;
unsigned char D_006332F8 = 0x80;
unsigned char D_006332F9 = 0x80;
unsigned char D_006332FA = 0x80;
unsigned char D_00633300 = 0xFF;
unsigned char D_00633301 = 0xFF;
unsigned char D_00633308 = 0x7F;
unsigned char D_00633309 = 0x00;
unsigned short D_0063330A = 0x8062;
unsigned int D_0063330C = 0x00000000;
unsigned int D_00633310 = 0x00000000;
unsigned int D_00633314 = 0x00000000;
unsigned int D_00633318 = 0x00000000;
unsigned int D_0063331C = 0x41C80000;
unsigned int D_00633320 = 0x00000000;
unsigned int D_00633324 = 0x00000000;
const char D_00633328[8] = "LOOP";
const char D_00633330[8] = "RELEASE";
const char D_00633338[8] = "SUB";
const char D_00633340[8] = "ADD";
const char D_00633348[8] = "BLEND";
const char D_00633350[8] = "COLOR B";
const char D_00633358[8] = "COLOR G";
const char D_00633360[8] = "COLOR R";
const char D_00633368[8] = "%4.3f";
const char D_00633370[8] = "(%d,%d)";
const char D_00633378[8] = "%d";
const char D_00633380[8] = "%s";
const char D_00633388[8] = "%s%s";
unsigned int D_00633390 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from clothTest_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

int *func_001C92D8(void)
{
    int *p = func_0013A0F8(D_00632010, 0x290, (char *)D_00618960, 0x41);
    *p = func_001C5BA0(D_004C0960);
    return p;
}
