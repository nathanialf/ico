#include "common.h"
extern int D_004D1B70[];

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;



extern int D_00633A00;
extern int func_0017B230(int a0);
extern int soundSeVolSet();
extern int actSt25aQueenDeadChk();
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void lt_fade_status(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05dDoor2(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepEnemyOne(a0, D_00631AE8, 200.0f) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    func_0017B258(0xAA);
    _ACTWait(0xA);
    stage_KillPlayBgAnimation(0xCA, 1, 0);
    while (func_0012AA80(0xCA) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern int D_004D1BB0[];
extern int D_00631AE4;
extern void actSt04lRope2Chk(void);

void actSt05dDoor2UpChk(volatile int a0) {
    GObj__p4 *gobj = *(GObj__p4 **)(a0 + 0x164);
    while (scpSleepSpiderGroupOne(D_00631AE4, 0xA000000) != 0) { _ACTWait(1); }
    {
        int *p = D_004D1B70 + 16;
        p[1] = (int)actSt04lRope2Chk;
        gobj->unkB4 = p;
    }
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

void actSt05dDoor2DownChk(int x) {
    volatile int local = x;
}

void actSt05dEne(int x) {
    volatile int local = x;
}

void actSt05dEnemy1(int x) {
    volatile int local = x;
}

void actSt05dEnemy2(int x) {
    volatile int local = x;
}

void actSt05dDoor2Event(int x) {
    volatile int local = x;
}

void actSt05dDoor2UpEffect(int x) {
    volatile int local = x;
}

void actSt05dDoor2DownEffect(int x) {
    volatile int local = x;
}

void actSt05dEneChk(int x) {
    volatile int local = x;
}

void func_0021F578(int x) {
    volatile int local = x;
}

void func_0021F588(int x) {
    volatile int local = x;
    char *p = actSt25aQueenDeadChk(0x40A);
    *(int *)(p + 0x16C) = 0;
}

extern int scpDoorTypeUpUp(int a0);

void func_0021F5B0(volatile int a0) {
    while (scpDoorTypeUpUp(0x402) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xB8);
}

void func_0021F5F8(volatile int a0) {
    while (scpDoorTypeUpUp(0x403) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xB9);
}

void func_0021F640(volatile int a0) {
    while (scpDoorTypeUpUp(0x454) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xBA);
}

void func_0021F688(volatile int a0) {
    while (scpDoorTypeUpUp(0x455) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xBB);
}

void func_0021F6D0(volatile int a0) {
    while (scpDoorTypeUpUp(0x456) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xBE);
}

void func_0021F718(volatile int a0) {
    while (scpDoorTypeUpUp(0x457) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xBF);
}

void func_0021F760(volatile int a0) {
    while (scpDoorTypeUpUp(0x406) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xBC);
}

void func_0021F7A8(volatile int a0) {
    while (scpDoorTypeUpUp(0x407) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0xBD);
}

void func_0021F7F0(void)
{
    if (D_00633A00 == 0) {
        return;
    }
    if (func_0017B230(0xD1) != 0) {
        return;
    }
    return soundSeVolSet(D_00633A00);
}

extern void AddWayPointTop(int a0, int a1);

void func_0021F828(void)
{
    if (func_0017B230(0xF9) == 0) {
        stage_KillPlayBgAnimation(0x130, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x130, 0, -1);
    }
    if (func_0017B230(0xFA) == 0) {
        stage_KillPlayBgAnimation(0x131, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x131, 0, -1);
    }
    if (func_0017B230(0xFB) == 0) {
        stage_KillPlayBgAnimation(0x132, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x132, 0, -1);
    }
    if (func_0017B230(0xFC) == 0) {
        stage_KillPlayBgAnimation(0x133, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x133, 0, -1);
    }
    if (func_0017B230(0xFD) == 0) {
        stage_KillPlayBgAnimation(0x134, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x134, 0, -1);
    }
    if (func_0017B230(0xFE) == 0) {
        stage_KillPlayBgAnimation(0x135, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x135, 0, -1);
    }
    if (func_0017B230(0xFF) == 0) {
        stage_KillPlayBgAnimation(0x136, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x136, 0, -1);
    }
    if (func_0017B230(0xE5) == 0) {
        AddWayPointTop(1, 0);
    } else {
        AddWayPointTop(1, 1);
    }
    if (func_0017B230(0xEA) == 0) {
        stage_KillPlayBgAnimation(0x127, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x127, 0, -1);
    }
    if (func_0017B230(0xEB) == 0) {
        stage_KillPlayBgAnimation(0x128, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x128, 0, -1);
    }
    if (func_0017B230(0xE4) == 0) {
        char *p = actSt25aQueenDeadChk(0x4FF);
        *(int *)(p + 0x16C) = 0;
    }
}

