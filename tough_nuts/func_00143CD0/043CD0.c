/* src/cod/043CD0.c — func_00143CD0 */

extern int D_006A95B0[];

int *func_00143CD0(int *target_ptr)
{
    int target = *target_ptr;
    char *p = (char *)D_006A95B0;
    char *end = p + 0x300;
    char *q = p;
    while (p < end) {
        if (*(int *)p == target) return (int *)q;
        p += 0x30;
        q += 0x30;
    }
    return 0;
}
