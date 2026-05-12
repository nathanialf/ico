/* src/cod/0EF9A8.c — func_001EF9A8 */

extern char D_00275120[];

void func_001EF9A8(int a0, float f12, float f13)
{
    char *p = D_00275120;
    int i12 = (int)f12;
    *(int *)(p + 0xEC) = i12;
    *(int *)(p + 0xF8) = a0;
    *(int *)(p + 0xF0) = (int)f13;
}
