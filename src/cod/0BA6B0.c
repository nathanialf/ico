extern int func_001BA668(void);

int func_001BA6B0(int *self)
{
    int x = ((int *)((int *)self[0x15C/4])[0x800/4])[0x8/4];
    if (x < 6) {
        if (x >= 2) {
            return 0;
        }
    }
    func_001BA668();
    return 1;
}
