#include "common.h"
#include "ico/types.h"

extern void func_0010F048(int a0);
extern void file_LoadCDFile(void *a0);

void CageFixGeo(GObj *a0) {
    Obj7F0 *base = GOBJ_SUB(a0)->p_7F0;
    func_0010F048((int)a0);
    file_LoadCDFile(base->p_0);
}

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

int CageFixDL(int a0, int a1, GObj *ctx)
{
    Obj7F0 *base = GOBJ_SUB(ctx)->p_7F0;
    MatrixDrive_TurnObjectMatrix(a0, (int)base->p_20->p_8->p_0);
    MatrixDrive_TurnObjectMatrix(a1, (int)base->p_20->p_8->p_0 + 0x10);
    *(float *)(a0 + 4) += 50.0f;
    *(float *)(a1 + 4) -= 150.0f;
    return base->f_40;
}

void InitCageFixGeo(GObj *a0, float a1) {
    GOBJ_SUB(a0)->p_7F0->f_3C = a1;
}

extern int *isysGObjSearchFromObjLayoutID(int x);
extern void CageDL(int *p);
extern int *isysGObjSearchFromObjKindID_next(int *p);

void func_001C0138(void)
{
    int *p = isysGObjSearchFromObjLayoutID(0x2B);
    if (p != 0) {
        do {
            CageDL(p);
            p = isysGObjSearchFromObjKindID_next(p);
        } while (p != 0);
    }
}

void func_001C0180(GObj *a0, int a1) {
    GOBJ_SUB(a0)->p_7F0->f_40 = a1;
}

extern int func_00105078(void);
extern void CopyMatrix(int a0, int a1);
extern void HotInitCageGeo(void *a0, int a1, int a2);

void func_001C0190(int *self)
{
    void *s0 = isysGObjSearchFromObjLayoutID(0x2B);
    if (s0 != 0) {
        int *p;
        int v;
        v = func_00105078();
        p = (int *)self[0x57];
        CopyMatrix(v, p[3]);
        v = func_00105078();
        p = (int *)self[0x57];
        HotInitCageGeo(s0, v + 0x30, p[4]);
    }
}
