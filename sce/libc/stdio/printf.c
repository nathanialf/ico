/* libc.a member printf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern void fiprintf();
extern void abort(void);
extern int _vfprintf_r(int *self, int subj, int b, void *args);

int _printf_r(int *self, int b, ...)
{
    void *args = (char *)__builtin_next_arg(b) - 0x30;
    return _vfprintf_r(self, self[2], b, args);
}

void printf(void *a0, ...)
{
    void *args = (char *)__builtin_next_arg(a0) - 0x38;
    int s = D_0054CEAC[0];
    *(int *)(*(int *)(s + 8) + 0x54) = s;
    vfprintf(*(int *)(s + 8), a0, args);
}

extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void _fwalk(int a0, void *a1);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int _sbrk_r(int *self, int a1);
extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern int _close_r(int *self, int a1);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
