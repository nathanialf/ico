#include "common.h"

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1E30[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void func_0021F7A8(void);
extern void gflagInit(int a0);

void actSt05cDoorDownChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xBB) != 0 || func_0017B230(0xBD) != 0) {
        gflagInit(0x407);
    } else {
        D_004D1E30[1] = (int)func_0021F7A8;
        gobj->unkB4 = D_004D1E30;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void gflagInit(int a0);

void actSt04rDoorChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xBE)) {
        gflagInit(0x4A3);
    }
}

void actSt04rDoor2Chk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xBF)) {
        gflagInit(0x4A4);
    }
}

extern void stage_KillPlayBgAnimation(int,int,int);

void actSt05cSolarXL(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1);
 if(func_0017B230(0x91) && !func_0017B230(0x9B)){ stage_KillPlayBgAnimation(0xE1,0,-1); }
 if(func_0017B230(0x91)==0 || func_0017B230(0x9B)){ stage_KillPlayBgAnimation(0xE1,0,0); } }

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern int actSt25aQueenDeadChk(int a0);

void actSt05cWaterXL(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x44A));
 while(func_0017B230(0xC8)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x44A)); }

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt04rDoor(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0xC8)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0);
}

void actSt04rDoor2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0xC8) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
}

extern int D_004D19D0[];
extern int D_00631AE4;
extern int D_006325B8;
extern void WeaponGeo(int a0);
extern void gflagOff(int a0, int a1);
extern int ACTGame_ConnectHand(int a0);
extern int func_001538F8(void);
extern void actSt05cDoorDownEvent(volatile int a0);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f);
extern void func_0017B258(int a0);

void actSt05cDoorDown(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xCC) != 0) {
        if (D_00631AE4 != 0) {
            gflagOff(D_00631AE4, 0);
            if (ACTGame_ConnectHand(D_00631AE4) == 0) {
                WeaponGeo(func_001538F8());
            }
        }
        func_0017B258(0x164);
        D_006325B8 = 0;
        actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
        D_004D19D0[1] = (int)actSt05cDoorDownEvent;
        gobj->unkB4 = D_004D19D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

typedef struct { char pad[0xC0]; void *f_B0; void *unkB4; } St05cBox;
extern int D_006325B4;
extern int D_004D1850[];
extern int *D_004D1890[];
extern void func_0021AA18(volatile int a0);

void actSt05cEne(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    *(int *)(gobj + 0xC0) = (int)D_004D1850;
    for (;;) {
        _ACTWait(1);
    }
}

void func_0021F060(volatile int a0) {
    St05cBox *obj = *(St05cBox **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D1890[1] = (int *)func_0021AA18;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004D1890;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D18B0[];
extern int *D_004D18F0[];
extern void func_0021AB40(volatile int a0);

void actSt05cEnemy1(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    *(int *)(gobj + 0xC0) = (int)D_004D18B0;
    for (;;) {
        _ACTWait(1);
    }
}

void func_0021F0E8(volatile int a0) {
    St05cBox *obj = *(St05cBox **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D18F0[1] = (int *)func_0021AB40;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004D18F0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D1910[];
extern int *D_004D1950[];
extern void func_0021AC68(volatile int a0);

void actSt05cEnemy2(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    *(int *)(gobj + 0xC0) = (int)D_004D1910;
    for (;;) {
        _ACTWait(1);
    }
}

void func_0021F170(volatile int a0) {
    St05cBox *obj = *(St05cBox **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D1950[1] = (int *)func_0021AC68;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004D1950;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_006339D8;
extern void actConte11Jimaku(float f);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern int func_0012AA80(int a0);
extern void func_0017B288(int a0);
extern void func_0017C9B0(int a0);
extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);

void actSt05cDoorDownEvent(volatile int a0) {
    func_0017B288(0xCC);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpPlayStart(0x1B, (int)&D_006339D8, 0, 1, 1);
    while (D_006339D8 == 0) { _ACTWait(1); }
    func_0017C9B0(7);
    actConte11Jimaku(6.0f);
    stage_KillPlayBgAnimation(0x103, 1, 0);
    while (func_0012AA80(0x103) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(7, D_00631AE4, 0, 2.0f, 8.0f);
}

void actSt05cDoorDownEffect(int x) {
    volatile int local = x;
}

void actSt05cEneChk(int x) {
    volatile int local = x;
}

void func_0021F2C8(int x) {
    volatile int local = x;
}

void func_0021F2D8(int x) {
    volatile int local = x;
}

void func_0021F2E8(int x) {
    volatile int local = x;
}

void func_0021F2F8(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st05c", func_0021F308);

INCLUDE_ASM("asm/nonmatchings/src/st05c", func_0021F350);

void func_0021F3A8(int x) {
    volatile int local = x;
}

