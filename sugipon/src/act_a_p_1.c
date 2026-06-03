#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", standAI);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", walkAI);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", hehehe);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", SleepAP1);

int WakeUpAP1(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[0];
}

void subAP1BrainMain(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    *(int *)((char *)q + 0x278) = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", hitProc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", SetAP1DeadStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", AP1BeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", actAP1Start);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", IsActCharDead);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", SetAP1HostGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", SetAP1PriorLevel);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", GetAP1AIMode);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_004BA160;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004B9D50;  /* stride 0x4 */

/* end struct shapes */
