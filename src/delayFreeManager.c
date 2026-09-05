#include "common.h"

extern void *D_00667340[3][384];
extern int D_00639EE0;
extern int D_00639EE4;
extern int iosFree();
/* prototypes: their order is the inline tail's emission order */
void InitDelayFree(void);
void ExecDelayFree(void);
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
INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", EntryDelayFree);
