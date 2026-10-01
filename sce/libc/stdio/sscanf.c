/* libc.a member sscanf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <string.h>
#include <reent.h>
#include <stdio.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int eofread(void)
{
    return 0;
}

/* kept local: libc_internal.h leaves it out: its definition takes vfscanf.c's own va_list */
extern int __svfscanf(void *a0, void *a1, void *a2);

int sscanf(void *a0, void *a1, ...)
{
    char buf[0x60];
    char *va;
    int len;
    *(short *)(buf + 0xC) = 4;
    *(int *)(buf + 0x10) = *(int *)(buf + 0x0) = (int)a0;
    *(int *)(buf + 0x14) = *(int *)(buf + 0x4) = len = strlen(a0);
    *(int *)(buf + 0x20) = (int)eofread;
    *(int *)(buf + 0x30) = 0;
    *(int *)(buf + 0x44) = 0;
    *(int *)(buf + 0x54) = (int)_impure_ptr;
    va = (char *)__builtin_next_arg(a1) - 48;
    return __svfscanf(buf, a1, va);
}
