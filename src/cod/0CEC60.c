/* src/cod/0CEC60.c — func_001CEC60 */

extern char D_0061D560[];

float func_001CEC60(char *self)
{
    char *p = *(char **)(*(char **)(self + 0x15C) + 0x800);
    char *new_var;
    int idx = *(int *)(p + 8);
    new_var = D_0061D560 - (-(idx * 0x14));
    return ((float *)new_var)[2];
}
