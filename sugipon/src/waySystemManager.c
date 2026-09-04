#include "common.h"

extern void playSEConditionID(int a0, int a1);

extern void GetRootMatrixByDObj();
extern void sceVu0SubVector();
extern void MatrixDrive_TurnObjectMatrix();

void CreateWaySystemManagerGObj(char *a0) {
    int buf[4];
    char *sub;
    GetRootMatrixByDObj(buf, a0);
    sub = *(char **)(a0 + 0x15C);
    sceVu0SubVector(sub + 0x120, buf, sub + 0x1E0);
    sub = *(char **)(a0 + 0x15C);
    MatrixDrive_TurnObjectMatrix(sub + 0x1E0, buf);
}

extern int func_0023D3C0(int a, int b, int c, int d, int e, int f, int g);
extern void func_001EF360(void);
extern int D_0062BA28;

int RequestGetWayBegin(void) {
    int v = func_0023D3C0(0, 0, 0, 0, (int)&func_001EF360, 0, 0);
    D_0062BA28 = v;
    return v;
}

extern void *actCreateSubThreadGOppArg(void *entry, int arg);
/* weak => the %hi/%lo below emits an R_MIPS_HI16/LO16 against the func_001EF310
   SYMBOL (as the original object did), not a `.text + offset` section reloc that
   the in-TU-defined sibling otherwise folds to. Both link byte-identically
   (verify_elf OK); the symbol binding is stripped from the .rom. */
extern __attribute__((weak)) void func_001EF310(volatile unsigned int self);

void *actWaySystemCore(int *a0) {
    void *t = actCreateSubThreadGOppArg(func_001EF310, 0x15);
    *(int **)((char *)t + 0x20) = a0;
    a0[0] = 0;
    return t;
}

extern int GetNearNigePointN(int a, int b, int c, int d);

void func_001EF310(volatile unsigned int self)
{
    volatile int local;
    int *s = (int *)((int *)self)[0x20 / 4];
    int v;
    v = GetNearNigePointN((int)((char *)s + 0x10), (int)((char *)s + 0x20), (int)((char *)s + 0xA0), 1);
    s[0x4 / 4] = v;
    s[0] = 1;
    s[0xB0 / 4] = 0;
}

extern void _ACTWait(int a0);
void func_001EF360(void) {
    for (;;) {
        _ACTWait(1);
    }
}

void func_001EF378(int a0) {
    playSEConditionID(a0, 0x40);
}

extern void ExecFrameDependSequence(int a0);

void func_001EF380(int a0) {
    ExecFrameDependSequence(a0);
    playSEConditionID(a0, 0x41);
}

void func_001EF3B0(int a0) {
    playSEConditionID(a0, 0x42);
}

void func_001EF3B8(int a0) {
    playSEConditionID(a0, 0x57);
}

void func_001EF3C0(int a0) {
    playSEConditionID(a0, 0x58);
}

extern void GetInverseQuaternion(void *a0, void *a1);
extern void GetRootMatrixByDObj(void *a0, int a1);
extern void func_001EF3B8(int a0);
extern int D_00271240[];

void func_001EF3C8(int a0, int a1, int a2, void *a3, float f12) {
    char *m = *(char **)(a0 + 0x15C);
    char *sub = *(char **)(m + 0x7F0);
    int a, b, q;

    if (*(int *)(sub + 0x8) != 0) {
        *(int *)(*(char **)(*(char **)(sub + 0x8) + 0x15C) + 0x620) = 0;
    }
    *(int *)(sub + 0xC) = -1;
    *(int *)(sub + 0x4) = 2;
    *(int *)(sub + 0x8) = 0;
    if (a3 != 0) {
        GetInverseQuaternion(m + 0x140, a3);
    }
    a = D_00271240[0] * 10;
    b = D_00271240[1];
    q = (0x3C - a) / b;
    *(int *)(sub + 0x64) = 0;
    *(int *)(sub + 0x60) = (int)((float)q * f12);
    GetRootMatrixByDObj(sub + 0x70, a0);
    MatrixDrive_TurnObjectMatrix(sub + 0x80, (void *)a1);
    GetInverseQuaternion(sub + 0x90, (void *)a2);
    *(float *)(sub + 0x68) = (*(float *)(sub + 0x84) - *(float *)(sub + 0x74)) / f12 - f12 * 490.0f;
    func_001EF3B8(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF4F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF8E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EFAF8);
