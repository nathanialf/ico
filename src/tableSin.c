#include "common.h"

#include "vu0.h"
#include "ico/types.h"

extern float D_00669A40[];

float GetTableSin(short a0) {
    int idx = __builtin_abs(a0);
    int s;
    float v;
    s = (unsigned int) a0 >> 0x1F;
    if (idx >= 0x4000) {
        idx = 0x8000 - idx;
    }
    v = D_00669A40[idx];
    if (s == 0) goto done;
    v = -v;
done:
    return v;
}
INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableCos);
INCLUDE_ASM("asm/nonmatchings/src/tableSin", InitTableSin);
INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcSin);
INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcCos);
extern short GetTableArcCos(float c);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcTan2);
