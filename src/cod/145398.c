/* src/cod/145398.c — func_00245398 */

void func_00245398(int **a0, long long val)
{
    int *buf = *a0;
    int *next;
    *buf++ = (int)val;
    next = buf + 1;
    *buf = (int)(val >> 32);
    *a0 = next;
}
