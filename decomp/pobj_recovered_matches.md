# PObj recovered matches (salvaged from the cancelled bulk campaign)

These are byte-match attempts for `common/src/PObj.c` recovered after the
bulk-orchestration experiment was cancelled. They are NOT yet integrated.
Integrate them ONE AT A TIME via the normal workflow (flip the yaml subsegment,
write src, quick_diff, ninja, commit), re-verifying each — the bulk merge is gone.

Provenance tags: scratch matches were reloc-normalized count=0 in worker context;
conversation-recovered ones were displayed during recovery and need re-verification.


---

# MATCHED (verify on integration) (50)


## func_0023EA68 — MATCHED
### decls
```c

```
### code
```c
int func_0023EA68(void *a0, int a1) {
    int s0 = a1 & 1;
    int ret;
    func_0023E440((char *)a0 + s0 * 0x28);
    if (!s0) goto zero_path;
    ret = func_0023E6E8((char *)a0 + 0x140);
    goto done;
zero_path:
    ret = func_0023E6E8((char *)a0 + 0x50);
done:
    return ret;
}
```
### notes
Recovered from scratch/w1 (match_diff count=0).


## func_00240578 — MATCHED
### decls
```c

```
### code
```c
void func_00240578(void *a0, void *a1, void *a2, void *a3, void *a4) {
    func_00240080(a0, a1);
    func_00240080((char *)a0 + 0x10, a2);
    func_00240080((char *)a0 + 0x20, a3);
    func_00240080((char *)a0 + 0x30, a4);
}
```
### notes
Recovered from scratch/w4 (match_diff count=0).


## func_00240980 — MATCHED
### decls
```c
```
### code
```c
int func_00240980(void *a0) {
    register int r __asm__("$2");
    __asm__ __volatile__(
        ".set noreorder\n"
        "vsub.xyzw $vf4, $vf0, $vf0\n"
        "lui $2, 0x4580\n"
        "dsll $2, $2, 16\n"
        "ori $2, $2, 0x4580\n"
        "dsll $2, $2, 16\n"
        "lqc2 $vf7, 0x0($4)\n"
        "qmtc2.ni $2, $vf6\n"
        "ctc2.ni $0, $vi16\n"
        "vsub.xyw $vf5, $vf7, $vf4\n"
        "vsub.xy $vf5, $vf6, $vf7\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2.ni $2, $vi16\n"
        ".set reorder\n"
        : "=r"(r));
    return r & 0xC0;
}
```
### notes
Recovered from conversation. VU0 bounding-test, $2-bound asm. Re-verify on integration.


## func_002409C8 — MATCHED
### decls
```c
```
### code
```c
int func_002409C8(void *a0, void *a1, void *a2) {
    register int ret __asm__("$2");
    __asm__ __volatile__(
        "vsub.xyzw $vf4, $vf0, $vf0\n"
        "lui $2, 0x4580\n"
        "dsll $2, $2, 16\n"
        "ori $2, $2, 0x4580\n"
        "dsll $2, $2, 16\n"
        "lqc2 $vf6, 0x0($4)\n"
        "lqc2 $vf8, 0x0($5)\n"
        "lqc2 $vf9, 0x0($6)\n"
        "qmtc2.ni $2, $vf7\n"
        "ctc2.ni $0, $vi16\n"
        "vsub.xyw $vf5, $vf6, $vf4\n"
        "vsub.xy $vf5, $vf7, $vf6\n"
        "vsub.xyw $vf5, $vf8, $vf4\n"
        "vsub.xy $vf5, $vf7, $vf8\n"
        "vsub.xyw $vf5, $vf9, $vf4\n"
        "vsub.xy $vf5, $vf7, $vf9\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2.ni $2, $vi16\n"
        "andi $2, $2, 0xC0\n"
        : "=r"(ret));
    return ret;
}
```
### notes
Recovered from conversation. 3-point VU0 test. Re-verify on integration.


## func_00240AB8 — MATCHED
### decls
```c
extern int D_0054A9B0[];
```
### code
```c
void func_00240AB8(void) {
    typedef unsigned int u128 __attribute__((mode(TI)));
    register int v __asm__("$8");

    *(volatile int *)0x10003830 = 0;
    *(volatile int *)0x10003820 = 0;
    *(volatile int *)0x10003810 = 1;

    __asm__ __volatile__(
        ".set noreorder\n"
        "cfc2.ni $8, $vi28\n"
        "ori $8, $8, 0x2\n"
        "ctc2.ni $8, $vi28\n"
        "sync.p\n"
        ".set reorder\n"
        : "=r"(v) : : "memory"
    );

    {
        volatile u128 *dst = (volatile u128 *)0x10004000;
        u128 *src = (u128 *)D_0054A9B0;
        *dst = src[0];
        *dst = src[1];
    }
}
```
### notes
Recovered from conversation. VU0 ctc2 + mode(TI) qword copies to GIF FIFO. Re-verify on integration.


## func_00241698 — MATCHED
### decls
```c
extern int func_002415E8(void *a0);
```
### code
```c
void func_00241698(int *a1, unsigned int a2) {
    int *a0;
    int s0;
    int v0;
    v0 = func_002415E8(a1);
    a0 = (int *)a1[0];
    do { s0 = a2 | 0x70000000; } while (0);
    a1[2] = v0;
    a0[0] = s0;
    a0++;
    a1[3] = 0;
    a1[0] = (int)(a0 + 1);
    a0[0] = 0;
}
```
### notes
Recovered from conversation. do-while(0) BB split. Re-verify on integration.


## func_00242978 — MATCHED
### decls
```c
extern int D_007115C0[];
extern int D_00711280[];
extern int D_0054C648[];
```
### code
```c
extern int func_00242978(int *a0, int a1, int a2, int *a3, int a4, int *a5, int a6, int a7, int a8);

int func_0024A538(void) {
    int ret;
    int val;
    D_007115C0[0] = 0xF;
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = D_007115C0[3];
    if (val != 1) {
        return val;
    }
    D_0054C648[0] = 0;
    return 1;
}
```
### notes
Recovered from scratch/w7 (match_diff count=0).


