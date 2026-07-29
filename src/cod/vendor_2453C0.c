#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct { int f0; int f4; char *f8; } RingBuf_241C80;

extern int D_005507D0[];
extern void func_00245B58(int a0);

void func_002453C0(int a0) {
    D_005507D0[0] = 0;
    func_00245B58(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002453D0);

extern void func_00100890(void *a0, void *a1);

long long func_00245410(void) {
    volatile int flag;
    volatile long long val;
    volatile int *p;
    flag = 0;
    func_00100890((void*)&flag, (void*)&val);
    p = (volatile int *)0x1000F000;
    *p = 4;
    while ((*p & 4) == 0 && flag == 0) {
    }
    *p = 4;
    return val;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00245470);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002454F0);

extern int func_00264050(void);

int func_00245568(void) {
    *(int *)func_00264050() = 5;
    return -1;
}

int func_00245590(int a1) {
    return -1;
}

int func_00245598(void) {
    return -1;
}

int func_002455A0(int a1, int a2, int a3) {
    return -1;
}

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002455A8\n"
    ".type func_002455A8, @function\n"
    "    .align 3\n"
    "func_002455A8:\n"
    "    addiu $29, $29, -0x40\n"
    "    sd $31, 0x30($29)\n"
    "    sd $18, 0x20($29)\n"
    "    sd $17, 0x10($29)\n"
    "    sd $16, 0x0($29)\n"
    "    mfc0 $17, $12\n"
    "    lui $2, (0x10000 >> 16)\n"
    "    and $17, $17, $2\n"
    "    beqz $17, .L00241B14\n"
    "    lui $18, %hi(D_005507D4)\n"
    ".L00241AF0:\n"
    "    di\n"
    "    sync.p\n"
    "    mfc0 $2, $12\n"
    "    lui $3, (0x10000 >> 16)\n"
    "    and $2, $2, $3\n"
    "    bnez $2, .L00241AF0\n"
    "    nop\n"
    "    b .L00241B18\n"
    "    lw $2, %lo(D_005507D4)($18)\n"
    ".L00241B14:\n"
    "    lw $2, %lo(D_005507D4)($18)\n"
    ".L00241B18:\n"
    "    jal func_00100500\n"
    "    addu $16, $2, $4\n"
    "    sltu $2, $2, $16\n"
    "    beqz $2, .L00241B50\n"
    "    lw $2, %lo(D_005507D4)($18)\n"
    "    jal func_00264050\n"
    "    nop\n"
    "    addiu $3, $0, 0xC\n"
    "    beqz $17, .L00241B44\n"
    "    sw $3, 0x0($2)\n"
    "    ei\n"
    ".L00241B44:\n"
    "    lui $2, (0xFFFFFFFF >> 16)\n"
    "    b .L00241B5C\n"
    "    ori $2, $2, (0xFFFFFFFF & 0xFFFF)\n"
    ".L00241B50:\n"
    "    beqz $17, .L00241B5C\n"
    "    sw $16, %lo(D_005507D4)($18)\n"
    "    ei\n"
    ".L00241B5C:\n"
    "    ld $31, 0x30($29)\n"
    "    ld $18, 0x20($29)\n"
    "    ld $17, 0x10($29)\n"
    "    ld $16, 0x0($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x40\n"
    ".size func_002455A8, . - func_002455A8\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

int func_00245658(void) {
    return 1;
}

int func_00245660(void *a0, void *a1) {
    *(long long *)((char *)a1 + 0x48) = 0;
    *(int *)((char *)a1 + 0x4) = 0x2000;
    return 0;
}

int func_00245678(void) {
    return 1;
}

extern void func_00100140(void *a0);

int func_00245680(int a0, void *a1) {
    if (a0 == 1) {
        func_00100140(a1);
    }
    return 0;
}

int func_002456A8(void) {
    *(int *)func_00264050() = 5;
    return -1;
}

int func_002456D0(void) {
    *(int *)func_00264050() = 5;
    return -1;
}

/* The 0x10-byte header of a print/format sink: f0 is set from the caller,
 * f4 is a running count, and f8/fC are two cursors that both start at the
 * payload (buf, at +0x10).  Field PURPOSE beyond that is not established,
 * so the members are named after their offsets rather than guessed at.
 * The fC-before-f8 order is load-bearing: sched1 emits the two
 * same-valued pointer stores in REVERSE source order (with the f4 store
 * scheduled between them, which is what puts the second one in the `jr`
 * delay slot). */
typedef struct { int f0; int f4; char *f8; char *fC; char buf[1]; } PrintSink;

extern PrintSink D_00713000;

