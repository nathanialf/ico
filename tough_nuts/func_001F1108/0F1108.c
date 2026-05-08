extern unsigned int D_00633718;
extern unsigned int D_0063371C;

int func_001F1108(void)
{
    unsigned int a = D_00633718;
    unsigned int b = D_0063371C;
    int ret = 1;
    if (b < a) {
        b += 0x28000;
    }
    if ((b >= a) && ((int)b < (int)(a + 0x1000))) {
        ret = 0;
    }
    return ret;
}
