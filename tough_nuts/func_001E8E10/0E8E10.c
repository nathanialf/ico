extern char D_007097F0[];
extern void func_00243B60(char *p, int x);

void func_001E8E10(int x)
{
    char *p = D_007097F0;
    char *limit = p + 0xC00;
    do {
        if (*(int *)p != 0) {
            char *callee = *(char **)(p + 0x14);
            if (callee != 0) {
                func_00243B60(callee + 0x40, x);
            }
        }
        p += 0x18;
    } while ((int)p < (int)limit);
}
