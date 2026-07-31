#include "common.h"

typedef struct { int f_0; char _pad4[4]; int f_8; char _pad_c[0x1B4]; int f_1C0; int f_1C4; int f_1C8; char _pad1cc[0xAC]; int f_278; } AP1Geo;



extern void MoveNextStage_Clear();
extern int D_00623468[];
extern int D_004BEE60[];
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", standAI);

extern void FlagGeo();
extern void GetRootMatrixByDObj();
extern void func_00102850();

void walkAI(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x800);
    GetRootMatrixByDObj(p + 0x1E0, a0);
    func_00102850(p + 0x1D0, a0);
    FlagGeo(*(int *)(p + 0x19C));
}

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", hehehe);

extern void InitFlagGeo();
extern void file_LoadCDFile();
extern void func_0010ECB8();
extern void func_0010ECD8();

void SleepAP1(char *a0) {
    char *sub = *(char **)(*(char **)(a0 + 0x15C) + 0x800);
    if (*(int *)(sub + 0x8) < 5) {
        if (*(int *)(sub + 0x278) != 0) {
            func_0010ECD8();
            func_0010ECB8(a0);
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
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x800);
    return q->f_0;
}

void subAP1BrainMain(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x800);
    q->f_278 = a1;
}

extern void GetSlerpQuaternionNoRegularize(void *a0);
extern void func_00102870(int self, int src);
extern void func_0010E158(int *self, short y);
extern void standAI();

int hitProc(void *a0, int a1) {
    float buf[4];
    int s = (short)a1;
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x800);
    if (q->f_8 < 6) {
        if (q->f_8 >= 2) {
            goto ret0;
        }
    }
    func_00102850(buf, a0);
    func_0010E158(buf, s);
    GetSlerpQuaternionNoRegularize(buf);
    func_00102870(a0, buf);
    standAI(a0);
    return 1;
ret0:
    return 0;
}

int SetAP1DeadStatus(self, a1)
int *self;
int a1;
{
    void (*fn)(int *);
    int *p;
    fn = (void (*)(int *))D_004BEE60[a1 * 2];
    p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    p[0x8 / 4] = a1;
    if (fn != 0) {
        fn(self);
    }
    return 1;
}


int AP1BeforeFunc(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x800);
    if (q->f_8 < 6) {
        if (q->f_8 >= 2) {
            return 0;
        }
    }
    SetAP1DeadStatus();
    return 1;
}

extern void func_00118648(int a, int b, int c);

int actAP1Start(void *a0, int a1, void *a2) {
    int flag;
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x800);
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
        AP1Geo *qq = *(AP1Geo **)((char *)pp + 0x800);
        func_00118648((char *)pp + 0x130, (char *)qq + 0x230, a2);
        return 1;
    }
    return 0;
}

void IsActCharDead(int *self)
{
  int *entry = (int *) (((char *) D_00623468) - (-(self[0x30 / 4] * 32)));
  MoveNextStage_Clear(0x3D, entry[0xC / 4], -1, 0, (int) self, -1, 7, 1);
  asm __volatile__("" : : : "memory");
}

extern int D_004BEA50[];

int SetAP1HostGObj(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x800);
    return D_004BEA50[q->f_8];
}

extern int walkMot();

int SetAP1PriorLevel(void *a0)
{
    int *p = *(int **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x800);
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
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x800);
    int ret = calcSubMission(a0);
    if (ret != -1) {
        return ret;
    }
    q->f_1C0 = 0;
    q->f_1C4 = 0;
    q->f_1C8 = 0;
    return 2;
}

