#include "sceneManager.h"
#include "memory.h"
#include "StageAnimation.h"
#include "debug.h"
#include <string.h>
#include "typedef.h"
#include "ios.h"
#include "lws_kyomi.h"
#include "main.h"
#include "geometryManager.h"
#include "brain.h"
#include "include_asm.h"

struct HintInfo { /* field names derived */
    int anim;     /* the stage animation the hint plays */
    int no;
    int time;
    int flags;
};

/* The two 4-byte hint flag sets the save block carries, then one timer per
   hint; Hint_Init clears the whole record. */
static struct {      /* field names derived */
    char save[8];    /* 0x00 */
    float timer[28]; /* 0x08 */
} hintWork;          /* derived name */

/* the record a new hint GObj starts from: no stage, no hint, no time, no
   flags */
static struct HintInfo hintDefault = {-1, -1, -1, 0}; /* derived name */

INCLUDE_ASM(LwsKyomiGeo);

INCLUDE_ASM(CreateKyomiGObj);

/* the hint timers, a window onto the per-hint elapsed-time array */
static float *hintTimers; /* derived name */

/* Clear one 4-byte half of the save block, then pack one flag bit of every
 * hint into it.  `buf` is the half being packed and `off` its byte offset
 * inside the block. */
#define MAKE_HINT_SAVE_BITS(buf, off, bit) /* derived name */                                      \
    for (i = 0; i < 4; i++) {                                                                      \
        hintWork.save[(off) + i] = 0;                                                              \
    }                                                                                              \
    for (i = 0; i < 28; i++) {                                                                     \
        if (((unsigned int)hintTable[i].flags >> (bit)) & 1) {                                     \
            int m = 1 << (i % 8);                                                                  \
            (buf)[i / 8] |= m;                                                                     \
        }                                                                                          \
    }
/* the inverse of MAKE_HINT_SAVE_BITS, unpacking one 4-byte half back into the
 * flag bit */
#define READ_HINT_SAVE_BITS(buf, bit) /* derived name */                                           \
    end = 0;                                                                                       \
    for (k = 0; k < 28; k++) {                                                                     \
        (hintTable + k)->flags &= ~(1 << (bit));                                                   \
    }                                                                                              \
    n = 0;                                                                                         \
    for (k = 0; k < 4; k++) {                                                                      \
        for (j = 0; j < 8; j++) {                                                                  \
            if ((((unsigned char *)(buf))[k] >> j) & 1) {                                          \
                (hintTable + n)->flags |= 1 << (bit);                                              \
            }                                                                                      \
            n++;                                                                                   \
            if (n < 28) {                                                                          \
                continue;                                                                          \
            }                                                                                      \
            end = 1;                                                                               \
            break;                                                                                 \
        }                                                                                          \
        if (end) {                                                                                 \
            break;                                                                                 \
        }                                                                                          \
    }

void SetParamKyomiGObj(GObj *gobj, float *root, float *param)
{
    float pos[4];
    float lv;
    int on1;
    int on2;

    on1 = 1;
    lv = param[0];
    if (param[1] < 0.5f) {
        on1 = 0;
    }
    on2 = 1;
    if (param[2] < 0.5f) {
        on2 = 0;
    }
    if (debug_lwskyomi_lookonly != 0) {
        if (on2 != 0) {
            on1 = 1;
        }
    }
    SetDirectRootPosition(gobj, root);
    UpdateRootMatrix(gobj);
    GetRootPosition(pos, gobj);
    brainSetLevelGop(gobj, lv, on1, on2);
}
