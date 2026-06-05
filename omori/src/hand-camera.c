#include "common.h"

extern void func_00240008(void *a0, void *a1, void *a2);
extern float func_0023FE70(void *a0, void *a1);

void RotateAccordingToStick_PatternThree(void *a0, void *a1) {
    char buf[0x10];
    func_00240008(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    func_0023FE70(buf, buf);
}


void HandyCamera_TargetMoveType(void *a0, void *a1) {
    char buf[0x10];
    func_00240008(buf, a0, a1);
    func_0023FE70(buf, buf);
}

extern void MatrixDrive_GetTurnYAngleXZ(float a0);

void ClearHandCameraCorrect(void *a0, void *a1) {
    char buf[0x10];
    func_00240008(buf, a0, a1);
    MatrixDrive_GetTurnYAngleXZ(func_0023FE70(buf, buf));
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", InitHandCameraCorrect);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", SetLimitHandCameraCorrect);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", HandCameraCorrect);

extern int HandCameraCorrect(void);

int func_00191D90(void) {
    int r = HandCameraCorrect();
    return r < 0 ? -r : r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00191DB8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00191E30);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00191E78);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00191F18);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00191FD0);

extern void func_0023FE98(void *a0, void *a1);

void func_00192008(void *a0, void *a1, void *a2) {
    char buf[0x10];
    func_00240008(buf, a1, a2);
    func_0023FE98(a0, buf);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00192040);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_001920A8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_001920F0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00192160);
