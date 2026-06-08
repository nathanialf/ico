#include "common.h"

int free_buf(int a0) {
    return *(int *)(a0 + 0xB8);
}

extern int func_0023CF40(int x);
extern int func_0024DFA8(int *self);

int videoDecCreate(int *self)
{
    int ret = 0;
    if (func_0023CF40((int)((char *)self + 0x50)) == 0) {
        ret = func_0024DFA8(self) != 0;
    }
    return ret;
}

extern void func_0023C040(int a0);
extern void voBufIncCount(int a0);
extern void func_0019B508(int a0, int a1, int a2);

void videoDecBeginPut(int *self)
{
    func_0023C040(self[0] + 0x50);
    voBufIncCount(self[2]);
    func_0019B508(self[0], self[1], self[2]);
    *(int *)(self[0] + 0xB8) = 3;
}

extern void debug_assertMessage(void *a0, int a1);
extern char D_0062C968[];

int videoDecEndPut(void *a0, int *a1) {
    debug_assertMessage(D_0062C968, a1[1]);
    return 1;
}

extern void GetStageDifferenceMatrix(void *a0, void *a1, void *a2);
extern void func_0023C310(void *a0);

int videoDecFlush(void *a0, void *a1, char *a2) {
    GetStageDifferenceMatrix(a0, a1, a2);
    func_0023C310(a2 + 0x50);
    return 1;
}

extern void func_0023C5B0(void *a0);

int videoCallback(int a0, int a1, void *a2) {
    func_0023C5B0((char *)a2 + 0x50);
    return 1;
}

extern void func_0023C738(void *a0);

int decBitStrm0(void *a0, void *a1, void *a2) {
    func_0023C738((char *)a2 + 0x50);
    return 1;
}
