#include "common.h"

extern int actSt25aQueenDeadChk(int a0);
extern void func_0012AB48(int a0, int *a1);

void scpLinkBGAtoLayoutedTarget(int a0, int a1) {
    int ret = actSt25aQueenDeadChk(a0);
    if (ret != 0) {
        int msg[2] = { ret, 0 };
        func_0012AB48(a1, msg);
    }
}

extern int actSt25aQueenDeadChk(int a0);
extern int DebugDisp1CollisionWithColor(int a0, int a1);
extern void func_0012ABB0(int a0, void *a1, int a2);
extern void debug_StdPrintfDummy(char *fmt);
extern char D_00554218[];
struct S { int a; int b; };
void scpLinkBGAtoLayoutedTargetSkelton(int a0, int a1, int a2){
 int ret = actSt25aQueenDeadChk(a0);
 if(ret != 0){ struct S copy; struct S pair;
  pair.a=ret; pair.b=DebugDisp1CollisionWithColor(ret,a1);
  copy=pair;
  if(copy.b==-1) debug_StdPrintfDummy(D_00554218);
  else func_0012ABB0(a2,&copy,1);
 } }

extern int actSt25aQueenDeadChk(int a0);
extern int DebugDisp1CollisionWithColor(int a0, int a1);
extern void func_0012ABB0(int a0, void *a1, int a2);
extern void debug_StdPrintfDummy(char *fmt);
extern char D_00554218[];
struct SVF { int a; int b; };
void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3){
  int ret = actSt25aQueenDeadChk(a0);
  if(ret != 0){ struct SVF copy; struct SVF pair;
   pair.a=ret; pair.b=DebugDisp1CollisionWithColor(ret,a1);
   copy=pair;
   if(copy.b==-1) debug_StdPrintfDummy(D_00554218);
   else func_0012ABB0(a2,&copy,a3);
  } }

extern int DebugDisp1CollisionWithColor(int a0, int a1);
extern void func_0012ABB0(int a0, void *a1, int a2);
extern void debug_StdPrintfDummy(char *fmt);
extern char D_00554218[];
struct SPMD { int a; int b; };
void scpPlayMotDir(int a0, int a1, int a2, int a3){
  int *ret = isysGObjSearchFromObjLayoutID(a0);
  if(ret != 0){ struct SPMD copy; struct SPMD pair;
   pair.a=(int)ret; pair.b=DebugDisp1CollisionWithColor((int)ret,a1);
   copy=pair;
   if(copy.b==-1) debug_StdPrintfDummy(D_00554218);
   else func_0012ABB0(a2,&copy,a3);
  } }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpGetWallCollision);

typedef struct {
    char _0[0xB4]; void *f_B4;
    char _B8[0x444 - 0xB8]; int f_444; float f_448;
} PlayMotState;
typedef struct { int f0; void *f4; int f8; int fC; } PlayMotMail;
extern PlayMotMail D_00286910[];
extern int func_00178DB0(int a0);
extern void GetRootMatrixTransOffset(float *dst, int outer);
extern void func_00179120(int a0, float *a1);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void func_0017C308();

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayMot);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayJump);

typedef struct { int f0; int *f4; int f8; int fC; int f10; } ScpEntry;
extern ScpEntry D_006C91F0[];

void scpPlayStart(int arg0, int *arg1, int arg2, int arg3, int arg4) {
    int i, ofs;
    if (arg1 != 0) {
        *arg1 = 0;
    }
    for (i = 0; i < 2; i++) {
        ofs = i * sizeof(ScpEntry);
        if (D_006C91F0[i].f0 == 0) {
            goto found;
        }
    }
    return;
found:
    *(int *)((char *)D_006C91F0 + ofs) = arg0;
    *(int *)((char *)D_006C91F0 + i * sizeof(ScpEntry) + 8) = arg3;
    *(int *)((char *)D_006C91F0 + i * sizeof(ScpEntry) + 12) = arg2;
    *(int *)((char *)D_006C91F0 + i * sizeof(ScpEntry) + 0x10) = arg4;
    *(int *)((char *)D_006C91F0 + i * sizeof(ScpEntry) + 4) = (int)arg1;
}


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

int scpIsTorchLightOn(int a0) {
    int ret1 = actSt25aQueenDeadChk(a0);
    int *ret2 = (int *)actSt25aQueenDeadChk(0);
    ret2[0x16C / 4] = 1;
    return TorchGeo(ret1);
}

extern int *isysGObjSearchFromObjLayoutID(int x);
extern int Draw2DLineG(int *p);
extern int *isysGObjSearchFromObjKindID_next(int *p);

int *scpIsBombExplode(int x)
{
    int *p = isysGObjSearchFromObjLayoutID(x);
    if (p != 0) {
        do {
            if (Draw2DLineG(p) != 0) {
                return p;
            }
            p = isysGObjSearchFromObjKindID_next(p);
        } while (p != 0);
    }
    return 0;
}

extern float MoveRotObjectWithHoldPoint(int a0);
extern void debug_StdPrintfDummy(char *fmt);
extern char D_00554188[];

float scpSekizou(int a0) {
    int ret = actSt25aQueenDeadChk(a0);
    if (ret != 0) {
        return MoveRotObjectWithHoldPoint(ret);
    }
    debug_StdPrintfDummy(D_00554188);
    return 0.0f;
}

extern int actSt25aQueenDeadChk(int a0);
extern int ExecRotObjectMoveStartReaction(int a0);
extern void debug_StdPrintfDummy(char *fmt);
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
 debug_StdPrintfDummy(D_005541D0);
 return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpTransLinear);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpRotateLinear);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpTriggerPosBall);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpTriggerBall);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSleepSpiderGroupOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpWakeupSpiderGroupOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpKillSpiderGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpTriggerPosBox);

void scpEffectStart(int a0, int a1) {
    int buf[4];
    GetMatrixFromQuaternion(buf);
    SetParticleEffectUpperLimit(a1, a0, buf);
}

extern void iosOmSendMail(int *a0, int a1, int *a2);

void scpDispOnAllWithKind(void) {
    int *o = isysGObjSearchFromObjLayoutID(4);
    if (o != 0) {
        do {
            iosOmSendMail(o, 0x20, o);
            o = isysGObjSearchFromObjKindID_next(o);
        } while (o != 0);
    }
    o = isysGObjSearchFromObjLayoutID(0x3C);
    if (o != 0) {
        do {
            iosOmSendMail(o, 0x20, o);
            o = isysGObjSearchFromObjKindID_next(o);
        } while (o != 0);
    }
}

extern void iosOmSendMail(int *a0, int a1, int *a2);

void scpActivateAllWithKind(void) {
    int *o = isysGObjSearchFromObjLayoutID(4);
    if (o != 0) {
        do {
            iosOmSendMail(o, 0x1F, o);
            o = isysGObjSearchFromObjKindID_next(o);
        } while (o != 0);
    }
    o = isysGObjSearchFromObjLayoutID(0x3C);
    if (o != 0) {
        do {
            iosOmSendMail(o, 0x1F, o);
            o = isysGObjSearchFromObjKindID_next(o);
        } while (o != 0);
    }
}
