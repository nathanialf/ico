/* src/cod/03E488.c — func_0013E488 */

extern unsigned int D_00633CA4;
extern char *D_00633CA0;

int func_0013E488(void)
{
    unsigned int count = D_00633CA4;
    int found = 0;
    if (count != 0) {
        char *base = D_00633CA0;
        unsigned int i = 0;
        do {
            int *p = (int *)(base + i * 0x174);
            int next = found + 1;
            i++;
            if (*p != 0) found = next;
        } while (i < count);
    }
    return found;
}
