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
 * land in this same file (per-TU layout); typed
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
__attribute__((section(".sdata.0x006325A8"))) float D_006325A8[2] = { 100000.0f, 100000.0f };
__attribute__((section(".sdata.0x00633874"))) int D_00633874 = 0;
__attribute__((section(".sdata.0x00633878"))) unsigned int D_00633878 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x0063387C"))) int D_0063387C = 0;
__attribute__((section(".sdata.0x00633880"))) const char D_00633880[8] = "pt.%d";
__attribute__((section(".sdata.0x00633888"))) unsigned int D_00633888 = 0x00000062;
__attribute__((section(".sdata.0x0063388C"))) int D_0063388C = 0;
__attribute__((section(".sdata.0x00633890"))) int D_00633890 = 0;
__attribute__((section(".sdata.0x00633894"))) int D_00633894 = 0;
__attribute__((section(".sdata.0x006338A0"))) const char D_006338A0[] = "test.wp";
__attribute__((section(".sdata.0x006338A8"))) const char D_006338A8[8] = "saved\n";
__attribute__((section(".sdata.0x006338B0"))) const char D_006338B0[8] = "%d ";
__attribute__((section(".sdata.0x006338B8"))) const char D_006338B8[8] = "\n";
__attribute__((section(".sdata.0x006338C8"))) const char D_006338C8[] = "way0000";
__attribute__((section(".sdata.0x006338D0"))) const char D_006338D0[8] = "%s.txt";
__attribute__((section(".sdata.0x006338D8"))) const char D_006338D8[8] = "play";

__attribute__((section(".rodata.0x0055A138"))) const char D_0055A138[16] = "deamon start";
__attribute__((section(".rodata.0x0055A148"))) const char D_0055A148[16] = "bridge create";
__attribute__((section(".rodata.0x0055A158"))) const char D_0055A158[24] = "bridge delete";
__attribute__((section(".rodata.0x0055A2A0"))) const char D_0055A2A0[16] = "face_sadow_sd";
__attribute__((section(".rodata.0x0055A2B0"))) const char D_0055A2B0[32] = "face_sadow_sd_00";
__attribute__((section(".rodata.0x0055A370"))) const char D_0055A370[16] = "queen_ball_scr";
__attribute__((section(".rodata.0x0055A380"))) const char D_0055A380[16] = "sekika_boy";

/* String rodata migrated from way_util_data.c */
__attribute__((section(".rodata.0x00559DE0"))) const char D_00559DE0[16] = "not same group\n";
__attribute__((section(".rodata.0x00559DF0"))) const char D_00559DF0[24] = "not same grp, %d\n";
__attribute__((section(".rodata.0x00559E08"))) const char D_00559E08[16] = "wp:%p %d\n";
__attribute__((section(".rodata.0x00559E18"))) const char D_00559E18[24] = "abnormal bridge\n";
__attribute__((section(".rodata.0x00559E30"))) const char D_00559E30[24] = "target is over bridge\n";
__attribute__((section(".rodata.0x00559E48"))) const char D_00559E48[24] = "set_check_wp:%p %p\n";
__attribute__((section(".rodata.0x0055A030"))) const char D_0055A030[24] = "start animation down\n";
__attribute__((section(".rodata.0x0055A048"))) const char D_0055A048[24] = "start animation up\n";
__attribute__((section(".rodata.0x0055A2E0"))) const char D_0055A2E0[56] = "Now waiting for standby stream motion system... %d\n";
__attribute__((section(".rodata.0x0055A3D8"))) const char D_0055A3D8[24] = "girl %p\n";

