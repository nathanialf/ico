/* src/cod/03ED40.c — func_0013ED40 */

extern int D_006321CC;

void func_0013ED40(int bit, int set)
{
    if (set != 0) goto set_path;
    D_006321CC &= ~(1 << bit);
    return;
set_path:
    D_006321CC |= (1 << bit);
}
