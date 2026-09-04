#include "common.h"
#include "ico/types.h"

extern void playSEConditionID(int a0, int a1);

void RopeFixGeo(void) {
}

struct vec4_rope { float x, y, z, w; } __attribute__((aligned(8)));

extern void RopeDL(GObj *o);
extern void GetRootMatrixByDObj(void *dst, void *src);
extern float GetChainCollision(void *a0, void *a1, float w);
extern GObj *D_00629DE4;

void RopeFixDL(GObj *a0) {
    struct vec4_rope m;
    Obj7F0 *obj;
    GObj *g;
    float w;
    RopeDL(a0);
    g = D_00629DE4;
    obj = GOBJ_SUB(a0)->p_7F0;
    GetRootMatrixByDObj(&m, g);
    w = GetChainCollision(obj->p_0, &m, 200.0f);
    do {
        if (0.0f < w) {
            GOBJ_SUB(g)->f_608 = w;
        }
    } while (0);
}

extern int isysGObjSearchFromObjLayoutID(int a0);
extern int UnLockChainGeo(int a0, int a1);

void InitRopeFixGeo(int a0)
{
    int v0 = isysGObjSearchFromObjLayoutID(0x15);
    if (v0 != 0) {
        return UnLockChainGeo(v0, a0);
    }
}

extern int func_0010F068(int a0);
extern int file_LoadCDFile(int a0);

void func_001E6B28(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010F068(a0);
        return file_LoadCDFile((int)s0);
    }
}

int func_001E6B70(void) {
    return 0;
}

void func_001E6B78(int a0) {
    playSEConditionID(a0, 0x33);
}

extern void ExecFrameDependSequence(int a0);

void func_001E6B80(int a0) {
    ExecFrameDependSequence(a0);
    playSEConditionID(a0, 0x38);
}

typedef struct { char _0[0x30]; int f30; } RopeC;
typedef struct { char _0[0x7F0]; RopeC *f7F0; } RopeB;
typedef struct { char _0[0x15C]; RopeB *f15C; } RopeA;
extern void gamesysObjInfoUniqDataSet(RopeA *a0);

void func_001E6BB0(RopeA *a0) {
    RopeC *q = a0->f15C->f7F0;
    if (q->f30++ >= 0x1F) {
        q->f30 = 0;
        gamesysObjInfoUniqDataSet(a0);
    }
}

extern int func_00105078(void);
extern void LocalizeDirectionOrient(int a0, void *a1);
extern void MatrixDrive_RotMatrixY(int a0);
extern void CopyMatrix(int a0, int a1);

void func_001E6BE0(int a0, void *a1) {
    Obj7F0 *obj = GOBJ_SUB(a1)->p_7F0;
    LocalizeDirectionOrient(func_00105078(), a1);
    MatrixDrive_RotMatrixY(*(short *)((char *)obj + 0x20));
    CopyMatrix(a0, func_00105078());
}

extern void func_0010F048(void *a0);

void func_001E6C48(char *self) {
    func_001E6BE0(*(int *)(*(char **)(self + 0x15C) + 0xC), self);
    func_0010F048(self);
}