## func_002437D8 — MATCHED
### decls
```c

```
### code
```c
int func_002437D8(void) {
    char *s3 = D_00270A8C;
    char *s1 = D_0070F5A8;
    int s2 = 0;
    int v0;
    v0 = func_00260424(s1, s3, 4);
    if (v0 == 0) goto done;
    v0 = func_00260424(s1, (char *)D_0054AB30[0], 4);
    if (v0 == 0) goto done;
    v0 = func_00260424(s3, (char *)D_0054AB30[0], 4);
    s2 = (unsigned)0 < (unsigned)v0;
done:
    return s2;
}
```
### notes
Recovered from scratch/w1 (match_diff count=0).


## func_00246690 — MATCHED
### decls
```c

```
### code
```c
int func_00246690(int a0) {
    int ret = D_0054AB34[0];
    if (ret < 0) return 0;
    D_0070F680[0] = a0;
    ret = func_00242978(D_0070F600, 1, 0, D_0070F680, 4, D_0070F640, 4, 0, 0);
    if (ret >= 0) return D_0070F640[0];
    return 0;
}
```
### notes
Recovered from scratch/w6 (match_diff count=0).


## func_00246700 — MATCHED
### decls
```c
extern int D_0054AB34[];
extern int D_0070F6C0[];
extern int D_0070F600[];
extern int D_0070F640[];
```
### code
```c
int func_00246700(int a0) {
    int v2 = D_0054AB34[0];
    if (v2 < 0) return 0;
    D_0070F6C0[0] = a0;
    v2 = func_00242978(D_0070F600, 2, 0, D_0070F6C0, 4, D_0070F640, 4, 0, 0);
    if (v2 < 0) return -1;
    return D_0070F640[0];
}
```
### notes
Recovered from scratch/w1 (match_diff count=0).


## func_00246968 — MATCHED
### decls
```c

```
### code
```c
int func_00246968(void) {
    void *s3 = D_00270A8C;
    void *s1 = D_0070FA28;
    int s2 = 0;
    int v;
    if (func_00260424(s1, (int)s3, 4) == 0) goto done;
    v = D_0054AB3C[0];
    if (func_00260424(s1, v, 4) == 0) goto done;
    v = D_0054AB3C[0];
    s2 = (0 < (unsigned int)func_00260424(s3, v, 4));
done:
    return s2;
}
```
### notes
Recovered from scratch/w2 (match_diff count=0).


## func_00247820 — MATCHED
### decls
```c
extern int D_0054AB40[];
extern void func_00247A00(void);
extern void func_001001D0(int a0, void *a1);
```
### code
```c
void *func_00247820(void *a0) {
    D_0054AB40[0] = (int)a0;
    func_001001D0(1, func_00247A00);
    func_001001D0(2, func_00247A00);
    func_001001D0(3, func_00247A00);
    return a0;
}
```
### notes
void* return keeps value in v0; three identical calls with different integer arg; function pointer passed as void*.


## func_00247880 — MATCHED
### decls
```c

```
### code
```c
int func_00247880(int a0, int a1) {
    int old;
    int orig = a0;
    unsigned int err = 0xFFFFFFFF;
    if ((unsigned)(a0 - 1) >= 13) {
        return (int)err;
    }
    old = D_0054AB48[orig];
    D_0054AB48[orig] = a1;
    if ((unsigned)(a0 - 1) < 3) {
        func_001001D0(orig, (void *)&func_00247C40);
    } else {
        func_001001E0(orig, (void *)&func_00247C40);
    }
    return old;
}
```
### notes
Recovered from scratch/w5 (match_diff count=0).


## func_00247A00 — MATCHED
### decls
```c
extern int D_0054AB40[];
```
### code
```c
extern void func_00247A00(void);
extern void func_001001D0(int a0, void *a1);

void *func_00247820(void *a0) {
    D_0054AB40[0] = (int)a0;
    func_001001D0(1, func_00247A00);
    func_001001D0(2, func_00247A00);
    func_001001D0(3, func_00247A00);
    return a0;
}
```
### notes
Recovered from scratch/w2 (match_diff count=0).


## func_002484A4 — MATCHED
### decls
```c

```
### code
```c
extern void func_002484A4(void);
extern int func_00100520(void *a0);
extern int func_001002A0(int a0, void *a1, int a2);
extern void func_00100530(int a0);

void func_002484D0(int a0) {
    int buf[6];
    int id;
    int mask;
    mask = a0 & 0xFFFF;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    id = func_00100520(buf);
    func_001002A0(mask, (char *)&func_002484A4 + 4, id);
    func_00100560(id);
    func_00100530(id);
}
```
### notes
Recovered from scratch/w5 (match_diff count=0).


## func_002484D0 — MATCHED
### decls
```c
extern int D_0054ABD0[];
extern int D_006289D8[];
extern void func_001019E0(void *a0);
extern int D_0054ABF0[];
extern char D_0054BD90[];
```
### code
```c
extern void func_002484D0(int a0);

int func_002490C0(int a0) {
    if (a0 == 0) {
        if (D_0054ABD0[0] > 0) {
            func_001019E0(D_006289D8);
        }
        do {
            while (D_0054ABF0[0] != 0) {
                func_002484D0(0x3C);
            }
        } while (func_00242B68(D_0054BD90));
        return 0;
    }
    if (D_0054ABF0[0] != 0) {
        return 1;
    }
    if (func_00242B68(D_0054BD90)) {
        return 1;
    }
    return 0;
}
```
### notes
Recovered from scratch/w7 (match_diff count=0).


