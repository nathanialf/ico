#include "common.h"
#include "st08a.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "typedef.h"

/* kept local: this TU's bytes only come out with its own view of PObjGObj, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct PObjGObjSt08A {
    char pad00[0x15C]; /* 0x000 */
    char *f15C;        /* 0x15C */
    char pad160[0x4];  /* 0x160 */
    Act *act;          /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObjSt08A;

static ActMail ene1_mes[2] = {{430}, {429}};

static ActMail ene2_mes[2] = {{430}, {429}};

static ActMail door_main_mes[2] = {{407, actSt08aDoorSwitch}, {429}};

static ActMail door_mes[2] = {{430}, {429}};

static ActMail door_switch_mes[2] = {{430}, {429}};

static float door_up_sound_pos[4] = {-3092.0f, -2727.0f, 3711.0f, 0.0f};

static ActMail intro_mes[2] = {{430}, {429}};

static ActMail girl_pos_mes[2] = {{430}, {429}};

static ActMail hint1_mes[2] = {{430}, {429}};

static ActMail hasi_main_mes[2] = {{408, actSt08aHasiSwitch}, {429}};

static ActMail hasi_mes[2] = {{430}, {429}};

static ActMail hasi_switch_mes[2] = {{430}, {429}};

static ActMail torch_mes[2] = {{430}, {429}};

static ActMail torch_on_mes[2] = {{430}, {429}};

static ActMail torch_off_mes[2] = {{430}, {429}};

extern int D_0063AA08;
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, void *a1, float radius);
extern void *D_00639EA4;
extern void *D_00639EA8;
extern int D_0063C568;
extern int D_0063C564;
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObjSt08A *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpSetCageVelocityFriction do not fit the prototype in script.h */
extern void scpSetCageVelocityFriction(int id, float f);

void actSt08aEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(0x49) == 0) {
            gflagOn(0x187);
        }
    }
}

/* kept local: this TU's uses of scpSleepEnemyOne do not fit the prototype in script.h */
extern void scpSleepEnemyOne(int id);
/* kept local: this TU's uses of scpWakeupEnemyOne do not fit the prototype in script.h */
extern void scpWakeupEnemyOne(int id);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(void *o, int mot);

void actSt08aEne1Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x47) == 0 || (scpTriggerFloorAttr(D_00639EA4, 0x6000000) == 0 &&
                                   scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0)) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyOne(0xEAD);
    gflagOn(0x48);
    gflagOn(0x4A);
    stage_SetAnimation(0x67, 1, 0);

    if (scpTriggerFloorAttr(D_00639EA4, 0x6000000) == 0 &&
        scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        SetCameraFlag_LwsCutBack();
    }

    while (stage_CheckAnimationFinish(0x67) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    scpWakeupEnemyOne(0xEAD);
}

extern int D_0063A538;
/* kept local: this TU's uses of scpKillEnemyOne do not fit the prototype in script.h */
extern void scpKillEnemyOne(int a0);
/* kept local: this TU's uses of scpKillSpiderGroup do not fit the prototype in script.h */
extern void scpKillSpiderGroup(int a0);

void actSt08aEne2Chk(volatile int a0)
{
    int save;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x48) == 0 || scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyOne(0xEAD);
    gflagOff(0x187);
    gflagOn(0x49);
    gflagOn(0x4B);
    _ACTWait(0x3C);

    save = D_0063A538;
    D_0063A538 = 0;

    scpKillEnemyOne(0x14E);
    scpKillEnemyOne(0x14F);
    scpKillEnemyOne(0x150);
    scpKillSpiderGroup(0x151);
    Generator_Delete(scpSearchGobj(0x152));
    Generator_Delete(scpSearchGobj(0x153));

    stage_SetAnimation(0x68, 1, 0);

    if (scpTriggerFloorAttr(D_00639EA4, 0x5000000) == 0) {
        SetCameraFlag_LwsCutBack();
    }

    while (stage_CheckAnimationFinish(0x68) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063A538 = save;
    scpPlayMot(D_00639EA4, 0);
    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyOne(0xEAD);
}

extern int D_0028F8F4[];
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float t);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);

void actSt08aDoorUp(volatile int a0)
{
    int th;

    lt_switch_layout(0x37);
    gflagOn(0x47);
    scpSleepEnemyAll();

    th = actCreateSubThread(actSt08aDoorUpSub, 0x15);
    D_0063C564 = 0;
    D_0063C568 = 0;

    while (D_0063C564 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C564 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x69, 0, -1);
        scpFadeIn(3.0f);
        if (D_0063C568 == 0) {
            soundSeDefPlay(0x4C6, 0, 0, 1);
        }
    }

    SetWayGroupActive(0xB, 1);
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

extern int *D_0063BF7C;
extern int D_00639EAC;

