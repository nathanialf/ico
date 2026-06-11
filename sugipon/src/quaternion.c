#include "common.h"

extern float D_00628CAC;
extern float D_00628CB0;
extern float D_00628CB4;

/* parked: needs real matching. See tough_nuts/MultiCurrentQuaternion/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", MultiCurrentQuaternion);

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void func_0010E148(void *a0, void *a1, void *a2);

void InvertCurrentQuaternion(void *a0) {
    void *p = &D_0065A5C0[D_00629E7C * 4];
    func_0010E148(p, p, a0);
}

extern void RegularizeQuaternion(int a0, int a1);

void SetCurrentQuaternion(void) {
    void *p = &D_0065A5C0[D_00629E7C * 4];
    RegularizeQuaternion(p, p);
}

extern void GetInverseQuaternion(void *a0, void *a1);

void RotCurrentQuaternionX(void *a0) {
    GetInverseQuaternion(&D_0065A5C0[D_00629E7C * 4], a0);
}

extern void func_0010E448(void *a0, int a1);

void RotCurrentQuaternionY(int a0) {
    func_0010E448(&D_0065A5C0[D_00629E7C * 4], (short)a0);
}

extern void func_0010E4E8(void *a0, int a1);

void RotCurrentQuaternionZ(int a0) {
    func_0010E4E8(&D_0065A5C0[D_00629E7C * 4], (short)a0);
}

extern void func_0010E588(void *a0, int a1);

void PushQuaternion(int a0) {
    func_0010E588(&D_0065A5C0[D_00629E7C * 4], (short)a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", InitQuaternionDrive);

extern void GetMatrixFromQuaternion(void *a0);

void SetIdentityQuaternion(void) {
    D_00629E7C = 0;
    GetMatrixFromQuaternion(D_0065A5C0);
}

extern int D_002724B0[];

void GetMatrixFromQuaternion(void *a0) {
    GetInverseQuaternion(a0, D_002724B0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", getQuaternionFromMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetQuaternionFromMatrix);

extern void func_00118AF0(void *a0, void *a1);
extern void GetQuaternionFromMatrix(void *a0, void *a1);
void CopyQuaternion(void *a0, void *a1) {
    char local[0x40];
    register void *aa __asm__("$4");
    func_00118AF0(local, a1);
    aa = a0;
    __asm__ volatile ("daddu $2,$sp,$0" :: "r"(aa));
    GetQuaternionFromMatrix(aa, local);
}

extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);

void GetInverseQuaternion(void *a0, void *a1) {
    MatrixDrive_TurnObjectMatrix(a0, a1);
}

extern void _PushVu0Registers(int a0, int a1, float f);

void RegularizeQuaternion(int a0, int a1)
{
    GetInverseQuaternion(a0, a1);
    _PushVu0Registers(a0, a1, -1.0f);
}

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
