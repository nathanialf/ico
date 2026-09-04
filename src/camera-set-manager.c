#include "common.h"




extern int D_006D06C8[];
extern int D_006D0680[];
extern int D_006D06B8[];
extern int D_00633D90;
extern int D_00633D84;
extern int D_00633D88;

void CameraGetTargets(int *a0, int *a1) {
    *a0 = D_00633D84;
    *a1 = D_00633D88;
}

void CameraSetMode(int x) {
    D_00633D90 = x;
    D_006D06B8[0] = 0;
}

int func_0018CC10(void) {
    return D_00633D90;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-set-manager", CameraGetOtherObjOffset);

INCLUDE_ASM("asm/nonmatchings/src/camera-set-manager", func_0018CD00);

INCLUDE_ASM("asm/nonmatchings/src/camera-set-manager", func_0018CD98);

INCLUDE_ASM("asm/nonmatchings/src/camera-set-manager", func_0018CE40);

int *func_0018CEC0(void) {
    return D_006D0680;
}

extern char D_00633D9C;
extern char D_00633D8C;

void func_0018CED0(void) {
    D_00633D9C = 1;
}

void func_0018CEE0(void) {
    D_00633D8C = 1;
}

int InsertCamera_isEnable(void) {
    return D_006D06C8[0] < 2;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-set-manager", CameraSetCameraPosition);

void func_0018CF58(void) {}

