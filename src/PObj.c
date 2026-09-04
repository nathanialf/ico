#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

extern const char D_006360D8[];
extern void debug_StdPrintfDummy();
INCLUDE_ASM("asm/nonmatchings/src/PObj", MakeBoundingBox);
INCLUDE_ASM("asm/nonmatchings/src/PObj", MakePacket);
INCLUDE_ASM("asm/nonmatchings/src/PObj", AllocPObj);
INCLUDE_ASM("asm/nonmatchings/src/PObj", InitPObj);
void FreePObj(void) {
    do {
        debug_StdPrintfDummy(D_006360D8);
    } while (0);
}
