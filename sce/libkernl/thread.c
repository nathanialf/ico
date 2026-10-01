/* libkernl.a(thread.o) */
#include <eekernel.h>
#include <libkernl_internal.h>

/* An EE syscall leaf (`addiu $3,$zero,NUM; syscall 0`) issued inline, for
   the calls that act on its result.  The syscall returns in $2. */
#define SYSCALL_INLINE(num, dst)                                                                   \
    {                                                                                              \
        register int __sc_ret __asm__("$2");                                                       \
        __asm__ __volatile__("addiu $3, $0, " #num "\n\tsyscall 0"                                 \
                             : "=r"(__sc_ret)                                                      \
                             :                                                                     \
                             : "$3", "memory");                                                    \
        (dst) = __sc_ret;                                                                          \
    }

typedef struct {
    unsigned char code;
    unsigned char id;
} KernEvent;

typedef struct {
    int ridx;
    int widx;
    KernEvent ent[512];
} KernEventRing;

/* the kernel event thread's stack (16-byte aligned, as CreateThread
   requires), the semaphore that wakes it and the ring of events the
   interrupt-side calls post to it */
static char kernEventStack[0x400] __attribute__((aligned(16))); /* derived name */

static int kernEventSema; /* derived name */

static KernEventRing kernEventRing; /* derived name */

void topThread(void *arg)
{
    KernEventRing *ring = (KernEventRing *)arg;
    int i;

    while (1) {
        WaitSema(kernEventSema);
        i = ring->ridx & 0x1FF;
        ring->ridx = i + 1;
        switch (ring->ent[i].code) {
        case 0:
            WakeupThread(ring->ent[i].id);
            break;
        case 1:
            RotateThreadReadyQueue(ring->ent[i].id);
            break;
        case 2:
            SuspendThread(ring->ent[i].id);
            break;
        default:
            kprintf("## internel error in libkernl.a!\n");
            break;
        }
    }
}

/* the kernel event thread's id, zero until InitKernEvent creates it */
static int kernEventThreadId = 0; /* derived name */

/* The link's small-data base, which no header declares */
extern char _gp[];

int InitThread(void)
{
    struct ThreadParam th;
    struct SemaParam sm;
    int tid;

    if (kernEventThreadId > 0) {
        return -1;
    }

    sm.maxCount = 0xFF;
    sm.initCount = 0;
    kernEventSema = CreateSema(&sm);
    if (kernEventSema < 0) {
        return -1;
    }

    th.entry = topThread;
    th.stack = kernEventStack;
    th.stackSize = 0x400;
    th.gpReg = _gp;
    th.initPriority = 0;
    tid = CreateThread(&th);
    kernEventThreadId = tid;
    if (tid < 0) {
        DeleteSema(kernEventSema);
        return -1;
    }

    kernEventRing.ridx = 0;
    kernEventRing.widx = 0;
    StartThread(tid, &kernEventRing);
    ChangeThreadPriority(GetThreadId(), 1);
    return kernEventThreadId;
}

int iWakeupThread(int id)
{
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return _iWakeupThread();
    }
    if ((unsigned int)r >= 0x100) {
        goto fail;
    }
    if (kernEventThreadId != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = kernEventRing.widx & 0x1FF;
    kernEventRing.widx = i + 1;
    kernEventRing.ent[i].code = 0;
    kernEventRing.ent[i].id = r;
    iSignalSema(kernEventSema);
    return r;
}

int iRotateThreadReadyQueue(int id)
{
    int i;
    if ((unsigned int)id >= 0x80) {
        goto fail;
    }
    if (kernEventThreadId != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = kernEventRing.widx & 0x1FF;
    kernEventRing.widx = i + 1;
    kernEventRing.ent[i].code = 1;
    kernEventRing.ent[i].id = id;
    iSignalSema(kernEventSema);
    return id;
}

int iSuspendThread(int id)
{
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return _iSuspendThread();
    }
    if ((unsigned int)r >= 0x100) {
        goto fail;
    }
    if (kernEventThreadId != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = kernEventRing.widx & 0x1FF;
    kernEventRing.widx = i + 1;
    kernEventRing.ent[i].code = 2;
    kernEventRing.ent[i].id = r;
    iSignalSema(kernEventSema);
    return r;
}
