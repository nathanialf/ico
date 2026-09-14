#include "common.h"
#include "ico/types.h"

extern int D_0028F8F4[];
extern int D_00639C80;
extern int D_00639C94;
extern void ExecKeyInput();

typedef struct {
    int *th[6];
} ThreadTbl;

extern ThreadTbl D_0054D508;
extern void iosThreadDestroy(int *th);

void Emergency_DestroyAllThread(void)
{
    int me = GetThreadId();
    ThreadTbl t = D_0054D508;
    unsigned int i;

    for (i = 0; i < 6; i++) {
        if (me != t.th[i][0x30 / 4]) {
            iosThreadDestroy(t.th[i]);
        }
    }
}

int movie_abort_check(void)
{
    int ret = 0;
    if (D_00639C94 != D_00639C80) {
        D_00639C94 = D_00639C80;
        ExecKeyInput();
        ret = 0;
        ret = (D_0028F8F4[0] & 0x800) != ret;
    }
    return ret;
}

void demoEnd(void) {}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/main", main);