void actSt08aHasiUpSub(volatile int a0)
{
    _ACTWait(0x3C);

    while (D_0063BF7C == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x6A, 1, 0);

    while (stage_CheckAnimationFrame(0x6A, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    AdpcmPlay(D_0063BF7C[0x2C / 4]);

    while (stage_CheckAnimationFrame(0x6A, 0xB4, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFinish(0x6A) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C564 = 1;
    _ACTWait(0);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int kind, int *id, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern int scpAdpcmFadeCloseFunc(int *h, int fade);

void actSt08aHasiUp(volatile int a0)
{
    int th;

    lt_switch_layout(0x37);
    gflagOn(0x4F);
    SetWayGroupActive(0x1E, 1);
    scpSleepEnemyAll();

    D_0063C564 = 0;
    scpAdpcmPlayRequestFunc(0x62, (int *)&D_0063BF7C, 1, 1, 0);

    th = actCreateSubThread(actSt08aHasiUpSub, 0x15);

    while (D_0063C564 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C564 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (D_0063BF7C == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc((int *)&D_0063BF7C, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x6A, 0, -1);
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    scpSearchGobj(0x171)->f16C = 0;
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(void *a0, int attr);

void actSt08aTorchOnChk(volatile int a0)
{
    Act *self = ((PObjGObjSt08A *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) != 0 ||
           scpTriggerFloorAttr(D_00639EA4, 0x7000000) != 0 ||
           scpTriggerFloorAttr(D_00639EA4, 0xA000000) != 0) {
        _ACTWait(1);
    }

    ((unsigned int *)scpSearchGobj(0x15E))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x15F))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x160))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x161))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x162))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x163))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x164))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x165))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x166))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x167))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(0x15C))[0x50 / 4] = 0xFFFFFFFF;

    torch_on_mes[0].func = actSt08aTorchOffChk;
    self->mail = torch_on_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08aTorchOffChk(volatile int a0)
{
    Act *self = ((PObjGObjSt08A *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) == 0 &&
           scpTriggerFloorAttr(D_00639EA4, 0x7000000) == 0 &&
           scpTriggerFloorAttr(D_00639EA4, 0xA000000) == 0) {
        _ACTWait(1);
    }

    ((int *)scpSearchGobj(0x15E))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x15F))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x160))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x161))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x162))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x163))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x164))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x165))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x166))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x167))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(0x15C))[0x50 / 4] = 0;

    torch_off_mes[0].func = actSt08aTorchOnChk;
    self->mail = torch_off_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x47) == 0) {
        stage_SetAnimation(0x69, 0, 0);
        door_mes[0].func = actSt08aDoorMain;
        self->mail = door_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0xB, 1);
        stage_SetAnimation(0x69, 0, -1);
    }
}

void actSt08aEne1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    shadow_SetLength(scpSearchGobj(0x16E)->f15C, 100.0f);
    shadow_SetLength(scpSearchGobj(0x16F)->f15C, 100.0f);
    shadow_SetLength(scpSearchGobj(0x170)->f15C, 100.0f);

    if (gflagChk(0x48) == 0) {
        ene1_mes[0].func = actSt08aEne1Chk;
        self->mail = ene1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08aEne2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x49) == 0) {
        ene2_mes[0].func = actSt08aEne2Chk;
        self->mail = ene2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08aEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x4A) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x74);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt08aEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x4A) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x64);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt08aEnemy3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x4B) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt08aEnemy4(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x4B) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt08aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x4C) == 0) {
        intro_mes[0].func = actSt08aIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08aHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x4D) == 0) {
        hint1_mes[0].func = actSt08aHint1Chk;
        self->mail = hint1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(2);
    }
}

void actSt08aGirlPos(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x4E) == 0) {
        SleepHint(2);
        girl_pos_mes[0].func = actSt08aGirlPosChk;
        self->mail = girl_pos_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08aHasi(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x4F) == 0) {
        stage_SetAnimation(0x6A, 0, 0);
        hasi_mes[0].func = actSt08aHasiMain;
        self->mail = hasi_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x6A, 0, -1);
        scpSearchGobj(0x171)->f16C = 0;
        SetWayGroupActive(0x1E, 1);
    }
}

void actSt08aTorch(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    torch_mes[0].func = actSt08aTorchOffChk;
    self->mail = torch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08aInit(void)
{
    float f = 0.95f;

    scpSetCageVelocityFriction(0x16D, f);
    scpSetCageVelocityFriction(0x16C, f);

    if (gflagChk(0x50) != 0) {
        stage_SetAnimation(0x172, 0, 0x1FE);
        scpSearchGobj(0x16D)->f16C = 0;
    } else {
        stage_SetAnimation(0x172, 0, 0);
        scpSearchGobj(0x16C)->f16C = 0;
    }
}

void actSt08aDoorMain(volatile int a0)
{
    int sub = *(int *)(a0 + 0x164);

    D_0063AA08 = 0;

    *(int *)(sub + 0xD0) = (int)door_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt08aDoorSwitch(volatile int a0)
{
    Act *sub = ((PObjGObjSt08A *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    door_switch_mes[0].func = actSt08aDoorUp;
    sub->mail = door_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08aDoorUpSub(volatile int a0)
{
    _ACTWait(0x3C);

    stage_SetAnimation(0x69, 1, 0);

    soundSeDefPlay(0x4C5, 0, door_up_sound_pos, 1);
    _ACTWait(0x1E);
    D_0063C568 = 1;
    soundSeDefPlay(0x4C6, 0, door_up_sound_pos, 1);

    while (stage_CheckAnimationFinish(0x69) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C564 = 1;
    _ACTWait(0);
}

void actSt08aIntroChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    gflagOn(0x4C);

    stage_SetAnimation(0x87, 1, 0);
    while (stage_CheckAnimationFinish(0x87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

void actSt08aGirlPosChk(volatile int a0)
{
    while (D_00639EA8 == 0 || scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x4E);
    WakeupHint(2);
}

void actSt08aHint1Chk(volatile int a0)
{
    while (gflagChk(0x50) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");

    gflagOn(0x4D);
    FinishHint(2);
}

void actSt08aHasiMain(volatile int a0)
{
    int sub = *(int *)(a0 + 0x164);

    D_0063AA08 = 0;

    *(int *)(sub + 0xD0) = (int)hasi_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt08aHasiSwitch(volatile int a0)
{
    Act *sub = ((PObjGObjSt08A *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    hasi_switch_mes[0].func = actSt08aHasiUp;
    sub->mail = hasi_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
