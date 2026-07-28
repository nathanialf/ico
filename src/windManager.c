#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/windManager", ExecWindManager);

INCLUDE_ASM("asm/nonmatchings/src/windManager", ReinitWindManager);

INCLUDE_ASM("asm/nonmatchings/src/windManager", SetWindManager);

extern float D_00631414;
extern float D_0063375C;
extern float D_00633764;
extern float D_0063376C;
extern float D_00633770;
extern int D_00633774;
extern void drawSenpuukiHaneUnit(float a0);
extern float pac_DispQW(void);

void InitWindManager(void) {
    float v;
    if (++D_00633774 >= 0x33) {
        D_0063376C = D_0063375C * ((pac_DispQW() * 2.0f - 1.0f) * D_00633764 + 1.0f);
        D_00633774 = 0;
    }
    v = D_00633770 + (D_0063376C - D_00633770) * D_00631414;
    D_00633770 = v;
    drawSenpuukiHaneUnit(v);
}

INCLUDE_ASM("asm/nonmatchings/src/windManager", GetRegularizedWindSpeed);

INCLUDE_ASM("asm/nonmatchings/src/windManager", func_001F5140);

INCLUDE_ASM("asm/nonmatchings/src/windManager", func_001F51C0);

