#include "common.h"

void actSt08bKurenSwitch(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08bKurenLeft(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08bKurenRight(int a0) {
    int buf[4];
    buf[0] = a0;
}

#include "common.h"
extern int scpIsBombExplode(int a0);
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062A894;
void actSt08bDoor(volatile int a0) {
    int r;
    while ((r = scpIsBombExplode(0x13)) == 0 || scpTriggerBall(a0, r, 350.0f) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_00178DD8(0xF0);
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x136, 1, 0);
    while (func_0012A958(0x136) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_00629DE4;
extern int D_004CCEC0[];
extern void actSt06aDoorDownChk(void);

void actSt08bDoorUpChk(volatile int a0) {
    struct { char pad[0xB4]; int *unkB4; } *gobj = *(void **)(a0 + 0x164);
    while (scpSleepSpiderGroupOne(D_00629DE4, 0xA000000) != 0) {
        _ACTWait(1);
    }
    D_004CCEC0[1] = (int)actSt06aDoorDownChk;
    gobj->unkB4 = D_004CCEC0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int scpIsTorchLightOn(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);

void actSt08bDoorDownChk(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x514) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF1);
}

void actSt08bKuren(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x515) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF2);
}

void actSt08bEne(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x560) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF3);
}

void actSt08bEnemy1(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x561) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF4);
}

void actSt08bEnemy2(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x562) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF7);
}

void actSt08bKurenMain(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x563) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF8);
}

extern int scpIsTorchLightOn(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);

void actSt08aGirlYoro(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x518) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF5);
}

void actSt08bDoorEvent(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x519) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF6);
}

extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void gflagInit(int a0);

void actSt08bDoorUpEffect(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDA) == 0) {
        stage_KillPlayBgAnimation(0xA5, 0, 0);
        stage_KillPlayBgAnimation(0xA7, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xA5, 0, -1);
        stage_KillPlayBgAnimation(0xA7, 0, -1);
        gflagInit(0x4D7);
        gflagInit(0x4D8);
    }
    if (func_00178DB0(0xDB) == 0) {
        stage_KillPlayBgAnimation(0xA6, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xA6, 0, -1);
        gflagInit(0x4D9);
        gflagInit(0x4DA);
    }
    if (func_00178DB0(0xE2) == 0) {
        stage_KillPlayBgAnimation(0xA8, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xA8, 0, -1);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoorDownEffect);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
void actSt08bEneChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDA) != 0 && func_00178DB0(0x7D) == 0) {
        stage_KillPlayBgAnimation(0x137, 0, -1);
    } else {
        stage_KillPlayBgAnimation(0x137, 0, 0);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_002214A8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xD1) == 0) {
        stage_KillPlayBgAnimation(0xDE, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xDE, 0, -1);
    }
}

extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void warpGirlInStage(float a0, float a1, float a2);
extern volatile float D_006298E8;
extern volatile float D_006298EC;
extern int D_004CCFE0[];
extern void actSt08bDoorDownEffect(void);

void func_00221508(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x8F) == 0) {
        stage_KillPlayBgAnimation(0xAA, 0, 0);
        D_004CCFE0[1] = (int)actSt08bDoorDownEffect;
        gobj->unkB4 = D_004CCFE0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xAA, 0, -1);
        if (func_00178DB0(0xDA) == 0) {
            warpGirlInStage(D_006298E8, D_006298EC, 0.0f);
        }
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_002215C8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x7D) == 0) {
        stage_KillPlayBgAnimation(0x10A, -1, -2);
    } else {
        stage_KillPlayBgAnimation(0x108, -1, -2);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00221630(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x7D) == 0) {
        stage_KillPlayBgAnimation(0x10D, -1, -2);
        stage_KillPlayBgAnimation(0x110, -1, -2);
    }
}

void func_00221690(int a0) {
    int buf[4];
    buf[0] = a0;
}
