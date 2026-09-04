#include "common.h"



extern void SetDirectRootPositionNoFitting();
extern void ClipWall(int arg);
extern void GetRootPosition(void *a0, char *outer);
extern float D_004C4760[48];
extern void ExecuteSEPackage(int a0, int a1);
void bombSparkStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x31);
}

void bombSparkSE(int a0)
{
    ExecuteSEPackage(a0, 0x32);
}

extern char D_00276140[];
extern char D_00618F40[];
extern char D_00618F68[];
extern char D_00633420[];
extern void GetMatrixFromQuaternion(int a0);
extern void RegularizeQuaternion(void *a0, void *a1);
extern void debug_StdPrintfDummy();
extern void func_00102850(void *a0, int a1);
extern void func_00102870(int a0, int a1);
extern void MultiQuaternion(int a0, void *a1, void *a2);
extern void func_001AD768(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);

void bombExplodeSE(int a0, int a1) {
    char buf0[0x10];
    char buf1[0x10];
    char *sub;

    if (a0 == 0) {
        debug_StdPrintfDummy(D_00618F40);
        func_001AD768(D_00618F68, 0x158);
        __assert(D_00618F68, 0x158, D_00633420);
    }
    sub = *(char **)(*(int *)(a0 + 0x15C) + 0x800);
    *(int *)(sub + 0xC) = 1;
    *(int *)(sub + 0x8) = 0;
    *(int *)(sub + 0x14) = a1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x74) = 0;
    GetMatrixFromQuaternion(*(int *)(a0 + 0x15C) + 0x150);
    if ((*(int *)(*(char **)(*(int *)(a0 + 0x15C) + 0x800) + 0x4) ^ 1) == 0) {
        func_00102870(a0, (int)D_00276140);
    }
    func_00102850(buf0, a0);
    func_00102850(buf1, a1);
    RegularizeQuaternion(buf1, buf1);
    MultiQuaternion((int)(sub + 0x20), buf1, buf0);
}

void HoldItem(void *self, int arg)
{
    char *p;
    if (arg == 0)
        return;
    p = (char *)D_004C4760;
    GetRootPosition(p, arg);
    GetRootPosition(p + 0x10, (int)self);
    ClipWall((int)p);
    if (*(int *)(p + 0x88) == 0)
        return;
    SetDirectRootPositionNoFitting(self, p + 0x20);
}

extern char D_004C4740[];
extern void GetMatrixFromQuaternion(int a0);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

void avoidInsideOfWall(char *a0)
{
    int *q = *(int **)(*(char **)(a0 + 0x15C) + 0x800);
    HoldItem(a0, q[5]);
    q[2] = 1;
    q[3] = 0;
    q[5] = 0;
    q[4] = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x74) = 1;
    MatrixDrive_TurnObjectMatrix(*(int *)(a0 + 0x15C) + 0x130, (int)D_004C4740);
    GetMatrixFromQuaternion(*(int *)(a0 + 0x15C) + 0x150);
}

extern void GetMatrixFromQuaternion(int a0);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

void ReleaseItem(char *a0, int a1)
{
    int *q = *(int **)(*(char **)(a0 + 0x15C) + 0x800);
    HoldItem(a0, q[5]);
    q[3] = 0;
    q[2] = 1;
    q[4] = 1;
    MatrixDrive_TurnObjectMatrix(*(int *)(a0 + 0x15C) + 0x130, a1);
    GetMatrixFromQuaternion(*(int *)(a0 + 0x15C) + 0x150);
}

INCLUDE_ASM("asm/nonmatchings/src/item", ThrowItem);

INCLUDE_ASM("asm/nonmatchings/src/item", InitItemGeo);

INCLUDE_ASM("asm/nonmatchings/src/item", carriedItemGeo);

INCLUDE_ASM("asm/nonmatchings/src/item", uncarriedItemGeo);

extern void InitItemGeo(void *a0);
extern void carriedItemGeo(void *a0);
extern void func_00102858(void *a0);
extern int func_001C05A8(void *a0);
extern void uncarriedItemGeo(void *a0);

void execBombGeo(void *a0) {
    char *ctrl = *(char **)((char *)a0 + 0x15C);
    char *item = *(char **)(ctrl + 0x800);
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
        if (box != 0 && *(int *)(box + 0xC) == 0x11 && func_001C05A8(box) == 2) {
            *(int *)(item + 0x14) = 0;
            ReleaseItem((char *)a0, *(int *)(box + 0x15C) + 0x130);
        }
    }
    func_00102858(a0);
    item2 = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    if ((*(int *)(item2 + 4) ^ 1) == 0) {
        uncarriedItemGeo(a0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/item", ItemGeo);

INCLUDE_ASM("asm/nonmatchings/src/item", ItemDL);

