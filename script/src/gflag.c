#include "common.h"

extern void *actSt25aQueenDeadChk(void);
extern void func_001EE9A8(void *a0);

void gflagInit(void) {
    void *r = actSt25aQueenDeadChk();
    if (r) {
        func_001EE9A8(r);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", gflagSave);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", gflagLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", gflagChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", gflagOn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", gflagOff);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_00179060);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_001790A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_001790E8);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A008);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A040);

extern void *isysGObjAddHead(void);
extern void DispAllSpiderGroups(void *a0);

void func_0017A078(void) {
    void *r = isysGObjAddHead();
    if (r) {
        DispAllSpiderGroups(r);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A0A8);

extern void *isysGObjAddHead(void);
extern void EntryRevivedSpiderGroupManager(void *a0);

void func_0017A0D8(void) {
    EntryRevivedSpiderGroupManager(isysGObjAddHead());
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A0F8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A158);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A198);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A1E0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/gflag", func_0017A220);
