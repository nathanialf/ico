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

/* declared ahead with no size for actSt22aIntroChk; the sized definition
   follows the stream handle in .sdata */
static int lightningAnims[];

/* .sdata: the lightning stream handle and the two animation numbers the
   lightning plays. */
struct SqEntry *lightning = 0;

static int lightningAnims[2] = {684, 685}; /* derived name */

void actSt22aLightningVolime(GObj *volatile self)
{
    /* the lightning's volume for height y, nested in this function */
    inline float getVolume(float y) /* derived name */
    {
        float lo = -8000.0f, hi = -1355.0f;

        if (y < lo) {
            return 0.0f;
        } else if (hi < y) {
            return 1.0f;
        }
        return (y - lo) / (hi - lo);
    }
    float *pos;
    float v;

    while (lightning == 0) {
        _ACTWait(1);
    }
    for (;;) {
        pos = GetCameraPos();
        v = getVolume(pos[2]);
        if (v < 0.1f) {
            v = 0.1f;
        }
        AdpcmVolumeSet(lightning, (int)(v * 16383.0f));
        _ACTWait(1);
    }
}

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

/* the point the boy turns to face when the intro is skipped */
static const StVec introFacePos = {{-2000.0f, 0.0f, -1129.0f, 1.0f}}; /* derived name */

/* no header declares it; gamesys.c defines it */
void actSt22aIntroChk(GObj *volatile self);

void actSt22aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    StVec pos;
    float dir[4];

    _ACTWait(1);
    lightning = 0;
    scpAdpcmPlayRequestFunc(92, &lightning, 1, 0, 1);
    actCreateSubThread(actSt22aLightningVolime, 21);
    ScpCallCameraSetTarget(7000.0f, 280.0f, 4938.0f);
    SetCageChainHangableFlag(scpSearchGobj(1704), 0);
    SetCageChainHangableFlag(scpSearchGobj(1705), 0);
    SetCageChainHangableFlag(scpSearchGobj(1706), 0);
    SetCageChainHangableFlag(scpSearchGobj(1707), 0);
    SetCageChainHangableFlag(scpSearchGobj(1708), 0);
    SetCageChainHangableFlag(scpSearchGobj(1709), 0);
    SetCageChainHangableFlag(scpSearchGobj(1710), 0);
    SetCageChainHangableFlag(scpSearchGobj(1711), 0);
    SetCageChainHangableFlag(scpSearchGobj(1712), 0);
    if (gflagChk(295) != 0) {
        return;
    }
    scpPlayPosSet(boyGObj, -808.0f, 148.0f, -1053.0f);
    if (gflagChk(294) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        gamesysNObjInfoInit();
        intro_mes[0].func = actSt22aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        gflagOn(295);
        pos = introFacePos;
        sceVu0SubVector(dir, &pos, test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, dir);
        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
    }
}

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

typedef struct St22Anims { /* field names derived */
    int id[2];
} St22Anims; /* derived name */

INCLUDE_ASM(actSt22aIntroChk);

INCLUDE_ASM(actSt22aIntroSub);
