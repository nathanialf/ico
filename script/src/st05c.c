#include "common.h"

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void gflagInit(int a0);
extern int D_004CCA40[];
extern void func_0021C7A0(void);
extern void BoxBarSoundOn(int a0, int a1);

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

void actSt05cDoorDownChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xBB) != 0 || func_00178DB0(0xBD) != 0) {
        gflagInit(0x404);
    } else {
        D_004CCA40[1] = (int)func_0021C7A0;
        gobj->unkB4 = D_004CCA40;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void gflagInit(int a0);

void actSt04rDoorChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xBE)) {
        gflagInit(0x49F);
    }
}

void actSt04rDoor2Chk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xBF)) {
        gflagInit(0x4A0);
    }
}

extern void stage_KillPlayBgAnimation(int,int,int);
void actSt05cSolarXL(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1);
 if(func_00178DB0(0x91) && !func_00178DB0(0x9B)){ stage_KillPlayBgAnimation(0xE0,0,-1); }
 if(func_00178DB0(0x91)==0 || func_00178DB0(0x9B)){ stage_KillPlayBgAnimation(0xE0,0,0); } }

extern int actSt25aQueenDeadChk(int a0);
void actSt05cWaterXL(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x447));
 while(func_00178DB0(0xC8)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x447)); }

extern void Generator_MaskOff(int a0);
void actSt04rDoor(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0xC8)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);

void actSt04rDoor2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0xC8) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
}

extern void func_00178DD8(int a0);
extern void gflagOff(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f);
extern int D_004CC5E0[];
extern int D_00629DE4;
extern int D_0062A898;
extern void actSt05cDoorDownEvent(volatile int a0);

void actSt05cDoorDown(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xCC) != 0) {
        if (D_00629DE4 != 0) {
            gflagOff(D_00629DE4, 0);
        }
        func_00178DD8(0x163);
        D_0062A898 = 0;
        actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
        D_004CC5E0[1] = (int)actSt05cDoorDownEvent;
        gobj->unkB4 = D_004CC5E0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_0062A894;
extern int D_004CC460[];

void actSt05cEne(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CC460;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xB0]; void *f_B0; void *unkB4; } St05cBox;
extern int *D_004CC4A0[];
extern void func_00217CF0(volatile int a0);
void func_0021C048(volatile int a0) {
    St05cBox *obj = *(St05cBox **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CC4A0[1] = (int *)func_00217CF0;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CC4A0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

extern int D_004CC4C0[];

void actSt05cEnemy1(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CC4C0;
    for (;;) {
        _ACTWait(1);
    }
}

extern int *D_004CC500[];
extern void func_00217E18(volatile int a0);
void func_0021C0D8(volatile int a0) {
    St05cBox *obj = *(St05cBox **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CC500[1] = (int *)func_00217E18;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CC500;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

extern int D_004CC520[];

void actSt05cEnemy2(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CC520;
    for (;;) {
        _ACTWait(1);
    }
}

extern int *D_004CC560[];
extern void func_00217F40(volatile int a0);
void func_0021C168(volatile int a0) {
    St05cBox *obj = *(St05cBox **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CC560[1] = (int *)func_00217F40;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CC560;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

#include "common.h"
extern void func_00178E08(int a0);
extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void func_0017A0F8(int a0);
extern void actConte11Jimaku(float f);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern int D_0062BCE0;
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void actSt05cDoorDownEvent(volatile int a0) {
    func_00178E08(0xCC);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpPlayStart(0x1B, (int)&D_0062BCE0, 0, 1, 1);
    while (D_0062BCE0 == 0) { _ACTWait(1); }
    func_0017A0F8(7);
    actConte11Jimaku(6.0f);
    stage_KillPlayBgAnimation(0x102, 1, 0);
    while (func_0012A958(0x102) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(7, D_00629DE4, D_00629DE8, 2.0f, 8.0f);
}

void actSt05cDoorDownEffect(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05cEneChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C2C0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C2D0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C2E0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C2F0(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void func_0021C300(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_00178DB0(0xA3) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(3, 1);
}

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void func_0021C348(volatile int a0) {
    while (func_00178DB0(0xA3) == 0 || func_00178DB0(0xA4) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(4, 1);
}

void func_0021C3A0(int a0) {
    int buf[4];
    buf[0] = a0;
}
