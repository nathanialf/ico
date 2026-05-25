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
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

extern float D_00631204;
extern float D_00631208;
extern float D_0063120C;
extern float D_00631210;
extern float D_00631214;
extern float D_00631218;
extern float D_0063121C;
extern float D_00631220;
extern float D_00631224;
extern float D_00631228;
extern float D_0063122C;
extern float D_00631230;
extern char D_00631940[16];
extern char D_00631950[16];
extern int D_00632D58;
extern float D_006332A8;
extern unsigned int D_006332AC;
extern unsigned int D_006332B0;
extern unsigned int D_006332B4;
extern int D_006332B8;
extern int D_006332BC;
extern int D_006332C0;
extern int D_006332C4;
extern char D_006332C8[8];
extern int D_006332D0;
extern int D_006332D4;
extern char D_006332D8;
extern char D_006332D9;
extern char D_006332DA;
extern int D_006332E0;
extern int D_006332E4;
extern char D_006332E8;
extern char D_006332E9;
extern char D_006332EA;
extern char D_006332F0;
extern char D_006332F1;
extern char D_006332F2;
extern unsigned char D_006332F8;
extern unsigned char D_006332F9;
extern unsigned char D_006332FA;
extern unsigned char D_00633300;
extern unsigned char D_00633301;
extern unsigned char D_00633308;
extern char D_00633309;
extern unsigned short D_0063330A;
extern int D_0063330C;
extern int D_00633310;
extern int D_00633314;
extern int D_00633318;
extern float D_0063331C;
extern int D_00633320;
extern int D_00633324;
extern const char D_00633328[8];
extern const char D_00633330[];
extern const char D_00633338[8];
extern const char D_00633340[8];
extern const char D_00633348[8];
extern const char D_00633350[];
extern const char D_00633358[];
extern const char D_00633360[];
extern const char D_00633368[8];
extern const char D_00633370[];
extern const char D_00633378[8];
extern const char D_00633380[8];
extern const char D_00633388[8];
extern int D_00633390;
extern unsigned int D_00633394;
extern short D_00633398;
extern short D_0063339A;
extern int D_0063339C;
extern unsigned int D_006333A0;
extern int D_006333A4;
extern int D_006333A8;
extern int D_006333AC;
extern char D_006333B0[8];
extern const char D_006333B8[8];
extern char D_006333C0[8];

unsigned char D_00275850[16] = { 0 };

const char D_00618930[24] = "src/clothAnimation.c";

const char D_00618970[16] = "FADE OUT RND";

const char D_00618980[16] = "FADE OUT";

const char D_00618990[16] = "FADE BASE RND";

const char D_006189A0[16] = "FADE BASE";

const char D_006189B0[16] = "BIRTH RATE";

const char D_006189C0[16] = "LIFE SPAN RND";

const char D_006189D0[16] = "LIFE SPAN";

const char D_006189E0[16] = "NB POLYGONS";

const char D_006189F0[16] = "SIZE GROW ACC";

const char D_00618A00[16] = "SIZE GROW RND";

const char D_00618A10[16] = "SIZE GROW";

const char D_00618A20[16] = "SIZE BASE RND";

const char D_00618A30[16] = "SIZE BASE";

const char D_00618A40[16] = "ROT GROW ACC";

const char D_00618A50[16] = "ROT GROW RND";

const char D_00618A60[16] = "ROT GROW";

const char D_00618A70[16] = "ROT BASE RND";

const char D_00618A80[16] = "ROT BASE";

const char D_00618A90[16] = "GRAVITY ACC";

const char D_00618AA0[16] = "VEL ACCEL    ";

const char D_00618AB0[16] = "VEL RND RATIO";

const char D_00618AC0[16] = "VELOCITY";

const char D_00618AD0[16] = "WIND EFFECT";

const char D_00618AE0[16] = "CONE ANGLE";

const char D_00618AF0[16] = "ALPHA TYPE";

const char D_00618B00[16] = "DRAIN TYPE";

const char D_00618B10[16] = "V OFFSET";

const char D_00618B20[16] = "U OFFSET";

const char D_00618B30[24] = "Unknown Data Type \"%s\"\n";

const char D_00618B48[24] = "%-20s:%s";

const float D_00618B60[4] = { 0.0f, 0.0f, 1e+02f, 1.0f };

const char D_00618B70[16] = "POS-X:%4.3f";

const char D_00618B80[16] = "POS-Y:%4.3f";

const char D_00618B90[16] = "POS-Z:%4.3f";

const char D_00618BA0[16] = "ROT-Y:%4.3f";

const char D_00618BB0[16] = "ROT-X:%4.3f";

const char D_00618BC0[16] = "initialize\n";

const char D_00618BD0[64] = "==== Save effect ============================================\n";

const char D_00618C10[40] = "saveEffectData: host file open error.\n";

const char D_00618C68[16] = "%d bytes wrote\n";

const char D_00618C78[64] = "=============================================================\n";

unsigned int D_00632010 = 0x00000000;

unsigned int D_00632018 = 0x00000000;

unsigned int D_0063201C = 0x00000000;

unsigned int D_00632020 = 0x00000000;

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C3988);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C3E08);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C4150);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C42F0);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C48F8);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C4A28);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C55F0);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C58C0);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C5BA0);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C5FD0);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C6090);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C62D0);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C63C8);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C6998);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C6DF0);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C7FB0);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C8218);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C8478);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", func_001C8958);

void func_001C8A00(int a0, int a1, float f)
{
    *(float *)(a0 + a1 * 0x50 + 0x10) = f;
}

/* ASCII debug strings — re-derived from EE rodata bytes. */
/* ASCII preview: "<ESC>[36mALLOC CLOTHES<ESC>[m<LF>" */
const char D_00618948[24] = "\033[36mALLOC CLOTHES\033[m\n";
