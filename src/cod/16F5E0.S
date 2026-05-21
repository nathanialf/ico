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
; sub_0410 — trivial no-op entry (callable empty routine).  Also the
; shared return target of sub_0428 (`b sub_0410` to terminate).
; -----------------------------------------------------------------------
sub_0410:
pad ; nop_swap                         ; do nothing
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0428 — skinned vertex transform with perspective divide,
;   color quantization, and front-face/back-face slot selection.
;
; Top-level shape:
;   Prologue (0x428..0x480):
;     - Read count and header quad from VIF input at vi13.
;     - Initialize input cursor vi02 = vi13+1 and output cursor
;       vi01 = vi02+192; mirror the post-header cursor in vi03.
;     - Seed vf26.w = 0, vf27.w = 0x8000 (sign-bit float — used as
;       the "back-face" position-slot marker).
;
;   Per-vertex loop body (sub_0428_loop):
;     1. Load two weight quads vf21,vf22 from the vi02 stream and
;        two matrix-index ints (vi10 from .x lane, vi11 from .z
;        lane) — these select two source matrices M, N from the
;        constant pool at low mem.
;     2. Compute M*vf21 → vf28, N*vf21 → vf29; M*vf22 → vf30,
;        N*vf22 → vf31 (standard mulax / madday / maddaz / maddw
;        accumulator chains, four times).
;     3. Blend the two pairs by the bone-weights in vf23.y/.w:
;          vf28 = M*vf21*vf23.y + N*vf21*vf23.w
;          vf22 = M*vf22*vf23.y + N*vf22*vf23.w
;     4. Transform skinned position by the model matrix
;        [vf09..vf12]: vf28 = [vf09..vf12] * vf28.
;     5. Transform skinned vector by [vf13..vf16]: vf30 = ... * vf22.
;        Concurrently fire `div Q, vf00.w, vf28.w` to start the
;        perspective-divide reciprocal.
;     6. Clamp negatives, waitq, then mulq.xyz vf28 *= Q (perspective
;        divide) and re-transform by [vf17..vf20]: vf30 = ... * vf30
;        (post-divide screen-space position).
;     7. Convert vf28 to fixed-point colors (ftoi4) into vf26, vf27;
;        load I-register with 255.0 (via I-bit on a mul.xyz bundle)
;        and use minii to saturate the post-mul color vf25 to 255.
;        ftoi0 truncates to int.
;     8. Use fmand to derive clip-flags into vi14; compare against
;        a clip-mask in vi09 to select front-face vs back-face
;        position slot (vf26 vs vf27).  vi07 is a 3-slot rotating
;        decimator (skip 2 out of 3 back-face writes?).
;     9. Store one output triplet (color, normal, position) at
;        mem[vi03..vi03+2]; advance vi03 by 3.
;
;   Loop tail (0x6D0..0x6F8):
;     - `ibne vi06, ..., sub_0428_loop` continues while count != 0.
;     - After the loop: `xgkick vi01` kicks the GIF packet, then
;       `b sub_0410` branches to the shared no-op terminator.
;
; The bundle at 0x0618 has the upper-half I-bit set (bit 31):
;   upper = 0x81DECE6A  (mul.xyz vf25, vf25, vf30 with I-bit)
;   lower = 0x437F0000  (= IEEE-754 255.0f, the I-register immediate)
; assemble_vu0.py has no I-bit suffix yet, so the bundle is emitted
; as two raw `.word`s with the byte sequence above.  The disassembler
; mis-decodes the immediate as `bal vi31, L_0620` because it doesn't
; track the I-bit — the iaddiu at 0x0620 is NOT a branch target.
; -----------------------------------------------------------------------
sub_0428:
pad ; xtop vi13                        ; vi13 = VIF top
pad ; iaddiu vi14, vi00, 32767         ; vi14 = 0x7FFF
pad ; iaddiu vi02, vi13, 1             ; vi02 = vi13 + 1     (vertex-stream ptr)
pad ; ilwr.x vi06, vi13                ; vi06 = *(int*)vi13  (count)
pad ; lq.xyzw vf28, 0(vi13)            ; vf28 = mem[vi13]    (header quad)
pad ; iand vi06, vi14, vi06            ; vi06 &= 0x7FFF
pad ; iaddiu vi01, vi02, 192           ; vi01 = vi02 + 192   (output base)
pad ; sq.xyzw vf28, 0(vi01)            ; mem[vi01] = vf28    (store header)
pad ; iaddi vi14, vi14, 1              ; vi14 = 0x8000       (sign-bit pattern)
pad ; iaddiu vi03, vi01, 1             ; vi03 = vi01 + 1     (output cursor)
pad ; mfir.w vf26, vi00                ; vf26.w = 0          (front-face marker)
pad ; mfir.w vf27, vi14                ; vf27.w = 0x8000     (back-face marker)

