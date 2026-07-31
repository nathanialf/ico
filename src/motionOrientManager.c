#include "common.h"

#include "ico/types.h"

typedef struct { char b[0x20]; } ShiftBlk;

typedef struct { int f_0; int f_4; char pad[0x10]; } Slip;

/* .rodata carved from blob (VMA 0x6196C8..0x6196E0, incl. null pad to the
 * jtbl_006196E0 .align 3 boundary that immediately follows it). Referenced
 * by %hi/%lo from the still-INCLUDE_ASM'd shiftMotionOrientEndFunc body
 * itself, so it needs a real definition even before that function is
 * ported. */
const char D_006196C8[0x18] = "%s \207 %s (%s)\n";


extern unsigned short D_00565060[];
extern int D_00292540[];
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern char D_00276140[];
extern int DebugDisp1CollisionWithColor(void *a0);
extern void GetInverseQuaternion(void *a0, void *a1);

int orientDebug(void *a0) {
    int r = DebugDisp1CollisionWithColor(a0);
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x7DC) + r * 0x40;
    if (r < 0) {
        return 0;
    }
    *(int *)p = 0;
    GetInverseQuaternion(p + 0x20, D_00276140);
    GetInverseQuaternion(p + 0x30, D_00276140);
    return 1;
}

int GetNbMotionFrames(void *a0, float f12) {
    int r = DebugDisp1CollisionWithColor(a0);
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x7DC) + r * 0x40;
    if (r < 0) {
        return 0;
    }
    *(float *)p = f12;
    GetInverseQuaternion(p + 0x20, D_00276140);
    GetInverseQuaternion(p + 0x30, D_00276140);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetMotionPlaySpeedRatio);

extern char *D_00633478;
extern char *D_00633F4C;
extern void MatrixDrive_TurnObjectMatrix__p4(int a0, void *a1) __asm__("MatrixDrive_TurnObjectMatrix");
extern void func_00105258(void);
extern void func_00105268(void);
extern void *func_00105278(void);
extern void func_001D88B8(int id);

void execFrameTrigger(int id) {
    char *e = D_00633478 + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);
    char *o;
    void *m;
    func_00105258();
    func_001D88B8(id);
    o = D_00633F4C + id * 0x10;
    m = func_00105278();
    MatrixDrive_TurnObjectMatrix__p4((int)o, (char *)m + 0x30);
    if (child != -1) {
        execFrameTrigger(child);
    }
    func_00105268();
    if (next != -1) {
        execFrameTrigger(next);
    }
}

void UpdateFrameCounter(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}

extern void ChangeFieldCollisionDebugMode();

int sendStateMail(char *a0, float f) {
    char buf[0xC0] __attribute__((aligned(16)));
    MatrixDrive_TurnObjectMatrix__p4((int)buf, a0);
    MatrixDrive_TurnObjectMatrix__p4((int)(buf + 0x10), a0);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + f;
    ChangeFieldCollisionDebugMode(buf);
    return *(int *)(buf + 0x94);
}

extern char *D_0063347C;
extern void func_001DF368(int a, int b);

void shiftMotionData(void) {
    ShiftBlk buf;
    int x, y;
    char *p;
    buf = *(ShiftBlk *)(*(char **)(D_0063347C + 0x15C) + 0x180);
    func_001DF368(x, y);
    p = *(char **)(D_0063347C + 0x15C);
    if (*(int *)(p + 0x634) != 0) {
        *(ShiftBlk *)(p + 0x180) = buf;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionOrientEndFunc);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionOrientBeginFunc);

extern char D_00565060__p4[] __asm__("D_00565060");
extern char D_00619738[];
extern char D_00619790[];
extern char D_006197D0[];
extern char D_0061C710[];
extern char D_00612068[], D_006120C0[], D_00612100[], D_006334C0[];
extern void debug_assertMessage();
extern void func_001AD748(char *a0, int a1, char *a2);
extern void func_00263FF0(char *a0, int a1, char *a2);
extern void func_00264DF8(char *buf, const char *fmt, ...);

float ForTest_ForceShiftMotion(int a0) {
    char buf[0x100];
    char *D = D_00565060__p4;
    int off = a0 * 0x190;
    char *f148 = D + 0x148;
    char *r;
    if (*(int *)(f148 + off) == 0xE4) {
        r = D - (-off);
    } else {
        int nidx = *(int *)(D_0061C710 + *(int *)(f148 + off) * 0x10);
        if (*(int *)(f148 + nidx * 0x190) != 0xE4) {
            char *dc8 = D + 0xC8;
            char *p = dc8 + off;
            debug_assertMessage(D_00619738, p);
            func_00264DF8(buf, D_00619790, p);
            func_001AD748(D_006197D0, 0x98, buf);
            func_00263FF0(D_006197D0, 0x98, D_006334C0);
        }
        r = D - (-(nidx * 0x190));
    }
    return *(float *)(r + 0x14C);
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", normalMotionShift);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", parallelMotionShift);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetMotionRequest);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getNodeBlendedFloatingMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getMotionGeometry);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getShapeGeometry);

