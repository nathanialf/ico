#include "common.h"
#include "memory.h"
#include "DisplayP2O.h"
#include "matrixDrive.h"
#include "tableSin.h"

extern int D_0063A438;
extern int rand(void);
/* prototypes: their order is the inline tail's emission order */
short *InitSugiLeafGeo(void);
void SugiLeafGeo(void *gobj);
short *InitSugiLeafGeo2(void *gobj);

inline short *InitSugiLeafGeo(void)
{
    short *h = iosMallocDebug(D_0063A438, 2, (void *)"src/sugiTree.c", 12);
    int r = rand();
    *h = r % 0x10000;
    return h;
}

inline void SugiLeafGeo(void *gobj)
{
    char *p = *(char **)((char *)gobj + 0x15C);
    short *ang = *(short **)(p + 0x830);

    CopyMatrix(MatrixDrive_GetMatrix(), p + 0x20);
    MatrixDrive_RotMatrixY(GetTableSin(*ang) * 256.0f);
    MatrixDrive_RotMatrixX(GetTableSin(*ang * 2) * 256.0f);
    CopyMatrix(*(void **)(p + 0xC), MatrixDrive_GetMatrix());
    *ang += 0x80;
}

inline short *InitSugiLeafGeo2(void *gobj)
{
    char *p = *(char **)((char *)gobj + 0x15C);
    int n = *(signed char *)(*(char **)(p + 0x854) + 0x2E);
    short *buf = iosMallocDebug(D_0063A438, n * 2, (void *)"src/sugiTree.c", 35);
    int i;

    for (i = 0; i < n; i++) {
        buf[i] = rand() % 0x10000;
    }
    return buf;
}

extern void sceVu0MulMatrix(void *a0, void *a1, void *a2);

void SugiLeafGeo2(void *gobj)
{
    char *p = *(char **)((char *)gobj + 0x15C);
    int n = *(signed char *)(*(char **)(p + 0x854) + 0x2E);
    short *ang = *(short **)(p + 0x830);
    int i;

    for (i = 0; i < n; i++) {
        if (i == n - 1) {
            CopyMatrix(*(char **)(p + 0xC) + i * 0x40, p + 0x20);
        } else {
            CopyMatrix(*(char **)(p + 0xC) + i * 0x40, p + 0x20);
            CopyMatrix(MatrixDrive_GetMatrix(),
                       *(char **)(*(char **)(p + 0x854) + 0x40) + i * 0x180 + 0x130);
            *(int *)(*(char **)(p + 0x870) + i * 0x50) =
                (int)(GetTableCos((short)((ang[i / 3] * 9 + i) * 10)) * 768.0f);
            *(int *)(*(char **)(p + 0x870) + i * 0x50 + 4) =
                (int)(GetTableSin((short)((ang[i / 3] * 6 + i) * 16)) * 768.0f);
            MatrixDrive_RotMatrixY(*(short *)(*(char **)(p + 0x870) + i * 0x50 + 4));
            MatrixDrive_RotMatrixX(*(short *)(*(char **)(p + 0x870) + i * 0x50));
            sceVu0MulMatrix(*(char **)(p + 0xC) + i * 0x40, *(char **)(p + 0xC) + i * 0x40,
                            MatrixDrive_GetMatrix());
            ang[i / 3]++;
        }
    }
}

extern void sceVu0UnitMatrix(void *m);

void SugiLeafDL2(void *gobj)
{
    char *p = *(char **)((char *)gobj + 0x15C);
    int n = *(signed char *)(*(char **)(p + 0x854) + 0x2E);
    char save[n][0x40];
    int i;

    for (i = 0; i < n; i++) {
        char *m = *(char **)(*(char **)(p + 0x854) + 0x40) + i * 0x180;

        CopyMatrix(save[i], m + 0x130);
    }
    p2o_DispVU1Default(gobj);
    for (i = 0; i < n; i++) {
        char *m = *(char **)(*(char **)(p + 0x854) + 0x40) + i * 0x180 + 0x130;

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(0.0f, -0.5f, 0.0f);
        MatrixDrive_ScaleMatrix(1.0f, 0.0f, 1.0f);
        MatrixDrive_RotMatrixX(0x2000);
        sceVu0MulMatrix(m, MatrixDrive_GetMatrix(), m);
    }
    for (i = 0; i < n; i++) {
        CopyMatrix(*(char **)(*(char **)(p + 0x854) + 0x40) + i * 0x180 + 0x130, save[i]);
    }
}
