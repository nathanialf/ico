/* libc.a member signal.o.  MAIN.MAP member spans tile this run exactly and
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
extern int strtok_r(int a0, int a1, int a2);
extern long long func_0027FEA8(void *a0, void *a1, int a2, int a3);
extern int raise(int a0);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void memset(void *a0, int a1, int a2);
extern void _fwalk(int a0, void *a1);
extern int memcpy(char *a0, char *a1, int a2);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _init_signal_r(void *ptr);

int _init_signal_r(void *ptr)
{
    int i;
    int *p;

    if (*(int **)((char *)ptr + 0x1D4) == 0) {
        p = (int *)_malloc_r(ptr, 0x80);
        *(int **)((char *)ptr + 0x1D4) = p;
        if (p == 0) {
            return -1;
        }
        for (i = 0; i < 32; i++) {
            p[i] = 0;
        }
    }
    return 0;
}

unsigned int _signal_r(void *a0, int a1, int a2)
{
    unsigned int *base;
    unsigned int old;
    if ((unsigned int)a1 >= 0x20) {
        *(int *)a0 = 0x16;
        return 0xFFFFFFFFU;
    }
    if (*(int *)((char *)a0 + 0x1D4) == 0) {
        if (_init_signal_r((int)a0) != 0) {
            return 0xFFFFFFFFU;
        }
    }
    base = *(unsigned int **)((char *)a0 + 0x1D4);
    old = base[a1];
    base[a1] = a2;
    return old;
}

extern int _getpid_r(void *ptr);
extern int _kill_r(void *ptr, int pid, int sig);

int _raise_r(void *ptr, int sig)
{
    int *base;
    int func;
    int ret = 0;

    if ((unsigned int)sig >= 0x20) {
        *(int *)ptr = 0x16;
        return -1;
    }
    if (*(int **)((char *)ptr + 0x1D4) == 0) {
        if (_init_signal_r(ptr) != 0) {
            return -1;
        }
    }
    base = *(int **)((char *)ptr + 0x1D4);
    switch (base[sig]) {
    case 0:
        return _kill_r(ptr, _getpid_r(ptr), sig);
    case -1:
        *(int *)ptr = 0x16;
        ret = 1;
        break;
    case 1:
        break;
    default:
        func = base[sig];
        base[sig] = 0;
        ((void (*)(int))func)(sig);
        break;
    }
    return ret;
}

int __sigtramp_r(void *ptr, int signo)
{
    int *base;
    int func;

    if ((unsigned int)signo >= 0x20) {
        return -1;
    }
    if (*(int **)((char *)ptr + 0x1D4) == 0) {
        if (_init_signal_r(ptr) != 0) {
            return -1;
        }
    }
    base = *(int **)((char *)ptr + 0x1D4);
    switch (base[signo]) {
    case 0:
        return 1;
    case -1:
        return 2;
    case 1:
        return 3;
    }
    func = base[signo];
    base[signo] = 0;
    ((void (*)(int))func)(signo);
    return 0;
}

extern int _raise_r(void *ptr, int sig);

int raise(int a0)
{
    return _raise_r(D_0054CEAC[0], a0);
}

int signal(int a0, int a1)
{
    return _signal_r(D_0054CEAC[0], a0, a1);
}

void *_init_signal(void)
{
    return _init_signal_r(D_0054CEAC[0]);
}

extern int __sigtramp_r(void *ptr, int signo);

int __sigtramp(int a0)
{
    return __sigtramp_r(D_0054CEAC[0], a0);
}

extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
