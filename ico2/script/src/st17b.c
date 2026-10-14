#include "st17b.h"
#include "act.h"
#include "commonact.h"
#include "gflag.h"
#include "StageManager.h"
#include "script.h"
#include "typedef.h"
#include "include_asm.h"

static ActMail check_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: the lightning stream handle. */
struct SqEntry *lightning2 = 0;

void actSt17bTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
}

INCLUDE_ASM(actSt17bCheck);

INCLUDE_ASM(func_00235AF0);

INCLUDE_ASM(actSt17bCheckChk);

INCLUDE_ASM(func_00235B98);
