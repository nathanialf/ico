#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", dispSquare2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", findActPoint);

extern int func_00105078(void);
extern int func_00104D20(void);
extern void func_00105068(void);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern int D_0062C234;
extern void func_00260568(void *a0, int a1, int a2);
extern void func_001050A8(void *a0);
extern void func_0023FDD8(int *a0, int a1, char *a2);
extern void ClipWallBoxStop(void *a0);
extern float MatrixDrive_GetTurnZAngleYX(void *a0, void *a1);
extern char D_004C1C60[];
extern char D_004C1C70[];

void checkActPointWithHeight(void) {
    char buf[0xC0];
    func_00260568(buf, 0, 0xC0);
    func_00104D20();
    func_001050A8(D_004C1C60);
    MatrixDrive_TurnObjectMatrix((int)buf, func_00105078() + 0x30);
    func_0023FDD8((int *)(buf + 0x10), func_00105078(), D_004C1C70);
    func_00105068();
    ClipWallBoxStop(buf);
    if (*(int *)(buf + 0x88) != 0) {
        float a;
        int *D;
        a = MatrixDrive_GetTurnZAngleYX(buf + 0x20, buf);
        D = (int *)D_0062C234;
        *(float *)((char *)D + 0x170) = a;
        *(int *)((char *)D + 0x108) = 1;
        *(int *)((char *)D + 0x14) = *(int *)((char *)D + 0x14) | 0x1000;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", clearCollisionStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkUpperWallState);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkWallSideState);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkWallState);

extern void func_00118AA0(int a0);
extern int func_00105078(void);
extern float func_00166A48(int a0, int a1);
extern void func_00105108(float, float, float);
extern void func_0010E300(char *p);
extern int func_00104D20(void);
extern void checkWallState(void);
extern void func_00105068(void);
extern void clearCollisionStatus(void);
extern int D_0062C230;
extern int D_0062C234;

void checkCliffState(void)
{
    func_00118AA0(func_00105078());
    {
        register float *p = (float *)D_0062C230;
        float r = func_00166A48(D_0062C230 + 0x120, D_0062C230);
        func_00105108(p[0], r, *(float *)(D_0062C230 + 8));
    }
    func_0010E300((char *)D_0062C230 + 0x30);
    func_00104D20();
    checkWallState();
    func_00105068();
    if (*(int *)(D_0062C234 + 0xE4) != 0) {
        func_00104D20();
        clearCollisionStatus();
        func_00105068();
    }
}

extern int D_0062C230;
extern int func_00105078(void);
extern void func_00105108(float, float, float);
extern void func_0010E300(char *p);
extern void func_00118AA0(int a0);
extern void checkWallState(void);

void _checkCliffAndWall(void)
{
    func_00118AA0(func_00105078());
    {
        register float *p = (float *)D_0062C230;
        func_00105108(p[0], p[1] + p[112] + 10.0f, p[2]);
    }
    func_0010E300((char *)D_0062C230 + 0x30);
    checkWallState();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkCliffAndWallStateOfLastPlane);

extern void gif_SpriteOffset();
extern void gsb_SetFrame();
extern int func_00104D20(void);
extern int func_00105078(void);
extern void f2400F8(int) __asm__("func_002400F8");
extern void func_00105108(float, float, float);
extern void func_00104EB0(float, float, float);
extern void InitMotionMemorySize(int);
extern void func_00105068(void);
extern void func_0010F9D0();
extern int D_0062C230;

void checkCliffAndWallStateAtJump(void)
{
    register float *p;
    int v;
    gif_SpriteOffset(0xB);
    gsb_SetFrame(1, 5, 0x80);
    func_00104D20();
    v = func_00105078();
    f2400F8(v);
    p = (float *)D_0062C230;
    func_00105108(p[104], p[105], p[106]);
    func_00104EB0(8.0f, 8.0f, 8.0f);
    InitMotionMemorySize(0xFF);
    func_00105068();
    func_0010F9D0();
}

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

extern void gif_SpriteOffset();
extern void gsb_SetFrame();
extern void func_001DD6E8();
extern void func_0010F9D0();

void func_001DDAB8(void) {
    int v;
    gif_SpriteOffset(0xB);
    gsb_SetFrame(1, 5, 0x80);
    func_00104D20();
    v = func_00105078();
    func_002400F8(v);
    func_001DD6E8(0);
    func_00105068();
    func_0010F9D0();
}

extern int D_0062B758;
extern int D_0062AF90;
extern void func_0010F048();
extern void func_001DDAB8_a(char *) __asm__("func_001DDAB8");

void func_001DDB10(char *a0) {
    int sub = *(int *)(a0 + 0x15C);
    int v;
    D_0062B75C = (int)a0;
    v = *(int *)(sub + 0x8C);
    D_0062B758 = v;
    if (v != 0) {
        func_0010F048();
        if (D_0062AF90 != 0) {
            func_001DDAB8_a(a0);
        }
    }
}

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
