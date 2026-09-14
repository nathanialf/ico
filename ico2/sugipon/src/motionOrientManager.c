#include "common.h"
#include "ico/types.h"

extern void shiftMotionData(int a0, int a1, int a2, int a3);

typedef struct {
    int id;
    int kind;
    int pad[4];
} MotionOrientEntry;

extern MotionOrientEntry D_002ADD60[];
extern MotionOrientEntry D_002BC4A8;
extern void CopyMotion(void *dst, void *src, int n);
extern void CopyVector(void *dst, void *src);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void SetQuaternionByAxisRotate(void *dst, int ang, float x, float y, float z);

struct MotOriHead8 {
    long long v;
} __attribute__((packed));

struct MotOriFloat {
    float f;
};

#define MOWORK(self) (*(char **)((char *)(self) + 0x15C))

extern int parallelMotionShift(void *self);
extern void SetNodeRotationLimitDataTable(void *self, int a1, int a2);
extern int soundSeGroupGet(void);

typedef struct MotOriTrigEnt {
    /* 0x000 */ char pad000[0xC0];
    /* 0x0C0 */ char name[0x70];
    /* 0x130 */ int f130;
    /* 0x134 */ char pad134[0x10];
    /* 0x144 */ int f144;
    /* 0x148 */ int f148;
    /* 0x14C */ int f14C;
    /* 0x150 */ char pad150[0x24];
    /* 0x174 */ float f174;
    /* 0x178 */ int f178;
    /* 0x17C */ char pad17C[0x18];
} MotOriTrigEnt;

extern MotOriTrigEnt D_0055FE58[];
extern int D_0028F4D4[];
extern void StopSEPackageWithGroupVariation(void *a0, int a1);
/* prototypes: their order is the inline tail's emission order */
MotionOrientEntry *GetMotionOrient(int i, int n, int id, int kind);
MotionOrientEntry *getMotionOrient(int i, int n, int id, int kind);
void CopyBlendMotionDataSource(void *self, short ang);
void SetParallelMotionTableWithNoRequest(void *self, int a1, int a2);
void SetParallelMotionTable(void *self, int a1, int a2, int a3, int a4);
void InitMotionOrient(void *self, int a1, int a2, int a3, int a4, int a5);
unsigned int GetCurrentMotionDirectionAdjustFlag(char *a0);
int ExecuteSlipProc(char *a0);
int ExecutePauseSlipProc(char *a0);

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", orientDebug);

extern char D_00620238[];
extern char D_00620290[];
extern char D_006202D0[];
extern char D_0063B988[];

typedef struct MotOriSub {
    /* 0x0 */ int f0;
    /* 0x4 */ int f4;
    /* 0x8 */ int f8;
    /* 0xC */ int fC;
} MotOriSub;

extern MotOriSub D_00623470[];
extern int sprintf(char *buf, char *fmt, ...);
extern void debug_assertMessage(char *file, int line, char *mes);

static inline void checkMotionKind(int i, int j)
{
    if (D_0055FE58[i].f178 != 0x140) {
        char buf[0x100];

        debug_StdPrintfDummy(D_00620238, D_0055FE58[j].name);
        sprintf(buf, D_00620290, D_0055FE58[j].name);
        debug_assertMessage(D_006202D0, 152, buf);
        __assert(D_006202D0, 152, D_0063B988);
    }
}

extern int *D_004EB758[];

int GetNbMotionFrames(int id)
{
    int m;
    int n;

    if (D_0055FE58[id].f178 == 0x140) {
        return *D_004EB758[id];
    }
    m = D_00623470[D_0055FE58[id].f178].f0;
    n = D_00623470[D_0055FE58[id].f178].fC;
    checkMotionKind(m, id);
    if (n != -1) {
        return n;
    }
    return *D_004EB758[m];
}

float GetMotionPlaySpeedRatio(int id)
{
    int m;

    if (D_0055FE58[id].f178 == 0x140) {
        return D_0055FE58[id].f174;
    }
    m = D_00623470[D_0055FE58[id].f178].f0;
    checkMotionKind(m, id);
    return D_0055FE58[m].f174;
}

