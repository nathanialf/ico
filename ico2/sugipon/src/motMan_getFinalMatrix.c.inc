/* motMan_getFinalMatrix.c.inc -- #included by motionManager.c into one motionManager.o (PAL listing SRCFILE.TXT). */
inline int SetDirectMotionProgramInterpInfo(char *a0, int a1, float f)
{
    int n = GetSkeltonFocusNode(a0, a1);
    char *e = *(char **)(*(char **)(a0 + 0x15C) + 0x80C) + (n << 6);
    if (n < 0)
        return 0;
    *(float *)e = f;
    CopyQuaternion(e + 0x20, IdentityQuaternion);
    CopyQuaternion(e + 0x30, IdentityQuaternion);
    return 1;
}

inline int ResetMotionProgramInterpInfo(char *a0, int a1)
{
    int n = GetSkeltonFocusNode(a0, a1);
    char *e = *(char **)(*(char **)(a0 + 0x15C) + 0x80C) + (n << 6);
    if (n < 0)
        return 0;
    *(int *)e = 0;
    CopyQuaternion(e + 0x20, IdentityQuaternion);
    CopyQuaternion(e + 0x30, IdentityQuaternion);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", limitHPAngleAndSetB);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", avoidReverseInterpOnCurrentMatrix);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", avoidReverseInterpOnCurrentMatrixWithLimit);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", _getFinalMatrix);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", EditRotEmphasys);

static inline void getFinalMatrixCore(int id)
{
    char *e = D_0063B938 + id * 0x40;
    MatrixDrive_PushMatrixWithNoCopy();
    PushQuaternionWithNoCopy();
    _getFinalMatrix(id);
    CopyMatrix(*(char **)(*(char **)(D_0063B93C + 0x15C) + 0xC) + id * 0x40,
               (void *)MatrixDrive_GetMatrix());
    CopyQuaternion(D_0063C480 + id * 0x10, GetCurrentQuaternion());
    if (*(int *)(e + 0x30) != -1) {
        getFinalMatrixCore(*(int *)(e + 0x30));
    }
    MatrixDrive_PopMatrix();
    PopQuaternion();
    if (*(int *)(e + 0x34) != -1) {
        getFinalMatrixCore(*(int *)(e + 0x34));
    }
}

void getFinalMatrix(int id)
{
    char v[0x10];

    MatrixDrive_PushMatrix();
    _ApplyMatrix(v, MatrixDrive_GetMatrix(), ZUnitVector);
    SetQuaternionByAxisRotateV(D_004EC9E0, *(short *)(D_0063C490 + 0x50), v);
    SetQuaternionByAxisRotateV(
        D_004EC9F0, *(short *)(D_0063C490 + 0x50) * (*(float *)(D_0063C490 + 0x54) - 1.0f - 0.5f),
        v);
    SetQuaternionByAxisRotateV(
        D_004ECA00, *(short *)(D_0063C490 + 0x50) * (*(float *)(D_0063C490 + 0x54) - 1.0f + 0.5f),
        v);
    MatrixDrive_PopMatrix();
    getFinalMatrixCore(id);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", getFinalMatrixWithNaturalGeometry);

void _calcNaturalGeometry(int a0)
{
    char *elemA = D_0063B938 + a0 * 0x40;
    char *elemB = D_0063C4A4 + a0 * 0x20;
    int x;
    if (*(int *)(elemA + 0x38) != -1) {
        _ScaleVectorXYZ(D_007201E0, elemA + 0x10, D_0063B900);
        GetMatrixFromQuaternionPos(D_007201A0, elemB + 0x10, D_007201E0);
    } else {
        GetMatrixFromQuaternion(D_007201A0, elemB + 0x10);
    }
    x = MatrixDrive_GetMatrix();
    _MulMatrix((void *)x, MatrixDrive_GetLastMatrix(), D_007201A0);
}

static inline void pursueNaturalGeometry(int id)
{
    char *e = D_0063B938 + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);
    char *o;
    int m;
    MatrixDrive_PushMatrixWithNoCopy();
    _calcNaturalGeometry(id);
    o = D_0063C4A0 + id * 0x10;
    m = MatrixDrive_GetMatrix();
    CopyVector((void *)o, (char *)m + 0x30);
    if (child != -1) {
        pursueNaturalGeometry(child);
    }
    MatrixDrive_PopMatrix();
    if (next != -1) {
        pursueNaturalGeometry(next);
    }
}
