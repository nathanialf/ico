#include "common.h"

typedef struct {
    int          f_0;    /* 0x00 */
    int          f_4;    /* 0x04 */
    long long    f_8;    /* 0x08 */
    unsigned int f_10;   /* 0x10 */
    int          pad_14; /* 0x14 */
    long long    f_18;   /* 0x18 */
    int          pad_20; /* 0x20 */
    int          f_24;   /* 0x24 */
} DlEntry;



extern void debug_assertMessage(char *fmt, ...);
extern int D_0061ABF0[];
extern DlEntry D_00710D10[];
extern int D_00633F70;
extern int D_00631C5C;
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_Init);

int dl_Clear(void)
{
    return 0x14;
}

int dl_Swap(void) {
    return (0x3200 / D_00631C5C) / 2;
}

extern int D_006337F0;
extern int D_006337F4;
extern int D_006337F8;
extern int D_006337FC;
extern int D_00633800;

void dl_PushPriority(void) {
    D_006337F0 = 0;
    D_00633800 = 0x80;
    D_006337FC = 0x80;
    D_006337F8 = 0x80;
    D_006337F4 = 0x80;
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_PopPriority);

extern int D_00633F6C;
extern int D_00710F18[];
extern void func_001FBBE0(void);
extern void gif_SpriteSensitive(void);
extern void pac_openDmaTag(void);

void dl_Debug(void)
{
    int flag = D_00633F6C ^ 1;
    int *src = (int *)((char *)D_00710F18 + flag * 0x34);
    char *dst = (char *)D_00710D10;
    int i;
    D_00633F6C = flag;
    D_00633F70 = 0;
    for (i = 0xC; i >= 0; i--) {
        int v = *src;
        *(int *)dst = 0;
        src++;
        *(int *)(dst + 0x24) = v;
        *(int *)(dst + 0x20) = v;
        dst += 0x28;
    }
    func_001FBBE0();
    gif_SpriteSensitive();
    pac_openDmaTag();
}

extern int D_00631C4C;
extern int D_0063378C;
extern void dl_GetPri();
extern void dpk_Init(int a0, int a1, int a2);
extern void dpk_SwapBuffer(int a0);
extern void func_001007A0(int a0);
extern void func_00244980(int a0, int a1);

void dl_CloseDma(void)
{
    int i;
    int j;
    int stride = 0x28;
    dpk_SwapBuffer(0xC);
    dpk_Init(7, 0, 0);
    dl_GetPri();
    i = 0;
    do {
        DlEntry *e;
        dpk_SwapBuffer(i);
        j = i + 1;
        e = (DlEntry *)((char *)D_00710D10 + j * stride);
        dpk_Init(1, e->pad_20 & 0xFFFFFFF, 0);
        dl_GetPri();
        i = j;
    } while (j < 0xC);
    func_001007A0(0);
    if (D_00631C4C) {
        func_00244980(D_0063378C, D_00710D10[11].pad_20 & 0xFFFFFFF);
    } else {
        func_00244980(D_0063378C, D_00710D10[0].pad_20 & 0xFFFFFFF);
    }
    dl_Debug();
}

extern char D_0061AB88[];
extern char D_0061ABA0[];
extern int D_00633810;
extern char D_00633818[];
extern int D_00710F80[];
extern void debug_assertMessage();
extern void func_001AD768(char *file, int line);
extern void func_00263FF0(char *file, int line, void *expr);

void dl_Out(void) {
    if (D_00633810 < 7) {
        int i = D_00633810;
        D_00710F80[i] = D_00633F70;
        D_00633810 = i + 1;
    } else {
        debug_assertMessage(D_0061ABA0);
        func_001AD768(D_0061AB88, 0x20E);
        func_00263FF0(D_0061AB88, 0x20E, D_00633818);
    }
}

extern char D_0061ABC8[];

void dl_SetDLPriority(void) {
    if (D_00633810 > 0) {
        int i = D_00633810 - 1;
        D_00633810 = i;
        D_00633F70 = D_00710F80[i];
    } else {
        debug_assertMessage(D_0061ABC8);
        func_001AD768(D_0061AB88, 0x220);
        func_00263FF0(D_0061AB88, 0x220, D_00633818);
    }
}

void dl_OpenDma(void)
{
    int *entry = (int *)D_00710D10 + D_00633F70 * 10;
    unsigned int end = entry[9];
    unsigned int start = entry[1];
    unsigned int count = (end - start) >> 4;
    return debug_assertMessage(D_0061ABF0, count - 1);
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_GetPri);

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB9F8);

