#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size;  /* 0x4 */
} PObjBlk;
struct D520 {
    char pad0[8];
    PObjBlk *blk;       /* 0x8 */
};

typedef struct {
    char *pos;   /* 0x0 */
    int len;     /* 0x4 */
} StreamBuf;

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void func_002834F8(void);

void __assert(int a0, int a1, int a2) {
    fiprintf(*(int *)(D_0054CEAC[0] + 0xC), (int)D_00637E38, a2, a0, a1);
    func_002834F8();
}
extern long long strtol(void *a0, int a1, int a2);

int atoi(void *a0) {
    return (int)strtol(a0, 0, 0xA);
}
int __errno(void) {
    return D_0054CEAC[0];
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", fiprintf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", memcmp);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", memcpy);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global memset\n"
    "    .type memset, @function\n"
    "    .align 3\n"
    "memset:\n"
    "    sltiu  $2, $6, 0x8\n"
    "    bnez   $2, .Lmemset002641D8002605E8\n"
    "    daddu  $3, $4, $0\n"
    "    andi   $2, $4, 0xF\n"
    "    bnez   $2, .Lmemset002641D8002605E8\n"
    "    daddu  $7, $4, $0\n"
    "    andi   $9, $5, 0xFF\n"
    "    sltiu  $10, $6, 0x20\n"
    "    daddu  $8, $9, $0\n"
    "    dsll   $3, $8, 8\n"
    "    or     $8, $3, $9\n"
    "    pcpyh  $3, $8\n"
    "    bnez   $10, .Lmemset002641D8002605D4\n"
    "    sltiu  $2, $6, 0x8\n"
    "    pcpyld $8, $3, $3\n"
    "    .align 2\n"
    ".Lmemset002641D8002605A4:\n"
    "    sq     $8, 0x0($7)\n"
    "    addiu  $6, $6, -0x20\n"
    "    addiu  $7, $7, 0x10\n"
    "    sltiu  $2, $6, 0x20\n"
    "    sq     $8, 0x0($7)\n"
    "    beqz   $2, .Lmemset002641D8002605A4\n"
    "    addiu  $7, $7, 0x10\n"
    "    b      .Lmemset002641D8002605D4\n"
    "    sltiu  $2, $6, 0x8\n"
    "    .align 2\n"
    ".Lmemset002641D8002605C8:\n"
    "    addiu  $6, $6, -0x8\n"
    "    addiu  $7, $7, 0x8\n"
    "    sltiu  $2, $6, 0x8\n"
    "    .align 2\n"
    ".Lmemset002641D8002605D4:\n"
    "    nop\n"
    "    nop\n"
    "    beql   $2, $0, .Lmemset002641D8002605C8\n"
    "    sd     $3, 0x0($7)\n"
    "    daddu  $3, $7, $0\n"
    "    .align 2\n"
    ".Lmemset002641D8002605E8:\n"
    "    lui    $2, 0xFFFF\n"
    "    addiu  $6, $6, -0x1\n"
    "    ori    $2, $2, 0xFFFF\n"
    "    beq    $6, $2, .Lmemset002641D800260620\n"
    "    nop\n"
    "    lui    $2, 0xFFFF\n"
    "    ori    $2, $2, 0xFFFF\n"
    "    .align 2\n"
    ".Lmemset002641D800260604:\n"
    "    sb     $5, 0x0($3)\n"
    "    addiu  $6, $6, -0x1\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    bne    $6, $2, .Lmemset002641D800260604\n"
    "    addiu  $3, $3, 0x1\n"
    "    .align 2\n"
    ".Lmemset002641D800260620:\n"
    "    jr     $31\n"
    "    daddu  $2, $4, $0\n"
    "    .size memset, . - memset\n"
    "    .set reorder\n"
    "    .set at\n"
);
extern int _vfprintf_r(int *self, int subj, int b, void *args);

int _printf_r(int *self, int b, ...)
{
    void *args = (char *)__builtin_next_arg(b) - 0x30;
    return _vfprintf_r(self, self[2], b, args);
}
extern int vfprintf();

