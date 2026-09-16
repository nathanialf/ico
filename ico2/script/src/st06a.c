#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    int act;           /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

extern void actSt06aShutterSwitch(volatile int a0);
extern void actSt06aJumpSwitch(volatile int a0);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copies read. */
typedef union {
    float f[4];
    long long d[2];
} ConstVec;

static const ConstVec doorUpEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}};

static const ConstVec doorUpEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}};

static const ConstVec doorUpEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}};

static const ConstVec suimonSubPos = {{-1869.0f, -1147.0f, -664.0f, 0.0f}};

static const ConstVec jumpPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}};

static const ConstVec jumpPos2 = {{-505.0f, -1447.0f, -5671.0f, 1.0f}};

static const ConstVec kyomiPos = {{-985.0f, -177.0f, -696.0f, 0.0f}};

static const ConstVec farPos = {{0.0f, 0.0f, -1000000.0f, 1.0f}};

/* Deferred-`inline` tail members: ee-gcc 2.9 emits a plain-`inline` function's
   out-of-line copy at the END of the object in PROTOTYPE order, while its
   string constants are emitted where the function is DEFINED.  That pair of
   rules is what puts "FALLDOWN..." first in this TU's .rodata run while
   actSt06aPistonRideOffChk's code sits near the end of its .text. */
inline void actSt06aPistonRideOffChk(volatile int a0);
inline void actSt06aPistonFlagOffChk(volatile int a0);
inline void actSt06aSoundChk(volatile int a0);
inline void actSt06aSound2Chk(volatile int a0);

static ActMail suimon_mes[2] = {{430}, {429}};

static float suimon_sound_pos[4] = {810.0f, -346.0f, 381.0f, 0.0f};

static ActMail door_down_mes[2] = {{430}, {429}};

static ActMail door_up_mes[2] = {{430}, {429}};

static ActMail door_upchk_mes[2] = {{430}, {429}};

static ActMail door_dnchk_mes[2] = {{430}, {429}};

static ActMail shutter_main_mes[2] = {{406, actSt06aShutterSwitch}, {429}};

static ActMail shutter_mes[2] = {{430}, {429}};

static ActMail shutter_switch_mes[2] = {{430}, {429}};

static ActMail exit_mes[2] = {{430}, {429}};

static ActMail exit_girl_mes[2] = {{430}, {429}};

static ActMail box_mes[2] = {{430}, {429}};

static ActMail box2_mes[2] = {{430}, {429}};

static ActMail box3_mes[2] = {{430}, {429}};

static ActMail ball_delete_mes[2] = {{430}, {429}};

static ActMail box_event2_in_mes[2] = {{430}, {429}};

static ActMail box_event2_out_mes[2] = {{430}, {429}};

static ActMail box_event2_inchk_mes[2] = {{430}, {429}};

static ActMail box_event2_out_chk_mes[2] = {{430}, {429}};

static ActMail way_mes[2] = {{430}, {429}};

static ActMail way_onchk_mes[2] = {{430}, {429}};

static ActMail way_offchk_mes[2] = {{430}, {429}};

static ActMail wall_way_on_mes[2] = {{430}, {429}};

static ActMail wall_way_off_mes[2] = {{430}, {429}};

static ActMail wall_way_onchk_mes[2] = {{430}, {429}};

static ActMail wall_way_offchk_mes[2] = {{430}, {429}};

static ActMail wall_way2_on_mes[2] = {{430}, {429}};

static ActMail wall_way2_off_mes[2] = {{430}, {429}};

static ActMail wall_way2_onchk_mes[2] = {{430}, {429}};

static ActMail wall_way2_offchk_mes[2] = {{430}, {429}};

static ActMail statue_mes[2] = {{430}, {429}};

static ActMail head_mes[2] = {{430}, {429}};

static ActMail tree_mes[2] = {{430}, {429}};

static ActMail kyomi_mes[2] = {{430}, {429}};

static ActMail kyomi_onchk_mes[2] = {{430}, {429}};

static ActMail kyomi_off_chk_mes[2] = {{430}, {429}};

static ActMail jump_main_mes[2] = {{407, actSt06aJumpSwitch}, {429}};

