extern int D_00275254[];
extern int D_006335F4;
extern int D_006335DC;
extern int D_006335FC;
extern int D_0070C6C8[];
extern unsigned char D_004C60C0[];
extern void func_001EA9C8(int p, unsigned char *q);

void func_001EBA40(void)
{
    int v = D_00275254[0];
    D_006335F4 = 0;
    if (v & 0x1000) {
        D_006335DC = D_006335DC - 1;
    }
    if (v & 0x4000) {
        D_006335DC = D_006335DC + 1;
    }
    if (D_006335FC > 0) {
        int i;
        for (i = 0; i < D_006335FC; i++) {
            func_001EA9C8(D_0070C6C8[i], &D_004C60C0[i * 0x10]);
        }
    }
}
