#include "common.h"

extern const char D_00621328[];
extern int D_0063A438;
extern short *iosMallocDebug(int handle, int size, void *file, int line);
extern int rand(void);
extern void CopyMatrix(void *dst, void *src);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_RotMatrixX(short a0);
extern void MatrixDrive_RotMatrixY(short a0);
extern float GetTableSin(short a0);
/* prototypes: their order is the inline tail's emission order */
short *InitSugiLeafGeo(void);
void SugiLeafGeo(void *gobj);
short *InitSugiLeafGeo2(void *gobj);
inline short *InitSugiLeafGeo(void) {
    short *h = iosMallocDebug(D_0063A438, 2, (void *)D_00621328, 0xC);
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
    short *buf = iosMallocDebug(D_0063A438, n * 2, (void *)D_00621328, 0x23);
    int i;

    for (i = 0; i < n; i++) {
        buf[i] = rand() % 0x10000;
    }
    return buf;
}
INCLUDE_ASM("asm/nonmatchings/src/sugiTree", SugiLeafGeo2);
INCLUDE_ASM("asm/nonmatchings/src/sugiTree", SugiLeafDL2);
