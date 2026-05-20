extern void func_00166E10(int *a0);

struct __attribute__((packed)) Pack8 { long long x; };
extern struct Pack8 D_006323C0_PACK __asm__("D_006323C0");

void func_00167258(int *a0)
{
    a0[0x25] = 0;
    *(struct Pack8 *)((char *)a0 + 0x8C) = D_006323C0_PACK;
    func_00166E10(a0);
}
