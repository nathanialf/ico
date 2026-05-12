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
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".sdata.0x0063201C"))) int D_0063201C = 0;
__attribute__((section(".sdata.0x00632020"))) int D_00632020 = 0;
__attribute__((section(".sdata.0x00632030"))) int D_00632030 = 0;
__attribute__((section(".sdata.0x00632038"))) int D_00632038 = 0;
__attribute__((section(".sdata.0x00632194"))) int D_00632194 = 0;
__attribute__((section(".sdata.0x00632198"))) char D_00632198[8] = { 0 };
__attribute__((section(".sdata.0x006321A0"))) char D_006321A0[8] = { 0 };
__attribute__((section(".sdata.0x006321A8"))) char D_006321A8[8] = { 0 };
__attribute__((section(".sdata.0x00632244"))) int D_00632244 = 0;
__attribute__((section(".sdata.0x00632248"))) const char D_00632248[8] = "first\n";
__attribute__((section(".sdata.0x00632250"))) const char D_00632250[8] = "set\n";
__attribute__((section(".sdata.0x00632898"))) char D_00632898[8] = { 0 };
__attribute__((section(".sdata.0x006328A0"))) const char D_006328A0[8] = "e";
__attribute__((section(".sdata.0x006328A8"))) const char D_006328A8[8] = "0";
__attribute__((section(".sdata.0x006328B0"))) const char D_006328B0[8] = "FALSE";
__attribute__((section(".sdata.0x006328B8"))) char D_006328B8[8] = { 0 };

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
__attribute__((section(".rodata.0x00553A58"))) const char D_00553A58[16] = "file init\n";
__attribute__((section(".rodata.0x00553A68"))) const char D_00553A68[16] = "iosInit\n";
__attribute__((section(".rodata.0x00612A08"))) const char D_00612A08[40] = "Illegal Model ID number: %d (\"%s\")\n";
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
__attribute__((section(".rodata.0x00612E88"))) const char D_00612E88[32] = "LACK OF DYNAMIC MOTION MEMORY.\n";
__attribute__((section(".rodata.0x00612ED8"))) const char D_00612ED8[32] = "LACK OF SWAP MOTION MEMORY.\n";
__attribute__((section(".rodata.0x00612F30"))) const char D_00612F30[48] = "ReadSoundBdFile:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612F60"))) const char D_00612F60[48] = "ReadSoundHdFile:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612F90"))) const char D_00612F90[48] = "ReadSoundSqFile:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612FC0"))) const char D_00612FC0[48] = "ReadAdpcmFile:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00612FF0"))) const char D_00612FF0[48] = "ReadShockData:loaded::[%d]%s  (size:%d)\n";
__attribute__((section(".rodata.0x00613058"))) const char D_00613058[32] = "Illegal Char ID Number. %d\n";
__attribute__((section(".rodata.0x00613078"))) const char D_00613078[48] = "Link polygon & skelton & collision -> DObj. %d\n";
__attribute__((section(".rodata.0x006130A8"))) const char D_006130A8[16] = "polygon %p.\n";
__attribute__((section(".rodata.0x006130B8"))) const char D_006130B8[24] = "object name %s.\n";
__attribute__((section(".rodata.0x006130D0"))) const char D_006130D0[16] = "shadow %p.\n";
__attribute__((section(".rodata.0x006130E0"))) const char D_006130E0[24] = "shadow object name %s.\n";
__attribute__((section(".rodata.0x006130F8"))) const char D_006130F8[16] = "skelton %p.\n";
__attribute__((section(".rodata.0x00613108"))) const char D_00613108[16] = "collision %p.\n";

/* Float rodata migrated from charFileManager_data.c */
__attribute__((section(".rodata.0x00553758"))) const float D_00553758[2] = { 0.0f, 10.907349f };