void *func_002456F8(int a0) {
    D_00713000.f0 = a0;
    D_00713000.f4 = 0;
    D_00713000.fC = D_00713000.buf;
    D_00713000.f8 = D_00713000.buf;
    return &D_00713000;
}

void func_00245720(int *q)
{
    int count = q[1] + 1;
    char *wp = (char *)q[3] + 1;
    int cap = q[0];
    q[1] = count;
    cap += 0x10;
    {
        char *end = (char *)q + cap;
        q[3] = (int)wp;
        if (wp == end) {
            q[3] = (int)q + 0x10;
        }
    }
}

void func_00245760(RingBuf_241C80 *a0) {
    a0->f4--;
    a0->f8++;
    if (a0->f8 == (char *)a0 + (a0->f0 + 0x10)) {
        a0->f8 = (char *)a0 + 0x10;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002457A0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00245938);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00245A88);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00245B58);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00245C18);

extern int D_005507D8[];
extern void func_0024BB58(void);

void func_00245DB8(void) {
    func_0024BB58();
    D_005507D8[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00245DE0);

void func_00245E88(void *a0) {
    int *p = (int *)a0;
    p[6] = 0;
    p[4] &= 0xFFFFFFFE;
}

int func_00245EA8(int *a0) {
    int rem = a0[9] % a0[6];
    int ret = a0[5] + rem * 64;
    a0[9] = rem + 1;
    return ret;
}

int func_00245ED8(int *a0, int a1) {
    if (a1 < 0) {
        goto err;
    }
    if (a1 < a0[8]) {
        goto elem;
    }
err:
    return func_00245EA8(a0);
elem:
    return a0[7] + a1 * 64;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00245F18);

extern int func_0024BD90(int a0, int a1, int a2, int a3, int t0, int t1);

void func_00245FD0(int *a0, int *a1) {
    int *ret = (int *)func_00245EA8(a1);
    int f14 = a0[5], f1c = a0[7];
    ret[5] = f14;
    ret[7] = f1c;
    ret[8] = 0x8000000C;
    func_0024BD90(0x80000008, (int)ret, 0x40, a0[8], a0[9], a0[10]);
}

int func_00246030(void *a0, int a1, int a2, int a3, int a4) {
    extern void *func_00245DE0(void *a0);
    extern int func_00100520(int *a0);
    extern int func_0024BD50(int a0, int a1, int a2, int a3, int a4, int a5);
    extern int func_00100530(int a0);
    extern int func_00100560(int a0);
    extern int D_00714BC0[];
    void *obj;
    int buf[8];

    obj = func_00245DE0(D_00714BC0);
    if (obj == 0) {
        return -1;
    }
    *(void **)((char *)a0 + 0) = obj;
    *(int *)((char *)a0 + 4) = *(int *)((char *)obj + 0x18);
    *(int *)((char *)obj + 0x20) = a1;
    *(int *)((char *)obj + 0x24) = a2;
    *(int *)((char *)obj + 0x28) = a3;
    *(void **)((char *)obj + 0x14) = obj;
    *(void **)((char *)obj + 0x1C) = a0;
    if ((a4 & 1) == 0) {
        int r;
        buf[1] = 1;
        buf[2] = 0;
        r = func_00100520(buf);
        *(int *)((char *)a0 + 8) = r;
        if (r < 0) {
            func_00245E88(obj);
            return -3;
        }
        if (func_0024BD50(0x8000000C, (int)obj, 0x40, 0, 0, 0) == 0) {
            func_00245E88(obj);
            func_00100530(*(int *)((char *)a0 + 8));
            return -2;
        }
        func_00100560(*(int *)((char *)a0 + 8));
        func_00100530(*(int *)((char *)a0 + 8));
        return 0;
    } else {
        *(int *)((char *)a0 + 8) = -1;
        if (func_0024BD50(0x8000000C, (int)obj, 0x40, 0, 0, 0) != 0) {
            return 0;
        }
        func_00245E88(obj);
        return -2;
    }
}

void *func_00246188(int a0, void *a1) {
    void *n5;
    void *n3;
    for (n5 = *(void **)((char *)a1 + 0x28); n5 != 0; n5 = *(void **)((char *)n5 + 0x14)) {
        for (n3 = *(void **)((char *)n5 + 0x8); n3 != 0; n3 = *(void **)((char *)n3 + 0x38)) {
            if (*(int *)n3 == a0) {
                return n3;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002461D8);

int func_00246288(void *a0, int a1, int a2) {
    extern void *func_00245DE0(void *a0);
    extern int func_00100520(int *a0);
    extern int func_0024BD50(int a0, int a1, int a2, int a3, int a4, int a5);
    extern int func_00100530(int a0);
    extern int func_00100560(int a0);
    extern int D_00714BC0[];
    void *obj;
    int buf[8];

    *(int *)((char *)a0 + 0x10) = 0;
    *(int *)((char *)a0 + 0x24) = 0;
    obj = func_00245DE0(D_00714BC0);
    if (obj == 0) {
        return -1;
    }
    *(void **)((char *)a0 + 0) = obj;
    *(int *)((char *)a0 + 4) = *(int *)((char *)obj + 0x18);
    *(int *)((char *)obj + 0x20) = a1;
    *(void **)((char *)obj + 0x14) = obj;
    *(void **)((char *)obj + 0x1C) = a0;
    if ((a2 & 1) == 0) {
        int r;
        buf[1] = 1;
        buf[2] = 0;
        r = func_00100520(buf);
        *(int *)((char *)a0 + 8) = r;
        if (r < 0) {
            func_00245E88(obj);
            return -3;
        }
        if (func_0024BD50(0x80000009, (int)obj, 0x40, 0, 0, 0) == 0) {
            func_00245E88(obj);
            func_00100530(*(int *)((char *)a0 + 8));
            return -2;
        }
        func_00100560(*(int *)((char *)a0 + 8));
        func_00100530(*(int *)((char *)a0 + 8));
        return 0;
    } else {
        *(int *)((char *)a0 + 8) = -1;
        if (func_0024BD50(0x80000009, (int)obj, 0x40, 0, 0, 0) != 0) {
            return 0;
        }
        func_00245E88(obj);
        return -2;
    }
}

extern void func_00100F18(int a0);

void func_002463C8(int *a0) {
    int *a5 = (int *)a0[13];
    int *a6 = (int *)a5[16];
    int *a2 = (int *)a6[3];
    if (a2 == 0) {
        a6[3] = (int)a5;
    } else {
        ((int *)a6[4])[15] = (int)a5;
    }
    a6[4] = (int)a5;
    {
        int t5 = a0[5], t7 = a0[7];
        a5[8] = t5;
        a5[7] = t7;
    }
    a5[9] = a0[8];
    a5[3] = a0[9];
    a5[10] = a0[10];
    a5[11] = a0[11];
    a5[12] = a0[12];
    a5[13] = a0[4];
    if ((int)a6[0] < 0) {
        return;
    }
    if (a6[1] != 0) {
        return;
    }
    func_00100F18(a6[0]);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00246458);

int func_00246648(char *a0) {
    char *p = *(char **)a0;
    if (p == 0) goto ret0;
    if (*(int *)(a0 + 4) != *(int *)(p + 0x18)) goto ret0;
    if (*(int *)(p + 0x10) & 1) goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00246688);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00246720);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002467F0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00246888);

extern void func_00101A40(int *self);
extern void func_00101A88(void);

int *func_00246918(int *self)
{
    int *p;
    int v;
    func_00101A40(self);
    p = (int *)self[0xC/4];
    if (p == 0) {
        self[0x4/4] = 0;
        goto after;
    }
    v = p[0x3C/4];
    self[0x4/4] = 1;
    self[0xC/4] = v;
after:
    func_00101A88();
    return p;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00246970);

extern void func_00246970(int *item);
extern void func_00100440(void);

/* Dispatcher thread body: drain the queue, and when it is empty block on
 * the kernel until something is posted.  Never returns. */
void func_00246B38(int *self) {
    int *item;
    for (;;) {
        while ((item = func_00246918(self)) != 0) {
            func_00246970(item);
        }
        func_00100440();
    }
}

extern int D_00550868[];
extern int D_0055086C[];

/* Lazily create the two semaphores that guard the slot table below. */
void func_00246B78(void) {
    extern int func_00100520(int *a0);
    int args[8];
    if (D_00550868[0] == -1) {
        args[5] = 0;
        args[2] = 1;
        args[1] = 1;
        D_00550868[0] = func_00100520(args);
        D_0055086C[0] = func_00100520(args);
    }
}

extern int D_00550868[];
extern char D_00715D00[];
extern void func_00100540(int a0);
extern int func_00100560(int a0);
extern void func_00246B78(void);

int func_00246BD8(void) {
    char *p;
    char *end;
    func_00246B78();
    func_00100560(D_00550868[0]);
    p = D_00715D00;
    end = p + 0x200;
    while (p < end) {
        if (*(int *)(p + 4) == 0) {
            *(int *)(p + 4) = 0x10000000;
            func_00100540(D_00550868[0]);
            return (int)p;
        }
        p += 0x10;
    }
    func_00100540(D_00550868[0]);
    return 0;
}

/* Hand out the i'th 16-byte slot under the semaphore; 0 if out of range. */
void *func_00246C60(unsigned int i) {
    char *p;
    func_00246B78();
    func_00100560(D_00550868[0]);
    if (i < 0x20) {
        goto ok;
    }
    func_00100540(D_00550868[0]);
    return 0;
ok:
    p = &D_00715D00[i * 16];
    func_00100540(D_00550868[0]);
    return p;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00246CD0);

extern int D_00550864[];
extern int func_00100520(int *self);

void func_00247088(void) {
    int self[8];
    if (D_00550864[0] == -1) {
        self[0x8 / 4] = 1;
        self[0x4 / 4] = 1;
        self[0x14 / 4] = 0;
        D_00550864[0] = func_00100520(self);
    }
}

int func_002470D8(int arg) {
    func_00247088();
    func_00100560(D_00550864[0]);
    return 0;
}

void func_00247108(void) {
    func_00100540(D_00550864[0]);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00247118);

extern char D_0027470C[];
extern int D_00550870[];
extern char D_00715F28[];
extern int func_00264094();

int func_002472B8(void) {
    char *s3 = D_0027470C;
    char *s1 = D_00715F28;
    int s2 = 0;
    int v0;
    v0 = func_00264094(s1, s3, 4);
    if (v0 == 0) goto done;
    v0 = func_00264094(s1, (char *)D_00550870[0], 4);
    if (v0 == 0) goto done;
    v0 = func_00264094(s3, (char *)D_00550870[0], 4);
    s2 = (unsigned)0 < (unsigned)v0;
done:
    return s2;
}

extern int D_00550860[];
extern void func_002641D8(void *a0, int a1, int a2);

int func_00247348(void) {
    D_00550860[0] = 0;
    func_002641D8(D_00715F28, 0, 4);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00247380);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00247608);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00247788);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002479C0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00247C30);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00247EF0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00248240);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00248418);

