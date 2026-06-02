extern char D_00717C50[];
extern int func_0026F3A0(int, int);

int *func_0024E4C8(int a0_idx, int a1_idx)
{
    int *s0_ptr;
    int v_lt;
    int *result;
    int idx = a1_idx * 0x1C + a0_idx * 0x70;
    s0_ptr = *(int **)(D_00717C50 + idx);
    func_0026F3A0((int)s0_ptr, (int)s0_ptr + 0x100);
    v_lt = (s0_ptr[0x58 / 4] < s0_ptr[0xD8 / 4]);
    result = (int *)((char *)s0_ptr + (v_lt << 7));
    return result;
}