static ActMail jump_mes[2] = {{430}, {429}};

static ActMail jump_switch_mes[2] = {{430}, {429}};

static ActMail piston_mes[2] = {{430}, {429}};

static ActMail piston_ride_onchk_mes[2] = {{430}, {429}};

static ActMail piston_ride_offchk_mes[2] = {{430}, {429}};

static ActMail piston_flag_mes[2] = {{430}, {429}};

static float piston_flag_sound_pos[4] = {87.0f, -772.0f, 1135.0f, 0.0f};

static ActMail piston_flag_onchk_mes[2] = {{430}, {429}};

static ActMail piston_flag_offchk_mes[2] = {{430}, {429}};

static ActMail sound_mes[2] = {{430}, {429}};

static float sound_chk_pos[4] = {810.0f, -346.0f, 381.0f, 0.0f};

static ActMail sound2_mes[2] = {{430}, {429}};

static float sound2_chk_pos[4] = {87.0f, -772.0f, 1135.0f, 0.0f};

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int D_0063AA08;
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void gflagOff(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern int scpTriggerBall(int a0, void *a1, float radius);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int handle);
extern void SetWayGroupActive(int a0, int a1);
extern int scpTriggerFloorAttr(void *obj, int attr);
extern void FinishHint(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void stage_SetLoopFlag(int a0, int a1);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int D_0063C558;
extern void debug_StdPrintfDummy(char *fmt);
extern void *D_00639EA4;
extern void *D_00639EA8;

void actSt06aInit(void)
{
    if (gflagChk(0x6A) == 0) {
        SetWayGroupActive(9, 0);
        SetWayGroupActive(0xA, 0);
    } else {
        SetWayGroupActive(9, 1);
        SetWayGroupActive(0xA, 1);
        FinishHint(0x13);
    }

    if (gflagChk(0x6B) == 0) {
        SetWayGroupActive(0xC, 0);
    } else {
        SetWayGroupActive(0xC, 1);
    }
}

extern void SetRotObjectLockFlag(PObjGObj *a0, int a1);
extern void ReInitBoxGeo(PObjGObj *a0);
extern void actSt06aSuimonChk(volatile int a0);

void actSt06aSuimon(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) == 0) {
        stage_SetAnimation(0x6B, 0, 0);
        scpSearchGobj(0x6D7)->f16C = 0;
        stage_SetLoopFlag(0x6C, 1);
        stage_SetAnimation(0x6C, 1, 0);
        suimon_mes[0].func = actSt06aSuimonChk;
        self->mail = suimon_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x6B, 0, -1);
        stage_SetAnimation(0x6D, 0, -1);
        scpSearchGobj(0x6D8)->f16C = 0;
        SetRotObjectLockFlag(scpSearchGobj(0x6EE), 1);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(0x6ED));
    }
}

typedef struct Pad {
    int unk00;        /* 0x00 */
    int trg;          /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} Pad;

extern Pad D_0028F8F0[];
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern void WakeupHint(int a0);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
extern char *shutter;
extern void actSt06aShutterOpenSub(volatile int a0);
extern void scpWakeupEnemyAll(void);
extern int actCreateSubThread(void *entry, int prio);
extern void actSt06aJumpSub(volatile int a0);
extern int scpAdpcmPlayRequestNum(void);
extern void iosThreadSetPri(int a0, int a1);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern void scpFadeIn(float f);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void SetCameraFlag_LwsCutBack(void);
extern int suimon;
extern int D_0063C55C;
extern float scpGetRotObjectRotCount(int a0);
extern void actSt06aSuimonFlagOn(volatile int a0);
extern void actSt06aSuimonEffect(volatile int a0);
extern void actSt06aSuimonSub(volatile int a0);