## func_00249160 — MATCHED
### decls
```c

```
### code
```c
int func_00249160(int a0) {
    if (!a0) {
        if (D_0054ABD0[0] > 0) func_001019E0(D_006289E8);
        while (func_00242B68(D_0054C608)) {
            func_002484D0(0x3C);
        }
        return 0;
    }
    return func_00242B68(D_0054C608);
}
```
### notes
Recovered from scratch/w8 (match_diff count=0).


## func_0024A858 — MATCHED [D_007112D0 cluster — needs shared-struct reconciliation]
### decls
```c
extern int D_007112D0[];
extern void func_0026B730(void *a0, void *a1);
```
### code
```c
int func_0024A858(int a0, int a1) {
    int s0;
    int v0, v1, r;
    s0 = *(int *)((char *)D_007112D0 + a1 * 0x1C + a0 * 0x70);
    func_0026B730((char *)s0, (char *)s0 + 0x100);
    v0 = *(int *)(s0 + 0x58);
    v1 = *(int *)(s0 + 0xD8);
    r = (v0 < v1);
    return s0 + (r << 7);
}
```
### notes
Recovered from conversation. Callers treat the return as a pointer -> may need `char *` return on reconciliation. Re-verify on integration.


## func_0024A8B8 — MATCHED [D_007112D0 cluster]
### decls
```c
typedef struct { char pad0[0x10]; int f10; char pad14[0x8]; } PObjA8B8Ent; /* 0x1C */
extern PObjA8B8Ent D_007112D0[][4];
extern char *func_0024A858(int a0, int a1);
```
### code
```c
int func_0024A8B8(int a0, int a1) {
    int ret = 0;
    if (D_007112D0[a0][a1].f10 == 0) {
        return ret;
    }
    return *(int *)(func_0024A858(a0, a1) + 0x58);
}
```
### notes
Recovered from conversation. 0x1C-stride 2D array; `int ret=0; if(==0)return ret;` form. Re-verify on integration.


## func_0024A908 — MATCHED [D_007112D0 cluster]
### decls
```c
extern int D_007112D0[];
extern int func_002604B8(int *a0, int *a1, int a2);
```
### code
```c
int func_0024A908(int a0, int a1, int a2) {
    int idx;
    int *p;
    int *s0;
    idx = a0 * 0x70 + a1 * 0x1C;
    p = D_007112D0 + idx/4;
    if (!p[0x10/4]) {
        return 0;
    }
    s0 = func_0024A858(a0);
    return func_002604B8(s0, s0, *(int*)(((char*)s0) + 0x60));
}
```
### notes
Recovered from conversation. Calls func_0024A858 with 1 arg (matched when callee was INCLUDE_ASM); reconcile to 2 args. Re-verify on integration.


## func_0024AA00 — MATCHED
### decls
```c
extern int D_0054C650[];
extern unsigned char D_00628D28[];
extern void func_002614F8(char *a0, int a1);
```
### code
```c
void func_0024AA00(int a0, char *a1) {
    if ((unsigned int)a0 < 8) {
        func_002614F8(a1, D_0054C650[a0]);
    } else {
        *a1 = D_00628D28[0];
    }
}
```
### notes
Recovered from conversation. Re-verify on integration.


## func_0024AA38 — MATCHED
### decls
```c

```
### code
```c
extern int func_0024AA38(int a0, int a1, int a2);

int func_0024B010(int a0, int a1, char *a2) {
    int *s0 = D_007115C0;
    int i;
    int val;
    int ret;
    D_007115C0[0] = 8;
    s0[1] = a0;
    s0[2] = a1;
    for (i = 0; i < 6; i++) {
        ((char *)s0)[0xC + i] = a2[i];
    }
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = s0[5];
    if (val == 1) {
        func_0024AA38(a0, a1, 2);
        val = s0[5];
    }
    return val;
}
```
### notes
Recovered from scratch/w7 (match_diff count=0).


## func_0024AAA0 — MATCHED [D_007112D0 cluster]
### decls
```c
typedef struct { int unk0,unk4,unk8,unkC,unk10,unk14,unk18; } PObjAAA0Elem;
extern PObjAAA0Elem D_007112D0[][4];
extern char *func_0024A858(int a0, int a1);
```
### code
```c
int func_0024AAA0(int a0, int a1) {
    if (D_007112D0[a0][a1].unk10 == 0) {
        return 0;
    }
    return func_0024A858(a0, a1)[0x71];
}
```
### notes
Recovered from conversation. Re-verify on integration.


## func_0024AAF0 — MATCHED
### decls
```c
extern int D_0054C670[];
extern unsigned char D_00628D28[];
extern void func_002614F8(char *a0, int a1);
```
### code
```c
void func_0024AAF0(int a0, char *a1) {
    if ((unsigned int)a0 < 4) {
        func_002614F8(a1, D_0054C670[a0]);
    } else {
        *a1 = D_00628D28[0];
    }
}
```
### notes
Recovered from conversation. Re-verify on integration.


## func_0024AEA0 — MATCHED
### decls
```c
extern int D_007115C0[];
extern int D_00711280[];
extern int func_00242978(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
```
### code
```c
int func_0024AEA0(int a0, int a1, int a2, int a3) {
    int *s0 = D_007115C0;
    int local = 0;
    int ret;
    int s;
    D_007115C0[0] = 6;
    s0[1] = a0;
    s0[2] = a1;
    s0[3] = a2;
    s0[4] = a3;
    ret = func_00242978((int)D_00711280, 1, 0, (int)s0, 0x80, (int)s0, 0x80, 0, local);
    if (ret < 0) {
        return 0;
    }
    s = s0[5];
    if (s == 1) {
        func_0024AA38(a0, a1, 2);
        s = s0[5];
    }
    return s;
}
```
### notes
Recovered from conversation. Re-verify on integration.


