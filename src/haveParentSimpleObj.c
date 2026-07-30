#include "common.h"








extern int func_001547B0(void);
extern int *func_001547A0(void);
extern int actBoyReadyMove();
extern int GetsizeGeneratorPacket(void);
extern int ReadGeneratorPacket();
extern int *GetbufpGeneratorPacket(void);
extern void func_00264128();
extern char D_006168F8[];
extern void debug_assertMessage(char *fmt, ...);
extern int D_00632F74;
extern void func_001AE8A0(int *self, int a1, int a2);
extern char D_004B3B68[];
extern char D_004B3D10[];
extern void func_002641D8();
extern void func_001A1008(void);
extern int AllocPObj();
extern int D_002A31B8[];
extern int D_00633E5C;
extern int D_00633E60;
extern int D_00633E64;
INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", ParentSimpleObjGeo);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", ParentSimpleObjDL);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", InitParentSimpleObjGeo);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001ACCD0);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AD0E8);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AD538);

extern char D_004B3468[];
extern char D_006167E0[];
extern char D_00616818[];
extern char D_00616848[];
extern char D_00632F18[];
extern void func_00265168(char *a0, void *a1);

void func_001AD668(void *a0) {
    func_00265168(D_004B3468, a0);
    debug_assertMessage(D_006167E0);
    debug_assertMessage(D_00616818);
    debug_assertMessage(D_00632F18, a0);
    debug_assertMessage(D_00616848);
}

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AD6C8);

void func_001AD740(void) {}

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AD748);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AD768);

extern int D_00632ED0;
extern void func_002450A8(void *a0, int a1);
extern void func_002450B8(void *a0);
extern void func_00245120(void *a0, int a1);
extern void func_002451D0(void *a0, int a1);

void func_001AD788(void *a0) {
    func_002450A8(a0, (D_00632ED0 << 13) | 0x70000000);
    func_002450B8(a0);
    func_00245120(a0, 0);
    func_002451D0(a0, 0);
    D_00632ED0 = (D_00632ED0 + 1) & 1;
}

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AD7F0);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AD8E8);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001ADA08);

void func_001ADB70(void) {
    D_00633E5C = 0;
    D_00633E60 = 1;
    D_00633E64 = 0;
}

int func_001ADB88(void)
{
    int rc = AllocPObj();
    return (int)((char *)D_002A31B8 + *(int *)(rc + 0xC) * 0x64);
}

void func_001ADBC0(void)
{
    int i;
    unsigned short (*a)[32] = (unsigned short (*)[32])D_004B3D10;
    for (i = 0; i < 0xB6; i++) {
        a[i][1] = 0;
        a[i][2] = 0xFFFF;
    }
    func_002641D8(D_004B3B68, 0, 0x1A0);
    func_001A1008();
}

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001ADC18);

void func_001ADCB0(int self) {
    func_001AE8A0(self, &D_00632F74, 4);
    func_001AE8A0(self, (int *)D_004B3D10, 0x2D80);
    func_001AE8A0(self, (int *)D_004B3B68, 0x1A0);
}

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001ADD00);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001ADED8);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AE188);

void func_001AE1B8(int *self, int n, int a2)
{
    if (n != 0) {
        func_00264128(self[0] + self[1], n);
    }
    self[1] += a2;
    debug_assertMessage(D_006168F8, self[1]);
}

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AE210);

void func_001AE258(int *a0)
{
    int s1 = GetbufpGeneratorPacket();
    int s2 = GetsizeGeneratorPacket();
    if (s1 != 0) {
        func_00264128(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadGeneratorPacket();
}

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AE2C0);

void func_001AE308(int *a0)
{
    int s1 = func_001547A0();
    int s2 = func_001547B0();
    if (s1 != 0) {
        func_00264128(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return actBoyReadyMove();
}

void func_001AE370(void)
{
    int mask = 0xFFFF;
    char *p = D_004B3D10;
    int i = 0x8B;
    p += 0xA80;
    do {
        *(short *)(p + 2) = 0;
        *(short *)(p + 4) = (short)mask;
        p += 0x40;
        i--;
    } while (i >= 0);
}

void func_001AE3B0(void)
{
    long long mask = -2LL;
    long long *p = (long long *)D_004B3D10;
    int i = 0xB5;
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}

void func_001AE3E8(void)
{
    long long mask = -3LL;
    long long *p = (long long *)D_004B3D10;
    int i = 0xB5;
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AE420);

INCLUDE_ASM("asm/nonmatchings/src/haveParentSimpleObj", func_001AE460);

