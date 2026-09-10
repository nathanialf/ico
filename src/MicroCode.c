#include "common.h"
#include "vu0.h"

/* prototypes: their order is the inline tail's emission order */
void mc_TransMicroCode(int a0, int a1);
void mc_Reset(void);
void mc_Init(void);
extern int D_00290B20[];
extern int D_0063C140;
extern int D_0067BFD0[];
extern int dl_CloseDma(void);
extern void dl_OpenDma(int a0, int a1, int a2);
extern int dl_SetDLPriority(int a0);
extern void mc_setBaseOffset(int base, int pri);

/* The display-list packet builder state and one 64-bit packet slot; same
   objects src/GifPacket.c builds its packets in. */
typedef struct {
    int cur;
    int *buf[2];
    char *dma;
    unsigned long long *ptr;
    char *tail;
    char *gif;
    char *end;
} GifDpk;

typedef union {
    long long d;
    int w[2];
} GifPkWord;

extern GifDpk D_004EE6F0;

void mc_setBaseOffset(int base, int pri)
{
    char *c;
    char *q;

    c = (char *)D_004EE6F0.ptr;
    D_004EE6F0.gif = 0;
    D_004EE6F0.dma = c;
    D_004EE6F0.end = 0;
    D_004EE6F0.tail = c;
    ((GifPkWord *)c)->d = 0x10000000;
    D_004EE6F0.ptr = (unsigned long long *)(c + 8);

    switch (base) {
    case 1:
    case 2: {
        char *p = (char *)D_004EE6F0.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000100;
        p += 4;
        D_004EE6F0.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x02000180;
        D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    } break;
    case 3: {
        char *p = (char *)D_004EE6F0.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000100;
        p += 4;
        D_004EE6F0.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x02000180;
        D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    } break;
    case 4: {
        char *p = (char *)D_004EE6F0.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000010;
        p += 4;
        D_004EE6F0.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x020001F8;
        D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    } break;
    case 5: {
        char *p = (char *)D_004EE6F0.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000010;
        p += 4;
        D_004EE6F0.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x0200016A;
        D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    } break;
    }

    q = (char *)D_004EE6F0.ptr;
    D_004EE6F0.tail = q;
    ((GifPkWord *)q)->d = 0x60000000;
    D_004EE6F0.ptr = (unsigned long long *)(q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(q + 0x10);
    dl_SetDLPriority(pri);
    dl_OpenDma(5, (int)D_004EE6F0.dma, 0);
    dl_CloseDma();
}

inline void mc_TransMicroCode(int a0, int a1)
{
    int *q = &D_00290B20[a0];
    int i;
    for (i = 0; i < 0xD; i++) {
        if ((a1 >> i) & 1) {
            if (a0 != D_0067BFD0[i]) {
                D_0063C140++;
                mc_setBaseOffset(a0, i);
                dl_SetDLPriority(i);
                dl_OpenDma(5, *q, 0);
                dl_CloseDma();
                D_0067BFD0[i] = a0;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/MicroCode", mc_SetMicroCode);

inline void mc_Init(void)
{
    int *p = D_0067BFD0;
    int i = 0xC;
    D_0063C140 = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

inline void mc_Reset(void)
{
    int *p = D_0067BFD0;
    int i = 0xC;
    D_0063C140 = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}
