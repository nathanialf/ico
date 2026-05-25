/* ios/message.c — __FILE__ anchor at .rodata 0x00557540 */

#include "include_asm.h"
#include "regpin.h"

const char D_00557540[16] = "ios/message.c";
const char D_00557550[16] = "sema[%d] = %p\n";
const char D_00557560[24] = "msg:null message queue\n";
const char D_00557578[16] = "MSG NO SEND\n";
const char D_00557588[24] = "evt:null message queue\n";
const char D_005575A0[16] = "where is here\n";
const char D_005575B0[32] = "evt:signal added\n";
const char D_005575D0[16] = "FINDCTP1";
const char D_005575E0[16] = "DISCONNECT";

extern int D_006A6990[];
extern void func_001A6E28(const char *fmt, ...);
extern void func_001AD768(const char *file, int line);
extern void func_00263FF0(const char *file, int line, const char *expr);
extern int func_00100530(int x);
extern int func_00100540(int a0, int *a1);
extern const char D_006320F0[];
extern const char D_006320E8[];

void func_0013A220(int *a0)
{
    register int *v1 REG("$3") = a0;
    register int *a1 REG("$5") = (int *)v1[0x10 / 4];
    int v0;
    int new_a0;
    if (a1 == 0) {
        return;
    }
    v0 = a1[0x44 / 4];
    new_a0 = v1[0x2C / 4];
    v1[0x10 / 4] = v0;
    a1[0x44 / 4] = 0;
    return func_00100540(new_a0, a1);
}

INCLUDE_ASM_NOP_PAD(func_0013A248);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A250);

void func_0013A2F8(int *self)
{
    int idx;
    func_001A6E28(D_006320F0, self);
    idx = self[0x2C / 4];
    if (idx < 0) {
        func_001AD768(D_00557540, 0x88);
        func_00263FF0(D_00557540, 0x88, D_006320E8);
        idx = self[0x2C / 4];
    }
    D_006A6990[idx] = 0;
    func_00100530(idx);
}

INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A380);
extern int func_0013A0F8(int a0, int a1, const char *fmt, int line);
extern void func_0013D700(int a0, int a1, void *a2, int a3, int a4, int a5, int a6);
extern void func_0013D3C8(int a0);
extern void func_00100200(int a0, void *entry, int a2);
extern int func_00100A70(int a0);
extern void func_0013A380(void);
extern int func_0013A820(int a0);
extern const char D_00632100[];
extern int D_00632004;

void func_0013A498(int a0, int a1, int a2)
{
    int *s0;
    if (a1 == 0)
    {
        func_001A6E28(D_00557588);
    }
    s0 = (int *) func_0013A0F8(D_00632004, 0x40C0, D_00557540, 0x1C5);
    func_0013D700((int) s0, 4, (void *) func_0013A380, (int) s0,
                  (int)((char *) s0 + 0x70), 0x4000, 0xB);
    s0[0x4090 / 4] = a1;
    s0[0x4094 / 4] = a2;
    s0[0x4098 / 4] = a0;
    func_0013D3C8((int) s0);
    func_001A6E28(D_005575A0);
    func_00100200(a0, (void *) func_0013A820, -1);
    {
        int r = func_00100A70(a0);
        func_001A6E28(D_00632100, r);
    }
    func_001A6E28(D_005575B0);
}

void func_0013A580(void)
{
    int *p = D_006A6990;
    int i;
    p += 0xFF;
    for (i = 0xFF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}

INCLUDE_ASM_NOP_PAD(func_0013A5B4);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A5B8);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A6C0);

void func_0013A7C8(void) {
    int *p;
    int i;
    int **q = (int **)D_006A6990;
    i = 0xFF;
    do {
        p = *q++;
        if (p != 0) {
            func_0013A2F8(p);
        }
        i--;
    } while (i >= 0);
}
