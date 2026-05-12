/* src/cod/049EA8.c — func_00149EA8 */

void func_00149EA8(char *a0)
{
    int *p;
    p = *(int * volatile *)(a0 + 0x15C); p[0x544 / 4] = 1;
    p = *(int * volatile *)(a0 + 0x15C); p[0x54C / 4] = 1;
    p = *(int * volatile *)(a0 + 0x15C); p[0x548 / 4] = 1;
    p = *(int * volatile *)(a0 + 0x15C); p[0x7C / 4] = 1;
}
