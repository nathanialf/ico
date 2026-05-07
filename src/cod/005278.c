extern int D_00631B40;
extern int D_0065FA40[];

int *func_00105278(void)
{
    register int *p __asm__("$2");
    __asm__ (
        "lw  $3, %%gp_rel(D_00631B40)($gp)\n\t"
        "lui $2, %%hi(D_0065FA40)\n\t"
        "addiu $2, $2, %%lo(D_0065FA40)\n\t"
        "sll $3, $3, 6\n\t"
        "addu $2, $3, $2"
        : "=r"(p) :: "$3"
    );
    return p;
}
