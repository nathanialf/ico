extern char D_006E4890[];
extern char D_004B2FD0[];
extern int D_00632898;
extern void func_0018B2F8(void);
extern void func_0018CFF0(void);

struct __attribute__((packed)) Pack24 { long long a; long long b; long long c; };

void func_001A10B0(void)
{
    char *dst = D_006E4890;
    char *end = dst + 0x9450;
    D_00632898 = 0;
    do {
        if (*(int *)(dst + 0x14) == 1) {
            *(struct Pack24 *)dst = *(struct Pack24 *)D_004B2FD0;
        }
        dst += 0x18;
    } while ((int)dst < (int)end);
    func_0018B2F8();
    func_0018CFF0();
}
