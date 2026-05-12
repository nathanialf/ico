/* pool.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".lit4.0x00630984"))) float D_00630984 = 3.14159274f;
__attribute__((section(".lit4.0x00630988"))) float D_00630988 = 0.0005f;
__attribute__((section(".lit4.0x0063098C"))) float D_0063098C = 0.05f;
__attribute__((section(".lit4.0x00630990"))) float D_00630990 = 0.8f;
__attribute__((section(".lit4.0x00630994"))) float D_00630994 = 0.1f;
__attribute__((section(".lit4.0x00630998"))) float D_00630998 = 0.1f;
__attribute__((section(".lit4.0x0063099C"))) float D_0063099C = 0.8f;
__attribute__((section(".lit4.0x006309A0"))) float D_006309A0 = 1.15f;
__attribute__((section(".lit4.0x006309A4"))) float D_006309A4 = 0.8f;
__attribute__((section(".lit4.0x006309A8"))) float D_006309A8 = 0.3f;
__attribute__((section(".lit4.0x006309AC"))) float D_006309AC = 0.005f;
__attribute__((section(".lit4.0x006309B0"))) float D_006309B0 = 0.01f;
__attribute__((section(".lit4.0x006309B4"))) float D_006309B4 = 0.01f;
__attribute__((section(".lit4.0x006309B8"))) float D_006309B8 = 0.05f;
__attribute__((section(".lit4.0x006309BC"))) float D_006309BC = 1.57079637f;
__attribute__((section(".lit4.0x006309C0"))) float D_006309C0 = 16385.0f;
__attribute__((section(".lit4.0x006309C4"))) float D_006309C4 = 10430.3779f;
__attribute__((section(".lit4.0x006309C8"))) float D_006309C8 = 0.001f;
__attribute__((section(".lit4.0x006309CC"))) float D_006309CC = 536870880.0f;
__attribute__((section(".sdata.0x00631B68"))) int D_00631B68 = 0;
__attribute__((section(".sdata.0x00631B6C"))) int D_00631B6C = 0;
__attribute__((section(".sdata.0x00631B70"))) int D_00631B70 = 0x80808080;
__attribute__((section(".sdata.0x00631B74"))) int D_00631B74 = 0x00000000;
__attribute__((section(".sdata.0x00631B78"))) unsigned int D_00631B78 = 0x80FFFFFF;
__attribute__((section(".sdata.0x00631B7C"))) unsigned int D_00631B7C = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00631B80"))) int D_00631B80 = 0;
__attribute__((section(".sdata.0x00631B84"))) unsigned int D_00631B84 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00631B88"))) const char D_00631B88[8] = "done.\n";
__attribute__((section(".sdata.0x00631BCC"))) unsigned int D_00631BCC = 0x00000001;
__attribute__((section(".sdata.0x00631BD0"))) unsigned char D_00631BD0 = 0x70;
__attribute__((section(".sdata.0x00631BD1"))) unsigned char D_00631BD1 = 0x70;
__attribute__((section(".sdata.0x00631BD2"))) unsigned char D_00631BD2 = 0x70;
__attribute__((section(".sdata.0x00631BD3"))) unsigned char D_00631BD3 = 0x80;
__attribute__((section(".sdata.0x00631BD4"))) int _pad_00631BD4 = 0;
__attribute__((section(".sdata.0x00631BD8"))) unsigned int D_00631BD8 = 0x00000046;
__attribute__((section(".sdata.0x00631BDC"))) unsigned int D_00631BDC = 0x00000032;
__attribute__((section(".sdata.0x00631BE0"))) int D_00631BE0 = 0;
__attribute__((section(".sdata.0x00631BE4"))) int D_00631BE4 = 0;
__attribute__((section(".sdata.0x00631BE8"))) const char D_00631BE8[8] = "D";
__attribute__((section(".sdata.0x00631BF0"))) const char D_00631BF0[8] = "B";
__attribute__((section(".sdata.0x00631BF8"))) unsigned int D_00631BF8 = 0x80808080;
__attribute__((section(".sdata.0x00631BFC"))) int D_00631BFC = 0;
__attribute__((section(".sdata.0x00631C00"))) const char D_00631C00[8] = "L";
__attribute__((section(".sdata.0x00631C08"))) const char D_00631C08[8] = "P";
__attribute__((section(".sdata.0x00631C10"))) unsigned int D_00631C10 = 0x0000004B;
__attribute__((section(".sdata.0x00631C14"))) unsigned int D_00631C14 = 0x00000001;
__attribute__((section(".sdata.0x00631C18"))) char D_00631C18[8] = { 0 };
__attribute__((section(".sdata.0x00631C20"))) const char D_00631C20[8] = "On";
__attribute__((section(".sdata.0x00631C28"))) unsigned int D_00631C28 = 0x0066664F;
__attribute__((section(".sdata.0x00631C2C"))) int D_00631C2C = 0;
__attribute__((section(".sdata.0x00631C30"))) const char D_00631C30[] = "%s : %s";
__attribute__((section(".sdata.0x00631C38"))) const char D_00631C38[] = "%s : %d";
__attribute__((section(".sdata.0x00631C40"))) int D_00631C40 = 0;
__attribute__((section(".sdata.0x00631C44"))) unsigned int D_00631C44 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00631C48"))) unsigned int D_00631C48 = 0x00007325;
__attribute__((section(".sdata.0x00631C5C"))) int D_00631C5C = 0;
__attribute__((section(".sdata.0x00631C60"))) int D_00631C60 = 0;
__attribute__((section(".sdata.0x00631C68"))) int D_00631C68 = 0;
__attribute__((section(".sdata.0x00631C6C"))) int D_00631C6C = 0;
__attribute__((section(".sdata.0x00632D48"))) int D_00632D48 = 0;

__attribute__((section(".rodata.0x00553DE0"))) const char D_00553DE0[16] = "src/pool.c";

__attribute__((section(".rodata.0x00553E90"))) const char D_00553E90[32] = "display object = %d";
__attribute__((section(".rodata.0x00553F10"))) const char D_00553F10[24] = "cdrom0:\\IOPRP224.IMG;1";
__attribute__((section(".rodata.0x00553F40"))) const char D_00553F40[24] = "cdrom0:\\SIO2MAN.IRX;1";
__attribute__((section(".rodata.0x00553F58"))) const char D_00553F58[24] = "cdrom0:\\PADMAN.IRX;1";
__attribute__((section(".rodata.0x00553F70"))) const char D_00553F70[24] = "cdrom0:\\MCMAN.IRX;1";
__attribute__((section(".rodata.0x00553F88"))) const char D_00553F88[24] = "cdrom0:\\MCSERV.IRX;1";
__attribute__((section(".rodata.0x00553FA0"))) const char D_00553FA0[24] = "cdrom0:\\LIBSD.IRX;1";
__attribute__((section(".rodata.0x00553FB8"))) const char D_00553FB8[24] = "cdrom0:\\SNDN2DRV.IRX;1";

/* String rodata migrated from pool_data.c */
__attribute__((section(".rodata.0x00553E00"))) const char D_00553E00[40] = "Quaternion stack not initialized.\n";
__attribute__((section(".rodata.0x00553E28"))) const char D_00553E28[32] = "Quaternion stack overflow!!\n";
__attribute__((section(".rodata.0x00553E48"))) const char D_00553E48[40] = "Quaternion stack underflow!!\n";
__attribute__((section(".rodata.0x00553EB0"))) const char D_00553EB0[48] = "-------------------------------- read from CD\n";
__attribute__((section(".rodata.0x00553EE0"))) const char D_00553EE0[24] = "initialize CD device.\n";
__attribute__((section(".rodata.0x00553EF8"))) const char D_00553EF8[24] = "load default module.\n";
__attribute__((section(".rodata.0x00553F28"))) const char D_00553F28[24] = "loading iop modules.\n";

/* Float rodata migrated from pool_data.c */
__attribute__((section(".rodata.0x00553DF0"))) const float D_00553DF0[4] = { 2048.0f, 2048.0f, 0.0f, 0.0f };
