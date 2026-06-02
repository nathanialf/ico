extern char D_0061B040[];
extern void func_001A6E28(char *a0);

void func_00203F18(int a0, int *a1, int *a2)
{
    int v = *a2;
    if (v >= 0x10) {
        func_001A6E28(D_0061B040);
        return;
    }
    *a2 = v + 1;
    a1[v] = a0;
}
