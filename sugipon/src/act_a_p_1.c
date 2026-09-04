#include "common.h"

/* AP1 0x7F0 view (local) */
typedef struct { int f_0; char _pad4[4]; int f_8; char _pad_c[0x1B4]; int f_1C0; int f_1C4; int f_1C8; char _pad1cc[0xAC]; int f_278; } AP1Geo;

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", hehehe);

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

int hitProc(void *a0, int a1) {
    float buf[4];
    int s = (short)a1;
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    if (q->f_8 < 6) {
        if (q->f_8 >= 2) {
            goto ret0;
        }
    }
    func_00102820(buf, a0);
    func_0010E4E8(buf, s);
    GetSlerpQuaternionNoRegularize(buf);
    func_00102840(a0, buf);
    standAI(a0);
    return 1;
ret0:
    return 0;
}


typedef struct { int (*fp)(); int _4; } DeadProc;
extern DeadProc D_004BA160[];

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

int actAP1Start(void *a0, int a1, void *a2) {
    int flag;
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    if (q->f_8 < 6) {
        if (q->f_8 >= 2) {
            flag = 0;
            goto check;
        }
    }
    SetAP1DeadStatus(a0);
    flag = 1;
check:
    if (flag != 0) {
        int *pp = *(int **)((char *)a0 + 0x15C);
        AP1Geo *qq = *(AP1Geo **)((char *)pp + 0x7F0);
        _ApplyMatrix((char *)pp + 0x120, (char *)qq + 0x230, a2);
        return 1;
    }
    return 0;
}


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
