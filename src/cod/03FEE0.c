extern int *D_00281A70[];

int *func_0013FEE0(int idx, int target)
{
    int *p = D_00281A70[idx];
    if (p != 0) {
        do {
            if (p[0] == target) {
                return p;
            }
            p = (int *)p[0x10/4];
        } while (p != 0);
    }
    return 0;
}
