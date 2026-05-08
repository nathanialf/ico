extern int D_006A6F30[];
extern char D_006A7330[];
extern int func_00100410(void);
extern void func_0013A5B8(char *a, int b, int c);

void func_0013D3F8(int a0)
{
    int a1 = a0;
    if (a0 == 0) {
        a1 = D_006A6F30[func_00100410()];
    }
    func_0013A5B8(D_006A7330, a1, 0);
}
