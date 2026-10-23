#include "StageManager.h"
#include "debug.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "sceneManager.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "jimaku.h"
#include "way_llf.h"
#include "brain.h"
#include "generator.h"
#include "camera-root.h"
#include "fightSound.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "staticBlur.h"
#include "windManager.h"
#include <libvu0.h>
#include <string.h>
#include "act.h"
#include "gobj_process.h"
#include "typedef.h"
#include "commonact.h"
#include "streamMotionManager.h"
#include "kanbanBoot.h"
#include "layout_action.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

INCLUDE_ASM(actE3WarningChk);

#include "e3.h"

/* .sdata: the title stream's handle, the capsule's, the cage fall's, the
   first gate's, then the stone statue shake's pad actuator handle and its
   volume. */
static SqEntry *e3title = 0; /* derived name */

SqEntry *e3capsule = 0;

static SqEntry *e3cage = 0; /* derived name */

SqEntry *e3gate1st = 0;

int sekizo_e3 = 0;

unsigned char sekizo_e3_vol = 0;

/* actE3Warning's mail, the first object of the TU's .data */
static ActMail warning_mes[2] = {{393}, {392}}; /* derived name */

static ActMail title_mes[2] = {{393}, {392}}; /* derived name */

static ActMail inst1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail capsule_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorMain_mes[2] = {{372, actE3DoorSwitch}, {392}}; /* derived name */

static ActMail door_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{393}, {392}}; /* derived name */

static float doorUpPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

static ActMail st13cIntro_mes[2] = {{393}, {392}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{393}, {392}}; /* derived name */

static ActMail cageFall_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st01bEne_mes[2] = {{393}, {392}}; /* derived name */

static float st09aSekizoPos[4] = {1548.0f, -412.0f, -608.0f, 0.0f}; /* derived name */

static ActMail st09aSekizo_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gate_mes[2] = {{393}, {392}}; /* derived name */

INCLUDE_ASM(actE3Title);

INCLUDE_ASM(actE3TitleChk);

INCLUDE_ASM(actE3TitleFrameChk);

INCLUDE_ASM(actE3Inst1Chk);

INCLUDE_ASM(actE3Capsule);

/* .sbss: the capsule demo's sub-thread and the flag that thread raises when
   the demo has finished. */
static GProc *capsuleDemoThread; /* derived name */

static int demoEnd;

INCLUDE_ASM(actE3CapsuleDemoCancel);

INCLUDE_ASM(actE3CapsuleDemo);

INCLUDE_ASM(actE3St13cInit);

INCLUDE_ASM(actE3CageFall);

INCLUDE_ASM(actE3CageFallChk);

INCLUDE_ASM(actE3CageFallDemo);

INCLUDE_ASM_LIT(actE3CapsuleDemoEnd);

void actE3CageFallEffect(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0:
            gflagOn(21);
            break;
        case 64:
            iosPadActRequest(boyPad, 17);
            {
                EffectArg b1 = {{-88.0f, -50.0f, -1.0f, 1.0f}};
                scpEffectStart(&b1, 0);
            }
            {
                EffectArg b2 = {{-96.0f, -45.0f, 34.0f, 1.0f}};
                scpEffectStart(&b2, 0);
            }
            break;
        case 68: {
            EffectArg b3 = {{72.0f, -50.0f, 8.0f, 1.0f}};
            scpEffectStart(&b3, 0);
        }
            {
                EffectArg b4 = {{80.0f, -50.0f, 2.0f, 1.0f}};
                scpEffectStart(&b4, 0);
            }
            break;
        case 96: {
            EffectArg b5 = {{-27.0f, -50.0f, 100.0f, 1.0f}};
            scpEffectStart(&b5, 0);
        }
            {
                EffectArg b6 = {{-56.0f, -50.0f, 66.0f, 1.0f}};
                scpEffectStart(&b6, 0);
            }
            {
                EffectArg b7 = {{-5.0f, -50.0f, 42.0f, 1.0f}};
                scpEffectStart(&b7, 0);
            }
            break;
        case 180:
            iosPadActRequest(boyPad, 15);
            break;
        case 300: {
            EffectArg b8 = {{-10.0f, 0.0f, 466.0f, 1.0f}};
            scpEffectStart(&b8, 0);
        }
            {
                EffectArg b9 = {{-25.0f, 0.0f, 450.0f, 1.0f}};
                scpEffectStart(&b9, 0);
            }
            break;
        case 380:
            iosPadActRequest(boyPad, 16);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 400.0f);
}

INCLUDE_ASM(actE3St09aSekizo);

INCLUDE_ASM_LIT(actE3St09aGirlWay);

INCLUDE_ASM(actE3St09aSekizoChk);

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

INCLUDE_ASM(actE3GateChk);

INCLUDE_ASM(actE3GateDemo);

void actE3GateJimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 300:
            jimaku_msg.sub.block = 25;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1420:
            jimaku_msg.sub.block = 26;
            jimaku_msg.sub.jump = 30;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 7300.0f);
}

INCLUDE_ASM(actE3St01bInit);

INCLUDE_ASM(actE3Warning);

INCLUDE_ASM(actE3Inst1);

INCLUDE_ASM(actE3Door);

INCLUDE_ASM(actE3CageFallReady);

INCLUDE_ASM(actE3St13cIntro);

INCLUDE_ASM(actE3St13cGene1);

INCLUDE_ASM(actE3St13cGene2);

void actE3Floor(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
}

INCLUDE_ASM(actE3St01bEne);

INCLUDE_ASM(actE3St01bGene1);

INCLUDE_ASM(actE3St01bGene2);

INCLUDE_ASM(actE3St01bGene3);

INCLUDE_ASM(actE3Gate);

INCLUDE_ASM(actE3CapsuleChk);

INCLUDE_ASM(actE3CapsuleDemoEnd);

INCLUDE_ASM(actE3DoorMain);

INCLUDE_ASM(actE3DoorSwitch);

INCLUDE_ASM(actE3DoorUp);

INCLUDE_ASM(actE3St13cIntroChk);

INCLUDE_ASM(actE3CageFallReadyChk);

INCLUDE_ASM(actE3St01bEneChk);

INCLUDE_ASM(actE3St09aGirlWay);
