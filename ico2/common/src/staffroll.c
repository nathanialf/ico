#include "common.h"
#include "debug.h"
#include "DisplayFont.h"
#include <string.h>

/* staffroll.o's whole .data run: the roll's display area, centred on the
   origin, {x, y, width, height}.  Only the first word is read here, as the
   running scroll position. */
static int staffRollArea[4] = {-5120, -1792, 10240, 3584};

extern int staffRollAlpha;

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

/* .sbss, owned by staffroll.o and reached only from this file (MAIN.MAP names
   no symbol in the run), in the ROM's run order. */
static float rollSpeed; /* lines the roll climbs per frame */

static float rollOffset; /* how far it has climbed so far */

static int rollNameIdx; /* the next entry of staffRollNameData to post */

static int rollWidth; /* the roll's right edge, closing in on 640 */

static float areaStep; /* per-frame close of the display area */

static float widthStep; /* per-frame close of rollWidth */

static int closing; /* the area is closing */

static int rollStep; /* the roll's own sequence step */

/* .bss, owned by staffroll.o and reached only from this file: the posted
   lines, 0x12C0 bytes of StaffRollEntry. */
static StaffRollEntry rollLines[300];

extern int D_0028F4C0[];
extern int staffRollStartFlag;
extern float staffRollCenterOffsetX;
extern float staffRollCenterOffsetXDest;

void staffRollStart(float t, int alpha)
{
    staffRollStartFlag = 1;
    rollSpeed = (t + t) * 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    staffRollAlpha = alpha;
    rollNameIdx = 0;
    rollOffset = 0.0f;
    rollStep = 0;
    rollWidth = 0;
    closing = 0;
    staffRollCenterOffsetX = staffRollCenterOffsetXDest = rollOffset;
    staffRollArea[0] = 0x500;
    memset(rollLines, 0, sizeof(rollLines));
}

extern void font_Print(unsigned int attr, char *str, int size, StaffRollCol col, float x, float y);

/* The scroll loop walks the 300-entry table by BYTE offset and spells the base
   at every use site: that is what keeps the entry address a giv of the byte
   counter with no separate index multiply, so loop.c can drop the counter
   itself and compare the cursor against base + 0x12C0. */
#define SROLL(off) ((StaffRollEntry *)((char *)rollLines + (off)))

int staffRollScroll(void)
{
    int count;
    int i;
    int a;
    float t;

    count = 0;

    rollOffset += rollSpeed;
    for (i = 0; i < 300 * 16; i += 16) {
        if (SROLL(i)->str == 0) {
            continue;
        }
        count++;

        SROLL(i)->y -= rollSpeed;
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
                       (float)rollWidth, SROLL(i)->y);
        } else {
            SROLL(i)->str = 0;
        }
    }

    return count;
}

extern char *staffRollNameData[];
extern char D_0063B660[];
extern int D_0063B674;
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

int staffRollNameOut(void)
{
    StaffRollEntry *e;
    char **s;
    int i;

    if (rollOffset / (float)(font_GetHeight() + 1) >= (float)rollNameIdx) {
        for (i = 0; i < 300; i++) {
            if (rollLines[i].str == 0)
                goto found;
        }
        /* staff roll: out of area */
        debug_StdPrintfDummy("staff roll 領域不足\n");
        debug_assert(__FILE__, 0xC0);
        __assert(__FILE__, 0xC0, D_0063B660);
    found:

        e = &rollLines[i];
        s = &staffRollNameData[rollNameIdx++];
        if (*s != 0)
            e->str = s;

        e->y = (float)(font_GetHeight() + 449);
        e->size = font_CheckAlign(&e->col, *e->str);
    }
    return rollNameIdx >= D_0063B674;
}

extern unsigned char D_0063B66B;

void staffRollMain(void)
{
    int a;
    int n;

    if (closing != 0) {
        n = 0;
        staffRollArea[0] = (int)((float)staffRollArea[0] - areaStep);
        if (staffRollArea[0] < -0x1400) {
            staffRollArea[0] = -0x1400;
            n = 1;
        }
        rollWidth = (int)((float)rollWidth - widthStep);
        if (rollWidth < 0x280) {
            rollWidth = 0x280;
            n++;
        }
        if (n == 2) {
            closing = 0;
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
    /* volatile: measured 2026-09-15, dropping it sinks this store into the
       following bc1f delay slot where ROM keeps it between the two lwc1 and
       the c.lt.s. No async writer is proven, D_0063B66B is read and written
       only by this function (five ROM sites) and by nothing else in the ELF. */
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

    switch (rollStep) {
    case 0:
        font_Init();
        D_0063B66B = 0;
        rollStep++;
        /* fallthrough */
    case 1:
        staffRollCenterOffsetXDest = 0.0f;
        if (D_0063B66B == staffRollAlpha && staffRollCenterOffsetX == staffRollCenterOffsetXDest) {
            rollStep++;
        }
        break;
    case 2:
        staffRollScroll();
        if (staffRollNameOut() != 0) {
            rollStep++;
        }
        break;
    case 3:
        if (staffRollScroll() == 0) {
            rollStep++;
        }
        break;
    case 4:
        staffRollAlpha = 0;
        staffRollCenterOffsetXDest = 0.0f;
        if (D_0063B66B == 0) {
            rollStep++;
        }
        break;
    case 5:
        if (staffRollCenterOffsetX == 0.0f) {
            rollStep++;
        }
        break;
    case 6:
        staffRollStartFlag = 0;
        break;
    }
}

void staffRollWide(void)
{
    closing = 1;
    areaStep = (float)((staffRollArea[0] + 0x1400) / 30);
    widthStep = (float)((rollWidth - 0x280) / 30);
    staffRollAlpha = 0xFF;
}
