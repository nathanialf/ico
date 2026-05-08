extern int D_00274ED4[];
extern int D_00275254[];
extern int D_0063304C;
extern int func_001B7288(int a0);

int func_001B5870(int a0) {
    if (a0) {
        D_00274ED4[0] = 1;
    }
    if ((D_00275254[0] & 0x800) == 0) {
        return -1;
    }
    func_001B7288(0);
    D_0063304C = 0;
    return 0x33;
}
