/*
 * ico2/ito/include/itou_boss.h
 *
 * The declarations of what itou_boss.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ITOU_BOSS_H
#define ITOU_BOSS_H

/* the functions itou_boss.c defines `inline` */
int InqCapsuleGhostBossStage(void);
void actBossCtrlStart(void *a0);
int InitBossCtrlGeo(void *a0);
void CapsuleGhostBossStart(void);
int InqCapsuleGhostBossEnd(void);
void BossCtrlGeo(void *self);
void itou_boss_gflag_init(void);
inline void gene_eff_end_func(int id);

#endif /* ITOU_BOSS_H */
