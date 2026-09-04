#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void dl_Out(void);
void dl_SetDLPriority(int a0);
void dl_OpenDma(int a0, int a1, int a2);
int dl_GetPri(void);
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
extern int D_0063C4BC;
extern int D_0063C4C0;
extern DlEntry D_00728310[];
extern int D_00728518[];
extern void dpk_SwapBuffer(void);
extern void gif_Init(void);
extern void mc_Reset(void);
extern int D_0063A054;
extern int dmaVif;
extern void FlushCache(int a0);
extern void dl_CloseDma();
extern void sceDmaSend(int a0, int a1);
extern int D_006218E0[];
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void iosFree(int a0);
extern int D_00728310__pn[] __asm__("D_00728310");
extern int dl_CloseDma__pn(void) __asm__("dl_CloseDma");
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_Init);
inline void dl_Out(void) {
    int i;
    for (i = 0; i < 2; i++) {
        int *p = (int *)((char *)D_00728518 + i * 0x34);
        int j;
        for (j = 0xC; j >= 0; j--) {
            iosFree(*p);
            p++;
        }
    }
}
void dl_Clear(void)
{
    int flag = D_0063C4BC ^ 1;
    int *src = (int *)((char *)D_00728518 + flag * 0x34);
    char *dst = (char *)D_00728310;
    int i;
    D_0063C4BC = flag;
    D_0063C4C0 = 0;
    for (i = 0xC; i >= 0; i--) {
        int v = *src;
        *(int *)dst = 0;
        src++;
        *(int *)(dst + 0x24) = v;
        *(int *)(dst + 0x20) = v;
        dst += 0x28;
    }
    dpk_SwapBuffer();
    gif_Init();
    mc_Reset();
}
void dl_Swap(void)
{
    int i;
    int j;
    int stride = 0x28;
    dl_SetDLPriority(0xC);
    dl_OpenDma(7, 0, 0);
    dl_CloseDma();
    i = 0;
    do {
        DlEntry *e;
        dl_SetDLPriority(i);
        j = i + 1;
        e = (DlEntry *)((char *)D_00728310 + j * stride);
        dl_OpenDma(1, e->pad_20 & 0xFFFFFFF, 0);
        dl_CloseDma();
        i = j;
    } while (j < 0xC);
    FlushCache(0);
    if (D_0063A054) {
        sceDmaSend(dmaVif, D_00728310[11].pad_20 & 0xFFFFFFF);
    } else {
        sceDmaSend(dmaVif, D_00728310[0].pad_20 & 0xFFFFFFF);
    }
    dl_Clear();
}
inline void dl_SetDLPriority(int a0)
{
    if (a0 < 0) {
        D_0063C4C0 = 0;
    } else if (a0 >= 0xD) {
        D_0063C4C0 = 0xC;
    } else {
        D_0063C4C0 = a0;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_PushPriority);
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_PopPriority);
inline int dl_GetPri(void) {
    return D_0063C4C0;
}
void dl_Debug(void)
{
    int *entry = (int *)D_00728310 + D_0063C4C0 * 10;
    unsigned int end = entry[9];
    unsigned int start = entry[1];
    unsigned int count = (end - start) >> 4;
    return debug_StdPrintfDummy(D_006218E0, count - 1);
}
inline void dl_OpenDma(int a0, int a1, int a2) {
    int *entry = &D_00728310__pn[D_0063C4C0 * 10];
    int old;
    if (entry[0]) {
        dl_CloseDma__pn();
    }
    old = entry[9];
    *(long long *)(entry + 6) = a0;
    entry[4] = a2;
    entry[0] = 1;
    *(long long *)(entry + 2) = (long long)a1 & 0xFFFFFFFLL;
    entry[1] = old;
    entry[9] = old + 0x10;
}
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_CloseDma);
