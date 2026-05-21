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

; -----------------------------------------------------------------------
; Entry-stub dispatch table (continued).  Each `pad ; b L_XXXX` bundle
; is a callable VU0 entry point at its 8-byte slot — the EE selects
; one by setting VU0_TPC to that offset before VCALLMS.  The bundle
; that immediately follows a branch is its delay slot (always
; `pad ; nop_swap`); intervening `pad ; nop_swap` bundles are reserved
; / unused dispatch slots and alignment padding.
; -----------------------------------------------------------------------
pad ; nop_swap                        ; 0x40 — reserved slot
pad ; nop_swap                        ; 0x48 — reserved slot
pad ; b L_01D0                        ; 0x50 — entry → sub_01D0
pad ; nop_swap                        ;        delay slot
pad ; b L_0240                        ; 0x60 — entry → sub_0240
pad ; nop_swap                        ;        delay slot
pad ; b L_0318                        ; 0x70 — entry → sub_0318
pad ; nop_swap                        ;        delay slot

pad ; nop_swap                        ; 0x80 — reserved slot
pad ; nop_swap                        ; 0x88 — reserved slot
pad ; b L_0330                        ; 0x90 — entry → sub_0330
pad ; nop_swap                        ;        delay slot
pad ; b L_03B8                        ; 0xA0 — entry → sub_03B8
pad ; nop_swap                        ;        delay slot
pad ; b L_0410                        ; 0xB0 — entry → sub_0410
pad ; nop_swap                        ;        delay slot

pad ; b L_0700                        ; 0xC0 — entry → sub_0700
pad ; nop_swap                        ;        delay slot
pad ; b L_0A30                        ; 0xD0 — entry → sub_0A30
pad ; nop_swap                        ;        delay slot
pad ; nop_swap                        ; 0xE0 — reserved slot
pad ; nop_swap                        ; 0xE8 — reserved slot
pad ; nop_swap                        ; 0xF0 — reserved slot
pad ; nop_swap                        ; 0xF8 — reserved slot

pad ; nop_swap                        ; 0x100 — reserved slot
pad ; nop_swap                        ; 0x108 — reserved slot

; -----------------------------------------------------------------------
; sub_0110 — quad-copy loop with embedded count header.
;
; Reads a 16-bit count from the first int of the VIF unpack buffer
; (`ilwr.x` loads the .x lane of *vi12 into vi10), masks it to 15
; bits, then copies `count` quadwords from input cursor vi12 to output
; cursor vi09 (= vi12 + 191).  Both cursors auto-increment via the
; `lqi`/`sqi` post-increment forms.
;
; Pre-loop unrolls the first iteration so the loop tests after one
; iteration has already completed; the body therefore runs count
; times total (decrement-then-`ibne`-against-zero).
; -----------------------------------------------------------------------
sub_0110:
pad ; xtop vi12                        ; vi12 = VIF unpack top (input ptr)
pad ; ilwr.x vi10, vi12                ; vi10 = *(int*)vi12  (count word)
pad ; iaddiu vi07, vi12, 191           ; vi07 = vi12 + 191   (output base)
pad ; iaddiu vi09, vi07, 0             ; vi09 = vi07         (output cursor)
pad ; lqi.xyzw vf29, vi12              ; vf29 = *vi12++      (first quad)
pad ; iaddiu vi13, vi00, 32767         ; vi13 = 0x7FFF       (count mask)
pad ; iand vi10, vi13, vi10            ; vi10 &= 0x7FFF
pad ; sqi.xyzw vf29, vi09              ; *vi09++ = vf29      (store first)

sub_0110_loop:
pad ; lqi.xyzw vf28, vi12              ; vf28 = *vi12++
pad ; iaddi vi10, vi10, -1             ; --count
pad ; nop_swap
pad ; ibne vi10, vi00, sub_0110_loop   ; loop while count != 0
pad ; sqi.xyzw vf28, vi09              ; *vi09++ = vf28   (branch delay slot)
pad ; nop_swap

.assert_pc 0x180
