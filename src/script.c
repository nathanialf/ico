#include "common.h"

struct SPMD { int a; int b; };

struct SVF { int a; int b; };

typedef struct { int f0; int *f4; int f8; int fC; int f10; } ScpEntry;

struct S { int a; int b; };






extern void GetMatrixFromQuaternion(int a0);
extern int func_001E8B48(int a0, int a1, int a2);
extern float func_001EA108(int a0);
extern void debug_assertMessage();
extern int D_00559EA8[];
extern int actSt25aQueenDeadChk();
extern int isysGObjSearchFromObjKindID_begin();
extern int Draw2DLineG(char *self);
extern int isysGObjSearchFromObjLayoutID();
extern unsigned int D_0028A640[];
extern void _ACTWait();
extern int func_0017BB98();
extern int D_006CF910[];
INCLUDE_ASM("asm/nonmatchings/src/script", scpTorchLightOn);

extern char D_00559F38[];
extern int DebugDisp1CollisionWithColor(int a0, int a1);
extern int actSt25aQueenDeadChk__p4(int a0) __asm__("actSt25aQueenDeadChk");
extern void debug_assertMessage__p4(char *fmt) __asm__("debug_assertMessage");
extern void func_0012ACD8(int a0, void *a1, int a2);

void scpTorchLightOff(int a0, int a1, int a2){
 int ret = actSt25aQueenDeadChk__p4(a0);
 if(ret != 0){ struct S copy; struct S pair;
  pair.a=ret; pair.b=DebugDisp1CollisionWithColor(ret,a1);
  copy=pair;
  if(copy.b==-1) debug_assertMessage__p4(D_00559F38);
  else func_0012ACD8(a2,&copy,1);
 } }

void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3){
  int ret = actSt25aQueenDeadChk__p4(a0);
  if(ret != 0){ struct SVF copy; struct SVF pair;
   pair.a=ret; pair.b=DebugDisp1CollisionWithColor(ret,a1);
   copy=pair;
   if(copy.b==-1) debug_assertMessage__p4(D_00559F38);
   else func_0012ACD8(a2,&copy,a3);
  } }

extern int *isysGObjSearchFromObjLayoutID__p4(int x) __asm__("isysGObjSearchFromObjLayoutID");

void scpPlayMotDir(int a0, int a1, int a2, int a3){
  int *ret = isysGObjSearchFromObjLayoutID__p4(a0);
  if(ret != 0){ struct SPMD copy; struct SPMD pair;
   pair.a=(int)ret; pair.b=DebugDisp1CollisionWithColor((int)ret,a1);
   copy=pair;
   if(copy.b==-1) debug_assertMessage__p4(D_00559F38);
   else func_0012ACD8(a2,&copy,a3);
  } }

INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayMotDirSmz);

INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayMot);

INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayJump);

extern ScpEntry D_006CF910__p4[] __asm__("D_006CF910");

void scpPlayStart(int arg0, int *arg1, int arg2, int arg3, int arg4) {
    int i, ofs;
    if (arg1 != 0) {
        *arg1 = 0;
    }
    for (i = 0; i < 2; i++) {
        ofs = i * sizeof(ScpEntry);
        if (D_006CF910__p4[i].f0 == 0) {
            goto found;
        }
    }
    return;
found:
    *(int *)((char *)D_006CF910__p4 + ofs) = arg0;
    *(int *)((char *)D_006CF910__p4 + i * sizeof(ScpEntry) + 8) = arg3;
    *(int *)((char *)D_006CF910__p4 + i * sizeof(ScpEntry) + 12) = arg2;
    *(int *)((char *)D_006CF910__p4 + i * sizeof(ScpEntry) + 0x10) = arg4;
    *(int *)((char *)D_006CF910__p4 + i * sizeof(ScpEntry) + 4) = (int)arg1;
}

int scpPlayEnd(void)
{
    int count = 0;
    int *p = D_006CF910;
    int *end = (int *)((char *)p + 0x28);
    do {
        int v = *p;
        int next = count + 1;
        p = (int *)((char *)p + 0x14);
        if (v != 0) count = next;
    } while ((int)p < (int)end);
    return count;
}

int scpTrans(void *a0, short a1)
{
  short *p;
  if (a0 == 0)
  {
    goto out;
  }
  p = *((short **) (((char *) a0) + 0x2C));
  if (p == 0)
  {
    out:
    return 0;

    goto out;
  }
  *((short *) (((char *) p) + 0x44)) = a1;
  return 1;
}

