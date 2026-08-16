#include "common.h"

extern int actInitialize(int a0);



extern void *D_00631AE8;
extern int func_0017B230(int a0);
extern void func_0017B258(int bit_idx);
extern void backStageProcessMain(void);
extern void _ACTWait();

typedef struct KSub {
    char pad[0xC4];
    int *unkC4;
} KSub;

struct SndBuf { long long a, b; };

extern int scpKillSpiderGroup(int a0, int a1);
extern void actCreateSubThread(void *fn, int a1);
extern void func_00235818(volatile int a0);
extern volatile float D_006316B8, D_006316BC, D_006316C0;
extern void func_0017E870(float a, float b, float c, float d);
extern void func_0012ABE0(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern struct SndBuf D_0061C220;
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void soundSeDefPitchSet(int a0);
extern int func_0012AA80(int a0);
extern void func_00234C08(volatile int a0);
extern int D_004D37B0[];
extern void BoxBarSoundOn(int a0, int a1);

INCLUDE_ASM("asm/nonmatchings/src/st24a", actSt24aSwordChk);

extern void *D_00631AEC;
extern int *D_00631AE4;
extern int scpSleepSpiderGroupOne(void *a0, int a1);
extern void iosPadDevRead(void *a0, int a1);
extern void AddWayPointTop(int a0, int a1);
extern int actSt25aQueenDeadChk(int a0);
extern void func_0018CED0(void);
extern void actSt24aSaku(volatile int a0);
extern int ACTEnvGetTest(void);
extern long long D_0061C260[];
extern void gflagOff(void *a0, int a1);
extern long long D_0061C270[];
extern void *ContinueCorrectPosition(void *a0);
extern void func_00243AE8(void *a0, void *a1, void *a2);
extern void gflagChk(void *a0, void *a1);
extern void func_0017B4E0(void *a0, int a1);
extern long long D_0061C280[];
extern void actSt25aQueenTalkChk(void *a0, int a1, int *buf, int a3, float f);
extern float D_006316C4, D_006316C8, D_006316CC, D_006316D0;
extern void func_0017C5B8(float f12, float f13, float f14, float f15, float f16, float f17);

INCLUDE_ASM("asm/nonmatchings/src/st24a", actSt24aSword);

INCLUDE_ASM("asm/nonmatchings/src/st24a", actSt24aSaku);

extern int D_004D3710[];
extern void func_002356D0(volatile int a0);

void func_002354B0(volatile int a0) {
    int x = a0;
    KSub *s = (KSub *)actInitialize(a0);
    _ACTWait(1);
    D_004D3710[1] = (int)func_002356D0;
    s->unkC4 = D_004D3710;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern float D_006316D4, D_006316D8, D_006316DC;
extern void func_0017BF78(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);

void func_00235518(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_0017BF78(a0, 0x1E, 0x45, 0x6E, 0x12, D_006316D4, D_006316D8, 1000.0f, D_006316D4, D_006316D8, D_006316DC);
}

extern int D_004D37D0[];
extern void actSt24aSword(volatile int a0);

void func_00235580(volatile int a0) {
    int x = a0;
    KSub *s = (KSub *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x1F) == 0) {
        *(int *)(actSt25aQueenDeadChk(0xDD) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x70, 0, 0);
        AddWayPointTop(3, 1);
        D_004D37D0[1] = (int)actSt24aSword;
        s->unkC4 = D_004D37D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        *(int *)(actSt25aQueenDeadChk(0xDC) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x70, 0, -1);
    }
}

extern int D_004D37F0[];
extern void func_00235908(volatile int a0);

void func_00235648(volatile int a0) {
    int x = a0;
    KSub *s = (KSub *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x20) == 0) {
        D_004D37F0[1] = (int)func_00235908;
        s->unkC4 = D_004D37F0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

void func_002356C0(int x) {
    volatile int local = x;
}

extern void scpPlayMotDirSmz(float a0, float a1, float a2, float a3, float a4, float a5);

void func_002356D0(volatile int a0)
{
    *(int *)(D_00631AE4[0x57] + 0x4E8) = 1;
    *(int *)(D_00631AE4[0x57] + 0x4E8) = 0;
    scpPlayMotDirSmz(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
}

void func_00235728(int x) {
    volatile int local = x;
}

extern long long D_0061C230[];
extern long long D_0061C240[];
extern void scpDispOffAllWithKind(int *buf, int a1);

void func_00235738(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061C230[0]; long long v0b=D_0061C240[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061C230[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061C240[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern long long D_0061C250[];

void func_00235818(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061C240[0]; long long v0b=D_0061C250[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061C240[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061C250[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void func_002358F8(int x) {
    volatile int local = x;
}

extern void lt_fade_status(int a0);
extern int D_006325B4;
extern void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int D_00633AE8;
extern void func_002359C8(volatile int a0);

void func_00235908(volatile int a0)
{
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_0017B258(0x20);
    if (D_00631AE8 != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x3B, D_00631AE4);
        actCreateSubThread(func_002359C8, 0x15);
    }
    scpPlayStart(0x33, &D_00633AE8, 1, 1, 1);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x46, 1, 0);
    func_0018CED0();
    while (func_0012AA80(0x46) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_006325B4 = 0;
}

extern long long D_0061C300[];

void func_002359C8(volatile int a0)
{
    long long buf[2];
    buf[0] = D_0061C300[0];
    buf[1] = D_0061C300[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 2, 100.0f);
}


void func_00235A18(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

extern volatile float D_006316E0, D_006316E4, D_006316E8;
extern void warpGirlInStage(float x, float y, float z);
extern int D_00633AEC;
extern int D_004D3810[];
extern void func_00235B68(int a0);

void func_00235A48(volatile int a0) {
    int x = a0;
    KSub *s = (KSub *)actInitialize(a0);
    _ACTWait(1);
    warpGirlInStage(D_006316E0, D_006316E4, D_006316E8);
    scpPlayStart(0x5C, &D_00633AEC, 1, 0, 1);
    if (func_0017B230(0x21) == 0) {
        D_004D3810[1] = (int)func_00235B68;
        s->unkC4 = D_004D3810;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D3830[];
extern void func_00235B98(volatile int a0);

void func_00235AF0(volatile int a0) {
    int x = a0;
    KSub *s = (KSub *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x22) == 0) {
        D_004D3830[1] = (int)func_00235B98;
        s->unkC4 = D_004D3830;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

void func_00235B68(int a0)
{
    volatile int local = a0;
    _ACTWait(1);
    backStageProcessMain();
    func_0017B258(0x20);
}


void func_00235B98(volatile int a0)
{
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x1000000) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_0017B258(0x22);
    stage_KillPlayBgAnimation(0x74, 1, 0);
    while (func_0012AA80(0x74) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_006325B4 = 0;
}

void func_00235C38(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x39) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

