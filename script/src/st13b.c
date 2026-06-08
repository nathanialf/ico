#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bFloor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bFloorChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bConte02);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bSekizo2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bMeetAgain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bBoss);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actConte10b);

void actSt13bElevDown(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bElevUp);

extern int *D_00629DE4;
extern int D_0062C2AC;
extern void gflagOff(int *p, int n);
extern void actSt25aQueenBefore(int *p);
extern void _ACTWait(int x);

void actSt13bElevUpChk(volatile int unused)
{
    gflagOff(D_00629DE4, 0x1D0);
    actSt25aQueenBefore(D_00629DE4);
    gflagOff(D_00629DE4, 0x1D1);
    actSt25aQueenBefore(D_00629DE4);
    D_0062C2AC = 1;
    _ACTWait(0);

}

extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);
extern int D_00629DE8;
extern long long D_00614AA0[];

void actSt13bSekizo(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_00614AA0[0];
    buf[1] = D_00614AA0[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

extern long long D_00614AB0[];

void actSt13bSekizo2(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_00614AB0[0];
    buf[1] = D_00614AB0[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt13bBossAfter(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bStoneGirl);

extern long long D_00614AC0[];

void actSt13bExit(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_00614AC0[0];
    buf[1] = D_00614AC0[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt13bElev(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bDoor);

void actBossTest(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bConte02Jimaku);

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSt13bSekizo2Event(void) {
    if (D_00629DE8 == 0) return;
    if (func_00178DB0(0x45) != 0) return;
    func_00178DD8(0x165);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b", actSt13bMeetAgainChk);
