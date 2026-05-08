extern int func_001B7288(int x);
extern int D_0063304C;

int func_001B56D0(int a0, int a1)
{
    if (a1 == 0xB7) {
        func_001B7288(0);
        D_0063304C = 0;
        return 0x2E;
    }
    if (a1 == 0xB8) {
        func_001B7288(0);
        D_0063304C = 0;
        return 0x1A;
    }
    return -1;
}
