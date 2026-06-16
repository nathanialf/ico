#include "common.h"

extern int actSt25aQueenDeadChk(int a0);
extern void func_0012AB48(int a0, int *a1);

void scpTorchLightOn(int a0, int a1) {
    int ret = actSt25aQueenDeadChk(a0);
    if (ret != 0) {
        int msg[2] = { ret, 0 };
        func_0012AB48(a1, msg);
    }
}

extern int actSt25aQueenDeadChk(int a0);
extern int DebugDisp1CollisionWithColor(int a0, int a1);
extern void func_0012ABB0(int a0, void *a1, int a2);
extern void debug_assertMessage(char *fmt);
extern char D_00554218[];
struct S { int a; int b; };
void scpTorchLightOff(int a0, int a1, int a2){
 int ret = actSt25aQueenDeadChk(a0);
 if(ret != 0){ struct S copy; struct S pair;
  pair.a=ret; pair.b=DebugDisp1CollisionWithColor(ret,a1);
  copy=pair;
  if(copy.b==-1) debug_assertMessage(D_00554218);
  else func_0012ABB0(a2,&copy,1);
 } }

extern int actSt25aQueenDeadChk(int a0);
extern int DebugDisp1CollisionWithColor(int a0, int a1);
extern void func_0012ABB0(int a0, void *a1, int a2);
extern void debug_assertMessage(char *fmt);
extern char D_00554218[];
struct SVF { int a; int b; };
void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3){
  int ret = actSt25aQueenDeadChk(a0);
  if(ret != 0){ struct SVF copy; struct SVF pair;
   pair.a=ret; pair.b=DebugDisp1CollisionWithColor(ret,a1);
   copy=pair;
   if(copy.b==-1) debug_assertMessage(D_00554218);
   else func_0012ABB0(a2,&copy,a3);
  } }

extern int DebugDisp1CollisionWithColor(int a0, int a1);
extern void func_0012ABB0(int a0, void *a1, int a2);
extern void debug_assertMessage(char *fmt);
extern char D_00554218[];
struct SPMD { int a; int b; };
void scpPlayMotDir(int a0, int a1, int a2, int a3){
  int *ret = isysGObjSearchFromObjLayoutID(a0);
  if(ret != 0){ struct SPMD copy; struct SPMD pair;
   pair.a=(int)ret; pair.b=DebugDisp1CollisionWithColor((int)ret,a1);
   copy=pair;
   if(copy.b==-1) debug_assertMessage(D_00554218);
   else func_0012ABB0(a2,&copy,a3);
  } }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayMotDirSmz);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayMot);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayJump);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayStart);

typedef struct { int f0; char pad[0x10]; } ScpEntry;
extern ScpEntry D_006C91F0[];

int scpPlayEnd(void) {
    int count = 0;
    int i;
    for (i = 0; i < 2; i++) {
        if (D_006C91F0[i].f0) {
            count++;
        }
    }
    return count;
}

int scpTrans(void *a0, short a1) {
    char *p;
    if (a0 == 0) {
        goto fail;
    }
    p = *(char **)((char *)a0 + 0x2C);
    if (p != 0) {
        goto succ;
    }
fail:
    return 0;
succ:
    *(short *)(p + 0x44) = a1;
    return 1;
}

int scpTriggerBallTargetMan(int *a0) {
    if (a0 == 0) goto fail;
    a0 = (int *)a0[0xB];
    if (a0 == 0) goto fail;
    if (a0[0xA] != 0) goto succ;
fail:
    return 0;
succ:
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpDoorTypeUpDown);

extern int TorchGeo(int a0);

int scpDoorTypeUpUp(int a0) {
    int ret1 = actSt25aQueenDeadChk(a0);
    int *ret2 = (int *)actSt25aQueenDeadChk(0);
    ret2[0x16C / 4] = 1;
    return TorchGeo(ret1);
}

extern int *isysGObjSearchFromObjLayoutID(int x);
extern int Draw2DLineG(int *p);
extern int *isysGObjSearchFromObjKindID_begin(int *p);

int *scpSubAdpcmPlay(int x)
{
    int *p = isysGObjSearchFromObjLayoutID(x);
    if (p != 0) {
        do {
            if (Draw2DLineG(p) != 0) {
                return p;
            }
            p = isysGObjSearchFromObjKindID_begin(p);
        } while (p != 0);
    }
    return 0;
}

extern float MoveRotObjectWithHoldPoint(int a0);
extern void debug_assertMessage(char *fmt);
extern char D_00554188[];

float scpSekizou(int a0) {
    int ret = actSt25aQueenDeadChk(a0);
    if (ret != 0) {
        return MoveRotObjectWithHoldPoint(ret);
    }
    debug_assertMessage(D_00554188);
    return 0.0f;
}

extern int actSt25aQueenDeadChk(int a0);
extern int ExecRotObjectMoveStartReaction(int a0);
extern void debug_assertMessage(char *fmt);
extern char D_005541D0[];
int _SCPBoySupportGirl(int a0, int a1, int a2){
 int q = actSt25aQueenDeadChk(a0);
 if(q != 0){
  int e = ExecRotObjectMoveStartReaction(q);
  short A1 = (a1 << 15) / 0xB4;
  short A2 = (a2 << 15) / 0xB4;
  if(A2 < A1){ if(A1 < e || e < A2) return 1; return 0; }
  if(A1 < e && e < A2) return 1;
  return 0;
 }
 debug_assertMessage(D_005541D0);
 return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", _SCPMoveCharactorByWay_Cancel);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSekizouCheckPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpWakeupEnemyOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSleepEnemyOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSleepSpiderGroupOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpWakeupSpiderGroupOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpKillSpiderGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", preload);

void scpDispOffAllWithKind(int a0, int a1) {
    int buf[4];
    GetMatrixFromQuaternion(buf);
    SetParticleEffectUpperLimit(a1, a0, buf);
}

extern void iosOmBeforeFuncStandard(int *a0, int a1, int *a2);

void scpDispOnAllWithKind(void) {
    int *o = isysGObjSearchFromObjLayoutID(4);
    if (o != 0) {
        do {
            iosOmBeforeFuncStandard(o, 0x20, o);
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
    o = isysGObjSearchFromObjLayoutID(0x3C);
    if (o != 0) {
        do {
            iosOmBeforeFuncStandard(o, 0x20, o);
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
}

extern void iosOmBeforeFuncStandard(int *a0, int a1, int *a2);

void scpActivateAllWithKind(void) {
    int *o = isysGObjSearchFromObjLayoutID(4);
    if (o != 0) {
        do {
            iosOmBeforeFuncStandard(o, 0x1F, o);
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
    o = isysGObjSearchFromObjLayoutID(0x3C);
    if (o != 0) {
        do {
            iosOmBeforeFuncStandard(o, 0x1F, o);
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
}
