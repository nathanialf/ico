extern int D_00633048;
extern int D_0063303C;
extern void func_001B1B90(void);

int func_001B5118(void) {
    if (D_00633048 == 0) {
        if ((1 >> D_0063303C) & 1) {
            return -1;
        }
    }
    func_001B1B90();
    return -1;
}
