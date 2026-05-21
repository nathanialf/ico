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

; =======================================================================
; SUBROUTINE BODIES.  These are the targets of the entry-stub branches
; above.  Each routine is callable independently (via VCALLMS with a
; matching VU0_TPC) and terminates via an E-bit upper-half pad followed
; by its implicit one-bundle delay slot.
;
; The E-bit pad (upper=`0x400002FF`, lower=anything) is encoded via
; `.word` until assemble_vu0.py learns it as a symbolic mnemonic; the
; lower halves of those bundles continue to use symbolic `nop_swap`.
; =======================================================================

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

; -----------------------------------------------------------------------
; sub_0180 — finalize GIF kick and end the VU0 program.
;
; xgkick at vi07 triggers the GS write of the GIF packet that previous
; routines built up at the mem[vi07] region.  The E-bit upper on the
; next bundle halts the VU0 after one more bundle (the E-bit's implicit
; delay slot).
; -----------------------------------------------------------------------
sub_0180:
pad ; xgkick vi07                      ; kick GIF packet at mem[vi07]
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot — VU0 halts after

; -----------------------------------------------------------------------
; sub_0198 — patch the .xy lanes of VU mem[2] from a VIF input quad.
;
; Reads the persistent constant at mem[2] (likely a view-translate
; quad), copies the .xy lanes from the next VIF input over it, and
; writes the result back.  The .zw lanes of mem[2] are preserved.
; -----------------------------------------------------------------------
sub_0198:
pad ; xtop vi01                        ; vi01 = VIF top
pad ; lq.xyzw vf30, 2(vi00)            ; vf30 = mem[2]
pad ; lqi.xyzw vf31, vi01              ; vf31 = *vi01++
pad ; move.xy vf30, vf31               ; vf30.xy = vf31.xy
pad ; sq.xyzw vf30, 2(vi00)            ; mem[2] = vf30
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_01D0 — bulk 4-quad upload to mem[256..259].
;
; Loads four quads from VIF unpack into vf18, vf19, vf16, vf17 (note
; non-sequential destination order) and writes them out to mem[256+]
; in the same order.  Looks like a 4-row matrix upload into the
; persistent matrix slot at mem[256].
; -----------------------------------------------------------------------
sub_01D0:
pad ; xtop vi12                        ; vi12 = VIF top
pad ; iaddiu vi13, vi00, 256           ; vi13 = mem[256] base
pad ; lqi.xyzw vf18, vi12              ; vf18 = *vi12++   (row 0)
pad ; lqi.xyzw vf19, vi12              ; vf19 = *vi12++   (row 1)
pad ; lqi.xyzw vf16, vi12              ; vf16 = *vi12++   (row 2)
pad ; lqi.xyzw vf17, vi12              ; vf17 = *vi12++   (row 3)
pad ; sqi.xyzw vf18, vi13              ; mem[256] = vf18
pad ; sqi.xyzw vf19, vi13              ; mem[257] = vf19
pad ; sqi.xyzw vf16, vi13              ; mem[258] = vf16
pad ; sqi.xyzw vf17, vi13              ; mem[259] = vf17
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

; -----------------------------------------------------------------------
; exit_0230 — shared "end immediately" stub.
;
; Branched-to by routines (e.g. sub_0318) that need to bail out without
; doing further work.  The E-bit halts the VU0 program after the
; implicit delay slot.
; -----------------------------------------------------------------------
exit_0230:
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0240 — palette-indexed vertex transform with GS kick.
;
; Reads a 16-bit count from *(int*)vi12, then iterates `count` times:
;   - load vertex quad from the vi11 stream (vi11 = vi12 + 1)
;   - extract the .w lane as an int, mask bit 0 → palette index 0/1
;   - load the chosen palette entry from mem[256 + idx]
;   - add palette to vf09.xy, zero vf09.w
;   - ftoi4 convert and store via sqi to the output cursor (vi09)
; After the loop, `xgkick` triggers GS output.  The routine then
; falls through into sub_0318's final-add tail, which branches to
; exit_0230 to terminate.
; -----------------------------------------------------------------------
sub_0240:
pad ; xtop vi12                        ; vi12 = VIF top
pad ; iaddiu vi11, vi12, 1             ; vi11 = vi12 + 1     (vertex stream)
pad ; ilwr.x vi10, vi12                ; vi10 = *(int*)vi12  (count)
pad ; lq.xyzw vf29, 0(vi12)            ; vf29 = *vi12        (header quad)
pad ; iaddiu vi13, vi00, 32767         ; vi13 = 0x7FFF
pad ; iaddiu vi07, vi12, 191           ; vi07 = vi12 + 191   (output base)
pad ; iaddiu vi09, vi07, 0             ; vi09 = vi07
pad ; sqi.xyzw vf29, vi09              ; *vi09++ = vf29      (store header)
pad ; iand vi10, vi13, vi10            ; vi10 &= 0x7FFF
pad ; iaddiu vi13, vi00, 1             ; vi13 = 1            (palette bit mask)
pad ; lq.xyzw vf09, 0(vi11)            ; vf09 = *vi11        (first vertex)
pad ; ilwr.w vi14, vi11                ; vi14 = (int)vi11.w
pad ; nop_swap
pad ; iand vi15, vi13, vi14            ; vi15 = vi14 & 1

