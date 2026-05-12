/* src/cod/03A580.c — func_0013A580 */

extern int D_006A6990[];

void func_0013A580(void)
{
    int *p = D_006A6990;
    int i;
    p += 0xFF;
    for (i = 0xFF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}
