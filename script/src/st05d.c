#include "common.h"

#include "common.h"
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int D_00629DE8;
void actSt05dDoor2(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpTriggerBall(a0, D_00629DE8, 200.0f) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    func_00178DD8(0xAA);
    _ACTWait(0xA);
    stage_KillPlayBgAnimation(0xC9, 1, 0);
    while (func_0012A958(0xC9) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern int D_004CC7C0[];
extern int D_00629DE4;
extern void actSt04lRope2Chk(void);

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

void actSt05dDoor2UpChk(int a0) {
    volatile int buf[4];
    GObj *s;
    buf[0] = a0;
    s = (GObj *)*(int *)(buf[0] + 0x164);
    while (scpSleepSpiderGroupOne(D_00629DE4, 0xA000000) != 0) {
        _ACTWait(1);
    }
    D_004CC7C0[1] = (int)actSt04lRope2Chk;
    s->unkB4 = D_004CC7C0;
    BoxBarSoundOn(buf[0], 0x189);
    _ACTWait(0);
}


void actSt05dDoor2DownChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dEne(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dEnemy1(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dEnemy2(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dDoor2Event(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dDoor2UpEffect(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dDoor2DownEffect(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dEneChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C570(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void *actSt25aQueenDeadChk(int a0);

void func_0021C580(volatile int a0) {
    void *p = actSt25aQueenDeadChk(0x407);
    *(int *)((char *)p + 0x16C) = 0;
}

extern void _ACTWait(int a0);
extern int scpIsTorchLightOn(int a0);
extern void func_00178DD8(int a0);

void func_0021C5A8(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x3FF) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xB8);
}

void func_0021C5F0(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x400) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xB9);
}

void func_0021C638(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x451) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xBA);
}

void func_0021C680(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x452) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xBB);
}

void func_0021C6C8(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x453) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xBE);
}

void func_0021C710(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x454) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xBF);
}

void func_0021C758(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x403) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xBC);
}

void func_0021C7A0(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpIsTorchLightOn(0x404) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xBD);
}

extern int D_0062BD08;
extern int func_00178DB0(int a0);
extern void soundSeVolSet(int a0);

void func_0021C7E8(void) {
    if (D_0062BD08 != 0) {
        if (func_00178DB0(0xD1) == 0) {
            soundSeVolSet(D_0062BD08);
        }
    }
}

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void SetWayGroupActive(int a0, int a1);

void func_0021C820(void) {
    if (func_00178DB0(0xF9) == 0) stage_KillPlayBgAnimation(0x12F, 0, 0); else stage_KillPlayBgAnimation(0x12F, 0, -1);
    if (func_00178DB0(0xFA) == 0) stage_KillPlayBgAnimation(0x130, 0, 0); else stage_KillPlayBgAnimation(0x130, 0, -1);
    if (func_00178DB0(0xFB) == 0) stage_KillPlayBgAnimation(0x131, 0, 0); else stage_KillPlayBgAnimation(0x131, 0, -1);
    if (func_00178DB0(0xFC) == 0) stage_KillPlayBgAnimation(0x132, 0, 0); else stage_KillPlayBgAnimation(0x132, 0, -1);
    if (func_00178DB0(0xFD) == 0) stage_KillPlayBgAnimation(0x133, 0, 0); else stage_KillPlayBgAnimation(0x133, 0, -1);
    if (func_00178DB0(0xFE) == 0) stage_KillPlayBgAnimation(0x134, 0, 0); else stage_KillPlayBgAnimation(0x134, 0, -1);
    if (func_00178DB0(0xFF) == 0) stage_KillPlayBgAnimation(0x135, 0, 0); else stage_KillPlayBgAnimation(0x135, 0, -1);
    if (func_00178DB0(0xE5) == 0) SetWayGroupActive(1, 0); else SetWayGroupActive(1, 1);
    if (func_00178DB0(0xEA) == 0) stage_KillPlayBgAnimation(0x126, 0, 0); else stage_KillPlayBgAnimation(0x126, 0, -1);
    if (func_00178DB0(0xEB) == 0) stage_KillPlayBgAnimation(0x127, 0, 0); else stage_KillPlayBgAnimation(0x127, 0, -1);
    if (func_00178DB0(0xE4) == 0) {
        *(int *)((char *)actSt25aQueenDeadChk(0x4FB) + 0x16C) = 0;
    }
}
