/*
 * ico2/fumi/include/act-parallel-control.h
 *
 * The declarations of what act-parallel-control.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_PARALLEL_CONTROL_H
#define ACT_PARALLEL_CONTROL_H

int *ActPara_GetDefTbl(void);
void ActPara_InitSystem(void);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
void ActPara_MakeTbl(int *tbl, int mask, int n);
#else
void ActPara_MakeTbl(int *tbl, unsigned long long mask, int n);
#endif

/* motion-random-def.o's table (a data-only member, extracted from the base
   ELF at build time): 1147-terminated runs of motion ids that
   ActPara_MakeTbl picks from for a layout entry above 0xFFFF. */
extern const int randomMotionKind[];

/* parallel-motion-tbl: one parallel action's motions, 0xB0 bytes; motion[0]
 * is its id. Reader: ico2/fumi/src/act-parallel-control.c. Owner:
 * ico2/fumi/include/act-parallel-control.h. */
typedef struct { /* field names derived */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    int motion[37]; /* 0x00, one per status bit */
#else
    int motion[44]; /* 0x00, one per status bit */
#endif
} ParallelMotionRow; /* derived name */

extern ParallelMotionRow parallelMotionTbl[];

#endif /* ACT_PARALLEL_CONTROL_H */
