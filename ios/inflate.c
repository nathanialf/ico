#include "common.h"



extern void new_segment(int *self);
extern int D_00633C7C;
extern char D_006A5C80[];
extern char D_00556AE8[];
extern void debug_assertMessage();
extern int func_0024DAB8(int a0, int a1, int a2, void *a3);

int inflate_start(int a0, int a1, int a2, int *a3) {
    int local, result;
    *a3 = 0;
    result = func_0024DAB8(a2 >> 11, a1, 1, &local) << 11;
    if (local != 0) { debug_assertMessage(D_00556AE8, local); *a3 = 1; }
    return result;
}

extern void iosCdvdManager(int *a0, void *buf, int n);

long long close_inflate_handler(void *a0, int a1, int *a2, int a3) {
    long long d = (unsigned int)(a2[0x4E] - a2[9]);
    int lt = d < a1;
    long long n = d;
    if (!lt) n = a1;
    if (n) iosCdvdManager(a2, a0, (int)n);
    return n;
}

void inflate(void)
{
    char *p = D_006A5C80;
    int i;
    p += 0x708;
    for (i = 6; i >= 0; i--) {
        *p = 0;
        p -= 0x12C;
    }
    D_00633C7C = 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00133608);

INCLUDE_ASM("asm/nonmatchings/ios/inflate", open_inflate_handler);

INCLUDE_ASM("asm/nonmatchings/ios/inflate", fill_inbuf);

INCLUDE_ASM("asm/nonmatchings/ios/inflate", huft_free);

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001348F0);

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00134B50);

void func_00135468(void *a0)
{
    int *w = (int *)((char *) a0 + 0x18000);
    w[0x78 / 4] = -1;
    w[0x48 / 4] = 0;
    *(long long *)((char *) w + 0x68) = 0;
    *(long long *)((char *) w + 0x70) = 0;
    w[0x50 / 4] = 0;
    w[0x4C / 4] = 0;
    w[0x54 / 4] = 0;
    w[0x58 / 4] = 0;
    w[0x7C / 4] = 0;
    w[0x84 / 4] = 0;
    w[0x80 / 4] = 0;
    w[0x88 / 4] = 0;
    new_segment((char *) a0 + 0x18098);
}

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001354B8);

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135580);

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135A48);

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135AD8);

