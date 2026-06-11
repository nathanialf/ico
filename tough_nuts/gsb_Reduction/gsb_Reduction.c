typedef struct {
    unsigned char pad[0x10];
    unsigned long long *cur;  /* 0x10 */
} GsBaseRed;
extern GsBaseRed D_004C3850;

void gsb_Reduction(int a0) {
    unsigned long long *p = D_004C3850.cur;
    if (a0) {
        *p = 0x50000;
    } else {
        *p = 0x30000;
    }
    p++;
    *(unsigned long long *volatile *)&D_004C3850.cur = p;
    *p = 0x47;
    *(unsigned long long *volatile *)&D_004C3850.cur = p + 1;
}
