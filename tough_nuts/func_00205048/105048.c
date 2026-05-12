/* src/cod/105048.c — func_00205048 */

int func_00205048(float *a, float *b)
{
    if (a[1] < b[1]) return -1;
    if (b[1] < a[1]) return 1;
    return 0;
}
