#include "common.h"

typedef struct { long long a, b; } WpData16;

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkC4;
} GObj__p4;


extern int func_0017B230(int a0);
extern void AddWayPointTop();
extern void stage_KillPlayBgAnimation();
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0F50[];
extern int D_004D0E10[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void func_00210DF0(volatile int a0);

void actSt02aInit(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x40) == 0) {
        D_004D0F50[1] = (int)func_00210DF0;
        gobj->unkC4 = D_004D0F50;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);

void actSt02aDoor(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x41)==0){ _ACTWait(1); }
 _ACTWait(0x74); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

void actSt02aDoorUpChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x41)==0){ _ACTWait(1); }
 _ACTWait(0x64); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

void actSt02aDoorDownChk(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x41)==0){ _ACTWait(1); }
 _ACTWait(0x82); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

void actSt02WaterFallBoySplashCheck(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_0017B230(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x73); Generator_Call(a0);
}

void actSt02aWaterFallChk(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_0017B230(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x7D); Generator_Call(a0);
}

void actSt02aGondolaUp(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_0017B230(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x6E); Generator_Call(a0);
}

extern int D_004D0F70[];
extern void func_00210F20(volatile int a0);

void actSt02aGondolaDown(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x42) == 0) {
        D_004D0F70[1] = (int)func_00210F20;
        gobj->unkC4 = D_004D0F70;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0F90[];
extern void actSt02aBoxEvent2(volatile int a0);

void actSt02aBox(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    D_004D0F90[1] = (int)actSt02aBoxEvent2;
    gobj->unkC4 = D_004D0F90;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

void actSt02aGondola(void) {}

void actSt02aFence(int x) {
    volatile int local = x;
}

void actSt02aWaterFall(int x) {
    volatile int local = x;
}

extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004D0FB0[];
extern int D_00631AE8;
extern void actSt02aEne(volatile int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt02aBoxEvent2(volatile int a0) {
    GObj__p4 *obj = *(GObj__p4 **)(a0 + 0x164);
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    for (;;) {
        if (scpSleepSpiderGroupOne(D_00631AE8, 0x1000000) != 0 && func_0017B230(0x42) != 0) break;
        _ACTWait(1);
    }
    AddWayPointTop(4, 1);
    D_004D0FB0[1] = (int)actSt02aEne;
    obj->unkC4 = D_004D0FB0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D0FD0[];

void actSt02aEne(volatile int a0) {
    GObj__p4 *obj = *(GObj__p4 **)(a0 + 0x164);
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    for (;;) {
        if (scpSleepSpiderGroupOne(D_00631AE8, 0x2000000) != 0 && func_0017B230(0x42) != 0) break;
        _ACTWait(1);
    }
    AddWayPointTop(4, 0);
    {
        int *p = D_004D0F50 + 32;
        p[1] = (int)actSt02aBoxEvent2;
        obj->unkC4 = p;
    }
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

void actSt02aEnemy1(void)
{
    if (func_0017B230(0x69) == 0) {
        AddWayPointTop(0x1A, 0);
        stage_KillPlayBgAnimation(0x55, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x55, 0, -1);
    }
}

extern int D_004D0FF0[];
extern int D_004D1010[];
extern char *D_00631AE4;
extern void actSt02aSekizo(volatile int a0);
extern void actSt02aWay(volatile int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);

void actSt02aEnemy2(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, (int)D_00631AE4, 200.0f) != 0) goto way;
    if (D_00631AE8 == 0) goto sekizo;
    if (scpSleepEnemyOne(a0, (int)D_00631AE8, 400.0f) == 0) goto sekizo;
way:
    stage_KillPlayBgAnimation(0x54, 0, 0);
    _ACTWait(0x3C);
    D_004D0FF0[1] = (int)actSt02aWay;
    gobj->unkC4 = D_004D0FF0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
    return;
sekizo:
    stage_KillPlayBgAnimation(0x53, 0, 0);
    D_004D1010[1] = (int)actSt02aSekizo;
    gobj->unkC4 = D_004D1010;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D1030[];
extern WpData16 D_0061BA10;
extern void actCreateSubThread(void *fn, int a1);
extern void actSt03tGene(void);
extern int func_0012AA80(int a0);
extern void func_0017E870(float a, float b, float c, float d);
extern int scpKillSpiderGroup(int a0, int a1);
extern void soundSeDefPitchSet(int a0);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);

void actSt02aSekizo(volatile int a0) {
    GObj__p4 *obj = *(GObj__p4 **)(a0 + 0x164);
    WpData16 buf;
    int r;
    while (scpKillSpiderGroup(a0, 0x1000000) == 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread((void *)actSt03tGene, 0x15);
    func_0017E870(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_KillPlayBgAnimation(0x53, 1, 0);
    buf = D_0061BA10;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    r = soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPitchSet(r);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012AA80(0x53) == 0) { _ACTWait(1); }
    _ACTWait(1);
    {
        int *p = D_004D0E10 + 136;
        p[1] = (int)actSt02aWay;
        obj->unkC4 = p;
    }
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWay);
ASM_LIT4_SLOT(D_006314F4, -1827.0f);
ASM_LIT4_SLOT(D_006314F8, 2285.0f);

extern long long D_0061BA40[];
extern char *D_00631AE4;
extern int DebugDisp1CollisionWithColor(void *obj, int kind);
extern void MatrixDrive_TurnObjectMatrix(void *a0, float *a1);
extern void scpDispOffAllWithKind(void *buf, int kind);
extern int scpWakeupEnemyOne(void *a, void *b, float f);

void actSt02aTakiWay(volatile int a0){
 long long buf[4]; long long buf2[2]; int idx;
 if(D_00631AE4==0) return;
 buf[0]=D_0061BA40[0]; buf[1]=D_0061BA40[1]; buf[2]=D_0061BA40[2]; buf[3]=D_0061BA40[3];
 for(;;){
  idx=DebugDisp1CollisionWithColor(D_00631AE4,0x23);
  MatrixDrive_TurnObjectMatrix(buf2,(float*)(*(int*)(*(char**)(D_00631AE4+0x15C)+0xC)+(idx<<6)+0x30));
  if(scpWakeupEnemyOne(&buf[0],buf2,100.0f)) scpDispOffAllWithKind(buf2,0x2F);
  _ACTWait(0xA);
  idx=DebugDisp1CollisionWithColor(D_00631AE4,0x23);
  MatrixDrive_TurnObjectMatrix(buf2,(float*)(*(int*)(*(char**)(D_00631AE4+0x15C)+0xC)+(idx<<6)+0x30));
  if(scpWakeupEnemyOne(&buf[2],buf2,100.0f)) scpDispOffAllWithKind(buf2,0x2F);
  _ACTWait(0xA);
 } }

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aSecretItem);

extern void *actSt25aQueenDeadChk(int a0);
extern void func_001E8EA8(void *a0);
extern void func_0017EA50(void *a0, float x, float y, float z);
extern void func_001BFFE8(void *a0);

void func_00211EC8(volatile int a0) {
    char *o = *(char **)(D_00631AE4 + 0x164);
    void *p;
    *(long long *)(o + 0x20) &= ~0x04000000;
    p = actSt25aQueenDeadChk(0x61A);
    *(int *)((char *)p + 0x16C) = 1;
    p = actSt25aQueenDeadChk(0x616);
    *(int *)((char *)p + 0x16C) = 0;
    p = actSt25aQueenDeadChk(0x61F);
    *(int *)((char *)p + 0x16C) = 0;
    p = actSt25aQueenDeadChk(0x620);
    *(int *)((char *)p + 0x16C) = 0;
    p = actSt25aQueenDeadChk(0x623);
    *(int *)((char *)p + 0x16C) = 0;
    func_001E8EA8(actSt25aQueenDeadChk(0x640));
    func_001E8EA8(actSt25aQueenDeadChk(0x641));
    func_001E8EA8(actSt25aQueenDeadChk(0x642));
    func_001E8EA8(actSt25aQueenDeadChk(0x643));
    stage_KillPlayBgAnimation(0x163, -1, -2);
    func_0017EA50(actSt25aQueenDeadChk(0x630), 0.0f, -200.0f, 0.0f);
    func_0017EA50(actSt25aQueenDeadChk(0x632), 0.0f, -200.0f, 0.0f);
    _ACTWait(5);
    func_001BFFE8(actSt25aQueenDeadChk(0x630));
    func_001BFFE8(actSt25aQueenDeadChk(0x632));
}

extern int D_004D1170[];
extern int D_00631AEC;
extern int D_006325B4;
extern int D_00633974;
extern void actSt03tSekizoEvent(volatile int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern void iosPadDevRead(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void soundSeVolSet(int a0);

void actSt02aDoorEvent(volatile int a0) {
    GObj__p4 *obj = *(GObj__p4 **)(a0 + 0x164);
    scpPlayStart(0x55, &D_00633974, 1, 1, 1);
    while (D_00633974 == 0) { _ACTWait(1); }
    _ACTWait(0x10);
    stage_KillPlayBgAnimation(0x57, 1, 0);
    func_0017B258(0x6A);
    while (func_0012AB50(0x57, 0x95, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x10);
    _ACTWait(0x78);
    if (D_00633974 != 0) {
        soundSeVolSet(D_00633974);
    }
    lt_fade_status(0x32);
    D_006325B4 = 0;
    scpActivateAllWithKind();
    D_004D1170[1] = (int)actSt03tSekizoEvent;
    obj->unkC4 = D_004D1170;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D1190[];
extern int D_00633978;
extern void func_0017B288(int a0);

void actSt02aDoorUpEffect(volatile int a0) {
    GObj__p4 *obj = *(GObj__p4 **)(a0 + 0x164);
    scpPlayStart(0x55, &D_00633978, 1, 1, 1);
    while (D_00633978 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x57, 1, 0x96);
    func_0017B288(0x6A);
    while (func_0012AB50(0x57, 0x12C, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x10);
    _ACTWait(0x78);
    if (D_00633978 != 0) {
        soundSeVolSet(D_00633978);
    }
    lt_fade_status(0x32);
    D_006325B4 = 0;
    scpActivateAllWithKind();
    D_004D1190[1] = (int)actSt03tSekizoEvent;
    obj->unkC4 = D_004D1190;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

