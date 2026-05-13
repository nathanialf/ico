#include "matching.h"

extern char D_00565060[];
extern void func_0015B780(int *self, float *src, float f12);

void func_0015D358(int *self, float *src)
{
    int *p = (int *)self[0x59];
    int *p2 = (int *)self[0x57];
    *(float *)((char *)p + 0x110) = src[0];
    *(float *)((char *)p + 0x114) = src[1];
    *(float *)((char *)p + 0x118) = src[2];
    func_0015B780(self, src, (float)*(int *)&D_00565060[p2[0x128] * 0x190 + 0x138]);
    DEFEAT_TCO();
}
