extern char D_0061B1B0[];
extern void func_001A6E28(char *p, int *self);

int func_00205AD8(int *self, int which) {
    if (self == 0) {
        return 0;
    }
    func_001A6E28(D_0061B1B0, self);
    if (which == 0) {
        return self[0x8 / 4];
    }
    return self[0xC / 4];
}
