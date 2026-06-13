#include "common.h"

/* AP1 0x7F0 view (local) */
typedef struct { int f_0; char _pad4[4]; int f_8; char _pad_c[0x1B4]; int f_1C0; int f_1C4; int f_1C8; char _pad1cc[0xAC]; int f_278; } AP1Geo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", standAI);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", walkAI);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", hehehe);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", SleepAP1);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", actAP1Start);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", IsActCharDead);

extern int D_004B9D50[];
int SetAP1HostGObj(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    AP1Geo *q = *(AP1Geo **)((char *)p + 0x7F0);
    return D_004B9D50[q->f_8];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/act_a_p_1", SetAP1PriorLevel);

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
