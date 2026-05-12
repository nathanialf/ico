/* src/cod/03CD30.c — func_0013CD30 */

unsigned char *func_0013CD30(int *a0)
{
    int count = a0[0];
    int i = 0;
    if (count > 0) {
        unsigned char *p = (unsigned char *)a0[1];
        do {
            if (*p != 0) return p;
            i++;
            p += 0x40;
        } while (i < count);
    }
    return 0;
}