void printf(void *a0, ...) {
    void *args = (char *)__builtin_next_arg(a0) - 0x38;
    int s = D_0054CEAC[0];
    *(int *)(*(int *)(s + 8) + 0x54) = s;
    vfprintf(*(int *)(s + 8), a0, args);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", qsort);
void srand(int a0) {
    char *p = (char *)D_0054CEAC[0];
    *(int *)(p + 0x58) = a0;
}
int rand(void) {
    char *p = (char *)D_0054CEAC[0];
    int s = *(int *)(p + 0x58) * 0x41C64E6D + 0x3039;
    *(int *)(p + 0x58) = s;
    return s & 0x7fffffff;
}
int _sprintf_r(void *a0, int a1, int a2, ...) {
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(a2) - 40;
    int n;
    *(int *)(buf + 0x0) = a1;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = a1;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = (int)a0;
    n = vfprintf(buf, a2, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
    return n;
}
int sprintf(void *a0, int a1, ...) {
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(a1) - 48;
    int n;
    *(int *)(buf + 0x0) = (int)a0;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = (int)a0;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = D_0054CEAC[0];
    n = vfprintf(buf, a1, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
    return n;
}
int eofread(void) {
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", sscanf);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global strcat\n"
    "    .type strcat, @function\n"
    "    .align 3\n"
    "strcat:\n"
    "    addiu  $29, $29, -0x20\n"
    "    sq     $16, 0x0($29)\n"
    "    daddu  $16, $4, $0\n"
    "    andi   $2, $16, 0x7\n"
    "    bnez   $2, .Lstrcat0026137C\n"
    "    sq     $31, 0x10($29)\n"
    "    andi   $2, $16, 0xF\n"
    "    lui    $3, 0x101\n"
    "    ori    $3, $3, 0x101\n"
    "    dsll   $3, $3, 16\n"
    "    ori    $3, $3, 0x101\n"
    "    dsll   $3, $3, 16\n"
    "    ori    $3, $3, 0x101\n"
    "    lui    $4, 0x8080\n"
    "    ori    $4, $4, 0x8080\n"
    "    dsll   $4, $4, 16\n"
    "    ori    $4, $4, 0x8080\n"
    "    dsll   $4, $4, 16\n"
    "    ori    $4, $4, 0x8080\n"
    "    bnez   $2, .Lstrcat00261338\n"
    "    ld     $6, 0x0($16)\n"
    "    lq     $2, 0x0($16)\n"
    "    pcpyld $7, $3, $3\n"
    "    pcpyld $8, $4, $4\n"
    "    psubb  $3, $2, $7\n"
    "    pnor   $2, $0, $2\n"
    "    pand   $3, $3, $2\n"
    "    pand   $3, $3, $8\n"
    "    pcpyud $2, $3, $3\n"
    "    or     $3, $2, $3\n"
    "    bnez   $3, .Lstrcat0026137C\n"
    "    daddu  $4, $16, $0\n"
    "    addiu  $6, $4, 0x10\n"
    "    .align 2\n"
    ".Lstrcat0026130C:\n"
    "    lq     $2, 0x0($6)\n"
    "    pnor   $3, $0, $2\n"
    "    psubb  $2, $2, $7\n"
    "    pand   $2, $2, $3\n"
    "    pand   $2, $2, $8\n"
    "    pcpyud $3, $2, $2\n"
    "    or     $2, $2, $3\n"
    "    beql   $2, $0, .Lstrcat0026130C\n"
    "    addiu  $6, $6, 0x10\n"
    "    b      .Lstrcat0026137C\n"
    "    daddu  $4, $6, $0\n"
    "    .align 2\n"
    ".Lstrcat00261338:\n"
    "    daddu  $7, $3, $0\n"
    "    daddu  $8, $4, $0\n"
    "    dsubu  $3, $6, $3\n"
    "    nor    $2, $0, $6\n"
    "    and    $3, $3, $2\n"
    "    and    $3, $3, $4\n"
    "    bnez   $3, .Lstrcat0026137C\n"
    "    daddu  $4, $16, $0\n"
    "    addiu  $6, $16, 0x8\n"
    "    .align 2\n"
    ".Lstrcat0026135C:\n"
    "    ld     $2, 0x0($6)\n"
    "    nor    $3, $0, $2\n"
    "    dsubu  $2, $2, $7\n"
    "    and    $2, $2, $3\n"
    "    and    $2, $2, $8\n"
    "    beql   $2, $0, .Lstrcat0026135C\n"
    "    addiu  $6, $6, 0x8\n"
    "    daddu  $4, $6, $0\n"
    "    .align 2\n"
    ".Lstrcat0026137C:\n"
    "    lb     $2, 0x0($4)\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    bnel   $2, $0, .Lstrcat0026137C\n"
    "    addiu  $4, $4, 0x1\n"
    "    jal    strcpy\n"
    "    nop\n"
    "    daddu  $2, $16, $0\n"
    "    lq     $31, 0x10($29)\n"
    "    lq     $16, 0x0($29)\n"
    "    jr     $31\n"
    "    addiu  $29, $29, 0x20\n"
    "    .size strcat, . - strcat\n"
    "    .set reorder\n"
    "    .set at\n"
);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", strcmp);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", strcpy);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", strlen);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", strncmp);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", strncpy);
char *strrchr(char *s, char c) {
    char *last = 0;
    while (*s != 0) {
        if (*s == c) {
            last = s;
        }
        s++;
    }
    return (*s == c) ? s : last;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", strstr);
extern int func_0027FE08(int a0, int a1, int a2);

int strtok(int a0, int a1) {
    return func_0027FE08(a0, a1, D_0054CEAC[0] + 0x5C);
}
int func_0027FE08(int a0, int a1, int a2) {
    char *s = (char *)a0;
    char *delim = (char *)a1;
    char **last = (char **)a2;
    char *spanp;
    char *tok;
    int c;
    int sc;

    if (s == 0 && (s = *last) == 0) {
        return 0;
    }

cont:
    c = *s++;
    for (spanp = delim; (sc = *spanp++) != 0;) {
        if (c == sc) {
            goto cont;
        }
    }

    if (c == 0) {
        *last = 0;
        return 0;
    }
    tok = s - 1;

    for (;;) {
        c = *s++;
        spanp = delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0) {
                    s = 0;
                } else {
                    s[-1] = 0;
                }
                *last = s;
                return (int)tok;
            }
        } while (sc != 0);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", func_0027FEA8);
extern long long func_0027FEA8(void *a0, void *a1, int a2, int a3);

long long strtol(void *a0, int a1, int a2) {
    return func_0027FEA8((void *)D_0054CEAC[0], a0, a1, a2);
}
extern int __sfvwrite();

int __sprint(int a0, int *a1) {
    int ret;
    if (a1[2] == 0) {
        a1[1] = 0;
        return 0;
    }
    ret = __sfvwrite(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __sbprintf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", vfiprintf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _vfiprintf_r);
int func_00280E60(int a0, int *a1) {
    int ret;
    if (a1[2] == 0) {
        a1[1] = 0;
        return 0;
    }
    ret = __sfvwrite(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", func_00280EA8);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", vfprintf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _vfprintf_r);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", cvt);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", exponent);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __svfscanf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __sccl);
int vsprintf(void *out, void *a1, void *a2) {
    char s[0x60];
    int n;
    *(void **)(s + 0x0) = out;
    *(int *)(s + 0x8) = 0x7FFFFFFF;
    *(short *)(s + 0xC) = 0x208;
    *(void **)(s + 0x10) = out;
    *(int *)(s + 0x14) = 0x7FFFFFFF;
    *(int *)(s + 0x54) = D_0054CEAC[0];
    n = vfprintf(s, a1, a2);
    *(char *)(*(void **)(s + 0x0)) = 0;
    return n;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __swsetup);
extern void func_001000B8(int a0);
extern int raise(int a0);

void func_002834F8(void) {
    for (;;) {
        raise(6);
        func_001000B8(1);
    }
}
extern int strtod();

int func_00283518(int a0) {
    return strtod(a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", quorem);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _dtoa_r);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", fflush);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", std);
extern void *_malloc_r(void *a0, int a1);
extern void memset(void *a0, int a1, int a2);

void *__sfmoreglue(void *a0, int a1) {
    int sz;
    char *p;
    char *body;
    sz = a1 * 0x58;
    p = (char *)_malloc_r(a0, sz + 0xC);
    if (p == 0) {
        return 0;
    }
    body = p + 0xC;
    *(int *)(p + 0x4) = a1;
    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x8) = (int)body;
    memset(body, 0, sz);
    return p;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __sfp);
extern void _fwalk(int a0, void *a1);
extern int fflush(void);

void _cleanup_r(int a0) {
    _fwalk(a0, fflush);
}
extern void _cleanup_r(int a0);

void _cleanup(void) {
    _cleanup_r(D_0054CEAC[0]);
}
extern void std();

void __sinit(char *a0) {
    char *p = a0 + 0x1E4;
    *(void **)(a0 + 0x3C) = (void *)_cleanup_r;
    *(int *)(a0 + 0x38) = 1;
    std(p, 4, 0, (int)a0);
    std(a0 + 0x23C, 9, 1, (int)a0);
    std(a0 + 0x294, 0xA, 2, (int)a0);
    *(char **)(a0 + 0x1E0) = p;
    *(int *)(a0 + 0x1DC) = 3;
    *(int *)(a0 + 0x1D8) = 0;
}
extern int __srefill(StreamBuf *s);
extern int memcpy(char *a0, char *a1, int a2);

int fread(char *dst, int size, int count, StreamBuf *s) {
    unsigned int total = count * size;
    int len;
    unsigned int avail;
    unsigned int total_orig;
    char *p;

    if (total == 0) {
        return 0;
    }
    len = s->len;
    if (len < 0) {
        s->len = 0;
        len = 0;
    }
    avail = len;
    total_orig = total;
    p = dst;
    if (avail < total) {
        do {
            memcpy(p, s->pos, avail);
            total -= avail;
            p += avail;
            s->pos += avail;
            if (__srefill(s) != 0) {
                return (total_orig - total) / size;
            }
            avail = s->len;
        } while (avail < total);
    }
    memcpy(p, s->pos, total);
    s->len -= total;
    s->pos += total;
    return count;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _free_r);
extern struct D520 D_0054CEC8;
extern int D_0054D2E0[];
extern int D_0054D2F8[];
extern void __malloc_lock(void);
extern void __malloc_unlock();
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int _sbrk_r(int *self, int a1);

int _malloc_trim_r(int *self, unsigned int a1) {
    long long A;
    long long need;
    long long newlen;
    int r4;

    __malloc_lock();
    A = D_0054CEC8.blk->size & 0xFFFFFFFC;
    need = __udivdi3((A - a1) + 0xFEF, 0x1000);
    newlen = __muldi3(need - 1, 0x1000);
    if (newlen < 0x1000) {
        goto fail;
    }
    if (_sbrk_r(self, 0) != (int)D_0054CEC8.blk + (int)A) {
        goto fail;
    }
    if (_sbrk_r(self, -(int)newlen) != 0xFFFFFFFFU) {
        goto adjust;
    }
    r4 = _sbrk_r(self, 0);
    A = r4 - (int)D_0054CEC8.blk;
    if (A >= 0x10) {
        D_0054D2F8[0] = r4 - D_0054D2E0[0];
        D_0054CEC8.blk->size = A | 1;
    }
fail:
    __malloc_unlock(self);
    return 0;
adjust:
    D_0054CEC8.blk->size = (A - newlen) | 1;
    D_0054D2F8[0] -= (int)newlen;
    __malloc_unlock(self);
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __sfvwrite);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _fwalk);
extern int D_00638878[];
extern const unsigned int D_00638888[];
extern int strcmp(int *p, int *buf);

int _setlocale_r(void *a0, int a1, int a2) {
    if (a2 == 0) goto no_check;
    if (strcmp(a2, D_00638888) == 0) goto found;
    if (strcmp(a2, D_00638878) != 0) return 0;
found:
    *(int *)((char *)a0 + 0x30) = a1;
    *(int *)((char *)a0 + 0x34) = a2;
no_check:
    return (int)D_00638888;
}
extern const unsigned int D_00638848[];

void *_localeconv_r(int a0) {
    return D_00638848;
}
int setlocale(int a0, int a1) {
    return _setlocale_r(D_0054CEAC[0], a0, a1);
}
void *localeconv(void) {
    return _localeconv_r(D_0054CEAC[0]);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __smakebuf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", malloc_extend_top);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _malloc_r);
int _mbtowc_r(int a0, int *a1, unsigned char *a2, int a3) {
    int local;
    int *p = &local;
    if (a1 != 0) p = a1;
    if (a2 == 0) goto zero;
    if (a3 != 0) goto store;
    return -1;
zero:
    return 0;
store:
    *p = *a2;
    return *a2 != 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", memchr);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", memmove);
void __malloc_lock(void) {
}
void __malloc_unlock() {
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _Balloc);
void _Bfree(char *a0, int *a1) {
    if (a1) {
        int off = a1[1] * 4;
        int *slot;
        a0 = *(char **)(a0 + 0x4C);
        off += (int)a0;
        slot = (int *)off;
        a1[0] = slot[0];
        slot[0] = (int)a1;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _multadd);
extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);

int _s2b(void *a0, char *a1, int a2, int a3, int a4)
{
    int n3 = (a3 + 8) / 9;
    int p = 1;
    int five = 0;
    int i18;
    int *r5;
    int i17;

    if (p < n3) {
        do {
            p <<= 1;
            five++;
        } while (p < n3);
    }
    i18 = a2 < 10;
    r5 = _Balloc(a0, five);
    i17 = 9;
    r5[5] = a4;
    r5[4] = 1;
    if (i18 == 0) {
        a1 += 9;
        do {
            i17++;
            r5 = _multadd(a0, r5, 10, a1[0] - 0x30);
            a1++;
        } while (i17 < a2);
        a1++;
    } else {
        a1 += 10;
    }
    if (i17 < a3) {
        i17 = a3 - i17;
        do {
            r5 = _multadd(a0, r5, 10, a1[0] - 0x30);
            a1++;
            i17--;
        } while (i17 != 0);
    }
    return (int)r5;
}
int _hi0bits(unsigned int a0) {
    int n = 0;
    if ((a0 & 0xFFFF0000) == 0) { n = 16; a0 <<= 16; }
    if ((a0 & 0xFF000000) == 0) { n += 8; a0 <<= 8; }
    if ((a0 & 0xF0000000) == 0) { n += 4; a0 <<= 4; }
    if ((a0 & 0xC0000000) == 0) { n += 2; a0 <<= 2; }
    if ((int)a0 >= 0) {
        n += 1;
        if ((a0 & 0x40000000) == 0) {
            return 0x20;
        }
    }
    return n;
}
int _lo0bits(int *p) {
    unsigned int v = *p;
    int n;
    if (v & 7) {
        if (v & 1) {
            return 0;
        }
        if (v & 2) {
            *p = v >> 1;
            return 1;
        }
        *p = v >> 2;
        return 2;
    }
    n = 0;
    if ((v & 0xFFFF) == 0) {
        n = 0x10;
        v >>= 16;
    }
    if ((v & 0xFF) == 0) {
        n += 8;
        v >>= 8;
    }
    if ((v & 0xF) == 0) {
        n += 4;
        v >>= 4;
    }
    if ((v & 3) == 0) {
        n += 2;
        v >>= 2;
    }
    if (v & 1) {
        *p = v;
    } else {
        v >>= 1;
        n += 1;
        if (v == 0) {
            return 0x20;
        }
        *p = v;
    }
    return n;
}
void *_i2b(void *a0, int a1) {
    int *r = _Balloc(a0, 1);
    r[5] = a1;
    r[4] = 1;
    return r;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _multiply);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _pow5mult);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _lshift);
