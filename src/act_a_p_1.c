#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", standAI);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", walkAI);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", hehehe);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", SleepAP1);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", WakeUpAP1);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", func_001C4DC0);
extern int AP1MotReqForce(int *self, int a1);

void func_001C5250(int a0)
{
    AP1MotReqForce(a0, 5);
}
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", SetAP1DeadStatus);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", AP1BeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", actAP1Start);
int IsActCharDead(int *a0)
{
    int *v1 = (int *)a0[0x164 / 4];
    long x = *(unsigned int *)((char *)v1 + 0x1C);
    return (((int)x) & 1) ^ 1;
}
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", SetAP1HostGObj);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", SetAP1PriorLevel);
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", GetAP1AIMode);
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
