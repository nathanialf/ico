#include "common.h"

void actSt08bKurenSwitch(int x) {
    volatile int local = x;
}

void actSt08bKurenLeft(int x) {
    volatile int local = x;
}

void actSt08bKurenRight(int x) {
    volatile int local = x;
}

extern int D_006325B4;
extern void _ACTWait(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern int scpTriggerBall(int a0, int a1, float f);
extern int scpIsBombExplode(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt08bDoor(volatile int a0) {
    int r;
    while ((r = scpIsBombExplode(0x13)) == 0 || scpTriggerBall(a0, r, 350.0f) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    func_0017B258(0xF0);
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x137, 1, 0);
    while (func_0012AA80(0x137) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D22B0[];
extern int D_00631AE4;
extern void _ACTWait(int a0);
extern void actSt06aDoorDownChk(void);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt08bDoorUpChk(volatile int a0) {
    struct { char pad[0xC4]; int *unkB4; } *gobj = *(void **)(a0 + 0x164);
    while (scpSleepSpiderGroupOne(D_00631AE4, 0xA000000) != 0) {
        _ACTWait(1);
    }
    D_004D22B0[1] = (int)actSt06aDoorDownChk;
    gobj->unkB4 = D_004D22B0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern void func_0017B258(int a0);
extern int scpIsTorchLightOn(int a0);

void actSt08bDoorDownChk(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x518) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xF1);
}

void actSt08bKuren(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x519) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xF2);
}

void actSt08bEne(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x566) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xF3);
}

void actSt08bEnemy1(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x567) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xF4);
}

void actSt08bEnemy2(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x568) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xF7);
}

void actSt08bKurenMain(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x569) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xF8);
}

void actSt08aGirlYoro(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x51C) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xF5);
}

void actSt08bDoorEvent(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x51D) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xF6);
}

extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void gflagInit(int a0);

void actSt08bDoorUpEffect(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDA) == 0) {
        stage_KillPlayBgAnimation(0xA6, 0, 0);
        stage_KillPlayBgAnimation(0xA8, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xA6, 0, -1);
        stage_KillPlayBgAnimation(0xA8, 0, -1);
        gflagInit(0x4DB);
        gflagInit(0x4DC);
    }
    if (func_0017B230(0xDB) == 0) {
        stage_KillPlayBgAnimation(0xA7, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xA7, 0, -1);
        gflagInit(0x4DD);
        gflagInit(0x4DE);
    }
    if (func_0017B230(0xE2) == 0) {
        stage_KillPlayBgAnimation(0xA9, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xA9, 0, -1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorDownEffect);

extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt08bEneChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDA) != 0 && func_0017B230(0x7D) == 0) {
        stage_KillPlayBgAnimation(0x138, 0, -1);
    } else {
        stage_KillPlayBgAnimation(0x138, 0, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st08b", func_00224778);

INCLUDE_ASM("asm/nonmatchings/src/st08b", func_002247D8);

INCLUDE_ASM("asm/nonmatchings/src/st08b", func_00224898);

INCLUDE_ASM("asm/nonmatchings/src/st08b", func_00224900);

void func_00224960(int x) {
    volatile int local = x;
}

