#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", SetWSMatrix);

extern int D_006C9F60[];
extern void SetWSMatrix(int *a0, int a1);
extern void func_00188D60(int *a0);

void ConvertCameraSet(void) {
    SetWSMatrix(D_006C9F60, 0);
    func_00188D60(D_006C9F60);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", MakeCameraMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", CameraEditManual);

extern int D_0062AFF8;
extern float D_006C9F74[];
extern void func_0018A0F0(int a0, int a1, int a2);

void DebugCameraManual(int a0, int a1, int a2, int a3, int a4) {
    *(float *)a3 = D_006C9F74[0];
    *(float *)a4 = (float)D_0062AFF8 / 100.0f;
    func_0018A0F0(a0, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", DebugCameraSemiAuto);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", BackToGameCamera);

extern int D_006C9FA0[];
extern int D_0062AA14;

void GetCameraInfomationFromGlobalPosition(void) {
    if (D_006C9FA0[2] < 4) {
        D_006C9FA0[0] = D_0062AA14;
        D_006C9FA0[2] = 0;
        D_006C9FA0[1] = 0;
    }
}

void InitCamera(int a0, int a1, int a2) {
    if (a2 >= D_006C9FA0[2]) {
        D_006C9FA0[0] = a0;
        D_006C9FA0[1] = a1;
        D_006C9FA0[2] = a2;
    }
}

extern int actBoyCall(void);
extern int isysGObjAddHead(int a0);
extern int D_00629DE4;

int SetCameraMatrix(void) {
    int v = actBoyCall();
    if (v == 0) {
        return D_00629DE4;
    }
    v = isysGObjAddHead(v);
    if (v != 0) {
        return v;
    }
    return D_00629DE4;
}

extern int D_0062C074;
extern int D_0062C078;

void Camctrl_ExitEveRock(int a0, int a1) {
    D_0062C074 = a0;
    D_0062C078 = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", Camctrl_SetTarget);


int GetCameraDefaultTargetGObj(void) {
    return D_0062C074;
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    short              f_12;  /* 0x12 */
    unsigned long long f_18;  /* 0x18 */
} S_006C9F60;

typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_006C9F80;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_006C9FA0;

typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_00287150;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00554C30;  /* stride 0x4 */

/* end struct shapes */
