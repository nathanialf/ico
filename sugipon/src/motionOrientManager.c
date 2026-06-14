#include "common.h"
#include "ico/types.h"

extern int DebugDisp1CollisionWithColor(void *a0);
extern void GetInverseQuaternion(void *a0, void *a1);
extern char D_002724B0[];

int orientDebug(void *a0) {
    int r = DebugDisp1CollisionWithColor(a0);
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x7CC) + r * 0x40;
    if (r < 0) {
        return 0;
    }
    *(int *)p = 0;
    GetInverseQuaternion(p + 0x20, D_002724B0);
    GetInverseQuaternion(p + 0x30, D_002724B0);
    return 1;
}

extern int DebugDisp1CollisionWithColor(void *a0);
extern void GetInverseQuaternion(void *a0, void *a1);
extern char D_002724B0[];

int GetNbMotionFrames(void *a0, float f12) {
    int r = DebugDisp1CollisionWithColor(a0);
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x7CC) + r * 0x40;
    if (r < 0) {
        return 0;
    }
    *(float *)p = f12;
    GetInverseQuaternion(p + 0x20, D_002724B0);
    GetInverseQuaternion(p + 0x30, D_002724B0);
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", GetMotionPlaySpeedRatio);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", execFrameTrigger);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void UpdateFrameCounter(int a0, char *a1) {
    MatrixDrive_TurnObjectMatrix(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}

extern void ChangeFieldCollisionDebugMode();

int sendStateMail(char *a0, float f) {
    char buf[0xC0] __attribute__((aligned(16)));
    MatrixDrive_TurnObjectMatrix((int)buf, a0);
    MatrixDrive_TurnObjectMatrix((int)(buf + 0x10), a0);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + f;
    ChangeFieldCollisionDebugMode(buf);
    return *(int *)(buf + 0x94);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", shiftMotionData);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", shiftMotionOrientEndFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", shiftMotionOrientBeginFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", ForTest_ForceShiftMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", normalMotionShift);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", parallelMotionShift);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", SetMotionRequest);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", getNodeBlendedFloatingMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", getMotionGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", getShapeGeometry);

extern void getNodeBlendedFloatingMotion(int a0, int a1, int a2, int a3);

void getStreamMotionGeometry(int a0, int a1) {
    getNodeBlendedFloatingMotion(a0, a1, a1, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", getStreamShapeGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", getStreamMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", ExecMotionOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", SetNodeRotationLimitDataTable);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", GetMotionOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", getMotionOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", CopyBlendMotionDataSource);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", SetParallelMotionTableWithNoRequest);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", SetParallelMotionTable);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", InitMotionOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", GetCurrentMotionDirectionAdjustFlag);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", ExecuteSlipProc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", ExecutePauseSlipProc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", func_001E1860);

void func_001E1980(void *a0, int a1, int a2) {
    char *p = *(char **)((char *)a0 + 0x15C) + 0x460;
    if (*(int *)(p + 0x18) == 0) {
        *(int *)(p + 0x1C) = a2;
        *(int *)(p + 0x20) = a1;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", func_001E19A8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", func_001E1A18);

extern char D_0055DA10[];

int func_001E1AB8(char *a0) {
    int idx = GOBJ_SUB(a0)->f_490;
    char *e = D_0055DA10 + idx * 0x190;
    unsigned int v = *(unsigned int *)(e + 0x184);
    return (v >> 28) & 3;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_100;  /* 0x100 */
    unsigned int       f_118;  /* 0x118 */
    unsigned int       f_11C;  /* 0x11C */
    unsigned int       f_130;  /* 0x130 */
    unsigned int       f_134;  /* 0x134 */
    unsigned int       f_148;  /* 0x148 */
    unsigned int       f_15C;  /* 0x15C */
    short              f_180;  /* 0x180 */
    unsigned int       f_184;  /* 0x184 */
    unsigned short     f_186;  /* 0x186 */
    unsigned int       f_188;  /* 0x188 */
    unsigned short     f_18A;  /* 0x18A */
    unsigned int       f_18C;  /* 0x18C */
} S_0055DA10;  /* stride 0x190 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004C0A98;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006169D8;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00612010;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00612290;  /* stride 0x4 */

/* end struct shapes */
