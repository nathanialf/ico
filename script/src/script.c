#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpTorchLightOn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpTorchLightOff);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSetCageVelocityFriction);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayMotDir);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayMotDirSmz);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayMot);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayJump);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayStart);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpPlayEnd);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/script", scpSubAdpcmPlay);

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
