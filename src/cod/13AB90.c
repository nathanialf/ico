typedef struct {
    long long lo;
    long long hi;
} V16;

extern V16 D_0061C360;
extern int D_00631AE8;
extern void func_0017DF38(int, int, V16 *, int, float);

void func_0023AB90(volatile unsigned int x)
{
    volatile int local;
    V16 buf;
    buf = D_0061C360;
    func_0017DF38(D_00631AE8, 0, &buf, 0, 100.0f);
}
