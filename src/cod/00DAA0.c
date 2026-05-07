extern int D_00631B7C;
extern int D_00660A40[];

int *func_0010DAA0(void)
{
    register int *p __asm__("$2");
    __asm__ (
        "lw  $3, %%gp_rel(D_00631B7C)($gp)\n\t"
        "lui $2, %%hi(D_00660A40)\n\t"
        "addiu $2, $2, %%lo(D_00660A40)\n\t"
        "sll $3, $3, 4\n\t"
        "addu $2, $3, $2"
        : "=r"(p) :: "$3"
    );
    return p;
}


