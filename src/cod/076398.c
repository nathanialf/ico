extern void func_00132B90(int a0, int a1, int a2);
extern int  func_00133500(int a0, int a1);

void func_00176398(int self, int a1, int size)
{
    int large = size + 0x7FE;
    int v1 = size - 1;
    int neg_one = -1;
    if (neg_one < v1) large = v1;
    large = ((large >> 11) + 1) << 11;
    func_00132B90(self, a1, large);
    func_00133500(self, *(int *)((char *)self + 0x110) + size);
}