## func_0024B2B0 — MATCHED [D_007112D0 cluster]
### decls
```c
extern int func_0024B1A0(int a0, int a1, int a2);
```
### code
```c
int func_0024B2B0(int a0, int a1) {
    if (D_007112D0[a0][a1].unk10 == 0) {
        return 0;
    }
    return func_0024B1A0(a0, a1, 0xFFF);
}
```
### notes
Recovered from conversation (uses cluster struct D_007112D0[][4] with .unk10). Re-verify on integration.


## func_0024B308 — MATCHED [D_007112D0 cluster]
### decls
```c
extern int func_0024B1A0(int a0, int a1, int a2);
```
### code
```c
int func_0024B308(int a0, int a1) {
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    return func_0024B1A0(a0, a1, 0);
}
```
### notes
Recovered from conversation (uses cluster struct D_007112D0[][4] with .f10). Re-verify on integration.


## func_0024B498 — MATCHED
### decls
```c

```
### code
```c
int func_0024B498(int a0) {
    int ret;
    D_007115C0[0] = 0xD;
    D_007115C0[1] = a0;
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[3];
}
```
### notes
Recovered from scratch/w6 (match_diff count=0).


## func_0024DE80 — MATCHED
### decls
```c

```
### code
```c
int func_0024DE80(int *a0, unsigned int a1, int a2) {
    int *p = (int *)a0[0x40/4];
    a1 = (a1 & 0x0FFFFFFF) | 0x20000000;
    p[0xB0/4] = 1;
    p[0xD8/4] = a1;
    p[0xE4/4] = a2;
    p[0xE0/4] = 0;
    p[0xDC/4] = 0;
    return func_0024E260((int)a0);
}
```
### notes
Recovered from scratch/w2 (match_diff count=0).


## func_0024E740 — MATCHED
### decls
```c

```
### code
```c
void func_0024E740(int a0) {
    int t;
    if (D_0054C89C[0]) {
        func_0024E920(D_00628EA8);
        D_0054C89C[0] = 0;
        return;
    }
    t = D_0054C92C[0];
    if (t == 3) {
        func_00253DB0(D_0054C784[0], a0 - 1);
    } else {
        func_00253EC8(D_0054C790[0], D_0054C79C[0], a0 - 1);
    }
    D_0054C89C[0] = 0;
}
```
### notes
Recovered from scratch/w7 (match_diff count=0).


## func_002529D8 — MATCHED
### decls
```c

```
### code
```c
void func_002529D8(void) {
    int v;
    func_00252310();
    {
        register volatile int *ptr __asm__("$2") = (volatile int *)0x10002020;
        v = (-((*ptr) & 7)) & 7;
    }
    if (v) func_00252758(v);
    while (func_00252620(0x18) != 1) {
        func_00252758(8);
    }
}
```
### notes
Recovered from scratch/w8 (match_diff count=0).


## func_00253DB0 — MATCHED
### decls
```c
extern int D_0054C89C[];
extern int D_0054C92C[];
extern int D_00628EA8[];
extern int D_0054C784[];
extern int D_0054C790[];
extern int D_0054C79C[];
```
### code
```c
extern void func_00253DB0(int a0, int a1);
extern void func_00253EC8(int a0, int a1, int a2);

void func_0024E740(int a0) {
    int t;
    if (D_0054C89C[0]) {
        func_0024E920(D_00628EA8);
        D_0054C89C[0] = 0;
        return;
    }
    t = D_0054C92C[0];
    if (t == 3) {
        func_00253DB0(D_0054C784[0], a0 - 1);
    } else {
        func_00253EC8(D_0054C790[0], D_0054C79C[0], a0 - 1);
    }
    D_0054C89C[0] = 0;
}
```
### notes
Recovered from scratch/w7 (match_diff count=0).


## func_00253EC8 — MATCHED
### decls
```c
extern int D_0054C89C[];
extern int D_0054C92C[];
extern int D_00628EA8[];
extern int D_0054C784[];
extern int D_0054C790[];
extern int D_0054C79C[];
extern void func_00253DB0(int a0, int a1);
```
### code
```c
extern void func_00253EC8(int a0, int a1, int a2);

void func_0024E740(int a0) {
    int t;
    if (D_0054C89C[0]) {
        func_0024E920(D_00628EA8);
        D_0054C89C[0] = 0;
        return;
    }
    t = D_0054C92C[0];
    if (t == 3) {
        func_00253DB0(D_0054C784[0], a0 - 1);
    } else {
        func_00253EC8(D_0054C790[0], D_0054C79C[0], a0 - 1);
    }
    D_0054C89C[0] = 0;
}
```
### notes
Recovered from scratch/w7 (match_diff count=0).


## func_00258168 — MATCHED
### decls
```c

```
### code
```c
void func_00258168(void *a0) {
    void *s0 = a0;
    void *p = func_00255060();
    int t = *(unsigned short *)((char *)s0 + 0x28);
    int val;
    int pval;
    if (t == 1) goto case1;
    if (t >= 2) goto ge2;
    if (t == 0) goto case0;
    goto done;
ge2:
    if (t == 2) goto case12;
    goto done;
case0: {
    int q0 = *(int *)((char *)p + 0x10);
    int b0 = *(unsigned char *)((char *)q0 + 0x2);
    *(short *)((char *)s0 + 0x2A) = 0;
    *(short *)((char *)s0 + 0x26) = b0;
    goto done;
}
case1:
case12: {
    int q12 = *(int *)((char *)p + 0x10);
    int b12 = *(unsigned char *)((char *)q12 + 0x2);
    *(short *)((char *)s0 + 0x2A) = b12;
}
done:
    val = *(int *)((char *)s0 + 0x4);
    *(int *)((char *)s0 + 0x4) = val + 3;
}
```
### notes
Recovered from scratch/w2 (match_diff count=0).


