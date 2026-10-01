/* libkernl.a(deci2.o) */
#include <libkernl_internal.h>

/* the work area sceDeci2Open hands the kernel, through its uncached alias.
   Each call hands the kernel a block of four argument words, addresses
   included. */
static char deci2Buffer[36]; /* derived name */

int sceDeci2Open(unsigned short protocol, void *opt, void *handler)
{
    int args[4];
    args[0] = protocol;
    args[1] = (int)opt;
    args[2] = (int)handler;
    args[3] = (int)deci2Buffer | 0x20000000;
    return Deci2Call(1, args);
}

void sceDeci2Close(int s)
{
    int args[4];
    args[0] = s;
    Deci2Call(2, args);
}

int sceDeci2ReqSend(int s, signed char a1)
{
    int args[4];
    args[0] = s;
    args[1] = a1;
    return Deci2Call(3, args);
}

void sceDeci2Poll(int s)
{
    int args[4];
    args[0] = s;
    Deci2Call(4, args);
}

int sceDeci2ExRecv(int s, void *buf, unsigned short len)
{
    int args[4];
    args[0] = s;
    args[1] = (int)buf;
    args[2] = len;
    return Deci2Call(-5, args);
}

int sceDeci2ExSend(int s, void *buf, unsigned short len)
{
    int args[4];
    args[0] = s;
    args[1] = (int)buf;
    args[2] = len;
    return Deci2Call(-6, args);
}

void sceDeci2ExReqSend(int s, signed char a1)
{
    int args[4];
    args[0] = s;
    args[1] = a1;
    Deci2Call(-7, args);
}

void sceDeci2ExLock(int s)
{
    int args[4];
    args[0] = s;
    Deci2Call(-8, args);
}

void sceDeci2ExUnLock(int s)
{
    int args[4];
    args[0] = s;
    Deci2Call(-9, args);
}

void kputs(char *s)
{
    int args[4];
    args[0] = (int)s;
    Deci2Call(0x10, args);
}
