#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/moveColTest", MoveColTestGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/moveColTest", MoveColTestDL);

extern void func_0010F048(void *a0);

void InitMoveColTestGeo(void *a0) {
    func_0010F048(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/moveColTest", func_001E3BE8);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006126B0;  /* stride 0x4 */

/* end struct shapes */
