extern int D_004C7710[];

void func_00112148(int a0)
{
    long long *p;
    long long tag1;
    if (a0 == 0) {
        tag1 = 0x30000LL;
    } else {
        tag1 = 0x50000LL;
    }
    p = (long long *)D_004C7710[4];
    *p = tag1;
    p++;
    D_004C7710[4] = (int)p;
    *p = 0x47LL;
    p++;
    D_004C7710[4] = (int)p;
}
