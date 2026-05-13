extern void func_00263520(void *a0, void *a1);
extern void func_00263388(int a0, int a1, int a2, long long a3);

void func_00263FB0(float f12)
{
    int local0[4];
    float local1[4];
    long long a3_val;
    local1[0] = f12;
    func_00263520(local1, local0);
    a3_val = (long long)(unsigned int)local0[3] << 32;
    func_00263388(local0[0], local0[1], local0[2], (long long)((unsigned long long)a3_val >> 2));
}
