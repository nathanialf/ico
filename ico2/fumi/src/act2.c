#include "act.h"
#include "act2.h"
#include "isys.h"
#include "include_asm.h"

INCLUDE_ASM(BeforeFunc2);

void actDummy(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
}
