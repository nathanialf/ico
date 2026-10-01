/*
 * sce/libkernl/sifcmd.h
 *
 * The SIF command records this archive's sifrpc, iopreset and sifcmd members
 * share, under the PS2 SDK's public name for the SIF command interface's
 * header.  Nothing here is copied from an SDK header.  libkernl's members
 * include it, and libcdvd's cdvd000.o for sceSifAddCmdHandler.
 */
#ifndef SCE_LIBKERNL_SIFCMD_H
#define SCE_LIBKERNL_SIFCMD_H

/* the SIF command packet the EE sends to the IOP kernel to ask for a reset.
   psize is the byte count of the whole packet and dsize the DMA payload
   length; the packet is 16-byte aligned. */
/* the command id has its own type.  Only the zero member is known; the
   developers' list of command ids is not recoverable from this member. */
typedef enum { SIF_CMD_DIAG = 0 } SifCmdId;

typedef struct {
    unsigned int psize : 8;
    unsigned int dsize : 24;
    void *dest;
    SifCmdId cid;
    unsigned int opt;
} SifCmdHeader;

typedef struct {
    SifCmdHeader header;
    int arglen;
    int mode;
    char arg[80];
} SifCmdResetData;

typedef struct {
    int src;
    int dest;
    int size;

    /* the attribute word is reached through a union member.  Only the word
       member is known; the developers' union may have carried a flag-bit
       view beside it. */
    union {
        int attr;
    } u;
} SifDmaTransfer;

void sceSifRemoveCmdHandler(int a0);                                /* definition in sce/ */
int isceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1); /* definition in sce/ */
void sceSifAddCmdHandler(int a0, int a1, int a2);                   /* definition in sce/ */
int sceSifGetSreg(int a0);                                          /* definition in sce/ */
void sceSifInitCmd(void);                                           /* definition in sce/ */
int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1);  /* definition in sce/ */
void sceSifSetDChain(void);                                         /* the spelling at 1 site */
int isceSifSetDma(int p, int a);                                    /* the spelling at 1 site */

#endif /* SCE_LIBKERNL_SIFCMD_H */