extern int func_00248418(void *a0, int a1);

int func_002485C0(void *a0) {
    return func_00248418(a0, 6);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002485E0);

int func_00248790(void *a0) {
    return func_00248418(a0, 8);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002487B0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00248A20);

int func_00248B40(void *a0) {
    return func_00248418(a0, 0x10);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00248B60);

extern int D_00714C40[];
extern int D_00715880[];
extern int D_00715F00[];
extern int func_00100530(int a0);
extern int func_00246458();
extern void *func_00246C60(unsigned int a0);

int func_00248C00(unsigned int a0) {
    extern int func_00100520(int *a0);
    extern int func_00100560(int a0);
    int *g = D_00714C40;
    void *obj;
    int f0;
    int uv;
    int h;
    int rc;
    int result;
    int buf[8];

    obj = func_00246C60(a0);
    func_002470D8(0xA);
    if (D_00550860[0] == 0) {
        func_00247108();
        return -1;
    }
    if (obj == 0 || ((int *)obj)[1] == 0) {
        func_00247108();
        return -9;
    }
    f0 = ((int *)obj)[0];
    g[3] = f0;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_00714C40[0] = h = func_00100520(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = func_00246458(D_00715F00, 0xA, 0, g, 0x14, D_00715880, 4, 0, 0);
    if (rc < 0) {
        func_00100530(h);
        func_00247108();
        return -0xB;
    }
    ((int *)obj)[1] = 0;
    uv = *(int *)((int)D_00715880 | 0x20000000);
    func_00247108();
    if (uv == 0) {
        func_00100530(h);
        return -0xB;
    }
    func_00100560(h);
    func_00100530(h);
    if (result < 0) {
        return result;
    }
    return 0;
}

int func_00248D68(unsigned int a0, int a1) {
    extern int func_00100520(int *a0);
    extern int func_00100560(int a0);
    int *g = D_00714C40;
    void *obj;
    int f0;
    int uv;
    int rc;
    int result;
    int buf[8];

    obj = func_00246C60(a0);
    func_002470D8(0xB);
    if (D_00550860[0] == 0) {
        func_00247108();
        return -1;
    }
    if (obj == 0 || ((int *)obj)[1] == 0) {
        func_00247108();
        return -9;
    }
    f0 = ((int *)obj)[0];
    g[4] = a1;
    g[3] = f0;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_00714C40[0] = a1 = func_00100520(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = func_00246458(D_00715F00, 0xB, 0, g, 0x20, D_00715880, 4, 0, 0);
    if (rc < 0) {
        func_00100560(a1);
        func_00247108();
        return -0xB;
    }
    uv = *(int *)((int)D_00715880 | 0x20000000);
    func_00247108();
    if (uv == 0) {
        func_00100530(a1);
        return -0xB;
    }
    func_00100560(a1);
    func_00100530(a1);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00248EC0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00249060);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002492A0);

int func_00249490(void *a0) {
    return func_00248418(a0, 0x12);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002494B0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00249648);

int func_002498B8(void *a0) {
    return func_00248418(a0, 0x15);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_002498D8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00249B10);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00249D40);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_00249F20);

extern int D_00550874[];
extern int D_00715F80[];
extern char D_FFFFF[];
extern int func_00246288__p4() __asm__("func_00246288");

int func_0024A0E8(void)
{
    int i;
    int ret;
    int val;
    goto no_delay;
again:
    __asm__ volatile ("lui %0,%%hi(D_FFFFF)" : "=r"(i));
    do {
        __asm__ volatile ("addiu %0,%0,%%lo(D_FFFFF)" : "+r"(i));
    } while (i != -1);
no_delay:
    ret = func_00246288__p4(D_00715F80, 0x80000003, 0);
    if (ret < 0) return -1;
    val = D_00715F80[0x24 / 4];
    if (val == 0) goto again;
    D_00550874[0] = 0;
    __asm__ volatile ("");
    return 0;
}

extern int D_00550874[];
extern int D_00715F80[];
extern int D_00715FC0[];
extern int D_00716000[];

int func_0024A170(int a0) {
    int ret = D_00550874[0];
    if (ret < 0) return 0;
    D_00716000[0] = a0;
    ret = func_00246458(D_00715F80, 1, 0, D_00716000, 4, D_00715FC0, 4, 0, 0);
    if (ret >= 0) return D_00715FC0[0];
    return 0;
}

extern int D_00716040[];

int func_0024A1E0(int a0) {
    int v2 = D_00550874[0];
    if (v2 < 0) return 0;
    D_00716040[0] = a0;
    v2 = func_00246458(D_00715F80, 2, 0, D_00716040, 4, D_00715FC0, 4, 0, 0);
    if (v2 < 0) return -1;
    return D_00715FC0[0];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_0024A258);