int scpTriggerBallTargetMan(int *a0)
{
    int *p;
    int v0;
    if (a0 == 0) goto fail;
    p = (int *)a0[0xB];
    if (p == 0) goto fail;
    v0 = p[0xA];
    if (v0 != 0) goto succ;
fail:
    return 0;
succ:
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/script", func_0017D128);

void func_0017D1D0(volatile int a0)
{
    unsigned int i;
    short *p;

    _ACTWait(10);
    p = (short *)D_0028A640;
    for (i = 0; i < 7; i++) {
        if ((int)*p == ((int *)a0)[2]) goto found;
        p = (short *)((char *)p + 0x30);
    }
    return;
found:
    func_0017BB98(a0);
}

extern int TorchGeo(int a0);
extern int actSt25aQueenDeadChk__p4(int a0) __asm__("actSt25aQueenDeadChk");

int scpDoorTypeUpUp(int a0) {
    int ret1 = actSt25aQueenDeadChk__p4(a0);
    int *ret2 = (int *)actSt25aQueenDeadChk__p4(0);
    ret2[0x16C / 4] = 1;
    return TorchGeo(ret1);
}

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

float scpSekizou(void)
{
    int v = actSt25aQueenDeadChk();
    if (v != 0) {
        return func_001EA108(v);
    }
    debug_assertMessage(D_00559EA8);
    return 0.0f;
}

extern char D_00559EF0[];
extern int func_001EA128(int a0);

int _SCPBoySupportGirl(int a0, int a1, int a2){
 int q = actSt25aQueenDeadChk__p4(a0);
 if(q != 0){
  int e = func_001EA128(q);
  short A1 = (a1 << 15) / 0xB4;
  short A2 = (a2 << 15) / 0xB4;
  if(A2 < A1){ if(A1 < e || e < A2) return 1; return 0; }
  if(A1 < e && e < A2) return 1;
  return 0;
 }
 debug_assertMessage__p4(D_00559EF0);
 return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/script", _SCPMoveCharactorByWay_Cancel);

INCLUDE_ASM("asm/nonmatchings/src/script", scpSekizouCheckPoint);

INCLUDE_ASM("asm/nonmatchings/src/script", scpWakeupEnemyOne);

INCLUDE_ASM("asm/nonmatchings/src/script", scpSleepEnemyOne);

INCLUDE_ASM("asm/nonmatchings/src/script", scpSleepSpiderGroupOne);

INCLUDE_ASM("asm/nonmatchings/src/script", scpWakeupSpiderGroupOne);

INCLUDE_ASM("asm/nonmatchings/src/script", scpKillSpiderGroup);

INCLUDE_ASM("asm/nonmatchings/src/script", preload);

void scpDispOffAllWithKind(int a0, int a1)
{
    int buf[4];
    GetMatrixFromQuaternion(buf);
    func_001E8B48(a1, a0, buf);
}

extern void iosOmBeforeFuncStandard(int *a0, int a1, int *a2);
extern int *isysGObjSearchFromObjKindID_begin__p4(int *p) __asm__("isysGObjSearchFromObjKindID_begin");

void scpDispOnAllWithKind(void) {
    int *o = isysGObjSearchFromObjLayoutID__p4(4);
    if (o != 0) {
        do {
            iosOmBeforeFuncStandard(o, 0x20, o);
            o = isysGObjSearchFromObjKindID_begin__p4(o);
        } while (o != 0);
    }
    o = isysGObjSearchFromObjLayoutID__p4(0x3D);
    if (o != 0) {
        do {
            iosOmBeforeFuncStandard(o, 0x20, o);
            o = isysGObjSearchFromObjKindID_begin__p4(o);
        } while (o != 0);
    }
}

void scpActivateAllWithKind(void) {
    int *o = isysGObjSearchFromObjLayoutID__p4(4);
    if (o != 0) {
        do {
            iosOmBeforeFuncStandard(o, 0x1F, o);
            o = isysGObjSearchFromObjKindID_begin__p4(o);
        } while (o != 0);
    }
    o = isysGObjSearchFromObjLayoutID__p4(0x3D);
    if (o != 0) {
        do {
            iosOmBeforeFuncStandard(o, 0x1F, o);
            o = isysGObjSearchFromObjKindID_begin__p4(o);
        } while (o != 0);
    }
}

