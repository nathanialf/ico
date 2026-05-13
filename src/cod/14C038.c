extern int func_0024CBC0(int x);
extern void func_00101A40(void);
extern void func_00101A88(void);
extern int D_00717900[3];

int func_0024C038(int self)
{
    if (func_0024CBC0(1) != 0) {
        return 0;
    }
    func_00101A40();
    {
        int prev = D_00717900[0];
        D_00717900[0] = self;
        func_00101A88();
        return prev;
    }
}
