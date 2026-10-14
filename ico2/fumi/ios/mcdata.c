#include "cdvd.h"
#include "mcdata.h"
#include "thread.h"
#include "mcard.h"
#include "include_asm.h"

struct McIconWork { /* field names derived */
    int remain;
    int size;
    void *buf;
}; /* derived name */

/* the flag the mcard thread raises when the request the caller is spinning
   on has finished */
static int mcDataDone; /* derived name */

/* Background-read callback: pulls the icon file off the disc a chunk at a
   time into a 64-byte aligned buffer and waits for the writer to drain it. */
static int _iosMcIconWriteIconsys(CdvdBgReq *self, struct McIconWork *p);

INCLUDE_ASM(iosMcIconWriteIconsys);

INCLUDE_ASM(iosMcIconWriteIcon);

INCLUDE_ASM(_iosMcIconWriteIconsys);
