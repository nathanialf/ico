/*
 * ico2/common/include/main.h
 *
 * RECONSTRUCTION: the disc records no file of this name (a header that only
 * declares leaves no rows in SRCFILE.TXT). It declares the globals main.c
 * defines, as main.c defines them; the other TUs still carry their own
 * extern spellings of these objects.
 */
#ifndef MAIN_H
#define MAIN_H

#include "typedef.h"

extern int systemStatus[12];
extern int db[140];
extern StageSetting GlobalStageSetting;
extern PadState pad[16];
extern int stageMgrMsg[6];
extern int SchedulerMsgQ[12];

/* .sdata; the ones marked derived are named by this tree, the rest by MAIN.MAP */
extern char NetLoadTARGET[];
extern int buffer_ID;
extern int odd_even;
extern int frame_count;
extern char *matrixptr;
extern int debugMoveMode;
extern int stage_no;
extern int before_stage_no;
extern int exit_no;
extern int motionFrameUpdate;
extern int interlace;
extern int thisIsYourStartStage;
extern int NonLinearCameraMove;
extern int GlobalTimer;
extern int lock_execIcoMisc;
extern int graphics_ready;
extern int game_pause;
extern int data_loading;
extern int screen_offset_x;
extern int screen_offset_y;
extern int fall_death_active;
extern int title_fading_out;
extern int collis_flg_stock;
extern int IosPadLock;
extern int IosCdLock;
extern int IosSndLock;
extern int IosStgMgrLock;
extern int systemFault;
extern int optionControlType; /* derived name */
extern int optionScreenMode;  /* derived name */
extern int girlControlMode;   /* derived name */
extern GObj *boyGObj;
extern GObj *girlGObj;
extern int boyPad;
extern int girlPad; /* derived name */
extern int gameover_flag;
extern int gameover_layout_flag;
extern int itemWatchOff; /* derived name */
extern GObj *CurrentTargetGObj;
extern GObj *CurrentTargetGObjSub;
extern int current_stage_no;
extern void (*system_stage_func)(void);
extern int InterStageSwitchLock;

#endif /* MAIN_H */
