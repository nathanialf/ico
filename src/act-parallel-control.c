#include "common.h"
#include "ico/types.h"

extern int D_006C0928[];
extern char D_003089C0[];
extern int D_005D3B58[];

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

            if (D_005D3B58[m] != 0x47B) {
                do {
                    m++;
                    k++;
                } while (D_005D3B58[m] != 0x47B);
            }
            if (k == 0) {
                v = 0x47B;
            } else {
                int e = idx + n % k;

                v = D_005D3B58[e];
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
