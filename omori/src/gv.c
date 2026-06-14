#include "common.h"

/* gv 0x7F0 view (local; 0x8/0x50 also read as ushort in _InterRotGV) */
typedef struct { char _0[8]; int f_8; } GVGeo;

int _InterGV(void *a0, void *a1) {
    *(float *)a0 = *(float *)((char *)a1 + 0x10);
    *(float *)((char *)a0 + 4) = *(float *)((char *)a1 + 0x14);
    *(float *)((char *)a0 + 8) = *(float *)((char *)a1 + 0x18);
    return 1;
}

extern int iosOmBeforeFuncStandard(void *a0, int a1, void *a2);

int GetMatrixDirectionToZ(void *a0, void *a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    int h = *(short *)((char *)a1 + 0x30);
    *(int *)((char *)q + 0x50) = h;
    *(int *)((char *)q + 0x8) = *(short *)((char *)a1 + 0x32);
    if (h == 1) {
        *(int *)((char *)q + 0x54) = 2;
        iosOmBeforeFuncStandard(a0, 1, a0);
    }
    return 1;
}

int _InterRotGV(void *a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    unsigned short *q = *(unsigned short **)((char *)p + 0x7F0);
    *(unsigned short *)a0 = *(unsigned short *)((char *)q + 0x50);
    *(unsigned short *)((char *)a0 + 2) = *(unsigned short *)((char *)q + 0x8);
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _DistxzSqGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _DistSqGV);

extern void debug_assertMessage(char *a0, int a1);
extern char D_005550A8[];

void _DistGV(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    debug_assertMessage(D_005550A8, *(int *)((char *)a0 + 0x8));
    *(unsigned long *)((char *)p + 0x18) |= (unsigned long)0x8000 << 19;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _DistxzGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _MoveGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _RotyGV);

int _AbsRotyGV(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GVGeo *q = *(GVGeo **)((char *)p + 0x7F0);
    return q->f_8 == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _ApplyRyGV);

void _GetDirection(short *a0) {
    a0[0] = 1;
    a0[1] = 1;
}

typedef struct { char _[0x48]; int f48; } GVState;
extern GVState D_002E0064;

void _RotGV(void) {
    D_002E0064.f48 = (D_002E0064.f48 | 0x200000) & 0xFFFBFFFF;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _RotGVF);

extern void assertMsg1(char *a0) __asm__("debug_assertMessage");
extern char D_0062C900[];
extern void func_0023FFC8(void *a0, void *a1, void *a2, float a3);

void _OrientXZGV(void *a0, void *a1, void *a2, float a3, float a4) {
    if (a0 == 0 || a1 == 0 || a2 == 0) {
        assertMsg1(D_0062C900);
    }
    func_0023FFC8(a0, a1, a2, a4 / (a3 + a4));
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _OrientGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _FrontGV);
