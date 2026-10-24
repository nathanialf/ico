/*
 * ico2/ito/include/itou_boss.h
 *
 * The declarations of what itou_boss.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ITOU_BOSS_H
#define ITOU_BOSS_H

#ifdef VERSION_JUN26
/* the functions itou_boss.c defines that other files name */
void actBossCtrlStart(void *gobj);
int InitBossCtrlGeo(void *gobj);
int InqCapsuleGhostBossEnd(void);
void BossCtrlGeo(void *self);
#else
/* the functions itou_boss.c defines `inline` */
int InqCapsuleGhostBossStage(void);
void actBossCtrlStart(void *gobj);
int InitBossCtrlGeo(void *gobj);
void CapsuleGhostBossStart(void);
int InqCapsuleGhostBossEnd(void);

#ifdef VERSION_AUG6
/* declared ahead of the file's gene_eff_end_func prototype: Aug 6 emits it
   (0x195B40) before gene_eff_end_func (0x195B48) */
void BossCtrlDL(void);
#endif

void BossCtrlGeo(void *self);
void itou_boss_gflag_init(void);
#endif

#endif /* ITOU_BOSS_H */
