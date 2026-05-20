extern long long D_006323C0;
extern void func_00166E10(int *self);

typedef long long __attribute__((aligned(1))) U64;

void func_00167230(int *self)
{
    *(int *)((char *)self + 0xB0) = 0;
    *(int *)((char *)self + 0x94) = 0;
    *(int *)((char *)self + 0x88) = 0;
    *(U64 *)((char *)self + 0x80) = *(U64 *)&D_006323C0;
    func_00166E10(self);
}
