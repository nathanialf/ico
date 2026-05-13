#include "regpin.h"

extern int *D_00632024;
extern char D_00554CA8[];
extern char *D_00633C34;
extern char *func_0013A0F8(int *x, int n, char *t, int line);

void *func_00117820(void *self)
{
    char *new_node = func_0013A0F8(D_00632024, 0xA0, D_00554CA8, 0x2D3);
    register char *old REG("$4");
    old = D_00633C34;
    *(void **)(new_node + 0x90) = self;
    *(float *)(new_node + 0x80) = 1.0f;
    if (old != 0) {
        *(char **)(old + 0x94) = new_node;
    }
    *(char **)(new_node + 0x98) = old;
    *(int *)(new_node + 0x94) = 0;
    D_00633C34 = new_node;
    return new_node;
}
