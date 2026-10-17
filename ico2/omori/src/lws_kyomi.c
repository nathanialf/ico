#include "sceneManager.h"
#include "memory.h"
#include "StageAnimation.h"
#include "debug.h"
#include <string.h>
#include "typedef.h"
#include "ios.h"
#include "lws_kyomi.h"
#include "main.h"
#include "geometryManager.h"
#include "brain.h"
#include "include_asm.h"

struct HintInfo { /* field names derived */
    int anim;     /* the stage animation the hint plays */
    int no;
    int time;
    int flags;
};

/* This build has no hint system here: no hint record in .bss and no save-bit
   packers (no function of the demo addresses one). */

/* (this build keeps no hint template in .data) */

INCLUDE_ASM(LwsKyomiGeo);

INCLUDE_ASM(CreateKyomiGObj);

/* This build keeps no hint-timer window in .sbss (no function of the demo
   addresses one). */

INCLUDE_ASM(SetParamKyomiGObj);