sub_0428_loop:
pad ; lqi.xyzw vf21, vi02              ; vf21 = *vi02++       (weight quad 0)
pad ; lqi.xyzw vf22, vi02              ; vf22 = *vi02++       (weight quad 1)
pad ; ilwr.x vi10, vi02                ; vi10 = (int)mem[vi02].x  (matrix M base)
pad ; ilwr.z vi11, vi02                ; vi11 = (int)mem[vi02].z  (matrix N base)
pad ; lq.xyzw vf01, 0(vi10)            ; vf01..vf04 = M
pad ; lq.xyzw vf02, 1(vi10)
pad ; lq.xyzw vf03, 2(vi10)
pad ; lq.xyzw vf04, 3(vi10)

; ACC = M * vf21 → vf28
mulax.xyzw  vf01, vf21 ; lq.xyzw vf05, 0(vi11)    ; ACC.xyzw = vf01 * vf21.x; load N[0]
madday.xyzw vf02, vf21 ; lq.xyzw vf06, 1(vi11)    ; ACC += vf02 * vf21.y;   load N[1]
maddaz.xyzw vf03, vf21 ; lq.xyzw vf07, 2(vi11)    ; ACC += vf03 * vf21.z;   load N[2]
maddw.xyzw  vf28, vf04, vf00 ; lq.xyzw vf08, 3(vi11) ; vf28 = ACC + vf04 * vf00.w; load N[3]

; ACC = N * vf21 → vf29
mulax.xyzw  vf05, vf21 ; iaddi vi06, vi06, -1     ; ACC.xyzw = vf05 * vf21.x; --count
madday.xyzw vf06, vf21 ; lqi.xyzw vf23, vi02      ; ACC += vf06 * vf21.y; vf23 = *vi02++ (bone weights)
maddaz.xyzw vf07, vf21 ; nop_swap                 ; ACC += vf07 * vf21.z
maddw.xyzw  vf29, vf08, vf00 ; move.xyzw vf04, vf00 ; vf29 = ACC + vf08*vf00.w; vf04 = (0,0,0,1)

; ACC = M * vf22 → vf30   (note: maddw uses vf22.w here, not vf00.w)
mulax.xyzw  vf01, vf22 ; nop_swap                 ; ACC = vf01 * vf22.x
madday.xyzw vf02, vf22 ; nop_swap                 ; ACC += vf02 * vf22.y
maddaz.xyzw vf03, vf22 ; nop_swap                 ; ACC += vf03 * vf22.z
maddw.xyzw  vf30, vf04, vf22 ; move.xyzw vf08, vf00 ; vf30 = ACC + (0,0,0,1)*vf22.w; vf08 = (0,0,0,1)

; ACC = N * vf22 → vf31
mulax.xyzw  vf05, vf22 ; move.w vf28, vf00        ; ACC = vf05 * vf22.x; vf28.w = 1
madday.xyzw vf06, vf22 ; nop_swap                 ; ACC += vf06 * vf22.y
maddaz.xyzw vf07, vf22 ; nop_swap                 ; ACC += vf07 * vf22.z
maddw.xyzw  vf31, vf08, vf22 ; nop_swap           ; vf31 = ACC + vf08*vf22.w

; Bone-weight blend by vf23.y / vf23.w → vf28 (from vf28, vf29) and vf22 (from vf30, vf31)
mulay.xyz   vf28, vf23 ; move.w vf22, vf00        ; ACC.xyz = vf28 * vf23.y;  vf22.w = 1
maddw.xyz   vf28, vf29, vf23 ; nop_swap           ; vf28.xyz = ACC + vf29*vf23.w
mulay.xyz   vf30, vf23 ; nop_swap                 ; ACC.xyz = vf30 * vf23.y
maddw.xyz   vf22, vf31, vf23 ; nop_swap           ; vf22.xyz = ACC + vf31*vf23.w

; Apply per-model matrix [vf09..vf12] to vf28 (skinned color/light vector)
mulax.xyzw  vf09, vf28 ; nop_swap                 ; ACC = vf09 * vf28.x
madday.xyzw vf10, vf28 ; nop_swap                 ; ACC += vf10 * vf28.y
maddaz.xyzw vf11, vf28 ; nop_swap                 ; ACC += vf11 * vf28.z
maddw.xyzw  vf28, vf12, vf28 ; nop_swap           ; vf28 = ACC + vf12 * vf28.w

; Apply [vf13..vf16] to vf22 (skinned position pre-divide) + start perspective divide
mulax.xyzw  vf13, vf22 ; lqi.xyzw vf24, vi02      ; ACC = vf13*vf22.x; vf24 = *vi02++ (alt-color quad)
madday.xyzw vf14, vf22 ; nop_swap                 ; ACC += vf14*vf22.y
maddaz.xyzw vf15, vf22 ; nop_swap                 ; ACC += vf15*vf22.z
maddw.xyzw  vf30, vf16, vf22 ; div Q, vf00.w, vf28.w ; vf30 = ACC + vf16*vf22.w; Q = 1.0/vf28.w

