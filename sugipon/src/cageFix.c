#include "common.h"

extern void func_0010F048(int a0);
extern void file_LoadCDFile(void *a0);

void CageFixGeo(void *a0) {
    void *p = *(void **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    func_0010F048((int)a0);
    file_LoadCDFile(*(void **)p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cageFix", CageFixDL);

void InitCageFixGeo(void *a0, float a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *(float *)((char *)q + 0x3C) = a1;
}

extern int *isysGObjSearchFromObjLayoutID(int x);
extern void CageDL(int *p);
extern int *isysGObjSearchFromObjKindID_begin(int *p);

void func_001C0138(void)
{
    int *p = isysGObjSearchFromObjLayoutID(0x2B);
    if (p != 0) {
        do {
            CageDL(p);
            p = isysGObjSearchFromObjKindID_begin(p);
        } while (p != 0);
    }
}

void func_001C0180(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    *(int *)((char *)q + 0x40) = a1;
}

extern int func_00105078(void);
extern void MatrixDrive_TurnXObjectMatrixYZ(int a0, int a1);
extern void HotInitCageGeo(void *a0, int a1, int a2);

void func_001C0190(int *self)
{
    void *s0 = isysGObjSearchFromObjLayoutID(0x2B);
    if (s0 != 0) {
        int *p;
        int v;
        v = func_00105078();
        p = (int *)self[0x57];
        MatrixDrive_TurnXObjectMatrixYZ(v, p[3]);
        v = func_00105078();
        p = (int *)self[0x57];
        HotInitCageGeo(s0, v + 0x30, p[4]);
    }
}
