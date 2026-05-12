/* src/cod/090408.c — func_00190408 */

typedef struct { long long ll; } __attribute__((packed)) Pack8;

void func_00190408(char *dst, int *self)
{
    int *q = (int *)self[0x57];
    char *p = (char *)q[0x200];
    long long ll = ((Pack8 *)(p + 0xA4))->ll;
    int last = *(int *)(p + 0xAC);
    ((Pack8 *)dst)->ll = ll;
    *(int *)(dst + 8) = last;
}
