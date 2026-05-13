int func_001D40A0(char *a0)
{
    int *p15c = *((int **)(a0 + 0x15C));
    int *v0_p800 = (int *)*((int *)((char *)p15c + 0x800));
    int v1 = (int)v0_p800;
    int new_var2 = *((int *)(a0 + 0x16C));
    int result;
    if (v1 == 1) goto set;
    result = 0;
    if (new_var2 != 0) goto end;
set:
    result = 1;
end:
    return result;
}
