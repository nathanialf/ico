extern int D_006335FC;
extern int D_0070C6C8[];

void func_001EBA18(int a0)
{
    int idx = D_006335FC;
    D_006335FC = idx + 1;
    D_0070C6C8[idx] = a0;
}
