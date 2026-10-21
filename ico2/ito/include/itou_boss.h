/*
 * ico2/ito/include/itou_boss.h
 *
 * The declarations of what itou_boss.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ITOU_BOSS_H
#define ITOU_BOSS_H

/* the functions itou_boss.c defines that other files name */
void actBossCtrlStart(void *gobj);
int InitBossCtrlGeo(void *gobj);
int InqCapsuleGhostBossEnd(void);
void BossCtrlGeo(void *self);

#endif /* ITOU_BOSS_H */
