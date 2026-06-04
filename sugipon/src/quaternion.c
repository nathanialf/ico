#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", MultiCurrentQuaternion);

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void func_0010E148(void *a0, void *a1, void *a2);

void InvertCurrentQuaternion(void *a0) {
    void *p = &D_0065A5C0[D_00629E7C * 4];
    func_0010E148(p, p, a0);
}

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void RegularizeQuaternion(void *a0, void *a1);

void SetCurrentQuaternion(void) {
    void *p = &D_0065A5C0[D_00629E7C * 4];
    RegularizeQuaternion(p, p);
}

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void GetInverseQuaternion(void *a0, void *a1);

void RotCurrentQuaternionX(void *a0) {
    GetInverseQuaternion(&D_0065A5C0[D_00629E7C * 4], a0);
}

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void func_0010E448(void *a0, int a1);

void RotCurrentQuaternionY(int a0) {
    func_0010E448(&D_0065A5C0[D_00629E7C * 4], (short)a0);
}

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void func_0010E4E8(void *a0, int a1);

void RotCurrentQuaternionZ(int a0) {
    func_0010E4E8(&D_0065A5C0[D_00629E7C * 4], (short)a0);
}

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void func_0010E588(void *a0, int a1);

void PushQuaternion(int a0) {
    func_0010E588(&D_0065A5C0[D_00629E7C * 4], (short)a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", InitQuaternionDrive);

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void GetMatrixFromQuaternion(void *a0);

void SetIdentityQuaternion(void) {
    D_00629E7C = 0;
    GetMatrixFromQuaternion(D_0065A5C0);
}

extern void GetInverseQuaternion(void *a0, void *a1);
extern int D_002724B0[];

void GetMatrixFromQuaternion(void *a0) {
    GetInverseQuaternion(a0, D_002724B0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", getQuaternionFromMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetQuaternionFromMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", CopyQuaternion);

extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);

void GetInverseQuaternion(void *a0, void *a1) {
    MatrixDrive_TurnObjectMatrix(a0, a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", RegularizeQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetSlerpQuaternionNoRegularize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetSlerpQuaternion);

extern void GetSlerpQuaternion(void *a0);
extern void GetSlerpQuaternionNoRegularize(void *a0);

void GetCurrentQuaternion(void *a0) {
    GetSlerpQuaternion(a0);
    GetSlerpQuaternionNoRegularize(a0);
}

void *GetLastQuaternion(void) {
    return &D_0065A5C0[D_00629E7C * 4];
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_002724D0;  /* stride 0x4 */

/* end struct shapes */
