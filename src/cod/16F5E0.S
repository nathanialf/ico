; -----------------------------------------------------------------------
; VU0 microcode — first 8 bundles of ICO's .vutext blob (0x0026F5E0+0x00).
;
; This is the FIRST hand-written chunk of `.vutext` — a clean-room
; re-derivation from understanding the instruction shape (entry stub
; with three INTERRUPT-like wait-loops branching to a dispatcher at
; section offset 0x1A00-0x1A20).
;
; Each bundle is a 64-bit upper/lower pair. Upper-half opcodes whose
; encoding is not yet symbolic in `tools/assemble_vu0.py` are written
; as `.word 0x<hex>` (the same form `tools/disasm_vu0.py` emits in its
; reference listing — those encodings will become symbolic as the
; FMAC / LSU / control encoder tables grow).
;
; Build pipeline:
;   src/cod/16F5E0.S
;     → tools/assemble_vu0.py    (this file → src/cod/16F5E0.s)
;     → mips-linux-gnu-as        (existing as_hasm ninja rule)
;     → .vutext section of build/ico.elf
;
; Cross-check (no build needed):
;   tools/assemble_vu0.py src/cod/16F5E0.S --check \
;     assets/cod/16F5E0.textbin.bin
; -----------------------------------------------------------------------
.vu0
.org 0x0000

; --- entry stub (first bundle is true zero upper, never `pad`)
nop              ; .word 0x600000DA
.word 0x4A000000 ; nop

; --- four wait-then-dispatch slots that branch to a far-away
;     dispatcher table (offsets 0x1A00 / 0x1A10 / 0x1A18 / 0x1A20).
;     L_<addr> in branch targets resolves to the absolute section
;     offset in `tools/assemble_vu0.py` — labels in this file are
;     only required for in-file branches.
pad ; .word 0x4000001F
pad ; b L_1A00
pad ; .word 0x4000002E
pad ; b L_1A10
pad ; b L_1A18
pad ; b L_1A20
