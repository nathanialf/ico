#include "common.h"

extern int D_0062B698;

void DispFlyInfo(void) {
    D_0062B698 = 0;
}

extern int D_0062B698;
extern float D_00629544;
extern void func_00260568(void *a0, int a1, int a2);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void ClipWallField(void *a0, int a1);

int InitFlyInfo(char *out, void *a1) {
    char buf[0xC0];
    if (D_0062B698 == 0) {
        return 0;
    }
    func_00260568(buf, 0, 0xC0);
    MatrixDrive_TurnObjectMatrix(buf, a1);
    MatrixDrive_TurnObjectMatrix(buf + 0x10, a1);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + D_00629544;
    ClipWallField(buf, D_0062B698);
    if (*(int *)(buf + 0x94) != 0) {
        int v = *(int *)(buf + 0x98) & 0xF;
        int n;
        *(float *)out = *(float *)(buf + 0x24);
        if (v == 1) {
            n = 0;
        } else {
            n = v * 100;
        }
        n = -n;
        *(int *)(out + 0xC) = 0;
        *(float *)(out + 0x8) = (float)n;
        *(float *)(out + 0x4) = *(float *)out + (float)n;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flyManager", InitFlyManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flyManager", GetFlyLimitHeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flyManager", GetFlyLimitClearance);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flyManager", func_001CDBB0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flyManager", func_001CDCB0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flyManager", func_001CDEF8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flyManager", func_001CE0B0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flyManager", func_001CE340);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_38;  /* 0x38 */
} S_005CD670;  /* stride 0x3C */

typedef struct {
    unsigned int       f_8;  /* 0x08 */
} S_00535F68;  /* stride 0xC */

typedef struct {
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
} S_006189F8;  /* stride 0x24 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00618950;  /* stride 0xC */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00618CC8;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006195E0;  /* stride 0xC */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00619F58;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00702F50;  /* stride 0x4 */

/* end struct shapes */
