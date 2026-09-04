#include "common.h"

#include "ico/types.h"

typedef struct { char b[0x20]; } ShiftBlk;

typedef struct { int f_0; int f_4; char pad[0x10]; } Slip;

extern unsigned short D_00565060[];
extern Slip D_00292540[];
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

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getFinalMatrixCore);

extern char *D_00633478;
extern char *D_00633F4C;
extern void MatrixDrive_PushMatrixWithNoCopy(void);
extern void MatrixDrive_PopMatrix(void);
extern void *func_00105278(void);
extern void _calcNaturalGeometry(int id);

void pursueNaturalGeometry(int id) {
    char *e = D_00633478 + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);
    char *o;
    void *m;
    MatrixDrive_PushMatrixWithNoCopy();
    _calcNaturalGeometry(id);
    o = D_00633F4C + id * 0x10;
    m = func_00105278();
    MatrixDrive_TurnObjectMatrix((void *)o, (char *)m + 0x30);
    if (child != -1) {
        pursueNaturalGeometry(child);
    }
    MatrixDrive_PopMatrix();
    if (next != -1) {
        pursueNaturalGeometry(next);
    }
}

void GetWallVector(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}

extern void ChangeFieldCollisionDebugMode();

int upperFieldCheck(char *a0, float f) {
    char buf[0xC0] __attribute__((aligned(16)));
    MatrixDrive_TurnObjectMatrix((void *)buf, a0);
    MatrixDrive_TurnObjectMatrix((void *)(buf + 0x10), a0);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + f;
    ChangeFieldCollisionDebugMode(buf);
    return *(int *)(buf + 0x94);
}

extern char *D_0063347C;
extern void func_001DF368(int a, int b);

void getGeometryOfMotion(void) {
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

/* motionOrientManager .rodata run 0x619620..0x619BB0 -- byte-verified
 * against baseelf; extends the old narrow D_006196C8-only carve (moved down
 * from the top of the file to its real VMA-ordered position -- gcc compiles
 * -fdata-sections globals in DECLARATION order into the .o's section table,
 * so a top-of-file const landed ahead of shiftMotionOrientEndFunc's own
 * embedded D_00619620..D_006196B8 content once the carve widened to include
 * it). jtbl_006196E0 is a standalone splat-migrated stub with no owning-
 * function INCLUDE_ASM wiring it in (shiftMotionOrientEndFunc references it
 * via %hi/%lo but never .includes it) -- wired via INCLUDE_RODATA, same
 * shape as enemy_act/Packet. */
const char D_006196C8[0x18] = "%s ‡ %s (%s)\n\0\0\0\0\0\0\0\0\0\0\0";
INCLUDE_RODATA("asm/nonmatchings/src/motionOrientManager", jtbl_006196E0);
const char D_00619738[0x58] = "¥Î¡¼¥É¤òº®¤¼¤ë¥â¡¼¥·¥ç¥ó(%s)¤¬¡¢\nºÆÅÙ¥Î¡¼¥É¤òº®¤¼¤ë¥â¡¼¥·¥ç¥ó¤òÍøÍÑ¤·¤Æ¤¤¤Þ¤¹¡£\n\0\0\0\0\0\0\0\0";
const char D_00619790[0x40] = "NODE BLEND MOTION \"%s\" REFERS\nNODE BLEND MOTION RECURSIVELY.\n\0\0\0";
const char D_006197D0[0x20] = "src/motionOrientManager.c\0\0\0\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionOrientBeginFunc);

extern char D_0061C710[];
extern char D_00612068[], D_006120C0[], D_00612100[], D_006334C0[];
extern void debug_StdPrintfDummy();
extern void func_001AD748(char *a0, int a1, char *a2);
extern void __assert(char *a0, int a1, char *a2);
extern void sprintf(char *buf, const char *fmt, ...);

float ForTest_ForceShiftMotion(int a0) {
    char buf[0x100];
    char *D = (char *)D_00565060;
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
            debug_StdPrintfDummy(D_00619738, p);
            sprintf(buf, D_00619790, p);
            func_001AD748(D_006197D0, 0x98, buf);
            __assert(D_006197D0, 0x98, D_006334C0);
        }
        r = D - (-(nidx * 0x190));
    }
    return *(float *)(r + 0x14C);
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", normalMotionShift);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", parallelMotionShift);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", sendStateMail);

