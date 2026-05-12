/* src/cod/13F740.c — func_0023F740 */

int *func_0023F740(int *a0, long long a1, long long a2, long long a3)
{
    long long t = (a1 << (27 + 32)) | (a3 << 48) | (a2 << 32);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x51;
    a0[0] = 0;
    a0[3] = 0;
    return a0 + 4;
}
