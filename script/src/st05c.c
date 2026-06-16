#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cDoorDownChk);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cDoorDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cDoorDownEvent);

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
