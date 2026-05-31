/* func_001F42E8 - parked seed: single function extracted from its coalesced
 * TU snapshot (the full-TU seed exceeded the check_no_rom 256KiB cap).
 * Externs/typedefs for permuter context live in the TU itself. */

float func_001F42E8(char *a0)
{
    Sub15C *p = *(char **)((char *)((GObj *)(a0))->p_15C + 0x800);
    int idx = *(int *)p;
    register float v;
    v = (float)D_006124F8[idx].field;
    __asm__ __volatile__("" : "+f"(v));
    NOP();
    return v;
}
