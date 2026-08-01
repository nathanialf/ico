/* delayslot_queue: pac_makeMaterialTableLine
 * TU: src/Packet.c   ROM addr: 0x0011A2F0
 * Reverted 2026-08-01: matched only under MODERN gas. gcc leaves the
 * `j debug_assertMessage` tail call with an UNFILLED delay slot; ROM has
 * `sw a1,44(v1)` in the slot. Period ee-as 2.9-991111 leaves nop.
 */
void pac_makeMaterialTableLine(void)
{
    register char *base = D_00672FD0;
    volatile int * volatile *curp = (volatile int * volatile *)(base + 0x2C);
    volatile int *p = *curp;
    *p++ = 0x17000000;
    *curp = p;
    p[0] = 0;
    *curp = p + 1;
    p[1] = 0;
    *curp = p + 2;
    p[2] = 0;
    *curp = p + 3;
    debug_assertMessage((const char *)(p + 3));
}
