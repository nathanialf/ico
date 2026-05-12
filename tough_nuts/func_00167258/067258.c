/* src/cod/067258.c — func_00167258 */

extern char D_006323C0[];
extern void func_00166E10(char *a0);

typedef struct {
    long long ll;
} __attribute__((packed)) U64u;

void func_00167258(char *a0)
{
    *(int *)(a0 + 0x94) = 0;
    ((U64u *)(a0 + 0x8C))->ll = ((U64u *)D_006323C0)->ll;
    return func_00166E10(a0);
}
