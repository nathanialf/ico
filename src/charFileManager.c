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


unsigned int D_00274ECC = 0x00000000;

unsigned char D_0028A520[48] = { 0 };

unsigned char D_004B3B68[424] = { 0 };

unsigned char D_004B3D10[64] = { 0 };

unsigned int D_004B3D50 = 0x00000000;

const char D_004D42B0[48] = "object/sdf/boy/model/skelton.skb";

const char D_00553700[48] = "## internel error in libkernl.a!\n";

const float D_00553758[2] = { 0.0f, 10.907349f };

const char D_00553900[16] = "Main() in\n";

const char D_00553910[16] = "IosPadLock %d\n";

const char D_00553920[24] = "IosstgMgrLock %d\n";

const char D_00553938[16] = "main start\n";

const char D_00553948[16] = "idle() in\n";

const char D_00553958[64] = "--------------------------------------------------------------\n";

const char D_00553998[40] = "--- loop continues infinitely ... ---\n";

const char D_005539C0[16] = "idle time:%d\n";

const char D_005539D0[16] = "scheduler() in\n";

const char D_005539E0[40] = "\245\341\241\274\245\363\245\271\245\354\245\303\245\311\244\316\265\257\306\260\274\272\307\324\244\267\244\336\244\267\244\277\n";

const char D_00553A58[16] = "file init\n";

const char D_00553A68[16] = "iosInit\n";

const char D_00612A08[40] = "Illegal Model ID number: %d (\"%s\")\n";

const char D_00612A30[64] = "commmon/include/charFileName.h\244\316MAX_CHARS\244\362\301\375\244\344\244\267\244\306\244\257\244\300\244\265\244\244\n";

const char D_00612A70[24] = "src/charFileManager.c";

const char D_00612A88[48] = "ReadModelFile:Already loaded. (id:%d)%s\n";

const char D_00612AB8[56] = "ReadModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n";

const char D_00612AF0[32] = "Illegal Volume ID number. %d\n";

const char D_00612B10[48] = "ReadVolumeModelFile:Already loaded. (id:%d)%s\n";

const char D_00612B40[56] = "ReadVolumeModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n";

const char D_00612B78[32] = "Illegal Shadow ID number. %d\n";

const char D_00612B98[48] = "ReadShadowModelFile:Already loaded. (id:%d)%s\n";

const char D_00612BC8[56] = "ReadShadowModelFile:loaded::(id:%d)%s(addr:%p/size:%d)\n";

const char D_00612C00[48] = "ReadTextureFile:texture size is zero.%s\n";

const char D_00612C30[56] = "ReadTextureFile:loaded::(%d)%s(addr:%p/size:%d)\n";

const char D_00612C68[40] = "ReadSkeltonFile:Already loaded. %s\n";

const char D_00612C90[40] = "ReadSkeltonFile:loaded::%s  (size:%d)\n";

const char D_00612CB8[56] = "ReadSkeltonFile:Skelton file is not applied. %s\n";

const char D_00612CF0[40] = "ReadCollisionFile:Already loaded. %s\n";

const char D_00612D18[24] = "collision size:%d\n";

const char D_00612D30[48] = "ReadCollisionFile:loaded::%s  (size:%d)\n";

const char D_00612D60[16] = "ch      :%p\n";

const char D_00612D70[16] = "ch->wcl :%p\n";

const char D_00612D80[16] = "ch->fcl :%p\n";

const char D_00612D90[16] = "ch->wblk:%p\n";

const char D_00612DA0[16] = "ch->fblk:%p\n";

const char D_00612DB0[16] = "ch->ofs :%p\n";

const char D_00612DC0[16] = "w %2d %2d :%p\n";

const char D_00612DD0[16] = "f %2d %2d :%p\n";

const char D_00612DE0[56] = "ReadCollisionFile:Collision file is not applied. %s\n";

