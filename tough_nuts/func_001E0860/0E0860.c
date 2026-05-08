extern int D_0063347C;
extern int D_00633478;
extern int D_00632CC8;
extern void func_0010ECB8(void);
extern void func_001E0808(int *self);

void func_001E0860(int *self) {
    int *p;
    int sub;
    p = (int *)self[0x15C/4];
    D_0063347C = (int)self;
    sub = p[0x8C/4];
    if (sub == 0) return;
    D_00633478 = sub;
    func_0010ECB8();
    if (D_00632CC8 == 0) return;
    func_001E0808(self);
}
