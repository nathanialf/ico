extern void func_00243B60(int *dst, int *src);
extern int (*D_006323F0)(int *, int);

int func_0016A158(int *a0, int *a1)
{
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    func_00243B60(buf, a0);
    func_00243B60(buf + 4, a1);
    D_006323F0(buf, 1);
    return buf[34];
}
