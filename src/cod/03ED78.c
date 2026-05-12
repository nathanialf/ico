/* src/cod/03ED78.c — func_0013ED78 */

extern int D_006321D0;

void func_0013ED78(int bit, int set)
{
    if (set != 0) goto set_path;
    D_006321D0 &= ~(1 << bit);
    return;
set_path:
    D_006321D0 |= (1 << bit);
}
