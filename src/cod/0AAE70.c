extern int D_00632B48[];
extern int D_00632B50[];

int *func_001AAE70(int a0, void *a1)
{
    int mask = 1 << a0;
    long bits = *(long *)((char *)a1 + 0x9C0);
    if ((bits & mask) != 0) {
        return D_00632B48;
    }
    return D_00632B50;
}
