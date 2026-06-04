#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", debug_TargetGObj);

extern int D_0062AF3C;

void init_debug_menu(void) {
    D_0062AF3C = 0;
}

void debug_TargetGObj_Func(int a0) {
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7350);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7420);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7480);

extern int D_0062ACFC;

void func_001A74B8(int a0) {
    D_0062ACFC = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A74C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7578);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7630);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7658);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7700);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A77A8);

void func_001A77F0(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A77F8);

int func_001A7A80(void) {
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7A88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7AE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7B18);

void func_001A7B50(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7B58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7BA0);

extern int D_006F26D0[];

void func_001A7BD0(int a0, int a1) {
    *(int *)((char *)D_006F26D0 + a1 * 8 + a0 * 0xD0) = 0;
}

extern char D_00271270[];
extern void gsb_antiAlias(void *a0);

int func_001A7BF8(void) {
    gsb_antiAlias(D_00271270);
    return 1;
}

extern int D_0062ACB0;

int func_001A7C20(void) {
    D_0062ACB0 = *(volatile int *)0x10000000;
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7C38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7CE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A7F90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A8238);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_menu", func_001A8320);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_006F26D0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_004AE440;  /* stride 0xC */

/* end struct shapes */
