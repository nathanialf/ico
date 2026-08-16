#include "common.h"

typedef struct ActB4Obj_st13b { char pad[0xC0]; int *unkB0; int *unkB4; } ActB4Obj_st13b;





extern int D_00631AE8;
extern void func_0017B258(int bit_idx);
extern int func_0017B230(int a0);
extern void func_0018CED0();
extern int *D_00631AE4;
extern int D_00633FAC;
extern void actSt25aQueenBefore(int *self);
extern void gflagOff();
extern int func_0012AA80(int key);
extern void stage_KillPlayBgAnimation();
extern void gflagInit();
extern void func_001C3270();
extern void _ACTWait();
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bFloor);

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actInitialize(int a0);

void actSt13bFloorChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x76)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }


void actSt13bConte02(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x76)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }


void actSt13bSekizoChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x76)==0){ _ACTWait(1); }
 _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D2A90[];
extern void actSt13bConte02Jimaku(volatile int a0);

void actSt13bSekizo2Chk(volatile int a0){
 int x=a0;
 ActB4Obj_st13b *gobj=(ActB4Obj_st13b*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x78)==0){
  D_004D2A90[1]=(int)actSt13bConte02Jimaku;
  gobj->unkB4=D_004D2A90;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
}


void actSt13bMeetAgain(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x79)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }


void actSt13bBoss(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x79)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }


void actConte10b(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x79) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

void actSt13bElevDown(int x) {
    volatile int local = x;
}

void actSt13bElevUp(volatile unsigned int self)
{
    volatile int local;
    stage_KillPlayBgAnimation(0x142, 1, 0);
    while (func_0012AA80(0x142) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_001C3270();
    _ACTWait(0x78);
    gflagInit(0x18A);
    gflagInit(0x18B);
    _ACTWait(0);
}

void actSt13bElevUpChk(volatile int unused)
{
    gflagOff(D_00631AE4, 0x1D0);
    actSt25aQueenBefore(D_00631AE4);
    gflagOff(D_00631AE4, 0x1D1);
    actSt25aQueenBefore(D_00631AE4);
    D_00633FAC = 1;
    _ACTWait(0);

}

extern long long D_0061BF80[];
extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);

void actSt13bSekizo(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_0061BF80[0];
    buf[1] = D_0061BF80[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

extern long long D_0061BF90[];

void actSt13bSekizo2(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_0061BF90[0];
    buf[1] = D_0061BF90[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt13bBossAfter(int x) {
    volatile int local = x;
}

void actSt13bStoneGirl(volatile int unused)
{
    stage_KillPlayBgAnimation(0x143, 1, 0);
    stage_KillPlayBgAnimation(0x144, 1, 0);
    func_0018CED0();
    while (func_0012AA80(0x144) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_00633FAC = 1;
    _ACTWait(0);

}

extern long long D_0061BFA0[];

void actSt13bExit(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_0061BFA0[0];
    buf[1] = D_0061BFA0[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt13bElev(int x) {
    volatile int local = x;
}

extern int D_006325B4;
extern void lt_fade_status(int a0);
extern int scpSleepEnemyOne(int a0, int *a1, float f);

void actSt13bDoor(volatile int a0) {
    while (scpSleepEnemyOne(a0, D_00631AE4, 100.0f) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    func_0017B258(0x73);
    D_006325B4 = 1;
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x140, 1, 0);
    while (func_0012AA80(0x140) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_006325B4 = 0;
}

void actBossTest(int x) {
    volatile int local = x;
}

extern void func_0017B288(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt13bConte02Jimaku(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (func_0017B230(0x9B) == 0 || scpSleepSpiderGroupOne(D_00631AE8, 0x4000000) == 0) {
        _ACTWait(1);
    }
    func_0017B288(0x166);
    func_0017B258(0x78);
    func_0017B258(0x79);
}

void actSt13bSekizo2Event(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x45) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

extern int actSt25aQueenDeadChk(int a0);
extern void func_0017C8C0(int a0);
extern void func_0017C8F8(int a0);

void actSt13bMeetAgainChk(volatile int a0){ int a; int b;
 if(D_00631AE8==0) _ACTWait(0);
 for(;;){
  if(scpSleepSpiderGroupOne(D_00631AE8,0x1000000)!=0 && scpSleepSpiderGroupOne(D_00631AE4,0x6000000)!=0) break;
  a = scpSleepSpiderGroupOne(D_00631AE8,0x1000000);
  b = scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x14B),0x1000000);
  if((a & b) != 0) break;
  _ACTWait(1);
 }
 lt_fade_status(0x33); D_006325B4 = 1; func_0017C8F8(0xD7D);
 func_0017B258(0x44); func_0017B258(0x46);
 stage_KillPlayBgAnimation(0x59,1,0);
 while(func_0012AA80(0x59)==0) _ACTWait(1); _ACTWait(1);
 D_006325B4 = 0; lt_fade_status(0x32); func_0017C8C0(0xD7D); }

