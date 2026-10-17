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

/* This build has no request-done flag here (no function of the demo
   addresses one). */

INCLUDE_ASM(D_002695F8);

/* Background-read callback: pulls the icon file off the disc a chunk at a
   time into a 64-byte aligned buffer and waits for the writer to drain it. */
INCLUDE_ASM(iosMcIconWriteIconsys);

INCLUDE_ASM(iosMcIconWriteIcon);

INCLUDE_ASM(_iosMcIconWriteIconsys);
