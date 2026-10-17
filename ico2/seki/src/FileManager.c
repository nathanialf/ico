#include "debug.h"
#include "cdvd.h"
#include "memory.h"
#include "ios.h"
#include <string.h>
#include <ctype.h>
#include <eekernel.h>
#include "FileManager.h"
#include "debug_exception.h"
#include <libcdvd.h>
#include <sifrpc.h>
#include <assert.h>
#include "include_asm.h"

/* libcdvd.h leaves sceCdlFILE incomplete.  This file's entry is 48 bytes,
   with a 32-byte name. */
typedef struct sceCdlFILE {
    unsigned int lsn;
    unsigned int size;
    char name[32];
    unsigned char date[8];
} sceCdlFILE;

/* Wait for the disc; inlined at all seven wait sites. */
static inline void file_WaitDisc(void) /* derived name */
{
    sceCdDiskReady(0);
    while (sceCdStatus() != 10)
        ;
}

INCLUDE_ASM(file_Init);

static int file_LoadCDFile(void **adr, char *fname, int area);

INCLUDE_ASM(file_LoadCDFile);

int file_LoadFile(void **adr, char *fname, int area)
{
    return file_LoadCDFile(adr, fname, area);
}
