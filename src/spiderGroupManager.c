/* spiderGroupManager.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x006335FC"))) int D_006335FC = 0;
__attribute__((section(".sdata.0x00633600"))) int D_00633600 = 0;
__attribute__((section(".sdata.0x00633604"))) int D_00633604 = 0;
__attribute__((section(".sdata.0x00633608"))) int D_00633608 = 0;
__attribute__((section(".sdata.0x0063360C"))) int D_0063360C = 0;
__attribute__((section(".sdata.0x00633610"))) int D_00633610 = 0;
__attribute__((section(".sdata.0x00633614"))) int D_00633614 = 0;
__attribute__((section(".sdata.0x00633618"))) unsigned int D_00633618 = 0x00000065;
__attribute__((section(".sdata.0x0063361C"))) int D_0063361C = 0;
__attribute__((section(".sdata.0x00633620"))) unsigned int D_00633620 = 0x00000001;
__attribute__((section(".sdata.0x00633624"))) unsigned int D_00633624 = 0x00000001;
__attribute__((section(".sdata.0x00633628"))) unsigned int D_00633628 = 0x00000001;
__attribute__((section(".sdata.0x0063362C"))) unsigned int D_0063362C = 0x00000002;
__attribute__((section(".sdata.0x00633630"))) int D_00633630 = 0;
__attribute__((section(".sdata.0x00633634"))) int D_00633634 = 0;
__attribute__((section(".sdata.0x00633638"))) int D_00633638 = 0;
__attribute__((section(".sdata.0x0063363C"))) int D_0063363C = 0;
__attribute__((section(".sdata.0x00633640"))) float D_00633640 = 100.0f;
__attribute__((section(".sdata.0x00633644"))) float D_00633644 = 400.0f;
__attribute__((section(".sdata.0x00633648"))) float D_00633648[2] = { 200.0f, 0.0f };
__attribute__((section(".sdata.0x00633650"))) unsigned char D_00633650[8] = { 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00633658"))) char D_00633658[8] = { 0 };
__attribute__((section(".sdata.0x00633660"))) float D_00633660[2] = { -2.0f, 0.0f };
__attribute__((section(".sdata.0x00633668"))) unsigned char D_00633668[8] = { 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00633670"))) unsigned char D_00633670[8] = { 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00633678"))) unsigned char D_00633678[8] = { 0x8B, 0x88, 0x84, 0x28, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00633680"))) char D_00633680[8] = { 0 };
__attribute__((section(".sdata.0x00633688"))) unsigned int D_00633688 = 0x80808080;
__attribute__((section(".sdata.0x0063368C"))) unsigned int D_0063368C = 0x00000096;
__attribute__((section(".sdata.0x00633690"))) unsigned char D_00633690[8] = { 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00633698"))) unsigned char D_00633698[8] = { 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x006336A0"))) unsigned char D_006336A0[8] = { 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x006336A8"))) unsigned int D_006336A8 = 0x00808080;
__attribute__((section(".sdata.0x006336AC"))) int D_006336AC = 0;
__attribute__((section(".sdata.0x006336B0"))) int D_006336B0 = 0;
__attribute__((section(".sdata.0x006336B4"))) int D_006336B4 = 0;
__attribute__((section(".sdata.0x006336B8"))) unsigned char D_006336B8[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x006336C0"))) const char D_006336C0[8] = "SBLUR";
__attribute__((section(".sdata.0x006336C8"))) const char D_006336C8[8] = "DEPTH";
__attribute__((section(".sdata.0x006336D0"))) const char D_006336D0[8] = "GLOW";
__attribute__((section(".sdata.0x006336D8"))) const char D_006336D8[] = "BLSBLUR";
__attribute__((section(".sdata.0x006336E0"))) int D_006336E0 = 0;
__attribute__((section(".sdata.0x006336E4"))) unsigned int D_006336E4 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x006336E8"))) const char D_006336E8[8] = "AURA";
__attribute__((section(".sdata.0x006336F0"))) const char D_006336F0[8] = "MIRAGE";
__attribute__((section(".sdata.0x006336F8"))) const char D_006336F8[] = "AURA V2";
__attribute__((section(".sdata.0x00633700"))) const char D_00633700[8] = "SUN";
__attribute__((section(".sdata.0x00633708"))) int D_00633708 = 0;
__attribute__((section(".sdata.0x0063370C"))) int D_0063370C = 0;
__attribute__((section(".sdata.0x00633710"))) int D_00633710 = 0;
__attribute__((section(".sdata.0x00633714"))) int D_00633714 = 0;
__attribute__((section(".sdata.0x00633718"))) int D_00633718 = 0;
__attribute__((section(".sdata.0x0063371C"))) int D_0063371C = 0;
