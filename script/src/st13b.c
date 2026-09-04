#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bFloor);

extern void Generator_Call(int a0);
void actSt13bFloorChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x76)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void actSt13bConte02(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x76)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

void actSt13bSekizoChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x76)==0){ _ACTWait(1); }
 _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

typedef struct ActB4Obj_st13b { char pad[0xB0]; int *unkB0; int *unkB4; } ActB4Obj_st13b;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CD620[];
extern void actSt13bConte02Jimaku(volatile int a0);
void actSt13bSekizo2Chk(volatile int a0){
 int x=a0;
 ActB4Obj_st13b *gobj=(ActB4Obj_st13b*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x78)==0){
  D_004CD620[1]=(int)actSt13bConte02Jimaku;
  gobj->unkB4=D_004CD620;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
}

void actSt13bMeetAgain(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x79)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void actSt13bBoss(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x79)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void actConte10b(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x79) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

void actSt13bElevDown(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int func_0012A958(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagInit(int a0);
extern void func_001C04E0(void);
void actSt13bElevUp(volatile int a0){
 stage_KillPlayBgAnimation(0x141, 1, 0);
 while(func_0012A958(0x141)==0) _ACTWait(1);
 _ACTWait(1); func_001C04E0(); _ACTWait(0x78);
 gflagInit(0x189); gflagInit(0x18A); _ACTWait(0);
}

extern int *D_00629DE4;
extern int D_0062C2AC;
extern void gflagOff(int *p, int n);
extern void actSt25aQueenBefore(int *p);
extern void _ACTWait(int x);

void actSt13bElevUpChk(volatile int unused)
{
    gflagOff(D_00629DE4, 0x1D0);
    actSt25aQueenBefore(D_00629DE4);
    gflagOff(D_00629DE4, 0x1D1);
    actSt25aQueenBefore(D_00629DE4);
    D_0062C2AC = 1;
    _ACTWait(0);

}

extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);
extern int D_00629DE8;
extern long long D_00614AA0[];

void actSt13bSekizo(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_00614AA0[0];
    buf[1] = D_00614AA0[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

extern long long D_00614AB0[];

void actSt13bSekizo2(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_00614AB0[0];
    buf[1] = D_00614AB0[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt13bBossAfter(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void func_0018A380(void);
void actSt13bStoneGirl(volatile int a0){
 stage_KillPlayBgAnimation(0x142,1,0); stage_KillPlayBgAnimation(0x143,1,0); func_0018A380();
 while(func_0012A958(0x143)==0) _ACTWait(1);
 _ACTWait(1); D_0062C2AC = 1; _ACTWait(0); }

extern long long D_00614AC0[];

void actSt13bExit(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_00614AC0[0];
    buf[1] = D_00614AC0[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt13bElev(int a0) {
    int buf[4];
    buf[0] = a0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int *a1, float f);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int *D_00629DE4;
extern int D_0062A894;
void actSt13bDoor(volatile int a0) {
    while (scpTriggerBall(a0, D_00629DE4, 100.0f) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    func_00178DD8(0x73);
    D_0062A894 = 1;
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x13F, 1, 0);
    while (func_0012A958(0x13F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
}

void actBossTest(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178E08(int a0);
extern void func_00178DD8(int a0);
void actSt13bConte02Jimaku(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (func_00178DB0(0x9B) == 0 || scpSleepSpiderGroupOne(D_00629DE8, 0x4000000) == 0) {
        _ACTWait(1);
    }
    func_00178E08(0x165);
    func_00178DD8(0x78);
    func_00178DD8(0x79);
}

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSt13bSekizo2Event(void) {
    if (D_00629DE8 == 0) return;
    if (func_00178DB0(0x45) != 0) return;
    func_00178DD8(0x165);
}

extern int actSt25aQueenDeadChk(int a0);
extern void lt_fade_status(int a0);
extern void scpSleepEnemyOne(int a0);
extern void scpWakeupEnemyOne(int a0);
extern int D_0062A894;
void actSt13bMeetAgainChk(volatile int a0){ int a; int b;
 if(D_00629DE8==0) _ACTWait(0);
 for(;;){
  if(scpSleepSpiderGroupOne(D_00629DE8,0x1000000)!=0 && scpSleepSpiderGroupOne(D_00629DE4,0x6000000)!=0) break;
  a = scpSleepSpiderGroupOne(D_00629DE8,0x1000000);
  b = scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x14A),0x1000000);
  if((a & b) != 0) break;
  _ACTWait(1);
 }
 lt_fade_status(0x33); D_0062A894 = 1; scpSleepEnemyOne(0xD57);
 func_00178DD8(0x44); func_00178DD8(0x46);
 stage_KillPlayBgAnimation(0x58,1,0);
 while(func_0012A958(0x58)==0) _ACTWait(1); _ACTWait(1);
 D_0062A894 = 0; lt_fade_status(0x32); scpWakeupEnemyOne(0xD57); }
