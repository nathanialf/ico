#include "common.h"
#include "st22a.h"
#include "layout_texture.h"
#include "thread.h"
#include "act.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "cage.h"
#include <libvu0.h>
#include "st04c.h"

/* The TU starts at 0x00252418, where MAIN.MAP puts st22a.o. */
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st22a", actSt22aLightningVolime);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st22a", actSt22aIntro);

extern int D_00639EA4;

/* .sbss, owned by st22a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

extern StVec D_00623090;
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
