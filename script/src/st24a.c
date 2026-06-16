#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSwordChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSword);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231C58);

extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_006299BC;
extern float D_006299C0;
extern float D_006299C4;

void func_00231CC0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x1E, 0x45, 0x6D, 0x12, D_006299BC, D_006299C0, 1000.0f, D_006299BC, D_006299C0, D_006299C4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231D28);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231DF0);

void func_00231E68(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231E78);

void func_00231ED0(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231EE0);

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614D50[]; extern long long D_00614D60[];
void func_00231FC0(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614D50[0]; long long v0b=D_00614D60[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614D50[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614D60[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void func_002320A0(int a0) {
    int buf[4];
    buf[0] = a0;
}

#include "common.h"
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern void actCreateSubThread(void *fn, int a1);
extern void func_00232170();
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_0018A380(void);
extern int func_0012A958(int a0);
extern int D_00629DE8;
extern int D_00629DE4;
extern int D_0062BDF0;
extern int D_0062A894;
void func_002320B0(volatile int a0) {
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x20);
    if (D_00629DE8 != 0) {
        iosOmBeforeFuncStandard(D_00629DE8, 0x3A, D_00629DE4);
        actCreateSubThread(func_00232170, 0x15);
    }
    scpPlayStart(0x33, (int)&D_0062BDF0, 1, 1, 1);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x46, 1, 0);
    func_0018A380();
    while (func_0012A958(0x46) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
}

extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);
extern int D_00629DE8;
extern long long D_00614E10[];

void func_00232170(volatile unsigned int a0) {
    volatile int local;
    long long buf[2];
    buf[0] = D_00614E10[0];
    buf[1] = D_00614E10[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 2, 100.0f);
}

extern void actInitialize(int a0);
extern void _ACTWait(int a0);

void func_002321C0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_002321F0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00232298);

extern void backStageProcessMain(void);
extern void func_00178DD8(int a0);

void func_00232310(volatile int a0) {
    _ACTWait(1);
    backStageProcessMain();
    func_00178DD8(0x20);
}

extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void stage_KillPlayBgAnimation(int,int,int);
extern int func_0012A958(int a0);
extern int D_00629DE4;
extern int D_0062A894;
void func_00232340(volatile int a0){
 while(scpSleepSpiderGroupOne(D_00629DE4, 0x1000000)==0) _ACTWait(1);
 lt_fade_status(0x33); D_0062A894 = 1; func_00178DD8(0x22);
 stage_KillPlayBgAnimation(0x73,1,0);
 while(func_0012A958(0x73)==0) _ACTWait(1); _ACTWait(1);
 lt_fade_status(0x32); D_0062A894 = 0; }

extern int D_00629DE8;
extern int func_00178DB0(int a0);

void func_002323E0(void) {
    if (D_00629DE8 != 0) {
        if (func_00178DB0(0x39) == 0) {
            func_00178DD8(0x165);
        }
    }
}
