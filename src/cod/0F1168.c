extern int D_00633720;
extern int D_00633724;
extern int D_00633728;
extern void func_00139598(int a0);

void func_001F1168(void)
{
    if (D_00633720 != 0) {
        func_00139598(D_00633720);
        func_00139598(D_00633728);
        D_00633728 = 0;
        D_00633720 = 0;
        D_00633724 = 0;
    }
}
