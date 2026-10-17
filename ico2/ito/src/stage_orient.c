#include "typedef.h"
#include "Matrix.h"
#include "matrixDrive.h"
#include <libvu0.h>

/* This build's record is 0x24 bytes: no second anchor; the word after the
   anchor is 0 in every record of the demo's table. */
typedef struct { /* field names derived */
    char name[16];
    float angle;
    float pos[4];
} StageOrientDef; /* derived name */

static const StageOrientDef stageOrientDefs[35] = {
    /* derived name */
    {"st47a", 0.0f, {200.0f, -350.0f, -950.0f}},
    {"st18a", -3.14159f, {-4850.0f, -1650.0f, 3075.0f}},
    {"st01b", -1.5708f, {-4845.0f, -2175.0f, 6140.0f}},
    {"st09a", 3.14159f, {-4425.0f, -1700.0f, 9300.0f}},
    {"st03t", 1.5708f, {-3050.0f, -925.0f, 5100.0f}},
    {"st10l", 3.14159f, {-1070.0f, 475.0f, 5660.0f}},
    {"st04a", 1.5708f, {4800.0f, -1750.0f, -1.04092e-13f}},
    {"st04b", 1.5708f, {5725.0f, 205.0f, 3175.0f}},
    {"st04c", 3.14159f, {6555.0f, 840.0f, 12095.0f}},
    {"st04d", -3.14159f, {6550.0f, 1035.0f, 14165.0f}},
    {"st04e", 3.14159f, {6055.0f, 1235.0f, 16190.0f}},
    {"st05b", 1.5708f, {5145.0f, 180.0f, -2605.0f}},
    {"st05c", 0.0f, {6550.0f, 1285.0f, -11885.0f}},
    {"st05d", 0.0f, {6550.0f, 1845.0f, -13955.0f}},
    {"st05e", 0.0f, {5845.0f, 1600.0f, -15810.0f}},
    {"st02a", -1.5708f, {-4035.0f, -765.0f, -3180.0f}},
    {"st06a", -1.5708f, {-7050.0f, 290.0f, -2950.0f}},
    {"st22a", 0.0f, {7640.0f, -5670.0f, -2105.0f}},
    {"st19a", 0.0f, {-6445.0f, -2250.0f, -4785.0f}},
    {"st20a", 0.0f, {-4380.0f, -3505.0f, -9725.0f}},
    {"st10r", 0.0f, {-685.0f, 5.0f, -5550.0f}},
    {"st19b", 0.0f, {-5055.0f, -5165.0f, -4865.0f}},
    {"st17b", 0.0f, {-12960.0f, -6075.0f, -3520.0f}},
    {"st17a", 0.0f, {-14230.0f, -40.0f, 455.0f}},
    {"st08a", 0.0f, {-9490.0f, 680.0f, 2970.0f}},
    {"st07a", 3.14159f, {-4300.0f, -475.0f, 2.08167e-13f}},
    {"st00a", -1.5708f, {-10560.0f, -150.0f, 50.0f}},
    {"st13c", -3.14159f, {-18650.0f, -230.0f, 450.0f}},
    {"st13d", 3.14159f, {-18620.0f, 2505.0f, 450.0f}},
    {"st13b", 3.14159f, {-24850.0f, -430.0f, 450.0f}},
    {"st13a", 0.0f, {-24005.0f, -7620.0f, 485.0f}},
    {"st24a", -1.5708f, {-21330.0f, -10450.0f, 390.0f}},
    {"st25a", 0.0f, {-25000.0f, 4640.0f, 450.0f}},
    {"st24b", -1.5708f, {-20500.0f, -10450.0f, -600.0f}},
    {"st27a", 1.5708f, {27325.0f, -12310.0f, 77370.0f}},
};

/* the orient index each stage resolves to, -1 where the stage has none (120
   shorts in this build: the run ends where mv_main's starts, 0x722880) */
static short stageOrientIdx[120]; /* derived name */

#include "stage_orient.h"
#include <stdio.h>
#include <string.h>
#include "include_asm.h"

INCLUDE_ASM_LIT(StageOrientInit);

/* the matrix that places a stage at its orient record's anchor and angle,
   for GetStageDifferenceMatrix and StageOrientGet2 */
static inline void MakeStageOrientMatrix(float *m, const StageOrientDef *p) /* derived name */
{
    VECTOR v = {p->pos[0], p->pos[1], p->pos[2], 1.0f};

    MatrixDrive_PushMatrix();
    _UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(&v);
    MatrixDrive_RotMatrixY((short)(p->angle * 10430.37793f));
    CopyMatrix(m, MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
}

INCLUDE_ASM(StageOrientInit);

INCLUDE_ASM(StageOrientGet);
