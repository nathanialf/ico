#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", SetWSMatrix);

extern int D_006C9F60[];
extern void SetWSMatrix(int *a0, int a1);
extern void func_00188D60(int *a0);

void ConvertCameraSet(void) {
    SetWSMatrix(D_006C9F60, 0);
    func_00188D60(D_006C9F60);
}

extern float SetLimitHandCameraCorrect(int *a0, int *a1, int *a2, float t);
extern void GetRootMatrixByDObj(void *buf, int obj);
extern void func_00188C18(int *a0, void *a1);
extern int D_006C9F80[];
extern int D_0062C074;

void MakeCameraMatrix(void) {
    if (D_006C9F80[6] != 0) {
        if (SetLimitHandCameraCorrect(D_006C9F60, D_006C9F60, D_006C9F80, 50.0f) < 1.0f) {
            D_006C9F80[6] = 0;
        }
    } else {
        float buf[10];
        SetWSMatrix(D_006C9F60, 1);
        buf[0] = ((float *)D_006C9F60)[0];
        buf[1] = ((float *)D_006C9F60)[1];
        buf[2] = ((float *)D_006C9F60)[2];
        buf[8] = ((float *)D_006C9F60)[5];
        GetRootMatrixByDObj(&buf[4], D_0062C074);
        func_00188C18(D_006C9F60, buf);
    }
    func_00188D60(D_006C9F60);
}

extern void func_00260568(void *, int, int);
extern void func_0023FED0(void *, void *);
extern void MatrixDrive_TurnObjectMatrix(void *, void *);
extern void func_0023FDD8(void *, void *, void *);
extern void func_00240038(void *, void *, float);
extern void GetRootMatrixByDObj(void *, int);
extern float ClearHandCameraCorrect(void *, void *);
extern void func_0023FFF0(void *, void *, void *);
extern void func_00188B48(void *, void *, float);
extern char *D_00629C70;
extern int D_0062AA14;
extern float D_0062C088;

void CameraEditManual(void) {
    char buf[0x80];
    float f20v;
    func_00260568(buf, 0, 0x10);
    *(float *)(buf + 8) = 1.0f;
    func_0023FED0(buf + 0x20, D_00629C70 + 0x80);
    MatrixDrive_TurnObjectMatrix(buf + 0x70, D_00629C70 + 0xB0);
    *(int *)(buf + 0x7C) = 0;
    func_0023FDD8(buf + 0x10, buf + 0x20, buf + 0x70);
    func_00240038(buf + 0x10, buf + 0x10, -1.0f);
    GetRootMatrixByDObj(buf + 0x60, D_0062AA14);
    f20v = ClearHandCameraCorrect(buf + 0x10, buf + 0x60);
    *(int *)(buf + 0xC) = 0;
    func_0023FDD8(buf, buf + 0x20, buf);
    func_00240038(buf, buf, f20v);
    func_0023FFF0(buf, buf, buf + 0x10);
    func_00188B48(buf, buf + 0x10, D_0062C088);
}

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

typedef struct { unsigned long _0, _8, _10, _18; } CamTgt;
extern void func_00240008(void *, void *, void *);

void Camctrl_SetTarget(int a0, int a1) {
    char buf[0x30];
    if (a0 == 0) {
        *(int *)(buf + 0) = 0;
        *(int *)(buf + 4) = 0;
        *(int *)(buf + 8) = 0;
    } else {
        GetRootMatrixByDObj(buf + 0x10, a0);
        GetRootMatrixByDObj(buf + 0x20, a1);
        func_00240008(buf, buf + 0x20, buf + 0x10);
    }
    *(CamTgt *)D_006C9F80 = *(CamTgt *)D_006C9F60;
    func_0023FFF0(D_006C9F80, D_006C9F80, buf);
    D_006C9F80[6] = 1;
}


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