## func_00259DF8 — MATCHED
### decls
```c

```
### code
```c
void func_00259DF8(unsigned int a0, int a1) {
    volatile int *p;
    int v, v2, v3;
    if (a0 >= 0x30) return;
    if (a1 < 0) return;
    if (a1 >= 0x4000) return;
    p = (volatile int *)func_00254FE0(a0);
    v = p[0];
    *(int *)((char *)p + 0x40) = a1;
    v |= 0x2000;
    p[0] = v;
    v2 = p[0];
    v2 |= 0x400;
    p[0] = v2;
    v3 = p[0];
    v3 = (int)((unsigned int)v3 & 0xFFFFDFFFU);
    p[0] = v3;
}
```
### notes
Recovered from scratch/w2 (match_diff count=0).


## func_0025A3E0 — MATCHED
### decls
```c

```
### code
```c
int func_0025A3E0(int *a0) {
    unsigned int n1, n2;
    int v, v2, ret;
    ret = -1;
    n1 = a0[2];
    if ((unsigned int)0x1FFFFF < n1) goto done;
    n2 = a0[3];
    if ((unsigned int)0x1FFFFF < n2) goto done;
    v = a0[0];
    if (v < 0) goto done;
    if (v < 0x10) {
        v2 = a0[1];
        func_00255580(0x48, (v << 24) | v2, n1, n2);
        ret = 0;
    }
    done:
    return ret;
}
```
### notes
Recovered from scratch/w4 (match_diff count=0).


## func_0025FBD0 — MATCHED
### decls
```c

```
### code
```c
int func_0025FBD0(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    func_0025F8B0(buf + 0x30, buf);
    func_0025F8B0(buf + 0x34, buf + 0x10);
    *(int *)(buf + 0x14) ^= 1;
    ret = func_0025F940(buf, buf + 0x10, buf + 0x20);
    return func_0025F7A0(ret);
}
```
### notes
Recovered from scratch/w2 (match_diff count=0).


## func_00260424 — MATCHED
### decls
```c
extern char D_00270A8C[];
extern int D_0054AB3C[];
```
### code
```c
extern int func_00260424(void *a0, int a1, int a2);

int func_00246968(void) {
    void *s3 = D_00270A8C;
    void *s1 = D_0070FA28;
    int s2 = 0;
    int v;
    if (func_00260424(s1, (int)s3, 4) == 0) goto done;
    v = D_0054AB3C[0];
    if (func_00260424(s1, v, 4) == 0) goto done;
    v = D_0054AB3C[0];
    s2 = (0 < (unsigned int)func_00260424(s3, v, 4));
done:
    return s2;
}
```
### notes
Recovered from scratch/w2 (match_diff count=0).


## func_00260628 — MATCHED
### decls
```c
extern int func_00262D78(int *self, int a1, int b, void *args);
```
### code
```c
int func_00260628(int *self, int b, ...)
{
    void *args = (char *)__builtin_next_arg(b) - 0x30;
    return func_00262D78(self, self[2], b, args);
}
```
### notes
Recovered from conversation. Varargs forwarder (ee-gcc 2.9 next_arg idiom). Re-verify on integration.


## func_00260668 — MATCHED
### decls
```c
extern void func_00262D00(int a0, void *a1, void *args);
```
### code
```c
void func_00260668(void *a0, ...) {
    void *args = (char *)__builtin_next_arg(a0) - 0x38;
    int s = D_0054D504[0];
    *(int *)(*(int *)(s + 8) + 0x54) = s;
    func_00262D00(*(int *)(s + 8), a0, args);
}
```
### notes
Recovered from conversation. Varargs (1 named -> ap=next_arg-0x38). Needs D_0054D504 decl + any sibling decl of func_00260668 made varargs. Re-verify on integration.


## func_002610E0 — MATCHED
### decls
```c
extern void *D_0054D504_alias[] __asm__("D_0054D504");
```
### code
```c
void func_002610E0(int a0) {
    char *p = (char *)D_0054D504_alias[0];
    *(int *)(p + 0x58) = a0;
}
```
### notes
Recovered from conversation. asm-label alias for D_0054D504. Re-verify on integration.


## func_002610F0 — MATCHED
### decls
```c
extern void *D_0054D504_alias[] __asm__("D_0054D504");
```
### code
```c
int func_002610F0(void) {
    char *p = (char *)D_0054D504_alias[0];
    int s = *(int *)(p + 0x58) * 0x41C64E6D + 0x3039;
    *(int *)(p + 0x58) = s;
    return s & 0x7fffffff;
}
```
### notes
Recovered from conversation. LCG rng. Re-verify on integration.


## func_002611F8 — MATCHED
### decls
```c
```
### code
```c
int func_002611F8(void) {
    return 0;
}
```
### notes
Recovered from conversation. Re-verify on integration.


## func_002613B4 — MATCHED
### decls
```c
extern int D_0062A858[];
extern int D_0062A848[];
```
### code
```c
extern int func_002613B4(int a0, int *a1);

void *func_00267440(void *a0, int a1, int a2) {
    int *s1 = (int *)a0;
    if (a2 == 0) goto no_check;
    if (func_002613B4(a2, D_0062A858) == 0) goto found;
    if (func_002613B4(a2, D_0062A848) != 0) return 0;
found:
    *(int *)((char *)a0 + 0x30) = a1;
    *(int *)((char *)a0 + 0x34) = a2;
no_check:
    return D_0062A858;
}
```
### notes
Recovered from scratch/w6 (match_diff count=0).


## func_0026160C — MATCHED
### decls
```c

```
### code
```c
extern int func_0026160C(int a0);
extern int func_00264520(int *a0, int a1, char *a2);
extern int func_002611F8(void);

void func_00261200(int a0, int a1, ...) {
    int buf[22];
    int r;
    register int s0 __asm__("$16");
    s0 = a1;
    *(short *)((char *)buf + 0xC) = 4;
    buf[0] = a0;
    buf[4] = a0;
    r = func_0026160C(a0);
    buf[1] = r;
    buf[5] = r;
    buf[8] = (int)&func_002611F8;
    buf[21] = D_0054D504[0];
    buf[12] = 0;
    buf[17] = 0;
    func_00264520(buf, s0, (char *)__builtin_next_arg(a1) - 6*8);
}
```
### notes
Recovered from scratch/w5 (match_diff count=0).


