/* src/cod/04AF70.c — func_0014AF70 */

extern int D_006AA4B0[];

unsigned int func_0014AF70(int unused, int target)
{
    int count = D_006AA4B0[0x12C];
    int i = 0;
    int *cur;
    if (count <= 0) return 0;
    cur = D_006AA4B0;
    do {
        if (*cur == target) {
            i++;
            return *(unsigned char *)((char *)cur + 0x190);
        }
        i++;
        cur++;
    } while (i < count);
    return 0;
}