void actSt06aSuimonChk(volatile int a0)
{
    int he;
    int hs;

    while ((scpGetRotObjectRotCount(0x6EE) < -2.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    FinishHint(0x13);

    SetRotObjectLockFlag(scpSearchGobj(0x6EE), 1);

    stage_SetLoopFlag(0x6C, 0);
    stage_SetLoopFlag(0x71, 0);
    stage_SetAnimation(0x71, 0, 0);

    soundSeDefPlay(0x54F, 0, suimon_sound_pos, 1);

    D_0063AA08 = 1;
    scpSleepEnemyAll();

    _ACTWait(0x1E);

    scpAdpcmPlayRequestFunc(0x44, &suimon, 1, 1, 1);

    while (suimon == 0) {
        _ACTWait(1);
    }

    D_0063C558 = 0;
    D_0063C55C = 0;

    actCreateSubThread(actSt06aSuimonFlagOn, 0x15);
    he = actCreateSubThread(actSt06aSuimonEffect, 0x15);
    hs = actCreateSubThread(actSt06aSuimonSub, 0x15);

    while (D_0063C558 == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    D_0063C55C = D_0063C558 ^ 1;

    iosThreadSetPri(hs + 0x24, 0x22);
    iosThreadSetPri(he + 0x24, 0x22);

    if (D_0063C558 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&suimon, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x6B, 0, -1);
        stage_SetAnimation(0x6D, 0, -1);
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    scpSearchGobj(0x6D7)->f16C = 1;
    scpSearchGobj(0x6D8)->f16C = 0;

    SetWayGroupActive(9, 1);
    SetWayGroupActive(0xA, 1);
}

extern void actSt06aDoorDownChk(volatile int a0);
extern void actSt06aDoorUpChk(volatile int a0);

void actSt06aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x70, 0, 0);
        _ACTWait(0x3C);
        door_down_mes[0].func = actSt06aDoorDownChk;
        self->mail = door_down_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x6F, 0, 0);
        door_up_mes[0].func = actSt06aDoorUpChk;
        self->mail = door_up_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern void actSt06aDoorUpEffect(volatile int a0);
extern void actSt06aDoorDownEffect(volatile int a0);

void actSt06aDoorUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt06aDoorUpEffect, 0x15);

    scpWakeupItemWithBoundary(-1879.0f, -1047.0f, -620.0f, 100.0f);

    stage_SetAnimation(0x6F, 1, 0);

    buf[0] = suimonSubPos.d[0];
    buf[1] = suimonSubPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x6F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_upchk_mes[0].func = actSt06aDoorDownChk;
    sub->mail = door_upchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt06aDoorDownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt06aDoorDownEffect, 0x15);

    scpWakeupItemWithBoundary(-1879.0f, -1047.0f, -620.0f, 100.0f);

    stage_SetAnimation(0x70, 1, 0);

    buf[0] = suimonSubPos.d[0];
    buf[1] = suimonSubPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x70) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_dnchk_mes[0].func = actSt06aDoorUpChk;
    sub->mail = door_dnchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt06aShutterOpen(volatile int a0)
{
    int h;

    lt_switch_layout(0x37);
    gflagOn(0x6B);
    WakeupHint(0x13);
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x53, (int *)&shutter, 1, 1, 0);

    h = actCreateSubThread(actSt06aShutterOpenSub, 0x15);

    D_0063C558 = 0;

    while (D_0063C558 == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C558 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (shutter == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc((int *)&shutter, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x6E, 0, -1);
        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }

    scpSearchGobj(0x6CE)->f16C = 0;
    scpSearchGobj(0x6CF)->f16C = 1;
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    SetWayGroupActive(0xC, 1);
}

extern void SetCameraFlag_GamecamCutBack(void);
extern void actSt06aBoxSub(volatile int a0);

