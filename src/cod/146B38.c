#include "matching.h"

extern int func_00246918(int);
extern void func_00246970(int);
extern void func_00100440(void);

void func_00246B38(int a0)
{
    for (;;) {
        int v;
        while ((v = func_00246918(a0)) != 0) {
            func_00246970(v);
        }
        func_00100440();
    }
}
