#include "common.h"
#include "sceneManager.h"
#include "memory.h"
#include "StageAnimation.h"
#include <string.h>

struct HintInfo {
    int _0;
    int no;
    int time;
    int flags;
};

/* The hint TABLE's element type differs from the per-GObj record above in one
 * field: D_002ADBA0[i].time is a float (seconds), the record's is an int
 * (frames).  CreateKyomiGObj converts one into the other. */
struct HintDef {
    int _0;
    int no;
    float time;
    int flags;
};

extern struct HintDef D_002ADBA0[];
extern char D_006E99B0[];
extern char D_006E99B4[];
extern struct HintInfo D_002A6020;
extern int D_0028F4C0[];
extern int D_0063A438;
extern char D_005556A8[];
extern int D_002A5580[];
/* kept local: this TU's uses of brainStatusDefaultSet do not fit the prototype in brain.h */
extern void brainStatusDefaultSet(void *b, int gobj, int idx);
extern int stage_no;

char *CreateKyomiGObj(int no)
{
    float lay[16];
    char *gobj;
    struct HintInfo *hint;
    int i;

    memset(lay, 0, 0x40);
    lay[8] = 1.0f;
    lay[9] = 1.0f;
    lay[10] = 1.0f;
    gobj = CreateLayoutedGObj(61, 0x4B, -1, 0, lay, 1, 7, 0);
    hint = (struct HintInfo *)iosMallocDebug(D_0063A438, 16, D_005556A8, 101);
    *(struct HintInfo **)(*(char **)(gobj + 0x15C) + 0x830) = hint;
    *hint = D_002A6020;
    hint->_0 = no;
    for (i = 0; i < 28; i++) {
        if (D_002ADBA0[i]._0 == stage_no && D_002ADBA0[i].no == no) {
            hint->no = i;
            hint->time = (int)(D_002ADBA0[i].time * 60.0f * 60.0f *
                               (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f);
        }
    }
    brainStatusDefaultSet(D_002A5580, (int)gobj, 1);
    return gobj;
}

/* .sbss, owned by lws_kyomi.o (MAIN.MAP names no symbol in the run): the hint timers, a window onto the
   per-hint elapsed-time array */
static float *hintTimers;

/* kept local: this TU's uses of brainSubLevelGop do not fit the prototype in brain.h */
extern void brainSubLevelGop(void *gobj, float lv);

void LwsKyomiGeo(void *gobj)
{
    struct HintInfo *hint;
    int i;
    unsigned char fin;

    hint = *(struct HintInfo **)(*(char **)((char *)gobj + 0x15C) + 0x830);
    hint->flags &= ~1;
    for (i = 0; i < 28; i++) {
        if (D_002ADBA0[i]._0 == stage_no && (D_002ADBA0[i].flags & 1) == 0) {
            if ((((unsigned int)D_002ADBA0[i].flags >> 1) & 1) == 0 && i == hint->no) {
                hint->flags |= 1;
            }
            break;
        }
    }
    if (hint->no != -1) {
        fin = stage_CheckAnimationFinish(hint->_0);
        if (hint->flags & 1) {
            hintTimers[hint->no] += 1.0f;
            if ((float)hint->time < hintTimers[hint->no]) {
                if (fin != 0) {
                    stage_SetAnimation(hint->_0, 1, 0);
                }
            }
        } else {
            if (fin == 0) {
                stage_SetAnimation(hint->_0, -1, -2);
            }
        }
    }
    brainSubLevelGop(gobj, 0.1f);
}

/* lws_kyomi.c:264 and :265 are one source line each, so the clear-then-pack
 * pair of loops is a macro; the name is ours.  `buf` is the 4-byte half of the
 * save block being packed and `off` its byte offset inside it. */
#define MAKE_HINT_SAVE_BITS(buf, off, bit)                                                         \
    for (i = 0; i < 4; i++) {                                                                      \
        D_006E99B0[(off) + i] = 0;                                                                 \
    }                                                                                              \
    for (i = 0; i < 28; i++) {                                                                     \
        if (((unsigned int)D_002ADBA0[i].flags >> (bit)) & 1) {                                    \
            int m = 1 << (i % 8);                                                                  \
            (buf)[i / 8] |= m;                                                                     \
        }                                                                                          \
    }

void MakeHintSaveInfo(void)
{
    int i;

    MAKE_HINT_SAVE_BITS(D_006E99B0, 0, 0);
    MAKE_HINT_SAVE_BITS(D_006E99B4, 4, 1);
}

/* lws_kyomi.c:305 and :306 are one source line each: the inverse of
 * MAKE_HINT_SAVE_BITS, unpacking one 4-byte half back into the flag bit. */
#define READ_HINT_SAVE_BITS(buf, bit)                                                              \
    end = 0;                                                                                       \
    for (k = 0; k < 28; k++) {                                                                     \
        (D_002ADBA0 + k)->flags &= ~(1 << (bit));                                                  \
    }                                                                                              \
    n = 0;                                                                                         \
    for (k = 0; k < 4; k++) {                                                                      \
        for (j = 0; j < 8; j++) {                                                                  \
            if ((((unsigned char *)(buf))[k] >> j) & 1) {                                          \
                (D_002ADBA0 + n)->flags |= 1 << (bit);                                             \
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

void ReadHintSaveInfo(void)
{
    int j;
    int k;
    int n;
    int end;

    READ_HINT_SAVE_BITS(D_006E99B0, 0);
    READ_HINT_SAVE_BITS(D_006E99B4, 1);
}

extern int D_0063B238;
/* kept local: this TU's uses of SetDirectRootPosition do not fit the prototype in geometryManager.h */
extern void SetDirectRootPosition(void *gobj);
/* kept local: this TU's uses of UpdateRootMatrix do not fit the prototype in geometryManager.h */
extern void UpdateRootMatrix(void *gobj);
/* kept local: this TU's uses of GetRootPosition do not fit the prototype in geometryManager.h */
extern void GetRootPosition(void *out, void *gobj);
/* kept local: the declaration in brain.h changes this TU codegen */
extern void brainSetLevelGop(void *gobj, float lv, int a1, int a2);

void SetParamKyomiGObj(void *gobj, int a1, float *param)
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
    if (D_0063B238 != 0) {
        if (on2 != 0) {
            on1 = 1;
        }
    }
    SetDirectRootPosition(gobj);
    UpdateRootMatrix(gobj);
    GetRootPosition(pos, gobj);
    brainSetLevelGop(gobj, lv, on1, on2);
}

void FinishHint(int no)
{
    (D_002ADBA0 + no)->flags |= 1;
}

void SleepHint(int no)
{
    (D_002ADBA0 + no)->flags |= 2;
}

void WakeupHint(int no)
{
    (D_002ADBA0 + no)->flags &= ~2;
}

int IsTopHint(void *gobj)
{
    if (*(int *)((char *)gobj + 0xC) == 61) {
        struct HintInfo *hint = *(struct HintInfo **)(*(char **)((char *)gobj + 0x15C) + 0x830);

        if (hint->flags & 1) {
            return 1;
        }
    }
    return 0;
}

void DebugHintStart(void *gobj)
{
    struct HintInfo *hint;

    hint = *(struct HintInfo **)(*(char **)((char *)gobj + 0x15C) + 0x830);
    hintTimers[hint->no] = hint->time;
}

int GetSizeHintSaveInfo(void)
{
    return 0x78;
}

char *GetBuffHintSaveInfo(void)
{
    return D_006E99B0;
}

extern float D_006E99B8[];

void Hint_Init(void)
{
    struct HintInfo *p;
    int i;

    hintTimers = D_006E99B8;
    memset((char *)D_006E99B8 - 8, 0, 0x78);
    p = D_002ADBA0;
    for (i = 0; i < 28; i++) {
        p->flags &= ~2;
        p->flags &= ~1;
        p++;
    }
}
