#include "common.h"
#include "mv_defs.h"

int free_buffer(void *a0, int a1) {
    int *p = (int *)a0;
    int n = p[3];
    int t = n;
    if (a1 < n) {
        n = a1;
    }
    p[3] = t - n;
    return n;
}

extern void func_002614F8(void *a0);
extern void iosCdvdSync(void *a0);

int readBufDelete(char *a0) {
    func_002614F8(a0 + 0x34);
    iosCdvdSync(a0);
    return 1;
}

extern int inflate_dynamic(void);

int readBufCreate(void)
{
    inflate_dynamic();
    return 1;
}

extern int inflate_start(void *a0);

int readBufBeginPut(void *a0) {
    return inflate_start(a0);
}

extern void func_0019B720(void *a0);

void readBufEndPut(void *a0) {
    func_0019B720(*(void **)((char *)a0 + 0x48));
}

extern void func_0024DC00(void *a0, int a1, int a2);
extern void func_0024E060(void *a0, int a1, void *a2, void *a3);
extern int func_0023BE80(void *a0);
extern int videoDecEndPut();
extern int videoDecFlush();
extern int videoCallback();
extern int decBitStrm0();
extern int func_0019B8E0();

int readBufBeginGet(void *a0) {
    int mes = deq_movie_mes(0x17C300);
    *(int *)((char *)a0 + 0x48) = mes;
    if (mes == 0) {
        return -1;
    }
    func_0024DC00(a0, mes, 0x17C300);
    func_0024E060(a0, 0, videoDecEndPut, 0);
    func_0024E060(a0, 1, videoDecFlush, a0);
    func_0024E060(a0, 2, videoCallback, a0);
    func_0024E060(a0, 3, decBitStrm0, a0);
    func_0024E060(a0, 5, func_0019B8E0, a0);
    *(int *)((char *)a0 + 0xB8) = 0;
    return func_0023BE80((char *)a0 + 0x50) == 0 ? 0 : -1;
}

extern void func_0023C1D8(void *a0);

void readBufEndGet(void *a0) {
    func_0023C1D8((char *)a0 + 0x50);
}
