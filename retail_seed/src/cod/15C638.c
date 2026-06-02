extern int func_00258C68(int a0, int a1);
extern void func_00258D10(void);

void func_0025C638(int a0, int a1)
{
    int rc = func_00258C68(a0, a1);
    if (*(int *)(rc + 0x44) != 0) {
        func_00258D10();
    }
}
