/* Vendor SCE library member: libkernl.a(initsys.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x100990..0x100A08, 3 functions. */
#include "common.h"
#include "syscall.h"
#include "r5900.h"

void setup(int a0, int a1)
{
    __asm__ __volatile__("addiu $3, $zero, 116\n\tsyscall 0" : : : "$3", "memory");
}

extern void setup();

void InitSysCall(void)
{
    int i = 0x80;
    do {
        setup(i, 0);
        i++;
    } while (i < 0x100);
}

extern void InitAlarm(void);
extern void InitThread(void);

void _InitSys(void)
{
    InitSysCall();
    InitAlarm();
    InitThread();
}
