#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", dispSquare2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", findActPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkActPointWithHeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", clearCollisionStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkUpperWallState);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkWallSideState);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkWallState);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkCliffState);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", _checkCliffAndWall);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkCliffAndWallStateOfLastPlane);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkCliffAndWallStateAtJump);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", dispActNode);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", dispLastNode);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", _getGeometryOfMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", execPositionReserver);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", GetGeometryOfMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", GetMatrixOfMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001D8398);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", getInitialMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", dispSkelton);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", SkelTest);

extern int D_0062B75C;
extern int D_0062C230;
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

void SkelTestGeo(void) {
    iosOmBeforeFuncStandard(D_0062B75C, 0x18, D_0062B75C);
    MatrixDrive_TurnObjectMatrix(D_0062C230 + 0x140, D_0062C230);
}

void SetHitCollisionDisplay(void) {
    iosOmBeforeFuncStandard(D_0062B75C, 0xF0, D_0062B75C);
    MatrixDrive_TurnObjectMatrix(D_0062C230 + 0x140, D_0062C230);
}

extern void func_00105108(float, float, float);
extern int func_00105078(void);
extern void func_0010E300(char *p);
extern float D_00703094[];
extern int func_00104D20(void);
extern int func_002400F8(int);
extern void checkActPointWithHeight(void);
extern void func_00105068(void);

void GetWallVector(void)
{
    int v;
    func_00104D20();
    v = func_00105078();
    func_002400F8(v);
    {
        register float *p = (float *)D_0062C230;
        func_00105108(p[0], p[1] - D_00703094[0], p[2]);
    }
    func_0010E300((char *)D_0062C230 + 0x30);
    checkActPointWithHeight();
    func_00105068();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", getGeometryOfMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001D9E10);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DA508);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DA980);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DAAC0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB538);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB620);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB710);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB870);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB9A0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DBBB8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DBFF8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DC208);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DC428);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DC640);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DCB70);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DCE78);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DD3A8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DD6E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DD9B8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DDAB8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DDB10);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DDB68);

extern int D_0062B718;
extern int D_0062B71C;

void func_001DDC28(int a0, int a1) {
    D_0062B718 = a0;
    D_0062B71C = a1;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611DE0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611E60;  /* stride 0x4 */

/* end struct shapes */
