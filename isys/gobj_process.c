/* isys/gobj_process.c — __FILE__ anchor at .rodata 0x00557AD0
 *
 * TU range: [0x0013F700, 0x0013F778)  (next subseg: src/cod/03F778 at 0x0013F778)
 *
 * Single func:
 *   - func_0013F700: alloc count*0x94 GObjProcess pool, zero first int per slot.
 *     ptr pinned to $5 (a1) and stride pinned to $2 (v0) so gcc emits the
 *     original `mult3` per-iter index instead of strength-reducing to a
 *     pointer increment. Compiled with -fno-strength-reduce.
 */

#include "gobj_process.h"

void func_0013F700(int count)
{
    register int *ptr REG("$5");
    register int stride REG("$2");
    unsigned int i;
    ptr = (int *)func_0013A0F8(D_00632008, count * 0x94, D_00557AD0, 0x49);
    D_00633CAC = count;
    D_00633CA8 = (int)ptr;
    i = 0;
    if (count != 0) {
        do {
            stride = 0x94;
            *(int *)((char *)ptr + i * stride) = 0;
            i += 1;
        } while (i < (unsigned int)count);
    }
}