int __mcmp(unsigned int *a, unsigned int *b) {
 int n = a[4] - b[4]; unsigned int *pa, *pb, *pae, *pbe;
 if (n != 0) return n;
 n = b[4]; pa = a + 5; pb = b + 5; pae = pa + n; pbe = pb + n;
 do { --pae; --pbe; if (*pae != *pbe) return (*pae < *pbe) ? -1 : 1; } while (pa < pae);
 return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __mdiff);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _ulp);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _b2d);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _d2b);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _ratio);
extern const long D_006388A0[];
extern long dpmul(long a, long b);

long _mprec_log10(int n) {
    long acc = (long)0xFFC0 << 46;
    if (n < 0x18) {
        return D_006388A0[n];
    }
    while (n > 0) {
        acc = dpmul(acc, (long)0x8048 << 47);
        n--;
    }
    return acc;
}
extern int fflush(void);

int lflush(void) {
    return fflush();
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __srefill);
int isinf(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (int)(((unsigned int)(hx | (-hx))) >> 31);
}
int isnan(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    do { return ((unsigned int)hx) >> 31; } while (0);
}
extern int D_0063C5D8[];
extern unsigned int sbrk(int a0);

int _sbrk_r(int *self, int a1)
{
    unsigned int ret;
    D_0063C5D8[0] = 0;
    ret = sbrk(a1);
    if (ret == 0xFFFFFFFF) {
        if (D_0063C5D8[0] != 0) {
            self[0] = D_0063C5D8[0];
        }
    }
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _init_signal_r);
extern int _init_signal_r(int a0);

