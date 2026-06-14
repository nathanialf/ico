#include "common.h"

extern void playSEConditionID(int a0, int a1);

void bombSparkStartSE(int a0) {
    playSEConditionID(a0, 0x31);
}

void bombSparkSE(int a0) {
    playSEConditionID(a0, 0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", bombExplodeSE);

extern float D_004C0850[48];
extern void GetRootMatrixByDObj(void *buf, int v);
extern void ClipWallBoxStop(int arg);
extern void CylinderCollision(void *self, char *spill);

void HoldItem(void *self, int arg)
{
    char *p;
    if (arg == 0)
        return;
    p = (char *)D_004C0850;
    GetRootMatrixByDObj(p, arg);
    GetRootMatrixByDObj(p + 0x10, (int)self);
    ClipWallBoxStop((int)p);
    if (*(int *)(p + 0x88) == 0)
        return;
    CylinderCollision(self, p + 0x20);
}

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern void GetMatrixFromQuaternion(int a0);
extern char D_004C0830[];

void avoidInsideOfWall(char *a0)
{
    int *q = *(int **)(*(char **)(a0 + 0x15C) + 0x7F0);
    HoldItem(a0, q[5]);
    q[2] = 1;
    q[3] = 0;
    q[5] = 0;
    q[4] = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x74) = 1;
    MatrixDrive_TurnObjectMatrix(*(int *)(a0 + 0x15C) + 0x120, (int)D_004C0830);
    GetMatrixFromQuaternion(*(int *)(a0 + 0x15C) + 0x140);
}

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern void GetMatrixFromQuaternion(int a0);

void ReleaseItem(char *a0, int a1)
{
    int *q = *(int **)(*(char **)(a0 + 0x15C) + 0x7F0);
    HoldItem(a0, q[5]);
    q[3] = 0;
    q[2] = 1;
    q[4] = 1;
    MatrixDrive_TurnObjectMatrix(*(int *)(a0 + 0x15C) + 0x120, a1);
    GetMatrixFromQuaternion(*(int *)(a0 + 0x15C) + 0x140);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", ThrowItem);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", InitItemGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", carriedItemGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", uncarriedItemGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", execBombGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", ItemGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", ItemDL);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_004CECE0;  /* stride 0x14 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006118E0;  /* stride 0x4 */

/* end struct shapes */
