#include "common.h"

/* AP1 0x7F0 view (local) */
typedef struct { int f_0; char _pad4[4]; int f_8; char _pad_c[0x1B4]; int f_1C0; int f_1C4; int f_1C8; char _pad1cc[0xAC]; int f_278; } AP1Geo;

typedef struct { int (*fp)(); int _4; } DeadProc;
extern DeadProc D_004BA160[];

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", standAI);

extern void GetRootMatrixByDObj();
extern void func_00102820();
extern void FlagGeo();

void walkAI(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    GetRootMatrixByDObj(p + 0x1E0, a0);
    func_00102820(p + 0x1D0, a0);
    FlagGeo(*(int *)(p + 0x19C));
}

extern void standAI(char *a0);
extern void updateMatrix(char *a0);
extern void *func_00105078(void);
extern void _MulMatrix(void *a0, void *a1, void *a2);
extern void func_001CCBC0(void *a0, void *a1, float a2);
extern void CopyMatrix(void *dst, void *src);
extern void MatrixDrive_RotMatrixZ(int a0);
extern void MatrixDrive_RotMatrixX(int a0);
extern void debug_StdPrintfDummy(char *msg);
extern char D_004BA1A0[];
extern char D_004BA220[];
extern char D_00610EA0[];
extern float D_00629424;
extern float D_00629428;

void hehehe(char *self)
{
    char *geo = *(char **)(*(char **)(self + 0x15C) + 0x7F0);
    int st = *(int *)(geo + 0x8);
    int (*fp)(char *);
    char *p;
    float diff;

    switch (st) {
    default:
        if (*(int *)(geo + 0x274) < 0xA) {
            *(int *)(geo + 0x274) = *(int *)(geo + 0x274) + 1;
            walkAI(self);
            st = *(int *)(geo + 0x8);
        }
        fp = (int (*)(char *))D_004BA160[st]._4;
        *(int *)(geo + 0x8) = fp(self);
        {
            char *g2 = *(char **)((char *)*(int *)(self + 0x15C) + 0x7F0);
            int c = *(int *)(g2 + 0x270) + 1;
            *(int *)(g2 + 0x270) = c;
            if (c >= 0x21)
                *(int *)(g2 + 0x270) = 0;
        }
        break;
    case 5:
        *(int *)(geo + 0x8) = 4;
        break;
    case 4:
        *(int *)(geo + 0x8) = 6;
        break;
    case 7:
        break;
    case 6:
        *(int *)(self + 0x16C) = 0;
        break;
    }

    standAI(self);
    updateMatrix(self);
    _MulMatrix(func_00105078(), *(char **)(*(char **)(self + 0x15C) + 0xC), D_004BA1A0);
    func_001CCBC0(*(char **)(geo + 0x19C), func_00105078(), 1.0f);
    if (*(int *)(geo + 0x4) != 0) {
        CopyMatrix(func_00105078(), *(char **)(*(char **)(self + 0x15C) + 0xC));
        MatrixDrive_RotMatrixZ(0x4000);
        MatrixDrive_RotMatrixX(0x4000);
        _MulMatrix(*(char **)(*(char **)(self + 0x15C) + 0xC), func_00105078(), D_004BA220);
    }
    p = *(char **)(self + 0x15C);
    diff = *(float *)(p + 0x54) - *(float *)(*(char **)(p + 0xC) + 0x34);
    if (diff < 0.0f) {
        if (*(volatile float *)&D_00629424 < -diff)
            goto bad;
    } else {
        if (*(volatile float *)&D_00629428 < diff)
            goto bad;
    }
    return;
bad:
    *(int *)(p + 0x5E8) = 0x800;
    debug_StdPrintfDummy(D_00610EA0);
}

extern void func_0010F068();
extern void func_0010F048();
extern void file_LoadCDFile();
extern void InitFlagGeo();

void SleepAP1(char *a0) {
    char *sub = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    if (*(int *)(sub + 0x8) < 5) {
        if (*(int *)(sub + 0x278) != 0) {
            func_0010F068();
            func_0010F048(a0);
            if (*(int *)(sub + 0x4) == 0) {
                file_LoadCDFile(*(int *)(sub + 0x194));
                file_LoadCDFile(*(int *)(sub + 0x198));
            }
            InitFlagGeo(*(int *)(sub + 0x19C));
        }
    }
}

int WakeUpAP1(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    return q->f_0;
}

void subAP1BrainMain(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    q->f_278 = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", hitProc);

int SetAP1DeadStatus(a0, a1)
void *a0;
int a1;
{
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    int (*fp)() = D_004BA160[a1].fp;
    q->f_8 = a1;
    if (fp) {
        fp(a0);
    }
    return 1;
}

int AP1BeforeFunc(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    if (q->f_8 < 6) {
        if (q->f_8 >= 2) {
            return 0;
        }
    }
    SetAP1DeadStatus();
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", actAP1Start);

typedef struct { char _pad[0xC]; int f; char _pad2[0x10]; } S;
extern S D_0061D730[];
extern int MoveNextStage_Clear(int a0, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);

int IsActCharDead(void *a0) {
    return MoveNextStage_Clear(0x3C, D_0061D730[*(int *)((char *)a0 + 0x30)].f,
        -1, 0, a0, -1, 7, 1);
}

extern int D_004B9D50[];
int SetAP1HostGObj(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    return D_004B9D50[q->f_8];
}

extern int walkMot();

int SetAP1PriorLevel(void *a0)
{
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    int ret = walkMot(a0, 0);
    if (ret != -1) {
        return ret;
    }
    q->f_1C0 = 0;
    q->f_1C4 = 0;
    q->f_1C8 = 0;
    return 0;
}

extern int calcSubMission(void *a0);

int GetAP1AIMode(void *a0)
{
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    int ret = calcSubMission(a0);
    if (ret != -1) {
        return ret;
    }
    q->f_1C0 = 0;
    q->f_1C4 = 0;
    q->f_1C8 = 0;
    return 2;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_004BA160;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004B9D50;  /* stride 0x4 */

/* end struct shapes */
