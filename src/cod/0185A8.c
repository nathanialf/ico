#include "r5900.h"

void func_001185A8(void *dst, void *src)
{
    __asm__ __volatile__("lq $a2, 0($a1)" : : : "memory");
    __asm__ __volatile__("lq $a3, 0x10($a1)" : : : "memory");
    __asm__ __volatile__("lq $t0, 0x20($a1)" : : : "memory");
    __asm__ __volatile__("lq $t1, 0x30($a1)" : : : "memory");
    __asm__ __volatile__("sq $a2, 0($a0)" : : : "memory");
    __asm__ __volatile__("sq $a3, 0x10($a0)" : : : "memory");
    __asm__ __volatile__("sq $t0, 0x20($a0)" : : : "memory");
    __asm__ __volatile__("sq $t1, 0x30($a0)" : : : "memory");
    __asm__ __volatile__("nop");
}