void actSt06aBoxChk(volatile int a0)
{
    int h;

    while (scpTriggerBall(a0, scpSearchGobj(0x6ED), 300.0f) == 0 || gflagChk(0x6A) != 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    gflagOn(0x6D);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    h = actCreateSubThread(actSt06aBoxSub, 0x15);

    D_0063C558 = 0;

    while (D_0063C558 == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C558 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        scpSearchGobj(0x6ED)->f16C = 0;
        stage_SetAnimation(0x73, 0, -1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

extern void ReviveAllCarryableItemsWithRandomVelocity(float a0, float a1);

void actSt06aStatueChk(volatile int a0)
{
    int handle;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    scpSearchGobj(0x715)->f16C = 0;
    stage_SetAnimation(0x103, -1, -2);
    stage_SetAnimation(0x75, 1, 0);

    handle = soundSeDefPlay(0x54D, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x75, 0x32, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerBall(a0, scpSearchGobj(0x6EA), 150.0f) != 0) {
        ReviveAllCarryableItemsWithRandomVelocity(-50.0f, 0.0f);
    }

    while (stage_CheckAnimationFrame(0x75, 0x6D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(handle);

    while (stage_CheckAnimationFinish(0x75) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    _ACTWait(0x78);

    gflagOn(0x71);
}

extern int toge;
extern int D_0063AA00;
extern int GetCharHeldItem(void *a0);
extern void scpPlayMot(void *a0, int a1);

void actSt06aHeadChk(volatile int a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(0x6EA), 70.0f) == 0 || gflagChk(0x71) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    gflagOn(0x72);

    _ACTWait(0x78);

    scpAdpcmPlayRequestFunc(0x37, &toge, 1, 1, 1);

    while (toge == 0) {
        _ACTWait(1);
    }

    if (D_0063AA00 == 0) {
        stage_SetAnimation(0x77, 1, 0);

        if (scpTriggerFloorAttr(D_00639EA4, 0x7000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0) {
            SetCameraFlag_LwsCutBack();
        }

        while (stage_CheckAnimationFrame(0x77, 0x82, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x35B, 0, 0, 1);

        while (stage_CheckAnimationFrame(0x77, 0xD0, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        scpSearchGobj(0x6EB)->f16C = 1;

        while (stage_CheckAnimationFinish(0x77) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }

    if (D_0063AA00 != 0) {
        stage_SetAnimation(0x78, 1, 0);

        if (scpTriggerFloorAttr(D_00639EA4, 0x7000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0) {
            SetCameraFlag_LwsCutBack();
        }

        while (stage_CheckAnimationFrame(0x78, 0x82, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x35B, 0, 0, 1);

        while (stage_CheckAnimationFrame(0x78, 0xD0, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        scpSearchGobj(0x6EC)->f16C = 1;

        while (stage_CheckAnimationFinish(0x78) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }

    if (GetCharHeldItem(D_00639EA4) == 6) {
        scpPlayMot(D_00639EA4, 0);
    }

    scpSearchGobj(0x6EA)->f16C = 0;

    if (toge != 0) {
        scpAdpcmFadeCloseFunc(&toge, 0x50);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

void actSt06aJumpMove(volatile int a0)
{
    int h;

    lt_switch_layout(0x37);
    scpSleepEnemyAll();

    h = actCreateSubThread(actSt06aJumpSub, 0x15);

    D_0063C558 = 0;

    while (D_0063C558 == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C558 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetLoopFlag(0x71, 1);
        stage_SetAnimation(0x71, 1, 0);
        gflagOn(0x74);
        stage_SetAnimation(0x72, 0, -1);
        SetCameraFlag_LwsCutBack();
        scpFadeIn(8.0f);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

extern void iosOmSendMail(void *a0, int a1, void *a2);
extern void actSt06aPistonRideOnChk(volatile int a0);

inline void actSt06aPistonRideOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x6000000) != 0) {
        if (gflagChk(0x75) != 0) {
            debug_StdPrintfDummy("FALLDOWN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            iosOmSendMail(D_00639EA4, 7, D_00639EA4);
        }
        _ACTWait(1);
    }

    piston_ride_offchk_mes[0].func = actSt06aPistonRideOnChk;
    sub->mail = piston_ride_offchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt06aPistonFlagOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (gflagChk(0x74) == 0 || gflagChk(0x6A) != 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFrame(0x71, 0x7A, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(0x551, 0, piston_flag_sound_pos, 1);
    gflagOn(0x75);
    debug_StdPrintfDummy("PISTON_FLAG_ON!\n");

    while (stage_CheckAnimationFrame(0x71, 0x7C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    piston_flag_onchk_mes[0].func = actSt06aPistonFlagOffChk;
    sub->mail = piston_flag_onchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void SleepHint(int a0);
extern void actSt06aShutterMain(volatile int a0);

void actSt06aShutter(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6B) == 0) {
        stage_SetAnimation(0x6E, 0, 0);
        scpSearchGobj(0x6CF)->f16C = 0;
        SleepHint(0x13);
        shutter_mes[0].func = actSt06aShutterMain;
        self->mail = shutter_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x6E, 0, -1);
        scpSearchGobj(0x6CE)->f16C = 0;
    }
}

extern void actSt06aExitChk(volatile int a0);

void actSt06aExit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    exit_mes[0].func = actSt06aExitChk;
    self->mail = exit_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aExitGirlChk(volatile int a0);

void actSt06aExitGirl(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    exit_girl_mes[0].func = actSt06aExitGirlChk;
    self->mail = exit_girl_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aBoxChk(volatile int a0);

void actSt06aBox(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6C) == 0 && gflagChk(0x6D) == 0) {
        box_mes[0].func = actSt06aBoxChk;
        self->mail = box_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x6ED)->f16C = 0;
    }
}

extern void actSt06aBox2Chk(volatile int a0);

void actSt06aBox2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6C) == 0 && gflagChk(0x6D) == 0) {
        box2_mes[0].func = actSt06aBox2Chk;
        self->mail = box2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt06aBox3Chk(volatile int a0);

void actSt06aBox3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6C) == 0 && gflagChk(0x6D) == 0) {
        box3_mes[0].func = actSt06aBox3Chk;
        self->mail = box3_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt06aBoxEvent2InChk(volatile int a0);
extern void actSt06aBoxEvent2OutChk(volatile int a0);

void actSt06aBoxEvent2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6E) == 0) {
        box_event2_in_mes[0].func = actSt06aBoxEvent2InChk;
        self->mail = box_event2_in_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        box_event2_out_mes[0].func = actSt06aBoxEvent2OutChk;
        self->mail = box_event2_out_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt06aWayOnChk(volatile int a0);

void actSt06aWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    way_mes[0].func = actSt06aWayOnChk;
    self->mail = way_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aWallWayOnChk(volatile int a0);
extern void actSt06aWallWayOffChk(volatile int a0);

void actSt06aWallWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6F) == 0) {
        wall_way_on_mes[0].func = actSt06aWallWayOnChk;
        self->mail = wall_way_on_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0x17, 1);
        SetWayGroupActive(0x18, 1);
        wall_way_off_mes[0].func = actSt06aWallWayOffChk;
        self->mail = wall_way_off_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt06aWallWay2OnChk(volatile int a0);
extern void actSt06aWallWay2OffChk(volatile int a0);

void actSt06aWallWay2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x70) == 0) {
        wall_way2_on_mes[0].func = actSt06aWallWay2OnChk;
        self->mail = wall_way2_on_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0x17, 1);
        SetWayGroupActive(0x18, 1);
        wall_way2_off_mes[0].func = actSt06aWallWay2OffChk;
        self->mail = wall_way2_off_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt06aStatueChk(volatile int a0);

void actSt06aStatue(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x71) == 0) {
        stage_SetAnimation(0x75, 0, 0);
        statue_mes[0].func = actSt06aStatueChk;
        self->mail = statue_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x75, 0, -1);
        scpSearchGobj(0x715)->f16C = 0;
        stage_SetAnimation(0x103, -1, -2);
    }
}

extern void actSt06aHeadChk(volatile int a0);

void actSt06aHead(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x72) == 0) {
        scpSearchGobj(0x6EB)->f16C = 0;
        scpSearchGobj(0x6EC)->f16C = 0;
        head_mes[0].func = actSt06aHeadChk;
        self->mail = head_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        if (D_0063AA00 == 0) {
            scpSearchGobj(0x6EC)->f16C = 0;
        }
        if (D_0063AA00 != 0) {
            scpSearchGobj(0x6EB)->f16C = 0;
        }
    }
}

extern void actSt06aTreeChk(volatile int a0);

void actSt06aTree(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x72) == 0) {
        scpSearchGobj(0x6EA)->f16C = 0;
        tree_mes[0].func = actSt06aTreeChk;
        self->mail = tree_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x6EA)->f16C = 0;
    }
}

extern void actSt06aBallDeleteChk(volatile int a0);

void actSt06aBallDelete(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    ball_delete_mes[0].func = actSt06aBallDeleteChk;
    self->mail = ball_delete_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aKyomiOffChk(volatile int a0);

void actSt06aKyomi(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    kyomi_mes[0].func = actSt06aKyomiOffChk;
    self->mail = kyomi_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aJumpMain(volatile int a0);

void actSt06aJump(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x74) == 0) {
        stage_SetAnimation(0x71, 0, 0);
        jump_mes[0].func = actSt06aJumpMain;
        self->mail = jump_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else if (gflagChk(0x6A) == 0) {
        stage_SetLoopFlag(0x71, 1);
        stage_SetAnimation(0x71, 1, 0);
    } else {
        stage_SetAnimation(0x71, 0, 0);
    }
}

extern void actSt06aPistonRideOnChk(volatile int a0);

void actSt06aPiston(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    piston_mes[0].func = actSt06aPistonRideOnChk;
    self->mail = piston_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aPistonFlagOnChk(volatile int a0);

void actSt06aPistonFlag(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    piston_flag_mes[0].func = actSt06aPistonFlagOnChk;
    self->mail = piston_flag_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt06aSound(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) == 0) {
        sound_mes[0].func = actSt06aSoundChk;
        self->mail = sound_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt06aSound2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) == 0) {
        sound2_mes[0].func = actSt06aSound2Chk;
        self->mail = sound2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt06aSuimonEvent(int x)
{
    volatile int local = x;
}

extern int scpEffectStart(int *buf, int a1);

void actSt06aSuimonEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long b3[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorUpEffect2Pos.d[0];
    long long v0c = doorUpEffect3Pos.d[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = doorUpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            b3[0] = v0c;
            b3[1] = doorUpEffect3Pos.d[1];
            scpEffectStart((int *)b3, 0);
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(0);
}

extern int D_0028F4C0[];
extern float D_0063C088;

void actSt06aSuimonFlagOn(volatile int a0)
{
    int i = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 7.0;

    D_0063C088 = 0.005f;

    while (i-- > 0) {
        if (D_0063C55C != 0) {
            D_0063C088 = 1000.0f;
            break;
        }
        _ACTWait(1);
    }
    gflagOn(0x6A);
}

void actSt06aSuimonSub(volatile int a0)
{
    stage_SetAnimation(0x6B, 1, 0);
    stage_SetAnimation(0x6D, 1, 0);

    while (stage_CheckAnimationFinish(0x6B) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C558 = 1;
    _ACTWait(0);
}

void actSt06aDoorEvent(int x)
{
    volatile int local = x;
}

extern void _ACTWait(int a0);
extern int scpEffectStart(int *buf, int a1);

void actSt06aDoorUpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = jumpPos.d[0];
    long long v0b = jumpPos2.d[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = jumpPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = jumpPos2.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt06aDoorDownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = jumpPos2.d[0];
    long long v0b = jumpPos.d[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = jumpPos2.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = jumpPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt06aShutterMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = shutter_main_mes;

    while (1) {
        _ACTWait(1);
    }
}

extern void actSt06aShutterOpen(volatile int a0);

void actSt06aShutterSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    shutter_switch_mes[0].func = actSt06aShutterOpen;
    sub->mail = shutter_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void AdpcmPlay(int a0);

void actSt06aShutterOpenSub(volatile int a0)
{
    _ACTWait(0x3C);

    while (shutter == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(shutter + 0x2C));

    stage_SetAnimation(0x6E, 1, 0);

    while (stage_CheckAnimationFinish(0x6E) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C558 = 1;
    _ACTWait(0);
}

extern int RequestStageChange(int a0, void *a1, int a2, float a3, float a4);

void actSt06aExitChk(volatile int a0)
{
    while (gflagChk(0x6A) != 0 || scpTriggerBall(a0, D_00639EA4, 400.0f) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 0;
    RequestStageChange(3, D_00639EA4, 0, 16.0f, 16.0f);
}

extern void RequestStageChangeDirect(void *a0, int a1, void *buf, int a3);
extern void SetDirectRootPosition(void *a0, void *a1);
extern void ScpCallCameraSetTarget(float x, float y, float z);

void actSt06aExitGirlChk(volatile int a0)
{
    long long buf1[2];
    long long buf2[2];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x6A) != 0 || scpTriggerBall(a0, D_00639EA8, 400.0f) == 0) {
        _ACTWait(1);
    }

    buf1[0] = kyomiPos.d[0];
    buf1[1] = kyomiPos.d[1];
    RequestStageChangeDirect(D_00639EA8, 0x16, buf1, 0xB4);

    buf2[0] = farPos.d[0];
    buf2[1] = farPos.d[1];
    SetDirectRootPosition(D_00639EA8, buf2);

    ScpCallCameraSetTarget(-800.0f, -500.0f, 2200.0f);
}

void actSt06aBoxSub(volatile int a0)
{
    _ACTWait(0x3C);

    stage_SetAnimation(0x73, 1, 0);

    scpSearchGobj(0x6ED)->f16C = 0;

    while (stage_CheckAnimationFinish(0x73) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 7);

    D_0063C558 = 1;
    _ACTWait(0);
}

void actSt06aBox2Chk(volatile int a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(0x6ED), 200.0f) == 0 || gflagChk(0x6A) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x6C);
    scpSearchGobj(0x6ED)->f16C = 0;
}

void actSt06aBox3Chk(volatile int a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(0x6ED), 200.0f) == 0 || gflagChk(0x6A) != 0) {
        _ACTWait(1);
    }
}

void actSt06aBallDeleteChk(volatile int a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(0x6EA), 200.0f) == 0 || gflagChk(0x6A) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x6EA)->f16C = 0;
}

extern void actSt06aBoxEvent2OutChk(volatile int a0);

void actSt06aBoxEvent2InChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(scpSearchGobj(0x6ED), 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x6E);

    box_event2_inchk_mes[0].func = actSt06aBoxEvent2OutChk;
    sub->mail = box_event2_inchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aBoxEvent2InChk(volatile int a0);

void actSt06aBoxEvent2OutChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(scpSearchGobj(0x6ED), 0x2000000) != 0) {
        _ACTWait(1);
    }

    gflagOff(0x6E);

    box_event2_out_chk_mes[0].func = actSt06aBoxEvent2InChk;
    sub->mail = box_event2_out_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int scpCheckExistAliveEnemy(void);
extern void actSt06aWayOffChk(volatile int a0);

void actSt06aWayOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x16, 1);

    way_onchk_mes[0].func = actSt06aWayOffChk;
    sub->mail = way_onchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aWayOnChk(volatile int a0);

