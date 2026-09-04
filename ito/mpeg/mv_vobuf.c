#include "common.h"

#include "mv_defs.h"

#include "r5900.h"

void func_001A7180(a0, a1)
int *a0;
int a1;
{
    func_001A7318(a0[0]);
    func_001A7318(a0[1]);
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufCreate);
extern void func_001A7180();

void voBufDelete(void) {
    func_001A7180();
}
extern void iosFree();

void func_001A7318(int a0)
{
    iosFree(phys_addr(a0));
}
void voBufReset(volatile int *self)
{
    self[3] = 0;
    self[2] = 0;
}
int voBufIsFull(int *self) {
    return self[3] == self[4];
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufIncCount);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufGetData);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufGetTag);
void voBufDecCount(int *p) {
    if (*(volatile int *)(p + 3) > 0) {
        --(*(volatile int *)(p + 3));
    }
}
