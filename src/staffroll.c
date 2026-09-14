#include "common.h"

extern int D_004E4600[];
extern int staffRollAlpha;
extern int D_0063C42C;
extern float D_0063C430;
extern float D_0063C434;
extern int D_0063C438;

typedef struct {
    unsigned char b[4];
} StaffRollCol;

typedef struct {
    char **str;       /* 0x00 */
    float y;          /* 0x04 */
    char size;        /* 0x08 */
    StaffRollCol col; /* 0x09 */
    char pad[3];      /* 0x0D */
} StaffRollEntry;     /* 0x10 */

extern StaffRollEntry D_0071D980[];
extern int D_0028F4C0[];
extern int staffRollStartFlag;
extern float D_0063C420;
extern float D_0063C424;
extern int D_0063C428;
extern int D_0063C43C;
extern float staffRollCenterOffsetX;
extern float staffRollCenterOffsetXDest;
extern void memset(void *dst, int c, int n);

void staffRollStart(float t, int alpha)
{
    staffRollStartFlag = 1;
    D_0063C420 = (t + t) * 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    staffRollAlpha = alpha;
    D_0063C428 = 0;
    D_0063C424 = 0.0f;
    D_0063C43C = 0;
    D_0063C42C = 0;
    D_0063C438 = 0;
    staffRollCenterOffsetX = staffRollCenterOffsetXDest = D_0063C424;
    D_004E4600[0] = 0x500;
    memset(D_0071D980, 0, 0x12C0);
}

extern void font_Print(unsigned int attr, char *str, int size, StaffRollCol col, float x, float y);

/* The scroll loop walks the 300-entry table by BYTE offset and spells the base
   at every use site: that is what keeps the entry address a giv of the byte
   counter with no separate index multiply, so loop.c can drop the counter
   itself and compare the cursor against base + 0x12C0. */
#define SROLL(off) ((StaffRollEntry *)((char *)D_0071D980 + (off)))

int staffRollScroll(void)
{
    int count;
    int i;
    int a;
    float t;

    count = 0;

    D_0063C424 += D_0063C420;
    for (i = 0; i < 300 * 16; i += 16) {
        if (SROLL(i)->str == 0) {
            continue;
        }
        count++;

        SROLL(i)->y -= D_0063C420;
        t = SROLL(i)->y - 112.0f;
        a = (int)(184.0f - (t < 0.0f ? -t : t) * 120.0f / 112.0f);
        if (a < 0) {
            a = 0;
        }
        if (a > 128) {
            a = 128;
        }
        if ((float)(-(font_GetHeight() + 449)) < SROLL(i)->y) {
            font_Print(a | 0x70707000, *SROLL(i)->str, SROLL(i)->size, SROLL(i)->col,
                       (float)D_0063C42C, SROLL(i)->y);
        } else {
            SROLL(i)->str = 0;
        }
    }

    return count;
}

extern char *D_004E4610[];
extern char D_0061DF10[];
extern char D_0061DF28[];
extern char D_0063B660[];
extern int D_0063B674;
extern int font_GetHeight(void);
extern int font_CheckAlign(StaffRollCol *col, char *str);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

int staffRollNameOut(void)
{
    StaffRollEntry *e;
    char **s;
    int i;

    if (D_0063C424 / (float)(font_GetHeight() + 1) >= (float)D_0063C428) {
        for (i = 0; i < 300; i++) {
            if (D_0071D980[i].str == 0)
                goto found;
        }
        debug_StdPrintfDummy(D_0061DF10);
        debug_assert(D_0061DF28, 0xC0);
        __assert(D_0061DF28, 0xC0, D_0063B660);
    found:

        e = &D_0071D980[i];
        s = &D_004E4610[D_0063C428++];
        if (*s != 0)
            e->str = s;

        e->y = (float)(font_GetHeight() + 449);
        e->size = font_CheckAlign(&e->col, *e->str);
    }
    return D_0063C428 >= D_0063B674;
}

extern unsigned char D_0063B66B;
extern void font_Init(void);

void staffRollMain(void)
{
    int a;
    int n;

    if (D_0063C438 != 0) {
        n = 0;
        D_004E4600[0] = (int)((float)D_004E4600[0] - D_0063C430);
        if (D_004E4600[0] < -0x1400) {
            D_004E4600[0] = -0x1400;
            n = 1;
        }
        D_0063C42C = (int)((float)D_0063C42C - D_0063C434);
        if (D_0063C42C < 0x280) {
            D_0063C42C = 0x280;
            n++;
        }
        if (n == 2) {
            D_0063C438 = 0;
        }
    }

    a = D_0063B66B;
    if (a < staffRollAlpha) {
        a += 2;
        if (staffRollAlpha < a) {
            a = staffRollAlpha;
        }
    } else {
        a -= 2;
        if (a < staffRollAlpha) {
            a = staffRollAlpha;
        }
    }
    /* the fade level is written through a volatile view at this one site;
       D_0063B66B is referenced only by this function (five sites in the ROM)
       so no async writer is proven, see the r24 LEDGER row */
    *(volatile unsigned char *)&D_0063B66B = a;

    if (staffRollCenterOffsetXDest > staffRollCenterOffsetX) {
        staffRollCenterOffsetX += 0.5f;
        if (staffRollCenterOffsetXDest < staffRollCenterOffsetX) {
            staffRollCenterOffsetX = staffRollCenterOffsetXDest;
        }
    } else {
        staffRollCenterOffsetX -= 0.5f;
        if (staffRollCenterOffsetX < staffRollCenterOffsetXDest) {
            staffRollCenterOffsetX = staffRollCenterOffsetXDest;
        }
    }

    switch (D_0063C43C) {
    case 0:
        font_Init();
        D_0063B66B = 0;
        D_0063C43C++;
        /* fallthrough */
    case 1:
        staffRollCenterOffsetXDest = 0.0f;
        if (D_0063B66B == staffRollAlpha && staffRollCenterOffsetX == staffRollCenterOffsetXDest) {
            D_0063C43C++;
        }
        break;
    case 2:
        staffRollScroll();
        if (staffRollNameOut() != 0) {
            D_0063C43C++;
        }
        break;
    case 3:
        if (staffRollScroll() == 0) {
            D_0063C43C++;
        }
        break;
    case 4:
        staffRollAlpha = 0;
        staffRollCenterOffsetXDest = 0.0f;
        if (D_0063B66B == 0) {
            D_0063C43C++;
        }
        break;
    case 5:
        if (staffRollCenterOffsetX == 0.0f) {
            D_0063C43C++;
        }
        break;
    case 6:
        staffRollStartFlag = 0;
        break;
    }
}

void staffRollWide(void)
{
    D_0063C438 = 1;
    D_0063C430 = (float)((D_004E4600[0] + 0x1400) / 30);
    D_0063C434 = (float)((D_0063C42C - 0x280) / 30);
    staffRollAlpha = 0xFF;
}