const char D_00619800[0x48] = "²¿¤é¤«¤ÎÍýÍ³¤ÇSE¤ÎÆâÉô½èÍý¤¬¤ª¤«¤·¤¤¤è¤¦¤Ç¤¹¡£¿ù»³¤ËÊó¹ð¤·¤Æ¤¯¤À¤µ¤¤¡£\n\0";

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

const unsigned int D_00619928[0x4] = { 0x00633510, 0x00633518, 0x00633520, 0x00633528 };
const char D_00619938[0x28] = "%s %s at %s ignore %d times\0\0\0\0\0\0\0\0\0\0\0\0\0";
INCLUDE_RODATA("asm/nonmatchings/src/motionOrientManager", jtbl_00619960);
const char D_00619998[0x30] = "(%s)º®¤¼¤ë¥â¡¼¥·¥ç¥ó¤¬ÄêµÁ¤µ¤ì¤Æ¤¤¤Þ¤»¤ó¡£\n\0\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetNodeRotationLimitDataTable);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetMotionOrient);

const char D_00619A80[0x58] = "¥·¥§¥¤¥×¥â¡¼¥·¥ç¥ó¥Ç¡¼¥¿¤È¥¿¡¼¥²¥Ã¥È¤Î¿ô¤¬°ã¤¤¤Þ¤¹¡£\n¥â¡¼¥·¥ç¥ó:%d ¥¿¡¼¥²¥Ã¥È:%d\n\0\0\0\0\0\0\0";
const char D_00619AD8[0x38] = "¼õÅÏ¤·¥Ç¡¼¥¿¤ò³ÊÇ¼¤¹¤ë¾ì½ê¤¬³ÎÊÝ¤µ¤ì¤Æ¤¤¤Þ¤»¤ó¡£\n\0\0\0\0\0\0\0";
const unsigned int D_00619B10[0x4] = { 0x00000040, 0x00000020, 0x00000000, 0x00000080 };
const unsigned int D_00619B20[0x4] = { 0x000000FF, 0x00000080, 0x00000000, 0x00000080 };
const char D_00619B30[0x38] = "\033[36m¥â¡¼¥·¥ç¥óÃÖ¤­´¹¤¨µ¡Ç½¤¬Ää»ß¤·¤Æ¤¤¤Þ¤¹¡£\033[m: %p\n\0\0\0";
const char D_00619B68[0x48] = "¥Î¡¼¥É²óÅ¾¥ê¥ß¥Ã¥È¥Ç¡¼¥¿¤Î¼¨¤¹¥Î¡¼¥É¤¬¥¹¥±¥ë¥È¥óÃæ¤Ë¤¢¤ê¤Þ¤»¤ó¡£\n\0\0\0\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getMotionOrient);

extern char D_00275850[];
extern int GetPureVerticalPlane(void *a0, void *a1, void *a2, int a3);
extern void CopyMotion(void *dst, void *src, int n);
extern void _ScaleVectorXYZ(void *a0, void *a1, float a2);
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
            _ScaleVectorXYZ(local, local, f20);
            q = *(char **)((char *)a0 + 0x15C);
        }
        local[0] = local[0] - *(float *)(q + 0x670);
        local[1] = local[1] - *(float *)(q + 0x674);
        local[2] = local[2] + *(float *)(q + 0x678);
        func_001DFBC8(a0, buf, buf, local, D_00275850, -1, 1.0f);
        {
            char *r = *(char **)((char *)a0 + 0x15C);
            CopyMotion(*(void **)(r + 0x78C), buf, *(int *)(r + 0x88));
        }
        {
            char *s = *(char **)((char *)a0 + 0x15C);
            MatrixDrive_TurnObjectMatrix((void *)(s + 0x790), local);
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

extern Slip D_0029F038;

void *ExecutePauseSlipProc(int i, int limit, int a2, int a3)
{
    void *r;
    int found = -1;
    while (i < limit) {
        if (D_00292540[i].f_4 == a3) {
            if (D_00292540[i].f_0 == a2) {
                r = &D_00292540[i];
                goto done;
            }
            if (D_00292540[i].f_0 == 0x43D) {
                found = i;
            }
        }
        i++;
    }
    if (found != -1) {
        r = &D_00292540[found];
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

