/* StageAnimation.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00631A10"))) char D_00631A10[16] = { 0 };
__attribute__((section(".sdata.0x00631D88"))) const char D_00631D88[8] = "0";
__attribute__((section(".sdata.0x00631D90"))) const char D_00631D90[8] = "BGA";
__attribute__((section(".sdata.0x00631D98"))) const char D_00631D98[8] = "e";
__attribute__((section(".sdata.0x00631DA0"))) const char D_00631DA0[8] = "PSMT8";
__attribute__((section(".sdata.0x00631DA8"))) const char D_00631DA8[8] = "PSMT4";
__attribute__((section(".sdata.0x00631DB0"))) const char D_00631DB0[] = "PSMCT32";
__attribute__((section(".sdata.0x00631DB8"))) const char D_00631DB8[] = "PSMCT24";
__attribute__((section(".sdata.0x00631DC0"))) const char D_00631DC0[] = "PSMCT16";
__attribute__((section(".sdata.0x00631DC8"))) const char D_00631DC8[8] = "NONE";

__attribute__((section(".rodata.0x00555BF8"))) const char D_00555BF8[24] = "src/StageAnimation.c";

__attribute__((section(".rodata.0x00612348"))) const char D_00612348[48] = "object/sdf/demo/conte06/d6.smb";
__attribute__((section(".rodata.0x00612378"))) const char D_00612378[48] = "object/sdf/demo/conte09/d9.smb";
__attribute__((section(".rodata.0x006123A8"))) const char D_006123A8[48] = "object/sdf/demo/conte09a/d9a.smb";
__attribute__((section(".rodata.0x00612498"))) const char D_00612498[48] = "object/sdf/demo/conte13/d13.smb";
__attribute__((section(".rodata.0x006124C8"))) const char D_006124C8[48] = "object/sdf/demo/conte06/e3d6.smb";

/* String rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x00555BB0"))) const char D_00555BB0[32] = "Bga Object Already %d %d %d\n";
__attribute__((section(".rodata.0x00555BD0"))) const char D_00555BD0[40] = "stage_MakeGObj:can't alloc gobj %d\n";
__attribute__((section(".rodata.0x00555C10"))) const char D_00555C10[40] = "Too much Stage Animation Objects.\n";
__attribute__((section(".rodata.0x00555C38"))) const char D_00555C38[48] = "stage_ApplyData:Data is not registered. \n\n%s\n";
__attribute__((section(".rodata.0x00555CF8"))) const char D_00555CF8[40] = "Max Bga = %d // Max DObj %d\n";
__attribute__((section(".rodata.0x00555D78"))) const char D_00555D78[56] = "stage_CheckAnimationFinish:illegal Animation No.\n";
__attribute__((section(".rodata.0x00555DB0"))) const char D_00555DB0[48] = "stage_ContinueAnimation:illegal Animation No.\n";

/* Float rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x00555B70"))) const float D_00555B70[16] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };

/* String-pool rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x006123D8"))) const char D_006123D8[96] = "object/sdf/demo/conte09a/d9b.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000object/sdf/demo/conte12/d12.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
__attribute__((section(".rodata.0x00612438"))) const char D_00612438[96] = "object/sdf/demo/conte12x/d12x.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000object/sdf/demo/conte12x/d12y.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "stgBgas が%d有り MAX_ANIM_KIND %dを越えました
" */
__attribute__((section(".rodata.0x00555C68"))) const char D_00555C68[48] = "stgBgas \244\254%d\315\255\244\352 MAX_ANIM_KIND %d\244\362\261\333\244\250\244\336\244\267\244\277\n";
/* EUC-JP: "1ステージ中の BgAnimation の種類が多すぎます
" */
__attribute__((section(".rodata.0x00555C98"))) const char D_00555C98[48] = "1\245\271\245\306\241\274\245\270\303\346\244\316 BgAnimation \244\316\274\357\316\340\244\254\302\277\244\271\244\256\244\336\244\271\n";
/* EUC-JP: "stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました
" */
__attribute__((section(".rodata.0x00555CC8"))) const char D_00555CC8[48] = "stgBgas \244\254%d\315\255\244\352 MAX_ANIM_GOBJ %d\244\362\261\333\244\250\244\336\244\267\244\277\n";
/* EUC-JP: "指定したIDが存在しないか、アニメーションが読み込まれていません.
" */
__attribute__((section(".rodata.0x00555DE0"))) const char D_00555DE0[72] = "\273\330\304\352\244\267\244\277ID\244\254\302\270\272\337\244\267\244\312\244\244\244\253\241\242\245\242\245\313\245\341\241\274\245\267\245\347\245\363\244\254\306\311\244\337\271\376\244\336\244\354\244\306\244\244\244\336\244\273\244\363.\n";
/* EUC-JP: "ステージセグメントにメモリが確保できません.(ヒープメモリ不足)
" */
__attribute__((section(".rodata.0x00555E28"))) const char D_00555E28[72] = "\245\271\245\306\241\274\245\270\245\273\245\260\245\341\245\363\245\310\244\313\245\341\245\342\245\352\244\254\263\316\312\335\244\307\244\255\244\336\244\273\244\363.(\245\322\241\274\245\327\245\341\245\342\245\352\311\324\302\255)\n";
