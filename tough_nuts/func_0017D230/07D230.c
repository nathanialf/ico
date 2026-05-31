#include "matching.h"

extern int *func_0017E188(int a0);
extern void func_001F2148(int *p);

void func_0017D230(int a0) {
    int *first = func_0017E188(a0);
    int *second = func_0017E188(0);
    second[0x16C/4] = 1;
    func_001F2148(first);
    DEFEAT_TCO();
}
