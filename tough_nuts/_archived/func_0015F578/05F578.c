/* src/cod/05F578.c — func_0015F578 */

extern char D_006322F0[];
extern unsigned char D_00282660[];
extern void func_001A6E28(const char *fmt);
extern void func_00158960(int *self, int x);

typedef struct { long long ll; } __attribute__((packed)) Pack8;

void func_0015F578(volatile int self_arg)
{
    volatile int local;
    int *self;
    int *p;
    long long src_ll;
    int src_int;
    func_001A6E28(D_006322F0);
    self = (int *)self_arg;
    p = (int *)self[0x57];
    src_ll = ((Pack8 *)&D_00282660[0])->ll;
    src_int = *(int *)&D_00282660[8];
    ((Pack8 *)((char *)p + 0x1C0))->ll = src_ll;
    *(int *)((char *)p + 0x1C8) = src_int;
    self = (int *)self_arg;
    func_00158960(self, 0);
}
