void func_00245398(int **buf_ptr, long long val)
{
    int *p = *buf_ptr;
    *p = (int)val;
    p += 1;
    *p = (int)(val >> 32);
    *buf_ptr = p + 1;
}
