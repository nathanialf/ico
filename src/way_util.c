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

extern float D_00630E7C;
extern float D_00630E80;
extern float D_00630E84;
extern float D_00630E88;
extern float D_00630E8C;
extern float D_00630E90;
extern float D_00630E94;
extern float D_00630E98;
extern float D_00630E9C;
extern float D_00630EA0;
extern float D_00630EA4;
extern float D_00630EA8;
extern float D_00630EAC;
extern float D_00630EB0;
extern float D_00630EB4;
extern float D_00630EB8;
extern float D_00630EBC;
extern float D_00630EC0;
extern float D_00630EC4;
extern float D_00630EC8;
extern float D_00630ECC;
extern float D_00630ED0;
extern float D_00630ED4;
extern int D_00633874;
extern unsigned int D_00633878;
extern int D_0063387C;
extern const char D_00633880[8];
extern unsigned int D_00633888;
extern int D_0063388C;
extern int D_00633890;
extern int D_00633894;
extern const char D_006338A0[];
extern const char D_006338A8[8];
extern const char D_006338B0[8];
extern const char D_006338B8[8];
extern const char D_006338C8[];
extern const char D_006338D0[8];
extern const char D_006338D8[8];

unsigned char D_0028A4A0[48] = { 0 };
unsigned int D_0028A5A0[8] = { 0x0000018D, 0x00000000, 0x00000000, 0x00000000, 0x0000018C, 0x00000000, 0x00000000, 0x00000000 };
unsigned int D_0028A5C0[8] = { 0x0000018D, 0x00000000, 0x00000000, 0x00000000, 0x0000018C, 0x00000000, 0x00000000, 0x00000000 };
unsigned int D_0028A5E0[8] = { 0x0000018D, 0x00000000, 0x00000000, 0x00000000, 0x0000018C, 0x00000000, 0x00000000, 0x00000000 };
unsigned int D_0028A600[8] = { 0x0000018D, 0x00000000, 0x00000000, 0x00000000, 0x0000018C, 0x00000000, 0x00000000, 0x00000000 };
unsigned int D_0028A620[8] = { 0x0000018D, 0x00000000, 0x00000000, 0x00000000, 0x0000018C, 0x00000000, 0x00000000, 0x00000000 };
unsigned int D_002F2318[27] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000001, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000090, 0x00000040, 0x00000030, 0x00000100, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
unsigned int D_002F23F0[532] = { 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001, 0x00000000, 0x000005EB, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
float D_002F2C40[16] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
unsigned int D_002F2C80[8] = { 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
unsigned char D_002F2CA0[192] = { 0 };
float D_002F2D60[24] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
unsigned char D_004CAED8[8] = { 0 };
unsigned char D_004CC1E0[16] = { 0 };
unsigned char D_004CC1F0[17520] = { 0 };
unsigned char D_004D0660[64] = { 0 };
unsigned int D_00559DA0[16] = { 0x2F637273, 0x5F796177, 0x6C697475, 0x0000632E, 0x00000080, 0x00000000, 0x00000000, 0x00000080, 0x00000000, 0x00000080, 0x00000000, 0x00000080, 0x00000000, 0x00000000, 0x00000080, 0x00000080 };
const char D_00559DE0[16] = "not same group\n";
const char D_00559DF0[24] = "not same grp, %d\n";
const char D_00559E08[16] = "wp:%p %d\n";
const char D_00559E18[24] = "abnormal bridge\n";
const char D_00559E30[24] = "target is over bridge\n";
const char D_00559E48[24] = "set_check_wp:%p %p\n";
/* EUC-JP: "ぶら下がりオブジェクトが見つかりません。(scpSetCageVelocityFriction)\n" */
const char D_00559E60[72] = "\244\326\244\351\262\274\244\254\244\352\245\252\245\326\245\270\245\247\245\257\245\310\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243(scpSetCageVelocityFriction)\n";
/* EUC-JP: "押し回しオブジェクトが見つかりません。(scpGetRotObjectRotCount)\n" */
const char D_00559EA8[72] = "\262\241\244\267\262\363\244\267\245\252\245\326\245\270\245\247\245\257\245\310\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243(scpGetRotObjectRotCount)\n";
/* EUC-JP: "押し回しオブジェクトが見つかりません。(scpGetRotObjectZDirInclude)\n" */
const char D_00559EF0[72] = "\262\241\244\267\262\363\244\267\245\252\245\326\245\270\245\247\245\257\245\310\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243(scpGetRotObjectZDirInclude)\n";
/* EUC-JP: "LWSのスケルトンペアレント処理において,ノードが見つかりませんでした\n" */
const char D_00559F38[72] = "LWS\244\316\245\271\245\261\245\353\245\310\245\363\245\332\245\242\245\354\245\363\245\310\275\350\315\375\244\313\244\252\244\244\244\306,\245\316\241\274\245\311\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\244\307\244\267\244\277\n";
/* EUC-JP: "scpGetWallCollision: (%4.3f, %4.3f, %4.3f) => (%4.3f, %4.3f, %4.3f)\n\t壁コリジョンが見つかりません。\n" */
const char D_00559F80[112] = "scpGetWallCollision: (%4.3f, %4.3f, %4.3f) => (%4.3f, %4.3f, %4.3f)\n\t\312\311\245\263\245\352\245\270\245\347\245\363\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243\n";
unsigned int D_00559FF0[4] = { 0x00000000, 0x00000010, 0x00000020, 0x00000080 };
unsigned int D_0055A000[4] = { 0x00000001, 0x00000002, 0x00000004, 0x00000000 };
const char D_0055A030[24] = "start animation down\n";
const char D_0055A048[24] = "start animation up\n";
/* EUC-JP: "ADPCM一杯で開けませんでした。\n" */
const char D_0055A060[32] = "ADPCM\260\354\307\325\244\307\263\253\244\261\244\336\244\273\244\363\244\307\244\267\244\277\241\243\n";
/* EUC-JP: "戦闘曲を止めて,変わりにリクエストします。以降ステージ切り換えまで戦闘曲なりません。\n" */
const char D_0055A080[88] = "\300\357\306\256\266\312\244\362\273\337\244\341\244\306,\312\321\244\357\244\352\244\313\245\352\245\257\245\250\245\271\245\310\244\267\244\336\244\271\241\243\260\312\271\337\245\271\245\306\241\274\245\270\300\332\244\352\264\271\244\250\244\336\244\307\300\357\306\256\266\312\244\312\244\352\244\336\244\273\244\363\241\243\n";
/* EUC-JP: "戦闘曲なっていないので,プログラムを止めないために\n全部曲を止めて,変わりにリクエストします。\n" */
const char D_0055A0D8[96] = "\300\357\306\256\266\312\244\312\244\303\244\306\244\244\244\312\244\244\244\316\244\307,\245\327\245\355\245\260\245\351\245\340\244\362\273\337\244\341\244\312\244\244\244\277\244\341\244\313\n\301\264\311\364\266\312\244\362\273\337\244\341\244\306,\312\321\244\357\244\352\244\313\245\352\245\257\245\250\245\271\245\310\244\267\244\336\244\271\241\243\n";
const char D_0055A138[16] = "deamon start";
const char D_0055A148[16] = "bridge create";
const char D_0055A158[24] = "bridge delete";
const float D_0055A198[2] = { 0.0f, 4.3945312f };
const float D_0055A1A0[4] = { 6646.0f, -2157.0f, 1102.0f, 0.0f };
const float D_0055A1B0[4] = { -1e+06f, 0.0f, 0.0f, 0.0f };
unsigned int D_0055A1C0[4] = { 0x00000000, 0x00000020, 0x00000010, 0x00000080 };
/* EUC-JP: "scpCheckExistAliveEnemy: 生きている敵を発見\n" */
const char D_0055A1D0[48] = "scpCheckExistAliveEnemy: \300\270\244\255\244\306\244\244\244\353\305\250\244\362\310\257\270\253\n";
/* EUC-JP: "scpCheckExistAliveEnemy: 生きている敵はいません\n" */
const char D_0055A200[56] = "scpCheckExistAliveEnemy: \300\270\244\255\244\306\244\244\244\353\305\250\244\317\244\244\244\336\244\273\244\363\n";
/* EUC-JP: "scpCheckExistAliveSpider: 生きている蜘蛛を発見\n" */
const char D_0055A238[48] = "scpCheckExistAliveSpider: \300\270\244\255\244\306\244\244\244\353\303\330\351\341\244\362\310\257\270\253\n";
/* EUC-JP: "scpCheckExistAliveSpider: 生きている蜘蛛はいません\n" */
const char D_0055A268[56] = "scpCheckExistAliveSpider: \300\270\244\255\244\306\244\244\244\353\303\330\351\341\244\317\244\244\244\336\244\273\244\363\n";
const char D_0055A2A0[16] = "face_sadow_sd";
const char D_0055A2B0[32] = "face_sadow_sd_00";
const float D_0055A2D0[4] = { 2e+03f, 0.0f, 0.0f, 1.0f };
const char D_0055A2E0[56] = "Now waiting for standby stream motion system... %d\n";
const float D_0055A360[4] = { -1472.7711f, 928.20026f, -18.074427f, 0.0f };
const char D_0055A370[16] = "queen_ball_scr";
const char D_0055A380[16] = "sekika_boy";
/* EUC-JP: "warpGirl.c:もしDEBUG STAGE SELECTでなくてここを通ったら おかしい！" */
const char D_0055A390[72] = "warpGirl.c:\244\342\244\267DEBUG STAGE SELECT\244\307\244\312\244\257\244\306\244\263\244\263\244\362\304\314\244\303\244\277\244\351 \244\252\244\253\244\267\244\244\241\252";
const char D_0055A3D8[24] = "girl %p\n";
unsigned char D_00631A00[16] = { 0 };
unsigned int D_00632514 = 0x00000000;
unsigned char D_00632548[8] = { 0 };
unsigned int D_00632550[16] = { 0x00000000, 0x00000000, 0x65736572, 0x00000A74, 0x0A746968, 0x00000000, 0x65657266, 0x0000000A, 0x6C696166, 0x0000000A, 0x253A7665, 0x00000A66, 0x20747364, 0x000A7025, 0x70253E2D, 0x0000000A };
const char D_00632598[8] = "0";
const char D_006325A0[8] = "gid:%d\n";
float D_006325A8[2] = { 100000.0f, 100000.0f };
unsigned int D_006325BC = 0x00000000;
unsigned char D_006325C0[8] = { 0 };
unsigned int D_006325C8 = 0x00000000;
unsigned int D_006325CC = 0x00000000;

/* Inlined data (Phase 3e) — migrated from way_util_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00630E38 = 10000.0f;
/* 0x630E3C (100000.0f) is func_0017A230's compiler .lit4 pool entry, not a
 * named global — it is provided by the literal in func_0017A230 and placed
 * via config/lit4_pool_slots.txt (.lit4 -> .lit4.0x00630E3C). See the
 * ".lit4/.lit8 TU-pool migration" task. */
float D_00630E40 = 100000.0f;
float D_00630E44 = 100000.0f;
float D_00630E48 = 100000.0f;
float D_00630E4C = 100000.0f;
float D_00630E50 = 100000.0f;
float D_00630E54 = 100000.0f;
float D_00630E58 = 100000.0f;
float D_00630E5C = 100000.0f;
float D_00630E60 = 100000.0f;
float D_00630E64 = 100000.0f;
float D_00630E68 = 100000.0f;
float D_00630E6C = 40000.0f;
float D_00630E70 = 40000.0f;
float D_00630E74 = 3.1415927f;
float D_00630E78 = 3.1415927f;

/* Inlined data (Phase 3e) — migrated from way_util_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* misaligned arrays (scalar head + aligned tail) */
unsigned int D_002F2384 = 0xFFFFFFFF;
unsigned int D_002F2388[26] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000001, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000090, 0x00000140, 0x00000030, 0x00000100, 0x00000030, 0x00000000, 0x00000000, 0x00000000 };

#include "include_asm.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00178990);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00178B20);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00178CC8);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00178E78);

/* Matched body inlined from src/cod/079040.c during TU coalesce. */
void func_00179040(void) {
    volatile int local[12];
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017904C);

/* Matched body inlined from src/cod/079050.c during TU coalesce. */
void func_00179050(void) {
    volatile int local[12];
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017905C);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179060);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179248);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179438);
extern void func_00139598(int x);
void func_00179558(int *self)
{
    func_00139598(self[0]);
    func_00139598(self[2]);
    func_00139598(self[1]);
    func_00139598(self[3]);
    func_00139598(self[4]);
    func_00139598(self[5]);
    func_00139598(self[6]);
    func_00139598((int)self);
}
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_001795B8);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179878);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179B50);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179E10);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179F68);
extern char *func_00205A78(int handle);
extern char *func_00205A98(char *node);
extern void func_00243AE8(int *buf, int *p, int *q);
extern float func_0016A2F8(int a0);

