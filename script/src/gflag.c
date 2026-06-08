#include "common.h"

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", gflagOn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", gflagOff);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179060);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_001790A8);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179D00);

extern void GetOtherStageGirlOrient(void *a0);

void func_00179F60(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    *(long long *)(p + 0x18) &= 0xFFFFFBFFFFFFFFFFLL;
    GetOtherStageGirlOrient(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179F88);

extern void *isysGObjAddHead(void);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A0F8);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A220);
