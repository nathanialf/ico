#include "r5900.h"

void func_00105F20(void *dst, void *src)
{
    __asm__ __volatile__("lq $a2, 0($a1)" : : : "memory");
    __asm__ __volatile__("sq $a2, 0($a0)" : : : "memory");
    __asm__ __volatile__("lq $a2, 0x10($a1)" : : : "memory");
    __asm__ __volatile__("sq $a2, 0x10($a0)" : : : "memory");
    __asm__ __volatile__("lq $a2, 0x20($a1)" : : : "memory");
    __asm__ __volatile__("sq $a2, 0x20($a0)" : : : "memory");
    __asm__ __volatile__("lq $a2, 0x30($a1)" : : : "memory");
    __asm__ __volatile__("sq $a2, 0x30($a0)" : : : "memory");
    __asm__ __volatile__("nop");
}
