#include "staffroll.h"
#include "debug.h"
#include "DisplayFont.h"
#include <string.h>
#include "main.h"
#include "debug_exception.h"
#include <assert.h>

#ifdef VERSION_JUN26
#include "GifPacket.h"
#include "DmaPacket.h"
#include "GsBase.h"

/* staffroll.o's whole .data run: the roll's display area, {x, y, width,
   height}, which staffRollMain draws as a sprite.  x is also the running
   scroll position, which starts at 1280 in this build. */
static int staffRollArea[4] = {1280, -1792, 10240, 3584}; /* derived name */

/* one posted line, 8 bytes in this build (staffRollNameOut indexes the table
   with a shift of 3): no alignment or colour per line */
typedef struct {             /* field names derived */
    char **str;              /* 0x00 */
    float y;                 /* 0x04 */
} StaffRollEntry; /* 0x08 */ /* derived name */
#else
/* staffroll.o's whole .data run: the roll's display area, centred on the
   origin, {x, y, width, height}.  Only the first word is read here, as the
   running scroll position. */
static int staffRollArea[4] = {-5120, -1792, 10240, 3584}; /* derived name */

typedef struct {             /* field names derived */
    char **str;              /* 0x00 */
    float y;                 /* 0x04 */
    char align;              /* 0x08, font_CheckAlign's result for the line */
    SprCol col;              /* 0x09 */
    char pad[3];             /* 0x0D */
} StaffRollEntry; /* 0x10 */ /* derived name */
#endif

/* .sbss */
static float rollSpeed; /* derived name */ /* lines the roll climbs per frame */

static float rollOffset; /* derived name */ /* how far it has climbed so far */

static int rollNameIdx; /* derived name */ /* the next entry of staffRollNameData to post */

static int rollWidth; /* derived name */ /* the roll's right edge, closing in on 640 */

static float areaStep; /* derived name */ /* per-frame close of the display area */

static float widthStep; /* derived name */ /* per-frame close of rollWidth */

static int closing; /* derived name */ /* the area is closing */

static int rollStep; /* derived name */ /* the roll's own sequence step */

/* .bss: the posted lines, 0x12C0 bytes of StaffRollEntry */
static StaffRollEntry rollLines[300]; /* derived name */

/* .sdata: the three globals the roll's state starts with; the roll's colour
   and staffRollAlpha are defined after staffRollNameOut. */
int staffRollStartFlag = 0;

float staffRollCenterOffsetX = 0.0f;

float staffRollCenterOffsetXDest = 0.0f;

void staffRollStart(float t, int alpha)
{
    staffRollStartFlag = 1;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
    rollSpeed = t + t;
#else
#ifdef VERSION_JUN26
    rollSpeed = t * 6.0f / 4.0f;
#else
    rollSpeed = (t + t) * 30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
#endif
#endif
    staffRollAlpha = alpha;
    rollNameIdx = 0;
    rollOffset = 0.0f;
    rollStep = 0;
#ifdef VERSION_JUN26
    rollWidth = 404;
#else
    rollWidth = 0;
#endif
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
#ifdef VERSION_JUN26
    char **str;
#endif

    count = 0;

    rollOffset += rollSpeed;
#ifdef VERSION_JUN26
    for (i = 0; i < 300 * 8; i += 8) {
        str = SROLL(i)->str;
        if (str == 0) {
#else
    for (i = 0; i < 300 * 16; i += 16) {
        if (SROLL(i)->str == 0) {
#endif
            continue;
        }
        count++;

        SROLL(i)->y -= rollSpeed;
#ifdef VERSION_JUN26
        t = SROLL(i)->y - (float)(ScreenHeight >> 2);
        a = (int)(136.0f - (t < 0.0f ? -t : t) * 120.0f / (float)(ScreenHeight >> 2));
#else
        t = SROLL(i)->y - 112.0f;
        a = (int)(184.0f - (t < 0.0f ? -t : t) * 120.0f / 112.0f);
#endif
        if (a < 0) {
            a = 0;
        }
#ifdef VERSION_JUN26
        if (-8.0f < SROLL(i)->y) {
            font_Print(rollWidth, (int)SROLL(i)->y, a | 0xA0A0A000, *str);
#else
        if (a > 128) {
            a = 128;
        }
        if ((float)(-(font_GetHeight() + 449)) < SROLL(i)->y) {
            font_Print(a | 0x70707000, *SROLL(i)->str, (float)rollWidth, SROLL(i)->y,
                       SROLL(i)->align, SROLL(i)->col);
#endif
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

#ifdef VERSION_JUN26
    if (rollOffset / 6.0f >= (float)rollNameIdx) {
#else
    if (rollOffset / (float)(font_GetHeight() + 1) >= (float)rollNameIdx) {
#endif
        for (i = 0; i < 300; i++) {
            if (rollLines[i].str == 0)
                goto found;
        }
        /* staff roll: out of area */
        debug_StdPrintfDummy("staff roll 領域不足\n");
        debug_assert(__FILE__, LN(192, 189, 189, 189, 189, 165, 189));
        __assert(__FILE__, LN(192, 189, 189, 189, 189, 165, 189), "0");
    found:

        e = &rollLines[i];
        s = &staffRollNameData[rollNameIdx++];
        if (*s != 0)
            e->str = s;

#ifdef VERSION_JUN26
        e->y = 246.0f;
#else
        e->y = (float)(font_GetHeight() + 449);
        e->align = font_CheckAlign(&e->col, *e->str);
#endif
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

#ifdef VERSION_JUN26
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
#endif
    if (closing != 0) {
        n = 0;
        staffRollArea[0] = (int)((float)staffRollArea[0] - areaStep);
        if (staffRollArea[0] < -5120) {
            staffRollArea[0] = -5120;
            n = 1;
        }
        rollWidth = (int)((float)rollWidth - widthStep);
#ifdef VERSION_JUN26
        if (rollWidth < 220) {
            rollWidth = 220;
#else
        if (rollWidth < 640) {
            rollWidth = 640;
#endif
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
#ifndef VERSION_JUN26
        font_Init();
#endif
        rollColour[3] = 0;
        rollStep++;
        /* fallthrough */
    case 1:
#ifdef VERSION_JUN26
        staffRollCenterOffsetXDest = (float)ScreenWidth * 120.0f / 640.0f;
#else
        staffRollCenterOffsetXDest = 0.0f;
#endif
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
#ifdef VERSION_JUN26
    widthStep = (float)((rollWidth - 220) / 30);
#else
    widthStep = (float)((rollWidth - 640) / 30);
#endif
    staffRollAlpha = 255;
}
