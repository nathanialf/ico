#include "common.h"

struct HintInfo {
    int _0;
    int no;
    int time;
    int flags;
};

extern struct HintInfo D_002ADBA0[];
extern char D_006E99B0[];
extern char D_006E99B4[];

INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", CreateKyomiGObj);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", LwsKyomiGeo);

/* lws_kyomi.c:264 and :265 are one source line each, so the clear-then-pack
 * pair of loops is a macro; the name is ours.  `buf` is the 4-byte half of the
 * save block being packed and `off` its byte offset inside it. */
#define MAKE_HINT_SAVE_BITS(buf, off, bit)                                                         \
    for (i = 0; i < 4; i++) {                                                                      \
        D_006E99B0[(off) + i] = 0;                                                                 \
    }                                                                                              \
    for (i = 0; i < 0x1C; i++) {                                                                   \
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

INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", ReadHintSaveInfo);

extern int D_0063B238;
extern void SetDirectRootPosition(void *gobj);
extern void UpdateRootMatrix(void *gobj);
extern void GetRootPosition(void *out, void *gobj);
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

INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", IsTopHint);

extern float *D_0063C2E8;

void DebugHintStart(void *gobj)
{
    struct HintInfo *hint;

    hint = *(struct HintInfo **)(*(char **)((char *)gobj + 0x15C) + 0x830);
    D_0063C2E8[hint->no] = hint->time;
}

int GetSizeHintSaveInfo(void)
{
    return 0x78;
}

char *GetBuffHintSaveInfo(void)
{
    return D_006E99B0;
}

extern void memset(void *a0, int a1, int a2);
extern float D_006E99B8[];

void Hint_Init(void)
{
    struct HintInfo *p;
    int i;

    D_0063C2E8 = D_006E99B8;
    memset((char *)D_006E99B8 - 8, 0, 0x78);
    p = D_002ADBA0;
    for (i = 0; i < 28; i++) {
        p->flags &= ~2;
        p->flags &= ~1;
        p++;
    }
}
