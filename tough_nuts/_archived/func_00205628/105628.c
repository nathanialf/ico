/* src/cod/105628.c — func_00205628 */

extern int D_004CAEC0[];
extern int D_004CC1E0[];

int func_00205628(int idx1, int idx2)
{
    int *node1 = (int *)((char *)D_004CAEC0 + idx1 * 0x34);
    int *node2 = (int *)((char *)D_004CC1E0 + idx2 * 0x40);
    int *old;
    int v;
    node2[2] = 0;
    old = (int *)node1[2];
    node1[2] = (int)node2;
    v = old[2];
    node2[3] = v;
    old[2] = (int)node2;
    return 0;
}
