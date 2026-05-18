/* src/weapon.c — __FILE__ anchor at .rodata 0x0061A850 */

__attribute__((section(".rodata.0x0061A850"))) const char D_0061A850[16] = "src/weapon.c";

/* Float rodata migrated from weapon_data.c */
__attribute__((section(".rodata.0x0061A860"))) const float D_0061A860[4] = { 0.0f, 1e+01f, 0.0f, 1.0f };

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"

extern void func_001F3188(int a0);
extern void func_001F3390(int a0);
extern int func_00109F10(int a, int b);
extern void func_001F19F0(int x);
struct E36 { char pad[0xC]; int field; char pad2[0x14]; };
extern struct E36 D_006124F8[];

INCLUDE_ASM("asm/nonmatchings/src/weapon", func_001F34C8);
INCLUDE_ASM("asm/nonmatchings/src/weapon", func_001F36F0);

void func_001F3A00(int a0)
{
    func_001F3188(a0);
    func_001F3390(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", func_001F3A28);
INCLUDE_ASM("asm/nonmatchings/src/weapon", func_001F3BD0);

void func_001F3F58(int *self, int *other, int a2)
{
    int *s1;
    int rv;
    s1 = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    s1[0x8 / 4] = (int)other;
    rv = func_00109F10((int)other, a2);
    s1[0xC / 4] = rv;
    ((int *)other[0x15C / 4])[0x630 / 4] = (int)self;
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", func_001F3FB0);

void func_001F4098(int *self)
{
    int *p = (int *) self[0x15C / 4];
    int *q = (int *) p[0x800 / 4];
    int v = q[0x8 / 4];
    int ret = -1;
    if (v != 0)
    {
        int *r = (int *) ((int *) v)[0x15C / 4];
        r[0x630 / 4] = 0;
    }
    q[0x4 / 4] = 0;
    q[0xC / 4] = ret;
    do { q[0x8 / 4] = 0; } while (0);
}


int func_001F40C8(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(int *)(p + 0x0);
}

extern void func_001F2388(int x);
extern void func_001F1868(int x);
void func_001F40D8(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    register int count REG("$2");
    int i;
    count = p[0x50 / 4];
    if (count == 0) goto exit;
    func_001F2388(((int *)p[0x54 / 4])[0]);
    if (p[0x50 / 4] <= 0) goto exit;
    i = 0;
    __asm__ __volatile__("" : "+r"(i));
    do {
        int *arr = (int *)p[0x54 / 4];
        func_001F1868(arr[i]);
        i++;
    } while (i < p[0x50 / 4]);
exit:
    ;
}
void func_001F4150(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    register int count REG("$2");
    int i;
    count = p[0x50 / 4];
    if (count == 0) goto exit;
    func_001F2388(((int *)p[0x54 / 4])[0]);
    if (p[0x50 / 4] <= 0) goto exit;
    i = 0;
    __asm__ __volatile__("" : "+r"(i));
    do {
        int *arr = (int *)p[0x54 / 4];
        func_001F1868(arr[i]);
        i++;
    } while (i < p[0x50 / 4]);
exit:
    ;
}

void func_001F41C8(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    int i;
    for (i = 0; i < p[0x50 / 4]; i++) {
        int *arr = (int *)p[0x54 / 4];
        func_001F19F0(arr[i]);
    }
}


long func_001F4228(int *a0)
{
    register int *v REG("$2") = (int *)a0[0x57];
    register int *v1 REG("$3");
    v = (int *)v[0x200];
    v1 = (int *)v[0x14];
    if (0 == v1) goto fail;
    v1 = (int *)v[0x15];
    return v1[0];
fail:
    return 0;
}

extern void func_0010D830(int *arg);
extern void func_00105F00(int *arg, int b);
void func_001F4250(int *self, int arg1, int a2)
{
    register int a2_check REG("$5");
    int *s0;
    int *p;
    int v;
    int *s1;
    a2_check = a2;
    s0 = (int *) self[0x15C / 4];
    p = (int *) s0[0x800 / 4];
    v = p[0x8 / 4];
    s1 = s0 + 0xA0 / 4;
    if (v != 0) {
        int *r = (int *) ((int *)v)[0x15C / 4];
        r[0x630 / 4] = 0;
    }
    {
        int neg1 = -1;
        int one = 1;
        p[0x4 / 4] = one;
        p[0xC / 4] = neg1;
    }
    p[0x8 / 4] = 0;
    if (a2_check != 0) {
        func_0010D830(s0 + 0x150 / 4);
    }
    func_00105F00(s0 + 0x130 / 4, arg1);
    s1[0x9C / 4] = 0;
}

int func_001F42D0(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(int *)(p + 0xA0) = 0;
    return 1;
}

INCLUDE_ASM_NOP_PAD(func_001F42E4);

float func_001F42E8(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x800);
    int idx = *(int *)p;
    register float v REG("$f0");
    v = (float)D_006124F8[idx].field;
    __asm__ __volatile__("" : "+f"(v));
    NOP();
    return v;
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", func_001F4318);
extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern unsigned int D_004C6240[];
extern void func_001F34C8(int *self, int i, int arg1);
typedef struct { long long w[22]; } WeaponBuf_B0;
int func_001F43D0(int *self, int arg1)
{
    int s2 = func_0013A0F8(D_00632010, 0xB0, D_0061A850, 0x2F2);
    register int count_outer REG("$3");
    int i;
    ((int *)self[0x15C / 4])[0x800 / 4] = s2;
    *(WeaponBuf_B0 *)s2 = *(WeaponBuf_B0 *)D_004C6240;
    count_outer = ((int *)self[0x15C / 4])[0x8 / 4];
    if (count_outer > 0) {
        i = 0;
        do {
            func_001F34C8(self, i, arg1);
            i++;
        } while (i < ((int *)self[0x15C / 4])[0x8 / 4]);
    }
    return s2;
}
