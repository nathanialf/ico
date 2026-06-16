#include "common.h"

void actE3WarningChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x14B)==0){ _ACTWait(1); }
 _ACTWait(0x190); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actE3Title(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x14B)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x78); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);

void actE3TitleChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3TitleFrameChk);

void actE3Inst1Chk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

void actE3Capsule(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

void actE3CapsuleDemoCancel(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CapsuleDemo);

#include "common.h"
extern void func_00179F88(void);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void actConte11Jimaku(float f);
extern int actCreateSubThread(void *fn, int a1);
extern void actEnemySleep();
extern int D_0062BBF8;
extern int D_0062C290;
void actE3St13cInit(volatile int a0) {
    func_00179F88();
    func_00178DD8(0x145);
    scpPlayStart(2, &D_0062BBF8, 1, 1, 1);
    while (D_0062BBF8 == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(6.0f);
    D_0062C290 = actCreateSubThread(actEnemySleep, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFall);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFallChk);

#include "common.h"
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012A958(int a0);
extern int D_004CB6C0[];
extern int D_0062A894;
void actE3CageFallDemo(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x146);
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x31F, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)D_004CB6C0, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)D_004CB6C0, 1);
    while (func_0012A958(0x31F) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int,int,int);
extern int func_0012A958(int a0);
extern int D_0062A894;
void actE3CageFallEffect(volatile int a0){
 lt_fade_status(0x33); func_00178DD8(0x14A); D_0062A894=1; _ACTWait(0x78);
 stage_KillPlayBgAnimation(0x320,1,0);
 while(func_0012A958(0x320)==0) _ACTWait(1); _ACTWait(1); lt_fade_status(0x32); D_0062A894=0; }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int D_0062BBFC;
extern int D_00629DE4;
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
void actE3St09aSekizo(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    D_0062BBFC = 0;
    _ACTWait(1);
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0) { _ACTWait(1); }
    scpPlayStart(3, &D_0062BBFC, 1, 1, 0);
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int D_00629DE8;
extern int D_0062A894;
void actE3St09aSekizoChk(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    _ACTWait(0x1E);
    func_00178DD8(0x149);
    stage_KillPlayBgAnimation(0xA0, 1, 0);
    while (func_0012A958(0xA0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
}

#include "common.h"
struct GateS { long long a, b; };
extern struct GateS D_00614440;
extern int actSt25aQueenTalkChk(int a0, int a1, void *a2, int a3, float f);
extern void func_00260568(void *a0, int a1, int a2);
extern void actSwordEffXL(int a0, int a1, void *a2, int a3);
extern void lt_fade_status(int a0);
extern void saveEditedDataBinary(void);
extern int D_00629DE8;
extern int D_0062A894;
void actE3GateChk(volatile int a0) {
    struct GateS buf1 = D_00614440;
    int buf2[4];
    actSt25aQueenTalkChk(D_00629DE8, 0, &buf1, 0, 100.0f);
    func_00260568(buf2, 0, 0x10);
    actSwordEffXL(D_00629DE8, 0x64, buf2, 0xB4);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    saveEditedDataBinary();
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3GateDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3GateJimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3St01bInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Warning);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Inst1);
