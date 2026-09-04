#include "common.h"





extern void viBufBeginPut();
extern void func_0019E150(int a0);
extern void func_001331D8();
extern void func_00132FF0();
extern void strcpy();
extern int iosCdvdDirectStRead();
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
    strcpy(a0 + 0x34);
    func_00132FF0(a0);
    return 1;
}

int readBufCreate(void) {
    func_001331D8();
    return 1;
}

int readBufBeginPut(void)
{
    return iosCdvdDirectStRead();
}

void free_buf(int a0)
{
    func_0019E150(*(int *)(a0 + 0x48));
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_readbuf", readBufBeginGet);

void readBufEndGet(int a0)
{
    viBufBeginPut(a0 + 0x50);
}

