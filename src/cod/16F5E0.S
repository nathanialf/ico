; -----------------------------------------------------------------------
; VU0 microcode — first 8 bundles of ICO's .vutext blob (0x0026F5E0+0x00).
;
; Re-derived after cross-referencing PCSX2 microVU (GPL-3.0) opcode
; dispatch: lower opcode is bits 25-31 (7-bit), not 26-31.  The
; previous version of this file mislabelled four bundles as `b L_1A00`
; etc. — those bytes are actually the BIOS-bug NOP pattern
; (0x8000033C), written here as `nop_swap`.  Three of the bundles
; that were `.word 0x4000XXXX` are real `b` branches; they're now
; symbolic.
;
; Build pipeline:
;   src/cod/16F5E0.S
;     → tools/assemble_vu0.py    (this file → src/cod/16F5E0.s)
;     → mips-linux-gnu-as        (existing as_hasm ninja rule)
;     → .vutext section of build/ico.elf
; -----------------------------------------------------------------------
.vu0
.org 0x0000

; Bundle 0x0000 — true-zero upper (the only zero-upper in this chunk;
; every subsequent upper is the canonical `pad` = 0x000002FF NOP).
nop              ; .word 0x600000DA   ; lower op7=0x30 — FCSET (status-flag clear)

; Bundle 0x0008 — upper carries an unknown FMAC-family encoding;
; lower is true zero.  Both will become symbolic when the encoder
; learns the FMAC and lower-special tables.
.word 0x4A000000 ; nop                ; upper op6=0x00 sub-field 0x12 (cross-ref VU0 ref)

; The bundles below are alternating "real branch" and "BIOS-NOP
; padding".  The branch targets land inside .vutext just past this
; entry stub (L_0110, L_0198, L_01D0 etc.) — they'll be named
; properly once we promote those regions to hand-typed source.
pad ; b L_0110                        ; was '.word 0x4000001F'
pad ; nop_swap                        ; was 'b L_1A00' (wrong — bytes are 0x8000033C)
pad ; b L_0198                        ; was '.word 0x4000002E'
pad ; nop_swap                        ; was 'b L_1A10'
pad ; nop_swap                        ; was 'b L_1A18'
pad ; nop_swap                        ; was 'b L_1A20'

.assert_pc 0x40
