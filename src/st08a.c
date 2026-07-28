#include "common.h"

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D21D0[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt06aSuimonChk(void);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt08aEnd(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xFD) == 0) {
        stage_KillPlayBgAnimation(0x134, 0, 0);
        D_004D21D0[1] = (int)actSt06aSuimonChk;
        gobj->unkB4 = D_004D21D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x134, 0, -1);
    }
}

extern int D_004D21F0[];
extern void actSt06aDoor(void);

void actSt08aEne1Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xFE) == 0) {
        stage_KillPlayBgAnimation(0x135, 0, 0);
        D_004D21F0[1] = (int)actSt06aDoor;
        gobj->unkB4 = D_004D21F0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x135, 0, -1);
    }
}

extern int D_004D2210[];
extern void actSt06aDoorUpChk(void);

void actSt08aEne2Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xFF) == 0) {
        stage_KillPlayBgAnimation(0x136, 0, 0);
        D_004D2210[1] = (int)actSt06aDoorUpChk;
        gobj->unkB4 = D_004D2210;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x136, 0, -1);
    }
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt08aDoorUp(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x94) != 0 && func_0017B230(0xD1) == 0) {
        stage_KillPlayBgAnimation(0x13A, 0, -1);
    }
    if (func_0017B230(0x94) == 0 || func_0017B230(0xD1) != 0) {
        stage_KillPlayBgAnimation(0x13A, 0, 0);
    }
}

typedef struct DoorSub {
    char pad[0xC0];
    void *field_B0;
    void *field_B4;
} DoorSub;

extern int D_006325B4;
extern int D_004D1E50[];

void actSt08aDoor(volatile int a0) {
    int s = *(int*)(a0 + 0x164);
    *(int*)(s + 0xC0) = (int)D_004D1E50;
    while (1) {
        _ACTWait(1);
    }
}

extern int *D_004D1E90[];
extern void actSt05eSolar(void);

void func_00223BF0(volatile int a0) {
    DoorSub *obj = *(DoorSub **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D1E90[1] = (int *)actSt05eSolar;
    obj->field_B0 = 0;
    obj->field_B4 = (void *)D_004D1E90;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D1EB0[];

void actSt08aEne1(volatile int a0) {
    int s = *(int*)(a0 + 0x164);
    *(int*)(s + 0xC0) = (int)D_004D1EB0;
    while (1) {
        _ACTWait(1);
    }
}

extern int *D_004D1EF0[];
extern void actSt05eWaterMain(void);

void func_00223C78(volatile int a0) {
    DoorSub *obj = *(DoorSub **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D1EF0[1] = (int *)actSt05eWaterMain;
    obj->field_B0 = 0;
    obj->field_B4 = (void *)D_004D1EF0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D1F10[];

void actSt08aEne2(volatile int a0) {
    int s = *(int*)(a0 + 0x164);
    *(int*)(s + 0xC0) = (int)D_004D1F10;
    while (1) {
        _ACTWait(1);
    }
}

extern int *D_004D1F50[];
extern void actSt05eWaterSwitch(void);

void func_00223D00(volatile int a0) {
    DoorSub *obj = *(DoorSub **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D1F50[1] = (int *)actSt05eWaterSwitch;
    obj->field_B0 = 0;
    obj->field_B4 = (void *)D_004D1F50;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_00631AE4;
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float a3, float a4);
extern int func_0017B230(int a0);

void actSt08aEnemy1(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_0017B230(0xDA) == 0 || func_0017B230(0xDB) == 0 ||
           func_0017B230(0xDC) == 0 || func_0017B230(0xCF) == 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(8, D_00631AE4, D_00631AE8, 2.0f, 8.0f);
}

void actSt08aEnemy2(int x) {
    volatile int local = x;
}

void actSt08aEnemy3(int x) {
    volatile int local = x;
}

void actSt08aEnemy4(int x) {
    volatile int local = x;
}

void actSt08aIntro(int x) {
    volatile int local = x;
}

void actSt08aInit(int x) {
    volatile int local = x;
}

void actSt08aDoorMain(int x) {
    volatile int local = x;
}

void actSt08aDoorSwitch(int x) {
    volatile int local = x;
}

extern void AddWayPointTop(int a0, int a1);

void actSt08aIntroChk(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_0017B230(0xEA) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(3, 1);
}

INCLUDE_ASM("asm/nonmatchings/src/st08a", func_00223E98);

void func_00223EF0(int x) {
    volatile int local = x;
}

void func_00223F00(int x) {
    volatile int local = x;
}

void func_00223F10(int x) {
    volatile int local = x;
}

void func_00223F20(int x) {
    volatile int local = x;
}

void func_00223F30(int x) {
    volatile int local = x;
}

