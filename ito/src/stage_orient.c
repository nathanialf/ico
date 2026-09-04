#include "common.h"

extern void *D_0062C0E8;
extern void RotateThreadReadyQueue(void *a0);

void GetStageDifferenceMatrix(void) {
    RotateThreadReadyQueue(D_0062C0E8);
}

extern void func_0023A410(void *a0);
extern int D_006D5F98[];

void StageOrientGet2(void) {
    func_0023A410(D_006D5F98);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", OtherStagePositionGet);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", StageOrientInit);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", StageOrientGet);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", func_0019AC48);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", func_0019AE20);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_C0;  /* 0xC0 */
    unsigned int       f_C4;  /* 0xC4 */
} S_006D5ED0;

/* end struct shapes */
