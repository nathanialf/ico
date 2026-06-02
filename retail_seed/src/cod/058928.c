/* src/cod/058928.c — func_00158928 */

extern void func_001C0708(int a0);
extern void func_001E9DF0(int a0);

void func_00158928(int *self)
{
    int *p = (int *)self[0x59];
    int code = p[0xC];
    switch (code) {
    case 0x31:
        func_001C0708(p[0x52]);
        break;
    case 0x33:
        func_001E9DF0(p[0x17A]);
        break;
    }
}
