#include "common.h"
#include "ico/types.h"

extern int  D_0070A8C0[];
extern void adpcmPauseRequest(short *p, int doubled_idx);

void GetDitchPosition(void)
{
    int i;
    for (i = 0; i < 0xB0; i += 0x58) {
        int *p = (int *)((char *)D_0070A8C0 + i);
        if (*p != 0) {
            int v = *(int *)((char *)p + 0x38);
            if (v == 0x20000) goto call0;
            if (v != 0x40000) goto skip;
            adpcmPauseRequest((short *)p, 2);
        call0:
            adpcmPauseRequest((short *)p, 0);
        skip: ;
        }
    }
}

int DebugActOrientFlag(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x2C);
    p += a1;
    return *(short *)((char *)p + 0x3C);
}

int ACTGetEnvironment(char *a0) {
    char *p = *(char **)(a0 + 0x2C);
    return *(short *)(p + 0x3C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", ACTSetEnvAllmighty);

void GetSofaPosition(void) {
}

void GetCollisCenterPositionSimple(void) {
}

extern int inflate_stored(void *a0, int a1, int a2);

int CheckWallAttributeEdegWall(void *a0, int *a1) {
    inflate_stored(a0, a1[3], 0x5C000);
    return 1;
}

void func_001FA070(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA078);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA130);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA3D0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE0A8);

extern int *D_00629DE4;
extern void func_0023FDD8(void *a0, int a1, void *a2);

extern char D_006138D0[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE250);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE2F8);
