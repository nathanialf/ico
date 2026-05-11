/* debug.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00631A20"))) char D_00631A20[48] = { 0 };
__attribute__((section(".sdata.0x00631A50"))) char D_00631A50[16] = { 0 };
__attribute__((section(".sdata.0x00631A60"))) char D_00631A60[16] = { 0 };
__attribute__((section(".sdata.0x00631A70"))) char D_00631A70[48] = { 0 };
__attribute__((section(".sdata.0x00631AA0"))) char D_00631AA0[16] = { 0 };
__attribute__((section(".sdata.0x006328C0"))) char D_006328C0[8] = { 0 };
__attribute__((section(".sdata.0x006328C8"))) const char D_006328C8[8] = "PAL";
__attribute__((section(".sdata.0x006328D0"))) const char D_006328D0[8] = "NTSC";
__attribute__((section(".sdata.0x006328D8"))) const char D_006328D8[8] = "Double";
__attribute__((section(".sdata.0x006328E0"))) const char D_006328E0[8] = "Single";
__attribute__((section(".sdata.0x006328E8"))) const char D_006328E8[8] = "On";
__attribute__((section(".sdata.0x006328F0"))) const char D_006328F0[8] = "Off";
__attribute__((section(".sdata.0x006328F8"))) const char D_006328F8[] = "Process";
__attribute__((section(".sdata.0x00632900"))) const char D_00632900[8] = "Half";
__attribute__((section(".sdata.0x00632908"))) const char D_00632908[8] = "Normal";
__attribute__((section(".sdata.0x00632910"))) const char D_00632910[8] = "BMP";
__attribute__((section(".sdata.0x00632918"))) const char D_00632918[8] = "TIM2";
__attribute__((section(".sdata.0x00632920"))) const char D_00632920[8] = "/16";
__attribute__((section(".sdata.0x00632928"))) const char D_00632928[8] = "/8";
__attribute__((section(".sdata.0x00632930"))) const char D_00632930[8] = "/4";
__attribute__((section(".sdata.0x00632938"))) const char D_00632938[8] = "/2";
__attribute__((section(".sdata.0x00632940"))) const char D_00632940[8] = "x1";
__attribute__((section(".sdata.0x00632948"))) const char D_00632948[8] = "x2";
__attribute__((section(".sdata.0x00632950"))) const char D_00632950[8] = "x4";
__attribute__((section(".sdata.0x00632958"))) const char D_00632958[8] = "x8";
__attribute__((section(".sdata.0x00632960"))) const char D_00632960[8] = "x16";
__attribute__((section(".sdata.0x00632968"))) const char D_00632968[8] = "x32";
__attribute__((section(".sdata.0x00632970"))) const char D_00632970[8] = "x64";
__attribute__((section(".sdata.0x00632978"))) const char D_00632978[8] = "x128";
__attribute__((section(".sdata.0x00632980"))) const char D_00632980[8] = "x256";
__attribute__((section(".sdata.0x00632988"))) const char D_00632988[8] = "x512";
__attribute__((section(".sdata.0x00632990"))) const char D_00632990[8] = "2Layer";
__attribute__((section(".sdata.0x00632998"))) const char D_00632998[8] = "1Layer";
__attribute__((section(".sdata.0x006329A0"))) const char D_006329A0[8] = "AllOff";
__attribute__((section(".sdata.0x006329A8"))) const char D_006329A8[8] = "AllOn";
__attribute__((section(".sdata.0x006329B0"))) const char D_006329B0[8] = "Object";
__attribute__((section(".sdata.0x006329B8"))) const char D_006329B8[8] = "Line";
__attribute__((section(".sdata.0x006329C0"))) const char D_006329C0[8] = "QUEEN";
__attribute__((section(".sdata.0x006329C8"))) const char D_006329C8[8] = "ENEMY";
__attribute__((section(".sdata.0x006329D0"))) const char D_006329D0[8] = "BIRD";
__attribute__((section(".sdata.0x006329D8"))) const char D_006329D8[8] = "GIRL";
__attribute__((section(".sdata.0x006329E0"))) unsigned int D_006329E0 = 0x00594F42;
__attribute__((section(".sdata.0x006329F8"))) const char D_006329F8[8] = "e";
__attribute__((section(".sdata.0x00632A00"))) unsigned int D_00632A00 = 0x00000030;
__attribute__((section(".sdata.0x00632A04"))) unsigned int D_00632A04 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00632A08"))) int _pad_00632A08 = 0;
__attribute__((section(".sdata.0x00632A0C"))) unsigned int D_00632A0C = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00632A10"))) const char D_00632A10[8] = "%d";
__attribute__((section(".sdata.0x00632A18"))) const char D_00632A18[8] = "#%s\n";
__attribute__((section(".sdata.0x00632A20"))) unsigned int D_00632A20 = 0x000A6425;
__attribute__((section(".sdata.0x00632A24"))) unsigned int D_00632A24 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00632A28"))) unsigned char D_00632A28[8] = { 0xFF, 0xFF, 0xFF, 0x7E, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00632A30"))) unsigned int D_00632A30 = 0x80000000;
__attribute__((section(".sdata.0x00632C90"))) int D_00632C90 = 0;
__attribute__((section(".sdata.0x00632C94"))) int D_00632C94 = 0;
__attribute__((section(".sdata.0x00632C98"))) int D_00632C98 = 0;
__attribute__((section(".sdata.0x00632CB4"))) int D_00632CB4 = 0;
__attribute__((section(".sdata.0x00632CB8"))) int D_00632CB8 = 0;
__attribute__((section(".sdata.0x00632CC0"))) int D_00632CC0 = 0;
__attribute__((section(".sdata.0x00632CC4"))) int D_00632CC4 = 0;
__attribute__((section(".sdata.0x00632CCC"))) int D_00632CCC = 0;
__attribute__((section(".sdata.0x00632CD0"))) int D_00632CD0 = 0;
__attribute__((section(".sdata.0x00632CD8"))) int D_00632CD8 = 0;
__attribute__((section(".sdata.0x00632CDC"))) int D_00632CDC = 0;
__attribute__((section(".sdata.0x00632CE4"))) int D_00632CE4 = 0;
__attribute__((section(".sdata.0x00632CE8"))) int D_00632CE8 = 0;
__attribute__((section(".sdata.0x00632CF0"))) int D_00632CF0 = 0;
__attribute__((section(".sdata.0x00632CF4"))) int D_00632CF4 = 0;
__attribute__((section(".sdata.0x00632CFC"))) int D_00632CFC = 0;
__attribute__((section(".sdata.0x00632D00"))) int D_00632D00 = 0;
__attribute__((section(".sdata.0x00632D0C"))) int D_00632D0C = 0;
__attribute__((section(".sdata.0x00632D10"))) int D_00632D10 = 0;
__attribute__((section(".sdata.0x00632D18"))) int D_00632D18 = 0;
__attribute__((section(".sdata.0x00632D1C"))) int D_00632D1C = 0;
__attribute__((section(".sdata.0x00632D20"))) int D_00632D20 = 0;
__attribute__((section(".sdata.0x00632D24"))) int D_00632D24 = 0;
__attribute__((section(".sdata.0x00632D30"))) int D_00632D30 = 0;
__attribute__((section(".sdata.0x00632D34"))) int D_00632D34 = 0;
__attribute__((section(".sdata.0x00632D38"))) int D_00632D38 = 0;
__attribute__((section(".sdata.0x00632D3C"))) int D_00632D3C = 0;
__attribute__((section(".sdata.0x00632D40"))) int D_00632D40 = 0;
__attribute__((section(".sdata.0x00632D44"))) int D_00632D44 = 0;
__attribute__((section(".sdata.0x00632D5C"))) int D_00632D5C = 0;
__attribute__((section(".sdata.0x00632D60"))) int D_00632D60 = 0;
__attribute__((section(".sdata.0x00632D64"))) int D_00632D64 = 0;
__attribute__((section(".sdata.0x00632D6C"))) int D_00632D6C = 0;
__attribute__((section(".sdata.0x00632D70"))) int D_00632D70 = 0;
__attribute__((section(".sdata.0x00632D74"))) int D_00632D74 = 0;
__attribute__((section(".sdata.0x00632D78"))) int D_00632D78 = 0;
__attribute__((section(".sdata.0x00632D7C"))) int D_00632D7C = 0;
__attribute__((section(".sdata.0x00632D88"))) int D_00632D88 = 0;
__attribute__((section(".sdata.0x00632D90"))) int D_00632D90 = 0;
__attribute__((section(".sdata.0x00632D98"))) int D_00632D98 = 0;
__attribute__((section(".sdata.0x00632D9C"))) int D_00632D9C = 0;
__attribute__((section(".sdata.0x00632DA0"))) int D_00632DA0 = 0;
__attribute__((section(".sdata.0x00632DA4"))) int D_00632DA4 = 0;
__attribute__((section(".sdata.0x00632DA8"))) int D_00632DA8 = 0;
__attribute__((section(".sdata.0x00632DAC"))) int D_00632DAC = 0;
__attribute__((section(".sdata.0x00632DB8"))) int D_00632DB8 = 0;
