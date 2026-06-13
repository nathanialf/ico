extern int ChangeBrain_ToKidnap(void *a0, int a1, int a2, int a3, unsigned char a4);
extern int func_00161998(void *a0, int a1, int a2, int a3, unsigned char a4);

int DispCollisionPC(void *a0, int a1, int a2, int a3, unsigned char a4)
{
    int brain = *(int *)(*(int *)((char *)a0 + 0x164) + 0x670);
    if (*(int *)(brain + 0x1DC) != 3)
        return ChangeBrain_ToKidnap(a0, a1, a2, a3, a4);
    return func_00161998(a0, a1, a2, a3, a4);
}
