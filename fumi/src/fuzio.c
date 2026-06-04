#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", fzShowV);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", fzShowM);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", fzMagnitude2f);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", fzMagnitude3f);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", fzMagnitudefv);

void fzMagnitude2fv(float *a0, float a1, float a2, float a3, float a4) {
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a3;
    a0[3] = a4;
}

int fzMagnitudeByLine(void *a0) {
    if (*(int *)((char *)a0 + 0x88) == 0) return 0;
    return *(int *)((char *)a0 + 0x98);
}

int fzMagnitudeByLineSeg(void *a0) {
    if (*(int *)((char *)a0 + 0x94) == 0) return 0;
    return *(int *)((char *)a0 + 0x98);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001668B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166910);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001669D0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166A00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166A48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166A88);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166AB8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166AF8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166BD8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166D00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166E50);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166FC0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167120);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167270);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001673B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001674F0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167630);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167798);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001678D8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167A00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167B48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167C88);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167DB0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167E88);

extern int D_0062A69C;
extern void ClipWallBoxStop(void);

void func_00167F60(void) {
    D_0062A69C = 1;
    ClipWallBoxStop();
    D_0062A69C = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167F88);

void func_00167FE8(void *a0) {
    int *p = (int *)a0;
    p[4] = (int)a0 + p[4];
    p[5] = (int)a0 + p[5];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00168008);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00168070);

extern float MatrixDrive_GetTurnYAngleXZ(float a0);

float func_001680D0(float a0, float a1) {
    return MatrixDrive_GetTurnYAngleXZ(a0 * a0 + a1 * a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001680F8);

extern float func_0023FE70(int a0, int a1);

float func_00168128(int a0) {
    return MatrixDrive_GetTurnYAngleXZ(func_0023FE70(a0, a0));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00168150);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001681E0);


/* recovered struct shapes */
typedef struct {
    short              f_0;  /* 0x00 */
} S_006A4B40;  /* stride 0x2 */

/* end struct shapes */
