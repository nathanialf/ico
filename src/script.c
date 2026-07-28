#include "common.h"






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

INCLUDE_ASM("asm/nonmatchings/src/script", scpTorchLightOff);

INCLUDE_ASM("asm/nonmatchings/src/script", scpSetCageVelocityFriction);

INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayMotDir);

INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayMotDirSmz);

INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayMot);

INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayJump);

INCLUDE_ASM("asm/nonmatchings/src/script", scpPlayStart);

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

INCLUDE_ASM("asm/nonmatchings/src/script", scpDoorTypeUpUp);

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

INCLUDE_ASM("asm/nonmatchings/src/script", _SCPBoySupportGirl);

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

INCLUDE_ASM("asm/nonmatchings/src/script", scpDispOnAllWithKind);

INCLUDE_ASM("asm/nonmatchings/src/script", scpActivateAllWithKind);

