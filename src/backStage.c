#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void backStageProcessInit(void);
void backStageDebugTimeZero(void);
void backStageTsuresariReturn(void);
void backStageProcessInit(void);
void backStageDebugTimeZero(void);
void backStageTsuresariReturn(void);
extern int D_0063ACF0;
extern int D_0063C350;
extern int D_0063C354;
extern int D_0063C358;
extern int D_0063C35C;
extern int D_0063C360;
extern int D_0063C364;
extern int D_0063C368;
extern int D_0063C36C;
extern int func_001B6CA0(void *, void *, int);
extern int gamesysMemoryHandlerRead(void *, void *, int);
extern int D_0063C370;
inline void backStageProcessInit(void) {
    D_0063ACF0 = 0;
    D_0063C35C = -1;
    D_0063C350 = 0;
    D_0063C370 = 0;
}
inline void backStageDebugTimeZero(void) {
    D_0063C354 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageProcessOutStage);
INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageProcessMain);
INCLUDE_ASM("asm/nonmatchings/src/backStage", routeSetPos);
INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageProcessInStage);
void backStageSave(void *a0) {
    func_001B6CA0(a0, &D_0063ACF0, 4);
    func_001B6CA0(a0, &D_0063C350, 4);
    func_001B6CA0(a0, &D_0063C354, 4);
    func_001B6CA0(a0, &D_0063C358, 4);
    func_001B6CA0(a0, &D_0063C35C, 4);
    func_001B6CA0(a0, &D_0063C360, 4);
    func_001B6CA0(a0, &D_0063C364, 4);
    func_001B6CA0(a0, &D_0063C368, 4);
    func_001B6CA0(a0, &D_0063C36C, 4);
}
void backStageLoad(void *a0) {
    gamesysMemoryHandlerRead(a0, &D_0063ACF0, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C350, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C354, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C358, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C35C, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C360, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C364, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C368, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C36C, 4);
}
inline void backStageTsuresariReturn(void) {}
