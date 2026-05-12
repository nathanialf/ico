/* src/cod/0A9EE8.c — func_001A9EE8 */

extern char D_006F1930[];
extern int D_006329E4;

void func_001A9EE8(void)
{
    char *p = D_006F1930;
    int i;
    p += 0x5B4;
    for (i = 0x1A; i >= 0; i--) {
        *p = 0;
        p -= 0x38;
    }
    D_006329E4 = 0;
}
