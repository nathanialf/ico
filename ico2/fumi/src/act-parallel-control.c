#include "common.h"

extern int D_006C0928[];
extern char D_003089C0[];

static const int actPara_MakeTblTbl[100] = {
    3,    5,   6,    1147, 554,  555,  556,  1147, 563,  564,  1147, 576,  1147, 580, 581,
    1147, 563, 564,  555,  1147, 563,  564,  554,  555,  1147, 563,  564,  554,  555, 556,
    1147, 563, 564,  554,  555,  556,  1147, 841,  842,  1147, 843,  844,  845,  846, 1147,
    927,  928, 1147, 927,  928,  929,  930,  931,  932,  1147, 927,  928,  929,  930, 931,
    932,  933, 934,  935,  936,  1147, 927,  933,  934,  935,  936,  1147, 897,  898, 1147,
    899,  900, 1147, 901,  902,  1147, 903,  904,  1147, 906,  907,  1147, 909,  910, 1147,
    848,  849, 850,  851,  1147, 955,  956,  957,  1147, 0};

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

            if (actPara_MakeTblTbl[m] != 0x47B) {
                do {
                    m++;
                    k++;
                } while (actPara_MakeTblTbl[m] != 0x47B);
            }
            if (k == 0) {
                v = 0x47B;
            } else {
                int e = idx + n % k;

                v = actPara_MakeTblTbl[e];
            }
        }
        return v;
    }

    for (i = 0; i < 0x2C; i++) {
        if (((mask >> i) & 1) == 1) {
            for (j = 0; j < 0x56; j++) {
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
    for (i = 0; i <= 0x55; i++) {
        D_006C0928[i] = *(int *)(D_003089C0 + i * 0xB0);
    }
}

int *ActPara_GetDefTbl(void)
{
    return D_006C0928;
}

int ActPara_StatusToFlag(int a0, int a1)
{
    int v = a0 ? 9 : 1;
    return a1 ? (v | 4) : v;
}

void ActPara_DebugOut(void) {}
