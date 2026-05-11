/* way_util.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00630E3C"))) float D_00630E3C = 100000.0f;
__attribute__((section(".lit4.0x00630E40"))) float D_00630E40 = 100000.0f;
__attribute__((section(".lit4.0x00630E44"))) float D_00630E44 = 100000.0f;
__attribute__((section(".lit4.0x00630E48"))) float D_00630E48 = 100000.0f;
__attribute__((section(".lit4.0x00630E4C"))) float D_00630E4C = 100000.0f;
__attribute__((section(".lit4.0x00630E50"))) float D_00630E50 = 100000.0f;
__attribute__((section(".lit4.0x00630E54"))) float D_00630E54 = 100000.0f;
__attribute__((section(".lit4.0x00630E58"))) float D_00630E58 = 100000.0f;
__attribute__((section(".lit4.0x00630E5C"))) float D_00630E5C = 100000.0f;
__attribute__((section(".lit4.0x00630E60"))) float D_00630E60 = 100000.0f;
__attribute__((section(".lit4.0x00630E64"))) float D_00630E64 = 100000.0f;
__attribute__((section(".lit4.0x00630E68"))) float D_00630E68 = 100000.0f;
__attribute__((section(".lit4.0x00630E6C"))) float D_00630E6C = 40000.0f;
__attribute__((section(".lit4.0x00630E70"))) float D_00630E70 = 40000.0f;
__attribute__((section(".lit4.0x00630E74"))) float D_00630E74 = 3.14159274f;
__attribute__((section(".lit4.0x00630E78"))) float D_00630E78 = 3.14159274f;
__attribute__((section(".lit4.0x00630E7C"))) float D_00630E7C = 3834.0f;
__attribute__((section(".lit4.0x00630E80"))) float D_00630E80 = 0.8f;
__attribute__((section(".lit4.0x00630E84"))) float D_00630E84 = 0.45f;
__attribute__((section(".lit4.0x00630E88"))) float D_00630E88 = 3834.0f;
__attribute__((section(".lit4.0x00630E8C"))) float D_00630E8C = 0.99f;
__attribute__((section(".lit4.0x00630E90"))) float D_00630E90 = 0.1f;
__attribute__((section(".lit4.0x00630E94"))) float D_00630E94 = 0.8f;
__attribute__((section(".lit4.0x00630E98"))) float D_00630E98 = 0.45f;
__attribute__((section(".lit4.0x00630E9C"))) float D_00630E9C = 625.0f;
__attribute__((section(".lit4.0x00630EA0"))) float D_00630EA0 = 1650.0f;
__attribute__((section(".lit4.0x00630EA4"))) float D_00630EA4 = 4200.0f;
__attribute__((section(".lit4.0x00630EA8"))) float D_00630EA8 = 3100.0f;
__attribute__((section(".lit4.0x00630EAC"))) float D_00630EAC = 0.01f;
__attribute__((section(".lit4.0x00630EB0"))) float D_00630EB0 = 1500.0f;
__attribute__((section(".lit4.0x00630EB4"))) float D_00630EB4 = 0.99f;
__attribute__((section(".lit4.0x00630EB8"))) float D_00630EB8 = 0.001f;
__attribute__((section(".lit4.0x00630EBC"))) float D_00630EBC = 0.01f;
__attribute__((section(".lit4.0x00630EC0"))) float D_00630EC0 = 0.0174532924f;
__attribute__((section(".lit4.0x00630EC4"))) float D_00630EC4 = 0.1f;
__attribute__((section(".lit4.0x00630EC8"))) float D_00630EC8 = 1.9f;
__attribute__((section(".lit4.0x00630ECC"))) float D_00630ECC = 3.14159274f;
__attribute__((section(".lit4.0x00630ED0"))) float D_00630ED0 = 0.0001f;
__attribute__((section(".lit4.0x00630ED4"))) float D_00630ED4 = 0.0001f;
__attribute__((section(".sdata.0x00632598"))) const char D_00632598[8] = "0";
__attribute__((section(".sdata.0x006325A0"))) const char D_006325A0[] = "gid:%d\n";
__attribute__((section(".sdata.0x006325A8"))) float D_006325A8[2] = { 100000.0f, 100000.0f };
__attribute__((section(".sdata.0x00633874"))) int D_00633874 = 0;
__attribute__((section(".sdata.0x00633878"))) unsigned int D_00633878 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x0063387C"))) int D_0063387C = 0;
__attribute__((section(".sdata.0x00633880"))) const char D_00633880[8] = "pt.%d";
__attribute__((section(".sdata.0x00633888"))) unsigned int D_00633888 = 0x00000062;
__attribute__((section(".sdata.0x0063388C"))) int D_0063388C = 0;
__attribute__((section(".sdata.0x00633890"))) int D_00633890 = 0;
__attribute__((section(".sdata.0x00633894"))) int D_00633894 = 0;
__attribute__((section(".sdata.0x00633898"))) const char D_00633898[] = "to boy\n";
__attribute__((section(".sdata.0x006338A0"))) const char D_006338A0[] = "test.wp";
__attribute__((section(".sdata.0x006338A8"))) const char D_006338A8[8] = "saved\n";
__attribute__((section(".sdata.0x006338B0"))) const char D_006338B0[8] = "%d ";
__attribute__((section(".sdata.0x006338B8"))) const char D_006338B8[8] = "\n";
__attribute__((section(".sdata.0x006338C0"))) const char D_006338C0[] = "loaded\n";
__attribute__((section(".sdata.0x006338C8"))) const char D_006338C8[] = "way0000";
__attribute__((section(".sdata.0x006338D0"))) const char D_006338D0[8] = "%s.txt";
__attribute__((section(".sdata.0x006338D8"))) const char D_006338D8[8] = "play";
