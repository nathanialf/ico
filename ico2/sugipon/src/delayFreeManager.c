#include "common.h"
#include "debug.h"
#include "memory.h"

extern void *D_00667340[3][384];
extern int D_00639EE0;
extern int D_00639EE4;
extern char D_00639EE8[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

#include "delayFreeManager.h"

static inline void ClearDelayFreeBuffer(int no)
{
    int i;

    for (i = 384 - 1; i >= 0; i--) {
        D_00667340[no][i] = 0;
    }
}

static inline void FreeDelayFreeBuffer(int no)
{
    int i;

    for (i = 0; D_00667340[no][i] != 0; i++) {
        iosFree(D_00667340[no][i]);
    }
}

inline void InitDelayFree(void)
{
    ClearDelayFreeBuffer(0);
    ClearDelayFreeBuffer(1);
    ClearDelayFreeBuffer(2);
    D_00639EE4 = 0;
    D_00639EE0 = 0;
}

inline void ExecDelayFree(void)
{
    int no = (D_00639EE0 + 2) % 3;

    FreeDelayFreeBuffer(no);
    ClearDelayFreeBuffer(no);
    D_00639EE4 = 0;
    D_00639EE0 = no;
}

void EntryDelayFree(void *p)
{
    D_00667340[D_00639EE0][D_00639EE4++] = p;
    if (D_00639EE4 >= 384) {
        debug_StdPrintfDummy("[33mERROR!!! TOO MANY DELAY FREE LIST ENTRY!!! EXIT...[m\n");
        debug_assert("src/delayFreeManager.c", 51);
        __assert("src/delayFreeManager.c", 51, D_00639EE8);
    }
}
