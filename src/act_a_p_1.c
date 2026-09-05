#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", standAI);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", walkAI);
extern char *D_004E5A78[];
extern void debug_StdPrintfDummy(char *a0);
void hehehe(char *a0) {
    debug_StdPrintfDummy(D_004E5A78[*(int *)(*(char **)(a0 + 0x164) + 0x34)]);
}
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", SleepAP1);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", WakeUpAP1);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", subAP1BrainMain);
extern int AP1MotReqForce(int *self, int a1);

void hitProc(int a0)
{
    AP1MotReqForce(a0, 5);
}
void SetAP1DeadStatus(int *a0) {
    typedef union { int i; long long ll; } U;
    int s = ((U *)((char *)a0 + 0x164))->i;
    *(int *)(s + 0x34) = 4;
    ((U *)(s + 0x18))->ll &= ~(1LL << 32);
    *(char *)(((U *)((char *)a0 + 0x164))->i + 0x1DA) = 1;
    AP1MotReqForce((int)a0, 5);
}
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", AP1BeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", actAP1Start);
int IsActCharDead(int *a0)
{
    int *v1 = (int *)a0[0x164 / 4];
    long x = *(unsigned int *)((char *)v1 + 0x1C);
    return (((int)x) & 1) ^ 1;
}
void SetAP1HostGObj(char *self, int val)
{
    *(int *)(*(char **)(self + 0x164) + 0xA8) = val;
}
void SetAP1PriorLevel(char *self, int val)
{
    *(int *)(*(char **)(self + 0x164) + 0xAC) = val;
}
extern char *D_004E5A30[];
extern char D_0063B6F8[];

char *GetAP1AIMode(char *self)
{
    char *p = *(char **)(self + 0x164);

    if (p == 0 || *(unsigned int *)(p + 0x34) >= 6) {
        return D_0063B6F8;
    }
    return D_004E5A30[*(int *)(p + 0x34)];
}
extern int AP1MotReq();

int jumpAI(int a0)
{
    return AP1MotReq(a0, 0) ? 0 : -1;
}
int attackAI(int a0)
{
    return AP1MotReq(a0, 0) ? 0 : -1;
}
void subAP1Control(int x) {
    volatile int local = x;
}
