#include "common.h"






extern int D_00633D74;
extern int D_00633D64;
extern float D_006326E0;
extern char D_006D04B4[];
extern void chain_simulate_term_simple();
extern void actBoySupportBGBegin();
extern void GetRootMatrixByDObj(void *a0, char *outer);
extern int *D_00631AE4;
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", CameraSetCameraSet);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", CameraSetCameraSet_Default);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetRootPositionForCamera);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ico2camera_GetTargetPos);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ico2camera_GetGroupNearest);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", initMonitorCamera);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", monitorMonitorCamera);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ChaseCamera);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", CameraMove);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ReflectCameraSetBinary);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", InitIco2Camera);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetTargetOffset);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", SetCameraMatrix_Ico2);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ReadCameraSet);

int SetCameraZoomOffsetRatio(int *a0, int a1, int a2)
{
  int *p;
  return ((int *) (a0[1] + (a1 * 0x4C)))[0x48 / 4] + (a2 * 0x5C);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetCameraGroupCurrent);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetCameraGroupFromGObj);

void GetCameraGroupFromPosition(void) {}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", AddPluralCameraSet);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", InitPluralCameraSet);

void GetPluralCameraSet(int a0, int a1)
{
    if (a1 == D_00631AE4) {
        actBoySupportBGBegin(a0, a1);
    } else {
        GetRootMatrixByDObj(a0, a1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", MakeCameraSetBinary);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetSizeOfCameraSetBinary);

void SetCameraTargetPosition(int a0)
{
    register char *p = D_006D04B4;
    register int one __asm__("$3") = 1;
    int masked = a0 & 0xFF;
    *p = (char)one;
    if (masked == 0) {
        return;
    }
    chain_simulate_term_simple(masked);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001886F4);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001886F8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00188C98);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00188E30);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001897A8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189AC8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189B88);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189D68);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018A400);

void func_0018B098(float val) {
    D_006326E0 = val;
}

int func_0018B0A0(void) {
    return D_00633D64;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B0A8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B180);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B248);

void func_0018B2F8(void) {
    D_00633D74 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B300);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B3A8);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B620);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B668);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B700);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B738);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B880);

