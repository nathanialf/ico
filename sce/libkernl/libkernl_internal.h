/*
 * sce/libkernl/libkernl_internal.h  (derived name: the file name is ours)
 *
 * libkernl's declarations that are not in the public headers this tree
 * reconstructs (eekernel.h, sifdev.h, sifrpc.h, sifcmd.h): the start-up
 * helpers _InitSys calls, the DECI2 and tty layer, the file stub's and the
 * SIF members' internal helpers, and the assembled TLB and cache entry
 * points the C members call.  Each declaration is the definition's in
 * sce/libkernl.
 */
#ifndef SCE_LIBKERNL_LIBKERNL_INTERNAL_H
#define SCE_LIBKERNL_LIBKERNL_INTERNAL_H

int Deci2Call(int req, void *args);         /* the spelling at 1 site */
void InitAlarm(void);                       /* definition in sce/ */
int InitThread(void);                       /* definition in sce/ */
int _iSuspendThread(void);                  /* the spelling at 1 site */
int _iWakeupThread(void);                   /* the spelling at 1 site */
extern char _kDebugException[];             /* the spelling at 1 site */
void _kExitTLBHandler(void);                /* the spelling at 1 site */
void _kTLBException(void);                  /* the spelling at 1 site */
void _change_addr(void *pkt, void *data);   /* definition in sce/ */
void _set_sreg(void *pkt, void *data);      /* definition in sce/ */
int _sceSifCmdIntrHdlr(int channel);        /* AddDmacHandler's handler, asm definition in sce/ */
void _request_bind(void *pkt, void *data);  /* definition in sce/ */
void _request_call(void *pkt, void *data);  /* definition in sce/ */
void _request_end(void *pkt, void *data);   /* definition in sce/ */
void _request_rdata(void *pkt, void *data); /* definition in sce/ */
int _sceCallCode(void *name, int code);     /* definition in sce/ */
void _sceFsIobSemaMK(void);                 /* definition in sce/ */
void _sceFsSigSema(void);                   /* definition in sce/ */
void _sceIDC(int a0, int a1);               /* the spelling at 1 site, asm definition in sce/ */
void _sceSDC(int a0, int a1);               /* the spelling at 1 site, asm definition in sce/ */
void deci2Putchar(int c);                   /* definition in sce/ */
void *get_iob(unsigned int i);              /* definition in sce/ */
void kExpandScratchPad(void);               /* the spelling at 1 site, asm definition in sce/ */
void kGetTLBEntry(void);                    /* the spelling at 1 site, asm definition in sce/ */
void kProbeTLBEntry(void);                  /* the spelling at 1 site, asm definition in sce/ */
void kPutTLBEntry(void);                    /* the spelling at 1 site, asm definition in sce/ */
void kSetTLBEntry(void);                    /* the spelling at 1 site, asm definition in sce/ */
void kprintf(char *fmt, ...);               /* definition in sce/ */
void kputs(char *s);                        /* definition in sce/ */
int sceDeci2ExRecv(int s, void *buf, unsigned short len);            /* definition in sce/ */
int sceDeci2ExSend(int s, void *buf, unsigned short len);            /* definition in sce/ */
int sceDeci2Open(unsigned short protocol, void *opt, void *handler); /* definition in sce/ */
void sceDeci2Poll(int s);                                            /* definition in sce/ */
int sceDeci2ReqSend(int s, signed char a1);                          /* definition in sce/ */
int sceFsInit(void);                                                 /* definition in sce/ */
void sceResetttyinit(void);                                          /* definition in sce/ */
void sceTtyHandler(int event, int param, void *opt);                 /* definition in sce/ */
int sceTtyInit(void);                                                /* definition in sce/ */
int sceTtyRead(void *buf, int size);                                 /* definition in sce/ */
int sceTtyWrite(const char *buf, int len);                           /* definition in sce/ */
void topThread(void *arg);                                           /* definition in sce/ */

#endif /* SCE_LIBKERNL_LIBKERNL_INTERNAL_H */
