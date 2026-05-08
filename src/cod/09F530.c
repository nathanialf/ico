extern int func_00103018(int a0);

struct __attribute__((packed)) u64_packed_19F530 { long long v; };
extern struct u64_packed_19F530 D_006323C0;

void func_0019F530(int *self)
{
    struct u64_packed_19F530 *dst;
    func_00103018((int)self);
    dst = (struct u64_packed_19F530 *)self[0x15C / 4];
    dst->v = D_006323C0.v;
}
