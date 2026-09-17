/* libc.a member readr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);
extern int _vfprintf_r(int *self, int subj, int b, void *args);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern int _sbrk_r(int *self, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int errno[];
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern int _close_r(int *self, int a1);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);

int _read_r(int *self, int a1, int a2, int a3)
{
    int ret;
    errno[0] = 0;
    ret = read(a1, a2, a3);
    if (ret == -1) {
        if (errno[0] != 0) {
            self[0] = errno[0];
        }
    }
    return ret;
}
