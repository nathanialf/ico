/* src/syscalls_late.c — 10 SYSCALL_WRAPPER macros + 1 dispatch loop
 *
 * Coalesced from src/cod/14B3E8.c..src/cod/14B4C8.c — contiguous 16-byte
 * slots interrupted by one 80-byte loop function. Same shape as
 * src/syscalls.c but covering the late-text syscall block
 * @0x0024B3E8..0x0024B4D8.
 */

#include "syscall.h"

SYSCALL_WRAPPER(func_0024B3E8, 0x74)

extern int D_005508C8[];

void func_0024B3F8(void)
{
    int *p = D_005508C8;
    unsigned int i = 0;
    do {
        i++;
        ((void (*)(int, int))func_0024B3E8)(p[0], p[1]);
        p += 2;
    } while (i < 6);
}

SYSCALL_WRAPPER(func_0024B448,  0x55)
SYSCALL_WRAPPER(func_0024B458, -0x55)
SYSCALL_WRAPPER(func_0024B468,  0x56)
SYSCALL_WRAPPER(func_0024B478, -0x56)
SYSCALL_WRAPPER(func_0024B488,  0x57)
SYSCALL_WRAPPER(func_0024B498, -0x57)
SYSCALL_WRAPPER(func_0024B4A8,  0x58)
SYSCALL_WRAPPER(func_0024B4B8, -0x58)
SYSCALL_WRAPPER(func_0024B4C8,  0x59)
