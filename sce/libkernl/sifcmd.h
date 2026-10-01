/*
 * sce/libkernl/sifcmd.h
 *
 * PUBLIC SDK NAMING RUNG, as sifrpc.h: the PS2 SDK's header for the SIF command
 * interface is called sifcmd.h and this archive's sifrpc, iopreset and sifcmd
 * members share its records.  The records are the tree's own reconstructions
 * (each carries its measurement below); nothing here is copied from an SDK
 * header.  Only libkernl's members include it.
 */
#ifndef SCE_LIBKERNL_SIFCMD_H
#define SCE_LIBKERNL_SIFCMD_H

/* Reconstruction: the SIF command packet the EE sends to the IOP kernel to
   ask for a reset.  psize is the byte count of the whole packet and dsize
   the DMA payload length; the ROM writes dsize through a 64-bit read/modify/
   write, which is get_best_mode picking DImode off the packet's 16-byte
   alignment. */
/* RECONSTRUCTION (user ruling 2026-09-22): the command id has its own
   type.  The ROM's schedule of _sceSifSendCmd needs the cid store outside
   the alias set of the int stores that fill the DMA records (the compiler's
   sched2 dump gives int set 1 and this enum set 10); with a plain int cid
   three words of that function come out in the wrong order.  Only the zero
   member is attested by the bytes; the developers' list of command ids is
   not recoverable from this member.  Re-audit (completeness pass 57): the
   public SDK naming's plain `int cid` was measured and changes 14 words of
   the object. */
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

    /* RECONSTRUCTION (user ruling 2026-09-22, same class as layout_action's
       R8Flags): the attribute word is reached through a union member.  The
       ROM's codegen of _sceSifSendCmd proves the store is an alias-set-0
       access: on the compiler's sched2 dump it must conflict with both the
       cid store and the size store while the cid store leaves the size
       store's set, and a 32-bit store gets set 0 only from a direct union
       member.  Only the word member is attested by the bytes; the
       developers' union may have carried a flag-bit view beside it.
       Re-audit (completeness pass 57): the public SDK naming's plain
       `int attr` was measured and puts three words of _sceSifSendCmd out of
       order. */
    union {
        int attr;
    } u;
} SifDmaTransfer;

void sceSifRemoveCmdHandler(int a0);                                /* definition in sce/ */
int isceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1); /* definition in sce/ */
int sceSifAddCmdHandler(int a0, int a1, int a2);                    /* definition in sce/ */
int sceSifGetSreg(int a0);                                          /* definition in sce/ */
void sceSifInitCmd(void);                                           /* definition in sce/ */
int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1);  /* definition in sce/ */
void sceSifSetDChain(void);                                         /* the spelling at 1 site */
int isceSifSetDma(int p, int a);                                    /* the spelling at 1 site */

#endif /* SCE_LIBKERNL_SIFCMD_H */
