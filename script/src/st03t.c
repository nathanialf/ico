#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchLChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchLUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchR);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void *actSt25aQueenDeadChk(int a0);

void actSt03tSwitchRChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x63) == 0) {
        ((int *)actSt25aQueenDeadChk(0x62A))[0x16C / 4] = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchRUpChk);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actSt03tBoxA(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_00178DB0(0x6D)==0){
  _ACTWait(1);
 }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

void actSt03tBoxB(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_00178DB0(0x6D)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_006297E8;
extern float D_006297EC;

void actSt03tInit(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x6E, 0x57, 0, 0x12, 900.0f, D_006297E8, D_006297EC, 800.0f, D_006297E8, D_006297EC);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tGirlCam);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tWay);

void actSt03tEne(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006145B0[]; extern long long D_006145C0[];
void actSt03tGene(volatile int a0){
 long long b1[2]; long long b2[2];
 long long v0a=D_006145B0[0]; long long v0b=D_006145C0[0];
 int i;
 for(i=0;i<0x32;i++){
  switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006145B0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006145C0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  }
  _ACTWait(1);
 } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006145C0[]; extern long long D_006145B0[];
void actSt03tGirlCamEvent(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006145C0[0]; long long v0b=D_006145B0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006145C0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006145B0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tGirlCamStartChk);

#include "common.h"
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BC78;
extern int D_0062A894;
void actSt03tGirlCamEndChk(volatile int a0) {
    scpDispOnAllWithKind();
    func_00178DD8(0x69);
    scpPlayStart(0x5E, (int)&D_0062BC78, 1, 1, 1);
    while (D_0062BC78 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x54, 1, 0);
    stage_KillPlayBgAnimation(0x55, 1, 0);
    while (func_0012A958(0x55) == 0) { _ACTWait(1); }
    _ACTWait(1);
    AddWayPointTop(0x1A, 1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSekizoEvent);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
void actSt03tEneChk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x6C);
    func_00178DD8(0x6D);
}

void actSt03tWayOnChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tWayOffChk);


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_00614610;

/* end struct shapes */
