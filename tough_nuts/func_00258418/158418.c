extern void func_00258470(int *self, int a1);

void func_00258418(int *self, int a1_param, int a2, int a3)
{
    self[3] = a1_param;
    self[9] = a2 + a3;
    self[10] = a3;
    self[2] = a1_param;
    *(long long *)self = 0;
    self[4] = 0;
    *(long long *)((char *)self + 0x18) = 0;
    self[8] = a2;
    func_00258470(self, 0);
}
