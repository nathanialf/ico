/* src/cod/043CD0.c — func_00143CD0 */

extern unsigned char D_006A95B0[];

void *func_00143CD0(int *target_ptr)
{
    int target = *target_ptr;
    char *base = (char *)&D_006A95B0[0];
    char *end = base + 0x300;
    char *p = base;
    do {
        if (*(int *)p == target) return p;
        p += 0x30;
    } while (p < end);
    return (void *)0;
}
