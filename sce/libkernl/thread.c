/* Vendor SCE library member: libkernl.a(thread.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x100D68..0x1010C8, 5 functions. */

/* EE syscall leaf wrappers.  This member's uses stand for a Sony-internal
   header this tree cannot name: MAIN.MAP attests archives and their members,
   never a header, so the definitions are kept per member.  Body is the
   four-instruction leaf `addiu $3,$zero,NUM; syscall 0; jr $31; nop`, the
   last two supplied by gcc's epilogue. */
#define SYSCALL_WRAPPER(name, num)                                                                 \
    void name(void)                                                                                \
    {                                                                                              \
        __asm__ __volatile__("addiu $3, $0, " #num "\n\tsyscall 0" : : : "$3", "memory");          \
    }
/* The same leaf issued INLINE, for the members that act on its result.
   `dst` is bound to $v0 because that is where the kernel ABI leaves the
   result; a plain "=r" output would let gcc pick a register the kernel
   never writes.  Operand binding, not a scheduling pin. */
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
    int f0;
    int widx;
    KernEvent ent[512];
} KernEventRing;

/* the kernel event thread's stack, the semaphore that wakes it and the ring
   of events the interrupt-side calls post to it */
static char kernEventStack[0x400]; /* derived name */

static int kernEventSema; /* derived name */

static KernEventRing kernEventRing; /* derived name */

extern int WaitSema(int id);
extern int WakeupThread(int id);
extern int RotateThreadReadyQueue(int id);
extern int SuspendThread(int id);
extern void kprintf(const char *fmt);

void topThread(void *arg)
{
    KernEventRing *ring = (KernEventRing *)arg;
    int i;

    while (1) {
        WaitSema(kernEventSema);
        i = ring->f0 & 0x1FF;
        ring->f0 = i + 1;
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

/* EE kernel thread/semaphore parameter blocks.  The field offsets are the
   ROM's own stores; the members this function never touches are named from
   the published EE kernel ABI. */
typedef struct {
    int count;        /* 0x00 */
    int max_count;    /* 0x04 */
    int init_count;   /* 0x08 */
    int wait_threads; /* 0x0C */
    unsigned attr;    /* 0x10 */
    unsigned option;  /* 0x14 */
} ee_sema_t;

typedef struct {
    int status;           /* 0x00 */
    void *func;           /* 0x04 */
    void *stack;          /* 0x08 */
    int stack_size;       /* 0x0C */
    void *gp_reg;         /* 0x10 */
    int initial_priority; /* 0x14 */
    int current_priority; /* 0x18 */
    unsigned attr;        /* 0x1C */
    unsigned option;      /* 0x20 */
} ee_thread_t;

/* the kernel event thread's id, zero until InitKernEvent creates it */
static int kernEventThreadId = 0;

extern char _gp[];
extern void topThread(void *arg);
extern int CreateSema(ee_sema_t *param);
extern void DeleteSema(int id);
extern int CreateThread(ee_thread_t *param);
extern int StartThread(int id, void *arg);
extern int GetThreadId(void);
extern int ChangeThreadPriority(int id, int prio);

int InitThread(void)
{
    ee_thread_t th;
    ee_sema_t sm;
    int tid;

    if (kernEventThreadId > 0) {
        return -1;
    }

    sm.max_count = 0xFF;
    sm.init_count = 0;
    kernEventSema = CreateSema(&sm);
    if (kernEventSema < 0) {
        return -1;
    }

    th.func = topThread;
    th.stack = kernEventStack;
    th.stack_size = 0x400;
    th.gp_reg = _gp;
    th.initial_priority = 0;
    tid = CreateThread(&th);
    kernEventThreadId = tid;
    if (tid < 0) {
        DeleteSema(kernEventSema);
        return -1;
    }

    kernEventRing.f0 = 0;
    kernEventRing.widx = 0;
    StartThread(tid, &kernEventRing);
    ChangeThreadPriority(GetThreadId(), 1);
    return kernEventThreadId;
}

extern int _iWakeupThread(void);
extern int iSignalSema(int handle);

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

extern int _iSuspendThread(void);

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
