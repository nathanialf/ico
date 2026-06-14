#include "common.h"

extern void *isysGObjRemoveObjDL(void);
extern void setTEX0_1(int a0, int a1);
extern void *func_0013E7E0(void *a0);

void ErrMessage(void) {
    int *p = (int *)isysGObjRemoveObjDL();
    while (p != 0) {
        setTEX0_1(p[2], 0);
        p = (int *)func_0013E7E0(p);
    }
}

extern void func_0023A6D0(void *a0);

void copy2area(int a0) {
    func_0023A6D0(*(void **)(a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_00239E18);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_00239FC0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A0E0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A410);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A5E8);

extern int iosMallocCheckLeak2(int a0);

void func_0023A6D0(void *a0) {
    iosMallocCheckLeak2((int)a0 & 0xFFFFFFF);
}

extern void func_0025A450(int a0);
extern void func_0025A3C8(void);

int func_0023A6E0(char *self) {
    copy2area((int)self);
    if (self[0x61]) {
        func_0025A450(0);
    }
    if (self[0x62]) {
        func_0025A450(1);
    }
    if (self[0x60]) {
        func_0025A3C8();
    }
    return 1;
}

extern void func_0025A578(int a, int b, int c);
extern void func_0025A4E8();

void func_0023A748(int *self)
{
    func_0025A578(3, 0, 0);
    func_0025A4E8(3);
    *(volatile int *)((char *)self + 0x50) = 0;
    *(volatile int *)((char *)self + 0) = 0;
    *(volatile int *)((char *)self + 0x2C) = 0;
    *(volatile int *)((char *)self + 0x34) = 0;
    *(volatile int *)((char *)self + 0x38) = 0;
    *(volatile int *)((char *)self + 0x40) = 0;
    *(volatile int *)((char *)self + 0x54) = 0;
    *(volatile int *)((char *)self + 0x4C) = 0;
}

int func_0023A7A0(void *a0) {
    int *p = (int *)a0;
    return p[0x15] >= p[0x12];
}

extern int func_0025A528(int a, int b);
extern int func_0025A4A8(int a);

void func_0023A7B8(int *self)
{
    func_0025A528(0, 0);
    func_0025A528(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        func_0025A578(3, half, half);
    } else {
        func_0025A578(1, 0, self[0x5C / 4]);
        func_0025A578(2, self[0x5C / 4], 0);
    }
    func_0025A4A8(3);
    self[0] = 2;
}

int func_0023A850(int a0)
{
    *(int *)a0 = 3;
    func_0025A578(3, 0, 0);
    func_0025A4E8(3);
    return 0;
}


void func_0023A888(int *self)
{
    func_0025A528(0, 0);
    func_0025A528(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        func_0025A578(3, half, half);
    } else {
        func_0025A578(1, 0, self[0x5C / 4]);
        func_0025A578(2, self[0x5C / 4], 0);
    }
    func_0025A4A8(3);
    self[0] = 2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A920);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023AA98);

extern int func_0023AA98(void *a0, int a1, int a2);

void func_0023AC90(void *a0, int a1, int a2) {
    int v = *(int *)((char *)a0 + 0x3C);
    func_0023AA98(a0, a1, v < a2 ? a2 : v);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023ACA0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023AD08);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023ADB0);

extern void func_0023E440(void *a0);

void func_0023B310(char *a0, int a1) {
    int val;
    if (a1) {
        val = *(int *)(a0 + 0x2C);
    } else {
        val = *(int *)(a0 + 0x28);
    }
    *(int *)(a0 + 0x10) = (*(int *)(a0 + 0x10) & ~0x1FF) | (val & 0x1FF);
    func_0023E440(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023B348);
