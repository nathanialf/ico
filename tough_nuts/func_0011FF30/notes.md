# func_0011FF30 (cod/01FF30)

Simple 3-call wrapper that's instruction-shape-correct but schedule
differs: original puts addiu a0=2 in jal delay slot; gcc 2.9 picks
addiu a1=lo for delay. Tried -fno-schedule-insns and -fno-schedule-insns2;
neither produces matching schedule.
