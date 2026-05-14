extern int D_00633F70;
extern int D_00710D10[];
extern int D_0061ABF0[];
extern void func_001A6E28(int *a0, int a1);

void func_001FB880(void)
{
    int *entry = &D_00710D10[D_00633F70 * 10];
    unsigned int end = entry[9];
    unsigned int start = entry[1];
    unsigned int count = (end - start) >> 4;
    return func_001A6E28(D_0061ABF0, count - 1);
}
