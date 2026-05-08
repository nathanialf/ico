extern int *func_00258C68(void);
extern int func_00246648(char *p);
extern char D_0071EB40[];

int func_0025C570(void)
{
    int ret = 0;
    int *p = func_00258C68();
    if (p[0x44 / 4] != 0) {
        ret = func_00246648(D_0071EB40);
    }
    return ret;
}