## func_00261B10 — MATCHED
### decls
```c
```
### code
```c
char *func_00261B10(char *a0, char *a1) {
    char c0;
    int j;
    c0 = *a0;
    if (!c0) {
        return *a1 ? (char*)0 : a0;
    }
    if (!*a1) {
        return a0;
    }
    j = 0;
    while (*a0) {
        char h0 = a0[0];
        if (a1[j] != h0) {
            a0++;
            goto outer;
        }
        j++;
    inner:
        {
            char hj = a1[j];
            char nj;
            if (!hj) return a0;
            nj = a0[j];
            if (hj == nj) {
                j++;
                goto inner;
            }
        }
        a0++;
    outer:
        c0 = *a0;
    }
    return (char*)0;
}
```
### notes
Recovered from conversation. Substring search, goto-CFG matching bnel/beql loop (C89 decl-order fixed). Re-verify on integration.


## func_00262D00 — MATCHED
### decls
```c

```
### code
```c
extern void func_00262D00(void *a0, void *a1, void *a2);

void func_00261188(char *a0, int a1, ...) {
    int buf[22];
    int m;
    char *ap;
    ap = (char *)__builtin_next_arg(a1) - 6*8;
    m = 0x7FFFFFFF;
    buf[0] = (int)a0;
    buf[2] = m;
    *(short *)((char *)buf + 0xC) = 0x208;
    buf[4] = (int)a0;
    buf[5] = m;
    buf[0x15] = D_0054D504[0];
    func_00262D00(buf, a1, ap);
    *(char *)buf[0] = 0;
}
```
### notes
Recovered from scratch/w5 (match_diff count=0).


## func_00264520 — MATCHED
### decls
```c
extern int func_0026160C(int a0);
```
### code
```c
extern int func_00264520(int *a0, int a1, char *a2);
extern int func_002611F8(void);

void func_00261200(int a0, int a1, ...) {
    int buf[22];
    int r;
    register int s0 __asm__("$16");
    s0 = a1;
    *(short *)((char *)buf + 0xC) = 4;
    buf[0] = a0;
    buf[4] = a0;
    r = func_0026160C(a0);
    buf[1] = r;
    buf[5] = r;
    buf[8] = (int)&func_002611F8;
    buf[21] = D_0054D504[0];
    buf[12] = 0;
    buf[17] = 0;
    func_00264520(buf, s0, (char *)__builtin_next_arg(a1) - 6*8);
}
```
### notes
Recovered from scratch/w5 (match_diff count=0).


## func_00267440 — MATCHED
### decls
```c
extern int D_0062A858[];
extern int D_0062A848[];
extern int func_002613B4(int a0, int *a1);
```
### code
```c

void *func_00267440(void *a0, int a1, int a2) {
    int *s1 = (int *)a0;
    if (a2 == 0) goto no_check;
    if (func_002613B4(a2, D_0062A858) == 0) goto found;
    if (func_002613B4(a2, D_0062A848) != 0) return 0;
found:
    *(int *)((char *)a0 + 0x30) = a1;
    *(int *)((char *)a0 + 0x34) = a2;
no_check:
    return D_0062A858;
}
```
### notes
Reformatted from worker '## Final C' style. goto-CFG; in-TU reloc jals.


## func_0026B908 — MATCHED
### decls
```c
extern long func_0025D748_i(int a0) __asm__("func_0025D748");
extern int func_0025F4A0_i(int a0, int a1) __asm__("func_0025F4A0");
extern int func_0025EF10_i(int a0, int a1) __asm__("func_0025EF10");
```
### code
```c
long func_0026B908(int a0) {
    int save_a0 = a0;
    int zero = 0;
    int ret;
    __asm__("":"+r"(zero));
    ret = func_0025F4A0_i(save_a0, zero);
    if (ret < 0) {
        ret = func_0025EF10_i(zero, save_a0);
        return -func_0025D748_i(ret);
    }
    return func_0025D748_i(save_a0);
}
```
### notes
Recovered from conversation. asm-label aliases for differently-typed callees. Re-verify on integration.


---

# FAILED / near-miss (best attempts) (16)


## func_0023FB60 — FAILED (best: 12 diff lines)
### decls
```c
```
### code
```c
void func_0023FB60(void *a0, short a1, short a2, short a3) {
    unsigned long long v = *(unsigned long long *)((char *)a0 + 0x30);
    long long f2 = (long long)(int)((unsigned int)((v >> 48) & 0x7FF));
    long long f3 = (long long)(int)((unsigned int)((v >> 16) & 0x7FF));
    long long r2, r3;
    long long da2, da1;
    long long lo, hi;
    r2 = (unsigned long long)(f2 + 1) >> 1;
    r3 = (unsigned long long)(f3 + 1) >> 1;
    da2 = (long long)a2 - r2;
    da1 = (long long)a1 - r3;
    lo = da1;
    if (a3) {
        lo = da1 << 4;
        hi = (da2 << 4) + 8;
        hi <<= 32;
    } else {
        hi = da2 << 36;
    }
    *(long long *)((char *)a0 + 0x20) = lo | hi;
}
```
### notes
ROM uses `dsubu a2, a2, v0` keeping da2 in a2 (not v0); also addiu vs daddiu for +1; dsrl vs dsra for >>1. Field extraction order (f2 before f3) crucial for v0/v1 assignment. 12-diff floor after 10 attempts.


## func_002428E8 — FAILED (best: 2 diff lines)
### decls
```c

```
### code
```c
void func_002428E8(int *a0) {
    int *a5 = (int *)a0[13];
    int *a6 = (int *)a5[16];
    int *a2 = (int *)a6[3];
    if (a2 == 0) {
        a6[3] = (int)a5;
    } else {
        ((int *)a6[4])[15] = (int)a5;
    }
    a6[4] = (int)a5;
    a5[8] = a0[5];
    a5[7] = a0[7];
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
```
### notes
Near-miss recovered from scratch/w7; reloc-normalized count=2.


