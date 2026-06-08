#include "common.h"

/* rotObject 0x7F0 view (local) */
typedef struct { char _0[0x24]; int f_24; } RotGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", moveStartSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", moveEndSE);

extern void func_001E6B78(int a0);

void RotObjectGeo(int a0) {
    func_001E6B78(a0);
}

extern void func_001E6B80(void);

void getRootMatrix(void) {
    func_001E6B80();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", RotObjectDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", GetRotObjectHoldPoint);

float MoveRotObjectWithHoldPoint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    RotGeo *q = *(RotGeo **)((char *)p + 0x7F0);
    return (float)q->f_24 * (1.0f / 65536.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rotObject", ExecRotObjectMoveStartReaction);

int ExecRotObjectMoveEndReaction(void) {
    return 1;
}
