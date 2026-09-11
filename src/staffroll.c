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

INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollScroll);
INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollNameOut);
INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollMain);

void staffRollWide(void)
{
    D_0063C438 = 1;
    D_0063C430 = (float)((D_004E4600[0] + 0x1400) / 30);
    D_0063C434 = (float)((D_0063C42C - 0x280) / 30);
    staffRollAlpha = 0xFF;
}
