#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void actSt13dInit(void);
void actSt13dInit(void);
inline void actSt13dInit(void) {}
INCLUDE_ASM("asm/nonmatchings/src/st13d", actSt13dExit);
INCLUDE_ASM("asm/nonmatchings/src/st13d", actSt13dExitR);
INCLUDE_ASM("asm/nonmatchings/src/st13d", actSt13dExitL);
