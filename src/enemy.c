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
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".lit4.0x00630930"))) float D_00630930 = 0.01f;
__attribute__((section(".lit4.0x00630934"))) float D_00630934 = 0.01f;
__attribute__((section(".lit4.0x00630938"))) float D_00630938 = 0.01f;
__attribute__((section(".lit4.0x0063093C"))) float D_0063093C = 1.00000011e-06f;
__attribute__((section(".lit4.0x00631234"))) float D_00631234 = 0.33333f;
__attribute__((section(".lit4.0x00631238"))) float D_00631238 = 10000.0f;
__attribute__((section(".lit4.0x0063123C"))) float D_0063123C = 2500.0f;
__attribute__((section(".lit4.0x00631240"))) float D_00631240 = 10000.0f;
__attribute__((section(".sdata.0x006333C8"))) const char D_006333C8[8] = "e";
__attribute__((section(".sdata.0x006333D0"))) unsigned int D_006333D0 = 0x000A7025;
__attribute__((section(".sdata.0x006333D4"))) int D_006333D4 = 0;
__attribute__((section(".sdata.0x006333D8"))) int D_006333D8 = 0;
__attribute__((section(".sdata.0x006333DC"))) int D_006333DC = 0;
__attribute__((section(".sdata.0x006333E0"))) int D_006333E0 = 0;
__attribute__((section(".sdata.0x006333E4"))) int D_006333E4 = 0;
__attribute__((section(".sdata.0x006333E8"))) int D_006333E8 = 0;
__attribute__((section(".sdata.0x006333EC"))) int D_006333EC = 0;
__attribute__((section(".sdata.0x006333F0"))) float D_006333F0 = 1.0f;
__attribute__((section(".sdata.0x006333F4"))) int D_006333F4 = 0;
__attribute__((section(".sdata.0x006333F8"))) const char D_006333F8[8] = "fuku03";
__attribute__((section(".sdata.0x00633400"))) const char D_00633400[] = "g_hair9";
__attribute__((section(".sdata.0x00633408"))) const char D_00633408[8] = "STONE";
__attribute__((section(".sdata.0x00633410"))) const char D_00633410[8] = "DEVIL";
__attribute__((section(".sdata.0x00633418"))) char D_00633418[8] = { 0 };

__attribute__((section(".rodata.0x00618CF0"))) const char D_00618CF0[16] = "src/enemy.c";

__attribute__((section(".rodata.0x00618D00"))) const char D_00618D00[16] = "enemy_sprite";

/* String rodata migrated from enemy_data.c */
__attribute__((section(".rodata.0x00618D40"))) const char D_00618D40[40] = "CAN'T ALLOCATE ENEMY'S PARTICLE MEMORY\n";

/* String-pool rodata migrated from enemy_data.c */
__attribute__((section(".rodata.0x0061DA78"))) const char D_0061DA78[104] = "+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "敵兵のパーティクルのメモリを確保できません
" */
__attribute__((section(".rodata.0x00618D10"))) const char D_00618D10[48] = "\305\250\312\274\244\316\245\321\241\274\245\306\245\243\245\257\245\353\244\316\245\341\245\342\245\352\244\362\263\316\312\335\244\307\244\255\244\336\244\273\244\363\n";
