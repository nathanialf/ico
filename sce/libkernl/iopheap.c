/* libkernl.a(iopheap.o) */

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

/* The LoadIopHeap RPC request block: the address argument at offset 0, the
 * module name copied in at offset 4, and i + 5 bytes sent, so the record is
 * one int followed by a 252-byte name and the sent length is the name length
 * plus the int plus the terminator. */
typedef struct {
    int addr;       /* 0x00 */
    char name[252]; /* 0x04 */
} SifHeapReq;

/* the LoadIopHeap RPC's send buffer, on its own 64-byte DMA line like the
   buffers above */
static SifHeapReq heapLoadReq __attribute__((aligned(64))); /* derived name */

int sceSifLoadIopHeap(char *name, void *addr)
{
    int i;

    if (iopheap_bind < 0) {
        return 0;
    }
    /* the terminator test reads the byte back out of the destination */
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
