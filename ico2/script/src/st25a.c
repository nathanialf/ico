#include "st25a.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "queen.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "boy.h"
#include "geometryManager.h"
#include "motionManager2.h"
#include "streamMotionManager.h"
#include <libvu0.h>
#include <string.h>
#include "e3.h"
#include "typedef.h"
#include "layout_action.h"
#include "main.h"
#include "script.h"
#include "jimaku.h"
#include "include_asm.h"

static void actSt25aElevCharaChk(GObj *volatile self);

/* .sdata: the ADPCM request slots the scenes hand scpAdpcmPlayRequestFunc
   and wait on, and conte12's flag. */
static SqEntry *conte11 = 0; /* derived name */

SqEntry *conte12 = 0;

SqEntry *sd2 = 0;

static int conte12Flag = 0; /* derived name */

SqEntry *dead = 0;

/* five words in this build: the demo's .sdata of the TU has no room for PAL's
   two elevator slots (elevAgain, elevFirst) */

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* this file's own view of Vec4 (the shared one is in typedef.h) */
typedef union Vec4St25A { /* derived name */ /* field names derived */
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) Vec4St25A; /* derived name */

typedef struct AnimSet18 { /* field names derived */
    int anim[18];          /* 0x00 */
} AnimSet18;               /* derived name */

/* the two face-shadow textures ConteQueenDead scrolls the UVs of. */
const char faceShadowTex[] = "face_sadow_sd"; /* script.c scrolls it too */

const char faceShadowTex00[] = "face_sadow_sd_00";

/* The offset the sekika boy is dropped by. */
static const Vec4St25A sekikaOfs = {{2000.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

static const char streamWaitFmt[] =
    "Now waiting for standby stream motion system... %d\n"; /* derived name */

static const char queenBallScrTexture[] = "queen_ball_scr"; /* derived name */

static const char sekikaBoyTexture[] = "sekika_boy"; /* derived name */

/* .data: eight actor mail records.  Each is
   the usual pair, the 377 entry whose handler the sender fills in and the 376
   terminator (this build's mail numbers).  queen_appear_mes is the only one
   another TU sends (script.c's scpObj1882), so it is the only global of the
   eight; the two elevator records are actSt25aObj1881's and
   actSt25aElevChk's. */
ActMail queen_appear_mes[2] = {{377}, {376}};

static ActMail queen_before_mes[2] = {{377}, {376}}; /* derived name */

static ActMail queen_talk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elev_up_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elev_chara_mes[2] = {{377}, {376}}; /* derived name */

static ActMail queen_dead_mes[2] = {{377}, {376}}; /* derived name */

static ActMail queen_dead_ready_mes[2] = {{377}, {376}}; /* derived name */

static ActMail queen_attack_mes[2] = {{377}, {376}}; /* derived name */

void actSt25aQueenBeforeChk(GObj *volatile self);
static void actSt25aQueenDeadReadyChk(GObj *volatile self);
void actItouQueenAttackChk(GObj *volatile self);
void actConte11(GObj *volatile self);
void actConte11Jimaku(GObj *volatile self);

INCLUDE_ASM(actSt25aQueenAppear);

INCLUDE_ASM(actSt25aQueenAppearChk);

INCLUDE_ASM(actConte11);

INCLUDE_ASM(func_00175498);

INCLUDE_ASM(actSt25aObj1881);

INCLUDE_ASM(func_001758A8);

/* actSt25aQueenTalkChk's work area: the stage animations the cancelled
   ending restores, or the boy's position and the direction vectors the
   scene's motions are played along */
typedef union TalkWork { /* derived name */ /* field names derived */
    AnimSet18 a;
    Vec4St25A v[3];
} TalkWork; /* derived name */

/* No .sbss: this build's functions here keep no end or event flag (no
   function of the demo addresses one). */

void actSt25aQueenTalkChk(GObj *volatile self);

INCLUDE_ASM(actSt25aQueenDeadChk);

void actConte13Jimaku(GObj *volatile self)
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
        case 600:
            jimaku_msg.sub.block = 110;
            jimaku_msg.sub.jump = 400;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1320:
            jimaku_msg.sub.block = 111;
            jimaku_msg.sub.jump = 200;
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
    } while (t < 3100.0f);
}

void BoySekikaTexScroll(void)
{
    tex_SetUVScroll(sekikaBoyTexture, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.5f, 1);
}

INCLUDE_ASM(actSt25aElevChk);

void actSt25aGenerator(GObj *volatile self)
{
    Generator_Mask(self);
}

INCLUDE_ASM(actSt25aQueenBefore);

INCLUDE_ASM(actSt25aQueenTalk);

INCLUDE_ASM(actSt25aQueenDeadReady);

INCLUDE_ASM(actSt25aQueenDead);

INCLUDE_ASM(actItouQueenAttack);

INCLUDE_ASM(actSt25aElev);

INCLUDE_ASM(actSwordEff);

INCLUDE_ASM(actSwordEffXL);

INCLUDE_ASM(actSt25aQueenBeforeChk);

void actConte11Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            break;
        case 10:
            jimaku_msg.sub.block = 93;
            jimaku_msg.sub.jump = -1;
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
    } while (t < 1500.0f);
}

INCLUDE_ASM(func_00176A38);

INCLUDE_ASM(func_00176AD8);

INCLUDE_ASM(func_00176BE0);

void actSt25aQueenDeadEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actItouQueenAttackChk);
