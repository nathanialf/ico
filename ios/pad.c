/* ios/pad.c — __FILE__ anchor at .rodata 0x005576B8 */

#include "matching.h"
#include "regpin.h"
#include "include_asm.h"

const char D_005575F0[24] = "pad:port:%d slot:%d %s\n";
const char D_00557608[16] = "pad:?%d\n";
const char D_00557618[16] = "phase %d\n";
const char D_00557628[16] = "pad id:%d\n";
const char D_00557638[16] = "pad: exid %d\n";
const char D_00557648[24] = "pad:default 0x%x\n";
const char D_00557660[16] = "pad:%03x\n";
const char D_00557670[32] = "pad:switch to ANALOG mode\n";
const char D_00557690[40] = "pad:switch to PRESSURE SENSE mode\n";
const char D_005576B8[24] = "ios/pad.c";
const char D_00557808[16] = "pad:init error\n";
const char D_00557818[40] = "ERROR: scePadPortOpen port%d slot%d\n";
const char D_00557840[32] = "pad:checking controler... ";
const char D_00557860[24] = "port:%d, slot:%d\n";
const char D_00557878[24] = "voice error? %d\n";

/* .data — pad-state zero buffers (two 1KB slot tables, voice/misc state). */
unsigned char D_002811C0[1024] = { 0 };
unsigned char D_002815C0[112]  = { 0 };
unsigned char D_00281630[48]   = { 0 };
unsigned char D_00281660[16]   = { 0 };
unsigned char D_00281670[1024] = { 0 };

/* .rodata — 23-entry button-mapping table. func_0013B610 indexes by row
 * (shift left 3 → 8-byte stride), then reads `id` as s16 at +4 and
 * `flag` as u16 at +6; offset 0 holds a u32 `kind`/count field. */
typedef struct { unsigned int kind; short id; unsigned short flag; } T_005F2F00_rec;
const T_005F2F00_rec D_005F2F00[23] = {
    { 0, 0,    0 },
    { 1, 0x00, 1 }, { 1, 0x01, 1 }, { 1, 0x02, 1 },
    { 1, 0x0B, 0 }, { 1, 0x0C, 0 },
    { 1, 0x0D, 1 }, { 1, 0x0E, 1 }, { 1, 0x0F, 1 },
    { 1, 0x10, 0 }, { 1, 0x11, 0 }, { 1, 0x12, 0 },
    { 1, 0x13, 1 }, { 1, 0x14, 1 }, { 1, 0x15, 1 },
    { 1, 0x16, 1 }, { 1, 0x17, 1 }, { 1, 0x18, 1 },
    { 1, 0x19, 1 }, { 1, 0x1A, 1 }, { 1, 0x1B, 1 },
    { 1, 0x1C, 1 }, { 1, 0x1D, 1 },
};

/* .lit4 — alternating scalar/array form matches original section alignment
 * (4-aligned VMAs use scalar `.align 2`, 8-aligned use `[1]` `.align 3`). */
const float D_00630A94    = 3.14159274f;      /* PI */
const float D_00630A98[1] = { 0.2f };
const float D_00630A9C    = 0.1f;
const float D_00630AA0[1] = { 0.05f };
const float D_00630AA4    = -0.0027777778f;   /* -1/360 */
const float D_00630AA8[1] = { 3000.0f };
const float D_00630AAC    = 0.1f;
const float D_00630AB0[1] = { 10000.0f };
const float D_00630AB4    = 3000.0f;
const float D_00630AB8[1] = { 0.1f };

/* .sdata — small flags and 8-byte zero scratch buffers. */
unsigned int  D_0063218C    = 0x00000001;
unsigned char D_00632190[4] = { 0 };
unsigned int  D_00632194    = 0x00000000;
unsigned char D_00632198[8] = { 0 };
unsigned char D_006321A0[8] = { 0 };
unsigned char D_006321A8[8] = { 0 };

extern const char D_00632140[8];
extern const char D_00632148[8];
extern unsigned int D_00632188;

extern int D_006A6D90[];
extern int D_006A6DB0[];
extern int D_00631950;
extern int D_00632108;
extern int D_00633C90;

extern void func_00100F18(int x, int *p);
extern void func_0013A250(int *a, int *b, int c);
extern void func_0013A5B8(int *a0, int a1, int a2);
extern void func_0013A6C0(int *a, void *b, int c);
extern void func_0013AF88(void);
extern int  func_0013D098(int a0);
extern void func_0013C958(int a0, int a1);
extern void func_002439B0(void *dst, void *src);
extern void func_002438B8(int *p17, void *mat, void *vec);
extern int  D_00631970;
extern void func_002641D8(void *dst, int val, int n);
extern void func_0013CE48(void);
extern void func_0013CF08(int a, int b);
extern void func_0013CF38(int *p);
extern void func_0013CF70(int *p);

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013A820);

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013A868);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013AD58);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013AF88);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B160);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B298);
INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B450);
extern int D_00632110;
extern int func_0013C110(int a0, int a1, unsigned long long a2, int a3, int a4);

struct U32_0013B610
{
    int v;
} __attribute__((packed));

typedef struct
{
    int f0;
    int f4;
    int f8;
    unsigned char fC, fD, fE, fF;
    short f10;
    short f12;
    unsigned char f14;
    unsigned char pad[3];
} PadSlot0013B610;

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

struct Vec0013B7E0
{
    float x;
    int z0;
    float y;
    int z1;
} __attribute__((aligned(8)));

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B7E0);

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B858);

void func_0013B868(void) {
    D_00633C90 = 0;
}

int func_0013B870(void) {
    return D_00633C90;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013B878);
void func_0013B8F0(int key)
{
    if (key == 0)
    {
        return;
    }
    for (;;)
    {
        int *p = D_006A6DB0;
        int *entry;
        int i = 0xF;
        while (1)
        {
            if (*p == key)
            {
                goto found;
            }
            i--;
            if (i == -1)
            {
                goto notfound;
            }
            p = (int *)((char *) p + 0x18);
        }
    notfound:
        entry = 0;
        goto check;
    found:
        entry = p;
    check:
        if (entry == 0)
        {
            break;
        }
        func_0013C958(entry[0x4 / 4], key);
        entry[0] = 0;
    }
}
void func_0013B970(void)
{
    int *p = D_006A6DB0;
    int i;
    for (i = 0xF; i != -1; i--) {
        int x = p[0];
        if (x != 0) {
            func_0013C958(p[1], x);
            p[0] = 0;
        }
        p = (int *)((char *)p + 0x18);
    }
}

int *func_0013B9D8(int key, unsigned int val)
{
    int *p = D_006A6DB0;
    int *rv;
    int i;
    val = val & 0xFF;
    i = 0xF;
    while (1) {
        if (*p == key) goto found;
        i--;
        if (i == -1) goto notfound;
        p = (int *)((char *)p + 0x18);
    }
notfound:
    rv = 0;
    goto end;
found:
    rv = p;
end:
    if (rv != 0) {
        *(unsigned char *)((char *)rv + 0x14) = val;
    }
    return rv;
}

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

INCLUDE_ASM("asm/nonmatchings/ios/pad", func_0013C488);

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

void func_0013C538(int *self)
{
    int *node = (int *) self[0];
    if (self[0x8 / 4] == 0)
    {
        goto end;
    }
    if (node == 0)
    {
        goto end;
    }
    do
    {
        int *cur = node;
        node = (int *) node[0x34 / 4];
        (*(void (**)(int, int))((char *) self + 8))((int) cur, self[0xC / 4]);
    } while (node != 0);
end:
    self[0] = 0;
}

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