void actSt06aWayOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x16, 0);

    way_offchk_mes[0].func = actSt06aWayOnChk;
    sub->mail = way_offchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2);
extern void actSt06aWallWayOffChk(volatile int a0);

void actSt06aWallWayOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpIsRotObjectZPlusDirInclude(0x6EF, 0xF0, 0x12C) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x17, 1);
    SetWayGroupActive(0x18, 1);
    gflagOn(0x6F);

    wall_way_onchk_mes[0].func = actSt06aWallWayOffChk;
    sub->mail = wall_way_onchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aWallWayOnChk(volatile int a0);

/* The wall-way-off watcher's mail record: it installs actSt06aWallWayOnChk
   here and posts it. Word 0 of each entry is the mail id the entry answers
   (430 the actor post, 429 the trailing entry); .func is filled in at
   run time. Named for the thread that owns and posts it. */

void actSt06aWallWayOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpIsRotObjectZPlusDirInclude(0x6EF, 0xF0, 0x12C) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x17, 0);
    SetWayGroupActive(0x18, 0);
    gflagOff(0x6F);

    wall_way_offchk_mes[0].func = actSt06aWallWayOnChk;
    sub->mail = wall_way_offchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aWallWay2OffChk(volatile int a0);

void actSt06aWallWay2OnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpIsRotObjectZPlusDirInclude(0x6EF, 0x3C, 0x78) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x17, 1);
    SetWayGroupActive(0x18, 1);
    gflagOn(0x70);

    wall_way2_onchk_mes[0].func = actSt06aWallWay2OffChk;
    sub->mail = wall_way2_onchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aWallWay2OnChk(volatile int a0);

