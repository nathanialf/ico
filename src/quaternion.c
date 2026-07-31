#include "common.h"







extern void MatrixDrive_TurnObjectMatrix();
extern char D_00276140[];
extern void func_0010E1F8();
extern void func_0010E158();
extern void func_0010E0B8();
extern int D_00660A40[];
extern void func_0010DDB8();
extern int D_00631B7C;
INCLUDE_ASM("asm/nonmatchings/src/quaternion", MultiCurrentQuaternion);

void InvertCurrentQuaternion(int a0)
{
    int *p = &D_00660A40[D_00631B7C * 4];
    func_0010DDB8(p, p, a0);
}

void SetCurrentQuaternion(void)
{
    int *p = &D_00660A40[D_00631B7C * 4];
    RegularizeQuaternion(p, p);
}

void RotCurrentQuaternionX(int a0)
{
    GetInverseQuaternion(&D_00660A40[D_00631B7C * 4], a0);
}

void RotCurrentQuaternionY(short a0)
{
    func_0010E0B8(&D_00660A40[D_00631B7C * 4], a0);
}

void RotCurrentQuaternionZ(short a0)
{
    func_0010E158(&D_00660A40[D_00631B7C * 4], a0);
}

void PushQuaternion(short a0)
{
    func_0010E1F8(&D_00660A40[D_00631B7C * 4], a0);
}

extern char D_00553E00[];
extern char D_00553E28[];
extern void SetIdentityQuaternion(void);
extern void debug_assertMessage(char *p);

void InitQuaternionDrive(void) {
    int v = D_00631B7C;
    if (v < 0) {
        debug_assertMessage(D_00553E00);
        SetIdentityQuaternion();
        v = D_00631B7C;
    }
    v++;
    D_00631B7C = v;
    if (v >= 0x40) {
        debug_assertMessage(D_00553E28);
        v = 0x3F;
        D_00631B7C = v;
    }
    {
        int idx = *(volatile int *)&D_00631B7C;
        GetInverseQuaternion(&D_00660A40[idx * 4], &D_00660A40[idx * 4 - 4]);
    }
}

void SetIdentityQuaternion(void)
{
    D_00631B7C = 0;
    GetMatrixFromQuaternion(D_00660A40);
}

void GetMatrixFromQuaternion(int a0)
{
    GetInverseQuaternion(a0, D_00276140);
}

extern char D_00275860[];
extern char D_00276150[];

void getQuaternionFromMatrix(char *a0, char *a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf11, 0x0($5)\n"
        "lqc2 $vf12, 0x0(%0)\n"
        "vmr32.w $vf14, $vf0\n"
        "vmr32.w $vf15, $vf0\n"
        "vmr32.w $vf16, $vf0\n"
        "vopmula.xyz $ACC, $vf11, $vf12\n"
        "vmadd.xyz $vf11, $vf0, $vf0\n"
        "vmulw.xyzw $vf11, $vf11, $vf12w\n"
        "vmul.xyz $vf13, $vf11, $vf11\n"
        "vopmula.xyz $ACC, $vf11, $vf11\n"
        "vmaddw.xyz $vf15, $vf11, $vf11w\n"
        "vmsubw.xyz $vf16, $vf11, $vf11w\n"
        "vopmula.xyz $ACC, $vf13, $vf12\n"
        "vmadd.xyz $vf17, $vf13, $vf12\n"
        "vopmula.xyz $ACC, $vf15, $vf12\n"
        "vmadd.xyz $vf15, $vf0, $vf0\n"
        "vsub.xyz $vf14, $vf12, $vf17\n"
        "vmove.y $vf17, $vf14\n"
        "vmove.y $vf14, $vf16\n"
        "vmove.y $vf16, $vf15\n"
        "vmove.y $vf15, $vf17\n"
        "vmove.z $vf17, $vf14\n"
        "vmove.z $vf14, $vf15\n"
        "vmove.z $vf15, $vf16\n"
        "vmove.z $vf16, $vf17\n"
        "sqc2 $vf14, 0x0($4)\n"
        "sqc2 $vf15, 0x10($4)\n"
        "sqc2 $vf16, 0x20($4)\n"
        ".set reorder\n"
        : : "r"(D_00276150) : "memory");
    MatrixDrive_TurnObjectMatrix(a0 + 0x30, D_00275860);
}

INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetQuaternionFromMatrix);

extern void GetQuaternionFromMatrix(void *a0, void *a1);
extern void func_001186C8(void *a0, void *a1);

void CopyQuaternion(void *a0, void *a1) {
    char local[0x40];
    register void *aa __asm__("$4");
    func_001186C8(local, a1);
    aa = a0;
    __asm__ volatile ("daddu $2,$sp,$0" :: "r"(aa));
    GetQuaternionFromMatrix(aa, local);
}

void GetInverseQuaternion(a0, a1, a2, a3)
int a0, a1, a2, a3;
{
    MatrixDrive_TurnObjectMatrix(a0, a1, a2, a3);
}

extern void _PushVu0Registers(int a0, int a1, float f);

void RegularizeQuaternion(int a0, int a1)
{
    GetInverseQuaternion(a0, a1);
    _PushVu0Registers(a0, a1, -1.0f);
}

extern void _InverseCurrentMatrix(void *a, void *b, float c);
extern float func_00117C20(float);

void GetSlerpQuaternionNoRegularize(void *a0) {
    register float d __asm__("$f12");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0(%1)\n"
        "lqc2 $vf15, 0x0(%1)\n"
        "vmul.xyzw $vf15, $vf14, $vf15\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "qmfc2.ni $2, $vf15\n"
        "mtc1 $2, $f12\n"
        ".set reorder\n"
        : "=f"(d) : "r"(a0) : "$2");
    _InverseCurrentMatrix(a0, a0, 1.0f / func_00117C20(d));
}

INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetSlerpQuaternion);

void GetCurrentQuaternion(int a0)
{
    GetSlerpQuaternion(a0);
    GetSlerpQuaternionNoRegularize(a0);
}

int *GetLastQuaternion(void)
{
    return &D_00660A40[D_00631B7C * 4];
}

