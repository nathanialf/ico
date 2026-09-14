/* libc.a member mbtowc_r.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
/* MAIN.MAP member memchr.o starts at 0x002862EC inside this file: not 8-aligned
 * in the shipped ELF, so it cannot open its own subsegment and is kept here. */
/* MAIN.MAP member memmove.o starts at 0x002863CC inside this file: not 8-aligned
 * in the shipped ELF, so it cannot open its own subsegment and is kept here. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void func_002834F8(void);
extern long long strtol(void *a0, int a1, int a2);
extern int func_0027FE08(int a0, int a1, int a2);
extern long long func_0027FEA8(void *a0, void *a1, int a2, int a3);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void memset(void *a0, int a1, int a2);
extern void _fwalk(int a0, void *a1);
extern int memcpy(char *a0, char *a1, int a2);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int strcmp(int *p, int *buf);

int _mbtowc_r(int a0, int *a1, unsigned char *a2, int a3)
{
    int local;
    int *p = &local;
    if (a1 != 0)
        p = a1;
    if (a2 == 0)
        goto zero;
    if (a3 != 0)
        goto store;
    return -1;
zero:
    return 0;
store:
    *p = *a2;
    return *a2 != 0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mbtowc_r", memchr);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mbtowc_r", memmove);

extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
