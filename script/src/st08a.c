#include "common.h"

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CCDE0[];
extern void actSt06aSuimonChk(void);

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

void actSt08aEnd(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xFD) == 0) {
        stage_KillPlayBgAnimation(0x133, 0, 0);
        D_004CCDE0[1] = (int)actSt06aSuimonChk;
        gobj->unkB4 = D_004CCDE0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x133, 0, -1);
    }
}


extern int D_004CCE00[];
extern void actSt06aDoor(void);

void actSt08aEne1Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xFE) == 0) {
        stage_KillPlayBgAnimation(0x134, 0, 0);
        D_004CCE00[1] = (int)actSt06aDoor;
        gobj->unkB4 = D_004CCE00;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x134, 0, -1);
    }
}


extern int D_004CCE20[];
extern void actSt06aDoorUpChk(void);

void actSt08aEne2Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xFF) == 0) {
        stage_KillPlayBgAnimation(0x135, 0, 0);
        D_004CCE20[1] = (int)actSt06aDoorUpChk;
        gobj->unkB4 = D_004CCE20;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x135, 0, -1);
    }
}


void actSt08aDoorUp(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x94) != 0 && func_00178DB0(0xD1) == 0) {
        stage_KillPlayBgAnimation(0x139, 0, -1);
    }
    if (func_00178DB0(0x94) == 0 || func_00178DB0(0xD1) != 0) {
        stage_KillPlayBgAnimation(0x139, 0, 0);
    }
}

extern int D_0062A894;
extern int D_004CCA60[];

void actSt08aDoor(volatile int a0) {
    int s = *(int*)(a0 + 0x164);
    D_0062A894 = 0;
    *(int*)(s + 0xB0) = (int)D_004CCA60;
    while (1) {
        _ACTWait(1);
    }
}

typedef struct DoorSub {
    char pad[0xB0];
    void *field_B0;
    void *field_B4;
} DoorSub;

extern int *D_004CCAA0[];
extern void actSt05eSolar(void);
extern void BoxBarSoundOn(int a0, int a1);

void func_00220918(volatile int a0) {
    DoorSub *obj = *(DoorSub **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CCAA0[1] = (int *)actSt05eSolar;
    obj->field_B0 = 0;
    obj->field_B4 = (void *)D_004CCAA0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int D_004CCAC0[];

void actSt08aEne1(volatile int a0) {
    int s = *(int*)(a0 + 0x164);
    D_0062A894 = 0;
    *(int*)(s + 0xB0) = (int)D_004CCAC0;
    while (1) {
        _ACTWait(1);
    }
}

extern int *D_004CCB00[];
extern void actSt05eWaterMain(void);

void func_002209A8(volatile int a0) {
    DoorSub *obj = *(DoorSub **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CCB00[1] = (int *)actSt05eWaterMain;
    obj->field_B0 = 0;
    obj->field_B4 = (void *)D_004CCB00;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int D_004CCB20[];

void actSt08aEne2(volatile int a0) {
    int s = *(int*)(a0 + 0x164);
    D_0062A894 = 0;
    *(int*)(s + 0xB0) = (int)D_004CCB20;
    while (1) {
        _ACTWait(1);
    }
}

extern int *D_004CCB60[];
extern void actSt05eWaterSwitch(void);

void func_00220A38(volatile int a0) {
    DoorSub *obj = *(DoorSub **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CCB60[1] = (int *)actSt05eWaterSwitch;
    obj->field_B0 = 0;
    obj->field_B4 = (void *)D_004CCB60;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int D_00629DE4;
extern int D_00629DE8;
extern void RequestStageChange(int a0, int a1, int a2, float a3, float a4);

void actSt08aEnemy1(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_00178DB0(0xDA) == 0 || func_00178DB0(0xDB) == 0 ||
           func_00178DB0(0xDC) == 0 || func_00178DB0(0xCF) == 0) {
        _ACTWait(1);
    }
    RequestStageChange(8, D_00629DE4, D_00629DE8, 2.0f, 8.0f);
}

void actSt08aEnemy2(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aEnemy3(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aEnemy4(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aIntro(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aInit(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aDoorMain(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aDoorSwitch(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aIntroChk(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_00178DB0(0xEA) == 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(3, 1);
}

void func_00220BD0(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_00178DB0(0xEA) == 0 || func_00178DB0(0xEB) == 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(4, 1);
}

void func_00220C28(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00220C38(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00220C48(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00220C58(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00220C68(int a0) {
    int buf[4];
    buf[0] = a0;
}