extern int D_00550878[];
extern char D_00716180[];
extern char D_00716380[];
extern char D_007163A8[];

int func_0024A348(void) {
    int i;
    int r;
    int val;
    if (D_00550878[0] >= 0) goto ret0;
loop:
    r = func_00246288__p4(D_00716380, 0x80000006, 0);
    if (r < 0) return -1;
    val = *(int *)(D_00716380 + 0x24);
    if (val == 0) goto delay;
    D_00550878[0] = 0;
    r = func_00246458(D_00716380, 0xFF, 0, 0, 0, D_00716180, 4, 0, 0);
    if (r < 0) return 0xFFFEFFFF;
    __builtin_memcpy(D_007163A8, D_00716180, 4);
    return 0;
delay:
    __asm__ volatile ("lui %0,%%hi(D_FFFFF)" : "=r"(i));
    do {
        __asm__ volatile ("addiu %0,%0,%%lo(D_FFFFF)" : "+r"(i));
    } while (i != -1);
    goto loop;
ret0:
    return 0;
}

extern int D_0055087C[];
extern char D_007163A8[];

int func_0024A448(void) {
    void *s3 = D_0027470C;
    void *s1 = D_007163A8;
    int s2 = 0;
    int v;
    if (func_00264094(s1, (int)s3, 4) == 0) goto done;
    v = D_0055087C[0];
    if (func_00264094(s1, v, 4) == 0) goto done;
    v = D_0055087C[0];
    s2 = (0 < (unsigned int)func_00264094(s3, v, 4));
done:
    return s2;
}

extern int D_00550878[];

int func_0024A4D8(void) {
    D_00550878[0] = -1;
    func_002641D8(D_007163A8, 0, 4);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_0024A510);

extern int func_0024A510(void *a0, int a1, int a2, void *a3);

void func_0024A718(void *a0, int a1, int a2) {
    int local[4];
    func_0024A510(a0, a1, a2, &local);
}

int func_0024A738(void *a0, int a1, int a2, void *a3) {
    return func_0024A510(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_0024A758);

extern void func_0024A758(void *a0, int a1, int a2, int a3, int a4);

void func_0024A980(void *a0, int a1, int a2) {
    int local;
    func_0024A758(a0, a1, a2, (int)&local, 0);
}

void func_0024A9A0(void *a0, int a1, int a2, int a3) {
    do {
        func_0024A758(a0, a1, a2, a3, 0);
    } while (0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2453C0", func_0024A9C0);
