/* sound/adpcm_init.c — __FILE__ anchor at .rodata 0x00557b78 */

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"

const char D_00557B78[24] = "sound/adpcm_init.c";
const char D_00557B90[32] = "AdpcmIopBuffAlloc not alloc\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "IOP領域が確保されているのにもかかわらず,使われていなので解放します\n" */
const char D_00557BB0[72] = "IOP\316\316\260\350\244\254\263\316\312\335\244\265\244\354\244\306\244\244\244\353\244\316\244\313\244\342\244\253\244\253\244\357\244\351\244\272,\273\310\244\357\244\354\244\306\244\244\244\312\244\316\244\307\262\362\312\374\244\267\244\336\244\271\n";
const char D_00557BF8[16] = "AdpcmPlay\n";
const char D_00557C08[24] = "AdpcmOpen id%d \n";
const char D_00557C20[16] = "AdpcmOpensync\n";
const char D_00557C30[32] = "AdpcmOpensync done\n";

extern int  D_00633CC0;
extern int  D_00633CC4;
extern int  D_00633CB0;
extern int  D_00633CB8[2];
extern int *D_00281A70[];
extern int  D_006A94E0[];

extern int  func_0013E488(int a0);
extern void func_0013F9D0(int a0, int a1, int a2, int a3);
extern void func_001A6E28(int *a0);
extern int  func_00135EB8(int x, char *p, int b);
extern void func_00140A20(short *p, int doubled_idx);
extern void func_0024A1E0(int a0);
extern void func_0025DEF0(long long a0);
extern void func_0025DF50(long long a0);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_0013F9D0);

void func_0013FBF8(int a0, int a1, int a2, int a3)
{
    func_0013F9D0(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_0013FC00);
void func_0013FD10(int idx, void (*fn)(int *, int), int arg)
{
    int *node = D_00281A70[idx];
    if (node != 0) {
        do {
            fn(node, arg);
            node = (int *)node[0x10 / 4];
        } while (node != 0);
    }
}
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_0013FD78);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_0013FE18);

void func_0013FEB0(int a0, int a1)
{
    *(int *)a0 = 0x140;
    *(int *)a1 = func_0013E488(a0);
}

int *func_0013FEE0(int idx, int target)
{
    int *p = D_00281A70[idx];
    if (p != 0) {
        do {
            if (p[0] == target) {
                return p;
            }
            p = (int *)p[0x10/4];
        } while (p != 0);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_0013FF20);

void func_0013FF80(void) {}

int func_0013FF88(char *self_arg, int val5, int val6)
{
    register char *self REG("$8") = self_arg;
    int *p = (int *)(self + 0x54);
    int count = p[1];
    register int idx REG("$3");
    register char *addr REG("$3");
    if (count == 0x20) return -1;
    idx = count * 8;
    __asm__("addu %0, %1, %2" : "=r"(addr) : "r"(self), "0"(idx));
    *(int *)(addr + 0x5C) = val5;
    {
        int c2 = p[1];
        register int idx2 REG("$3");
        register char *addr2 REG("$3");
        p[1] = c2 + 1;
        idx2 = c2 * 8;
        __asm__("addu %0, %1, %2" : "=r"(addr2) : "r"(self), "0"(idx2));
        *(int *)(addr2 + 0x60) = val6;
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_0013FFD0);

extern char *D_006321DC;
extern void func_0013E548(char *ctx);
extern void func_0013F810(char *ctx);
extern void func_0013F888(char *ctx);

typedef struct __attribute__((packed)) { long long v; } PackedLL;

int func_00140048(void (*cb)(long long)) {
    char *ctx = D_006321DC;
    char *base = ctx + 0x54;
    int count;
    int i;
    char *entries_base;
    count = *(int *)(base + 4);
    if (count <= 0) goto end;
    i = 0;
    entries_base = ctx + 0x5C;
    do {
        int op;
        char *entry_addr = (char *)((int)entries_base + (i << 3));
        op = *(int *)entry_addr;
        if ((unsigned)op < 5) {
            switch (op) {
                case 0: func_0013E548(ctx); break;
                case 1: func_0013F810(ctx); break;
                case 2: func_0013F888(ctx); break;
                case 3: case 4: break;
            }
        } else {
            char *addr = base + i * 8;
            __asm__ __volatile__(
                ".set push\n\t"
                ".set noreorder\n\t"
                "ldl $4, 15(%0)\n\t"
                "ldr $4, 8(%0)\n\t"
                "jalr %1\n\t"
                "nop\n\t"
                ".set pop"
                : : "r"(addr), "r"(cb) : "$4", "$31", "memory");
        }
        i++;
    } while (i < *(int *)(base + 4));
end:
    return 0;
}

void func_00140130(void)
{
    func_0024A1E0(D_00633CC4);
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140138);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140340);

void func_00140710(int a0)
{
    func_001A6E28(D_00557BF8);
    func_0025DEF0(*(long long *)(a0 + 0x30));
}

void func_00140740(int a0)
{
    func_0025DF50(*(long long *)(a0 + 0x30));
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140748);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140888);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140A20);

void func_00140B30(int *self, int idx, int val)
{
    short *p;
    int di;
    int dj;
    short *q1, *q2;
    p = (short *)self[0x2C / 4];
    di = idx * 2;
    dj = (di + 1) * 2;
    q1 = (short *)((char *)p + dj);
    q2 = p + di;
    q1[0x20] = (short)val;
    q2[0x1E] = (short)val;
    func_00140A20(p, di);
}

INCLUDE_ASM_NOP_PAD(func_00140B5C);

void func_00140B60(int a0, int a1)
{
    func_00140B30((int *)a0, 0, a1);
}

INCLUDE_ASM_NOP_PAD(func_00140B6C);

void func_00140B70(int val) {
    D_00633CC0 = val;
}

void func_00140B78(void)
{
    int a;
    a = func_00135EB8(0xB8800, D_00557B78, 0x44);
    D_00633CC4 = a;
    if ((a & 0x7FF) != 0) {
        D_00633CB0 = (a / 0x800 + 1) * 0x800;
    } else {
        D_00633CB0 = a;
    }
}

INCLUDE_ASM_NOP_PAD(func_00140BDC);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140BE0);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140CE0);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140D58);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140E48);

void func_00140EE8(short a0)
{
    int *p = D_006A94E0;
    int *end = (int *)((char *)p + 0xB0);
    do {
        if (*p != 0) {
            *(short *)((char *)p + 0x44) = a0;
        }
        p = (int *)((char *)p + 0x58);
    } while ((int)p < (int)end);
}

int func_00140F20(void)
{
    int count = 0;
    int *p = D_00633CB8;
    int n = 1;
    do {
        int v = *p;
        int next = count + 1;
        p++;
        n--;
        if (v != 0) count = next;
    } while (n >= 0);
    return count;
}

INCLUDE_ASM_NOP_PAD(func_00140F54);

int func_00140F58(void)
{
    int count = 0;
    int *p = D_00633CB8;
    int n = 1;
    do {
        int v = *p;
        int next = count + 1;
        p++;
        n--;
        if (v == 0) count = next;
    } while (n >= 0);
    return count;
}

INCLUDE_ASM_NOP_PAD(func_00140F8C);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140F90);

short func_00141020(char *self, int idx) {
    char *base = *(char **)(self + 0x2C);
    base += idx * 4;
    return *(short *)(base + 0x3C);
}

INCLUDE_ASM_NOP_PAD(func_00141034);