; Cycle-pad while Q divides; meanwhile set up clip-flag accumulator
sub.w       vf00, vf24, vf00 ; nop_swap          ; flag-set: vf24.w - 0
pad ; nop_swap
pad ; nop_swap
maxx.xyzw   vf30, vf30, vf00 ; nop_swap          ; vf30 = max(vf30, vf00.x=0)  (clamp negatives)
sub.w       vf24, vf24, vf24 ; fsand vi15, 0x2   ; vf24.w = 0; vi15 = MAC.flags & 0x02
mulq.xyz    vf28, vf28 ; waitq                   ; vf28.xyz *= Q (perspective divide)

; Apply [vf17..vf20] to vf30 (post-divide screen-space transform)
mulax.xyzw  vf17, vf30 ; nop_swap                 ; ACC = vf17 * vf30.x
madday.xyzw vf18, vf30 ; nop_swap                 ; ACC += vf18 * vf30.y
maddaz.xyzw vf19, vf30 ; iaddiu vi13, vi00, 0     ; ACC += vf19*vf30.z; vi13 = 0 (clip slot)
maddw.xyzw  vf30, vf20, vf30 ; lqi.xyzw vf25, vi02 ; vf30 = ACC + vf20*vf30.w; vf25 = *vi02++ (color)
maxx.xyzw   vf30, vf30, vf00 ; nop_swap          ; clamp vf30 to ≥ 0

; Quantize colors / set up clip-flag bits
ftoi4.xyz   vf26, vf28 ; lq.xyzw vf29, 0(vi13)   ; vf26.xyz = float→fix4(vf28); vf29 = mem[0] (clip-x bounds)
ftoi4.xyz   vf27, vf28 ; lq.xyzw vf31, 1(vi13)   ; vf27.xyz = float→fix4(vf28); vf31 = mem[1] (clip-y bounds)
mulq.xyz    vf24, vf24 ; nop_swap                ; vf24.xyz *= Q (perspective on alt-color)
; I-bit bundle: upper = mul.xyz vf25,vf25,vf30 with I-bit set; lower = 255.0f → I reg.
; (disasm shows lower as `bal vi31, L_0620` — a misread.  The iaddiu at 0x0620 is
;  the next sequential bundle, NOT a branch target.)
.word 0x81DECE6A ; .word 0x437F0000   ; mul.xyz[I] vf25,vf25,vf30 + I = 255.0f

pad ; iaddiu vi09, vi00, 208           ; vi09 = 0xD0  (clip-mask: bits .y/.z/.w?)
sub.xyw     vf00, vf29, vf28 ; nop_swap          ; flag-set: clip(vf29 - vf28) on xyw
sub.xyw     vf00, vf28, vf31 ; nop_swap          ; flag-set: clip(vf28 - vf31) on xyw
minii.xyzw  vf25, vf25 ; sq.xyzw vf24, 0(vi03)   ; saturate vf25 ≤ I(=255); store alt-color
pad ; nop_swap
pad ; fmand vi14, vi09                 ; vi14 = MAC.flags & vi09 (clip bits)
pad ; fmand vi14, vi14                 ; vi14 = MAC.flags & vi14 (combine)
ftoi0.xyzw  vf25, vf25 ; ibeq vi15, vi00, L_0670 ; ftoi0 (round-to-int); if vi15==0 skip-reset
pad ; nop_swap                         ;       (branch delay slot)
pad ; iaddiu vi07, vi00, 3             ; vi07 = 3 (back-face slot counter)

L_0670:
pad ; iaddi vi07, vi07, -1             ; --vi07
pad ; sq.xyzw vf25, 1(vi03)            ; mem[vi03+1] = vf25 (quantized color)
pad ; ibne vi14, vi09, L_06B0          ; if clip-flags don't match, use back-face slot
pad ; nop_swap                         ;       (branch delay slot)
pad ; ibgtz vi07, L_06B8               ; if vi07 > 0, also use back-face slot
pad ; sq.xyzw vf26, 2(vi03)            ; mem[vi03+2] = vf26 (front-face position)  (delay slot)
pad ; b L_06C0                         ; skip back-face write
pad ; nop_swap                         ;       (branch delay slot)
L_06B0:
pad ; iaddiu vi07, vi00, 3             ; reset vi07 = 3 (back-face slot triggered)
L_06B8:
pad ; sq.xyzw vf27, 2(vi03)            ; mem[vi03+2] = vf27 (back-face position)
L_06C0:
pad ; iaddiu vi03, vi03, 3             ; vi03 += 3 (advance output by 3 quads)
pad ; nop_swap
pad ; ibne vi06, vi00, sub_0428_loop   ; loop while count != 0
pad ; nop_swap                         ;       (branch delay slot)
pad ; xgkick vi01                      ; kick GIF packet at vi01
pad ; nop_swap
pad ; b sub_0410                       ; → sub_0410 (shared END stub)
pad ; nop_swap                         ;       (branch delay slot)

.assert_pc 0x700
