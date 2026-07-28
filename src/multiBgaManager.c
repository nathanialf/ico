#include "common.h"


extern void GetInverseQuaternion();
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern char D_00275850[];
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", InitMultiBgaManager);

void EntryMultiBgaManager(char *base, int idx, int v6, char *a7, char *a8)
{
    char *p = base + idx * 0x50;
    *(int *)(p + 0x40) = v6;
    MatrixDrive_TurnObjectMatrix(p + 0x10, a7);
    MatrixDrive_TurnObjectMatrix(p + 0x20, D_00275850);
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

INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", DispMultiBgaManager);

