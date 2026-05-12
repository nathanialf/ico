extern void func_002591F0(int a0, int a1, int a2, int a3);

void func_0025E1E8(unsigned long long a0, unsigned int a1, int a2)
{
    if (a1 <= 0x7FFF && a2 >= 0 && a2 <= 0x7FFF && (a0 & 0xFF000000) == 0) {
        func_002591F0(0x4A, (int)a0, a1, a2);
    }
}
