#include "st22a.h"
#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "cage.h"
#include <libvu0.h>
#include "st04c.h"
#include "typedef.h"
#include "gamesys.h"
#include "main.h"
#include "include_asm.h"

/* No .sdata: this build's functions here address no stream handle and no
   animation-number pair (their only data references are the mail tables). */

INCLUDE_ASM(actSt22aLightningVolime);

static ActMail intro_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st22a_mes020[2] = {{377}, {376}}; /* derived name */

static ActMail st22a_mes040[2] = {{377}, {376}}; /* derived name */

static ActMail st22a_mes060[2] = {{377}, {376}}; /* derived name */

/* the point the boy turns to face when the intro is skipped */
static const StVec introFacePos = {{-2000.0f, 0.0f, -1129.0f, 1.0f}}; /* derived name */

/* no header declares it; gamesys.c defines it */
void actSt22aIntroChk(GObj *volatile self);

INCLUDE_ASM(actSt22aIntro);

/* No .sbss here in this build: no function of the demo addresses such a flag. */

typedef struct St22Anims { /* field names derived */
    int id[2];
} St22Anims; /* derived name */

INCLUDE_ASM(actSt22aIntroChk);

INCLUDE_ASM(actSt22aIntroSub);
