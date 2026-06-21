#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEnd);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04cDoorDownChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x101, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04lDoorChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cSolarXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04lDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cDoorDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEne);

typedef struct { long long q[8]; } Mtx64;
extern Mtx64 D_004CC120;
extern int D_00271C00[];
extern void func_00118A70(int *a0, int a1, void *a2);
extern void _SetCurrentMatrix(void *a0, int *a1);

void actSt04cEnemy1(void *a0) {
    int m[4];
    int i;
    func_00118A70(m, *(int *)((char *)*(void **)((char *)a0 + 0x15C) + 0xC), D_00271C00);
    m[1] = 0;
    _SetCurrentMatrix((char *)*(void **)((char *)a0 + 0x15C) + 0x510, m);
    for (i = 0; i < *(int *)((char *)*(void **)((char *)a0 + 0x15C) + 0x88); i++) {
        ((Mtx64 *)*(void **)((char *)*(void **)((char *)a0 + 0x15C) + 0x7CC))[i] = D_004CC120;
    }
}

#include "common.h"
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void _deleteStreamMotionManager(int *a0);
extern void debug_assertMessage();
extern int DeleteStreamMotionManager(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern int D_00629DE8;
extern int D_0060AE20[];
extern int D_00614650[];
extern int D_0062BC8C;
void actSt04cEnemy2(volatile int a0) {
    int i;
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (D_00629DE8 == 0 || scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) { _ACTWait(1); }
    _deleteStreamMotionManager(D_0060AE20);
    i = 0;
    while (DeleteStreamMotionManager() == 0) {
        i++;
        debug_assertMessage(D_00614650, i);
        _ACTWait(1);
    }
    scpPlayStart(0x1F, (int)&D_0062BC8C, 1, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cWaterXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cDoorDownEvent);

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern int D_00271240[];
extern int D_00629DE8;

void actSt04cDoorDownEffect(int arg0) {
    volatile int home;
    int n;
    long long *flags;

    home = arg0;
    while (func_00178DB0(0x7E) == 0) {
        _ACTWait(1);
    }
    n = 0;
    flags = (long long *) ((char *) *(int *) ((char *) D_00629DE8 + 0x164) + 0x20);
    *flags |= 8;
    for (;;) {
        n++;
        flags = (long long *) ((char *) *(int *) ((char *) D_00629DE8 + 0x164) + 0x20);
        if ((((*flags << 26) >> 32) & 1) == 0) {
            n = 0;
        }
        if (((0x3C - D_00271240[0]) / D_00271240[1]) * 3 < n) {
            iosOmBeforeFuncStandard(D_00629DE8, 0x65, D_00629DE8);
            n = 0;
        }
        _ACTWait(1);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEneChk);

#include "common.h"
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void func_0017A040(int a0);
extern void func_00178E08(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_0018A380(void);
extern int func_0012A958(int a0);
extern void func_0017A008(int a0);
extern int D_00629DE8;
extern int D_0062A894;
void actSt04cIntroChk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (func_00178DB0(0x7C) == 0 || scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_0017A040(0xD57);
    func_00178E08(0x165);
    _ACTWait(0x3C);
    func_00178DD8(0x8C);
    func_00178DD8(0x8D);
    stage_KillPlayBgAnimation(0xA2, 1, 0);
    func_0018A380();
    while (func_0012A958(0xA2) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    func_0017A008(0xD57);
}

extern void gflagInit(int a0);
void actSt04lDoorEvent(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_00178DB0(0x9B)==0){ stage_KillPlayBgAnimation(0xA3,0,0); stage_KillPlayBgAnimation(0xA4,0,0); } else { stage_KillPlayBgAnimation(0xA3,0,-1); stage_KillPlayBgAnimation(0xA4,0,-1); gflagInit(0x3C6); gflagInit(0x3C7); } }

void func_00215CD0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0xDC, 0, 0);
}

extern int func_00178DB0(int a0);

void func_00215D10(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9B) == 0) {
        stage_KillPlayBgAnimation(0xDD, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xDD, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215D70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215E30);

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void func_00215EA8(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x8D)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0);
}

void func_00215F48(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x8D)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }
