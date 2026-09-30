/* Vendor SCE library member: libkernl.a(eeloadfile.o).  MAIN.MAP names the
 * member and its .text size (0x994), which tiles the shipped ELF from one
 * retail function start to the next; VMA 0x263EA0..0x264834,
 * 14 functions. */

#include <sifrpc.h>
#include <string.h>

extern int memcmp();

/* eeloadfile.o's .data: -1 until _lf_bind has bound the loadfile server, then
   the stamp _lf_version accepts besides the library's own (its four dots are
   the member's first .rodata, 0x636710). */
static int lf_bind_state = -1;

static char *lf_stamp = "....";

extern char D_0072D780[];
extern char D_0072D980[];
extern char D_0072D9A8[];

int _lf_bind(void)
{
    int i;
    int r;
    int val;
    if (lf_bind_state >= 0)
        goto ret0;
loop:
    r = sceSifBindRpc(D_0072D980, 0x80000006, 0);
    if (r < 0)
        return -1;
    val = *(int *)(D_0072D980 + 0x24);
    if (val == 0)
        goto delay;
    lf_bind_state = 0;
    r = sceSifCallRpc(D_0072D980, 0xFF, 0, 0, 0, D_0072D780, 4, 0, 0);
    if (r < 0)
        return 0xFFFEFFFF;
    __builtin_memcpy(D_0072D9A8, D_0072D780, 4);
    return 0;
delay:
    /* IOP-side retry back-off: spin 0x100000 times, no memory touched. */
    i = 0x100000;
    do {
        i--;
    } while (i != -1);
    goto loop;
ret0:
    return 0;
}

extern char D_0028ED0C[];

int _lf_version(void)
{
    void *s3 = D_0028ED0C;
    void *s1 = D_0072D9A8;
    int s2 = 0;
    char *v;
    if (memcmp(s1, (int)s3, 4) == 0)
        goto done;
    v = lf_stamp;
    if (memcmp(s1, v, 4) == 0)
        goto done;
    v = lf_stamp;
    s2 = (0 < (unsigned int)memcmp(s3, v, 4));
done:
    return s2;
}

int sceSifLoadFileReset(void)
{
    lf_bind_state = -1;
    memset(D_0072D9A8, 0, 4);
    return 0;
}

/* The request's 0xFC-byte argument block.  The oversize copy below is a record
   assignment, which gcc expands inline through movstrsi; memcpy stays a call at
   -fno-builtin, so the inline ldl/ldr run can only come from a record. */
typedef struct {
    char v[0xFC];
} SceLfArgBuf;

/* The loadfile RPC send buffer at D_0072D780 (0x200 bytes sent, 8 read back). */
typedef struct {
    int addr;
    int arglen;
    char name[0xFC];
    SceLfArgBuf args;
} SceLfRpcBuf;

