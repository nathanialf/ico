extern void dpk_SwapBuffer(void);
extern void dpk_Init(int a0, void *a1, int a2);
extern int dl_GetPri(void);
extern char D_0054FBE0[];

void reg_dispLine(void) {
    register void *p __asm__("$5");
    register int n __asm__("$6");
    dpk_SwapBuffer();
    p = D_0054FBE0;
    n = 4;
    __asm__ volatile("" : : "r"(p), "r"(n));
    dpk_Init(2, p, n);
    dl_GetPri();
}
