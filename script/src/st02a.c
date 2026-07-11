#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CBB60[];
extern void func_0020E210(volatile int a0);

void actSt02aInit(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x40) == 0) {
        D_004CBB60[1] = (int)func_0020E210;
        gobj->unkB4 = D_004CBB60;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


void actSt02aDoor(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x41)==0){ _ACTWait(1); }
 _ACTWait(0x74); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

void actSt02aDoorUpChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x41)==0){ _ACTWait(1); }
 _ACTWait(0x64); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern void Generator_MaskOff(int a0);
void actSt02aDoorDownChk(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x41)==0){ _ACTWait(1); }
 _ACTWait(0x82); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
void actSt02WaterFallBoySplashCheck(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x73); Generator_Call(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
void actSt02aWaterFallChk(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x7D); Generator_Call(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
void actSt02aGondolaUp(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x41) == 0) { _ACTWait(1); }
    _ACTWait(0x6E); Generator_Call(a0);
}

extern int D_004CBB80[];
extern void func_0020E340(volatile int a0);

void actSt02aGondolaDown(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x42) == 0) {
        D_004CBB80[1] = (int)func_0020E340;
        gobj->unkB4 = D_004CBB80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CBBA0[];
extern void actSt02aBoxEvent2(volatile int a0);

void actSt02aBox(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CBBA0[1] = (int)actSt02aBoxEvent2;
    gobj->unkB4 = D_004CBBA0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


void actSt02aGondola(void) {
}

void actSt02aFence(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt02aWaterFall(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void AddWayPointTop(int a0, int a1);
extern int D_00629DE8;
extern int D_004CBBC0[];
extern void actSt02aEne(volatile int a0);

void actSt02aBoxEvent2(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    for (;;) {
        if (scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) != 0 && func_00178DB0(0x42) != 0) break;
        _ACTWait(1);
    }
    AddWayPointTop(4, 1);
    D_004CBBC0[1] = (int)actSt02aEne;
    obj->unkB4 = D_004CBBC0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_004CBBE0[];

void actSt02aEne(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    for (;;) {
        if (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) != 0 && func_00178DB0(0x42) != 0) break;
        _ACTWait(1);
    }
    AddWayPointTop(4, 0);
    D_004CBBE0[1] = (int)actSt02aBoxEvent2;
    obj->unkB4 = D_004CBBE0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt02aEnemy1(void) {
    if (func_00178DB0(0x69) == 0) {
        AddWayPointTop(0x1A, 0);
        stage_KillPlayBgAnimation(0x54, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x54, 0, -1);
    }
}

extern int scpSleepEnemyOne(int a0, int a1, float f);
extern char *D_00629DE4;
extern int D_004CBC00[];
extern int D_004CBC20[];
extern void actSt02aWay(volatile int a0);
extern void actSt02aSekizo(volatile int a0);

void actSt02aEnemy2(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, (int)D_00629DE4, 200.0f) != 0) goto way;
    if (D_00629DE8 == 0) goto sekizo;
    if (scpSleepEnemyOne(a0, (int)D_00629DE8, 400.0f) == 0) goto sekizo;
way:
    stage_KillPlayBgAnimation(0x53, 0, 0);
    _ACTWait(0x3C);
    D_004CBC00[1] = (int)actSt02aWay;
    gobj->unkB4 = D_004CBC00;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
    return;
sekizo:
    stage_KillPlayBgAnimation(0x52, 0, 0);
    D_004CBC20[1] = (int)actSt02aSekizo;
    gobj->unkB4 = D_004CBC20;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


typedef struct { long long a, b; } WpData16;
extern WpData16 D_006145A0;
extern void actSt03tGene(void);
extern int scpKillSpiderGroup(int a0, int a1);
extern void actCreateSubThread(void *fn, int a1);
extern void func_0017BF50(float a, float b, float c, float d);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void soundSeDefPitchSet(int a0);
extern int func_0012A958(int a0);
extern volatile float D_006297D8;
extern volatile float D_006297DC;
extern int D_004CBC40[];

void actSt02aSekizo(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    WpData16 buf;
    int r;
    while (scpKillSpiderGroup(a0, 0x1000000) == 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread((void *)actSt03tGene, 0x15);
    func_0017BF50(D_006297D8, -1072.0f, D_006297DC, 100.0f);
    stage_KillPlayBgAnimation(0x52, 1, 0);
    buf = D_006145A0;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    r = soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPitchSet(r);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012A958(0x52) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_004CBC40[1] = (int)actSt02aWay;
    obj->unkB4 = D_004CBC40;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aWay);


extern int DebugDisp1CollisionWithColor(void *obj, int kind);
extern int scpWakeupEnemyOne(void *a, void *b, float f);
extern void MatrixDrive_TurnObjectMatrix(void *a0, float *a1);
extern void scpDispOffAllWithKind(void *buf, int kind);
extern void _ACTWait(int n);
extern char *D_00629DE4;
extern long long D_006145D0[];
void actSt02aTakiWay(volatile int a0){
 long long buf[4]; long long buf2[2]; int idx;
 if(D_00629DE4==0) return;
 buf[0]=D_006145D0[0]; buf[1]=D_006145D0[1]; buf[2]=D_006145D0[2]; buf[3]=D_006145D0[3];
 for(;;){
  idx=DebugDisp1CollisionWithColor(D_00629DE4,0x23);
  MatrixDrive_TurnObjectMatrix(buf2,(float*)(*(int*)(*(char**)(D_00629DE4+0x15C)+0xC)+(idx<<6)+0x30));
  if(scpWakeupEnemyOne(&buf[0],buf2,100.0f)) scpDispOffAllWithKind(buf2,0x2F);
  _ACTWait(0xA);
  idx=DebugDisp1CollisionWithColor(D_00629DE4,0x23);
  MatrixDrive_TurnObjectMatrix(buf2,(float*)(*(int*)(*(char**)(D_00629DE4+0x15C)+0xC)+(idx<<6)+0x30));
  if(scpWakeupEnemyOne(&buf[2],buf2,100.0f)) scpDispOffAllWithKind(buf2,0x2F);
  _ACTWait(0xA);
 } }

extern int actSt25aQueenDeadChk(int a0);
extern void func_001E6108(int a0);
extern void func_0017C130(int a0, float b, float c, float d);
extern void BoxGeo(int a0);

void actSt02aSecretItem(volatile int a0) {
    int *p = *(int **)((char *)D_00629DE4 + 0x164);
    *(long long *)((char *)p + 0x20) &= ~0x80000LL;
    ((int *)actSt25aQueenDeadChk(0x60C))[0x16C / 4] = 1;
    ((int *)actSt25aQueenDeadChk(0x608))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x611))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x612))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x615))[0x16C / 4] = 0;
    func_001E6108(actSt25aQueenDeadChk(0x636));
    func_001E6108(actSt25aQueenDeadChk(0x637));
    func_001E6108(actSt25aQueenDeadChk(0x638));
    func_001E6108(actSt25aQueenDeadChk(0x639));
    stage_KillPlayBgAnimation(0x162, -1, -2);
    func_0017C130(actSt25aQueenDeadChk(0x626), 0.0f, -200.0f, 0.0f);
    func_0017C130(actSt25aQueenDeadChk(0x628), 0.0f, -200.0f, 0.0f);
    _ACTWait(5);
    BoxGeo(actSt25aQueenDeadChk(0x626));
    BoxGeo(actSt25aQueenDeadChk(0x628));
}


extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int D_0062BC7C;
extern void func_00178DD8(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern int D_00629DEC;
extern void iosPadDevRead(int a0, int a1);
extern void soundSeVolSet(int a0);
extern int D_004CBD80[];
extern int D_0020FF58[];

void actSt02aDoorEvent(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    scpPlayStart(0x55, &D_0062BC7C, 1, 1, 1);
    while (D_0062BC7C == 0) { _ACTWait(1); }
    _ACTWait(0x10);
    stage_KillPlayBgAnimation(0x56, 1, 0);
    func_00178DD8(0x6A);
    while (func_0012AA28(0x56, 0x95, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    _ACTWait(0x78);
    if (D_0062BC7C != 0) {
        soundSeVolSet(D_0062BC7C);
    }
    D_004CBD80[1] = (int)D_0020FF58;
    obj->unkB4 = D_004CBD80;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_0062BC80;
extern void func_00178E08(int a0);
extern int D_004CBDA0[];

void actSt02aDoorUpEffect(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    scpPlayStart(0x55, &D_0062BC80, 1, 1, 1);
    while (D_0062BC80 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x56, 1, 0x96);
    func_00178E08(0x6A);
    while (func_0012AA28(0x56, 0x12C, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    _ACTWait(0x78);
    if (D_0062BC80 != 0) {
        soundSeVolSet(D_0062BC80);
    }
    D_004CBDA0[1] = (int)D_0020FF58;
    obj->unkB4 = D_004CBDA0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}



/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_006145D0;

/* end struct shapes */
