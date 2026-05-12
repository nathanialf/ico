/* src/cod/0CE9B8.c — func_001CE9B8 */

int func_001CE9B8(char *self)
{
    int *obj = *(int **)(self + 0x15C);
    int count = *(int *)((char *)obj + 0x88);
    int zero_count = 0;
    if (count > 0) {
        int *p = (int *)*(int *)(*(int *)((char *)obj + 0x800) + 0x14);
        do {
            int v = *p;
            int next = zero_count + 1;
            p++;
            count--;
            if (v == 0) zero_count = next;
        } while (count != 0);
    }
    return zero_count;
}
