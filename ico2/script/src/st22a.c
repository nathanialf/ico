#include "common.h"
#include "st22a.h"
#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "act.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "cage.h"
#include <libvu0.h>
#include "st04c.h"
#include "typedef.h"

/* The TU starts at 0x00252418, where MAIN.MAP puts st22a.o. */
extern int D_0063C048;

void actSt22aLightningVolime(volatile int a0)
{
    /* Listing rows 123-127 sit above the loop's own rows and run inside it:
       an inline helper nested in this function. */
    inline float getVolume(float y)
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

    while (D_0063C048 == 0) {
        _ACTWait(1);
    }
    for (;;) {
        pos = GetCameraPos();
        v = getVolume(pos[2]);
        if (v < 0.1f) {
            v = 0.1f;
        }
        AdpcmVolumeSet(D_0063C048, (int)(v * 16383.0f));
        _ACTWait(1);
    }
}

extern int D_00639EA4;

static ActMail intro_mes[2] = {{430}, {429}};

extern StVec D_00623090;
/* no header declares it; gamesys.c defines it */
extern void gamesysNObjInfoInit(void);
void actSt22aIntroChk(volatile int a0);

void actSt22aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    StVec pos;
    float dir[4];

    _ACTWait(1);
    D_0063C048 = 0;
    scpAdpcmPlayRequestFunc(94, &D_0063C048, 1, 0, 1);
    actCreateSubThread(actSt22aLightningVolime, 21);
    ScpCallCameraSetTarget(7000.0f, 280.0f, 4938.0f);
    SetCageChainHangableFlag(scpSearchGobj(1847), 0);
    SetCageChainHangableFlag(scpSearchGobj(1848), 0);
    SetCageChainHangableFlag(scpSearchGobj(1849), 0);
    SetCageChainHangableFlag(scpSearchGobj(1850), 0);
    SetCageChainHangableFlag(scpSearchGobj(1851), 0);
    SetCageChainHangableFlag(scpSearchGobj(1852), 0);
    SetCageChainHangableFlag(scpSearchGobj(1853), 0);
    SetCageChainHangableFlag(scpSearchGobj(1854), 0);
    SetCageChainHangableFlag(scpSearchGobj(1855), 0);
    if (gflagChk(324) != 0) {
        return;
    }
    scpPlayPosSet(D_00639EA4, -808.0f, 148.0f, -1053.0f);
    if (gflagChk(323) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        gamesysNObjInfoInit();
        intro_mes[0].func = actSt22aIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        gflagOn(324);
        pos = D_00623090;
        sceVu0SubVector(dir, &pos, test_CURRENTROOT(D_00639EA4));
        scpPlayMotDir(D_00639EA4, dir);
        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
    }
}

/* .sbss, owned by st22a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

extern int D_0063AA08;
extern int D_0028F4C0[];
extern int D_0028F8F4[];

typedef struct St22Anims {
    int id[2];
} St22Anims;

extern int D_0063C050[];

void actSt22aIntroChk(volatile int a0)
{
    St22Anims anims;
    StVec pos;
    float dir[4];
    int th;
    int fin;
    unsigned int i;

    gflagOn(323);
    scpSekizouCheckPoint();
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    gflagOn(324);
    stage_SetAnimation(758, 1, 0);
    _ACTWait((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 10);
    scpFadeIn(6.0f);
    th = actCreateSubThread(actSt22aIntroSub, 21);
    demoEnd = 0;
    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    fin = demoEnd ^ 1;
    if (fin != 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    iosThreadSetPri(th + 0x24, 34);
    if (fin != 0) {
        anims = *(St22Anims *)D_0063C050;
        for (i = 0; i < 2; i++) {
            stage_SetAnimation(anims.id[i], 1, -1);
            _ACTWait(1);
        }
        stage_SetAnimation(759, 1, -1);
        StabilizeAllLayoutedCage();
        scpPlayPosSet(D_00639EA4, -808.0f, 148.0f, -1053.0f);
        pos = D_00623090;
        sceVu0SubVector(dir, &pos, test_CURRENTROOT(D_00639EA4));
        scpPlayMotDir(D_00639EA4, dir);
        scpPlayMot(D_00639EA4, 0);
        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(6.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    } else {
        scpPlayMot(D_00639EA4, 0);
    }
    scpPlayEnd(D_00639EA4);
    lt_switch_layout(54);
    D_0063AA08 = 0;
}

void actSt22aIntroSub(volatile int a0)
{
    StVec pos;
    float dir[4];

    stage_SetAnimation(758, 1, 0);
    scpPlayMot(D_00639EA4, 397);
    while (stage_ContinueAnimation(758, 759) == 0) {
        _ACTWait(1);
    }
    scpPlayPosSet(D_00639EA4, -707.0f, 148.0f, -1112.0f);
    pos = D_00623090;
    sceVu0SubVector(dir, &pos, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    scpPlayMot(D_00639EA4, 398);
    while (stage_CheckAnimationFinish(759) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}
