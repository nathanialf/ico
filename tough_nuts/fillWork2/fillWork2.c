#include "common.h"

extern int sprintf(void *buf, const char *fmt, int n);
extern void traceLine(int a0, int a1, unsigned int a2, void *a3);
extern int D_00271634[];
extern const char D_00612D40[];
extern const char D_00612D50[];
extern const char D_00612D60[];
extern const char D_00612D70[];
extern int D_0062AF84;
extern unsigned char D_0062B958[4];
extern int D_0062B994;

void colorSetting(void) {
    char buf[256];
    int x;
    int v4 = D_00271634[0];
    int v5;
    int delta;
    int hi;

    if (!(v4 & 0x1000)) {
        goto else1;
    }
    v5 = D_0062B994;
    v5 -= 1;
    D_0062B994 = v5;
    goto after1;
else1:
    v5 = D_0062B994;
after1:
    if (!(v4 & 0x4000)) {
        goto after2;
    }
    v5 += 1;
    D_0062B994 = v5;
after2:
    if (v5 < 4) {
        goto after3;
    }
    D_0062B994 = 0;
    v5 = 0;
after3:
    if (v5 >= 0) {
        goto after4;
    }
    v5 = 3;
    D_0062B994 = v5;
after4:
    delta = 0;
    if (v4 & 0x2000) {
        delta = 1;
    }
    if (v4 & 0x8000) {
        delta = -1;
    }
    if (v5 == 1) {
        goto c1;
    }
    if (v5 < 2) {
        goto c0;
    }
    if (v5 == 2) {
        goto c2;
    }
    if (v5 == 3) {
        goto c3;
    }
c0:
    sprintf(buf, D_00612D40, D_0062B958[0]);
    hi = 0xFF;
    x = D_0062B958[0] + delta;
    x = (-1 < x) ? x : 0;
    x = (x < 0x100) ? x : hi;
    D_0062B958[0] = x;
    goto tail;
c1:
    sprintf(buf, D_00612D50, D_0062B958[1]);
    hi = 0xFF;
    x = D_0062B958[1] + delta;
    x = (-1 < x) ? x : 0;
    x = (x < 0x100) ? x : hi;
    D_0062B958[1] = x;
    goto tail;
c2:
    sprintf(buf, D_00612D60, D_0062B958[2]);
    hi = 0xFF;
    x = D_0062B958[2] + delta;
    x = (-1 < x) ? x : 0;
    x = (x < 0x100) ? x : hi;
    D_0062B958[2] = x;
    goto tail;
c3:
    sprintf(buf, D_00612D70, D_0062B958[3]);
    hi = 0xFF;
    x = D_0062B958[3] + delta;
    x = (-1 < x) ? x : 0;
    x = (x < 0x100) ? x : hi;
    D_0062B958[3] = x;
tail:
    if (D_0062AF84 & 1) {
        traceLine(0x1B8, 0x28, 0xFFFFFF00, buf);
    }
}
