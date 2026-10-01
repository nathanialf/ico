/*
 * sce/libkernl/sifrpc.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (sifrpc.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBKERNL_SIFRPC_H
#define SCE_LIBKERNL_SIFRPC_H

/* the SIF records are defined in sifcmd.h, which only the libraries
   include */
struct sceSifDmaData;

struct sceSifRpcClientData;

struct sceSifServeData;

extern char __ps2_klibinfo__[]; /* klib.s's library stamp; bytes 12..15 are the version */
int _sceSifLoadElfPart(void *a0, int a1, int a2, int a3);

int _sceSifLoadModule(void *a0, int a1, int a2, int a3,
                      int a4); /* returns the module id or a negative error */

int _sceSifLoadModuleBuffer(void *a0, int a1, int a2, void *a3);
int _sceSifSendCmd(int cid, int mode, void *pkt, int pktsize, void *src, void *dest, int size);
int sceSifAllocIopHeap(int a0); /* definition in sce/ */
int sceSifBindRpc(struct sceSifRpcClientData *cd, unsigned int sid, int mode);

int sceSifCallRpc(struct sceSifRpcClientData *cd, unsigned int rpc_number, unsigned int mode,
                  void *sendbuf, int ssize, void *recvbuf, int rsize, void (*end_func)(void *),
                  void *end_param);

int sceSifCheckStatRpc(struct sceSifRpcClientData *cd); /* definition in sce/ */
int sceSifDmaStat(int h);
void sceSifExecRequest(struct sceSifServeData *sd);
void sceSifExitCmd(void);      /* definition in sce/ */
int sceSifFreeIopHeap(int a0); /* definition in sce/ */

unsigned int
sceSifGetReg(unsigned int a0); /* the register number is unsigned, see sceSifResetIop */

int sceSifInitIopHeap(void);                     /* definition in sce/ */
void sceSifInitRpc(int mode);                    /* definition in sce/ */
int sceSifLoadFileReset(void);                   /* definition in sce/ */
void sceSifLoadModule(void *a0, int a1, int a2); /* definition in sce/ */
int sceSifRebootIop(const char *img);
int sceSifSetDma(struct sceSifDmaData *sdd, int len);
unsigned int sceSifSetReg(int a0, int a1); /* returns a value */
int sceSifSyncIop(void);                   /* definition in sce/ */
void sceSifWriteBackDCache(void *addr, int len);
void sceSifExitRpc(void);                /* definition in sce/ */
void sceSifStopDma(void);                /* the spelling at 1 site */
int sceSifResetIop(char *arg, int mode); /* definition in sce/ */

#endif /* SCE_LIBKERNL_SIFRPC_H */
