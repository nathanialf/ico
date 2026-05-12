/* src/cod/0D40A0.c — func_001D40A0 */

int func_001D40A0(char *a0)
{
    int *p15c = *(int **)(a0 + 0x15C);
    int v0_p800 = *(int *)((char *)p15c + 0x800);
    int v1 = *(int *)v0_p800;
    int result;
    if (v1 == 1) goto set;
    result = 0;
    if (*(int *)(a0 + 0x16C) != 0) goto end;
set:
    result = 1;
end:
    return result;
}
