/* src/cod/002790.c — func_00102790 */

extern void func_0010DDB8(int a0, int a1, int a2);
extern void func_0010D830(int a0, int a1);

void func_00102790(int a0, int *a1)
{
    int *p;
    int *q;
    int idx;
    p = (int *)a1[0];
    if (p == 0) goto null_path;
    q = (int *)p[0x57];
    idx = a1[1];
    func_0010DDB8(a0, q[0x4] + (idx << 4), (int)a1 + 0xD0);
    return;
null_path:
    func_0010D830(a0, (int)a1 + 0xD0);
}
