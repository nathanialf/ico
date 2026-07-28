#include "common.h"



extern void _ACTWait();
extern void actInitialize();
extern int actSt25aQueenDeadChk();
extern int func_0017B230(int a0);
extern void *D_00631AE8;
extern void func_0017B258(int bit_idx);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1);

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1UpChk);

void actSt04dDoor1DownChk(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2);

void actSt04dDoor2UpChk(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x92) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2DownChk);

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1Event);

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1UpEffect);

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1DownEffect);

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2Event);

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2UpEffect);

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2DownEffect);

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_00219358);

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_002193E8);

void func_00219478(volatile unsigned int a0)
{
  volatile int local;
  unsigned int unused = a0;
  (void) unused;
  {
    register unsigned int _v asm("$4");
    asm volatile("lw %0, %1" : "=r"(_v) : "m"(a0));
    asm volatile("nop");
    actInitialize(_v);
  }
  _ACTWait(1);
  if (func_0017B230(0xCD) != 0)
  {
    *((int *) (((char *) actSt25aQueenDeadChk(0x3EE)) + 0x16C)) = 0;
  }
}

void func_002194C8(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_002194D8);

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_002195F0);

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_00219660);

void func_00219728(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_00219738);

