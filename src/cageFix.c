#include "common.h"

#include "ico/types.h"



extern int *func_00105278(void);
extern void CopyMatrix(void *dst, void *src);
extern void HotInitCageGeo(int *self, int a1, int a2);
extern int isysGObjSearchFromObjKindID_next();
extern void CageDL();
extern int isysGObjSearchFromObjLayoutID();
extern void file_LoadCDFile(void *a0);
extern void func_0010ECB8(int a0);

void CageFixGeo(GObj *a0) {
    Obj7F0 *base = ((Obj7F0 *)GOBJ_SUB(a0)->p_800);
    func_0010ECB8((int)a0);
    file_LoadCDFile(base->p_0);
}

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

int CageFixDL(int a0, int a1, GObj *ctx)
{
    Obj7F0 *base = ((Obj7F0 *)GOBJ_SUB(ctx)->p_800);
    MatrixDrive_TurnObjectMatrix(a0, (int)base->p_20->p_8->p_0);
    MatrixDrive_TurnObjectMatrix(a1, (int)base->p_20->p_8->p_0 + 0x10);
    *(float *)(a0 + 4) += 50.0f;
    *(float *)(a1 + 4) -= 150.0f;
    return base->f_40;
}

void InitCageFixGeo(GObj *a0, float a1) {
    ((Obj7F0 *)GOBJ_SUB(a0)->p_800)->f_3C = a1;
}

void func_001C2EC8(void)
{
    int *p = isysGObjSearchFromObjLayoutID(0x2B);
    if (p != 0) {
        do {
            CageDL(p);
            p = isysGObjSearchFromObjKindID_next(p);
        } while (p != 0);
    }
}

void func_001C2F10(GObj *a0, int a1) {
    ((Obj7F0 *)GOBJ_SUB(a0)->p_800)->f_40 = a1;
}

void func_001C2F20(int *self)
{
    void *s0 = isysGObjSearchFromObjLayoutID(0x2B);
    if (s0 != 0) {
        int *p;
        int v;
        v = func_00105278();
        p = (int *)self[0x57];
        CopyMatrix(v, p[3]);
        v = func_00105278();
        p = (int *)self[0x57];
        HotInitCageGeo(s0, v + 0x30, p[4]);
    }
}