int _sceSifLoadModuleBuffer(void *addr, int arglen, int args, void *ret)
{
    SceLfRpcBuf *p;
    int r;

    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (_lf_version() != 0) {
        return 0xFFFEFFFC;
    }
    p = (SceLfRpcBuf *)D_0072D780;
    ((SceLfRpcBuf *)D_0072D780)->addr = (int)addr;
    if (args != 0) {
        if (arglen >= 0xFD) {
            p->args = *(SceLfArgBuf *)args;
            /* What the bytes pin: this store goes through the buffer itself,
               not p; the ROM re-forms its address after the copy loop
               (addiu $3,%lo(D_0072D780) then sw 4($3)), where p's register
               serves the other two arms.  A member of the record gives that
               (explow.c memory_address copies the lo_sum base to a register);
               a byte-offset constant would give %lo(D_0072D780+4). */
            ((SceLfRpcBuf *)D_0072D780)->arglen = 0xFC;
        } else {
            memcpy(&p->args, (char *)args, arglen);
            p->arglen = arglen;
        }
    } else {
        p->arglen = 0;
    }
    if (sceSifCallRpc(D_0072D980, 6, 0, D_0072D780, 0x200, D_0072D780, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = ((SceLfRpcBuf *)D_0072D780)->addr;
    *(int *)ret = ((SceLfRpcBuf *)D_0072D780)->arglen;
    return r;
}

void sceSifLoadModuleBuffer(void *a0, int a1, int a2)
{
    int local[4];
    _sceSifLoadModuleBuffer(a0, a1, a2, &local);
}

int sceSifLoadStartModuleBuffer(void *a0, int a1, int a2, void *a3)
{
    return _sceSifLoadModuleBuffer(a0, a1, a2, a3);
}

extern char D_0072D788[];

int _sceSifLoadModule(void *name, int arglen, int args, int ret, int rpcno)
{
    char *buf;
    int r;

    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (_lf_version() != 0) {
        return 0xFFFEFFFC;
    }
    strncpy(D_0072D788, (char *)name, 252);
    buf = D_0072D788 - 8;
    buf[0x103] = 0;
    if (args != 0) {
        if (arglen >= 0xFD) {
            *(SceLfArgBuf *)(buf + 0x104) = *(SceLfArgBuf *)args;
            *(int *)D_0072D780 = 0xFC;
        } else {
            memcpy(buf + 0x104, (char *)args, arglen);
            *(int *)buf = arglen;
        }
    } else {
        buf[0x104] = 0;
        *(int *)buf = 0;
    }
    if (sceSifCallRpc(D_0072D980, rpcno, 0, D_0072D780, 0x200, D_0072D780, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = *(int *)(D_0072D780 + 0);
    *(int *)ret = *(int *)(D_0072D780 + 4);
    return r;
}

void sceSifLoadModule(void *a0, int a1, int a2)
{
    int local;
    _sceSifLoadModule(a0, a1, a2, (int)&local, 0);
}

int sceSifLoadStartModule(void *a0, int a1, int a2, int a3)
{
    return _sceSifLoadModule(a0, a1, a2, a3, 0);
}

extern char D_0072D788[];

int _sceSifLoadElfPart(void *name, int sec, int out, int rpcno)
{
    char *buf;
    int r;

    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (_lf_version() != 0) {
        return 0xFFFEFFFC;
    }
    strncpy(D_0072D788, (char *)name, 252);
    buf = D_0072D788 - 8;
    buf[0x103] = 0;
    strncpy(D_0072D788 + 252, (char *)sec, 252);
    buf[0x1FF] = 0;
    if (sceSifCallRpc(D_0072D980, rpcno, 0, buf, 0x200, buf, 0x10, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = *(int *)buf;
    if (r == 0) {
        return 0xFFFEFFFD;
    }
    ((int *)out)[0] = r;
    ((int *)out)[1] = *(int *)(buf + 4);
    return 0;
}

int sceSifLoadElfPart(void *a0, int a1, int a2)
{
    return _sceSifLoadElfPart(a0, a1, a2, 1);
}

int sceSifLoadElf(void *a0, int a1)
{
    return _sceSifLoadElfPart(a0, (int)"all", a1, 1);
}

int sceSifGetIopAddr(int a0, void *a1, int a2)
{
    int r;
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if ((unsigned int)a2 >= 3) {
        return 0xFFFEFFFE;
    }
    *(int *)(D_0072D780 + 0) = a0;
    *(int *)(D_0072D780 + 4) = a2;
    r = sceSifCallRpc(D_0072D980, 3, 0, D_0072D780, 0x20, D_0072D780, 0x20, 0, 0);
    if (r < 0) {
        return 0xFFFEFFFF;
    }
    if (a2 == 0) {
        *(unsigned char *)a1 = *(unsigned char *)D_0072D780;
    } else if (a2 == 1) {
        *(unsigned short *)a1 = *(unsigned short *)D_0072D780;
    } else if (a2 == 2) {
        *(int *)a1 = *(int *)D_0072D780;
    } else {
        return 0xFFFEFFFE;
    }
    return 0;
}

int sceSifSetIopAddr(int a0, void *a1, int a2)
{
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    *(int *)(D_0072D780 + 0) = a0;
    *(int *)(D_0072D780 + 4) = a2;
    if (a2 == 0) {
        *(unsigned char *)(D_0072D780 + 8) = *(unsigned char *)a1;
    } else if (a2 == 1) {
        *(unsigned short *)(D_0072D780 + 8) = *(unsigned short *)a1;
    } else if (a2 == 2) {
        *(int *)(D_0072D780 + 8) = *(int *)a1;
    } else {
        return 0xFFFEFFFE;
    }
    if (sceSifCallRpc(D_0072D980, 2, 0, D_0072D780, 0x20, D_0072D780, 0x10, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    return 0;
}
