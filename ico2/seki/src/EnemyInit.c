#include "common.h"

extern char D_0063BD38[8];

/* .bss, owned by EnemyInit.o and reached only from this file (MAIN.MAP names
   no symbol in the run, 0x6C bytes): one slot per enemy kind, each holding the
   position table enemy_Initialize allocates for that kind, or 0. */
static int enemyPositionTable[27];

typedef int Qw128 __attribute__((mode(TI)));

/* RECONSTRUCTION from the ROM's own addressing: the stage table is a record of
   a pointer and a count, reached with one e<<3 index off two bases (the ROM
   keeps `table + 4` in $s7 for the count). */
typedef struct EnemySet {
    int **list; /* 0x0 */
    int n;      /* 0x4 */
} EnemySet;

extern EnemySet D_004F1D58[];
extern void *D_0063A44C;
extern void *iosMallocDebug(void *heap, int size, char *file, int line);

void enemy_Initialize(void)
{
    int cnt[27];
    int e;
    int k;
    int i;
    int j;
    int **tbl;
    int *q;
    float (*dst)[4];
    /* The slot count lives in a local, not in a literal bound: with 27 written
       into the tests cse folds the duplicated k tests before gcse, the count
       loop is then processed by loop.c and its count read is hoisted, which
       the ROM does not do (listing line 104, between the set store and the
       e loop, carries no code). */
    int kindNum = 27;
    /* Vestigial: counted once per copied quadword and never read. The ROM
       pins real code after the copy loop's exit test (stmt.c expand_end_loop
       rolls the test to the bottom only then, and jump.c
       duplicate_loop_exit_test gives the peeled first iteration at
       0x20BDFC..0x20BE24); cse deletes it as dead. The bytes pin that such a
       statement existed, not its text. */
    int copyNum = 0;

    *(int *)D_0063BD38 = 1;
    for (e = 0; e < *(int *)D_0063BD38; e++) {
        tbl = D_004F1D58[e].list;
        for (k = 0; k < kindNum; k++) {
            cnt[k] = 0;
            for (i = 0; i < D_004F1D58[e].n; i++) {
                for (j = 0; j < tbl[i][1]; j++) {
                    int *rec = (int *)(j * 8 + *(int *)tbl[i]);

                    if (rec[1] == k) {
                        q = (int *)rec[0];
                        do {
                            cnt[k]++;
                            q++;
                        } while (*q != -1);
                    }
                }
            }
        }
        for (k = 0; k < kindNum; k++) {
            if (cnt[k] > 0) {
                *(int *)((char *)enemyPositionTable + k * 4 + e * 0x6C) =
                    (int)iosMallocDebug(D_0063A44C, (cnt[k] + 1) << 4, "src/EnemyInit.c", 124);
            } else {
                *(int *)((char *)enemyPositionTable + k * 4 + e * 0x6C) = 0;
                continue;
            }
            dst = (float (*)[4]) * (int *)((char *)enemyPositionTable + k * 4 + e * 0x6C);
            for (i = 0; i < D_004F1D58[e].n; i++) {
                for (j = 0; j < tbl[i][1]; j++) {
                    int *rec = (int *)(j * 8 + *(int *)tbl[i]);

                    if (rec[1] == k) {
                        q = (int *)rec[0];
                        for (;;) {
                            *(Qw128 *)dst = ((Qw128 *)tbl[i][2])[*q];
                            dst++;
                            if (*++q == -1)
                                break;
                            copyNum++;
                        }
                    }
                }
            }
            (*dst)[0] = (*dst)[1] = (*dst)[2] = (*dst)[3] = -1.0f;
        }
    }
}

int enemy_GetPositionTable(int idx, int sub_idx)
{
    int factor;
    if (idx < 0 || idx >= *(int *)D_0063BD38)
        return 0;
    factor = 0x6C;
    return *(int *)((char *)enemyPositionTable + idx * factor + sub_idx * 4);
}
