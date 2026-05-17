/* charFileManager.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00612A70"))) const char D_00612A70[24] = "src/charFileManager.c";

__attribute__((section(".data.0x004D42B0"))) const char D_004D42B0[48] = "object/sdf/boy/model/skelton.skb";
__attribute__((section(".rodata.0x00613A70"))) const char D_00613A70[16] = "Hide-High";
__attribute__((section(".rodata.0x00613A80"))) const char D_00613A80[16] = "Hide-Low";
__attribute__((section(".rodata.0x00613A90"))) const char D_00613A90[16] = "Through-High";
__attribute__((section(".rodata.0x00613AA0"))) const char D_00613AA0[16] = "Through-Low";
__attribute__((section(".rodata.0x00613AB0"))) const char D_00613AB0[16] = "High-Deco";
__attribute__((section(".rodata.0x00613AC0"))) const char D_00613AC0[16] = "Low-Deco";
__attribute__((section(".rodata.0x00613AD0"))) const char D_00613AD0[16] = "Variable";
__attribute__((section(".rodata.0x00613AE0"))) const char D_00613AE0[16] = "Double+Wide";
__attribute__((section(".rodata.0x00613AF0"))) const char D_00613AF0[16] = "Negative-High";
__attribute__((section(".rodata.0x00613B00"))) const char D_00613B00[16] = "Positive-High";
__attribute__((section(".rodata.0x00613B10"))) const char D_00613B10[16] = "Negative-Low";
__attribute__((section(".rodata.0x00613B20"))) const char D_00613B20[16] = "Positive-Low";
__attribute__((section(".rodata.0x00613B30"))) const char D_00613B30[16] = "Light+Ambient";
__attribute__((section(".rodata.0x00613B40"))) const char D_00613B40[16] = "AmbientOnly";
__attribute__((section(".rodata.0x00613B50"))) const char D_00613B50[16] = "LightOnly";
__attribute__((section(".rodata.0x00613B60"))) const char D_00613B60[16] = "Material";
__attribute__((section(".rodata.0x00613B70"))) const char D_00613B70[16] = "ExceptCharacter";
__attribute__((section(".rodata.0x00613B80"))) const char D_00613B80[16] = "IgnoreCarryZ";
__attribute__((section(".rodata.0x00613B90"))) const char D_00613B90[16] = "CarryZOnly";

/* String rodata migrated from charFileManager_data.c */
__attribute__((section(".rodata.0x00553700"))) const char D_00553700[48] = "## internel error in libkernl.a!\n";
__attribute__((section(".rodata.0x00553900"))) const char D_00553900[16] = "Main() in\n";
__attribute__((section(".rodata.0x00553910"))) const char D_00553910[16] = "IosPadLock %d\n";
__attribute__((section(".rodata.0x00553920"))) const char D_00553920[24] = "IosstgMgrLock %d\n";
__attribute__((section(".rodata.0x00553938"))) const char D_00553938[16] = "main start\n";
__attribute__((section(".rodata.0x00553948"))) const char D_00553948[16] = "idle() in\n";
__attribute__((section(".rodata.0x00553958"))) const char D_00553958[64] = "--------------------------------------------------------------\n";
__attribute__((section(".rodata.0x00553998"))) const char D_00553998[40] = "--- loop continues infinitely ... ---\n";
__attribute__((section(".rodata.0x005539C0"))) const char D_005539C0[16] = "idle time:%d\n";
__attribute__((section(".rodata.0x005539D0"))) const char D_005539D0[16] = "scheduler() in\n";
/* EUC-JP: "メーンスレッドの起動失敗しました\n" */
__attribute__((section(".rodata.0x005539E0"))) const char D_005539E0[40] = "\245\341\241\274\245\363\245\271\245\354\245\303\245\311\244\316\265\257\306\260\274\272\307\324\244\267\244\336\244\267\244\277\n";
__attribute__((section(".rodata.0x00553A58"))) const char D_00553A58[16] = "file init\n";
__attribute__((section(".rodata.0x00553A68"))) const char D_00553A68[16] = "iosInit\n";
__attribute__((section(".rodata.0x00612A08"))) const char D_00612A08[40] = "Illegal Model ID number: %d (\"%s\")\n";
/* EUC-JP: "commmon/include/charFileName.hのMAX_CHARSを増やしてください\n" */
__attribute__((section(".rodata.0x00612A30"))) const char D_00612A30[64] = "commmon/include/charFileName.h\244\316MAX_CHARS\244\362\301\375\244\344\244\267\244\306\244\257\244\300\244\265\244\244\n";
__attribute__((section(".rodata.0x00612A88"))) const char D_00612A88[48] = "ReadModelFile:Already loaded. (id:%d)%s\n";
__attribute__((section(".rodata.0x00612AB8"))) const char D_00612AB8[56] = "ReadModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n";
__attribute__((section(".rodata.0x00612AF0"))) const char D_00612AF0[32] = "Illegal Volume ID number. %d\n";
__attribute__((section(".rodata.0x00612B10"))) const char D_00612B10[48] = "ReadVolumeModelFile:Already loaded. (id:%d)%s\n";
__attribute__((section(".rodata.0x00612B40"))) const char D_00612B40[56] = "ReadVolumeModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n";
__attribute__((section(".rodata.0x00612B78"))) const char D_00612B78[32] = "Illegal Shadow ID number. %d\n";
__attribute__((section(".rodata.0x00612B98"))) const char D_00612B98[48] = "ReadShadowModelFile:Already loaded. (id:%d)%s\n";
__attribute__((section(".rodata.0x00612BC8"))) const char D_00612BC8[56] = "ReadShadowModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n";
__attribute__((section(".rodata.0x00612C00"))) const char D_00612C00[48] = "ReadTextureFile:texture size is zero.%s\n";
__attribute__((section(".rodata.0x00612C30"))) const char D_00612C30[56] = "ReadTextureFile:loaded::(%d)%s(addr:%p/size:%d)\n";
__attribute__((section(".rodata.0x00612C68"))) const char D_00612C68[40] = "ReadSkeltonFile:Already loaded. %s\n";
__attribute__((section(".rodata.0x00612C90"))) const char D_00612C90[40] = "ReadSkeltonFile:loaded::%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612CB8"))) const char D_00612CB8[56] = "ReadSkeltonFile:Skelton file is not applied. %s\n";
__attribute__((section(".rodata.0x00612CF0"))) const char D_00612CF0[40] = "ReadCollisionFile:Already loaded. %s\n";
__attribute__((section(".rodata.0x00612D18"))) const char D_00612D18[24] = "collision size:%d\n";
__attribute__((section(".rodata.0x00612D30"))) const char D_00612D30[48] = "ReadCollisionFile:loaded::%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612D60"))) const char D_00612D60[16] = "ch      :%p\n";
__attribute__((section(".rodata.0x00612D70"))) const char D_00612D70[16] = "ch->wcl :%p\n";
__attribute__((section(".rodata.0x00612D80"))) const char D_00612D80[16] = "ch->fcl :%p\n";
__attribute__((section(".rodata.0x00612D90"))) const char D_00612D90[16] = "ch->wblk:%p\n";
__attribute__((section(".rodata.0x00612DA0"))) const char D_00612DA0[16] = "ch->fblk:%p\n";
__attribute__((section(".rodata.0x00612DB0"))) const char D_00612DB0[16] = "ch->ofs :%p\n";
__attribute__((section(".rodata.0x00612DC0"))) const char D_00612DC0[16] = "w %2d %2d :%p\n";
__attribute__((section(".rodata.0x00612DD0"))) const char D_00612DD0[16] = "f %2d %2d :%p\n";
__attribute__((section(".rodata.0x00612DE0"))) const char D_00612DE0[56] = "ReadCollisionFile:Collision file is not applied. %s\n";
__attribute__((section(".rodata.0x00612E18"))) const char D_00612E18[56] = "ReadStageAnimationFile:loaded::[%d]%s (size:%d)\n";
/* EUC-JP: "ダイナミックモーション領域のメモリが足りません。\n" */
__attribute__((section(".rodata.0x00612E50"))) const char D_00612E50[56] = "\245\300\245\244\245\312\245\337\245\303\245\257\245\342\241\274\245\267\245\347\245\363\316\316\260\350\244\316\245\341\245\342\245\352\244\254\302\255\244\352\244\336\244\273\244\363\241\243\n";
__attribute__((section(".rodata.0x00612E88"))) const char D_00612E88[32] = "LACK OF DYNAMIC MOTION MEMORY.\n";
/* EUC-JP: "モーションスワップ領域のメモリが足りません。\n" */
__attribute__((section(".rodata.0x00612EA8"))) const char D_00612EA8[48] = "\245\342\241\274\245\267\245\347\245\363\245\271\245\357\245\303\245\327\316\316\260\350\244\316\245\341\245\342\245\352\244\254\302\255\244\352\244\336\244\273\244\363\241\243\n";
__attribute__((section(".rodata.0x00612ED8"))) const char D_00612ED8[32] = "LACK OF SWAP MOTION MEMORY.\n";
__attribute__((section(".rodata.0x00612F30"))) const char D_00612F30[48] = "ReadSoundBdFile:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612F60"))) const char D_00612F60[48] = "ReadSoundHdFile:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612F90"))) const char D_00612F90[48] = "ReadSoundSqFile:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612FC0"))) const char D_00612FC0[48] = "ReadAdpcmFile:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612FF0"))) const char D_00612FF0[48] = "ReadShockData:loaded::[%d]%s  (size:%d)\n";
/* EUC-JP: "カメラデータをロードするためのメモリが足りません\n" */
__attribute__((section(".rodata.0x00613020"))) const char D_00613020[56] = "\245\253\245\341\245\351\245\307\241\274\245\277\244\362\245\355\241\274\245\311\244\271\244\353\244\277\244\341\244\316\245\341\245\342\245\352\244\254\302\255\244\352\244\336\244\273\244\363\n";
__attribute__((section(".rodata.0x00613058"))) const char D_00613058[32] = "Illegal Char ID Number. %d\n";
__attribute__((section(".rodata.0x00613078"))) const char D_00613078[48] = "Link polygon & skelton & collision -> DObj. %d\n";
__attribute__((section(".rodata.0x006130A8"))) const char D_006130A8[16] = "polygon %p.\n";
__attribute__((section(".rodata.0x006130B8"))) const char D_006130B8[24] = "object name %s.\n";
__attribute__((section(".rodata.0x006130D0"))) const char D_006130D0[16] = "shadow %p.\n";
__attribute__((section(".rodata.0x006130E0"))) const char D_006130E0[24] = "shadow object name %s.\n";
__attribute__((section(".rodata.0x006130F8"))) const char D_006130F8[16] = "skelton %p.\n";
__attribute__((section(".rodata.0x00613108"))) const char D_00613108[16] = "collision %p.\n";
/* EUC-JP: "\x1b[36m シェイプデータの数情報が古いです。%d\x1b[m\n" */
__attribute__((section(".rodata.0x00613118"))) const char D_00613118[48] = "\033[36m \245\267\245\247\245\244\245\327\245\307\241\274\245\277\244\316\277\364\276\360\312\363\244\254\270\305\244\244\244\307\244\271\241\243%d\033[m\n";
/* EUC-JP: "\x1b[36m\"%s\"のスケルトンは正常(%x)\x1b[m\n" */
__attribute__((section(".rodata.0x00613148"))) const char D_00613148[40] = "\033[36m\"%s\"\244\316\245\271\245\261\245\353\245\310\245\363\244\317\300\265\276\357(%x)\033[m\n";
/* EUC-JP: "\x1b[33m\"%s\"のスケルトンが破損しています(%x(NOW)!=%x)\x1b[m\n" */
__attribute__((section(".rodata.0x006131B8"))) const char D_006131B8[56] = "\033[33m\"%s\"\244\316\245\271\245\261\245\353\245\310\245\363\244\254\307\313\302\273\244\267\244\306\244\244\244\336\244\271(%x(NOW)!=%x)\033[m\n";
/* EUC-JP: "\x1b[33mロード直後からステージ配置の間に壊されました\x1b[m\n" */
__attribute__((section(".rodata.0x006131F0"))) const char D_006131F0[56] = "\033[33m\245\355\241\274\245\311\304\276\270\345\244\253\244\351\245\271\245\306\241\274\245\270\307\333\303\326\244\316\264\326\244\313\262\365\244\265\244\354\244\336\244\267\244\277\033[m\n";

/* Float rodata migrated from charFileManager_data.c */
__attribute__((section(".rodata.0x00553758"))) const float D_00553758[2] = { 0.0f, 10.907349f };

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A1138);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A1308);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A14D8);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A16B8);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A17C0);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A1A18);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A1D88);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A1E90);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A20D8);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2170);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2320);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2500);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2610);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A26E0);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2758);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A27F8);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2AB0);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2C18);
