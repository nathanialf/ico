#include "common.h"

extern int D_0062A310;
extern char D_006126F8[];
extern void *iosFree(int handle, int size, char *file, int line);

typedef struct { double d[10]; } BgaEntry;
extern BgaEntry D_004C1EE0;

void *InitMultiBgaManager(int n)
{
    BgaEntry *base = (BgaEntry *)iosFree(D_0062A310, n * 0x50, D_006126F8, 0xB);
    int i;
    for (i = 0; i < n; i++) {
        base[i] = D_004C1EE0;
    }
    return base;
}

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