char *func_0017A230(int *arg0, int handle)
{
    int buf[4];
    char *result;
    char *node;
    float best;
    result = func_00205A78(handle);
    best = 100000.0f;
    node = result;
    if (result != 0) {
        do {
            float d;
            func_00243AE8(buf, (int *)(node + 0x10), arg0);
            d = func_0016A2F8((int)buf);
            if (d < best) {
                best = d;
                result = node;
            }
            node = func_00205A98(node);
        } while (node != 0);
    }
    return result;
}
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A2C8);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A368);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A410);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A4C0);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A578);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A638);
extern char *func_00205A78(int handle);
extern char *func_00205A98(char *node);
extern void func_00243AE8(int *buf, int *p, int *q);
extern float func_0016A2F8(int a0);

char *func_0017A6F8(int *arg0, float thresh)
{
    int buf[4];
    char *node = func_00205A78(D_00633874);
    if (node == 0) {
        return 0;
    }
    __asm__ __volatile__("" ::: "memory");
    do {
        func_00243AE8(buf, (int *)(node + 0x10), arg0);
        if (func_0016A2F8((int)buf) < thresh) {
            return node;
        }
        node = func_00205A98(node);
    } while (node != 0);
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A788);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A830);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A910);

/* Matched body inlined from src/cod/07A9B8.c during TU coalesce. */
extern void func_00178990(int *a0, int a1);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A9B8);

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A9D4);

