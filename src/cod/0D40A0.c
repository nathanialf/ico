int func_001D40A0(char *a0)
{
    char *sub;
    int *p;
    int ret;
    sub = *(char **)(a0 + 0x15C);
    p = *(int **)(sub + 0x800);
    ret = 0;
    if (p[0] == 1) goto one;
    if (*(int *)(a0 + 0x16C) != 0) goto end;
one:
    ret = 1;
end:
    return ret;
}
