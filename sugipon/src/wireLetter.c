#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DispWireLetter);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DispWireString);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DefaultColorWireString);

extern int D_004C36A0[];
extern int D_004C36B0[];

void ChangeColorWireString(void) {
    D_004C36B0[0] = D_004C36A0[0];
    D_004C36B0[1] = D_004C36A0[1];
    D_004C36B0[2] = D_004C36A0[2];
}

extern int D_004C36B0[];

void Draw2DBox(int a0, int a1, int a2) {
    D_004C36B0[0] = a0;
    D_004C36B0[1] = a1;
    D_004C36B0[2] = a2;
}

typedef struct { float x; float y; int z; } WLPnt;

extern int D_004C36B0[];
extern void gif_SpriteOffset(int a0);
extern void func_001D1DF0(void *a0, void *a1, void *a2, void *a3, int a4);
extern void func_0010F9D0(void);

void func_001F2610(float x0, float y0, float x1, float y1) {
    WLPnt a __attribute__((aligned(16))) = {x0, y0, 0};
    WLPnt b __attribute__((aligned(16))) = {x0, y1, 0};
    WLPnt c __attribute__((aligned(16))) = {x1, y1, 0};
    WLPnt d __attribute__((aligned(16))) = {x1, y0, 0};
    gif_SpriteOffset(0xB);
    func_001D1DF0(&a, D_004C36B0, &b, D_004C36B0, -1);
    func_001D1DF0(&b, D_004C36B0, &c, D_004C36B0, -1);
    func_001D1DF0(&c, D_004C36B0, &d, D_004C36B0, -1);
    func_001D1DF0(&d, D_004C36B0, &a, D_004C36B0, -1);
    func_0010F9D0();
}

extern int D_00629DE4;
extern char D_002715D0[];
extern int DebugDisp1CollisionWithColor(int a0, int a1);
extern void getAnimation(int a0, int a1);
extern void WormDL(int a0, float f12);
extern void WormGeo(int a0, int a1);
extern void GetWormRoute(void *a0, int a1, int a2, float f12);
extern void GetRootMatrixByDObj(void *a0, int a1);
extern void func_0023FFF0(void *a0, void *a1, void *a2);
extern void GetCylinderCollisionWithExceptOwnCollision(int a0, void *a1);

void func_001F26F0(int a0) {
    char buf[0x20];
    char *d = D_002715D0;
    int idx;

    if (*(int *)(d + 0x5C) & 0x20) {
        idx = DebugDisp1CollisionWithColor(D_00629DE4, 0x16);
        getAnimation(a0, *(int *)(*(char **)((char *)D_00629DE4 + 0x15C) + 0xC) + idx * 0x40 + 0x30);
        WormDL(a0, 1.0f);
    }
    if (*(int *)(d + 0x58) & 0x40) {
        idx = DebugDisp1CollisionWithColor(D_00629DE4, 0x16);
        WormGeo(a0, *(int *)(*(char **)((char *)D_00629DE4 + 0x15C) + 0xC) + idx * 0x40 + 0x30);
        GetWormRoute(buf, a0, *(int *)(*(char **)((char *)D_00629DE4 + 0x15C) + 0xC) + idx * 0x40 + 0x30, 5.0f);
        GetRootMatrixByDObj(buf + 0x10, D_00629DE4);
        func_0023FFF0(buf + 0x10, buf + 0x10, buf);
        GetCylinderCollisionWithExceptOwnCollision(D_00629DE4, buf + 0x10);
        WormDL(a0, 0.0f);
    } else {
        WormDL(a0, 1.0f);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", func_001F2818);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_004C36B0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_004C36A0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004C35E0;  /* stride 0x4 */

/* end struct shapes */
