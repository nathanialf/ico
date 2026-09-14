/* libc.a member fstatr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
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
extern int _vfprintf_r(int *self, int subj, int b, void *args);
extern int func_0027FE08(int a0, int a1, int a2);
extern long long func_0027FEA8(void *a0, void *a1, int a2, int a3);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void memset(void *a0, int a1, int a2);
extern int memcpy(char *a0, char *a1, int a2);
extern int _sbrk_r(int *self, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int errno[];
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern int _close_r(int *self, int a1);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);

int _fstat_r(int *self, int a1, int a2)
{
    int ret;
    errno[0] = 0;
    ret = fstat(a1, a2);
    if (ret == -1) {
        if (errno[0] != 0) {
            self[0] = errno[0];
        }
    }
    return ret;
}

extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