unsigned int _signal_r(void *a0, int a1, int a2) {
    unsigned int *base;
    unsigned int old;
    if ((unsigned int)a1 >= 0x20) {
        *(int *)a0 = 0x16;
        return 0xFFFFFFFFU;
    }
    if (*(int *)((char *)a0 + 0x1D4) == 0) {
        if (_init_signal_r((int)a0) != 0) {
            return 0xFFFFFFFFU;
        }
    }
    base = *(unsigned int **)((char *)a0 + 0x1D4);
    old = base[a1];
    base[a1] = a2;
    return old;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _raise_r);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __sigtramp_r);
extern int _raise_r(int a0, int a1);

int raise(int a0) {
    return _raise_r(D_0054CEAC[0], a0);
}
int signal(int a0, int a1) {
    return _signal_r(D_0054CEAC[0], a0, a1);
}
void *_init_signal(void) {
    return _init_signal_r(D_0054CEAC[0]);
}
extern int __sigtramp_r(int a0, int a1);

int __sigtramp(int a0) {
    return __sigtramp_r(D_0054CEAC[0], a0);
}
extern int kill(int a0, void *a1);

int _kill_r(int *self, int a1, int a2)
{
    int ret;
    D_0063C5D8[0] = 0;
    ret = kill(a1, a2);
    if (ret == -1) {
        if (D_0063C5D8[0] != 0) {
            self[0] = D_0063C5D8[0];
        }
    }
    return ret;
}
extern int getpid(void);

