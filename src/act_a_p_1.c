#include "common.h"



extern void MoveNextStage_Clear();
extern int D_00623468[];
extern int D_004BEE60[];
INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", standAI);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", walkAI);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", hehehe);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", SleepAP1);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", WakeUpAP1);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", subAP1BrainMain);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", hitProc);

int SetAP1DeadStatus(int *self, int a1)
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

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", AP1BeforeFunc);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", actAP1Start);

void IsActCharDead(int *self)
{
  int *entry = (int *) (((char *) D_00623468) - (-(self[0x30 / 4] * 32)));
  MoveNextStage_Clear(0x3D, entry[0xC / 4], -1, 0, (int) self, -1, 7, 1);
  asm __volatile__("" : : : "memory");
}

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", SetAP1HostGObj);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", SetAP1PriorLevel);

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", GetAP1AIMode);

