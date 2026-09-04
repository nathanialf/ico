#include "common.h"






extern void func_00240218();
extern void func_00240090();
extern void viBufAddDMA();
extern void GetStageDifferenceMatrix();
extern void voBufIncCount();
extern void func_0019DF38();
extern void func_0023FB20();
extern int func_00240A20(int *self);
extern int sceMpegIsRefBuffEmpty(char *self);
int videoDecGetState(int a0)
{
    return *(int *)(a0 + 0xB8);
}

int videoDecIsFlushed(int *self)
{
    int ret = 0;
    if (func_00240A20((int)((char *)self + 0x50)) == 0) {
        ret = sceMpegIsRefBuffEmpty(self) != 0;
    }
    return ret;
}

void videoDecMain(int *self)
{
    func_0023FB20(self[0] + 0x50);
    voBufIncCount(self[2]);
    func_0019DF38(self[0], self[1], self[2]);
    *(int *)(self[0] + 0xB8) = 3;
}

extern void debug_StdPrintfDummy(const char *fmt, int arg);
extern const char D_00632820[];

int mpegError(int a0, int *self)
{
    debug_StdPrintfDummy(D_00632820, self[1]);
    return 1;
}

int mpegNodata(int a0, int a1, int a2)
{
    GetStageDifferenceMatrix(a0, a1);
    viBufAddDMA(a2 + 0x50);
    return 1;
}

int videoCallback(int a0_unused, int a1_unused, char *p) {
    func_00240090((int)(p + 0x50));
    return 1;
}

int decBitStrm0(int a0_unused, int a1_unused, char *p) {
    func_00240218((int)(p + 0x50));
    return 1;
}

