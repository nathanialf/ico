#include "common.h"

/* mail-add-data 0x164 actor-state view (local) */
typedef struct { char _0[0x674]; int *p_674; } MailState;

int AlignDegGV(int a0)
{
    if (a0 < -135) a0 = 180;
    else if (a0 < -45) a0 = -90;
    else if (a0 < 45) a0 = 0;
    else {
        int v = a0;
        a0 = 180;
        if (v <= 134) a0 = 90;
    }
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", ActSendMail_WithAdditionalData);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", HandyCamera_TargetMoveType);

extern float D_006CCE30[];
extern int D_00271240[];
extern float D_0062C0B0;

void ClearMailAdditionalData(void)
{
    int a = D_00271240[0];
    int b = D_00271240[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006CCE30[0] = 0;
    *(int *)&D_006CCE30[1] = 0;
    q = diff / b;
    D_0062C0B0 = 60.0f / (float)q;
}


void InitHandCameraCorrect(void)
{
    int a = D_00271240[0];
    int b = D_00271240[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006CCE30[0] = 0;
    *(int *)&D_006CCE30[1] = 0;
    q = diff / b;
    D_006CCE30[5] = 120.0f;
    D_006CCE30[6] = 80.0f;
    D_0062C0B0 = 60.0f / (float)q;
}


void func_001926A8(float a0, float a1) {
    D_006CCE30[5] = a0;
    D_006CCE30[6] = a1;
}

extern float D_0062C0B0, D_006292CC;
extern void sceVu0SubVector(void *a, void *b, void *c);
extern float _RotGVF(void *a, void *b);
extern void ActSendMail_WithAdditionalData(void *a, void *b, float f12, float f13);
extern void HandyCamera_TargetMoveType(int a, int b);

void func_001926C0(int a0, int a1, float f12, float f13, float f14) {
    float buf[8];
    char *s = (char *)D_006CCE30;
    float r, t, m, n;
    D_0062C0B0 = f14;
    sceVu0SubVector(buf, (void *)a1, (void *)a0);
    buf[4] = buf[0];
    buf[6] = buf[2];
    *(int *)&buf[5] = 0;
    r = _RotGVF(&buf[4], buf);
    *(float *)(s + 0x10) = r;
    if (0.0f < buf[1]) {
        *(float *)(s + 0x10) = -r;
    }
    t = *(float *)(s + 0x18) * D_006292CC / 180.0f;
    {
        float u = *(float *)(s + 0x10);
        m = (t < u) ? u : t;
        n = -t;
        m = m - u;
        *(float *)(s + 8) = m;
        if (u < n) {
            n = u;
        }
        n = n - u;
        *(float *)(s + 0xC) = n;
    }
    ActSendMail_WithAdditionalData(s, s + 4, f12, -f13);
    HandyCamera_TargetMoveType(a0, a1);
}

extern void func_001929A0(char *self);

void func_001927E8(int **a0, int a1) {
    int *p = a0[0x59];
    p[0x19D] = a1;
    func_001929A0(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001927F8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/mail-add-data", func_001928F8);

extern void func_001AAD00(const char *, int);
extern void __assert(const char *, int, const char *);

extern char D_005550C8[];

extern char D_005550E0[];

void func_001929A0(char *self)
{
    MailState *sub_a = *(MailState **)(self + 0x164);
    int *sub_b;
    if (sub_a == 0) {
        func_001AAD00(D_005550C8, 0x47);
        __assert(D_005550C8, 0x47, D_005550E0);
        sub_a = *(MailState **)(self + 0x164);
    }
    sub_b = sub_a->p_674;
    *sub_b = 0;
}

extern void gif_SpriteOffset(int a0);
extern void gif_SetAlpha(int a0, int a1, int a2);

void func_00192A08(void) {
    gif_SpriteOffset(0xB);
    gif_SetAlpha(1, 2, 0x40);
}

extern void func_0010F9D0(void);

void func_00192A30(void) {
    func_0010F9D0();
}

extern int D_00629F5C, D_00629F60;

float _IsInScreen2(int *a0) {
    int z = a0[2];
    int x, y, hx, hy, xhi, yhi;
    float f2, f0;
    if (z < 0) {
        return -1.0f;
    }
    if (z > 0x0FFFFFF0) {
        return -1.0f;
    }
    x = a0[0];
    hx = D_00629F5C / 2;
    if (x < ((0x800 - hx) << 4)) {
        return -1.0f;
    }
    xhi = (hx + 0x800) << 4;
    if (xhi < x) {
        return -1.0f;
    }
    y = a0[1];
    hy = D_00629F60 / 2;
    if (y < ((0x800 - hy) << 4)) {
        return -1.0f;
    }
    yhi = (hy + 0x800) << 4;
    if (yhi < y) {
        return -1.0f;
    }
    f2 = (float)(x - 0x8000) / (float)(xhi - 0x8000);
    if (f2 < 0.0f) {
        f2 = -f2;
    }
    f0 = (float)(z - 0x8000) / (float)(yhi - 0x8000);
    if (f0 < 0.0f) {
        f0 = -f0;
    }
    if (f0 < f2) {
        return f2;
    }
    return f0;
}

extern void CopyMatrix(void *dst, void *src);
extern char D_00287300[];

void func_00192B50(void *a0) {
    CopyMatrix(D_00287300, a0);
    gif_SpriteOffset(0xB);
}
