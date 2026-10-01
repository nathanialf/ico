/*
 * sce/libcdvd/libcdvd_internal.h  (derived name: the file name is ours)
 *
 * libcdvd's declarations that are not public SDK API: cdvd000.o's command
 * state (the semaphores, the RPC buffers and client records' companions, the
 * callback words), the command pre-checks and the callback and delay helpers
 * the other members call.  Each declaration is the definition's in
 * sce/libcdvd, which includes this header.
 */
#ifndef SCE_LIBCDVD_LIBCDVD_INTERNAL_H
#define SCE_LIBCDVD_LIBCDVD_INTERNAL_H

extern int SCE_CD_debug;
extern int _sceCd_ncmd_semid;
extern int _sceCd_scmd_semid;
extern int _sceCd_c_cb_sem;
extern int _sceCd_ee_read_mode;
/* volatile: the pending-callback id the callback thread polls and clears */
extern volatile int sceCdCbfunc_num;
extern int _sceCd_ncmdrdata[];
extern int _sceCd_ncmdsdata[];
extern int _sceCd_rd_intr_data[];
extern int _sceCd_Read_cur_pos[];
extern int _sceCd_cd_ncmd[];
extern int _sceCd_scmdrdata[];
extern char _sceCd_cd_scmd[];
int _sceCd_ncmd_prechk(int cmd);
int _sceCd_scmd_prechk(int cmd);
void _sceCd_cd_callback(int *data);
void _sceCd_cd_read_intr(void *pkt);
int sceCdNcmdDiskReady(void);
void sceCdDelayThread(unsigned short a0);
void CB_DelayTh(int id, unsigned short time, void *arg); /* file-scope asm in cdvd000.c */
int PowerOffCB(void);
void _Cdvd_cbLoop(void *arg);
void cdvd_exit(void);
void cmd_sem_init(void);

#endif /* SCE_LIBCDVD_LIBCDVD_INTERNAL_H */
