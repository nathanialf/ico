/* libkernl.a(sifcmd.o) */

#include <eekernel.h>
#include <sifrpc.h>
#include <string.h>
#include <sifcmd.h>
#include <eeregs.h>
#include <libkernl_internal.h>

/* eekernel.h's spelling: FlushCache returns nothing. */

/* the two system commands sceSifInitCmd installs handlers for: the IOP moving
   its command buffer, and the IOP setting one of the software registers */
typedef struct {
    SifCmdHeader header;
    int newaddr;        /* the IOP buffer address, the number iopbuf holds */
} SifCmdChangeAddrData; /* derived name */

typedef struct {
    SifCmdHeader header;
    int rno;
    int value;
} SifCmdSRegData; /* derived name */

/* The 32-entry SIF command handler table, a
   handler function and the data pointer handed to it. */
typedef struct {
    void (*fn)();
    void *data;
} SifCmdEntry;

/* The SIF command data record (fields 3/4 and 5/6
   are what sceSifSetSysCmdBuffer and sceSifSetCmdBuffer swap). */
typedef struct {
    int sendbuf; /* the uncached alias of cmdSendBuf, its address OR 0x20000000 */
    int ackbuf;  /* the same for cmdAckBuf */
    int iopbuf;  /* the IOP's buffer address, read from and written to a SIF register */
    SifCmdEntry *systbl;
    int nsys;
    SifCmdEntry *usrtbl;
    int nusr;
    int *sreg;
} SifCmdData;

void _set_sreg(void *pkt, void *data)
{
    SifCmdSRegData *sr = pkt;
    SifCmdData *cd = data;

    cd->sreg[sr->rno] = sr->value;
}

void _change_addr(void *pkt, void *data)
{
    SifCmdChangeAddrData *ca = pkt;
    SifCmdData *cd = data;

    cd->iopbuf = ca->newaddr;
}

/* the member's .bss: the uncached send and ack buffers and the init packet on
   64-byte DMA lines, the DMAC handler id, the command data record, the system
   handler table (at least 16-byte aligned) and the software registers */
static int cmdSendBuf[32] __attribute__((aligned(64))); /* derived name */

static int cmdAckBuf[16] __attribute__((aligned(64))); /* derived name */

static int cmdInitPkt[5] __attribute__((aligned(64))); /* derived name */

static int cmdDmacId; /* derived name */

static SifCmdData cmdData; /* derived name */

static SifCmdEntry sysCmdTable[32] __attribute__((aligned(16))); /* derived name */

static int cmdSreg[32]; /* derived name */

int sceSifGetSreg(int reg)
{
    return cmdSreg[reg];
}

int sceSifSetSreg(int reg, int val)
{
    cmdSreg[reg] = val;
    return val;
}

void *sceSifGetDataTable(void)
{
    return &cmdData;
}

/* sifcmd.o's .data: set once sceSifInitCmd has run, cleared by sceSifExitCmd */
static int cmd_inited = 0; /* derived name */

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
    /* Both loops count up with the one i, which ends at 32 for the DMAC
       status write below. */
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
    if (*D_STAT & 0x20) {
        *D_STAT = 0x20;
    }
    if ((*D5_CHCR & 0x100) == 0) {
        sceSifSetDChain();
    }
    cmdDmacId = AddDmacHandler(5, _sceSifCmdIntrHdlr, 0);
    EnableDmac(5);
    cmdData.iopbuf = sceSifGetReg(0x80000000);
    if (cmdData.iopbuf != 0) {
        cmdInitPkt[4] = (int)cmdSendBuf;
        sceSifSendCmd(0x80000000, cmdInitPkt, 0x14, 0, 0, 0);
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
    sceSifSendCmd(0x80000002, cmdInitPkt, 0x14, 0, 0, 0);
}

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

/* The handler slot's address is worked as a byte offset into the table the
   id's sign selects, and cid itself then carries that table's address. */
void sceSifAddCmdHandler(int cid, void (*fn)(), void *data)
{
    int off = cid * 8;
    SifCmdEntry *h;
    if (cid >= 0)
        goto pos;
    cid = (int)cmdData.systbl;
    goto done;
pos:
    cid = (int)cmdData.usrtbl;
done:
    off += cid;
    h = (SifCmdEntry *)off;
    h->fn = fn;
    h->data = data;
}

void sceSifRemoveCmdHandler(int cid)
{
    int off = cid * 8;
    if (cid < 0) {
        cid = (int)cmdData.systbl;
    } else {
        cid = (int)cmdData.usrtbl;
    }
    off += cid;
    ((SifCmdEntry *)off)->fn = 0;
}

int _sceSifSendCmd(int cid, int mode, void *pkt, int pktsize, void *src, void *dest, int size)
{
    sceSifDmaData dmat[2];
    SifCmdHeader *header;
    int count;

    if (pktsize < 16 || pktsize > 112) {
        return 0;
    }
    header = pkt;
    count = 0;
    if (size > 0) {
        header->dsize = size;
        dmat[0].src = (unsigned int)src;
        dmat[0].dest = (unsigned int)dest;
        dmat[0].size = size;
        header->dest = dest;
        dmat[0].u.attr = 0;
        count = 1;
        if (mode & 4) {
            sceSifWriteBackDCache(src, size);
        }
    } else {
        header->dsize = 0;
        header->dest = 0;
    }
    dmat[count].src = (unsigned int)pkt;
    dmat[count].dest = cmdData.iopbuf;
    dmat[count].size = pktsize;
    header->cid = cid;
    header->psize = pktsize;
    dmat[count].u.attr = 0x44;
    count++;
    sceSifWriteBackDCache(pkt, pktsize);
    if (mode & 1) {
        return isceSifSetDma(dmat, count);
    }
    return sceSifSetDma(dmat, count);
}

unsigned int sceSifSendCmd(int cid, void *pkt, int pktsize, void *src, void *dest, int size)
{
    return _sceSifSendCmd(cid, 0, pkt, pktsize, src, dest, size);
}

unsigned int isceSifSendCmd(int cid, void *pkt, int pktsize, void *src, void *dest, int size)
{
    return _sceSifSendCmd(cid, 1, pkt, pktsize, src, dest, size);
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

/* The four `.align 2` directives below sit at the function's own internal
 * labels; they emit no bytes here, and without them the period assembler
 * inserts two nops before the first loop's closing bgtz. */
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

/* The jr that closes the block above has no delay-slot instruction of its
   own: the next object, libcdvd.a(cdvd000), starts with CB_DelayTh, whose
   first word sits in that slot. */
