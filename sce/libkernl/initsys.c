/* libkernl.a(initsys.o) */
#include <libkernl_internal.h>

void setup(int num, int handler)
{
    __asm__ __volatile__("addiu $3, $0, 116\n\tsyscall 0" : : : "$3", "memory");
}

void InitSysCall(void)
{
    int i = 0x80;
    do {
        setup(i, 0);
        i++;
    } while (i < 0x100);
}

void _InitSys(void)
{
    InitSysCall();
    InitAlarm();
    InitThread();
}
