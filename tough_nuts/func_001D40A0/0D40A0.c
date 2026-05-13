/* src/cod/0D40A0.c — func_001D40A0 */

int func_001D40A0(int *self)
{
    int *p = (int *)self[0x57];
    int *p1 = (int *)p[0x200];
    if (p1[0] == 1) return 1;
    if (self[0x5B] != 0) return 0;
    return 1;
}
