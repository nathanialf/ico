extern int func_00102E08(int a0);

struct __attribute__((packed)) u64_packed { long long v; };

void func_0019F4E8(int *self, struct u64_packed *src)
{
    struct u64_packed *dst;
    func_00102E08((int)self);
    dst = (struct u64_packed *)self[0x15C / 4];
    dst->v = src->v;
}
