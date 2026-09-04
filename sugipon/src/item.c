#include "common.h"

extern void playSEConditionID(int a0, int a1);

void bombSparkStartSE(int a0) {
    playSEConditionID(a0, 0x31);
}

void bombSparkSE(int a0) {
    playSEConditionID(a0, 0x32);
}

extern void debug_StdPrintfDummy();
extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);
extern void GetMatrixFromQuaternion(int a0);
extern void func_00102840(int a0, int a1);
extern void func_00102820(void *a0, int a1);
extern void RegularizeQuaternion(void *a0, void *a1);
extern void MultiQuaternion(int a0, void *a1, void *a2);
extern char D_00611870[];
extern char D_00611898[];
extern char D_0062D580[];
extern char D_002724B0[];

void bombExplodeSE(int a0, int a1) {
    char buf0[0x10];
    char buf1[0x10];
    char *sub;

    if (a0 == 0) {
        debug_StdPrintfDummy(D_00611870);
        func_001AAD00(D_00611898, 0x158);
        __assert(D_00611898, 0x158, D_0062D580);
    }
    sub = *(char **)(*(int *)(a0 + 0x15C) + 0x7F0);
    *(int *)(sub + 0xC) = 1;
    *(int *)(sub + 0x8) = 0;
    *(int *)(sub + 0x14) = a1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x74) = 0;
    GetMatrixFromQuaternion(*(int *)(a0 + 0x15C) + 0x140);
    if ((*(int *)(*(char **)(*(int *)(a0 + 0x15C) + 0x7F0) + 0x4) ^ 1) == 0) {
        func_00102840(a0, (int)D_002724B0);
    }
    func_00102820(buf0, a0);
    func_00102820(buf1, a1);
    RegularizeQuaternion(buf1, buf1);
    MultiQuaternion((int)(sub + 0x20), buf1, buf0);
}

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

extern int CanHoldBox(void *a0);
extern void InitItemGeo(void *a0);
extern void carriedItemGeo(void *a0);
extern void func_00102828(void *a0);
extern void uncarriedItemGeo(void *a0);

void execBombGeo(void *a0) {
    char *ctrl = *(char **)((char *)a0 + 0x15C);
    char *item = *(char **)(ctrl + 0x7F0);
    char *item2;
    if (*(int *)item == 1) {
        return;
    }
    if (*(int *)(item + 0xC) != 0) {
        InitItemGeo(a0);
    } else if (*(int *)(item + 8) != 0) {
        int old = *(int *)(ctrl + 0x74);
        *(int *)(ctrl + 0x74) = 0;
        carriedItemGeo(a0);
        if (old != 0) {
            *(int *)(*(char **)((char *)a0 + 0x15C) + 0x74) = 1;
        }
    } else {
        char *box = *(char **)ctrl;
        if (box != 0 && *(int *)(box + 0xC) == 0x11 && CanHoldBox(box) == 2) {
            *(int *)(item + 0x14) = 0;
            ReleaseItem((char *)a0, *(int *)(box + 0x15C) + 0x120);
        }
    }
    func_00102828(a0);
    item2 = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    if ((*(int *)(item2 + 4) ^ 1) == 0) {
        uncarriedItemGeo(a0);
    }
}


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
