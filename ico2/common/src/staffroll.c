#include "staffroll.h"
#include "debug.h"
#include "DisplayFont.h"
#include <string.h>
#include "main.h"
#include "debug_exception.h"
#include <assert.h>
#include "include_asm.h"

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

INCLUDE_ASM(staffRollStart);

/* The scroll loop walks the 300-entry table by byte offset and spells the
   base at every use site. */
#define SROLL(off) ((StaffRollEntry *)((char *)rollLines + (off)))

INCLUDE_ASM(staffRollScroll);

INCLUDE_ASM(staffRollNameOut);

/* the roll's colour; only its alpha byte is read and written, fading toward
   staffRollAlpha.  A 4-byte array is 8-aligned, which leaves the zero word
   after the assert text. */
static unsigned char rollColour[4] = {0}; /* derived name */

int staffRollAlpha = 0;

INCLUDE_ASM(staffRollMain);

INCLUDE_ASM(staffRollWide);
