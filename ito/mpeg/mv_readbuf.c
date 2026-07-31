#include "common.h"





extern void func_0023FCB8();
extern void func_0019E150(int a0);
extern void func_001331D8();
extern void func_00132FF0();
extern void func_00265168();
extern int inflate_start();
int free_buffer(int a0, int a1)
{
    int rest = *(int *)(a0 + 0xC);
    if (a1 < rest) {
        rest = a1;
    }
    *(int *)(a0 + 0xC) -= rest;
    return rest;
}

int readBufDelete(int a0)
{
    func_00265168(a0 + 0x34);
    func_00132FF0(a0);
    return 1;
}

int readBufCreate(void) {
    func_001331D8();
    return 1;
}

int readBufBeginPut(void)
{
    return inflate_start();
}

void readBufEndPut(int a0)
{
    func_0019E150(*(int *)(a0 + 0x48));
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_readbuf", readBufBeginGet);

void readBufEndGet(int a0)
{
    func_0023FCB8(a0 + 0x50);
}

