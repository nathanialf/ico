#include "common.h"

extern int D_0062C1B4;
extern int D_0062C1B8;
extern int D_0062C1BC;

void staffRollStart(int a0, int a1, int a2, int a3) {
    D_0062C1B4 = a1;
    D_0062C1B8 = a2;
    D_0062C1BC = a3;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", staffRollScroll);

extern char D_0062B448;
extern int D_0062B44C;

void staffRollNameOut(void) {
    D_0062B448 = 0;
    D_0062B44C = -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", staffRollMain);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", staffRollWide);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", func_001B58B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", func_001B59F0);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004B8C90;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060FD90;  /* stride 0x4 */

/* end struct shapes */
