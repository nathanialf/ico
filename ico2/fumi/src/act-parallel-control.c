#include "act-parallel-control.h"
#include "debug.h"
#include "debug_exception.h"
#include <assert.h>
#include "include_asm.h"

/* the parallel-action ids copied out of the layout table (ActPara_InitSystem
   copies 68, one per 148-byte parallel-motion row) */
static int parallelIds[68]; /* derived name */

/* Fill tbl from the parallel-motion table: for each bit set in mask, each
   row's motion for that bit, resolved by the nested helper (an id above
   0xFFFF picks one entry of a random-motion run, by n), replaces the row's
   entry unless it is 0x47B. */
INCLUDE_ASM(ActPara_MakeTbl);

void ActPara_InitSystem(void)
{
    int i;
    for (i = 0; i <= 67; i++) {
        parallelIds[i] = parallelMotionTbl[i].motion[0];
    }
    /* a compiled-out overflow check: its message and __FILE__ stay in
       .rodata (this build's has no __assert: no "0" in .sdata) */
    if (0) {
        /* too many parallel motions (way too many) */
        debug_StdPrintfDummy("並列モーションが増えすぎました（大森）");
        debug_assert(__FILE__, 103);
    }
}

int *ActPara_GetDefTbl(void)
{
    return parallelIds;
}

int ActPara_StatusToFlag(int a0, int a1)
{
    int v = a0 ? 9 : 1;
    return a1 ? (v | 4) : v;
}

void ActPara_DebugOut(void) {}
