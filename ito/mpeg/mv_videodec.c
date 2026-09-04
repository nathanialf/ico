#include "common.h"

#include "mv_defs.h"

#include "r5900.h"

extern void Free(int a0);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_videodec", free_buf);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_videodec", videoDecCreate);
extern void viBufBeginPut();

void videoDecBeginPut(int a0)
{
    viBufBeginPut(a0 + 0x50);
}
extern void viBufEndPut();

void videoDecEndPut(int a0)
{
    viBufEndPut(a0 + 0x50);
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_videodec", videoDecFlush);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_videodec", videoCallback);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_videodec", decBitStrm0);
extern void iosFree();

void Free(int a0)
{
    iosFree(phys_addr(a0));
}
extern int sceMpegDelete();
extern void viBufDelete();

int videoDecDelete(int a0)
{
    viBufDelete(a0 + 0x50);
    sceMpegDelete(a0);
    free_buf(a0);
    return 1;
}
extern void sceMpegAddStrCallback();

int videoDecSetStream(void) {
    sceMpegAddStrCallback();
    return 1;
}
void videoDecAbort(int a0)
{
    *(int *)(a0 + 0xB8) = 1;
}
int videoDecGetState(int a0)
{
    return *(int *)(a0 + 0xB8);
}
extern int sceMpegIsRefBuffEmpty(char *self);
extern int viBufCount(int *self);

int videoDecIsFlushed(int *self)
{
    int ret = 0;
    if (viBufCount((int)((char *)self + 0x50)) == 0) {
        ret = sceMpegIsRefBuffEmpty(self) != 0;
    }
    return ret;
}
extern void decBitStrm0();
extern void viBufReset();
extern void voBufReset();

void videoDecMain(int *self)
{
    viBufReset(self[0] + 0x50);
    voBufReset(self[2]);
    decBitStrm0(self[0], self[1], self[2]);
    *(int *)(self[0] + 0xB8) = 3;
}
extern const char D_0063AC88[];
extern void debug_StdPrintfDummy(const char *fmt, int arg);

int mpegError(int a0, int *self)
{
    debug_StdPrintfDummy(D_0063AC88, self[1]);
    return 1;
}
extern void switchThread();
extern void viBufAddDMA();

int mpegNodata(int a0, int a1, int a2)
{
    switchThread(a0, a1);
    viBufAddDMA(a2 + 0x50);
    return 1;
}
extern void viBufStopDMA();

int mpegStopDMA(int a0_unused, int a1_unused, char *p) {
    viBufStopDMA((int)(p + 0x50));
    return 1;
}
extern void viBufRestartDMA();

int mpegRestartDMA(int a0_unused, int a1_unused, char *p) {
    viBufRestartDMA((int)(p + 0x50));
    return 1;
}
extern void viBufGetTs();

int mpegTS(int a0_unused, int *a1, char *a2) {
    long long buf[4];
    viBufGetTs((int *)(a2 + 0x50), (int *)buf);
    *(long long *)((char *)a1 + 0x8) = buf[0];
    *(long long *)((char *)a1 + 0x10) = buf[1];
    return 1;
}
