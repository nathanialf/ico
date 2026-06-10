#include "common.h"

extern int D_0062C074;
extern int D_0062C078;

void InitCameraSetManager(int *a0, int *a1) {
    *a0 = D_0062C074;
    *a1 = D_0062C078;
}

extern int D_0062C080;
extern int D_006C9F98[];

void func_0018A0D8(int a0) {
    D_0062C080 = a0;
    D_006C9F98[0] = 0;
}

extern int D_0062C080;

int func_0018A0E8(void) {
    return D_0062C080;
}

extern int D_006C9F60[];
extern float D_006291E8;
extern float ClearHandCameraCorrect(void *a0, int a1);
extern void func_00240008();
extern void func_0023FE98(void *dst, void *src);
extern float func_00191E30(void *a0);

void func_0018A0F0(int a0, float *a1, int *a2) {
    int *base = D_006C9F60;
    float buf[4];
    int deg;
    *a1 = ClearHandCameraCorrect(base, a0);
    func_00240008(buf, a0, base);
    func_0023FE98(buf, buf);
    deg = (int)(func_00191E30(buf) / D_006291E8 * 180.0f) -
          *(short *)((char *)base + 0x12) * 180 / 32768;
    if (deg >= 181)
        deg -= 360;
    if (deg <= -180)
        deg += 360;
    *a2 = deg;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-set-manager", func_0018A1D8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-set-manager", func_0018A268);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-set-manager", func_0018A300);

extern int D_006C9F60[];
extern unsigned char D_0062C08C;
extern unsigned char D_0062C07C;

void *func_0018A370(void) {
    return D_006C9F60;
}

void func_0018A380(void) {
    D_0062C08C = 1;
}

void func_0018A390(void) {
    D_0062C07C = 1;
}

extern int D_006C9FA8[];

int func_0018A3A0(void) {
    return D_006C9FA8[0] < 2;
}

/* parked: needs real matching. See tough_nuts/func_0018A3B0/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-set-manager", func_0018A3B0);

void func_0018A408(void) {
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    char               f_31;  /* 0x31 */
    char               f_32;  /* 0x32 */
    unsigned long long f_38;  /* 0x38 */
} S_006C9FB0;

/* end struct shapes */
