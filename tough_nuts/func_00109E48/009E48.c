/* src/cod/009E48.c — func_00109E48 */

void func_00109E48(char *a0)
{
    int *p15c = *(int **)(a0 + 0x15C);
    int count = p15c[0x88 / 4];
    if (count > 0) {
        char *buf = (char *)p15c[0x7F0 / 4];
        int i;
        for (i = 0; i < count; i++) {
            buf[i] = 0;
            p15c = *(int **)(a0 + 0x15C);
            count = p15c[0x88 / 4];
        }
    }
}
