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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpTorchLightOff);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSetCageVelocityFriction);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayMotDir);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpDoorTypeUpUp);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSekizou);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", _SCPBoySupportGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", _SCPMoveCharactorByWay_Cancel);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSekizouCheckPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpWakeupEnemyOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSleepEnemyOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSleepSpiderGroupOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpWakeupSpiderGroupOne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpKillSpiderGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", preload);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpDispOffAllWithKind);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpDispOnAllWithKind);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpActivateAllWithKind);
