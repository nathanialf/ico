/* Vendor SCE library member: libkernl.a(sifcmd.o).  MAIN.MAP names the
 * member and its .text size (0x748), which tiles the shipped ELF from one
 * retail function start to the next (the retail link has it after tlbtrap.o, where the January listing also puts it; MAIN.MAP's own link has it after tty.o); VMA 0x2653A0..0x265AE8,
 * 16 functions. */

#include <sifrpc.h>
#include <string.h>
#include <sifcmd.h>

extern int DIntr();
extern int EIntr();
/* eekernel.h's spelling: a void call leaves no value register set after it,
   which sceSifInitCmd's allocation after its FlushCache call shows. */
extern void FlushCache(int a0);

void _set_sreg(int *a0, int *a1)
{
    ((int *)a1[7])[a0[4]] = a0[5];
}

void _change_addr(int *a0, int *a1)
{
    a1[2] = a0[4];
}

extern int D_0072EE80[];

int sceSifGetSreg(int a0)
{
    return D_0072EE80[a0];
}

extern int D_0072EE80[];

int sceSifSetSreg(int a0, int a1)
{
    D_0072EE80[a0] = a1;
    return a1;
}

/* Reconstruction: the 32-entry SIF command handler table at D_0072ED80, a
   handler function and the data pointer handed to it. */
typedef struct {
    void (*fn)();
    void *data;
} SifCmdEntry;

/* Reconstruction: the SIF command data record at D_0072ED58 (fields 3/4 and 5/6
   are what sceSifSetSysCmdBuffer and sceSifSetCmdBuffer swap). */
typedef struct {
    int sendbuf;
    int ackbuf;
    int iopbuf;
    SifCmdEntry *systbl;
    int nsys;
    SifCmdEntry *usrtbl;
    int nusr;
    int *sreg;
} SifCmdData;

extern SifCmdData D_0072ED58;

void *sceSifGetDataTable(void)
{
    return &D_0072ED58;
}

/* sifcmd.o's .data: set once sceSifInitCmd has run, cleared by sceSifExitCmd */
static int cmd_inited = 0;

extern int D_0072EC80[];
extern int D_0072ED00[];
extern int D_0072ED40[];
extern int D_0072ED54[];
extern int D_0072ED80[];
extern void sceSifSetDChain(void);
extern void _sceSifCmdIntrHdlr();
extern void _change_addr(int *a0, int *a1);
extern void _set_sreg(int *a0, int *a1);
extern int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1);

void sceSifInitCmd(void)
{
    SifCmdEntry *h;
    int i;

    DIntr();
    if (cmd_inited != 0) {
        EIntr();
        return;
    }
    cmd_inited = 1;
    D_0072ED58.sendbuf = (int)D_0072EC80 | 0x20000000;
    D_0072ED58.ackbuf = (int)D_0072ED00 | 0x20000000;
    D_0072ED58.iopbuf = 0;
    D_0072ED58.systbl = (SifCmdEntry *)D_0072ED80;
    D_0072ED58.nsys = 0x20;
    D_0072ED58.usrtbl = 0;
    D_0072ED58.nusr = 0;
    D_0072ED58.sreg = D_0072EE80;
    /* Both loops count up with the one i: loop.c reverses each counter and,
       since i is shared, sets i = 32 after the second, which is the register
       the DMAC status write below stores (the ROM keeps i in $16). */
    h = (SifCmdEntry *)D_0072ED80;
    for (i = 0; i < 32; i++) {
        h->fn = 0;
        h->data = 0;
        h++;
    }
    for (i = 0; i < 32; i++) {
        D_0072EE80[i] = 0;
    }
    ((SifCmdEntry *)D_0072ED80)[0].fn = _change_addr;
    ((SifCmdEntry *)D_0072ED80)[0].data = &D_0072ED58;
    ((SifCmdEntry *)D_0072ED80)[1].fn = _set_sreg;
    ((SifCmdEntry *)D_0072ED80)[1].data = &D_0072ED58;
    EIntr();
    FlushCache(0);
    if (*(volatile int *)0x1000E010 & 0x20) {
        *(volatile int *)0x1000E010 = 0x20;
    }
    if ((*(volatile int *)0x1000C000 & 0x100) == 0) {
        sceSifSetDChain();
    }
    D_0072ED54[0] = AddDmacHandler(5, _sceSifCmdIntrHdlr, 0);
    EnableDmac(5);
    D_0072ED58.iopbuf = sceSifGetReg(0x80000000);
    if (D_0072ED58.iopbuf != 0) {
        D_0072ED40[4] = (int)D_0072EC80;
        sceSifSendCmd(0x80000000, (int)D_0072ED40, 0x14, 0, 0, 0);
        return;
    }
    while ((sceSifGetReg(4) & 0x20000) == 0) {
        ;
    }
    D_0072ED58.iopbuf = sceSifGetReg(2);
    sceSifSetReg(0x80000000, D_0072ED58.iopbuf);
    sceSifSetReg(0x80000001, (int)&D_0072ED58);
    D_0072ED40[4] = (int)D_0072EC80;
    D_0072ED40[3] = 0;
    sceSifSendCmd(0x80000002, (int)D_0072ED40, 0x14, 0, 0, 0);
}

