#include "act-parallel-control.h"
#include "debug.h"

/* .bss, owned by act-parallel-control.o and reached only from this file
   (MAIN.MAP names no symbol in the run): the parallel-action ids copied out of
   the layout table. */
static int parallelIds[86];

extern char D_003089C0[];

/* listing lines 23-80.  The helper's rows (28-55) sit INSIDE this function's
   own line span and below its head, so it is a GNU nested function of the
   2001 source; gcc inlines it (it is called once), and its reference to the
   parameter n is what moves n to the frame slot at 0(sp). */
void ActPara_MakeTbl(int *tbl, unsigned long long mask, int n)
{
    int i;
    int j;
    int val;

    inline int resolve(int v)
    {
        if (v > 0xFFFF) {
            int idx = v - 0x10000;
            int m = idx;
            int k = 0;

            if (randomMotionKind[m] != 0x47B) {
                do {
                    m++;
                    k++;
                } while (randomMotionKind[m] != 0x47B);
            }
            if (k == 0) {
                v = 0x47B;
            } else {
                int e = idx + n % k;

                v = randomMotionKind[e];
            }
        }
        return v;
    }

    for (i = 0; i < 44; i++) {
        if (((mask >> i) & 1) == 1) {
            for (j = 0; j < 86; j++) {
                val = *(int *)(D_003089C0 + j * 0xB0 + i * 4);
                val = resolve(val);
                if (val != 0x47B) {
                    tbl[j] = val;
                }
            }
        }
    }
}

void ActPara_InitSystem(void)
{
    int i;
    for (i = 0; i <= 85; i++) {
        parallelIds[i] = *(int *)(D_003089C0 + i * 0xB0);
    }
    /* A compiled-out overflow check.  What the bytes pin: its message and
       __FILE__ are act-parallel-control.o's whole .rodata and its "0" the
       whole .sdata, in that order, with no instruction.  What they cannot:
       the condition that disabled it and its line; the listing's rows
       101-110, empty after this loop (99-100), are where it fits. */
    if (0) {
        /* too many parallel motions (way too many) */
        debug_StdPrintfDummy("並列モーションが増えすぎました（大森）");
        debug_assert(__FILE__, 103);
        __assert(__FILE__, 103, "0");
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
