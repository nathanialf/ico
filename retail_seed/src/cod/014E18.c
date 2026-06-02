#include "matching.h"

extern int D_00631C18;
extern int func_00242640(int a, int b);
extern void func_001A6E28(char *fmt, ...);
extern void func_00114080(void);
extern char D_00554780[];

int func_00114E18(void)
{
    int counter;
    if (func_00242640(1, 0) == 0) goto reset;
    counter = D_00631C18 + 1;
    D_00631C18 = counter;
    if (counter >= 0xB) {
        func_001A6E28(D_00554780);
        func_00114080();
        D_00631C18 = 0;
    }
    return 1;
reset:
    D_00631C18 = 0;
    return 0;
}
