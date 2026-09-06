#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aInit);
extern char *D_00639EA8;
void actSt00aEnd(void) {
    if (D_00639EA8 != 0) {
        if (gflagChk(0x2A) == 0) {
            gflagOn(0x187);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aStairChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2DownChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1DownChk);
typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(int);          /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD4];           /* 0x00 */
    ActMail *mail;              /* 0xD4 */
} Act;
extern Act *actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void _ACTWait(int a0);
extern ActMail D_004F7E70[];
void actSt00aEneChk(int a0);

void actSt00aEne(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x2A) == 0) {
        D_004F7E70[0].func = actSt00aEneChk;
        self->mail = D_004F7E70;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt00aEnemy1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x28) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x32);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x1E);
    Generator_Call(a0);
    _ACTWait(0x1E);
    Generator_Call(a0);
}

void actSt00aEnemy2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x28) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xA0);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x1E);
    Generator_Call(a0);
}
typedef struct PObjGObj {
    /*0x00*/ char pad00[0x164];
    /*0x164*/ Act *act;
    /*0x168*/ char pad168[0x4];
    /*0x16C*/ int f16C;
} PObjGObj;
extern PObjGObj *scpSearchGobj(int a0);
extern ActMail D_004F7E90[];
void actSt00aStairChk(int a0);

void actSt00aStair(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x29) == 0) {
        scpSearchGobj(0x110)->f16C = 0;
        D_004F7E90[0].func = actSt00aStairChk;
        self->mail = D_004F7E90;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x111)->f16C = 0;
    }
}
extern ActMail D_004F7E50[];
void actSt00aAtr2Chk(volatile int a0);

void actSt00aAtr2(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x2A) == 0) {
        D_004F7E50[0].func = actSt00aAtr2Chk;
        self->mail = D_004F7E50;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern int scpTriggerFloorAttr(int a0, int a1);

void actSt00aAtr2Chk(volatile int a0) {
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(0x2A);
}
extern int D_00639EAC;
extern int D_0063BE74;
extern unsigned char D_0063BE78;
extern int D_0063C4F8;
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern int stage_CheckAnimationFinish(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);

void actSt00aStairChkSub(volatile int a0) {
    _ACTWait(0x5A);
    iosPadActRequest(D_00639EAC, 0x11);
    while (stage_CheckAnimationFinish(0x57) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    stage_SetAnimation(0x59, 1, 0);
    stage_SetAnimation(0x5A, 1, 0);
    D_0063BE74 = iosPadActRequest(D_00639EAC, 9);
    D_0063BE78 = 0x80;
    iosPadActVolumeSet(D_0063BE74, 0x80);
    _ACTWait(0x1F4);
    D_0063C4F8 = 1;
    _ACTWait(0);
}
void actSt00aDoor2Event(int x) {
    volatile int local = x;
}
extern long long D_006226B0[];
extern long long D_006226C0[];
extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

void actSt00aDoor2UpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006226B0[0]; long long v0b=D_006226C0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006226B0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006226C0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt00aDoor2DownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006226C0[0]; long long v0b=D_006226B0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006226C0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006226B0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt00aDoor1Event(int x) {
    volatile int local = x;
}
extern long long D_006226E0[];
extern long long D_006226F0[];

void actSt00aDoor1UpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006226E0[0]; long long v0b=D_006226F0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006226E0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006226F0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt00aDoor1DownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006226F0[0]; long long v0b=D_006226E0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006226F0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006226E0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
