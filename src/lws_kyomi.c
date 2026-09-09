#include "common.h"

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
extern void memset(void *a0, int a1, int a2);
extern char *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
extern int iosMallocDebug(int heap, int size, const char *file, int line);
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
    gobj = CreateLayoutedGObj(0x3D, 0x4B, -1, 0, lay, 1, 7, 0);
    hint = (struct HintInfo *)iosMallocDebug(D_0063A438, 16, D_005556A8, 101);
    *(struct HintInfo **)(*(char **)(gobj + 0x15C) + 0x830) = hint;
    *hint = D_002A6020;
    hint->_0 = no;
    for (i = 0; i < 0x1C; i++) {
        if (D_002ADBA0[i]._0 == stage_no && D_002ADBA0[i].no == no) {
            hint->no = i;
            hint->time = (int)(D_002ADBA0[i].time * 60.0f * 60.0f *
                               (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f);
        }
    }
    brainStatusDefaultSet(D_002A5580, (int)gobj, 1);
    return gobj;
}

extern float *D_0063C2E8;
extern float D_0063922C;
extern int stage_CheckAnimationFinish(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void brainSubLevelGop(void *gobj, float lv);

void LwsKyomiGeo(void *gobj)
{
    struct HintInfo *hint;
    int i;
    unsigned char fin;

    hint = *(struct HintInfo **)(*(char **)((char *)gobj + 0x15C) + 0x830);
    hint->flags &= ~1;
    for (i = 0; i < 0x1C; i++) {
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
            D_0063C2E8[hint->no] += 1.0f;
            if ((float)hint->time < D_0063C2E8[hint->no]) {
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
    brainSubLevelGop(gobj, D_0063922C);
}

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
