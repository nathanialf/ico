/* src/cod/105670.c — func_00205670 */

extern int D_004CC1E0[];

int func_00205670(int dummy, int idx1, int idx2)
{
    int *node_a = (int *)((char *)D_004CC1E0 + idx1 * 0x40);
    int *node_b = (int *)((char *)D_004CC1E0 + idx2 * 0x40);
    int *old = (int *)node_a[3];
    node_a[3] = (int)node_b;
    node_b[2] = (int)node_a;
    node_b[3] = (int)old;
    old[2] = (int)node_b;
    return 0;
}