const char D_00612E18[56] = "ReadStageAnimationFile:loaded::[%d]%s (size:%d)\n";

const char D_00612E50[56] = "\245\300\245\244\245\312\245\337\245\303\245\257\245\342\241\274\245\267\245\347\245\363\316\316\260\350\244\316\245\341\245\342\245\352\244\254\302\255\244\352\244\336\244\273\244\363\241\243\n";

const char D_00612E88[32] = "LACK OF DYNAMIC MOTION MEMORY.\n";

const char D_00612EA8[48] = "\245\342\241\274\245\267\245\347\245\363\245\271\245\357\245\303\245\327\316\316\260\350\244\316\245\341\245\342\245\352\244\254\302\255\244\352\244\336\244\273\244\363\241\243\n";

const char D_00612ED8[32] = "LACK OF SWAP MOTION MEMORY.\n";

const char D_00612F30[48] = "ReadSoundBdFile:loaded::[%d]%s  (size:%d)\n";

const char D_00612F60[48] = "ReadSoundHdFile:loaded::[%d]%s  (size:%d)\n";

const char D_00612F90[48] = "ReadSoundSqFile:loaded::[%d]%s  (size:%d)\n";

const char D_00612FC0[48] = "ReadAdpcmFile:loaded::[%d]%s  (size:%d)\n";

const char D_00612FF0[48] = "ReadShockData:loaded::[%d]%s  (size:%d)\n";

const char D_00613020[56] = "\245\253\245\341\245\351\245\307\241\274\245\277\244\362\245\355\241\274\245\311\244\271\244\353\244\277\244\341\244\316\245\341\245\342\245\352\244\254\302\255\244\352\244\336\244\273\244\363\n";

const char D_00613058[32] = "Illegal Char ID Number. %d\n";

const char D_00613078[48] = "Link polygon & skelton & collision -> DObj. %d\n";

const char D_006130A8[16] = "polygon %p.\n";

const char D_006130B8[24] = "object name %s.\n";

const char D_006130D0[16] = "shadow %p.\n";

const char D_006130E0[24] = "shadow object name %s.\n";

const char D_006130F8[16] = "skelton %p.\n";

const char D_00613108[16] = "collision %p.\n";

const char D_00613118[48] = "\033[36m \245\267\245\247\245\244\245\327\245\307\241\274\245\277\244\316\277\364\276\360\312\363\244\254\270\305\244\244\244\307\244\271\241\243%d\033[m\n";

const char D_00613148[40] = "\033[36m\"%s\"\244\316\245\271\245\261\245\353\245\310\245\363\244\317\300\265\276\357(%x)\033[m\n";

const char D_006131B8[56] = "\033[33m\"%s\"\244\316\245\271\245\261\245\353\245\310\245\363\244\254\307\313\302\273\244\267\244\306\244\244\244\336\244\271(%x(NOW)!=%x)\033[m\n";

const char D_006131F0[56] = "\033[33m\245\355\241\274\245\311\304\276\270\345\244\253\244\351\245\271\245\306\241\274\245\270\307\333\303\326\244\316\264\326\244\313\262\365\244\265\244\354\244\336\244\267\244\277\033[m\n";

const char D_00613A70[16] = "Hide-High";

const char D_00613A80[16] = "Hide-Low";

const char D_00613A90[16] = "Through-High";

const char D_00613AA0[16] = "Through-Low";

const char D_00613AB0[16] = "High-Deco";

const char D_00613AC0[16] = "Low-Deco";

const char D_00613AD0[16] = "Variable";

const char D_00613AE0[16] = "Double+Wide";

const char D_00613AF0[16] = "Negative-High";

const char D_00613B00[16] = "Positive-High";

const char D_00613B10[16] = "Negative-Low";

const char D_00613B20[16] = "Positive-Low";

const char D_00613B30[16] = "Light+Ambient";

const char D_00613B40[16] = "AmbientOnly";

