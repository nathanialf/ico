/* src/cod/145228.c — func_00245228 */

void func_00245228(int *a0)
{
    int diff;
    int *base = (int *)a0[3];
    int p_minus_4 = a0[0] - 4;
    a0[3] = 0;
    diff = p_minus_4 - (int)base;
    *base = *base + (int)((unsigned int)(diff >> 2) >> 2);
}
