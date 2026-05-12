/* src/cod/105518.c — func_00205518 */

extern int D_004CAEC0[];

void func_00205518(int idx)
{
    int *node = (int *)((char *)D_004CAEC0 + idx * 0x34);
    int v1 = node[8 / 4];
    int v0 = node[12 / 4];
    node[20 / 4] = 1;
    *(int *)(v1 + 8) = v0;
    *(int *)(v0 + 12) = v1;
}
