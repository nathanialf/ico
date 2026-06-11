typedef struct {
    unsigned char pad[0x10];
    unsigned long long *cur;  /* 0x10 */
} GsBaseRed;
extern GsBaseRed D_004C3850;

void gsb_Reduction(int a0) {
    unsigned long long *p;
    if (a0) {
        a0 = 0x50000;
    } else {
        a0 = 0x30000;
    }
    p = D_004C3850.cur;
    *p = a0;
    p++;
    D_004C3850.cur = p;
    *(volatile unsigned long long *)p = 0x47;
    D_004C3850.cur = p + 1;
}
