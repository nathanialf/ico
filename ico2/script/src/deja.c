#include "deja.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "act.h"
#include "commonact.h"
#include "fightSound.h"
#include "gflag.h"
#include "script.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

/* actDeja installs actDejaChk as the actor's next mail handler. */

static ActMail _mes[2] = {{393}, {392}}; /* derived name */

static ActMail after_mes[2] = {{393}, {392}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the handler the wait loop below
   is spinning for. */
static int demoEnd;

void actDejaDemo(GObj *volatile self);
void actDejaAfterChk(GObj *volatile self);

/* .sdata: the scene's stream handle */
struct SqEntry *deja = 0;

static const Vec16 afterChkPos = {{-1000.0f, 0.0f, -2200.0f, 1.0f}}; /* derived name */

inline void actEnemySleep(GObj *volatile self)
{
    while (1) {
        scpSleepEnemyAll();
        _ACTWait(1);
    }
}

INCLUDE_ASM(actDejaChk);

INCLUDE_ASM(actDejaDemo);

INCLUDE_ASM(actDejaAfter);

INCLUDE_ASM(actDejaAfterChk);

INCLUDE_ASM(actDeja);
