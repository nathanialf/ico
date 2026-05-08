extern int func_00246918(int s0);
extern void func_00246970(int v);
extern void func_00100440(int v);

void func_00246B38(int s0) {
    while (1) {
        int v = func_00246918(s0);
        if (v != 0) {
            func_00246970(v);
        } else {
            func_00100440(0);
        }
    }
}
