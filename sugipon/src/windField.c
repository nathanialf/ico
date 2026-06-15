#include "common.h"

extern int D_00271BD0[];

extern void gif_SpriteOffset(int a0);
extern void gsb_SetFrame(int a0, int a1, int a2);
extern void func_001D1DF0();
extern void func_00105108(float f12, float f13, float f14);
extern void LightTorchOffOfWeapon(float f12);
extern void func_0010F9D0(void);
extern char D_004C27A0[];
extern char D_004C2490[];
extern char D_004C2600[];

void InitWindField(float scale) {
    char *cur;

    gif_SpriteOffset(0xB);
    gsb_SetFrame(1, 5, 0);
    cur = D_004C27A0;
    if (-1000.0f < *(float *)cur) {
        do {
            func_001D1DF0(cur, D_004C2490, cur + 0x10, D_004C2490, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
    func_00105108(0.0f, -100.0f, 0.0f);
    cur = D_004C2600;
    if (-1000.0f < *(float *)cur) {
        do {
            func_001D1DF0(cur, D_004C2490, cur + 0x10, D_004C2490, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
    func_00105108(0.0f, -10.0f, 20.0f);
    LightTorchOffOfWeapon(scale);
    func_0010F9D0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", drawSenpuukiHaneUnit);

extern int (*D_0062BA30)(void);

int drawSenpuuki(void) {
    return D_0062BA30();
}

void *ExecWindField(int *a0) {
    if (a0) {
        *a0 = 0;
    }
    return D_00271BD0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", GetWindVector);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/windField", dummyGetWindVector);

extern int (*D_0062BA30)(void);

void getParallelWindVector(void) {
    D_0062BA30 = ExecWindField;
}

extern void func_001D1DF0();
extern char D_004C2490[];

void getRadiateWindVector(char *a0) {
    char *cur = a0;
    if (-1000.0f < *(float *)cur) {
        do {
            func_001D1DF0(cur, D_004C2490, cur + 0x10, D_004C2490, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
}
