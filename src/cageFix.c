#include "common.h"



extern int *func_00105278(void);
extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern void HotInitCageGeo(int *self, int a1, int a2);
extern int isysGObjSearchFromObjKindID_begin();
extern void CageDL();
extern int isysGObjSearchFromObjLayoutID();
INCLUDE_ASM("asm/nonmatchings/src/cageFix", CageFixGeo);

INCLUDE_ASM("asm/nonmatchings/src/cageFix", CageFixDL);

INCLUDE_ASM("asm/nonmatchings/src/cageFix", InitCageFixGeo);

void func_001C2EC8(void)
{
    int *p = isysGObjSearchFromObjLayoutID(0x2B);
    if (p != 0) {
        do {
            CageDL(p);
            p = isysGObjSearchFromObjKindID_begin(p);
        } while (p != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cageFix", func_001C2F10);

void func_001C2F20(int *self)
{
    void *s0 = isysGObjSearchFromObjLayoutID(0x2B);
    if (s0 != 0) {
        int *p;
        int v;
        v = func_00105278();
        p = (int *)self[0x57];
        MatrixDrive_TurnXObjectMatrixYZ(v, p[3]);
        v = func_00105278();
        p = (int *)self[0x57];
        HotInitCageGeo(s0, v + 0x30, p[4]);
    }
}