sub_0240_loop:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)    ; vf09.xy += palette; load palette[idx]
pad ; move.w vf09, vf00                ; vf09.w = 0
pad ; iaddiu vi11, vi11, 1             ; vi11++
pad ; ilwr.w vi14, vi11                ; vi14 = (int)vi11.w
pad ; iaddi vi10, vi10, -1             ; --count
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09          ; ftoi4 vf09→vf10; *vi09++ = palette
pad ; lq.xyzw vf09, 0(vi11)            ; vf09 = next vertex
pad ; iand vi15, vi13, vi14            ; vi15 = vi14 & 1
pad ; ibne vi10, vi00, sub_0240_loop   ; loop while count != 0
pad ; sqi.xyzw vf10, vi09              ; *vi09++ = vf10      (delay slot)

pad ; nop_swap                         ; (0x300) post-loop pad
pad ; xgkick vi07                      ; (0x308) kick GIF packet
pad ; nop_swap                         ; (0x310) — falls through into sub_0318

; -----------------------------------------------------------------------
; sub_0318 — final palette-step + exit.  Reachable as its own entry
; (TPC=0x70 → b L_0318) OR by fall-through from sub_0240.  The single
; FMAC bumps vf16.xy by vf17.xy (i.e. advances the palette base by
; one palette stride), then branches to exit_0230 to end the program.
; -----------------------------------------------------------------------
sub_0318:
add.xy vf16, vf16, vf17 ; nop_swap     ; vf16.xy += vf17.xy
pad ; b exit_0230                      ; → exit_0230 (END)
pad ; nop_swap                         ; branch delay slot

; -----------------------------------------------------------------------
; sub_0330 — VIF-driven .w-lane patch of mem[2] + bulk copy + load
;   four working-constants from low mem.
;
; Like sub_0198 but patches the .w lane instead of .xy, then runs a
; `count`-iteration quad-copy from VIF into mem[16+], and finally
; loads four scratch quads (vf09..vf12) from the fixed slots mem[4..7]
; that are presumably needed by the next VU0 program.
; -----------------------------------------------------------------------
sub_0330:
pad ; xtop vi12                        ; vi12 = VIF top
pad ; ilwr.x vi06, vi12                ; vi06 = *(int*)vi12  (count)
pad ; lq.xyzw vf30, 2(vi00)            ; vf30 = mem[2]
pad ; lqi.xyzw vf31, vi12              ; vf31 = *vi12++
pad ; move.w vf30, vf31                ; vf30.w = vf31.w
pad ; sq.xyzw vf30, 2(vi00)            ; mem[2] = vf30
pad ; iaddiu vi13, vi00, 16            ; vi13 = mem[16] base

sub_0330_loop:
pad ; iaddi vi06, vi06, -1             ; --count
pad ; lqi.xyzw vf28, vi12              ; vf28 = *vi12++
pad ; ibne vi06, vi00, sub_0330_loop   ; loop
pad ; sqi.xyzw vf28, vi13              ; *vi13++ = vf28       (delay slot)

pad ; lq.xyzw vf09, 4(vi00)            ; vf09 = mem[4]
pad ; lq.xyzw vf10, 5(vi00)            ; vf10 = mem[5]
pad ; lq.xyzw vf11, 6(vi00)            ; vf11 = mem[6]
pad ; lq.xyzw vf12, 7(vi00)            ; vf12 = mem[7]
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_03B8 — bulk 8-quad load from VIF into vf13..vf20.
;
; Loads eight contiguous quads (a 2x4-matrix block, or two 4x1 vectors,
; or a small bone palette) into a contiguous register block.  No
; stores — the loaded data remains live for the next VU0 program.
; -----------------------------------------------------------------------
sub_03B8:
pad ; xtop vi12                        ; vi12 = VIF top
pad ; lqi.xyzw vf13, vi12              ; vf13 = *vi12++
pad ; lqi.xyzw vf14, vi12              ; vf14 = *vi12++
pad ; lqi.xyzw vf15, vi12              ; vf15 = *vi12++
pad ; lqi.xyzw vf16, vi12              ; vf16 = *vi12++
pad ; lqi.xyzw vf17, vi12              ; vf17 = *vi12++
pad ; lqi.xyzw vf18, vi12              ; vf18 = *vi12++
pad ; lqi.xyzw vf19, vi12              ; vf19 = *vi12++
pad ; lqi.xyzw vf20, vi12              ; vf20 = *vi12++
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0410 — trivial no-op entry (callable empty routine).
; -----------------------------------------------------------------------
sub_0410:
pad ; nop_swap                         ; do nothing
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

.assert_pc 0x428
