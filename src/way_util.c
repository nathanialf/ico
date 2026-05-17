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

extern float D_00630E3C;
extern float D_00630E40;
extern float D_00630E44;
extern float D_00630E48;
extern float D_00630E4C;
extern float D_00630E50;
extern float D_00630E54;
extern float D_00630E58;
extern float D_00630E5C;
extern float D_00630E60;
extern float D_00630E64;
extern float D_00630E68;
extern float D_00630E6C;
extern float D_00630E70;
extern float D_00630E74;
extern float D_00630E78;
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
extern const char D_00632598[8];
extern float D_006325A8[2];
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
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179558);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_001795B8);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179878);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179B50);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179E10);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_00179F68);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A230);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A2C8);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A368);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A410);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A4C0);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A578);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A638);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A6F8);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A788);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A830);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A910);

/* Matched body inlined from src/cod/07A9B8.c during TU coalesce. */
extern void func_00178990(int *a0, int a1);
void func_0017A9B8(int x) {
    func_00178990((int *)x, -1);
    DEFEAT_TCO();
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A9D4);

/* Matched body inlined from src/cod/07A9D8.c during TU coalesce. */
extern void func_00104508(int *a0, int a1);
void func_0017A9D8(int a0)
{
    int locals[4];
    func_00104508(locals, a0);
    func_00178990(locals, -1);
    KEEP_LIVE(locals);
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AA04);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AA08);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AB20);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AC48);
INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017ACD8);
