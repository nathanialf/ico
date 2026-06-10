extern int D_004C3850[];

void func_001F8848(void) {
    int idx = D_004C3850[0] ^ 1;
    int off;
    D_004C3850[0] = idx;
    off = idx * 4;
    __asm__("" : "+r"(off));
    D_004C3850[4] = *(int *)((char *)D_004C3850 + off + 4);
    D_004C3850[5] = 0;
    D_004C3850[6] = 0;
    D_004C3850[7] = 0;
}
