#include "common.h"

typedef struct {
    char pad[0x134];
    int node_id;  /* 0x134 */
    char pad2[0x190 - 0x134 - 4];
} MotionNode;
extern MotionNode D_0055DA10[];
extern int D_004C0A98[];

void pursueNodeList(int a0) {
    int i;
    for (i = 0; i <= 0x43F; i++) {
        if (D_0055DA10[i].node_id == a0) {
            D_004C0A98[i] = 0;
        }
    }
}

int CheckMotionIncludeFacialData(void *a0) {
    return (char *)a0 + 0x10 < *(char **)((char *)a0 + 0x8) ? 0 : -1;
}

extern void func_001D1DF0(void *a0, void *a1, void *a2, void *a3, int a4);
extern char D_004C1BE0[];
extern char D_004C1BF0[];
extern char D_004C1C00[];
extern char D_004C1C10[];
extern char D_004C1C20[];

void InitMotionMemorySize(void) {
    func_001D1DF0(D_004C1BF0, D_004C1BE0, D_004C1C10, D_004C1BE0, -1);
    func_001D1DF0(D_004C1C10, D_004C1BE0, D_004C1C00, D_004C1BE0, -1);
    func_001D1DF0(D_004C1C00, D_004C1BE0, D_004C1C20, D_004C1BE0, -1);
    func_001D1DF0(D_004C1C20, D_004C1BE0, D_004C1BF0, D_004C1BE0, -1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", limitHPAngleAndSetB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", avoidReverseInterpOnCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", avoidReverseInterpOnCurrentMatrixWithLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", ResetStatic2MotionManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", EditRotEmphasys);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", getFinalMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", getFinalMatrixWithNaturalGeometry);

extern char *D_0062B758;
extern char *D_0062C244;
extern float D_0062B720;
extern char D_00703040[];
extern char D_00703080[];
extern void _ScaleVectorXYZ(void *buf, void *p1, float f);
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
extern void getQuaternionFromMatrix(void *a0, void *a1);
extern void *func_00105078(void);
extern void *func_00105090(void);
extern void _MulMatrix(void *a0, void *a1, void *a2);

void _calcNaturalGeometry(int a0) {
    char *elemA = D_0062B758 + a0 * 0x40;
    char *elemB = D_0062C244 + a0 * 0x20;
    void *x;
    if (*(int *)(elemA + 0x38) != -1) {
        _ScaleVectorXYZ(D_00703080, elemA + 0x10, D_0062B720);
        GetMatrixFromQuaternionPos(D_00703040, elemB + 0x10, D_00703080);
    } else {
        getQuaternionFromMatrix(D_00703040, elemB + 0x10);
    }
    x = func_00105078();
    _MulMatrix(x, func_00105090(), D_00703040);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5D00);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611A30;  /* stride 0x4 */

/* end struct shapes */
