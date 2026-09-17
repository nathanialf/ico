/*
 * ico2/common/include/sceneManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what sceneManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order sceneManager.c's inline tail has. */
void ChangeStageStartInfo(int a0, int a1, int a2, int a3, int t0);
char *CreateLayoutedGObj(int id, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
void MoveNextStage_Set(float *a0, float *a1, int a2, int a3, int a4, int a5);
void test_nextstage_firstwalk_set(int unused, int a, int b, int c);
int GetStageStartInfo(int a0, int a1, int a2, int *p, int *q, int *r);
void MoveNextStage_Clear(void);

void InitStageLight(int stage);
void initParentLink(int id);
void initSceneGObj(int stage, int id);

#endif /* SCENEMANAGER_H */
