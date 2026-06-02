/* src/cod/09DB08.c — func_0019DB08 */

int func_0019DB08(int *a0, int *out)
{
    int a2 = a0[3];
    if (a2 != 0) {
        int v1 = a0[2] - a2;
        int divisor = a0[1];
        v1 = v1 + divisor;
        *out = a0[0] + (v1 % divisor);
    }
    return a2;
}
