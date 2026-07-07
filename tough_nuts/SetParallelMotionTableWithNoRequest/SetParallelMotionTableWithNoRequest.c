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

extern void func_00105058(void);
extern void GetTableCos(void);
extern void ResetStatic2MotionManager(int id);
extern void *func_00105078(void);
extern void MatrixDrive_TurnXObjectMatrixYZ(int a0, void *a1);
extern void *GetLastQuaternion(void);
extern void func_00105068(void);
extern void InitTableSin(void);
extern char *D_0062B758;
extern char *D_0062B75C;
extern char *D_0062C220;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", GetMotionPlaySpeedRatio);


extern char *D_0062B758;
extern char *D_0062C240;
extern void func_00105058(void);
extern void func_001D5C50(int id);
extern void *func_00105078(void);
extern void func_00105068(void);
extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void execFrameTrigger(int id) {
    char *e = D_0062B758 + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);
    char *o;
    void *m;
    func_00105058();
    func_001D5C50(id);
    o = D_0062C240 + id * 0x10;
    m = func_00105078();
    MatrixDrive_TurnObjectMatrix((int)o, (char *)m + 0x30);
    if (child != -1) {
        execFrameTrigger(child);
    }
    func_00105068();
    if (next != -1) {
        execFrameTrigger(next);
    }
}


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


extern void func_00261188(char *buf, const char *fmt, ...);
extern void display(void *a0, const char *a1, void *a2, void *a3, void *a4);
extern char D_0055DA10[];
extern char D_0055DAD8[];
extern char D_005C8010[];
extern int D_0062AFA8;
extern char D_0062D5E0[], D_0062D5E8[], D_0062D5F0[], D_0062D5F8[];
extern char D_0062D600[], D_0062D608[], D_0062D610[], D_0062D618[];
extern char D_00611F50[], D_00611F60[], D_00611F70[], D_00611F88[];
extern char D_00611FA0[], D_00611FB8[], D_00611FC8[], D_00611FD8[], D_00611FE8[];
extern char D_00611FF8[];

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionOrientManager", shiftMotionOrientEndFunc);


extern void debug_assertMessage();
extern void func_00261188(char *buf, const char *fmt, ...);
extern void func_001AACE0(char *a0, int a1, char *a2);
extern void func_00260380(char *a0, int a1, char *a2);
extern char D_0055DA10[];
extern char D_006169D8[];
extern char D_004C0A98[];
extern char D_00612068[], D_006120C0[], D_00612100[], D_0062D620[];

int shiftMotionOrientBeginFunc(int a0) {
    char buf[0x100];
    char *D = D_0055DA10;
    int off = a0 * 0x190;
    char *f148 = D + 0x148;
    int val = *(int *)(f148 + off);
    if (val == 0xE4) {
        return *((int **)D_004C0A98)[a0];
    }
    {
        int nidx = *(int *)(D_006169D8 + val * 0x10);
        int r17 = *(int *)(D_006169D8 + val * 0x10 + 0xC);
        if (*(int *)(f148 + nidx * 0x190) != 0xE4) {
            char *dc8 = D + 0xC8;
            char *p = dc8 + off;
            debug_assertMessage(D_00612068, p);
            func_00261188(buf, D_006120C0, p);
            func_001AACE0(D_00612100, 0x98, buf);
            func_00260380(D_00612100, 0x98, D_0062D620);
        }
        if (r17 != -1) {
            return r17;
        }
        return *((int **)D_004C0A98)[nidx];
    }
}


extern void debug_assertMessage();
extern void func_00261188(char *buf, const char *fmt, ...);
extern void func_001AACE0(char *a0, int a1, char *a2);
extern void func_00260380(char *a0, int a1, char *a2);
extern char D_0055DA10[];
extern char D_006169D8[];
extern char D_00612068[], D_006120C0[], D_00612100[], D_0062D620[];