## func_00246608 — FAILED (best: 11 diff lines)
### decls
```c

```
### code
```c
int func_00246608(void) {
    int i;
    int cmp;
    int ret;
    int val;
    goto no_delay;
    again:
    i = (int)D_FFFFF;
    cmp = -1;
    L:
    i += (int)D_FFFFF & 0xFFFF;
    __asm__("nop\nnop\nnop\nnop");
    if (i != cmp) goto L;
    no_delay:
    ret = func_002427A8(D_0070F600, 0x80000003, 0);
    if (ret < 0) return -1;
    val = D_0070F600[0x24 / 4];
    if (val == 0) goto again;
    D_0054AB34[0] = 0;
    return 0;
}
```
### notes
Near-miss recovered from scratch/w4; reloc-normalized count=11.


## func_002490C0 — FAILED (best: 13 diff lines)
### decls
```c

```
### code
```c
int func_002490C0(int a0) {
    if (a0 == 0) {
        if (D_0054ABD0[0] > 0) {
            func_001019E0(D_006289D8);
        }
        do {
            while (D_0054ABF0[0] != 0) {
                func_002484D0(0x3C);
            }
        } while (func_00242B68(D_0054BD90));
        return 0;
    }
    if (D_0054ABF0[0] != 0) {
        return 1;
    }
    if (func_00242B68(D_0054BD90)) {
        return 1;
    }
    return 0;
}
```
### notes
Near-miss recovered from scratch/w7; reloc-normalized count=13.


## func_0024A538 — FAILED (best: 3 diff lines)
### decls
```c

```
### code
```c
int func_0024A538(void) {
    int ret;
    int val;
    D_007115C0[0] = 0xF;
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = D_007115C0[3];
    if (val != 1) {
        return val;
    }
    D_0054C648[0] = 0;
    return 1;
}
```
### notes
Near-miss recovered from scratch/w7; reloc-normalized count=3.


## func_0024A988 — FAILED (best: 22 diff lines)
### decls
```c
extern char D_007112D0[];
```
### code
```c
int func_0024A988(int a0, int a1) {
    char *base;
    char *ptr;
    unsigned char *p;
    int b, b2;
    base = D_007112D0 + a0 * 0x70;
    ptr = base + a1 * 0x1C;
    if (*(int *)(ptr + 0x10) == 0) return 0x63;
    p = (unsigned char *)func_0024A858(a0);
    b = p[0x70];
    if (b != 6) return b;
    b2 = p[0x71];
    if (b2 != 2) return p[0x70];
    return 5;
}
```
### notes
ROM uses mult1/mult pair (a0*0x70 via secondary pipeline, a1*0x1C via primary) with a0-save-to-a2 pattern; also needs bnel+lbu-delay at tail instead of conditional move. Could not reproduce either pattern in 10 attempts.


## func_0024B010 — FAILED (best: 19 diff lines)
### decls
```c

```
### code
```c
int func_0024B010(int a0, int a1, char *a2) {
    int *s0 = D_007115C0;
    int i;
    int val;
    int ret;
    D_007115C0[0] = 8;
    s0[1] = a0;
    s0[2] = a1;
    for (i = 0; i < 6; i++) {
        ((char *)s0)[0xC + i] = a2[i];
    }
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = s0[5];
    if (val == 1) {
        func_0024AA38(a0, a1, 2);
        val = s0[5];
    }
    return val;
}
```
### notes
Near-miss recovered from scratch/w7; reloc-normalized count=19.


## func_00251F98 — FAILED (best: 2 diff lines)
### decls
```c

```
### code
```c
void func_00251F98(int *a0, int a1, int a2, int a3, int a4) {
    int limit, base, delta;
    int *ptr = a0;
    limit = 16 << a1;
    base = *ptr;
    if (a4) base = base >> 1;
    if (a2 > 0) {
        base = base + 1 + ((a2 - 1) << a1) + a3;
        if (base >= limit) base = base - (limit << 1);
    } else if (a2 < 0) {
        base = base - 1;
        delta = (~a2 << a1) + a3;
        base = base - delta;
        if (base < -limit) base = base + (limit << 1);
    }
    *ptr = a4 ? base << 1 : base;
}
```
### notes
Near-miss recovered from scratch/w8; reloc-normalized count=2.


## func_00257380 — FAILED (best: 8 diff lines)
### decls
```c

```
### code
```c
void func_00257380(int *a0) {
    int *p;
    unsigned short idx;
    char *base;
    char *v2;
    if (*(a0 + 0) & 2) {
        p = (int *)func_00255060();
        idx = *(unsigned short *)((char *)a0 + 0x4E);
        v2 = (char *)(*(int *)((char *)p + 0x10));
        base = (char *)(*(int *)((char *)p + 8)) + (idx << 4);
        *(base + 0x12) = *(unsigned char *)(v2 + 1);
        idx = *(unsigned short *)((char *)a0 + 0x4E);
        base = (char *)(*(int *)((char *)p + 8)) + (idx << 4);
        *(base + 0x1A) = 0x40;
        idx = *(unsigned short *)((char *)a0 + 0x4E);
        base = (char *)(*(int *)((char *)p + 8)) + (idx << 4);
        *(base + 0x1B) = 0x40;
    }
    *(a0 + 1) += 2;
}
```
### notes
Near-miss recovered from scratch/w5; reloc-normalized count=8.


