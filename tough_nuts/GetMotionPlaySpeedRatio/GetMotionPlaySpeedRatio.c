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

extern void MatrixDrive_PushMatrixWithNoCopy(void);
extern void PushQuaternionWithNoCopy(void);
extern void ResetStatic2MotionManager(int id);
extern void *func_00105078(void);
extern void CopyMatrix(int a0, void *a1);
extern void *GetLastQuaternion(void);
extern void MatrixDrive_PopMatrix(void);
extern void PopQuaternion(void);
extern char *D_0062B758;
extern char *D_0062B75C;
extern char *D_0062C220;

void getFinalMatrixCore(int id) {
    char *e;
    char *o1;
    char *o2;
    int t;
    void *r;
    int off;
    do {
        off = id * 0x40;
        e = D_0062B758 + off;
        MatrixDrive_PushMatrixWithNoCopy();
        PushQuaternionWithNoCopy();
        ResetStatic2MotionManager(id);
        o1 = *(char **)(*(char **)(D_0062B75C + 0x15C) + 0xC) + off;
        r = func_00105078();
        CopyMatrix((int)o1, r);
        o2 = D_0062C220 + id * 0x10;
        r = GetLastQuaternion();
        GetInverseQuaternion(o2, r);
        if (*(int *)(e + 0x30) != -1) {
            getFinalMatrixCore(*(int *)(e + 0x30));
        }
        MatrixDrive_PopMatrix();
        PopQuaternion();
        id = t = *(int *)(e + 0x34);
    } while (t != -1);
}


extern char *D_0062B758;
extern char *D_0062C240;
extern void MatrixDrive_PushMatrixWithNoCopy(void);
extern void _calcNaturalGeometry(int id);
extern void *func_00105078(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void pursueNaturalGeometry(int id) {
    char *e = D_0062B758 + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);
    char *o;
    void *m;
    MatrixDrive_PushMatrixWithNoCopy();
    _calcNaturalGeometry(id);
    o = D_0062C240 + id * 0x10;
    m = func_00105078();
    MatrixDrive_TurnObjectMatrix((int)o, (char *)m + 0x30);
    if (child != -1) {
        pursueNaturalGeometry(child);
    }
    MatrixDrive_PopMatrix();
    if (next != -1) {
        pursueNaturalGeometry(next);
    }
}


extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void GetWallVector(int a0, char *a1) {
    MatrixDrive_TurnObjectMatrix(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}

extern void ChangeFieldCollisionDebugMode();

int upperFieldCheck(char *a0, float f) {
    char buf[0xC0] __attribute__((aligned(16)));
    MatrixDrive_TurnObjectMatrix((int)buf, a0);
    MatrixDrive_TurnObjectMatrix((int)(buf + 0x10), a0);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + f;
    ChangeFieldCollisionDebugMode(buf);
    return *(int *)(buf + 0x94);
}

extern char *D_0062B75C;
extern void func_001DC640(int a, int b);

typedef struct { char b[0x20]; } ShiftBlk;

void shiftMotionData(void) {
    ShiftBlk buf;
    int x, y;
    char *p;
    buf = *(ShiftBlk *)(*(char **)(D_0062B75C + 0x15C) + 0x170);
    func_001DC640(x, y);
    p = *(char **)(D_0062B75C + 0x15C);
    if (*(int *)(p + 0x624) != 0) {
        *(ShiftBlk *)(p + 0x170) = buf;
    }
}


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

extern int StandbyStreamMotion(void *m);
extern void _infoUpdate(void *buf, void *m);
extern void CopyBlendMotionDataSource(void *a0, void *buf);
extern void SetParallelMotionTableWithNoRequest(void *a0, void *buf);

void SetParallelMotionTable(void *a0) {
    void *m = *(void **)(*(int *)((char *)a0 + 0x15C) + 0x460);
    int n = StandbyStreamMotion(m);
    char buf[n];
    _infoUpdate(buf, m);
    CopyBlendMotionDataSource(a0, buf);
    SetParallelMotionTableWithNoRequest(a0, buf);
}


INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", InitMotionOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", GetCurrentMotionDirectionAdjustFlag);

typedef struct { int f_0; int f_4; char pad[0x10]; } Slip;
extern Slip D_0028E680[];

void *ExecuteSlipProc(int i, int limit, int a2, int a3)
{
    int found = -1;
    while (i < limit) {
        if (D_0028E680[i].f_4 == a3) {
            if (D_0028E680[i].f_0 == a2) {
                return &D_0028E680[i];
            }
            if (D_0028E680[i].f_0 == 0x43F) {
                found = i;
            }
        }
        i++;
    }
    if (found != -1) {
        return &D_0028E680[found];
    }
    return (void *)0;
}

extern Slip D_0029AEF0;

void *ExecutePauseSlipProc(int i, int limit, int a2, int a3)
{
    void *r;
    int found = -1;
    while (i < limit) {
        if (D_0028E680[i].f_4 == a3) {
            if (D_0028E680[i].f_0 == a2) {
                r = &D_0028E680[i];
                goto done;
            }
            if (D_0028E680[i].f_0 == 0x43F) {
                found = i;
            }
        }
        i++;
    }
    if (found != -1) {
        r = &D_0028E680[found];
    } else {
        r = (void *)0;
    }
done:
    if (r == (void *)0) {
        r = &D_0029AEF0;
    }
    return r;
}


INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", func_001E1860);

void func_001E1980(void *a0, int a1, int a2) {
    char *p = *(char **)((char *)a0 + 0x15C) + 0x460;
    if (*(int *)(p + 0x18) == 0) {
        *(int *)(p + 0x1C) = a2;
        *(int *)(p + 0x20) = a1;
    }
}

extern int getStreamMotion();

void func_001E19A8(void *a0, int a1, int a2, int a3, int a4) {
    int *p = (int *)(*(int *)((char *)a0 + 0x15C) + 0x460);
    int *q;
    int old = *(int *)((char *)p + 0xD0);
    *(int *)((char *)p + 0xD0) = 0xEB;
    q = (int *)(*(int *)((char *)a0 + 0x15C) + 0x460);
    if (*(int *)((char *)q + 0x18) == 0) {
        *(int *)((char *)q + 0x1C) = a2;
        *(int *)((char *)q + 0x20) = a1;
    }
    *(int *)((char *)p + 0x24) = a3;
    *(int *)((char *)p + 0x28) = a4;
    if (getStreamMotion(a0) != 0) {
        *(int *)((char *)p + 0x44) = 0;
    } else {
        *(int *)((char *)p + 0xD0) = old;
    }
}


extern int GetCurrentMotionDirectionAdjustFlag();
extern int soundSePlayModeStop();

void func_001E1A18(void *obj, int p1, int p2, int p3, int p4, int p5) {
    char *s = *(char **)((char *)obj + 0x15C) + 0x460;
    if (p3 >= 0 && p4 >= 0) {
        GetCurrentMotionDirectionAdjustFlag(obj, p3, p4);
    }
    *(int *)(s + 0x4) = p1;
    *(int *)(s + 0x8) = p2;
    getNodeBlendedFloatingMotion((int)obj, p5, p5, 0);
    *(int *)(s + 0x1AC) = soundSePlayModeStop();
    *(int *)(s + 0x1B0) = soundSePlayModeStop();
}


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
