#include "memory.h"
#include "DisplayP2O.h"
#include "matrixDrive.h"
#include "tableSin.h"
#include "sugiTree.h"
#include <stdlib.h>
#include <libvu0.h>
#include "ios.h"
#include "include_asm.h"

INCLUDE_ASM_LIT(InitSugiLeafGeo);

void SugiLeafGeo2(GObj *gobj)
{
    Sub15C *p = GOBJ_SUB(gobj);
    int n = p->model->partCount;
    short *ang = p->work;
    int i;

    for (i = 0; i < n; i++) {
        if (i == n - 1) {
            CopyMatrix((char *)p->nodeMtx + i * 64, &p->matrix);
        } else {
            CopyMatrix((char *)p->nodeMtx + i * 64, &p->matrix);
            CopyMatrix(MatrixDrive_GetMatrix(), (char *)p->model->parts[i].mtx);
            p->nodes[i].rot[0] = (int)(GetTableCos((short)((ang[i / 3] * 9 + i) * 10)) * 768.0f);
            p->nodes[i].rot[1] = (int)(GetTableSin((short)((ang[i / 3] * 6 + i) * 16)) * 768.0f);
            MatrixDrive_RotMatrixY(*(short *)&p->nodes[i].rot[1]);
            MatrixDrive_RotMatrixX(*(short *)&p->nodes[i].rot[0]);
            sceVu0MulMatrix((char *)p->nodeMtx + i * 64, (char *)p->nodeMtx + i * 64,
                            MatrixDrive_GetMatrix());
            ang[i / 3]++;
        }
    }
}

void SugiLeafDL2(GObj *gobj)
{
    Sub15C *p = GOBJ_SUB(gobj);
    int n = p->model->partCount;
    char save[n][64];
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
        MatrixDrive_RotMatrixX(8192);
        sceVu0MulMatrix(m, MatrixDrive_GetMatrix(), m);
    }
    for (i = 0; i < n; i++) {
        CopyMatrix((char *)p->model->parts[i].mtx, save[i]);
    }
}

INCLUDE_ASM(InitSugiLeafGeo);

INCLUDE_ASM(SugiLeafGeo);

INCLUDE_ASM(InitSugiLeafGeo2);
