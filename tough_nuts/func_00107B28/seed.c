extern float D_0063097C;
extern unsigned int D_00275FD0[];
extern char D_00553CA0[];
extern unsigned int D_00631B5C_hi[] __asm__("D_00631B5C");
extern char D_00631B50_hi[] __asm__("D_00631B50");
extern unsigned int D_00631B58_hi[] __asm__("D_00631B58");
extern void GetWallGlobalInfo(void *a, void *b, int c, int d);
extern void sceVu0Normalize(void *a, void *b);
extern void sceVu0SubVector(void *a, void *b, void *c);
extern void sceVu0OuterProduct(void *a, void *b, void *c);
extern float sceVu0InnerProduct(void *a, void *b);
extern void sceVu0ScaleVectorXYZ(void *a, void *b, float f);
extern void func_00168A28(void *p, float a, float b, float c, float d);
extern float GetYDistanceFromPlane(void *a, int b);
extern void func_00105F00(void *a, void *b);
extern void func_001AD748(const char *f, int l, const char *m);
extern void __assert(const char *f, int l, const void *m);

int func_00107B28(int a0, int a1, int a2, int *a3, int a4, int a5)
{
    char vbuf[0x40];
    char b40[0x10];
    char b50[0x10];
    char b60[0x10];
    char b70[0x10];
    float b80[4];
    void *vbase;
    int best = -1;
    int *p;
    int i;
    float fbest = *(float *)D_00631B5C_hi;

    vbase = a2 ? (void *)a2 : (void *)vbuf;
    GetWallGlobalInfo(vbase, b40, a3[2],
                  *(int *)(*(int *)((char *)a3[0] + 0x15C) + 0xC) + (a3[1] << 6));
    *(int *)(b40 + 4) = 0;
    sceVu0Normalize(b40, b40);
    p = D_00275FD0;
    for (i = 0; i < 4; i++) {
        sceVu0SubVector(b80, (char *)vbase + (p[1] << 4), (char *)vbase + (p[0] << 4));
        sceVu0Normalize(b80, b80);
        sceVu0OuterProduct(b80, b80, b40);
        if (a4 != 0) {
            sceVu0ScaleVectorXYZ(b80, b80, -1.0f);
        }
        if (b80[1] < D_0063097C) {
            float f = sceVu0InnerProduct(b80, (char *)vbase + (p[0] << 4));
            float d;
            func_00168A28(b70, b80[0], b80[1], b80[2], -f);
            d = GetYDistanceFromPlane(b70, a5);
            if (d < 0.0f) d = -d;
            if (d < fbest) {
                func_00105F00(b50, b80);
                fbest = d;
                func_00105F00(b60, b40);
                best = i;
            }
        }
        p++;
    }
    if (best == -1) {
        func_001AD748(D_00553CA0, 0x54E, D_00631B50_hi);
        __assert(D_00553CA0, 0x54E, D_00631B58_hi);
    }
    if (a0 != 0) {
        float f = sceVu0InnerProduct(b50, (char *)vbase + (D_00275FD0[best] << 4));
        func_00168A28((void *)a0, *(float *)b50, *(float *)(b50 + 4), *(float *)(b50 + 8), -f);
    }
    if (a1 != 0) {
        float f = sceVu0InnerProduct(b60, (char *)vbase + (D_00275FD0[best] << 4));
        func_00168A28((void *)a1, *(float *)b60, *(float *)(b60 + 4), *(float *)(b60 + 8), -f);
    }
    return best;
}
