#include "common.h"

/* gflag 0x164 actor-state view (local) */
typedef struct { char _0[0x18]; long long f_18; } GflagState;

extern void *actSt25aQueenDeadChk(void);
extern void func_001EE9A8(void *a0);

void gflagInit(void) {
    void *r = actSt25aQueenDeadChk();
    if (r) {
        func_001EE9A8(r);
    }
}

extern void func_001EEB10(void *a0);

void gflagSave(void) {
    void *r = actSt25aQueenDeadChk();
    if (r) {
        func_001EEB10(r);
    }
}

extern void InitCageFixGeo(int *p, float f12);
extern int D_00554140[];
extern void debug_assertMessage(int *a0);

void gflagLoad(float f12) {
    int *v = actSt25aQueenDeadChk();
    if (v) {
        InitCageFixGeo(v, f12);
    }
    debug_assertMessage(D_00554140);
}

extern void func_0023FE98(int a0);
extern int dispPlane(int a0, int a1);

void gflagChk(int a0, int a1)
{
    int new_var;
    new_var = 1;
    if (new_var) {
        func_0023FE98(a1);
    }
    return dispPlane(a0, (0, a1));
}

extern void actCommonStoneDead(void *a0, int a1, float f12);
typedef struct { char _0[0x138]; int f_138; char _13C[0x54]; } MotionOrientRec; /* stride 0x190 */
extern MotionOrientRec D_0055DA10[];

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", gflagOn);


extern void *isysGObjAddHead();
extern void actCommonSlowrun(int a0, int a1);
extern int ExecMotionOrient(void *a0, int a1, int a2);
extern void func_001E1A18(void *a0, int a1, int a2, int a3, int a4, int a5);
extern void *D_00629DE4;
extern void *D_00629DE8;

void gflagOff(void *a0, int a1) {
    int state = -1;
    int s3 = *(int *)((char *)a0 + 0x164);
    if (a0 == D_00629DE4) {
        state = 0x4A9;
    } else if (a0 == D_00629DE8) {
        state = 0x701;
    } else if (a0 == isysGObjAddHead(0x796)) {
        state = 0x826;
    } else if ((*(int *)((char *)a0 + 0xC) ^ 4) == 0) {
        state = 0x81E;
    }
    if (state < 0) {
        func_001E1A18(a0, 0x705, 0x820, -1, -1, a1);
        return;
    }
    actCommonSlowrun(state, a1);
    *(int *)(s3 + 0x110) = ExecMotionOrient(a0, 0xEA, s3 + 0x610);
}


extern void func_0014A110(void *a0);
extern void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);

void func_00179060(void *a0, int a1) {
    func_0014A110(a0);
    *(int *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x670) + 0xC0) = a1;
    iosOmBeforeFuncStandard(a0, 0x2C, a0);
}

extern void func_0014A110(void *a0);
extern void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern void func_001D1ED8(void *a0, int a1);

void func_001790A8(void *a0) {
    func_0014A110(a0);
    iosOmBeforeFuncStandard(a0, 0x2D, a0);
    func_001D1ED8(a0, 0);
}

extern void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern void func_001D1ED8(void *a0, int a1);

void func_001790E8(void *a0) {
    iosOmBeforeFuncStandard(a0, 0x2E, a0);
    func_001D1ED8(a0, 2);
}

extern void UpdateRootMatrixByDObj(int a0, float a1, float a2, float a3);

void func_00179120(int a0, float *a1) {
    UpdateRootMatrixByDObj(a0, a1[0], a1[1], a1[2]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179130);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_001792E0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179430);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179580);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179710);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179D00);

extern void GetOtherStageGirlOrient(void *a0);

void func_00179F60(void *a0) {
    GflagState *p = *(GflagState **)((char *)a0 + 0x164);
    p->f_18 &= 0xFFFFFBFFFFFFFFFFLL;
    GetOtherStageGirlOrient(a0);
}

extern void *D_00629DE8;
extern void *D_00629DE4;
extern int D_00629C90;
extern void func_001AB9B8(void *a0, int a1, int a2, int a3);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
extern void func_00178E08(int a0);
extern void backStageProcessMain(void);

void func_00179F88(void) {
    int s0;
    if (D_00629DE8) {
        func_001AB9B8(D_00629DE8, *(int *)((char *)*(void **)((char *)D_00629DE8 + 0x164) + 0x434), 0, D_00629C90);
    }
    func_001AB9B8(D_00629DE4, *(int *)((char *)*(void **)((char *)D_00629DE4 + 0x164) + 0x434), 0, D_00629C90);
    s0 = func_00178DB0(0x15B);
    func_00178DD8(0x15B);
    backStageProcessMain();
    if (s0 == 0) {
        func_00178E08(0x15B);
    }
}

extern void *isysGObjAddHead();

void func_0017A008(void) {
    void *p = isysGObjAddHead();
    if (p != 0) {
        iosOmBeforeFuncStandard(p, 0x1F, p);
    }
}

void func_0017A040(void) {
    void *p = isysGObjAddHead();
    if (p != 0) {
        iosOmBeforeFuncStandard(p, 0x20, p);
    }
}

extern void DispAllSpiderGroups(void *a0);

void func_0017A078(void) {
    void *r = isysGObjAddHead();
    if (r) {
        DispAllSpiderGroups(r);
    }
}

extern void EntryToSpiderGroupManagerForReviveMaster(void *a0);

void func_0017A0A8(void) {
    void *r = isysGObjAddHead();
    if (r) {
        EntryToSpiderGroupManagerForReviveMaster(r);
    }
}

extern void EntryRevivedSpiderGroupManager(void *a0);

void func_0017A0D8(void) {
    EntryRevivedSpiderGroupManager(isysGObjAddHead());
}

typedef struct { char _0[0xA0]; short arr[0x78]; } OuterRec0F8;
typedef struct { char _0[0x24]; int f24; } Rec28_0F8;
extern int D_00629C90;
extern OuterRec0F8 D_005EBC48[];
extern Rec28_0F8 D_0055A2D8[];
extern void stgmgrForceSwitchWithFade(int a0);
extern void backStageProcessOutStage(int a0);

void func_0017A0F8(int a0) {
    short v = D_005EBC48[D_00629C90].arr[a0 - 1];
    stgmgrForceSwitchWithFade(D_0055A2D8[v].f24);
    backStageProcessOutStage(1);
}

extern int isysGObjSearchFromObjLayoutID();
extern int isysGObjSearchFromObjKindID_begin(int a0);

void func_0017A158(void)
{
    int v0 = isysGObjSearchFromObjLayoutID();
    while (v0 != 0) {
        *(int *)(v0 + 0x50) = 0;
        v0 = isysGObjSearchFromObjKindID_begin(v0);
    }
}


void func_0017A198(int x)
{
  unsigned int new_var;
  int *p = isysGObjSearchFromObjLayoutID(x);
  while (p != 0)
  {
    new_var = (int) 0xFFFFFFFFU;
    p[0x50 / 4] = new_var;
    p = isysGObjSearchFromObjKindID_begin(p);
  }

}

void func_0017A1E0(void)
{
    int *p = isysGObjSearchFromObjLayoutID();
    while (p != 0) {
        p[0x16C / 4] = 1;
        p = isysGObjSearchFromObjKindID_begin(p);
    }
}

void func_0017A220(void)
{
    int v0 = isysGObjSearchFromObjLayoutID();
    while (v0 != 0) {
        *(int *)(v0 + 0x16C) = 0;
        v0 = isysGObjSearchFromObjKindID_begin(v0);
    }
}
