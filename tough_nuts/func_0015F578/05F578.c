extern char D_006322F0[];
extern char D_00282660[];
extern void func_001A6E28(char *p, int *self);
extern void func_00158960(int *self, int x);

struct __attribute__((packed)) U64 { long long v; };

void func_0015F578(int *self) {
    int *p;
    func_001A6E28(D_006322F0, self);
    p = (int *)self[0x15C / 4];
    ((struct U64 *)((char *)p + 0x1C0))->v = ((struct U64 *)D_00282660)->v;
    *(int *)((char *)p + 0x1C8) = *(int *)(D_00282660 + 8);
    func_00158960(self, 0);
}
