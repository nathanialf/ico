/* clothAnimation.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00631204"))) float D_00631204 = 0.2f;
__attribute__((section(".lit4.0x00631208"))) float D_00631208 = 0.2f;
__attribute__((section(".lit4.0x0063120C"))) float D_0063120C = 4095.0f;
__attribute__((section(".lit4.0x00631210"))) float D_00631210 = 0.001f;
__attribute__((section(".lit4.0x00631214"))) float D_00631214 = 0.6666667f;
__attribute__((section(".lit4.0x00631218"))) float D_00631218 = 50000.0f;
__attribute__((section(".lit4.0x0063121C"))) float D_0063121C = 0.001f;
__attribute__((section(".lit4.0x00631220"))) float D_00631220 = 0.96f;
__attribute__((section(".lit4.0x00631224"))) float D_00631224 = 0.3f;
__attribute__((section(".lit4.0x00631228"))) float D_00631228 = 0.01f;
__attribute__((section(".lit4.0x0063122C"))) float D_0063122C = 0.01f;
__attribute__((section(".lit4.0x00631230"))) float D_00631230 = 0.001f;
__attribute__((section(".sdata.0x00631940"))) char D_00631940[16] = { 0 };
__attribute__((section(".sdata.0x00631950"))) char D_00631950[16] = { 0 };
__attribute__((section(".sdata.0x00632010"))) int D_00632010 = 0;
__attribute__((section(".sdata.0x00632D58"))) int D_00632D58 = 0;
__attribute__((section(".sdata.0x006332A8"))) float D_006332A8 = 1.0f;
__attribute__((section(".sdata.0x006332AC"))) unsigned int D_006332AC = 0x004C0560;
__attribute__((section(".sdata.0x006332B0"))) unsigned int D_006332B0 = 0x004C0588;
__attribute__((section(".sdata.0x006332B4"))) unsigned int D_006332B4 = 0x004C0568;
__attribute__((section(".sdata.0x006332B8"))) int D_006332B8 = 0x004C0580;
__attribute__((section(".sdata.0x006332BC"))) int D_006332BC = 0x00000000;
__attribute__((section(".sdata.0x006332C0"))) int D_006332C0 = 0;
__attribute__((section(".sdata.0x006332C4"))) int D_006332C4 = 0;
__attribute__((section(".sdata.0x006332C8"))) char D_006332C8[8] = { 0 };
__attribute__((section(".sdata.0x006332D0"))) int D_006332D0 = 0x00000144;
__attribute__((section(".sdata.0x006332D4"))) int D_006332D4 = 0x00000000;
__attribute__((section(".sdata.0x006332D8"))) char D_006332D8 = 0;
__attribute__((section(".sdata.0x006332D9"))) char D_006332D9 = 0;
__attribute__((section(".sdata.0x006332DA"))) char D_006332DA = 0;
__attribute__((section(".sdata.0x006332E0"))) int D_006332E0 = 0x80FFFFFF;
__attribute__((section(".sdata.0x006332E4"))) int D_006332E4 = 0x00000000;
__attribute__((section(".sdata.0x006332E8"))) char D_006332E8 = 0;
__attribute__((section(".sdata.0x006332E9"))) char D_006332E9 = 0;
__attribute__((section(".sdata.0x006332EA"))) char D_006332EA = 0;
__attribute__((section(".sdata.0x006332F0"))) char D_006332F0 = 0;
__attribute__((section(".sdata.0x006332F1"))) char D_006332F1 = 0;
__attribute__((section(".sdata.0x006332F2"))) char D_006332F2 = 0;
__attribute__((section(".sdata.0x006332F8"))) unsigned char D_006332F8 = 0x80;
__attribute__((section(".sdata.0x006332F9"))) unsigned char D_006332F9 = 0x80;
__attribute__((section(".sdata.0x006332FA"))) unsigned char D_006332FA = 0x80;
__attribute__((section(".sdata.0x00633300"))) unsigned char D_00633300 = 0xFF;
__attribute__((section(".sdata.0x00633301"))) unsigned char D_00633301 = 0xFF;
__attribute__((section(".sdata.0x00633308"))) unsigned char D_00633308 = 0x7F;
__attribute__((section(".sdata.0x00633309"))) char D_00633309 = 0;
__attribute__((section(".sdata.0x0063330A"))) unsigned short D_0063330A = 0x8062;
__attribute__((section(".sdata.0x0063330C"))) int D_0063330C = 0;
__attribute__((section(".sdata.0x00633310"))) int D_00633310 = 0;
__attribute__((section(".sdata.0x00633314"))) int D_00633314 = 0;
__attribute__((section(".sdata.0x00633318"))) int D_00633318 = 0;
__attribute__((section(".sdata.0x0063331C"))) float D_0063331C = 25.0f;
__attribute__((section(".sdata.0x00633320"))) int D_00633320 = 0;
__attribute__((section(".sdata.0x00633324"))) int D_00633324 = 0;
__attribute__((section(".sdata.0x00633328"))) const char D_00633328[8] = "LOOP";
__attribute__((section(".sdata.0x00633330"))) const char D_00633330[] = "RELEASE";
__attribute__((section(".sdata.0x00633338"))) const char D_00633338[8] = "SUB";
__attribute__((section(".sdata.0x00633340"))) const char D_00633340[8] = "ADD";
__attribute__((section(".sdata.0x00633348"))) const char D_00633348[8] = "BLEND";
__attribute__((section(".sdata.0x00633350"))) const char D_00633350[] = "COLOR B";
__attribute__((section(".sdata.0x00633358"))) const char D_00633358[] = "COLOR G";
__attribute__((section(".sdata.0x00633360"))) const char D_00633360[] = "COLOR R";
__attribute__((section(".sdata.0x00633368"))) const char D_00633368[8] = "%4.3f";
__attribute__((section(".sdata.0x00633370"))) const char D_00633370[] = "(%d,%d)";
__attribute__((section(".sdata.0x00633378"))) const char D_00633378[8] = "%d";
__attribute__((section(".sdata.0x00633380"))) const char D_00633380[8] = "%s";
__attribute__((section(".sdata.0x00633388"))) const char D_00633388[8] = "%s%s";
__attribute__((section(".sdata.0x00633390"))) int D_00633390 = 0;
__attribute__((section(".sdata.0x00633394"))) unsigned int D_00633394 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00633398"))) short D_00633398 = 0;
__attribute__((section(".sdata.0x0063339A"))) short D_0063339A = 0;
__attribute__((section(".sdata.0x0063339C"))) int D_0063339C = 0;
__attribute__((section(".sdata.0x006333A0"))) unsigned int D_006333A0 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x006333A4"))) int D_006333A4 = 0;
__attribute__((section(".sdata.0x006333A8"))) int D_006333A8 = 0;
__attribute__((section(".sdata.0x006333AC"))) int D_006333AC = 0;
__attribute__((section(".sdata.0x006333B0"))) char D_006333B0[8] = { 0 };
__attribute__((section(".sdata.0x006333B8"))) const char D_006333B8[8] = "exit\n";
__attribute__((section(".sdata.0x006333C0"))) char D_006333C0[8] = { 0 };

__attribute__((section(".rodata.0x00618930"))) const char D_00618930[24] = "src/clothAnimation.c";

__attribute__((section(".rodata.0x00618970"))) const char D_00618970[16] = "FADE OUT RND";
__attribute__((section(".rodata.0x00618980"))) const char D_00618980[16] = "FADE OUT";
__attribute__((section(".rodata.0x00618990"))) const char D_00618990[16] = "FADE BASE RND";
__attribute__((section(".rodata.0x006189A0"))) const char D_006189A0[16] = "FADE BASE";
__attribute__((section(".rodata.0x006189B0"))) const char D_006189B0[16] = "BIRTH RATE";
__attribute__((section(".rodata.0x006189C0"))) const char D_006189C0[16] = "LIFE SPAN RND";
__attribute__((section(".rodata.0x006189D0"))) const char D_006189D0[16] = "LIFE SPAN";
__attribute__((section(".rodata.0x006189E0"))) const char D_006189E0[16] = "NB POLYGONS";
__attribute__((section(".rodata.0x006189F0"))) const char D_006189F0[16] = "SIZE GROW ACC";
__attribute__((section(".rodata.0x00618A00"))) const char D_00618A00[16] = "SIZE GROW RND";
__attribute__((section(".rodata.0x00618A10"))) const char D_00618A10[16] = "SIZE GROW";
__attribute__((section(".rodata.0x00618A20"))) const char D_00618A20[16] = "SIZE BASE RND";
__attribute__((section(".rodata.0x00618A30"))) const char D_00618A30[16] = "SIZE BASE";
__attribute__((section(".rodata.0x00618A40"))) const char D_00618A40[16] = "ROT GROW ACC";
__attribute__((section(".rodata.0x00618A50"))) const char D_00618A50[16] = "ROT GROW RND";
__attribute__((section(".rodata.0x00618A60"))) const char D_00618A60[16] = "ROT GROW";
__attribute__((section(".rodata.0x00618A70"))) const char D_00618A70[16] = "ROT BASE RND";
__attribute__((section(".rodata.0x00618A80"))) const char D_00618A80[16] = "ROT BASE";
__attribute__((section(".rodata.0x00618A90"))) const char D_00618A90[16] = "GRAVITY ACC";
__attribute__((section(".rodata.0x00618AA0"))) const char D_00618AA0[16] = "VEL ACCEL    ";
__attribute__((section(".rodata.0x00618AB0"))) const char D_00618AB0[16] = "VEL RND RATIO";
__attribute__((section(".rodata.0x00618AC0"))) const char D_00618AC0[16] = "VELOCITY";
__attribute__((section(".rodata.0x00618AD0"))) const char D_00618AD0[16] = "WIND EFFECT";
__attribute__((section(".rodata.0x00618AE0"))) const char D_00618AE0[16] = "CONE ANGLE";
__attribute__((section(".rodata.0x00618AF0"))) const char D_00618AF0[16] = "ALPHA TYPE";
__attribute__((section(".rodata.0x00618B00"))) const char D_00618B00[16] = "DRAIN TYPE";
__attribute__((section(".rodata.0x00618B10"))) const char D_00618B10[16] = "V OFFSET";
__attribute__((section(".rodata.0x00618B20"))) const char D_00618B20[16] = "U OFFSET";
__attribute__((section(".rodata.0x00618B48"))) const char D_00618B48[24] = "%-20s:%s";
__attribute__((section(".rodata.0x00618B70"))) const char D_00618B70[16] = "POS-X:%4.3f";
__attribute__((section(".rodata.0x00618B80"))) const char D_00618B80[16] = "POS-Y:%4.3f";
__attribute__((section(".rodata.0x00618B90"))) const char D_00618B90[16] = "POS-Z:%4.3f";
__attribute__((section(".rodata.0x00618BA0"))) const char D_00618BA0[16] = "ROT-Y:%4.3f";
__attribute__((section(".rodata.0x00618BB0"))) const char D_00618BB0[16] = "ROT-X:%4.3f";

/* String rodata migrated from clothAnimation_data.c */
__attribute__((section(".rodata.0x00618B30"))) const char D_00618B30[24] = "Unknown Data Type \"%s\"\n";
__attribute__((section(".rodata.0x00618BC0"))) const char D_00618BC0[16] = "initialize\n";
__attribute__((section(".rodata.0x00618BD0"))) const char D_00618BD0[64] = "==== Save effect ============================================\n";
__attribute__((section(".rodata.0x00618C10"))) const char D_00618C10[40] = "saveEffectData: host file open error.\n";
__attribute__((section(".rodata.0x00618C68"))) const char D_00618C68[16] = "%d bytes wrote\n";
__attribute__((section(".rodata.0x00618C78"))) const char D_00618C78[64] = "=============================================================\n";

/* Float rodata migrated from clothAnimation_data.c */
__attribute__((section(".rodata.0x00618B60"))) const float D_00618B60[4] = { 0.0f, 0.0f, 1e+02f, 1.0f };
