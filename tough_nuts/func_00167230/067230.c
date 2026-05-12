/* src/cod/067230.c — func_00167230 */

extern char D_006323C0[];
extern void func_00166E10(char *a0);

typedef struct {
    long long ll;
} __attribute__((packed)) U64u;

void func_00167230(char *a0)
{
    *(int *)(a0 + 0xB0) = 0;
    *(int *)(a0 + 0x94) = 0;
    *(int *)(a0 + 0x88) = 0;
    ((U64u *)(a0 + 0x80))->ll = ((U64u *)D_006323C0)->ll;
    return func_00166E10(a0);
}