float ForTest_ForceShiftMotion(int a0) {
    char buf[0x100];
    char *D = D_0055DA10;
    int off = a0 * 0x190;
    char *f148 = D + 0x148;
    char *r;
    if (*(int *)(f148 + off) == 0xE4) {
        r = D - (-off);
    } else {
        int nidx = *(int *)(D_006169D8 + *(int *)(f148 + off) * 0x10);
        if (*(int *)(f148 + nidx * 0x190) != 0xE4) {
            char *dc8 = D + 0xC8;
            char *p = dc8 + off;
            debug_assertMessage(D_00612068, p);
            func_00261188(buf, D_006120C0, p);
            func_001AACE0(D_00612100, 0x98, buf);
            func_00260380(D_00612100, 0x98, D_0062D620);
        }
        r = D - (-(nidx * 0x190));
    }
    return *(float *)(r + 0x14C);
}


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

extern int GetPureVerticalPlane(void *a0, void *a1, void *a2, int a3);
extern void _PushVu0Registers(void *a0, void *a1, float a2);
extern void func_001DCE78(void *a0, void *a1, void *a2, void *a3, void *a4, int n, float f);
extern char D_00271BD0[];
extern void GetRootProjectionPosOfGObj(void *dst, void *src, int n);
extern void calcFootIK(void *a0, void *a1);

void CopyBlendMotionDataSource(void *a0, void *a1) {
    float local[3];
    char *p = *(char **)((char *)a0 + 0x15C);
    int cnt = *(int *)(p + 0x88);
    char *mat = *(char **)(p + 0x830);
    void *buf = __builtin_alloca(((unsigned)cnt << 8) >> 3);
    float f20 = *(float *)(mat + 0x20);
    if (GetPureVerticalPlane(buf, local, a1, *(int *)(p + 0x8C))) {
        char *q = *(char **)((char *)a0 + 0x15C);
        if (*(int *)(q + 0x650)) {
            _PushVu0Registers(local, local, f20);
            q = *(char **)((char *)a0 + 0x15C);
        }
        local[0] = local[0] - *(float *)(q + 0x660);
        local[1] = local[1] - *(float *)(q + 0x664);
        local[2] = local[2] + *(float *)(q + 0x668);
        func_001DCE78(a0, buf, buf, local, D_00271BD0, -1, 1.0f);
        {
            char *r = *(char **)((char *)a0 + 0x15C);
            GetRootProjectionPosOfGObj(*(void **)(r + 0x77C), buf, *(int *)(r + 0x88));
        }
        {
            char *s = *(char **)((char *)a0 + 0x15C);
            MatrixDrive_TurnObjectMatrix((int)(s + 0x780), local);
        }
        calcFootIK(a0, buf);
    }
}


extern int CheckFloorAttribute(void *a0);
extern float D_00629684;
extern float D_00629688;

void SetParallelMotionTableWithNoRequest(void *a0, void *a1) {
    int i;
    int n = *(int *)(*(char **)((char *)a0 + 0x15C) + 0x7F4);
    if (n != 0) {
        float *lb = (float *)__builtin_alloca(((unsigned)n << 5) >> 3);
        if (CheckFloorAttribute(lb)) {
            if (n > 0) {
                float g684 = D_00629684;
                float zero = 0.0f;
                float g688 = D_00629688;
                float *p = lb;
                for (i = 0; i < n; i++) {
                    int *dst = *(int **)(*(char **)((char *)a0 + 0x15C) + 0x7F8) + i;
                    float v = *p * g684;
                    if (v < zero) {
                        if (g688 < -v) {
                            *(float *)dst = v;
                        } else {
                            *dst = 0;
                        }
                    } else {
                        if (g688 < v) {
                            *(float *)dst = v;
                        } else {
                            *dst = 0;
                        }
                    }
                    p++;
                }
            }
        } else {
            if (n > 0) {
                for (i = 0; i < n; i++) {
                    int *dst = *(int **)(*(char **)((char *)a0 + 0x15C) + 0x7F8) + i;
                    *dst = 0;
                }
            }
        }
    }
}


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


extern void GetRootProjectionPosOfGObj(void *dst, void *src, int n);
extern void GetTableArcSin(void *a0, int a1, float f0, float f1, float f2);
extern void func_0010E148(void *a0, void *a1, void *a2);

typedef struct { char b[8]; } Blk8;

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
    char *e = D_0055DA10 + 0x190 * idx;
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
