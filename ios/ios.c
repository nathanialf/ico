#include "common.h"

extern char D_00551058[];
extern int D_0063A3E0;
extern int sceSifAllocIopHeap(int size);
extern void debug_StdPrintfDummy(char *fmt, ...);
/* prototypes: their order is the inline tail's emission order */
int iosSifAllocIopHeapDebug(int size, char *file, int line);
inline int iosSifAllocIopHeapDebug(int size, char *file, int line)
{
    int p = sceSifAllocIopHeap(size);

    if (p == 0) {
        debug_StdPrintfDummy(D_00551058, file, line);
        if (D_0063A3E0 != 0) {
            while (sceSifAllocIopHeap(size - D_0063A3E0) == 0) {
                D_0063A3E0++;
            }
        } else {
            D_0063A3E0 = size;
        }
    }
    return p;
}
INCLUDE_ASM("asm/nonmatchings/ios/ios", ios_init_plus);
INCLUDE_ASM("asm/nonmatchings/ios/ios", iosInitialize);