/* Float rodata migrated from way_util_data.c */
__attribute__((section(".rodata.0x0055A198"))) const float D_0055A198[2] = { 0.0f, 4.3945312f };
__attribute__((section(".rodata.0x0055A1A0"))) const float D_0055A1A0[4] = { 6646.0f, -2157.0f, 1102.0f, 0.0f };
__attribute__((section(".rodata.0x0055A1B0"))) const float D_0055A1B0[4] = { -1e+06f, 0.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x0055A2D0"))) const float D_0055A2D0[4] = { 2e+03f, 0.0f, 0.0f, 1.0f };
__attribute__((section(".rodata.0x0055A360"))) const float D_0055A360[4] = { -1472.7711f, 928.20026f, -18.074427f, 0.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "ぶら下がりオブジェクトが見つかりません。(scpSetCageVelocityFriction)
" */
__attribute__((section(".rodata.0x00559E60"))) const char D_00559E60[72] = "\244\326\244\351\262\274\244\254\244\352\245\252\245\326\245\270\245\247\245\257\245\310\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243(scpSetCageVelocityFriction)\n";
/* EUC-JP: "押し回しオブジェクトが見つかりません。(scpGetRotObjectRotCount)
" */
__attribute__((section(".rodata.0x00559EA8"))) const char D_00559EA8[72] = "\262\241\244\267\262\363\244\267\245\252\245\326\245\270\245\247\245\257\245\310\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243(scpGetRotObjectRotCount)\n";
/* EUC-JP: "押し回しオブジェクトが見つかりません。(scpGetRotObjectZDirInclude)
" */
__attribute__((section(".rodata.0x00559EF0"))) const char D_00559EF0[72] = "\262\241\244\267\262\363\244\267\245\252\245\326\245\270\245\247\245\257\245\310\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243(scpGetRotObjectZDirInclude)\n";
/* EUC-JP: "LWSのスケルトンペアレント処理において,ノードが見つかりませんでした
" */
__attribute__((section(".rodata.0x00559F38"))) const char D_00559F38[72] = "LWS\244\316\245\271\245\261\245\353\245\310\245\363\245\332\245\242\245\354\245\363\245\310\275\350\315\375\244\313\244\252\244\244\244\306,\245\316\241\274\245\311\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\244\307\244\267\244\277\n";
/* EUC-JP: "scpGetWallCollision: (%4.3f, %4.3f, %4.3f) => (%4.3f, %4.3f, %4.3f)
	壁コリジョンが見つかりません。
" */
__attribute__((section(".rodata.0x00559F80"))) const char D_00559F80[112] = "scpGetWallCollision: (%4.3f, %4.3f, %4.3f) => (%4.3f, %4.3f, %4.3f)\n\t\312\311\245\263\245\352\245\270\245\347\245\363\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243\n";
/* EUC-JP: "ADPCM一杯で開けませんでした。
" */
__attribute__((section(".rodata.0x0055A060"))) const char D_0055A060[32] = "ADPCM\260\354\307\325\244\307\263\253\244\261\244\336\244\273\244\363\244\307\244\267\244\277\241\243\n";
/* EUC-JP: "戦闘曲を止めて,変わりにリクエストします。以降ステージ切り換えまで戦闘曲なりません。
" */
__attribute__((section(".rodata.0x0055A080"))) const char D_0055A080[88] = "\300\357\306\256\266\312\244\362\273\337\244\341\244\306,\312\321\244\357\244\352\244\313\245\352\245\257\245\250\245\271\245\310\244\267\244\336\244\271\241\243\260\312\271\337\245\271\245\306\241\274\245\270\300\332\244\352\264\271\244\250\244\336\244\307\300\357\306\256\266\312\244\312\244\352\244\336\244\273\244\363\241\243\n";
/* EUC-JP: "戦闘曲なっていないので,プログラムを止めないために
全部曲を止めて,変わりにリクエストします。
" */
__attribute__((section(".rodata.0x0055A0D8"))) const char D_0055A0D8[96] = "\300\357\306\256\266\312\244\312\244\303\244\306\244\244\244\312\244\244\244\316\244\307,\245\327\245\355\245\260\245\351\245\340\244\362\273\337\244\341\244\312\244\244\244\277\244\341\244\313\n\301\264\311\364\266\312\244\362\273\337\244\341\244\306,\312\321\244\357\244\352\244\313\245\352\245\257\245\250\245\271\245\310\244\267\244\336\244\271\241\243\n";
/* EUC-JP: "scpCheckExistAliveEnemy: 生きている敵を発見
" */
__attribute__((section(".rodata.0x0055A1D0"))) const char D_0055A1D0[48] = "scpCheckExistAliveEnemy: \300\270\244\255\244\306\244\244\244\353\305\250\244\362\310\257\270\253\n";
/* EUC-JP: "scpCheckExistAliveEnemy: 生きている敵はいません
" */
__attribute__((section(".rodata.0x0055A200"))) const char D_0055A200[56] = "scpCheckExistAliveEnemy: \300\270\244\255\244\306\244\244\244\353\305\250\244\317\244\244\244\336\244\273\244\363\n";
/* EUC-JP: "scpCheckExistAliveSpider: 生きている蜘蛛を発見
" */
__attribute__((section(".rodata.0x0055A238"))) const char D_0055A238[48] = "scpCheckExistAliveSpider: \300\270\244\255\244\306\244\244\244\353\303\330\351\341\244\362\310\257\270\253\n";
/* EUC-JP: "scpCheckExistAliveSpider: 生きている蜘蛛はいません
" */
__attribute__((section(".rodata.0x0055A268"))) const char D_0055A268[56] = "scpCheckExistAliveSpider: \300\270\244\255\244\306\244\244\244\353\303\330\351\341\244\317\244\244\244\336\244\273\244\363\n";
/* EUC-JP: "warpGirl.c:もしDEBUG STAGE SELECTでなくてここを通ったら おかしい！" */
__attribute__((section(".rodata.0x0055A390"))) const char D_0055A390[72] = "warpGirl.c:\244\342\244\267DEBUG STAGE SELECT\244\307\244\312\244\257\244\306\244\263\244\263\244\362\304\314\244\303\244\277\244\351 \244\252\244\253\244\267\244\244\241\252";
