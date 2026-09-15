/* Vendor SCE library member: libkernl.a(deci2.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x101AA0..0x101C80, 10 functions. */
#include "common.h"
#include "syscall.h"
#include "r5900.h"

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/deci2", sceDeci2Open);

extern void Deci2Call(int req, void *args);

void sceDeci2Close(int a0)
{
    int args[4];
    args[0] = a0;
    Deci2Call(2, args);
}

void sceDeci2ReqSend(int a0, signed char a1)
{
    int args[4];
    args[0] = a0;
    args[1] = a1;
    Deci2Call(3, args);
}

void sceDeci2Poll(int a0)
{
    int args[4];
    args[0] = a0;
    Deci2Call(4, args);
}

void sceDeci2ExRecv(int a0, int a1, unsigned short a2)
{
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    Deci2Call(-5, args);
}

void sceDeci2ExSend(int a0, int a1, unsigned short a2)
{
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    Deci2Call(-6, args);
}

void sceDeci2ExReqSend(int a0, signed char a1)
{
    int args[4];
    args[0] = a0;
    args[1] = a1;
    Deci2Call(-7, args);
}

void sceDeci2ExLock(int a0)
{
    int args[4];
    args[0] = a0;
    Deci2Call(-8, args);
}

void sceDeci2ExUnLock(int a0)
{
    int args[4];
    args[0] = a0;
    Deci2Call(-9, args);
}

void kputs(int a0)
{
    int args[4];
    args[0] = a0;
    Deci2Call(0x10, args);
}
