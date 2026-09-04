typedef struct { long long q[6]; } M48;

typedef struct {
    char _p0[0x44];
    unsigned char f44;
    char _p1[0xB];
    union { M48 q; float f[12]; } saved; /* 0x50 */
    float f80, f84, f88; /* 0x80 */
    char _p2[4];
    float f90, f94; /* 0x90 */
    int f98; /* 0x98 */
    char _p3[4];
    float fA0, fA4; /* 0xA0 */
} CamG;
extern CamG D_006C9D50;
extern int D_0062AA1C;
extern char D_006C9DA0[]; /* saved block alias */
extern float ClearHandCameraCorrect(float *a, float *b);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0SubVector(float *a0, float *a1, float *a2);
extern float FSqrt(float a0);
extern void sceVu0Normalize(void *a, void *b);
extern void func_00240038_v(void *a, void *b, float s) __asm__("sceVu0ScaleVector");
extern void _InterGV(void *a0, void *a1, void *a2, float a3, float a4);
extern float D_0062C058;
extern float D_0062C05C;

void func_00185BF8(M48 *src, M48 *dst) {
    float *fs = (float *)src;
    float *fd = (float *)dst;
    float vd[4];
    float b20[4];
    float b30[4];
    float b40[4];
    float b50[4];
    float ang, ang2, t, f0, r1, r2, s;

    if (D_006C9D50.f44 != 0) {
        D_006C9D50.saved.q = *src;
        D_006C9D50.f98 = 0;
        D_006C9D50.fA0 = 0.0f;
        D_006C9D50.fA4 = 0.0f;
        D_006C9D50.f44 = 0;
        D_006C9D50.f80 = 0.0f;
        D_006C9D50.f84 = 0.0f;
        D_006C9D50.f88 = 0.0f;
        D_006C9D50.f90 = 0.0f;
        D_006C9D50.f94 = 0.0f;
        *dst = *src;
        return;
    }

    if (D_0062AA1C != 0) {
        *src = D_006C9D50.saved.q;
    }
    *dst = *src;

    sceVu0SubVector(b20, fs, D_006C9D50.saved.f);
    ang = FSqrt(b20[0] * b20[0] + b20[1] * b20[1] + b20[2] * b20[2]);

    if (D_0062C058 * 11.0f < ang) {
        float lim;
        if (D_0062C058 < D_006C9D50.fA0) {
            D_006C9D50.fA0 = D_0062C058;
        }
        lim = D_006C9D50.fA0;
        if (lim < ang) {
            ang = lim + D_0062C058 / 30.0f;
            sceVu0Normalize(b20, b20);
        } else {
            ang = D_0062C058;
            sceVu0Normalize(b20, b20);
        }
        func_00240038_v(b20, b20, ang);
        sceVu0AddVector(fd, D_006C9D50.saved.f, b20);
    } else {
        int n;
        _InterGV(fd, fs, D_006C9D50.saved.f, 10.0f, 1.0f);
        for (n = 2; n >= 0; n--) {
            __asm__ __volatile__("");
        }
    }

    sceVu0SubVector(b30, fd, (float *)D_006C9DA0);
    ang = FSqrt(b30[0] * b30[0] + b30[1] * b30[1] + b30[2] * b30[2]);
    D_006C9D50.fA0 = ang;
    s = D_0062C05C;
    if (s < 0.0f) {
        s = -s;
    }

    sceVu0SubVector(b40, fs + 4, (float *)(D_006C9DA0 + 0x10));
    ang = FSqrt(b40[0] * b40[0] + b40[1] * b40[1] + b40[2] * b40[2]);
    sceVu0Normalize(b40, b40);
    if (s * 9.0f < ang) {
        D_006C9D50.fA4 = D_006C9D50.fA4 + 0.5f;
        if (s < D_006C9D50.fA4) {
            D_006C9D50.fA4 = s;
        }
        func_00240038_v(b40, b40, D_006C9D50.fA4);
        sceVu0AddVector(fd + 4, (float *)(D_006C9DA0 + 0x10), b40);
    } else {
        _InterGV(fd + 4, fs + 4, (float *)(D_006C9DA0 + 0x10), 8.0f, 1.0f);
        sceVu0SubVector(b40, fd + 4, (float *)(D_006C9DA0 + 0x10));
        ang = FSqrt(b40[0] * b40[0] + b40[1] * b40[1] + b40[2] * b40[2]);
        if (s < ang) {
            ang = s;
        }
        sceVu0Normalize(b40, b40);
        func_00240038_v(b40, b40, ang);
        sceVu0AddVector(fd + 4, (float *)(D_006C9DA0 + 0x10), b40);
        sceVu0SubVector(b50, fd + 4, (float *)(D_006C9DA0 + 0x10));
        ang = FSqrt(b50[0] * b50[0] + b50[1] * b50[1] + b50[2] * b50[2]);
        t = ang;
        if (s < ang) {
            t = s;
        }
        D_006C9D50.fA4 = t;
    }

    f0 = fd[8] - D_006C9D50.saved.f[8];
    if (f0 == 0.0f) {
        goto skip;
    }
    r1 = ClearHandCameraCorrect(fd, fs);
    r2 = ClearHandCameraCorrect(fd, D_006C9D50.saved.f);
    if (r1 + r2 == 0.0f) {
        goto skip;
    }
    fd[8] = (fd[8] * r2 + D_006C9D50.saved.f[8] * r1) / (r1 + r2);
skip:
    vd[0] = fs[0] - D_006C9D50.saved.f[0];
    vd[1] = fs[1] - D_006C9D50.saved.f[1];
    vd[2] = fs[2] - D_006C9D50.saved.f[2];
    D_006C9D50.saved.q = *dst;
    D_006C9D50.f88 = vd[2];
    D_006C9D50.f80 = vd[0];
    D_006C9D50.f84 = vd[1];
}