const char D_00613B50[16] = "LightOnly";

const char D_00613B60[16] = "Material";

const char D_00613B70[16] = "ExceptCharacter";

const char D_00613B80[16] = "IgnoreCarryZ";

const char D_00613B90[16] = "CarryZOnly";

unsigned int D_00616988[10] = { 0x2F637273, 0x4D6F6369, 0x2E637369, 0x00000063, 0x00000000, 0x00000000, 0x000000FF, 0x000000FF, 0x000000FF, 0x00000080 };

const char D_00616C80[16] = "\000\354\377\377\000\371\377\377\000(\000\000\000\016";

const char D_00632890[8] = "%d\n";

const char D_006328A0[8] = "e";

const char D_006328A8[8] = "0";

const char D_006328B0[8] = "FALSE";

unsigned char D_006328B8[8] = { 0 };

unsigned char D_006328C0[8] = { 0 };

const char D_006328C8[8] = "PAL";

const char D_006328D0[8] = "NTSC";

const char D_006328D8[8] = "Double";

const char D_006328E0[8] = "Single";

const char D_006328E8[8] = "On";

const char D_006328F0[8] = "Off";

const char D_006328F8[8] = "Process";

const char D_00632900[8] = "Half";

const char D_00632908[8] = "Normal";

const char D_00632910[8] = "BMP";

const char D_00632918[8] = "TIM2";

const char D_00632920[8] = "/16";

const char D_00632928[8] = "/8";

const char D_00632930[8] = "/4";

const char D_00632938[8] = "/2";

const char D_00632940[8] = "x1";

const char D_00632948[8] = "x2";

const char D_00632950[8] = "x4";

const char D_00632958[8] = "x8";

const char D_00632960[8] = "x16";

const char D_00632968[8] = "x32";

const char D_00632970[8] = "x64";

const char D_00632978[8] = "x128";

const char D_00632980[8] = "x256";

const char D_00632988[8] = "x512";

const char D_00632990[8] = "2Layer";

const char D_00632998[8] = "1Layer";

const char D_006329A0[8] = "AllOff";

const char D_006329A8[8] = "AllOn";

const char D_006329B0[8] = "Object";

const char D_006329B8[8] = "Line";

const char D_006329C0[8] = "QUEEN";

const char D_006329C8[8] = "ENEMY";

const char D_006329D0[8] = "BIRD";

const char D_006329D8[8] = "GIRL";

unsigned int D_006329E0 = 0x00594F42;

unsigned int D_00632F74 = 0x00000000;

unsigned int D_00632F78 = 0x00000000;

unsigned int D_00632F7C = 0x00000000;

unsigned char D_00632F80[8] = { 0 };

unsigned int D_00632F88[2] = { 0x80FFFFFF, 0x00000000 };

const char D_00632F90[8] = "e";

const char D_00632F98[8] = "%10s";

unsigned int D_00632FA0 = 0x00000000;

unsigned int D_00632FA4 = 0x00000000;

unsigned int D_00632FA8 = 0x00000000;

unsigned int D_00632FAC = 0x00000001;

unsigned int D_00632FB0 = 0x00000000;

unsigned int D_00632FB4 = 0x00000000;

unsigned int D_00632FB8[2] = { 0xFFFFFFFF, 0x00000000 };

const char D_00632FC0[8] = "MOTION1";

const char D_00632FC8[8] = "MOTION2";

const char D_00632FD0[8] = "MOTION3";

const char D_00632FD8[32] = "%s\n";

unsigned char D_00632FF8[8] = { 0 };

unsigned int D_00633000[2] = { 0x00808080, 0x00000000 };

const char D_00633008[8] = "/";

const char D_00633010[8] = "0";

unsigned int D_00633018 = 0x7F808080;

unsigned int D_0063301C = 0x00000000;

unsigned int D_00633020 = 0x00000000;