/* Matched body inlined from src/cod/07A9D8.c during TU coalesce. */
extern void func_00104508(int *a0, int a1);
void func_0017A9D8(int a0)
{
    int locals[4];
    func_00104508(locals, a0);
    func_00178990(locals, -1);

}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AA04);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AA08);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AB20);
extern unsigned char D_004CAEC0[];

void *func_0017AC48(int arg0, int arg1)
{
    unsigned char *base = D_004CAEC0;
    char *b = (char *)D_004CC1E0;
    int va, vb, new_var, i;
    char *bA, *bB, *a;
    for (i = 0; i < 0x1318; i += 0x34) {
        a = (char *)base + i;
        if (*(int *)(a + 0x0) == 0) continue;
        if (*(int *)(a + 0x18) == 0) continue;
        bA = (char *)(*(int *)(a + 0x20) * 0x40 + (int)b);
        new_var = *(int *)(a + 0x24) * 0x40;
        va = *(int *)(bA + 0x20);
        bB = (char *)(new_var + (int)b);
        if (va != arg0) goto skipA;
        vb = *(int *)(bB + 0x20);
        if (vb != arg1) goto chkB;
        return bB;
    skipA:
        vb = *(int *)(bB + 0x20);
    chkB:
        if (vb != arg0) continue;
        if (va != arg1) continue;
        return bA;
    }
    return 0;
}
int func_0017ACD8(int arg0, int arg1)
{
    unsigned char *base = D_004CAEC0;
    char *b = (char *)D_004CC1E0;
    int va, vb, new_var, i;
    char *bA, *bB, *a;
    for (i = 0; i < 0x1318; i += 0x34) {
        a = (char *)base + i;
        if (*(int *)(a + 0x0) == 0) continue;
        if (*(int *)(a + 0x18) == 0) continue;
        bA = (char *)(*(int *)(a + 0x20) * 0x40 + (int)b);
        new_var = *(int *)(a + 0x24) * 0x40;
        va = *(int *)(bA + 0x20);
        bB = (char *)(new_var + (int)b);
        if (va != arg0) goto skipA;
        vb = *(int *)(bB + 0x20);
        if (vb != arg1) goto chkB;
        return *(int *)(a + 0xC);
    skipA:
        vb = *(int *)(bB + 0x20);
    chkB:
        if (vb != arg0) continue;
        if (va != arg1) continue;
        return *(int *)(a + 0x8);
    }
    return 0;
}


