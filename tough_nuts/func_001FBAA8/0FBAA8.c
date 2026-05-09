extern int D_00633F70;
extern char D_00710D10[];
extern void func_001FB8B8(void);

void func_001FBAA8(long long a, long long b, int c)
{
    int *slot = (int *)(D_00710D10 + D_00633F70 * 0x28);
    int prev24;
    if (slot[0] != 0) {
        func_001FB8B8();
    }
    prev24 = slot[9];
    *(long long *)((char *)slot + 0x18) = a;
    slot[4] = c;
    slot[9] = prev24 + 0x10;
    slot[0] = 1;
    *(long long *)((char *)slot + 0x8) = b & 0x0FFFFFFFLL;
    slot[1] = prev24;
}
