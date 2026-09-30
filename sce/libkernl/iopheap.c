/* Vendor SCE library member: libkernl.a(iopheap.o).  MAIN.MAP names the
 * member and its .text size (0x260), which tiles the shipped ELF from one
 * retail function start to the next; VMA 0x263C40..0x263EA0,
 * 4 functions. */

#include <sifrpc.h>
#include <string.h>

/* iopheap.o's .data: -1 until sceSifInitIopHeap has bound the server */
static int iopheap_bind = -1;

/* the member's .bss: the heap server's client record and the RPC buffers,
   each on its own 64-byte DMA line */
static int heapClient[10] __attribute__((aligned(64))); /* derived name */

static int heapRecv __attribute__((aligned(64)));     /* derived name */
static int heapAllocArg __attribute__((aligned(64))); /* derived name */
static int heapFreeArg __attribute__((aligned(64)));  /* derived name */
extern char D_FFFFF[];

int sceSifInitIopHeap(void)
{
    int i;
    int ret;
    int val;
    for (;;) {
        ret = sceSifBindRpc(heapClient, 0x80000003, 0);
        if (ret < 0)
            return -1;
        val = heapClient[0x24 / 4];
        if (val != 0) {
            iopheap_bind = 0;
            break;
        }
        /* IOP-side retry back-off: spin 0x100000 times, no memory touched. */
        i = 0x100000;
        do {
            i--;
        } while (i != -1);
    }
    return 0;
}

int sceSifAllocIopHeap(int a0)
{
    int ret = iopheap_bind;
    if (ret < 0)
        return 0;
    heapAllocArg = a0;
    ret = sceSifCallRpc(heapClient, 1, 0, &heapAllocArg, 4, &heapRecv, 4, 0, 0);
    if (ret >= 0)
        return heapRecv;
    return 0;
}

int sceSifFreeIopHeap(int a0)
{
    int v2 = iopheap_bind;
    if (v2 < 0)
        return 0;
    heapFreeArg = a0;
    v2 = sceSifCallRpc(heapClient, 2, 0, &heapFreeArg, 4, &heapRecv, 4, 0, 0);
    if (v2 < 0)
        return -1;
    return heapRecv;
}

/* The LoadIopHeap RPC request block, reconstructed: the ROM stores the address
 * argument at offset 0, copies the module name into offset 4 and sends
 * i + 5 bytes, so the record is one int followed by a 252-byte name and the
 * sent length is the name length plus the int plus the terminator.  It is
 * spelled as a struct rather than as `char heapLoadReq[]` because the ROM's
 * destination address is `addu $3,$3,$8`, base first: the C front end builds
 * `arr[j]` on an array object as PLUS_EXPR(ADDR_EXPR(arr), j), fold moves the
 * TREE_CONSTANT array address to the right and expand then emits
 * `addu dest,index,base`, while a COMPONENT_REF of a struct reaches expand
 * with the base already in a register and keeps the ROM's order. */
typedef struct {
    int addr;       /* 0x00 */
    char name[252]; /* 0x04 */
} SifHeapReq;

static SifHeapReq heapLoadReq __attribute__((aligned(64))); /* derived name */

int sceSifLoadIopHeap(char *name, void *addr)
{
    int i;

    if (iopheap_bind < 0) {
        return 0;
    }
    /* the terminator test reads the byte back out of the DESTINATION, which is
     * the value cse already holds; reading name[i] again cannot be folded away
     * because the char store may alias the char load, and the ROM loads the
     * name byte once (lbu, then sll 24 and beqz on the same register) */
    for (i = 0; i < 252; i++) {
        heapLoadReq.name[i] = name[i];
        if (heapLoadReq.name[i] == 0) {
            break;
        }
    }
    if (i == 252) {
        heapLoadReq.name[251] = 0;
        i = 251;
    }
    heapLoadReq.addr = (int)addr;
    heapLoadReq.name[251] = 0;
    if (sceSifCallRpc(heapClient, 3, 0, &heapLoadReq, i + 5, &heapRecv, 4, 0, 0) >= 0) {
        return heapRecv;
    }
    return -1;
}
