#include "common.h"

extern void *isysGObjGetExist_begin(void);
extern void setTEX0_1(int a0, int a1);
extern void *isysGObjGetExist_next(void *a0);

void ErrMessage(void) {
    int *p = (int *)isysGObjGetExist_begin();
    while (p != 0) {
        setTEX0_1(p[2], 0);
        p = (int *)isysGObjGetExist_next(p);
    }
}

extern void func_0023A6D0(void *a0);

void copy2area(int a0) {
    func_0023A6D0(*(void **)(a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_00239E18);

extern void debug_StdPrintfDummy();
extern char D_00614F70[], D_00614FA8[], D_006150E8[];

void func_00239FC0(void *self, int a1) {
    char *s = (char *)self;
    if (*(int *)s == 0) {
        int v2C = *(int *)(s + 0x2C);
        unsigned int space = (unsigned int)(0x28 - v2C);
        int take = (space < (unsigned int)a1) ? (int)space : a1;
        int nv = v2C + take;
        *(int *)(s + 0x2C) = nv;
        if ((unsigned int)nv >= 0x28) {
            *(int *)s = 1;
            debug_StdPrintfDummy(D_00614F70);
            debug_StdPrintfDummy(D_00614FA8, s[4], s[5], s[6], s[7],
                                *(int *)(s + 0x8), *(int *)(s + 0xC), *(int *)(s + 0x10),
                                *(int *)(s + 0x14), *(int *)(s + 0x18), *(int *)(s + 0x1C), *(int *)(s + 0x20));
            debug_StdPrintfDummy(D_006150E8, s[0x24], s[0x25], s[0x26], s[0x27], *(int *)(s + 0x28));
        }
        a1 -= take;
    }
    {
        int m = (*(int *)(s + 0x34) + a1) % *(int *)(s + 0x3C);
        *(int *)(s + 0x38) += a1;
        *(int *)(s + 0x40) += a1;
        *(int *)(s + 0x34) = m;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A0E0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A410);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A5E8);

extern int iosMallocCheckLeak2(int a0);

void func_0023A6D0(void *a0) {
    iosMallocCheckLeak2((int)a0 & 0xFFFFFFF);
}

extern void SgStPcmClose(int a0);
extern void SgStPcmQuit(void);

int func_0023A6E0(char *self) {
    copy2area((int)self);
    if (self[0x61]) {
        SgStPcmClose(0);
    }
    if (self[0x62]) {
        SgStPcmClose(1);
    }
    if (self[0x60]) {
        SgStPcmQuit();
    }
    return 1;
}

extern void SgStPcmVolume(int a, int b, int c);
extern void SgStPcmStop();

void func_0023A748(int *self)
{
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
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

extern int SgStPcmLseek(int a, int b);
extern int SgStPcmPlay(int a);

void func_0023A7B8(int *self)
{
    SgStPcmLseek(0, 0);
    SgStPcmLseek(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        SgStPcmVolume(3, half, half);
    } else {
        SgStPcmVolume(1, 0, self[0x5C / 4]);
        SgStPcmVolume(2, self[0x5C / 4], 0);
    }
    SgStPcmPlay(3);
    self[0] = 2;
}

int audioDecPause(int a0)
{
    *(int *)a0 = 3;
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    return 0;
}


void func_0023A888(int *self)
{
    SgStPcmLseek(0, 0);
    SgStPcmLseek(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        SgStPcmVolume(3, half, half);
    } else {
        SgStPcmVolume(1, 0, self[0x5C / 4]);
        SgStPcmVolume(2, self[0x5C / 4], 0);
    }
    SgStPcmPlay(3);
    self[0] = 2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A920);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023AA98);

extern int func_0023AA98(void *a0, int a1, int a2);

void setImageSize(void *a0, int a1, int a2) {
    int v = *(int *)((char *)a0 + 0x3C);
    func_0023AA98(a0, a1, v < a2 ? a2 : v);
}

extern void sceGsPutDispEnv(void *a0);
extern void sceGsSyncPath(int a0, int a1);
extern int D_0070C0C0[];

void sendDispEnv(void *a0) {
    sceGsPutDispEnv(a0);
    a0 = (void *)((unsigned int)D_0070C0C0 & 0x0FFFFFFF);
    *(volatile unsigned int *)0x1000A010 = (unsigned int)a0;
    *(volatile unsigned int *)0x1000A020 = 7;
    *(volatile unsigned int *)0x1000A000 = 0x101;
    sceGsSyncPath(0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023AD08);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023ADB0);

extern void sceGsPutDispEnv(void *a0);

void dispSwitch(char *a0, int a1) {
    int val;
    if (a1) {
        val = *(int *)(a0 + 0x2C);
    } else {
        val = *(int *)(a0 + 0x28);
    }
    *(int *)(a0 + 0x10) = (*(int *)(a0 + 0x10) & ~0x1FF) | (val & 0x1FF);
    sceGsPutDispEnv(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", vblankHandler);
