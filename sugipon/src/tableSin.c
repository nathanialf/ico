#include "common.h"

extern int D_00629E7C;
extern int D_0065A5B0[];

void *GetTableSin(void) {
    return &D_0065A5B0[D_00629E7C * 4];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", GetTableCos);

extern unsigned char D_0054E1F8[];
extern void debug_assertMessage(unsigned char *a0);

void InitTableSin(void) {
    if (--D_00629E7C < 0) {
        debug_assertMessage(D_0054E1F8);
        D_00629E7C = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", GetTableArcSin);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", GetTableArcCos);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", GetTableArcTan2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E088);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E0E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E148);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E188);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E250);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E300);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E348);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E448);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E4E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E588);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/tableSin", func_0010E628);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054E220;  /* stride 0x4 */

/* end struct shapes */
