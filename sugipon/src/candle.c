#include "common.h"
#include "ico/types.h"

extern int func_0010F068(int a0);
extern int file_LoadCDFile(int a0);
extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern void GetParticleEffectPackage(int id);

typedef struct {
    int id;   /* 0x0 */
    int flag; /* 0x4 */
} CandleElem;

void InitCandleGeo(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010F068(a0);
        return file_LoadCDFile((int)s0);
    }
}

int CandleDL(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/candle", CandleGeo);

void DeleteLayoutedCandleParticleEffect(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010F068(a0);
        return file_LoadCDFile((int)s0);
    }
}

extern int func_00105078(void);
extern void func_00105108(float a0, float a1, float a2);
extern void MatrixDrive_TurnXObjectMatrixYZ(int a0, int a1);
extern void ExecParticleEffects(int a0, int a1, int *a2);
extern int D_002724B0[];

void _deleteLayoutedCandleParticleEffect(GObj *self)
{
    Sub15C *sub = self->p_15C;
    CandleElem *arr = (CandleElem *)sub->p_7F0;
    if (sub->f_74 != 0) {
        if (sub->f_8 > 1) {
            int i;
            for (i = 0; i < sub->f_8; i++) {
                MatrixDrive_TurnXObjectMatrixYZ((int)func_00105078(),
                                                GOBJ_SUB(self)->f_C + i * 0x40);
                func_00105108(0.0f, -40.0f, 0.0f);
                if (arr[i].id != -1) {
                    ExecParticleEffects(arr[i].id,
                                        (int)func_00105078() + 0x30,
                                        D_002724B0);
                }
            }
        }
    }
}

void func_001C04E0(void)
{
    GObj *o = isysGObjSearchFromObjLayoutID(0x22);
    while (o != 0) {
        CandleElem *arr = (CandleElem *)GOBJ_SUB(o)->p_7F0;
        int n = GOBJ_SUB(o)->f_8;
        if (n > 1) {
            int i;
            for (i = 0; i < GOBJ_SUB(o)->f_8; i++) {
                if (arr[i].flag == 0) {
                    GetParticleEffectPackage(arr[i].id);
                    arr[i].id = -1;
                    arr[i].flag = 1;
                }
            }
        }
        o = isysGObjSearchFromObjKindID_begin(o);
    }
}
