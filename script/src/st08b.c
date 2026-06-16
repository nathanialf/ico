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
extern int scpSubAdpcmPlay(int a0);
extern void _ACTWait(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062A894;
void actSt08bDoor(volatile int a0) {
    int r;
    while ((r = scpSubAdpcmPlay(0x13)) == 0 || scpSleepEnemyOne(a0, r, 350.0f) == 0) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoorUpChk);

extern int scpDoorTypeUpUp(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);

void actSt08bDoorDownChk(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x514) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF1);
}

void actSt08bKuren(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x515) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF2);
}

void actSt08bEne(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x560) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF3);
}

void actSt08bEnemy1(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x561) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF4);
}

void actSt08bEnemy2(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x562) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF7);
}

void actSt08bKurenMain(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x563) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF8);
}

extern int scpDoorTypeUpUp(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);

void actSt08aGirlYoro(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x518) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF5);
}

void actSt08bDoorEvent(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x519) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xF6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoorUpEffect);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", func_00221508);

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
