#include "common.h"

#include "vu0.h"
#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableSin);
INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableCos);
INCLUDE_ASM("asm/nonmatchings/src/tableSin", InitTableSin);
INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcSin);
INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcCos);
extern short GetTableArcCos(float c);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcTan2);
