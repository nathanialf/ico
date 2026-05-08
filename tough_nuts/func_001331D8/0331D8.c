extern int func_0024DA80(int a0);
extern int func_0024D7B0(void);
extern void func_0024A1E0(int a0);

void func_001331D8(int a0)
{
    *(int *)((char *)a0 + 0xC) = 0;
    if (func_0024DA80(a0) == 0) {
        *(int *)((char *)a0 + 0xC) = func_0024D7B0();
    }
    func_0024A1E0(*(int *)((char *)a0 + 0x160));
}
