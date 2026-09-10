#include "common.h"
#include "ico/types.h"

extern void ropeGeo(void *o);
extern void GetRootPosition(void *dst, void *src);
extern float GetChainCollision(void *a0, void *a1, float w);
extern void *D_00639EA4;

INCLUDE_ASM("asm/nonmatchings/src/rope", InitRopeGeo);

inline int CheckRopeUpperWallClimbable(int a0, char *a1)
{
    return *(int *)(*(char **)(*(char **)(a1 + 0x15C) + 0x830) + 4);
}

void SetRopeFixPoint(char *a0, void *a1)
{
    CopyVector(**(char ***)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) + 0x20, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/rope", HoldRope);

inline void ReleaseRope(void) {}

extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void func_0025D440(void *a0, void *a1, void *a2);
extern void GetChainAnimation(void *sys, int obj, void *mtx);

void ropeGeo(void *a0)
{
    void **obj = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);

    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    if (**(int **)((char *)a0 + 0x15C) != 0) {
        func_0025D440(MatrixDrive_GetMatrix(),
                      *(char **)(*(char **)(**(char ***)((char *)a0 + 0x15C) + 0x15C) + 0xC) +
                          (*(int *)(*(char **)((char *)a0 + 0x15C) + 4) << 6),
                      MatrixDrive_GetMatrix());
    }
    GetChainAnimation(obj[0], 0, MatrixDrive_GetMatrix());
}

/* The listing inlines rope.c:215-221 into RopeGeo: the chain-length update
   is a static helper defined above it (its name is not recoverable). */
/* prototypes: their order is the inline tail's emission order */
int CheckRopeUpperWallClimbable(int a0, char *a1);
void ReleaseRope(void);
void RopeGeo(void *a0);

static inline void ropeChainCollision(void *a0)
{
    void *g = D_00639EA4;
    void **obj = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);
    float m[4];
    float w;

    GetRootPosition(m, g);
    w = GetChainCollision(obj[0], m, 200.0f);
    do {
        if (0.0f < w) {
            *(float *)((char *)*(void **)((char *)g + 0x15C) + 0x618) = w;
        }
    } while (0);
}

inline void RopeGeo(void *a0)
{
    ropeGeo(a0);
    ropeChainCollision(a0);
}

extern void p2o_SetDefaultEnviroment(void *a0);
extern void p2o_DispVU1DObjMulti(void *a0);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void MatrixDrive_GetTurnYAngleXZ(unsigned short *o1, unsigned short *o2, float x, float y,
                                        float z);
extern void MatrixDrive_RotMatrixX(short a0);
extern void MatrixDrive_RotMatrixZ(short a0);
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void CopyMatrix(void *dst, void *src);
extern void TestDispChainAnimation(void *a0);
extern int D_0063B148;

void RopeDL(void *a0)
{
    unsigned short ax;
    unsigned short az;
    char *sub = *(char **)((char *)a0 + 0x15C);
    void **p = *(void ***)(sub + 0x830);
    char *set = (char *)p[0];
    int i;
    int j;
    int n;
    float (*v)[4];

    p2o_SetDefaultEnviroment(a0);
    for (i = 0; i < *(int *)(set + 4); i++) {
        n = *(int *)(*(char **)set + i * 0x50);
        v = (float (*)[4]) * (int *)(*(char **)(set + 8) + i * 0x1A0);
        for (j = 1; j < n; j++) {
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            MatrixDrive_TransMatrix(v[j][0], v[j][1], v[j][2]);
            MatrixDrive_GetTurnYAngleXZ(&ax, &az, v[j][0] - v[j - 1][0], v[j][1] - v[j - 1][1],
                                        v[j][2] - v[j - 1][2]);
            MatrixDrive_RotMatrixX(-ax);
            MatrixDrive_RotMatrixZ(-az);
            MatrixDrive_RotMatrixX(-0x8000);
            MatrixDrive_ScaleMatrix(1.0f, 1.0f, 1.0f);
            CopyMatrix(*(char **)(sub + 0xC) + (j * 0x40 - 0x40), MatrixDrive_GetMatrix());
        }
        p2o_DispVU1DObjMulti(sub);
    }
    if (D_0063B148 != 0) {
        TestDispChainAnimation(p[0]);
    }
}
