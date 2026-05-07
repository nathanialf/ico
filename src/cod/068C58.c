#include "matching.h"

extern int D_00633D08;
extern int D_00633D0C;
extern int D_00633D10;
extern int D_00633D14;
extern int D_00633D18;
extern int D_00633D1C;
extern int D_00633D20;
extern int D_00633D24;
extern int D_00633D28;

void func_00168C58(void) {
    int tmp;
    D_00633D08 = 0;
    tmp = *(volatile int *)0x10000000;
    D_00633D0C = 0;
    D_00633D18 = tmp;
    DEFEAT_TCO();
    D_00633D10 = 0;
    D_00633D14 = 0;
    D_00633D1C = 0;
    D_00633D20 = 0;
    D_00633D24 = 0;
    D_00633D28 = 0;
}
