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

extern void debug_assertMessage(char *p);
extern void SetIdentityQuaternion(void);
extern char D_0054E1B0[];
extern char D_0054E1D8[];

void InitQuaternionDrive(void) {
    int v = D_00629E7C;
    if (v < 0) {
        debug_assertMessage(D_0054E1B0);
        SetIdentityQuaternion();
        v = D_00629E7C;
    }
    v++;
    D_00629E7C = v;
    if (v >= 0x40) {
        debug_assertMessage(D_0054E1D8);
        v = 0x3F;
        D_00629E7C = v;
    }
    {
        int idx = *(volatile int *)&D_00629E7C;
        GetInverseQuaternion(&D_0065A5C0[idx * 4], &D_0065A5C0[idx * 4 - 4]);
    }
}

extern void GetMatrixFromQuaternion(void *a0);

void SetIdentityQuaternion(void) {
    D_00629E7C = 0;
    GetMatrixFromQuaternion(D_0065A5C0);
}

extern int D_002724B0[];

void GetMatrixFromQuaternion(void *a0) {
    GetInverseQuaternion(a0, D_002724B0);
}

extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern char D_002724C0[];
extern char D_00271BE0[];

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
        : : "r"(D_002724C0) : "memory");
    MatrixDrive_TurnObjectMatrix(a0 + 0x30, D_00271BE0);
}

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

extern float func_00118048(float);
extern void _InverseCurrentMatrix(void *a, void *b, float c);

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
    _InverseCurrentMatrix(a0, a0, 1.0f / func_00118048(d));
}

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
