#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", CameraSetCameraSet);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", CameraSetCameraSet_Default);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetRootPositionForCamera);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", ico2camera_GetTargetPos);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", ico2camera_GetGroupNearest);

extern int *D_0062A8F4;

int initMonitorCamera(void) {
    return *D_0062A8F4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", monitorMonitorCamera);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", ChaseCamera);

int CameraMove(int a0) {
    return D_0062A8F4[1] + a0 * 0x4C;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", ReflectCameraSetBinary);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", InitIco2Camera);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetTargetOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", SetCameraMatrix_Ico2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", ReadCameraSet);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", SetCameraZoomOffsetRatio);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetCameraGroupCurrent);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetCameraGroupFromGObj);

void GetCameraGroupFromPosition(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", AddPluralCameraSet);

extern int D_00629C90;
extern unsigned char D_005EBC48[];
extern void AddPluralCameraSet(int a0);

extern int D_005EBC48_arr[][0x64] __asm__("D_005EBC48");
void InitPluralCameraSet(void) {
    AddPluralCameraSet(D_005EBC48_arr[D_00629C90][0x46]);
}

extern int D_00629DE4;
extern void actBoySupportBGBegin(void *a0, int a1);
extern void GetRootMatrixByDObj(void *a0, int a1);

void GetPluralCameraSet(void *a0, int a1) {
    if (a1 == D_00629DE4) {
        actBoySupportBGBegin(a0, a1);
        return;
    }
    GetRootMatrixByDObj(a0, a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", MakeCameraSetBinary);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", GetSizeOfCameraSetBinary);

extern unsigned char D_006C9D94[];
extern void chain_simulate_term_simple(void);

void SetCameraTargetPosition(void) {
    D_006C9D94[0] = 1;
    chain_simulate_term_simple();
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00185BF8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00186198);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00186330);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00186CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00186FC8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00187088);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00187268);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_001878E0);

extern float D_0062A9C0;

void func_00188578(float a0) {
    D_0062A9C0 = a0;
}

extern int D_0062C054;

int func_00188580(void) {
    return D_0062C054;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188588);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188660);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188728);

extern int D_0062C064;

void func_001887D8(void) {
    D_0062C064 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_001887E0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188888);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188B00);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188B48);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188BE0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188C18);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-ico2", func_00188D60);
