#include "hand-camera.h"
#include "act-game.h"
#include "gv.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include <math.h>
#include <string.h>
#include <libvu0.h>
#include "main.h"
#include "include_asm.h"

/* the correction rate scaled by the frame budget */
static float handCameraRate; /* derived name */

/* the correction work area, two angles and the two limits
   SetLimitHandCameraCorrect writes */
static float handCameraWork[7]; /* derived name */

INCLUDE_ASM(RotateAccordingToStick_PatternThree);

static void SetCurrentInfo(void *eye, void *at);

static void HandyCamera_TargetMoveType(void *eye, void *at)
{
    float *p = handCameraWork;
    float q[4];
    float d[4];
    float m[16];
    float q2[4];
    float v0[4];
    float v1[4];
    float n[4];
    float q3[4];

    sceVu0SubVector(d, at, eye);

    SetIdentityQuaternion(q);

    SetIdentityQuaternion(q2);
    SetQuaternionByAxisRotate(q2, -(p[1] * 32768.0f / 3.1415927f), 0.0f, 1.0f, 0.0f);
    MultiQuaternion(q, q, q2);

    v0[0] = d[0];
    v0[1] = d[1];
    v0[2] = d[2];
    v1[0] = d[0];
    v1[1] = 0.0f;
    v1[2] = d[2];
    sceVu0OuterProduct(n, v0, v1);
    sceVu0Normalize(n, n);
    if (v0[1] < 0.0f)
        sceVu0ScaleVector(n, n, -1.0f);

    SetIdentityQuaternion(q3);
    SetQuaternionByAxisRotate(q3, -(p[0] * 32768.0f / 3.1415927f), n[0], n[1], n[2]);
    MultiQuaternion(q, q, q3);

    GetMatrixFromQuaternionPos(m, q, eye);

    d[3] = 0.0f;
    sceVu0ApplyMatrix(d, m, d);
    sceVu0AddVector(at, eye, d);
}

INCLUDE_ASM(ClearHandCameraCorrect);

INCLUDE_ASM(InitHandCameraCorrect);

INCLUDE_ASM(SetLimitHandCameraCorrect);

INCLUDE_ASM(HandCameraCorrect);
