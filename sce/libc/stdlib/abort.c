/* libc.a member abort.o.  MAIN.MAP member spans tile this run exactly and
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

extern void fiprintf();
extern void abort(void);
extern void _exit(int a0);
extern int raise(int a0);

void abort(void)
{
    for (;;) {
        raise(6);
        _exit(1);
    }
}
