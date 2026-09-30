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

/* Reconstruction: the 32-entry SIF command handler table, a
   handler function and the data pointer handed to it. */
typedef struct {
    void (*fn)();
    void *data;
} SifCmdEntry;

/* Reconstruction: the SIF command data record (fields 3/4 and 5/6
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

/* the member's .bss: the uncached send and ack buffers and the init packet on
   64-byte DMA lines, the DMAC handler id, the command data record, the system
   handler table (the bytes pin at least 16-byte alignment) and the software
   registers */
static int cmdSendBuf[32] __attribute__((aligned(64))); /* derived name */

static int cmdAckBuf[16] __attribute__((aligned(64))); /* derived name */

static int cmdInitPkt[5] __attribute__((aligned(64))); /* derived name */

static int cmdDmacId; /* derived name */

static SifCmdData cmdData; /* derived name */

static SifCmdEntry sysCmdTable[32] __attribute__((aligned(16))); /* derived name */

static int cmdSreg[32]; /* derived name */

int sceSifGetSreg(int a0)
{
    return cmdSreg[a0];
}

int sceSifSetSreg(int a0, int a1)
{
    cmdSreg[a0] = a1;
    return a1;
}

void *sceSifGetDataTable(void)
{
    return &cmdData;
}

/* sifcmd.o's .data: set once sceSifInitCmd has run, cleared by sceSifExitCmd */
static int cmd_inited = 0;

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
    cmdData.sendbuf = (int)cmdSendBuf | 0x20000000;
    cmdData.ackbuf = (int)cmdAckBuf | 0x20000000;
    cmdData.iopbuf = 0;
    cmdData.systbl = sysCmdTable;
    cmdData.nsys = 0x20;
    cmdData.usrtbl = 0;
    cmdData.nusr = 0;
    cmdData.sreg = cmdSreg;
    /* Both loops count up with the one i: loop.c reverses each counter and,
       since i is shared, sets i = 32 after the second, which is the register
       the DMAC status write below stores (the ROM keeps i in $16). */
    h = sysCmdTable;
    for (i = 0; i < 32; i++) {
        h->fn = 0;
        h->data = 0;
        h++;
    }
    for (i = 0; i < 32; i++) {
        cmdSreg[i] = 0;
    }
    (sysCmdTable)[0].fn = _change_addr;
    (sysCmdTable)[0].data = &cmdData;
    (sysCmdTable)[1].fn = _set_sreg;
    (sysCmdTable)[1].data = &cmdData;
    EIntr();
    FlushCache(0);
    if (*(volatile int *)0x1000E010 & 0x20) {
        *(volatile int *)0x1000E010 = 0x20;
    }
    if ((*(volatile int *)0x1000C000 & 0x100) == 0) {
        sceSifSetDChain();
    }
    cmdDmacId = AddDmacHandler(5, _sceSifCmdIntrHdlr, 0);
    EnableDmac(5);
    cmdData.iopbuf = sceSifGetReg(0x80000000);
    if (cmdData.iopbuf != 0) {
        cmdInitPkt[4] = (int)cmdSendBuf;
        sceSifSendCmd(0x80000000, (int)cmdInitPkt, 0x14, 0, 0, 0);
        return;
    }
    while ((sceSifGetReg(4) & 0x20000) == 0) {
        ;
    }
    cmdData.iopbuf = sceSifGetReg(2);
    sceSifSetReg(0x80000000, cmdData.iopbuf);
    sceSifSetReg(0x80000001, (int)&cmdData);
    cmdInitPkt[4] = (int)cmdSendBuf;
    cmdInitPkt[3] = 0;
    sceSifSendCmd(0x80000002, (int)cmdInitPkt, 0x14, 0, 0, 0);
}

extern int DisableDmac(int a0);
extern int RemoveDmacHandler(int a0, int a1);

void sceSifExitCmd(void)
{
    DisableDmac(5);
    RemoveDmacHandler(5, cmdDmacId);
    cmd_inited = 0;
}

SifCmdEntry *sceSifSetCmdBuffer(SifCmdEntry *tbl, int n)
{
    SifCmdEntry *old = cmdData.usrtbl;
    cmdData.usrtbl = tbl;
    cmdData.nusr = n;
    return old;
}

SifCmdEntry *sceSifSetSysCmdBuffer(SifCmdEntry *tbl, int n)
{
    SifCmdEntry *old = cmdData.systbl;
    cmdData.systbl = tbl;
    cmdData.nsys = n;
    return old;
}

int sceSifAddCmdHandler(int a0, int a1, int a2)
{
    int off = a0 * 8;
    int *p;
    if (a0 >= 0)
        goto pos;
    a0 = (int)cmdData.systbl;
    goto done;
pos:
    a0 = (int)cmdData.usrtbl;
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
        a0 = (int)cmdData.systbl;
    } else {
        a0 = (int)cmdData.usrtbl;
    }
    off += a0;
    *(int *)off = 0;
}

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
    dmat[count].dest = cmdData.iopbuf;
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
        "    lui $3, %hi(cmdData)\n"
        "    lw $7, %lo(cmdData)($3)\n"
        "    addiu $16, $3, %lo(cmdData)\n"
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
