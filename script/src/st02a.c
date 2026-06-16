#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aInit);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aGondolaDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aBox);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aBoxEvent2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aEne);

extern int func_00178DB0(int a0);
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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aSekizo);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aSecretItem);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoorEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st02a", actSt02aDoorUpEffect);


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_006145D0;

/* end struct shapes */
