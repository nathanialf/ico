extern int func_0018B0A0(void);

int func_0023C17C(void)
{
    int v = func_0018B0A0();
    int flag;
    int ret;
    if (v == 3) goto set;
    if (v != 9) { flag = 0; goto done; }
set:
    flag = -1;
done:
    ret = -1;
    if (flag) ret = 0;
    return ret;
}
