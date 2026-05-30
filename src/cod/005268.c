extern int D_00631B40;

/* Declared void (see 005258.c): keeps the decrement in $v0 with the store
 * in the jr delay slot — matches WITHOUT the coalesce_v1_v0 postprocess. */
void func_00105268(void)
{
    D_00631B40--;
}
