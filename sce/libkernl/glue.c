/* libkernl.a(glue.o) */
#include <eeregs.h>
#include <eekernel.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libkernl_internal.h>

/* glue.o's .data: whether the tty is open (write and read open it on first
   use), then sbrk's current break, which starts at the end of the program's
   bss (the linker's _end).  Neither has a global symbol, so both are
   statics. */
/* The link's end of .bss, which no header declares */
extern char _end[];

static int tty_opened = 0;

static char *heap_ptr = _end;

void sceResetttyinit(void)
{
    tty_opened = 0;
    sceTtyInit();
}

/* VSync polls INTC_STAT (0x1000F000) for the VBLANK bit and clears it: a
   busy-wait on a hardware register, written as a whole-function asm. */
__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global VSync\n"
        ".type VSync, @function\n"
        "    .align 3\n"
        "VSync:\n"
        "    lui $2, (0x1000F000 >> 16)\n"
        "    addiu $3, $0, 0x4\n"
        "    ori $2, $2, (0x1000F000 & 0xFFFF)\n"
        "    sw $3, 0x0($2)\n"
        ".LVSync0025EF38:\n"
        "    lui $2, (0x10010000 >> 16)\n"
        "    lw $2, -0x1000($2)\n"
        "    andi $2, $2, 0x4\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    beqz $2, .LVSync0025EF38\n"
        "    nop\n"
        "    addiu $2, $0, 0x4\n"
        "    lui $1, (0x10010000 >> 16)\n"
        "    jr $31\n"
        "    sw $2, -0x1000($1)\n"
        "    .set reorder\n"
        "    .set at\n");

long long VSync2(void)
{
    volatile int flag;
    volatile long long val;
    volatile int *p;
    flag = 0;
    SetVSyncFlag((void *)&flag, (void *)&val);
    p = INTC_STAT;
    *p = 4;
    while ((*p & 4) == 0 && flag == 0) {}
    *p = 4;
    return val;
}

int write(int fd, void *buf, int size)
{
    if (fd - 1 < 2U) {
        if (tty_opened == 0) {
            if (sceTtyInit() == 0) {
                return -1;
            }
            tty_opened = 1;
        }
        return sceTtyWrite(buf, size);
    }
    return -1;
}

int read(int fd, void *buf, int size)
{
    if (fd == 0) {
        if (tty_opened == 0) {
            if (sceTtyInit() == 0) {
                return -1;
            }
            tty_opened = 1;
        }
        return sceTtyRead(buf, size);
    }
    return -1;
}

int open(void)
{
    *(int *)__errno() = 5;
    return -1;
}

int close(int a1)
{
    return -1;
}

int ioctl(void)
{
    return -1;
}

long lseek(int fd, long offset, int whence)
{
    return -1;
}

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global sbrk\n"
        ".type sbrk, @function\n"
        "    .align 3\n"
        "sbrk:\n"
        "    addiu $29, $29, -0x40\n"
        "    sd $31, 0x30($29)\n"
        "    sd $18, 0x20($29)\n"
        "    sd $17, 0x10($29)\n"
        "    sd $16, 0x0($29)\n"
        "    mfc0 $17, $12\n"
        "    lui $2, (0x10000 >> 16)\n"
        "    and $17, $17, $2\n"
        "    beqz $17, .Lsbrk00241B14\n"
        "    lui $18, %hi(heap_ptr)\n"
        ".Lsbrk00241AF0:\n"
        "    di\n"
        "    sync.p\n"
        "    mfc0 $2, $12\n"
        "    lui $3, (0x10000 >> 16)\n"
        "    and $2, $2, $3\n"
        "    bnez $2, .Lsbrk00241AF0\n"
        "    nop\n"
        "    b .Lsbrk00241B18\n"
        "    lw $2, %lo(heap_ptr)($18)\n"
        ".Lsbrk00241B14:\n"
        "    lw $2, %lo(heap_ptr)($18)\n"
        ".Lsbrk00241B18:\n"
        "    jal EndOfHeap\n"
        "    addu $16, $2, $4\n"
        "    sltu $2, $2, $16\n"
        "    beqz $2, .Lsbrk00241B50\n"
        "    lw $2, %lo(heap_ptr)($18)\n"
        "    jal __errno\n"
        "    nop\n"
        "    addiu $3, $0, 0xC\n"
        "    beqz $17, .Lsbrk00241B44\n"
        "    sw $3, 0x0($2)\n"
        "    ei\n"
        ".Lsbrk00241B44:\n"
        "    lui $2, (0xFFFFFFFF >> 16)\n"
        "    b .Lsbrk00241B5C\n"
        "    ori $2, $2, (0xFFFFFFFF & 0xFFFF)\n"
        ".Lsbrk00241B50:\n"
        "    beqz $17, .Lsbrk00241B5C\n"
        "    sw $16, %lo(heap_ptr)($18)\n"
        "    ei\n"
        ".Lsbrk00241B5C:\n"
        "    ld $31, 0x30($29)\n"
        "    ld $18, 0x20($29)\n"
        "    ld $17, 0x10($29)\n"
        "    ld $16, 0x0($29)\n"
        "    jr $31\n"
        "    addiu $29, $29, 0x40\n"
        ".size sbrk, . - sbrk\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

int isatty(int fd)
{
    return 1;
}

int fstat(int fd, struct stat *st)
{
    st->st_blksize = 0;
    st->st_mode = S_IFCHR;
    return 0;
}

int getpid(void)
{
    return 1;
}

int kill(int pid, int sig)
{
    if (pid == 1) {
        Exit(sig);
    }
    return 0;
}

int stat(void)
{
    *(int *)__errno() = 5;
    return -1;
}

int unlink(void)
{
    *(int *)__errno() = 5;
    return -1;
}