void actSt06aWallWay2OffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpIsRotObjectZPlusDirInclude(0x6EF, 0x3C, 0x78) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x17, 0);
    SetWayGroupActive(0x18, 0);
    gflagOff(0x70);

    wall_way2_offchk_mes[0].func = actSt06aWallWay2OnChk;
    sub->mail = wall_way2_offchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int ForMotionViewer_GetCurrentMotion(void *a0);
extern void ReviveAllCarryableItems(void);

void actSt06aTreeChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 150.0f) == 0 ||
           (ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x2F &&
            ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x30 &&
            ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x31 &&
            ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x3E)) {
        _ACTWait(1);
    }

    scpSearchGobj(0x6EA)->f16C = 1;
    ReviveAllCarryableItems();
}

extern void actSt06aKyomiOffChk(volatile int a0);

void actSt06aKyomiOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x6E6)->f16C = 1;
    scpSearchGobj(0x6E7)->f16C = 1;
    scpSearchGobj(0x6E8)->f16C = 1;
    scpSearchGobj(0x6E9)->f16C = 1;

    kyomi_onchk_mes[0].func = actSt06aKyomiOffChk;
    sub->mail = kyomi_onchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt06aKyomiOnChk(volatile int a0);

void actSt06aKyomiOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) != 0 &&
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x6E6)->f16C = 0;
    scpSearchGobj(0x6E7)->f16C = 0;
    scpSearchGobj(0x6E8)->f16C = 0;
    scpSearchGobj(0x6E9)->f16C = 0;

    kyomi_off_chk_mes[0].func = actSt06aKyomiOnChk;
    sub->mail = kyomi_off_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt06aJumpMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = jump_main_mes;

    while (1) {
        _ACTWait(1);
    }
}

