extern void func_00140A20(short *p, int doubled_idx);

void func_00140B30(int *self, int idx, int val)
{
    short *p;
    int di;
    int dj;
    short *q1, *q2;
    p = (short *)self[0x2C / 4];
    di = idx * 2;
    dj = (di + 1) * 2;
    q1 = (short *)((char *)p + dj);
    q2 = p + di;
    q1[0x20] = (short)val;
    q2[0x1E] = (short)val;
    func_00140A20(p, di);
}
