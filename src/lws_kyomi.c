#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", CreateKyomiGObj);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", LwsKyomiGeo);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", MakeHintSaveInfo);
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
struct HintInfo {
    int  _0;
    int  no;
    int  time;
    int  flags;
};
extern struct HintInfo D_002ADBA0[];

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
int GetSizeHintSaveInfo(void) {
    return 0x78;
}
extern char D_006E99B0[];
char *GetBuffHintSaveInfo(void) {
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