extern void getNodeBlendedFloatingMotion(int a0, int a1, int a2, int a3);

void getStreamMotionGeometry(int a0, int a1) {
    getNodeBlendedFloatingMotion(a0, a1, a1, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamShapeGeometry);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", ExecMotionOrient);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetNodeRotationLimitDataTable);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetMotionOrient);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getMotionOrient);

extern char D_00275850[];
extern int GetPureVerticalPlane(void *a0, void *a1, void *a2, int a3);
extern void GetRootProjectionPosOfGObj(void *dst, void *src, int n);
extern void _PushVu0Registers(void *a0, void *a1, float a2);
extern void calcFootIK(void *a0, void *a1);
extern void func_001DFBC8(void *a0, void *a1, void *a2, void *a3, void *a4, int n, float f);

void CopyBlendMotionDataSource(void *a0, void *a1) {
    float local[3];
    char *p = *(char **)((char *)a0 + 0x15C);
    int cnt = *(int *)(p + 0x88);
    char *mat = *(char **)(p + 0x840);
    void *buf = __builtin_alloca(((unsigned)cnt << 8) >> 3);
    float f20 = *(float *)(mat + 0x20);
    if (GetPureVerticalPlane(buf, local, a1, *(int *)(p + 0x8C))) {
        char *q = *(char **)((char *)a0 + 0x15C);
        if (*(int *)(q + 0x660)) {
            _PushVu0Registers(local, local, f20);
            q = *(char **)((char *)a0 + 0x15C);
        }
        local[0] = local[0] - *(float *)(q + 0x670);
        local[1] = local[1] - *(float *)(q + 0x674);
        local[2] = local[2] + *(float *)(q + 0x678);
        func_001DFBC8(a0, buf, buf, local, D_00275850, -1, 1.0f);
        {
            char *r = *(char **)((char *)a0 + 0x15C);
            GetRootProjectionPosOfGObj(*(void **)(r + 0x78C), buf, *(int *)(r + 0x88));
        }
        {
            char *s = *(char **)((char *)a0 + 0x15C);
            MatrixDrive_TurnObjectMatrix__p4((int)(s + 0x790), local);
        }
        calcFootIK(a0, buf);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetParallelMotionTableWithNoRequest);

extern void CopyBlendMotionDataSource(void *a0, void *buf);
extern void SetParallelMotionTableWithNoRequest(void *a0, void *buf);
extern int StandbyStreamMotion(void *m);
extern void _infoUpdate(void *buf, void *m);

void SetParallelMotionTable(void *a0) {
    void *m = *(void **)(*(int *)((char *)a0 + 0x15C) + 0x470);
    int n = StandbyStreamMotion(m);
    char buf[n];
    _infoUpdate(buf, m);
    CopyBlendMotionDataSource(a0, buf);
    SetParallelMotionTableWithNoRequest(a0, buf);
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", InitMotionOrient);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetCurrentMotionDirectionAdjustFlag);

int *ExecuteSlipProc(int start, int end, int a2, int a3) {
    int best = -1;
    if (start < end) {
        do {
            int *p = (int *)(((char *)D_00292540) - (-(start * 0x18)));
            if (p[1] == a3) {
                int *q = (int *)(((char *)D_00292540) + (start * 0x18));
                if (q[0] == a2) {
                    return q;
                }
                if (q[0] == 0x43D) {
                    best = start;
                }
            }
            start++;
        } while (start < end);
    }
    if (best != -1) {
        return (int *)(((char *)D_00292540) + (best * 0x18));
    }
    return (int *)0;
}

extern Slip D_00292540__p4[] __asm__("D_00292540");
extern Slip D_0029F038;

void *ExecutePauseSlipProc(int i, int limit, int a2, int a3)
{
    void *r;
    int found = -1;
    while (i < limit) {
        if (D_00292540__p4[i].f_4 == a3) {
            if (D_00292540__p4[i].f_0 == a2) {
                r = &D_00292540__p4[i];
                goto done;
            }
            if (D_00292540__p4[i].f_0 == 0x43D) {
                found = i;
            }
        }
        i++;
    }
    if (found != -1) {
        r = &D_00292540__p4[found];
    } else {
        r = (void *)0;
    }
done:
    if (r == (void *)0) {
        r = &D_0029F038;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", func_001E45E0);

void func_001E4700(void *self, int a1, int a2)
{
    char *m = *(char **)((char *)self + 0x15C) + 0x470;

    if (*(int *)(m + 0x18) == 0) {
        *(int *)(m + 0x1C) = a2;
        *(int *)(m + 0x20) = a1;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", func_001E4728);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", func_001E4798);

int func_001E4838(void *a0)
{
  void *p = *((void **) (((char *) a0) + 0x15C));
  int idx = *((int *) (((char *) p) + 0x4A0));
  int new_var;
  new_var = 0x184;
  return (((unsigned int) (*((int *) (((char *)D_00565060 + (idx * 0x190)) + new_var)))) >> 28) & 3;
}

