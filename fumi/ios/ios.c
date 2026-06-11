#include "common.h"

extern void iosMallocCheckLeak2(void *a0);

int ios_init_plus(char *a0) {
    char *p = a0;
    if (p != 0) {
        p -= 8;
        for (;;) {
            char *node = p;
            p = *(char **)(p + 4);
            iosMallocCheckLeak2(node);
            if (p == 0) {
                break;
            }
            p -= 8;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/ios", iosInitialize);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/ios", iosSifAllocIopHeapDebug);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_10;  /* 0x10 */
} S_006A0438;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_10;  /* 0x10 */
} S_006A0450;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_10;  /* 0x10 */
} S_006A0468;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_10;  /* 0x10 */
} S_006A0480;

/* end struct shapes */
