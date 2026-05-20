/* src/cod/03CD30.c — func_0013CD30 */

void *func_0013CD30(int *self)
{
    int count = self[0];
    char *arr = (char *)self[1];
    int i = 0;
    if (count <= 0) return (void *)0;
    do {
        unsigned char b = *(unsigned char *)arr;
        i += 1;
        if (b == 0) return arr;
        arr += 0x40;
    } while (i < count);
    return (void *)0;
}
