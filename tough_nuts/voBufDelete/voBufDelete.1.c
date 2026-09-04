#include "common.h"
#include "r5900.h"

extern int func_0023CCE0(int *a, int *b);

int mpegTS(int a0_unused, int *a1, char *a2) {
    long long buf[4];
    func_0023CCE0((int *)(a2 + 0x50), (int *)buf);
    *(long long *)((char *)a1 + 0x8) = buf[0];
    *(long long *)((char *)a1 + 0x10) = buf[1];
    return 1;
}

extern void voBufIsFull(int a0);

void voBufCreate(a0)
int *a0;
{
    voBufIsFull(a0[0]);
    voBufIsFull(a0[1]);
}

extern int D_0062A340;
extern char D_00557158[];
extern char D_00557178[];
extern int deq_mes_th(int a0, int a1, int a2, void *a3, int a4);
extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);
extern void memset(int a0, int a1, int a2);

int voBufDelete(volatile int *a0) {
    char *fp = D_00557158;
    int p, q, i;
    p = deq_mes_th(D_0062A340, 0x697800, 0x40, fp, 0x2A);
    if (p == 0) { func_001AAD00(fp, 0x2B); __assert(fp, 0x2B, D_00557178); }
    memset(p, 0, 0x697800);
    if (p == 0) return -1;
    *(void **)a0 = (void *)(((unsigned int)p & 0xFFFFFFF) | 0x20000000);
    q = deq_mes_th(D_0062A340, 0x323340, 0x40, fp, 0x2A);
    if (q == 0) { func_001AAD00(fp, 0x2B); __assert(fp, 0x2B, D_00557178); }
    memset(q, 0, 0x323340);
    a0[1] = q;
    if (q == 0) return -1;
    a0[2] = 0;
    a0[3] = 0;
    a0[4] = 5;
    i = 0;
    do {
        *(int *)((char *)q + i * 0xA0A40) = 0;
        i++;
    } while (i < a0[4]);
    return 0;
}


void voBufReset(void) {
    voBufCreate();
}

extern int iosMallocCheckLeak2(int a0);

void voBufIsFull(int a0) {
    iosMallocCheckLeak2(a0 & 0xFFFFFFF);
}

/* voBufIncCount — hand-written assembly in Ito's movie/IPU buffer layer. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel voBufIncCount\n"
    "    sw         $0, 0xC($4)\n"
    "    sw         $0, 0x8($4)\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel voBufIncCount\n"
    "    .set reorder\n"
    "    .set at\n"
);

int voBufGetData(int *a0) {
    return a0[3] == a0[4];
}

extern void DIntr(volatile int *a0);

/* voBufGetTag — critical-section update of the shared (volatile) movie output
 * ring: tags the current frame, bumps writeIdx, advances readIdx mod numFrames,
 * then SYNC + EI. The volatile struct pointer orders the field accesses to match
 * Ito's hand-scheduled IPU code. */
void voBufGetTag(volatile int *a0) {
    int w, n;
    DIntr(a0);
    *(int *)(a0[1] + a0[2] * 0xA0A40) = 2;
    w = a0[3];
    n = a0[4];
    a0[3] = w + 1;
    a0[2] = (a0[2] + 1) % n;
    SYNC();
    EI();
}