extern void actSt06aJumpMove(volatile int a0);

void actSt06aJumpSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    jump_switch_mes[0].func = actSt06aJumpMove;
    sub->mail = jump_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void SetCameraFlag_LwsCutBack(void);

void actSt06aJumpSub(volatile int a0)
{
    stage_SetAnimation(0x72, 1, 0);

    while (stage_CheckAnimationFrame(0x72, 0x3C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetLoopFlag(0x71, 1);
    stage_SetAnimation(0x71, 1, 0);
    gflagOn(0x74);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0x72) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C558 = 1;
    _ACTWait(1);
}

extern int scpTriggerFloorAttr(void *a0, int a1);

/* The piston-ride-on watcher's own mail record (installs
   actSt06aPistonRideOffChk). */

void actSt06aPistonRideOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (gflagChk(0x74) == 0 || scpTriggerFloorAttr(D_00639EA4, 0x6000000) == 0) {
        _ACTWait(1);
    }

    piston_ride_onchk_mes[0].func = actSt06aPistonRideOffChk;
    sub->mail = piston_ride_onchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void actSt06aPistonFlagOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (stage_CheckAnimationFrame(0x71, 0x7D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(0x75);
    debug_StdPrintfDummy("PISTON_FLAG_OFF!\n");

    while (stage_CheckAnimationFrame(0x71, 0xC7, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    piston_flag_offchk_mes[0].func = actSt06aPistonFlagOnChk;
    sub->mail = piston_flag_offchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void actSt06aSoundChk(volatile int a0)
{
    int handle = soundSeDefPlay(0x54E, 0, sound_chk_pos, 1);

    while (gflagChk(0x6A) == 0) {
        _ACTWait(1);
    }

    soundSeDefStop(handle);
}

inline void actSt06aSound2Chk(volatile int a0)
{
    int handle;

    while (gflagChk(0x74) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("PISTON_LOOP_SE!!!!!!!!!!!!\n");

    handle = soundSeDefPlay(0x550, 0, sound2_chk_pos, 1);

    while (gflagChk(0x6A) == 0) {
        _ACTWait(1);
    }

    soundSeDefStop(handle);
}