/* === BEGIN recovered struct shapes (tools/place_struct_shapes.py) === */
/* Field layouts mined from load/store access patterns; SPARSE
 * (only touched offsets, no padding). Unused typedefs — they add
 * no symbol and cannot affect codegen. Cast as ((S_<VMA> *)D_<VMA>).
 */

typedef struct {
    unsigned char    f_44;  /* 0x44  x2 */
    unsigned long long f_50;  /* 0x50  x3 */
    unsigned long long f_58;  /* 0x58  x3 */
    unsigned long long f_60;  /* 0x60  x3 */
    unsigned long long f_68;  /* 0x68  x3 */
    unsigned long long f_70;  /* 0x70  x3 */
    unsigned long long f_78;  /* 0x78  x3 */
    unsigned int     f_80;  /* 0x80  x1 */
    unsigned int     f_84;  /* 0x84  x1 */
    unsigned int     f_88;  /* 0x88  x1 */
    unsigned int     f_90;  /* 0x90  x1 */
    unsigned int     f_94;  /* 0x94  x1 */
    unsigned int     f_98;  /* 0x98  x1 */
    unsigned int     f_A0;  /* 0xA0  x1 */
    unsigned int     f_A4;  /* 0xA4  x1 */
} S_006D0470;  /* 28 accesses */

typedef struct {
    unsigned int     f_8;  /* 0x8  x4 */
    unsigned int     f_C;  /* 0xC  x8 */
    unsigned int     f_20;  /* 0x20  x5 */
    unsigned int     f_28;  /* 0x28  x2 */
} S_004CC1E0;  /* stride 0x40, 19 accesses */

/* === END recovered struct shapes === */
