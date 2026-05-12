extern int D_006AA968[];
extern int D_002E4E00[];

void func_0014BD88(void)
{
    int *dst = D_006AA968;
    char *src = (char *)D_002E4E00;
    int i = 0x46;
    do {
        *dst = *(int *)src;
        i--;
        src += 0x94;
        dst++;
    } while (i >= 0);
}
