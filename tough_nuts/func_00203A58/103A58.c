extern void func_0013D3F0(void);

void func_00203A58(int n)
{
    if (n == 0) {
        for (;;) {
            func_0013D3F0();
        }
    } else if (n > 0) {
        do {
            func_0013D3F0();
        } while (--n != 0);
    }
}
