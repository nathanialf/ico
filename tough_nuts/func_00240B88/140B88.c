extern int D_00633B98;
extern int D_00712CC0[];

int func_00240B88(int key)
{
    int n = D_00633B98;
    int i;
    if (n <= 0) return -1;
    i = 0;
    do {
        if (D_00712CC0[i] == key) return i;
        i++;
    } while (i < n);
    return -1;
}
