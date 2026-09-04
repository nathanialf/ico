#include "common.h"

#include "vu0.h"

extern char D_004E7420[];
extern char D_0061F2A0[];
extern int D_0063A438;
extern int InitClothes(char *p);
extern int *iosMallocDebug(int handle, int size, char *file, int line);

int *InitClothTestGeo(void)
{
    int *p = iosMallocDebug(D_0063A438, 0x290, (char *)D_0061F2A0, 0x41);
    *p = InitClothes(D_004E7420);
    return p;
}
void ClothTestGeo(void) {}
void ClothTestDL(void) {}
