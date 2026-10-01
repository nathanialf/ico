/*
 * ico2/fumi/include/ios.h
 *
 * The declarations of what ios.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef IOS_H
#define IOS_H

/* ios.o's .sdata globals: the IOP heap shortfall and the memory
   partition handles iosMallocSetPartition hands back */
extern int iopBuffOver;
extern struct IosMemPart *ios_partition_root;
extern struct IosMemPart *ios_partition_event;
extern struct IosMemPart *ios_partition_isys;
extern struct IosMemPart *ios_partition_hara;
extern struct IosMemPart *ios_partition_sugipon;
extern struct IosMemPart *ios_partition_common;
extern struct IosMemPart *ios_partition_dmotion;
extern struct IosMemPart *ios_partition_smotion;
extern struct IosMemPart *ios_partition_s2motion;
extern struct IosMemPart *ios_partition_seki;
extern struct IosMemPart *ios_partition_oomori;
extern struct IosMemPart *ios_partition_horagai;
extern struct IosMemPart *ios_partition_sound;
extern struct IosMemPart *ios_partition_sound_semi;
extern struct IosMemPart *ios_partition_shock;
extern struct IosMemPart *ios_partition_inflate;
extern struct IosMemPart *ios_partition_mpeg;
extern int global_variable;

/* ios.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
int iosSifAllocIopHeapDebug(int size, char *file, int line);

void iosInitialize(void);
void ios_init_plus(void);

#endif /* IOS_H */
