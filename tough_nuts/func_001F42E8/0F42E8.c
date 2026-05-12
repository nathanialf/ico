/* src/cod/0F42E8.c — func_001F42E8 */

extern char D_006124F8[];

float func_001F42E8(char *self)
{
    char *p = *(char **)(*(char **)(self + 0x15C) + 0x800);
    int idx = *(int *)p;
    return (float)*(int *)((D_006124F8 + idx * 0x24) + 0xC);
}
