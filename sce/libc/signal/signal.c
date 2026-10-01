/* libc.a member signal.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <signal.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

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

/* reent.h leaves it out: its definition takes no reentrancy pointer, which this
   member passes */
extern int _getpid_r(void *ptr);
/* reent.h leaves it out: its definition's argument types do not fit this member's
   calls */
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

int raise(int a0)
{
    return _raise_r((int)_impure_ptr, a0);
}

int signal(int a0, int a1)
{
    return _signal_r((int)_impure_ptr, a0, a1);
}

void *_init_signal(void)
{
    return _init_signal_r((int)_impure_ptr);
}

int __sigtramp(int a0)
{
    return __sigtramp_r((int)_impure_ptr, a0);
}
