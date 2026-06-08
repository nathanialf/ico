#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/multiBgaManager", InitMultiBgaManager);

extern char D_00271BD0[];
extern void MatrixDrive_TurnObjectMatrix(char *dst, char *src);
extern void GetInverseQuaternion(char *dst, int v);

void EntryMultiBgaManager(char *base, int idx, int v6, char *a7, char *a8)
{
    char *p = base + idx * 0x50;
    *(int *)(p + 0x40) = v6;
    MatrixDrive_TurnObjectMatrix(p + 0x10, a7);
    MatrixDrive_TurnObjectMatrix(p + 0x20, D_00271BD0);
    GetInverseQuaternion(p + 0x30, a8);
    *(int *)p = 0;
}


void EntryMultiBgaManagerSensitive(char *base, int idx, int v6, char *a7, char *a8, int a9)
{
    char *p = base + idx * 0x50;
    *(int *)(p + 0x40) = v6;
    MatrixDrive_TurnObjectMatrix(p + 0x10, a7);
    MatrixDrive_TurnObjectMatrix(p + 0x20, a9);
    GetInverseQuaternion(p + 0x30, a8);
    *(int *)p = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/multiBgaManager", DispMultiBgaManager);
