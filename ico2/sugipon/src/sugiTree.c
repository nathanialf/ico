#include "memory.h"
#include "DisplayP2O.h"
#include "matrixDrive.h"
#include "tableSin.h"
#include "sugiTree.h"
#include <stdlib.h>
#include <libvu0.h>
#include "ios.h"

inline short *InitSugiLeafGeo(void)
{
    short *h = iosMallocDebug(ios_partition_sugipon, 2, (void *)"src/sugiTree.c", 12);
    int r = rand();
    *h = r % 0x10000;
    return h;
}

inline void SugiLeafGeo(void *gobj)
{
    Sub15C *p = GOBJ_SUB(gobj);
    short *ang = p->f_830;

    CopyMatrix(MatrixDrive_GetMatrix(), &p->f_20);
    MatrixDrive_RotMatrixY(GetTableSin(*ang) * 256.0f);
    MatrixDrive_RotMatrixX(GetTableSin(*ang * 2) * 256.0f);
    CopyMatrix((void *)p->f_C, MatrixDrive_GetMatrix());
    *ang += 0x80;
}

inline short *InitSugiLeafGeo2(void *gobj)
{
    Sub15C *p = GOBJ_SUB(gobj);
    int n = p->model->partCount;
    short *buf = iosMallocDebug(ios_partition_sugipon, n * 2, (void *)"src/sugiTree.c", 35);
    int i;

    for (i = 0; i < n; i++) {
        buf[i] = rand() % 0x10000;
    }
    return buf;
}

void SugiLeafGeo2(void *gobj)
{
    Sub15C *p = GOBJ_SUB(gobj);
    int n = p->model->partCount;
    short *ang = p->f_830;
    int i;

    for (i = 0; i < n; i++) {
        if (i == n - 1) {
            CopyMatrix((char *)p->f_C + i * 64, &p->f_20);
        } else {
            CopyMatrix((char *)p->f_C + i * 64, &p->f_20);
            CopyMatrix(MatrixDrive_GetMatrix(), (char *)p->model->parts[i].mtx);
            p->p_870[i].rot[0] = (int)(GetTableCos((short)((ang[i / 3] * 9 + i) * 10)) * 768.0f);
            p->p_870[i].rot[1] = (int)(GetTableSin((short)((ang[i / 3] * 6 + i) * 16)) * 768.0f);
            MatrixDrive_RotMatrixY(*(short *)(*(char **)((char *)p + 0x870) + i * 0x50 + 4));
            MatrixDrive_RotMatrixX(*(short *)(*(char **)((char *)p + 0x870) + i * 0x50));
            sceVu0MulMatrix((char *)p->f_C + i * 64, (char *)p->f_C + i * 64,
                            MatrixDrive_GetMatrix());
            ang[i / 3]++;
        }
    }
}

void SugiLeafDL2(void *gobj)
{
    Sub15C *p = GOBJ_SUB(gobj);
    int n = p->model->partCount;
    char save[n][0x40];
    int i;

    for (i = 0; i < n; i++) {
        PObjPart *m = &p->model->parts[i];

        CopyMatrix(save[i], m->mtx);
    }
    p2o_DispVU1Default(gobj);
    for (i = 0; i < n; i++) {
        char *m = (char *)p->model->parts[i].mtx;

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(0.0f, -0.5f, 0.0f);
        MatrixDrive_ScaleMatrix(1.0f, 0.0f, 1.0f);
        MatrixDrive_RotMatrixX(0x2000);
        sceVu0MulMatrix(m, MatrixDrive_GetMatrix(), m);
    }
    for (i = 0; i < n; i++) {
        CopyMatrix((char *)p->model->parts[i].mtx, save[i]);
    }
}
