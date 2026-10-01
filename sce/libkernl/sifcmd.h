/*
 * sce/libkernl/sifcmd.h
 *
 * The SIF command records this archive's sifrpc, iopreset and sifcmd members
 * share, under the PS2 SDK's public name for the SIF command interface's
 * header.  The SIF DMA and RPC records are in sifrpc.h.  Nothing here is
 * copied from an SDK header.
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

void sceSifRemoveCmdHandler(int cid); /* definition in sce/ */

unsigned int isceSifSendCmd(int cid, void *pkt, int pktsize, void *src, void *dest,
                            int size); /* definition in sce/ */

void sceSifAddCmdHandler(int cid, void (*fn)(), void *data); /* definition in sce/ */
int sceSifGetSreg(int reg);                                  /* definition in sce/ */
void sceSifInitCmd(void);                                    /* definition in sce/ */

unsigned int sceSifSendCmd(int cid, void *pkt, int pktsize, void *src, void *dest,
                           int size); /* definition in sce/ */

void sceSifSetDChain(void);                            /* the spelling at 1 site */
int isceSifSetDma(struct sceSifDmaData *sdd, int len); /* the spelling at 1 site */

#endif /* SCE_LIBKERNL_SIFCMD_H */