void execFrameTrigger(void *self)
{
    char *w = MOWORK(self) + 0x470;
    float t;

    t = (float)D_0055FE58[*(int *)(w + 0x30)].f144;
    if (0.0f <= t) {
        if (*(int *)(w + 0x19C) == 0) {
            if (t < *(float *)(w + 0x3C)) {
                *(int *)(w + 0x198) = 1;
                *(int *)(w + 0x19C) = 1;
            } else {
                *(int *)(w + 0x198) = 0;
            }
        } else {
            *(int *)(w + 0x198) = 0;
        }
    }
    t = (float)D_0055FE58[*(int *)(w + 0x30)].f14C;
    if (0.0f <= t) {
        if (*(int *)(w + 0x1A4) != 0) {
            *(int *)(w + 0x1A0) = 0;
        } else if (t < *(float *)(w + 0x3C)) {
            *(int *)(w + 0x1A0) = 1;
            *(int *)(w + 0x1A4) = 1;
        } else {
            *(int *)(w + 0x1A0) = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", UpdateFrameCounter);

inline MotionOrientEntry *GetMotionOrient(int i, int n, int id, int kind)
{
    int found = -1;

    for (; i < n; i++) {
        if (D_002ADD60[i].kind == kind) {
            if (D_002ADD60[i].id == id) {
                return &D_002ADD60[i];
            }
            if (D_002ADD60[i].id == 0x47A) {
                found = i;
            }
        }
    }
    if (found != -1) {
        return &D_002ADD60[found];
    }
    return 0;
}

inline MotionOrientEntry *getMotionOrient(int i, int n, int id, int kind)
{
    MotionOrientEntry *p = GetMotionOrient(i, n, id, kind);

    if (p == 0) {
        p = &D_002BC4A8;
    }
    return p;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", sendStateMail);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", shiftMotionData);

extern char D_00620300[];
extern char D_0063B9B8[];
extern void debug_assert(char *file, int line);
extern void FeedbackWallWorkInfoToBrainSystem(void *self);

void shiftMotionOrientEndFunc(void *self)
{
    char *w = MOWORK(self) + 0x470;
    int x;

    if (*(int *)(w + 0x1AC) == -1) {
        debug_StdPrintfDummy(D_00620300);
        debug_assert(D_006202D0, 745);
        __assert(D_006202D0, 745, D_0063B9B8);
    }
    StopSEPackageWithGroupVariation(self, 0);
    StopSEPackageWithGroupVariation(self, 1);
    *(int *)(w + 0x1B8) = 0;
    x = *(int *)(w + 0x68);
    if (x < 9) {
        if (x >= 7) {
            goto ok;
        }
        return;
    }
    if (x != 16) {
        return;
    }
ok:
    if (D_0055FE58[*(int *)(w + 0x30)].f130 == 0) {
        return;
    }
    FeedbackWallWorkInfoToBrainSystem(self);
}

inline void CopyBlendMotionDataSource(void *self, short ang)
{
    char quat[0x10];
    char *mot = *(char **)(MOWORK(self) + 0x7D0);
    int i = 0;

    CopyMotion(mot, *(char **)(MOWORK(self) + 0x7B4), *(int *)(MOWORK(self) + 0x88));
    CopyVector(MOWORK(self) + 0x7E0, MOWORK(self) + 0x7C0);
    CopyVector(MOWORK(self) + 0x7F0, MOWORK(self) + 0x130);
    *(struct MotOriFloat *)(MOWORK(self) + 0x808) = *(struct MotOriFloat *)(MOWORK(self) + 0x160);
    *(struct MotOriHead8 *)(MOWORK(self) + 0x800) = *(struct MotOriHead8 *)MOWORK(self);
    while (*(int *)(*(char **)(MOWORK(self) + 0x8C) + i * 0x40 + 0x38) == -1) {
        SetQuaternionByAxisRotate(quat, ang, 0.0f, 1.0f, 0.0f);
        MultiQuaternion(mot + i * 0x20 + 0x10, quat, mot + i * 0x20 + 0x10);
        i = *(int *)(*(char **)(MOWORK(self) + 0x8C) + i * 0x40 + 0x34);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", shiftMotionOrientBeginFunc);

void ForTest_ForceShiftMotion(int a0, int a1)
{
    shiftMotionData(a0, a1, a1, 0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", normalMotionShift);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", parallelMotionShift);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", SetMotionRequest);

inline void SetParallelMotionTableWithNoRequest(void *self, int a1, int a2)
{
    char *m = (char *)*(int *)((char *)self + 0x15C) + 0x470;

    if (*(int *)(m + 0x18) == 0) {
        *(int *)(m + 0x1C) = a2;
        *(int *)(m + 0x20) = a1;
    }
}

inline void SetParallelMotionTable(void *self, int a1, int a2, int a3, int a4)
{
    char *m = (char *)*(int *)((char *)self + 0x15C) + 0x470;
    int old = *(int *)(m + 0xD0);

    *(int *)(m + 0xD0) = 0x10D;
    SetParallelMotionTableWithNoRequest(self, a1, a2);
    *(int *)(m + 0x24) = a3;
    *(int *)(m + 0x28) = a4;
    if (parallelMotionShift(self) != 0) {
        *(int *)(m + 0x44) = 0;
    } else {
        *(int *)(m + 0xD0) = old;
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getNodeBlendedFloatingMotion);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getMotionGeometry);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getShapeGeometry);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getStreamMotionGeometry);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getStreamBlendMotionGeometry);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getStreamBlendShapeGeometry);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getStreamShapeGeometry);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", getStreamMotion);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", ExecMotionOrient);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionOrientManager", SetNodeRotationLimitDataTable);

inline void InitMotionOrient(void *self, int a1, int a2, int a3, int a4, int a5)
{
    char *m = *(char **)((char *)self + 0x15C) + 0x470;

    if (a3 >= 0 && a4 >= 0) {
        SetNodeRotationLimitDataTable(self, a3, a4);
    }
    *(int *)(m + 0x4) = a1;
    *(int *)(m + 0x8) = a2;
    shiftMotionData((int)self, a5, a5, 0);
    *(int *)(m + 0x1AC) = soundSeGroupGet();
    *(int *)(m + 0x1B0) = soundSeGroupGet();
}

inline unsigned int GetCurrentMotionDirectionAdjustFlag(char *a0)
{
    char *rec = (char *)D_0055FE58 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 0x194;
    return *(unsigned int *)(rec + 0x188) >> 30;
}

inline int ExecuteSlipProc(char *a0)
{
    char *e = *(char **)(a0 + 0x15C);
    if (*(int *)(e + 0x628) != *(int *)(e + 0x624)) {
        StopSEPackageWithGroupVariation(a0, 1);
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x624) & 0x100000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x72, 1);
        }
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x624) & 0x200000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x74, 1);
        }
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x624) & 0x400000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x76, 1);
        }
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x624) & 0x800000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x78, 1);
        }
    }
    return 1;
}

inline int ExecutePauseSlipProc(char *a0)
{
    if (D_0028F4D4[0] != 0) {
        *(int *)(*(char **)(a0 + 0x15C) + 0x628) = 0;
        StopSEPackageWithGroupVariation(a0, 1);
    }
    return 1;
}
