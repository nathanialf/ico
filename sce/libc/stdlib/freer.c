/* libc.a member freer.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

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
extern void abort(void);
extern long long strtol(void *a0, int a1, int a2);
extern int _vfprintf_r(int *self, int subj, int b, void *args);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void memset(void *a0, int a1, int a2);
extern int memcpy(char *a0, char *a1, int a2);

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/freer", _free_r);

extern struct D520 D_0054CEC8;
extern int D_0054D2E0[];
extern int D_0054D2F8[];
extern void __malloc_lock(void);
extern void __malloc_unlock();
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int _sbrk_r(int *self, int a1);

int _malloc_trim_r(int *self, unsigned int a1)
{
    long long A;
    long long need;
    long long newlen;
    int r4;

    __malloc_lock();
    A = D_0054CEC8.blk->size & 0xFFFFFFFC;
    need = __udivdi3((A - a1) + 0xFEF, 0x1000);
    newlen = __muldi3(need - 1, 0x1000);
    if (newlen < 0x1000) {
        goto fail;
    }
    if (_sbrk_r(self, 0) != (int)D_0054CEC8.blk + (int)A) {
        goto fail;
    }
    if (_sbrk_r(self, -(int)newlen) != 0xFFFFFFFFU) {
        goto adjust;
    }
    r4 = _sbrk_r(self, 0);
    A = r4 - (int)D_0054CEC8.blk;
    if (A >= 0x10) {
        D_0054D2F8[0] = r4 - D_0054D2E0[0];
        D_0054CEC8.blk->size = A | 1;
    }
fail:
    __malloc_unlock(self);
    return 0;
adjust:
    D_0054CEC8.blk->size = (A - newlen) | 1;
    D_0054D2F8[0] -= (int)newlen;
    __malloc_unlock(self);
    return 1;
}

extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern int _close_r(int *self, int a1);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