extern int D_0072ED54[];
extern int DisableDmac(int a0);
extern int RemoveDmacHandler(int a0, int a1);

void sceSifExitCmd(void)
{
    DisableDmac(5);
    RemoveDmacHandler(5, D_0072ED54[0]);
    cmd_inited = 0;
}

SifCmdEntry *sceSifSetCmdBuffer(SifCmdEntry *tbl, int n)
{
    SifCmdEntry *old = D_0072ED58.usrtbl;
    D_0072ED58.usrtbl = tbl;
    D_0072ED58.nusr = n;
    return old;
}

SifCmdEntry *sceSifSetSysCmdBuffer(SifCmdEntry *tbl, int n)
{
    SifCmdEntry *old = D_0072ED58.systbl;
    D_0072ED58.systbl = tbl;
    D_0072ED58.nsys = n;
    return old;
}

extern int D_0072ED64[];
extern int D_0072ED6C[];

int sceSifAddCmdHandler(int a0, int a1, int a2)
{
    int off = a0 * 8;
    int *p;
    if (a0 >= 0)
        goto pos;
    a0 = D_0072ED64[0];
    goto done;
pos:
    a0 = D_0072ED6C[0];
done:
    off += a0;
    p = (int *)off;
    p[0] = a1;
    p[1] = a2;
}

void sceSifRemoveCmdHandler(int a0)
{
    int off = a0 * 8;
    if (a0 < 0) {
        a0 = D_0072ED64[0];
    } else {
        a0 = D_0072ED6C[0];
    }
    off += a0;
    *(int *)off = 0;
}

extern int D_0072ED60;
extern int isceSifSetDma(int p, int a);

int _sceSifSendCmd(int cid, int mode, int pkt, int pktsize, int src, int dest, int size)
{
    SifDmaTransfer dmat[2];
    SifCmdHeader *header;
    int count;

    if (pktsize < 16 || pktsize > 112) {
        return 0;
    }
    header = (SifCmdHeader *)pkt;
    count = 0;
    if (size > 0) {
        header->dsize = size;
        dmat[0].src = src;
        dmat[0].dest = dest;
        dmat[0].size = size;
        header->dest = dest;
        dmat[0].u.attr = 0;
        count = 1;
        if (mode & 4) {
            sceSifWriteBackDCache((void *)src, size);
        }
    } else {
        header->dsize = 0;
        header->dest = 0;
    }
    dmat[count].src = pkt;
    dmat[count].dest = D_0072ED60;
    dmat[count].size = pktsize;
    header->cid = cid;
    header->psize = pktsize;
    dmat[count].u.attr = 0x44;
    count++;
    sceSifWriteBackDCache((void *)pkt, pktsize);
    if (mode & 1) {
        return isceSifSetDma((int)dmat, count);
    }
    return sceSifSetDma((int)dmat, count);
}

int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1)
{
    return _sceSifSendCmd(a0, 0, a1, a2, a3, t0, t1);
}

int isceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1)
{
    return _sceSifSendCmd(a0, 1, a1, a2, a3, t0, t1);
}

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _sceSifCmdIntrHdlr\n"
        ".type _sceSifCmdIntrHdlr, @function\n"
        "    .align 3\n"
        "_sceSifCmdIntrHdlr:\n"
        "    addiu $29, $29, -0x90\n"
        "    sd $16, 0x70($29)\n"
        "    sd $31, 0x80($29)\n"
        "    jal EIntr\n"
        "    nop\n"
        "    lui $3, %hi(D_0072ED58)\n"
        "    lw $7, %lo(D_0072ED58)($3)\n"
        "    addiu $16, $3, %lo(D_0072ED58)\n"
        "    lbu $2, 0x0($7)\n"
        "    andi $5, $2, 0xFF\n"
        "    beqz $5, .LIntrHdlr002483E8\n"
        "    daddu $2, $0, $0\n"
        "    addiu $2, $5, 0xF\n"
        "    addiu $3, $0, -0x1\n"
        "    addiu $4, $5, 0x1E\n"
        "    slt $3, $3, $2\n"
        "    movn $4, $2, $3\n"
        "    daddu $6, $7, $0\n"
        "    sra $5, $4, 4\n"
        "    sb $0, 0x0($7)\n"
        "    blez $5, .LIntrHdlr0024834C\n"
        "    daddu $4, $5, $0\n"
        "    daddu $3, $29, $0\n"
        "    nop\n"
        ".LIntrHdlr00248330:\n"
        "    lq $2, 0x0($6)\n"
        "    addiu $4, $4, -0x1\n"
        "    addiu $6, $6, 0x10\n"
        "    sq $2, 0x0($3)\n"
        "    addiu $3, $3, 0x10\n"
        "    bnez $4, .LIntrHdlr00248330\n"
        "    nop\n"
        ".LIntrHdlr0024834C:\n"
        "    jal isceSifSetDChain\n"
        "    nop\n"
        "    lw $3, 0x8($29)\n"
        "    bgez $3, .LIntrHdlr002483A8\n"
        "    nop\n"
        "    lw $2, 0x8($29)\n"
        "    lui $3, (0x7FFFFFFF >> 16)\n"
        "    ori $3, $3, (0x7FFFFFFF & 0xFFFF)\n"
        "    lw $4, 0x10($16)\n"
        "    and $5, $2, $3\n"
        "    slt $4, $5, $4\n"
        "    beqz $4, .LIntrHdlr002483DC\n"
        "    sll $2, $5, 3\n"
        "    lw $3, 0xC($16)\n"
        "    addu $2, $2, $3\n"
        "    lw $6, 0x0($2)\n"
        "    beqz $6, .LIntrHdlr002483DC\n"
        "    nop\n"
        "    lw $5, 0x4($2)\n"
        "    jalr $6\n"
        "    daddu $4, $29, $0\n"
        "    b .LIntrHdlr002483DC\n"
        "    nop\n"
        ".LIntrHdlr002483A8:\n"
        "    lw $5, 0x8($29)\n"
        "    lw $2, 0x18($16)\n"
        "    slt $2, $5, $2\n"
        "    beqz $2, .LIntrHdlr002483DC\n"
        "    sll $2, $5, 3\n"
        "    lw $3, 0x14($16)\n"
        "    addu $2, $2, $3\n"
        "    lw $6, 0x0($2)\n"
        "    beqz $6, .LIntrHdlr002483DC\n"
        "    nop\n"
        "    lw $5, 0x4($2)\n"
        "    jalr $6\n"
        "    daddu $4, $29, $0\n"
        ".LIntrHdlr002483DC:\n"
        "    sync\n"
        "    ei\n"
        "    daddu $2, $0, $0\n"
        ".LIntrHdlr002483E8:\n"
        "    ld $31, 0x80($29)\n"
        "    ld $16, 0x70($29)\n"
        "    jr $31\n"
        "    addiu $29, $29, 0x90\n"
        ".size _sceSifCmdIntrHdlr, . - _sceSifCmdIntrHdlr\n"
        "    .set reorder\n"
        "    .set at\n");

/* The four `.align 2` directives below are the ones the shipped function's own
 * asm carries at its internal labels; they emit no bytes here, but without them
 * the period assembler inserts two nops before the first loop's closing bgtz
 * as soon as any other function in the object is compiled C rather than
 * assembled. */
__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global sceSifWriteBackDCache\n"
        ".type sceSifWriteBackDCache, @function\n"
        "    .align 3\n"
        "sceSifWriteBackDCache:\n"
        "    lui $25, (0xFFFFFFC0 >> 16)\n"
        "    ori $25, $25, (0xFFFFFFC0 & 0xFFFF)\n"
        "    blez $5, .L00265A380024849C\n"
        "    addu $10, $4, $5\n"
        "    and $8, $4, $25\n"
        "    addiu $10, $10, -0x1\n"
        "    and $9, $10, $25\n"
        "    subu $10, $9, $8\n"
        "    srl $11, $10, 6\n"
        "    addiu $11, $11, 0x1\n"
        "    andi $9, $11, 0x7\n"
        "    beqz $9, .L00265A3800248448\n"
        "    srl $10, $11, 3\n"
        "    .align 2\n"
        ".L00265A380024842C:\n"
        "    sync\n"
        "    cache 0x18, 0x0($8)\n"
        "    sync\n"
        "    addiu $9, $9, -0x1\n"
        "    nop\n"
        "    bgtz $9, .L00265A380024842C\n"
        "    addiu $8, $8, 0x40\n"
        "    .align 2\n"
        ".L00265A3800248448:\n"
        "    beqz $10, .L00265A380024849C\n"
        "    .align 2\n"
        ".L00265A380024844C:\n"
        "    addiu $10, $10, -0x1\n"
        "    sync\n"
        "    cache 0x18, 0x0($8)\n"
        "    sync\n"
        "    cache 0x18, 0x40($8)\n"
        "    sync\n"
        "    cache 0x18, 0x80($8)\n"
        "    sync\n"
        "    cache 0x18, 0xC0($8)\n"
        "    sync\n"
        "    cache 0x18, 0x100($8)\n"
        "    sync\n"
        "    cache 0x18, 0x140($8)\n"
        "    sync\n"
        "    cache 0x18, 0x180($8)\n"
        "    sync\n"
        "    cache 0x18, 0x1C0($8)\n"
        "    sync\n"
        "    bgtz $10, .L00265A380024844C\n"
        "    addiu $8, $8, 0x200\n"
        "    .align 2\n"
        ".L00265A380024849C:\n"
        "    jr $31\n"
        "    nop\n"
        "    jr $31\n"
        ".size sceSifWriteBackDCache, . - sceSifWriteBackDCache\n"
        "    .set reorder\n"
        "    .set at\n");

/* The stray jr that closes the block above has no delay-slot instruction of
   its own: the next input, libcdvd.a(cdvd000), starts with CB_DelayTh at
   0x265AE8, whose first word sits in that slot.  The member boundary is the
   object boundary, as the retail link had it. */