int _getpid_r(void) {
    return getpid();
}
extern int _read_r(int *self, int a1, int a2, int a3);

int __sread(void *a0, int a1, int a2) {
    long v = _read_r((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
    if ((int)v >= 0) {
        *(int *)((char *)a0 + 0x50) = *(int *)((char *)a0 + 0x50) + (int)v;
    } else {
        *(unsigned short *)((char *)a0 + 0xC) = *(unsigned short *)((char *)a0 + 0xC) & 0xEFFF;
    }
    return (int)v;
}
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);

long __swrite(void *a0, int a1, int a2) {
    unsigned short flag = *(unsigned short *)((char *)a0 + 0xC);
    if (flag & 0x100) {
        _lseek_r((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), 0, 2);
    }
    flag = *(unsigned short *)((char *)a0 + 0xC) & 0xEFFF;
    *(unsigned short *)((char *)a0 + 0xC) = flag;
    {
        unsigned long r = (unsigned long)_write_r((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
        return (int)r;
    }
}
long __sseek(void *a0, int a1, int a2) {
    unsigned long r = (unsigned long)_lseek_r((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
    if (r == -1) {
        *(unsigned short *)((char *)a0 + 0xC) &= 0xEFFF;
    } else {
        *(int *)((char *)a0 + 0x50) = (int)r;
        *(unsigned short *)((char *)a0 + 0xC) |= 0x1000;
    }
    return r;
}
extern int _close_r(int *self, int a1);

int __sclose(void *a0) {
    return _close_r((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE));
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _strtod_r);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", strtod);
extern int dptofp(long a0);
extern int strtod();

int strtodf(void) {
    return dptofp(strtod());
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _strtoul_r);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);

long long strtoul(void *a0, int a1, int a2) {
    return _strtoul_r((void *)D_0054CEAC[0], a0, a1, a2);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", __submore);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", ungetc);
extern int write(int a1, int a2, int a3);

int _write_r(int *self, int a1, int a2, int a3)
{
    int ret;
    D_0063C5D8[0] = 0;
    ret = write(a1, a2, a3);
    if (ret == -1) {
        if (D_0063C5D8[0] != 0) {
            self[0] = D_0063C5D8[0];
        }
    }
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _calloc_r);
extern int close(int a1);

int _close_r(int *self, int a1)
{
    int ret;
    D_0063C5D8[0] = 0;
    ret = close(a1);
    if (ret == -1) {
        if (D_0063C5D8[0] != 0) {
            self[0] = D_0063C5D8[0];
        }
    }
    return ret;
}
extern int fstat(void *a0, void *a1);

int _fstat_r(int *self, int a1, int a2)
{
    int ret;
    D_0063C5D8[0] = 0;
    ret = fstat(a1, a2);
    if (ret == -1) {
        if (D_0063C5D8[0] != 0) {
            self[0] = D_0063C5D8[0];
        }
    }
    return ret;
}
extern int lseek(int a1, int a2, int a3);

int _lseek_r(int *self, int a1, int a2, int a3)
{
    int ret;
    D_0063C5D8[0] = 0;
    ret = lseek(a1, a2, a3);
    if (ret == -1) {
        if (D_0063C5D8[0] != 0) {
            self[0] = D_0063C5D8[0];
        }
    }
    return ret;
}
extern int read(int a1, int a2, int a3);

int _read_r(int *self, int a1, int a2, int a3)
{
    int ret;
    D_0063C5D8[0] = 0;
    ret = read(a1, a2, a3);
    if (ret == -1) {
        if (D_0063C5D8[0] != 0) {
            self[0] = D_0063C5D8[0];
        }
    }
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27E5E0", _realloc_r);
