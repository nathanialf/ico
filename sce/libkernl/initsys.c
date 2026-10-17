/* libkernl.a(initsys.o) */
#include <libkernl_internal.h>
#include "include_asm.h"

void setup(int num, int handler);

INCLUDE_ASM(setup_initsys);

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
