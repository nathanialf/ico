#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", SugiLeafGeo2);
INCLUDE_ASM("asm/nonmatchings/src/sugiTree", SugiLeafDL2);
extern const char D_00621328[];
extern int D_0063A438;
extern short *iosMallocDebug(int handle, int size, void *file, int line);
extern int rand(void);

short *InitSugiLeafGeo(void) {
    short *h = iosMallocDebug(D_0063A438, 2, (void *)D_00621328, 0xC);
    int r = rand();
    *h = r % 0x10000;
    return h;
}
INCLUDE_ASM("asm/nonmatchings/src/sugiTree", SugiLeafGeo);
INCLUDE_ASM("asm/nonmatchings/src/sugiTree", InitSugiLeafGeo2);
