/* ios/pad.c — __FILE__ anchor at .rodata 0x005576B8 */

#include "matching.h"
#include "regpin.h"
#include "include_asm.h"

__attribute__((section(".rodata.0x005576B8"))) const char D_005576B8[24] = "ios/pad.c";
__attribute__((section(".rodata.0x00557840"))) const char D_00557840[32] = "pad:checking controler... ";

/* String rodata migrated from pad_data.c */
__attribute__((section(".rodata.0x005575F0"))) const char D_005575F0[24] = "pad:port:%d slot:%d %s\n";
__attribute__((section(".rodata.0x00557608"))) const char D_00557608[16] = "pad:?%d\n";
__attribute__((section(".rodata.0x00557618"))) const char D_00557618[16] = "phase %d\n";
__attribute__((section(".rodata.0x00557628"))) const char D_00557628[16] = "pad id:%d\n";
__attribute__((section(".rodata.0x00557638"))) const char D_00557638[16] = "pad: exid %d\n";
__attribute__((section(".rodata.0x00557648"))) const char D_00557648[24] = "pad:default 0x%x\n";
__attribute__((section(".rodata.0x00557660"))) const char D_00557660[16] = "pad:%03x\n";
__attribute__((section(".rodata.0x00557670"))) const char D_00557670[32] = "pad:switch to ANALOG mode\n";
__attribute__((section(".rodata.0x00557690"))) const char D_00557690[40] = "pad:switch to PRESSURE SENSE mode\n";
__attribute__((section(".rodata.0x00557808"))) const char D_00557808[16] = "pad:init error\n";
__attribute__((section(".rodata.0x00557818"))) const char D_00557818[40] = "ERROR: scePadPortOpen port%d slot%d\n";
__attribute__((section(".rodata.0x00557860"))) const char D_00557860[24] = "port:%d, slot:%d\n";
__attribute__((section(".rodata.0x00557878"))) const char D_00557878[24] = "voice error? %d\n";

extern const char D_00632140[8];
extern const char D_00632148[8];
extern unsigned int D_00632188;
extern unsigned int D_0063218C;
extern int D_00632190;

extern int D_002811C0[];
extern int D_00281630[];
extern int D_006A6D90[];
extern int D_00631950;
extern int D_00632108;
extern int D_00633C90;

extern void func_00100F18(int x, int *p);
extern void func_0013A250(int *a, int *b, int c);
extern void func_0013A5B8(int *a0, int a1, int a2);
extern void func_0013A6C0(int *a, void *b, int c);
extern void func_0013AF88(void);
extern int  func_0013D098(int a0);

int func_0013A820(int a0)
{
    if (a0 == 2) {
        register unsigned long long v REG("$3") = *(volatile unsigned long long *)0x12001000;
        register int *p REG("$5") = (int *)D_00632108;
        D_00631950 = ((v >> 13) & 1) ^ 1;
        func_00100F18(p[0xC], p);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013A868);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013AD58);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013AF88);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B160);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B298);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B450);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B610);

int func_0013B718(void)
{
    func_0013A5B8(D_00281630, 0, 0);
    return 0;
}

INCLUDE_ASM_NOP_PAD(func_0013B744);

int func_0013B748(int unused, int idx)
{
    return *(int *)((char *)D_002811C0 + (idx << 9));
}

int func_0013B760(int unused, int idx)
{
    int *p = (int *)((char *)D_002811C0 + (idx << 9));
    return p[1];
}

int func_0013B778(int a, int b)
{
    int *p = D_002811C0;
    int count = 0;
    do {
        count++;
        if (p[0] == a) {
            if (p[1] == b) {
                return p[2];
            }
        }
        p = (int *)((char *)p + 0x200);
    } while (count < 2);
    return -1;
}

TRAILING_PAD_NOP();

int func_0013B7C0(int a0, int a1, int a2, int a3)
{
    *(int *)(a0 + 0x4) = a3;
    *(int *)(a0 + 0x0) = (int)((char *)D_002811C0 + a2 * 512);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B7E0);

int func_0013B858(void)
{
    register int v REG("$2") = 1;
    D_00633C90 = v;
    return v;
}

INCLUDE_ASM_NOP_PAD(func_0013B864);

void func_0013B868(void) {
    D_00633C90 = 0;
}

int func_0013B870(void) {
    return D_00633C90;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B878);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B8F0);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B970);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B9D8);

void func_0013BA20(void)
{
    int local_buf;
    func_0013A250(D_00281630, D_006A6D90, 8);
    while (1) {
        func_0013A6C0(D_00281630, &local_buf, 1);
        func_0013AF88();
    }
}

INCLUDE_ASM_NOP_PAD(func_0013BA64);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013BA68);

void func_0013BB70(void) {}

void func_0013BB78(void) {}

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013BB80);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013BE20);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013C110);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013C320);

void func_0013C488(int *out, unsigned short *q)
{
    unsigned int v3;
    out[0] = (int)q;
    KEEP_LIVE_MEM(out[0]);
    out[3] = (int)q + (unsigned int)q[5] * 4;
    out[1] = (int)q + (unsigned int)q[1] * 4;
    v3 = q[3];
    q = (unsigned short *)((char *)q + v3 * 4);
    out[2] = (int)q;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013C4C0);

void func_0013C510(int *a0, int a1, int a2, int a3)
{
    a0[0] = 0;
    if (a1) {
        a0[1] = a1;
    } else {
        a0[1] = (int)&func_0013D098;
    }
    a0[2] = a2;
    a0[3] = a3;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013C538);

struct PadNode {
    char pad[0x30];
    struct PadNode *prev;
    struct PadNode *next;
};

void func_0013C598(struct PadNode **head, struct PadNode *new_node) {
    struct PadNode *old = *head;
    new_node->prev = (struct PadNode *)0;
    new_node->next = old;
    if (old != (struct PadNode *)0) {
        old->prev = new_node;
    }
    *head = new_node;
}
