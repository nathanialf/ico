extern int D_00633DB8;
extern int D_00633DB4;
extern int D_006D0B90[];

int func_00191D20(int a0)
{
    if (D_00633DB8 < 0) goto init;
    if (a0 != D_00633DB8) goto append;
    return 1;
init:
    D_00633DB8 = a0;
    return 1;
append:
    D_006D0B90[D_00633DB4] = a0;
    D_00633DB4++;
    return 0;
}
