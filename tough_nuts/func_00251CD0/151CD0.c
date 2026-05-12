/* src/cod/151CD0.c — func_00251CD0 */

int func_00251CD0(int *a0, int idx, int new_v0, int store_v1)
{
    int *base = (int *)a0[0x10];
    int *v1 = (int *)((char *)base + 0xC + idx * 8);
    int *v0 = (int *)((char *)base + idx * 8);
    int old;
    v0[0x10 / 4] = store_v1;
    old = v1[0];
    v1[0] = new_v0;
    return old;
}
