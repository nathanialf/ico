#include "matching.h"

void func_00109E48(char *a0)
{
    int *p = *(int **)(a0 + 0x15C);
    int i = 0;
    int count = p[0x88 / 4];
    if (count > 0) {
        char *buf = (char *)p[0x7F0 / 4];
        NOP();
        do {
            buf[i] = 0;
            i++;
            p = *(int **)(a0 + 0x15C);
            count = p[0x88 / 4];
        } while (i < count);
    }
}