unsigned int D_00633024 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from charFileManager_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_006310DC = 0x4B189680;
unsigned int D_006310FC = 0x40490FDB;
unsigned int D_00631100 = 0x40490FDB;

/* Inlined data (Phase 3e) — migrated from charFileManager_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* misaligned arrays (scalar head + aligned tail) */
unsigned int D_004B3D54 = 0x00000000;
unsigned char D_004B3D58[11576] = { 0 };

/* Inlined data (Phase 3e) — migrated from charFileManager_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* C-referenced data (extern kept, def supplies bytes) */
int D_00632888 = 0x00000000;
unsigned int D_0063288C = 0x00000000;
int D_00632898 = 0x00000000;
unsigned int D_0063289C = 0x00000000;

#include "include_asm.h"

extern int D_00632850;
extern int D_0063285C;
extern int D_0063286C;
extern int D_00632888;
extern int D_00633E30;
extern int D_00633E24;
extern int D_00633E44;
extern int D_00633E28;
extern char D_006E4890[];
extern char D_004B2FD0[];
extern int D_00632898;
extern void func_0018B2F8(void);
extern void func_0018CFF0(void);

struct __attribute__((packed)) Pack24 { long long a; long long b; long long c; };

void func_001A0090(void) {
    D_00632850 = 0;
    D_0063285C = 0;
    D_0063286C = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A00A0);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A05D0);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A07F8);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A0A38);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A0EB8);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A0F60);

void func_001A1008(void) {
    D_00632888 = 0;
    D_00633E30 = -1;
    D_00633E24 = 0;
    D_00633E44 = 0;
}

void func_001A1020(void) {
    D_00633E28 = 0;
}

void func_001A1028(void) {}

void func_001A1030(void)
{
    char *dst = D_006E4890;
    char *end = dst + 0x9450;
    D_00632898 = 0;
    do {
        *(struct Pack24 *)dst = *(struct Pack24 *)D_004B2FD0;
        dst += 0x18;
    } while ((int)dst < (int)end);
    func_0018B2F8();
    func_0018CFF0();
}

void func_001A10B0(void)
{
    char *dst = D_006E4890;
    char *end = dst + 0x9450;
    D_00632898 = 0;
    do {
        if (*(int *)(dst + 0x14) == 1) {
            *(struct Pack24 *)dst = *(struct Pack24 *)D_004B2FD0;
        }
        dst += 0x18;
    } while ((int)dst < (int)end);
    func_0018B2F8();
    func_0018CFF0();
}

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
extern int D_00632028;
extern int D_00274EC0[];
extern int func_0013A0F8(int a0, char *q, const char *src, int code);
extern void func_001320E8(int *self, int p, char *q);
extern void func_00139598(int p);

void func_001A26E0(int *self, int unused, char *q)
{
    int p = func_0013A0F8(D_00632028, q, D_00612A70, 0x349);
    D_00274EC0[8]++;
    func_001320E8(self, p, q);
    func_00139598(p);
}
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2758);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A27F8);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2AB0);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2C18);

int func_001A2D58(int idx)
{
    return *(int *)((char *)D_006E4890 + idx * 0x18);
}

/* ASCII debug strings — re-derived from EE rodata bytes. */
/* ASCII preview: "ReadMotionFile:[%d]%s (size:%d): <ESC>[33m%1.2fMB<ESC>[m<LF>" */
const char D_00612EF8[56] = "ReadMotionFile:[%d]%s (size:%d): \033[33m%1.2fMB\033[m\n";
/* ASCII preview: "<ESC>[33m --- W - A - R - N - I - N - G ------------------------<ESC>[m<LF>" */
const char D_00613170[72] = "\033[33m --- W - A - R - N - I - N - G ------------------------\033[m\n";
/* ASCII preview: "<ESC>[33m ------------------------------------------------------<ESC>[m<LF>" */
const char D_00613228[72] = "\033[33m ------------------------------------------------------\033[m\n";
