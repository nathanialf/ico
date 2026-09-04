#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", debug_TargetGObj);
extern int D_0063C388;
extern int D_0063C38C;
extern int D_0063C390;

void init_debug_menu(void) {
    D_0063C388 = 0;
    D_0063C38C = 1;
    D_0063C390 = 0;
}
extern int D_002C1270[];
extern int GetGObjP();

INCLUDE_ASM("asm/nonmatchings/src/debug_menu", debug_TargetGObj_Func);
