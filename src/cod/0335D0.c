/* src/cod/0335D0.c — func_001335D0 */

extern char D_006A5C80[];
extern int D_00633C7C;

void func_001335D0(void)
{
    char *p = D_006A5C80;
    int i;
    p += 0x708;
    for (i = 6; i >= 0; i--) {
        *p = 0;
        p -= 0x12C;
    }
    D_00633C7C = 0;
}