## func_0025A0B0 — FAILED (best: 16 diff lines)
### decls
```c

```
### code
```c
int func_0025A0B0(unsigned char *a0) {
    unsigned char *s0 = a0;
    unsigned int t2, a1, t0, t1, v0, a2, v1, a3, a0m;
    func_00254FF8();
    t2 = *(unsigned int *)(s0 + 12);
    a0m = 0xFF0000;
    t0 = 0xFF0000;
    a1 = s0[0];
    t1 = t2 >> 8;
    v0 = *(unsigned int *)(s0 + 4);
    t0 |= 0xFFFF;
    a2 = *(unsigned int *)(s0 + 0x10);
    a1 <<= 24;
    v1 = *(unsigned int *)(s0 + 0x14);
    v0 &= a0m;
    a3 = *(unsigned int *)(s0 + 8);
    a0m = a2 & 0xFF0000;
    a1 |= v0;
    v1 &= 0xFF00;
    a0m >>= 16;
    a1 |= v1;
    a3 &= t0;
    t1 &= 0xFFFF;
    t2 <<= 24;
    a2 <<= 16;
    a1 |= a0m;
    a2 |= t1;
    a3 = t2 | a3;
    func_00255580(0x3E, a1, a2, a3);
    return 0;
}
```
### notes
Near-miss recovered from scratch/w1; reloc-normalized count=16.


## func_00261120 — FAILED (best: 22 diff lines)
### decls
```c

```
### code
```c
void func_00261120(int a0, int a1, int a2, int a3,
                   int a4, int a5, int a6, int a7) {
    Rect261120 r;
    long long sargs[5] __attribute__((aligned(8)));
    r.idx = a0;
    sargs[0] = a3;
    sargs[1] = a4;
    sargs[2] = a5;
    sargs[3] = a6;
    sargs[4] = a7;
    r.type = 0x208;
    r.val = a1;
    r.max2 = 0x7FFFFFFF;
    r.p = (void *)a1;
    r.max = 0x7FFFFFFF;
    func_00262D00(&r, (void *)a2, sargs, (void *)a3);
    *(char *)r.p = 0;
}
```
### notes
Near-miss recovered from scratch/w3; reloc-normalized count=22.


## func_00261200 — FAILED (best: 7 diff lines)
### decls
```c

```
### code
```c
void func_00261200(int a0, int a1, ...) {
    int buf[22];
    int r;
    register int s0 __asm__("$16");
    s0 = a1;
    *(short *)((char *)buf + 0xC) = 4;
    buf[0] = a0;
    buf[4] = a0;
    r = func_0026160C(a0);
    buf[1] = r;
    buf[5] = r;
    buf[8] = (int)&func_002611F8;
    buf[21] = D_0054D504[0];
    buf[12] = 0;
    buf[17] = 0;
    func_00264520(buf, s0, (char *)__builtin_next_arg(a1) - 6*8);
}
```
### notes
Near-miss recovered from scratch/w5; reloc-normalized count=7.


## func_00265130 — FAILED (recovered, struct layout uncertain)
### decls
```c
typedef struct { int f00; int f04; int f08; int f0C; int f10; int f14; char pad18[0x3C]; int f54; } F65130Cmd;
extern void func_00262D00(void *cmd);
```
### code
```c
void func_00265130(int a0) {
    register int loaded __asm__("$8");
    register int saved_a0 __asm__("$7");
    F65130Cmd cmd;
    loaded = D_0054D504[0];
    saved_a0 = a0;
    cmd.f00 = saved_a0;
    cmd.f08 = 0x7FFFFFFF;
    cmd.f0C = 0x208;
    cmd.f10 = saved_a0;
    cmd.f14 = 0x7FFFFFFF;
    cmd.f54 = loaded;
    func_00262D00(&cmd);
    *(char *)cmd.f00 = 0;
}
```
### notes
Recovered from conversation. F65130Cmd struct layout reconstructed from accessed offsets (f00/f08/f0C/f10/f14/f54) — uncertain; func_00262D00 1-arg here conflicts with 3-arg view elsewhere. Re-derive struct + reconcile signature on integration.


## func_002667C8 — FAILED (partial recovery — body truncated)
### decls
```c
extern int func_00269A38(void *a0);
extern int func_002698E8(char *a0, int a1, int a2);
```
### code
```c
/* PARTIAL — only the opening stores were visible in the recovery conversation. */
void func_002667C8(char *a0, short a1, short a2, int a3) {
    *(int *)(a0 + 0x54) = a3;
    *(short *)(a0 + 0xC) = a1;
    *(short *)(a0 + 0xE) = a2;
    *(void **)(a0 + 0x20) = func_002698E8;
    *(void **)(a0 + 0x24) = func_00269950;
    *(void **)(a0 + 0x28) = func_002699D0;
    *(void **)(a0 + 0x2C) = func_00269A38;
    /* ... remainder unknown ... */
}
```
### notes
Vtable-init function; body truncated in the recovery source. Re-match from asm on integration.


## func_00269950 — FAILED (best: 2 diff lines)
### decls
```c

```
### code
```c
int func_00269950(void *a0, int a1, int a2) {
    unsigned short flag = *(unsigned short *)((char *)a0 + 0xC);
    if (flag & 0x100) {
        func_0026B058((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), 0, 2);
    }
    flag = *(unsigned short *)((char *)a0 + 0xC) & 0xEFFF;
    *(unsigned short *)((char *)a0 + 0xC) = flag;
    return func_0026AE80((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
}
```
### notes
Near-miss recovered from scratch/w8; reloc-normalized count=2.


## func_002699D0 — FAILED (best: 9 diff lines)
### decls
```c

```
### code
```c
int func_002699D0(char *a0, int a1, int a2) {
    int r;
    unsigned short f;
    long long rl;
    r = func_0026B058((int *)*(int *)(a0 + 0x54), *(short *)(a0 + 0xE), a1, a2);
    f = *(unsigned short *)(a0 + 0xC);
    if (r == -1) {
        f &= 0xEFFF;
    } else {
        rl = r;
        *(int *)(a0 + 0x50) = (int)rl;
        f |= 0x1000;
    }
    *(short *)(a0 + 0xC) = f;
    return r;
}
```
### notes
Near-miss recovered from scratch/w5; reloc-normalized count=9.
