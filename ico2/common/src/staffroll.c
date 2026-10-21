#include "staffroll.h"
#include "debug.h"
#include "DisplayFont.h"
#include <string.h>
#include "main.h"
#include "debug_exception.h"
#include <assert.h>
#include "GifPacket.h"
#include "DmaPacket.h"
#include "GsBase.h"

/* staffroll.o's whole .data run: the roll's display area, {x, y, width,
   height}.  Only the first word is read here, as the running scroll
   position, which starts at 1280 in this build. */
static int staffRollArea[4] = {1280, -1792, 10240, 3584}; /* derived name */

/* one posted line, 8 bytes in this build (staffRollNameOut indexes the table
   with a shift of 3): no alignment or colour per line */
typedef struct {             /* field names derived */
    char **str;              /* 0x00 */
    float y;                 /* 0x04 */
} StaffRollEntry; /* 0x08 */ /* derived name */

/* .sbss */
static float rollSpeed; /* derived name */ /* lines the roll climbs per frame */

static float rollOffset; /* derived name */ /* how far it has climbed so far */

static int rollNameIdx; /* derived name */ /* the next entry of staffRollNameData to post */

static int rollWidth; /* derived name */ /* the roll's right edge, closing in on 640 */

static float areaStep; /* derived name */ /* per-frame close of the display area */

static float widthStep; /* derived name */ /* per-frame close of rollWidth */

static int closing; /* derived name */ /* the area is closing */

static int rollStep; /* derived name */ /* the roll's own sequence step */

/* .bss: the posted lines, 0x960 bytes of StaffRollEntry */
static StaffRollEntry rollLines[300]; /* derived name */

/* .sdata: the three globals the roll's state starts with; the roll's colour
   and staffRollAlpha are defined after staffRollNameOut. */
int staffRollStartFlag = 0;

float staffRollCenterOffsetX = 0.0f;

float staffRollCenterOffsetXDest = 0.0f;

void staffRollStart(float t, int alpha)
{
    staffRollStartFlag = 1;
    rollSpeed = t * 6.0f / 4.0f;
    staffRollAlpha = alpha;
    rollNameIdx = 0;
    rollOffset = 0.0f;
    rollStep = 0;
    rollWidth = 404;
    closing = 0;
    staffRollCenterOffsetX = staffRollCenterOffsetXDest = rollOffset;
    staffRollArea[0] = 1280;
    memset(rollLines, 0, sizeof(rollLines));
}

/* The scroll loop walks the 300-entry table by byte offset and spells the
   base at every use site. */
#define SROLL(off) ((StaffRollEntry *)((char *)rollLines + (off)))

static int staffRollScroll(void)
{
    int count;
    int i;
    int a;
    float t;
    char **str;

    count = 0;

    rollOffset += rollSpeed;
    for (i = 0; i < 300 * 8; i += 8) {
        str = SROLL(i)->str;
        if (str == 0) {
            continue;
        }
        count++;

        SROLL(i)->y -= rollSpeed;
        t = SROLL(i)->y - (float)(ScreenHeight >> 2);
        a = (int)(136.0f - (t < 0.0f ? -t : t) * 120.0f / (float)(ScreenHeight >> 2));
        if (a < 0) {
            a = 0;
        }
        if (-8.0f < SROLL(i)->y) {
            font_Print(rollWidth, (int)SROLL(i)->y, a | 0xA0A0A000, *str);
        } else {
            SROLL(i)->str = 0;
        }
    }

    return count;
}

static int staffRollNameOut(void)
{
    StaffRollEntry *e;
    char **s;
    int i;

    if (rollOffset / 6.0f >= (float)rollNameIdx) {
        for (i = 0; i < 300; i++) {
            if (rollLines[i].str == 0)
                goto found;
        }
        /* staff roll: out of area */
        debug_StdPrintfDummy("staff roll 領域不足\n");
        debug_assert(__FILE__, 165);
        __assert(__FILE__, 165, "0");
    found:

        e = &rollLines[i];
        s = &staffRollNameData[rollNameIdx++];
        if (*s != 0)
            e->str = s;

        e->y = 246.0f;
    }
    return rollNameIdx >= staffRollNameDataNum;
}

/* the roll's colour; only its alpha byte is read and written, fading toward
   staffRollAlpha.  A 4-byte array is 8-aligned, which leaves the zero word
   after the assert text. */
static unsigned char rollColour[4] = {0}; /* derived name */

int staffRollAlpha = 0;

void staffRollMain(void)
{
    int a;
    int n;

    /* the roll's display area, a z-masked sprite in the roll colour */
    gif_StartPacketPri(11);
    gif_SetGsReg(71, 0x30000);
    gif_SetGsReg(78, 0x1300000C0LL);
    *PacketBufferStruct.ptr.d++ = 0;
    *PacketBufferStruct.ptr.d++ = 73;
    *PacketBufferStruct.ptr.d++ = 68;
    *PacketBufferStruct.ptr.d++ = 66;
    *PacketBufferStruct.ptr.d++ = (1 << 6) | 0x406;
    *PacketBufferStruct.ptr.d++ = 0;
    *PacketBufferStruct.ptr.d++ = (long long)rollColour[0] | ((long long)rollColour[1] << 8) |
                                  ((long long)rollColour[2] << 16) |
                                  ((long long)rollColour[3] << 24);
    *PacketBufferStruct.ptr.d++ = 1;
    *PacketBufferStruct.ptr.d++ =
        (long long)(staffRollArea[0] * ScreenWidth / 640 + 0x8000) |
        ((long long)(staffRollArea[1] * ScreenHeight / 224 + 0x8000) << 16) | (0xFFFFFFFFLL << 32);
    *PacketBufferStruct.ptr.d++ = 5;
    *PacketBufferStruct.ptr.d++ = (long long)(staffRollArea[0] * ScreenWidth / 640 + 0x8000 +
                                              staffRollArea[2] * ScreenWidth / 640) |
                                  ((long long)(staffRollArea[1] * ScreenHeight / 224 + 0x8000 +
                                               staffRollArea[3] * ScreenHeight / 224)
                                   << 16) |
                                  (0xFFFFFFFFLL << 32);
    *PacketBufferStruct.ptr.d++ = 5;
    gif_EndPacket();

    if (closing != 0) {
        n = 0;
        staffRollArea[0] = (int)((float)staffRollArea[0] - areaStep);
        if (staffRollArea[0] < -5120) {
            staffRollArea[0] = -5120;
            n = 1;
        }
        rollWidth = (int)((float)rollWidth - widthStep);
        if (rollWidth < 220) {
            rollWidth = 220;
            n++;
        }
        if (n == 2) {
            closing = 0;
        }
    }

    a = rollColour[3];
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
    /* the roll colour's alpha, a volatile store */
    *(volatile unsigned char *)&rollColour[3] = a;

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
        rollColour[3] = 0;
        rollStep++;
        /* fallthrough */
    case 1:
        staffRollCenterOffsetXDest = (float)ScreenWidth * 120.0f / 640.0f;
        if (rollColour[3] == staffRollAlpha &&
            staffRollCenterOffsetX == staffRollCenterOffsetXDest) {
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
        if (rollColour[3] == 0) {
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
    areaStep = (float)((staffRollArea[0] + 5120) / 30);
    widthStep = (float)((rollWidth - 220) / 30);
    staffRollAlpha = 255;
}
