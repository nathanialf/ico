extern void func_0013D3F0(void);

void func_00203A58(int n)
{
    if (n == 0) {
        for (;;) {
            func_0013D3F0();
        }
    }
    if (n > 0) {
        int i = n;
        do {
            func_0013D3F0();
            i--;
        } while (i != 0);
    }
}
