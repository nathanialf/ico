extern void func_0010ECD8(void);
extern void func_0010ECA0(int s);

void func_001C2FA0(int a0)
{
    int s0 = *(int *)(a0 + 0x15C);
    if (*(int *)(s0 + 0x74)) {
        func_0010ECD8();
        func_0010ECA0(s0);
    }
}
