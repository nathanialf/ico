#include "common.h"

extern void func_0010F9D0(void);

void before_DrawPolygon(void) {
    func_0010F9D0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", after_DrawPolygon);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", _IsInScreen2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", before_DrawLine);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", after_DrawLine);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", DrawPolygon);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", do_DrawLine);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", IsPointIsInScreen);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", func_001945F8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", func_001946F8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", func_001947F8);
