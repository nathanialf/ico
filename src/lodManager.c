/* src/lodManager.c — __FILE__ anchor at .rodata 0x00619060 */

#include "include_asm.h"

__attribute__((section(".rodata.0x00619060"))) const char D_00619060[32] = "src/lodManager.c";

__attribute__((section(".rodata.0x006191D0"))) const char D_006191D0[32] = "Emphasys Accel   Velocity";
__attribute__((section(".rodata.0x006191F0"))) const char D_006191F0[16] = "         %1.5f ";
__attribute__((section(".rodata.0x00619200"))) const char D_00619200[32] = "                 %1.5f";

/* String rodata migrated from lodManager_data.c */
__attribute__((section(".rodata.0x00619080"))) const char D_00619080[32] = "Invalid node formatID: (%d)\n";

/* Float rodata migrated from lodManager_data.c */
__attribute__((section(".rodata.0x00619220"))) const float D_00619220[48] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5e+01f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "%s: "[36m%s[m"のLODが"[36m%s[m"に設定されました
" */
__attribute__((section(".rodata.0x00619028"))) const char D_00619028[56] = "%s: \"\033[36m%s\033[m\"\244\316LOD\244\254\"\033[36m%s\033[m\"\244\313\300\337\304\352\244\265\244\354\244\336\244\267\244\277\n";
/* EUC-JP: "このMOBファイルは壊れているか、バージョンが古いです。
" */
__attribute__((section(".rodata.0x006190A0"))) const char D_006190A0[64] = "\244\263\244\316MOB\245\325\245\241\245\244\245\353\244\317\262\365\244\354\244\306\244\244\244\353\244\253\241\242\245\320\241\274\245\270\245\347\245\363\244\254\270\305\244\244\244\307\244\271\241\243\n";

extern int D_00633F18;
extern int D_00633F1C;

INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4358);
INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D43F8);
INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D45B0);
INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D49C0);
INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4A58);
INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4B40);
INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4BD0);
INCLUDE_ASM("asm/nonmatchings/src/lodManager", func_001D4CC8);

void func_001D4D98(void) {
    D_00633F18 = 0;
    D_00633F1C = 0;
}
