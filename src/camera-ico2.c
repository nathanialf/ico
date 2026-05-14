/* camera-ico2.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00630ED8"))) float D_00630ED8 = 3.14159274f;
__attribute__((section(".lit4.0x00630EDC"))) float D_00630EDC = 0.4f;
__attribute__((section(".lit4.0x00630EE0"))) float D_00630EE0 = 0.4f;
__attribute__((section(".lit4.0x00630EE4"))) float D_00630EE4 = 0.4f;
__attribute__((section(".lit4.0x00630EE8"))) float D_00630EE8 = 0.4f;
__attribute__((section(".lit4.0x00630EEC"))) float D_00630EEC = 0.4f;
__attribute__((section(".lit4.0x00630EF0"))) float D_00630EF0 = 3.14159274f;
__attribute__((section(".lit4.0x00630EF4"))) float D_00630EF4 = 3.14159274f;
__attribute__((section(".lit4.0x00630EF8"))) float D_00630EF8 = 3.14159274f;
__attribute__((section(".lit4.0x00630EFC"))) float D_00630EFC = 3.14159274f;
__attribute__((section(".sdata.0x006326E0"))) float D_006326E0 = 1.0f;
__attribute__((section(".sdata.0x006326E4"))) unsigned int D_006326E4 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x006326E8"))) char D_006326E8[8] = { 0 };
__attribute__((section(".sdata.0x006326F0"))) const char D_006326F0[16] = "0";
__attribute__((section(".sdata.0x00632700"))) unsigned int D_00632700 = 0x00000002;
__attribute__((section(".sdata.0x00632704"))) int D_00632704 = 0;
__attribute__((section(".sdata.0x00632708"))) const char D_00632708[] = "FREECAM";
__attribute__((section(".sdata.0x00632710"))) const char D_00632710[] = "GAMECAM";
__attribute__((section(".sdata.0x00632718"))) const char D_00632718[] = "HANDCAM";
__attribute__((section(".sdata.0x00632720"))) const char D_00632720[] = "PATHCAM";
__attribute__((section(".sdata.0x00632728"))) unsigned int D_00632728 = 0x00000001;
__attribute__((section(".sdata.0x0063272C"))) unsigned int D_0063272C = 0x00000003;
__attribute__((section(".sdata.0x00632730"))) int D_00632730 = 0;
__attribute__((section(".sdata.0x00632734"))) int D_00632734 = 0;
__attribute__((section(".sdata.0x00632CF8"))) int D_00632CF8 = 0;

__attribute__((section(".rodata.0x0055A940"))) const char D_0055A940[24] = "src/camera-ico2.c";

__attribute__((section(".rodata.0x0055AA50"))) const char D_0055AA50[16] = "%d,%d,%d %d";

/* String rodata migrated from camera-ico2_data.c */
__attribute__((section(".rodata.0x0055A9A8"))) const char D_0055A9A8[32] = "camera data version = [%d]\n";
__attribute__((section(".rodata.0x0055A9C8"))) const char D_0055A9C8[24] = "n_group[%d], n_pin[%d]\n";
__attribute__((section(".rodata.0x0055AA28"))) const char D_0055AA28[40] = "illegal camera data version [%d]\n";

/* Float rodata migrated from camera-ico2_data.c */
__attribute__((section(".rodata.0x0055AA60"))) const float D_0055AA60[4] = { 0.0f, -2e+02f, -5e+02f, 0.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "[%s]が見つかりません
" */
__attribute__((section(".rodata.0x0055A958"))) const char D_0055A958[24] = "[%s]\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\n";
/* EUC-JP: "１ステージに登録できるカメラセットは、最大[%d]個です。" */
__attribute__((section(".rodata.0x0055A970"))) const char D_0055A970[56] = "\243\261\245\271\245\306\241\274\245\270\244\313\305\320\317\277\244\307\244\255\244\353\245\253\245\341\245\351\245\273\245\303\245\310\244\317\241\242\272\307\302\347[%d]\270\304\244\307\244\271\241\243";
/* EUC-JP: "カメラデータのバージョンに異常があります。大森まで知らせてください
" */
__attribute__((section(".rodata.0x0055A9E0"))) const char D_0055A9E0[72] = "\245\253\245\341\245\351\245\307\241\274\245\277\244\316\245\320\241\274\245\270\245\347\245\363\244\313\260\333\276\357\244\254\244\242\244\352\244\336\244\271\241\243\302\347\277\271\244\336\244\307\303\316\244\351\244\273\244\306\244\257\244\300\244\265\244\244\n";
