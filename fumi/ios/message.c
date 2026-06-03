#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", deq_mes_th);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgQueueCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgQueueDestroy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", send_signal_message);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgSetEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", func_00139F80);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgSend);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgRecv);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgQueueDestroyAll);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A0510;  /* stride 0x4 */

/* end struct shapes */
