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

#endif /* MAIN_H */
