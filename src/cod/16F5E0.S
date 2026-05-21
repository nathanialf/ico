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

; -----------------------------------------------------------------------
; sub_0700 — second shared no-op terminator (TPC=0xC0 dispatch target).
; Identical 3-bundle layout to sub_0410 at a different VRAM slot; the
; sub_0718 routine `b sub_0708` returns to L_0708 here for END.
; -----------------------------------------------------------------------
sub_0700:
pad ; nop_swap                         ; do nothing (entry)
L_0708:
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0718 — second skinned vertex transform routine.
;
; Near-clone of sub_0428 (see that routine's docstring for the full
; algorithm).  Differences from sub_0428:
;   * Loop-relative: the first `lqi vf21, vi02` is unrolled above the
;     loop start label (sub_0718_loop = L_0780); subsequent iterations
;     only re-load vf22.  This means vf21 stays constant per call.
;   * Bundle at 0x0810 has flag bits set (E-bit / T-bit / bit 25);
;     the FMAC underneath is `add.yw vf04, vf00, vf19`.  Emitted via
;     `.word` because the assembler has no upper-flag suffix yet.
;   * Bundle at 0x0950 mirrors sub_0428's I-bit immediate trick:
;     upper 0x81DECE6A (mul.xyz vf25,vf25,vf30 with I-bit) + lower
;     0x437F0000 (= 255.0f → I-register).  disasm reads the lower as
;     `bal vi31, L_0958`; that is a misread.
;   * Two extra `mul.xyz vf30, vf30, vf30` bundles at 0x0910 / 0x0930
;     square vf30 twice (likely a specular-power approximation).
;   * The `maddw vf30, vf00, vf30` at 0x08E8 uses vf00 (not vf20) as
;     the .w-broadcast source; combined with the squaring it implies
;     this routine doesn't apply the screen-space matrix in vf17..20.
;   * Loop tail branches to sub_0708 (L_0708) instead of sub_0410.
; -----------------------------------------------------------------------
sub_0718:
pad ; xtop vi13                        ; vi13 = VIF top
pad ; iaddiu vi14, vi00, 32767         ; vi14 = 0x7FFF
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi06, vi13                ; vi06 = count
pad ; lq.xyzw vf28, 0(vi13)
pad ; iand vi06, vi14, vi06
pad ; iaddiu vi01, vi02, 192           ; output base = vi02 + 192
pad ; sq.xyzw vf28, 0(vi01)
pad ; iaddi vi14, vi14, 1              ; vi14 = 0x8000
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf26, vi00                ; vf26.w = 0
pad ; mfir.w vf27, vi14                ; vf27.w = 0x8000
pad ; lqi.xyzw vf21, vi02              ; vf21 = *vi02++ (loaded ONCE — not in loop)

sub_0718_loop:
pad ; lqi.xyzw vf22, vi02              ; vf22 = *vi02++
pad ; ilwr.x vi10, vi02
pad ; ilwr.z vi11, vi02
pad ; lq.xyzw vf01, 0(vi10)
pad ; lq.xyzw vf02, 1(vi10)
pad ; lq.xyzw vf03, 2(vi10)
pad ; lq.xyzw vf04, 3(vi10)

mulax.xyzw  vf01, vf21 ; lq.xyzw vf05, 0(vi11)
madday.xyzw vf02, vf21 ; lq.xyzw vf06, 1(vi11)
maddaz.xyzw vf03, vf21 ; lq.xyzw vf07, 2(vi11)
maddw.xyzw  vf28, vf04, vf00 ; lq.xyzw vf08, 3(vi11)

mulax.xyzw  vf05, vf21 ; iaddi vi06, vi06, -1
madday.xyzw vf06, vf21 ; lqi.xyzw vf23, vi02
maddaz.xyzw vf07, vf21 ; nop_swap
maddw.xyzw  vf29, vf08, vf00 ; move.xyzw vf04, vf00

mulax.xyzw  vf01, vf22 ; nop_swap
madday.xyzw vf02, vf22 ; nop_swap
maddaz.xyzw vf03, vf22 ; nop_swap
.word 0x4AB30100 ; nop                 ; upper: `add.yw vf04,vf00,vf19` + flag bits (E/T/25)
maddw.xyzw  vf30, vf04, vf22 ; move.xyzw vf08, vf00

mulax.xyzw  vf05, vf22 ; move.w vf28, vf00
madday.xyzw vf06, vf22 ; nop_swap
maddaz.xyzw vf07, vf22 ; nop_swap
maddw.xyzw  vf31, vf08, vf22 ; nop_swap

mulay.xyz   vf28, vf23 ; move.w vf22, vf00
maddw.xyz   vf28, vf29, vf23 ; nop_swap
mulay.xyz   vf30, vf23 ; nop_swap
maddw.xyz   vf22, vf31, vf23 ; nop_swap

mulax.xyzw  vf09, vf28 ; nop_swap
madday.xyzw vf10, vf28 ; nop_swap
maddaz.xyzw vf11, vf28 ; nop_swap
maddw.xyzw  vf28, vf12, vf28 ; nop_swap

mulax.xyzw  vf13, vf22 ; lqi.xyzw vf24, vi02
madday.xyzw vf14, vf22 ; nop_swap
maddaz.xyzw vf15, vf22 ; nop_swap
maddw.xyzw  vf30, vf16, vf22 ; div Q, vf00.w, vf28.w

sub.w       vf00, vf24, vf00 ; nop_swap
pad ; nop_swap
pad ; nop_swap
maxx.xyzw   vf30, vf30, vf00 ; nop_swap
sub.w       vf24, vf24, vf24 ; fsand vi15, 0x2
mulq.xyz    vf28, vf28 ; waitq

mulax.xyzw  vf17, vf30 ; nop_swap
madday.xyzw vf18, vf30 ; nop_swap
maddaz.xyzw vf19, vf30 ; iaddiu vi13, vi00, 0
maddw.xyzw  vf30, vf00, vf30 ; lqi.xyzw vf25, vi02   ; vf30.w-broadcast from vf30 itself
maxx.xyzw   vf30, vf30, vf00 ; nop_swap

pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
mul.xyz     vf30, vf30, vf30 ; nop_swap              ; vf30² (specular power step 1)
pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
mul.xyz     vf30, vf30, vf30 ; nop_swap              ; vf30⁴ (specular power step 2)

ftoi4.xyz   vf26, vf28 ; lq.xyzw vf29, 0(vi13)
ftoi4.xyz   vf27, vf28 ; lq.xyzw vf31, 1(vi13)
mulq.xyz    vf24, vf24 ; nop_swap
.word 0x81DECE6A ; .word 0x437F0000    ; mul.xyz[I] vf25,vf25,vf30 + I = 255.0f

pad ; iaddiu vi09, vi00, 208
sub.xyw     vf00, vf29, vf28 ; nop_swap
sub.xyw     vf00, vf28, vf31 ; nop_swap
minii.xyzw  vf25, vf25 ; sq.xyzw vf24, 0(vi03)
pad ; nop_swap
pad ; fmand vi14, vi09
pad ; fmand vi14, vi14
ftoi0.xyzw  vf25, vf25 ; ibeq vi15, vi00, L_09A8
pad ; nop_swap
pad ; iaddiu vi07, vi00, 3

L_09A8:
pad ; iaddi vi07, vi07, -1
pad ; sq.xyzw vf25, 1(vi03)
pad ; ibne vi14, vi09, L_09E8
pad ; nop_swap
pad ; ibgtz vi07, L_09F0
pad ; sq.xyzw vf26, 2(vi03)
pad ; b L_09F8
pad ; nop_swap
L_09E8:
pad ; iaddiu vi07, vi00, 3
L_09F0:
pad ; sq.xyzw vf27, 2(vi03)
L_09F8:
pad ; iaddiu vi03, vi03, 3
pad ; nop_swap
pad ; ibne vi06, vi00, sub_0718_loop
pad ; nop_swap
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_0708                         ; → sub_0700 / L_0708 (END)
; branch delay slot of `b L_0708` is the next bundle in source —
; which is sub_0A30's entry bundle at 0x0A30 (a `pad ; nop_swap`).

; -----------------------------------------------------------------------
; sub_0A30 — third shared no-op terminator (TPC=0xD0 dispatch target).
; Same 4-bundle shape as sub_0410 / sub_0700, with an extra `nop_swap`
; bundle (L_0A38) at +8 so sub_0A50's loop tail has a `b L_0A38`
; target with the E-bit one bundle later.
; -----------------------------------------------------------------------
sub_0A30:
pad ; nop_swap                         ; do nothing (entry / also sub_0718's branch delay slot)
L_0A38:
pad ; nop_swap                         ; sub_0A50's branch target
.word 0x400002FF ; nop_swap            ; upper: E-bit pad (END)
pad ; nop_swap                         ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0A50 — third skinned vertex transform routine.
;
; Near-clone of sub_0428 / sub_0718; same overall shape (per-vertex
; matrix×weight skinning with perspective divide, fmand-driven
; front/back face slot selection, and `xgkick`-then-`b L_0A38`
; termination).  Key differences from sub_0428:
;   * Setup phase additionally computes `vi12 = vi02 + 2` and loads
;     all four weight quads vf21/vf22/vf23/vf24 from low-mem-relative
;     `lq` (non-incrementing), with matrix indices read from vi12
;     instead of vi02.
;   * Setup also adds a one-shot `add.xy vf24, vf24, mem[2]` (FMAC
;     in upper of the lq vf03 bundle at 0x0B00).
;   * Loop body is restructured: the L_0B90 label is after a full
;     pre-loop matrix-mul prologue (M*vf22, N*vf22, M*vf21, N*vf21
;     all happen ONCE before the loop), and per-iteration only the
;     blends, divide, and per-vertex transforms re-execute.  Stream
;     advance is `iaddiu vi02, vi02, 5` (5 quads per vertex).
;   * Bundle 0x0C70 is the I-bit immediate trick (upper sub.xyw
;     vf00,vf29,vf28 with I-bit; lower 0x437F0000 = 255.0f → I).
;   * `mul.w vf25, vf25, vf23` at 0x0C68 — per-vertex alpha mod via
;     bone-weight .w.
;   * The clip-mismatch path at L_0D70/L_0D78 branches back to
;     L_0B90 (loop) WITHOUT going through the "common" tail —
;     there are TWO `xgkick` exits (post-front-face and post-back-
;     face), each followed by `b L_0A38`.
; -----------------------------------------------------------------------
sub_0A50:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi06, vi13
pad ; lq.xyzw vf28, 0(vi13)
pad ; iand vi06, vi14, vi06
pad ; iaddiu vi01, vi02, 192
pad ; sq.xyzw vf28, 0(vi01)
pad ; iaddi vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf26, vi00
pad ; mfir.w vf27, vi14
pad ; iaddiu vi12, vi02, 2            ; vi12 = vi02 + 2 (matrix-index ptr)
pad ; lq.xyzw vf21, 0(vi02)           ; vf21 = mem[vi02+0] (weight quad A)
pad ; lq.xyzw vf22, 1(vi02)           ; vf22 = mem[vi02+1] (weight quad B)
pad ; ilwr.x vi10, vi12               ; vi10 = (int)mem[vi12].x (matrix M idx)
pad ; ilwr.z vi11, vi12               ; vi11 = (int)mem[vi12].z (matrix N idx)
pad ; lq.xyzw vf23, 2(vi02)           ; vf23 = mem[vi02+2] (bone weights)
pad ; lq.xyzw vf24, 3(vi02)           ; vf24 = mem[vi02+3] (alt-color)
pad ; lq.xyzw vf28, 2(vi00)           ; vf28 = mem[2] (view-translate?)
pad ; lq.xyzw vf01, 0(vi10)           ; M[0]
pad ; lq.xyzw vf02, 1(vi10)           ; M[1]
add.xy      vf24, vf24, vf28 ; lq.xyzw vf03, 2(vi10) ; vf24.xy += mem[2].xy; M[2]
pad ; lq.xyzw vf04, 3(vi10)           ; M[3]

; M*vf22 → vf30 + load N
mulax.xyzw  vf01, vf22 ; lq.xyzw vf05, 0(vi11)
madday.xyzw vf02, vf22 ; lq.xyzw vf06, 1(vi11)
maddaz.xyzw vf03, vf22 ; lq.xyzw vf07, 2(vi11)
maddw.xyzw  vf30, vf00, vf22 ; lq.xyzw vf08, 3(vi11)

; N*vf22 → vf31  (with one iaddiu fold-in)
mulax.xyzw  vf05, vf22 ; nop_swap
madday.xyzw vf06, vf22 ; iaddiu vi09, vi00, 208     ; vi09 = 0xD0 clip-mask
maddaz.xyzw vf07, vf22 ; nop_swap
maddw.xyzw  vf31, vf00, vf22 ; nop_swap

; M*vf21 → vf28
mulax.xyzw  vf01, vf21 ; nop_swap
madday.xyzw vf02, vf21 ; nop_swap
maddaz.xyzw vf03, vf21 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap

; N*vf21 → vf29
mulax.xyzw  vf05, vf21 ; nop_swap
madday.xyzw vf06, vf21 ; nop_swap
maddaz.xyzw vf07, vf21 ; nop_swap
maddw.xyzw  vf29, vf08, vf00 ; nop_swap

sub_0A50_loop:
mulay.xyz   vf30, vf23 ; move.w vf22, vf00           ; ACC = vf30*vf23.y; vf22.w = 1
maddw.xyz   vf22, vf31, vf23 ; iaddiu vi02, vi02, 5  ; vf22 = ACC + vf31*vf23.w; vi02 += 5
mulay.xyz   vf28, vf23 ; move.w vf28, vf00           ; ACC = vf28*vf23.y; vf28.w = 1
maddw.xyz   vf28, vf29, vf23 ; iaddi vi06, vi06, -1  ; vf28 = ACC + vf29*vf23.w; --count
sub.w       vf00, vf24, vf00 ; iaddiu vi13, vi00, 0  ; flag-set; vi13 = 0 (clip-mem slot)
mulax.xyzw  vf13, vf22 ; iaddiu vi12, vi02, 2        ; ACC = vf13*vf22.x; vi12 = vi02+2 (next-iter matrix idx)
madday.xyzw vf14, vf22 ; lq.xyzw vf21, 0(vi02)       ; ACC += vf14*vf22.y; vf21 = next vf21
maddaz.xyzw vf15, vf22 ; ilwr.x vi10, vi12           ; ACC += vf15*vf22.z; vi10 = next M idx
maddw.xyzw  vf30, vf16, vf22 ; fsand vi15, 0x2       ; vf30 = ACC + vf16*vf22.w; vi15 = MAC.flag & 0x2

; Per-vertex matrix transform of vf28 (color/light) + prefetch next-iter matrix
mulax.xyzw  vf09, vf28 ; lq.xyzw vf29, 0(vi13)       ; ACC = vf09*vf28.x; vf29 = mem[0]
madday.xyzw vf10, vf28 ; lq.xyzw vf31, 1(vi13)       ; ACC += vf10*vf28.y; vf31 = mem[1]
maddaz.xyzw vf11, vf28 ; lq.xyzw vf22, 1(vi02)       ; ACC += vf11*vf28.z; vf22 = next vf22
maddw.xyzw  vf28, vf12, vf28 ; ilwr.z vi11, vi12     ; vf28 = ACC + vf12*vf28.w; vi11 = next N idx
maxx.xyzw   vf30, vf30, vf00 ; lq.xyzw vf01, 0(vi10) ; clamp vf30 ≥ 0; M[0] next-iter
sub.w       vf24, vf24, vf24 ; lq.xyzw vf02, 1(vi10) ; vf24.w = 0; M[1] next
pad ; lq.xyzw vf03, 2(vi10)                         ; M[2] next
pad ; div Q, vf00.w, vf28.w                          ; Q = 1/vf28.w
mulax.xyzw  vf17, vf30 ; lq.xyzw vf04, 3(vi10)       ; ACC = vf17*vf30.x; M[3] next
madday.xyzw vf18, vf30 ; lq.xyzw vf05, 0(vi11)       ; ACC += vf18*vf30.y; N[0] next
maddaz.xyzw vf19, vf30 ; lq.xyzw vf06, 1(vi11)       ; ACC += vf19*vf30.z; N[1] next
maddw.xyzw  vf30, vf20, vf30 ; lq.xyzw vf07, 2(vi11) ; vf30 = ACC + vf20*vf30.w; N[2] next
mulax.xyzw  vf01, vf22 ; lq.xyzw vf08, 3(vi11)       ; (next-iter M*vf22 start); N[3] next
madday.xyzw vf02, vf22 ; lq.xyzw vf23, 2(vi00)       ; ACC += vf02*vf22.y; vf23 = mem[2]
mulq.xyz    vf28, vf28 ; lq.xyzw vf25, -1(vi02)      ; vf28 *= Q; vf25 = mem[vi02-1] (color quad)
maxx.xyzw   vf30, vf30, vf00 ; nop_swap              ; clamp vf30 ≥ 0
mulq.xyz    vf24, vf24 ; nop_swap                    ; vf24 *= Q
maddaz.xyzw vf03, vf22 ; nop_swap                    ; ACC += vf03*vf22.z (next-iter M*vf22)
mul.w       vf25, vf25, vf23 ; nop_swap              ; vf25.w *= vf23.w (alpha by bone-weight-w)

; I-bit immediate bundle: upper = sub.xyw vf00,vf29,vf28 + I-bit; lower = 255.0f → I
; (disasm reads lower as `bal vi31, L_0C78` — misread; the next bundle at 0x0C78 is sequential.)
.word 0x81BCE82C ; .word 0x437F0000

mul.xyz     vf29, vf30, vf30 ; lq.xyzw vf23, 2(vi02) ; vf29 = vf30² (specular-pow); vf23 = next bone weights
sub.xyw     vf00, vf28, vf31 ; sq.xyzw vf24, 0(vi03) ; clip-flag; store alt-color
ftoi4.xyz   vf26, vf28 ; nop_swap                    ; vf26 = ftoi4(vf28)
ftoi4.xyz   vf27, vf28 ; fmand vi14, vi09            ; vf27 = ftoi4(vf28); vi14 = MAC & 0xD0
maddw.xyzw  vf30, vf00, vf22 ; nop_swap              ; vf30 += vf00*vf22.w (cont next-iter)
mul.xyz     vf25, vf25, vf29 ; fmand vi14, vi14      ; vf25 *= vf30²; combine MAC flags
mulax.xyzw  vf05, vf22 ; lq.xyzw vf24, 3(vi02)       ; (cont N*vf22 next-iter); vf24 = next alt-color
madday.xyzw vf06, vf22 ; nop_swap
maddaz.xyzw vf07, vf22 ; nop_swap
minii.xyzw  vf25, vf25 ; nop_swap                    ; saturate vf25 ≤ I(=255)
maddw.xyzw  vf31, vf00, vf22 ; iaddi vi07, vi07, -1  ; vf31 cont; --vi07
mulax.xyzw  vf01, vf21 ; nop_swap                    ; (cont M*vf21 next-iter)
madday.xyzw vf02, vf21 ; nop_swap
ftoi0.xyzw  vf25, vf25 ; nop_swap                    ; vf25 = ftoi0(vf25)
maddaz.xyzw vf03, vf21 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
mulax.xyzw  vf05, vf21 ; nop_swap                    ; (cont N*vf21 next-iter)
madday.xyzw vf06, vf21 ; sq.xyzw vf25, 1(vi03)       ; store vf25 color
maddaz.xyzw vf07, vf21 ; ibeq vi15, vi00, L_0D20     ; if vi15==0 skip-reset
maddw.xyzw  vf29, vf08, vf00 ; lq.xyzw vf25, 2(vi00) ; vf25 = mem[2] (alpha reset?)  (delay slot)
pad ; iaddiu vi07, vi00, 2                           ; vi07 = 2

L_0D20:
pad ; ibne vi14, vi09, L_0D70                       ; clip-mismatch → back-face path
pad ; nop_swap                                       ; (delay slot)
pad ; ibgtz vi07, L_0D78                            ; vi07 > 0 → back-face path
pad ; sq.xyzw vf26, 2(vi03)                          ; front-face position  (delay slot)
add.xy      vf24, vf24, vf25 ; ibne vi06, vi00, sub_0A50_loop ; vf24.xy += vf25.xy; loop
pad ; iaddiu vi03, vi03, 3                          ; vi03 += 3            (delay slot)
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_0A38                                       ; → END
pad ; nop_swap                                       ; (branch delay slot)
L_0D70:
pad ; iaddiu vi07, vi00, 3                          ; reset vi07 = 3
L_0D78:
pad ; sq.xyzw vf27, 2(vi03)                          ; back-face position
add.xy      vf24, vf24, vf25 ; ibne vi06, vi00, sub_0A50_loop ; vf24.xy += vf25.xy; loop
pad ; iaddiu vi03, vi03, 3                          ; vi03 += 3            (delay slot)
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_0A38                                       ; → END
pad ; nop_swap                                       ; (branch delay slot)

; =======================================================================
; SECOND VU0 PROGRAM begins here.  ICO's `.vutext` blob is a
; concatenation of multiple VU0 programs (each ≤ 4 KB of micro
; memory); the EE DMAs the appropriate slice into VU0 RAM before
; VCALLMS.  Bundle 0x0DB0 mirrors program 1's bundle 0x0000:
; nop-upper paired with a special-class lower (here a different op
; with op7=0x38), and bundle 0x0DC8 mirrors program 1's 0x0008
; FMAC-family `.word 0x4A000000` upper.
; =======================================================================

; Program-2 control-flag prologue (parallels 0x0000..0x0008 in program 1).
nop ; .word 0x70000000                  ; lower op7=0x38 (special class, not yet decoded)
nop ; nop                               ; literal-zero bundle (both halves true zero)
nop ; .word 0x6000009D                  ; lower op7=0x30 (FCSET imm24=0x9D)
.word 0x4A000000 ; nop                  ; upper op6=0x00 unknown-family + lower true-zero

; Program-2 entry-stub dispatch table (parallels 0x0010..0x00D8 in program 1).
pad ; b L_0EA0                          ; 0x0DD0 — entry → L_0EA0
pad ; nop_swap                          ;        delay slot
pad ; b L_0F28                          ; 0x0DE0 — entry → L_0F28
pad ; nop_swap                          ;        delay slot
pad ; nop_swap                          ; 0x0DF0 — reserved slot
pad ; nop_swap                          ; 0x0DF8 — reserved slot
pad ; nop_swap                          ; 0x0E00 — reserved slot
pad ; nop_swap                          ; 0x0E08 — reserved slot
pad ; b L_0F60                          ; 0x0E10 — entry → L_0F60
pad ; nop_swap                          ;        delay slot
pad ; b L_0FD0                          ; 0x0E20 — entry → L_0FD0
pad ; nop_swap                          ;        delay slot
pad ; b L_10A8                          ; 0x0E30 — entry → L_10A8
pad ; nop_swap                          ;        delay slot
pad ; nop_swap                          ; 0x0E40 — reserved slot
pad ; nop_swap                          ; 0x0E48 — reserved slot
pad ; b L_10C0                          ; 0x0E50 — entry → L_10C0
pad ; nop_swap                          ;        delay slot
pad ; b L_1118                          ; 0x0E60 — entry → L_1118
pad ; nop_swap                          ;        delay slot
pad ; b L_15D8                          ; 0x0E70 — entry → L_15D8  (far-target)
pad ; nop_swap                          ;        delay slot
pad ; b L_1170                          ; 0x0E80 — entry → L_1170
pad ; nop_swap                          ;        delay slot
pad ; b L_1398                          ; 0x0E90 — entry → L_1398
pad ; nop_swap                          ;        delay slot

; =======================================================================
; PROGRAM 2 SUBROUTINE BODIES — mostly direct clones of program 1's
; routines (sub_0110 / sub_0198 / sub_01D0 / sub_0240 / sub_0318 /
; sub_03B8), at fresh VRAM offsets in this concatenated blob.
; =======================================================================

; -----------------------------------------------------------------------
; sub_0EA0 — quad-copy loop with count header + xgkick + END.
;
; Same algorithm as sub_0110 (program 1) but self-contained: it ends
; with `xgkick vi07` and an E-bit terminator instead of falling
; through to a sibling routine.
; -----------------------------------------------------------------------
sub_0EA0:
pad ; xtop vi12
pad ; ilwr.x vi10, vi12
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; lqi.xyzw vf29, vi12
pad ; iaddiu vi13, vi00, 32767
pad ; iand vi10, vi13, vi10
pad ; sqi.xyzw vf29, vi09
sub_0EA0_loop:
pad ; lqi.xyzw vf28, vi12
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_0EA0_loop
pad ; sqi.xyzw vf28, vi09                ; (branch delay slot)
pad ; nop_swap
pad ; xgkick vi07
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0F28 — patch .xy lanes of mem[2] from VIF input.  Direct clone
; of sub_0198 in program 1.
; -----------------------------------------------------------------------
sub_0F28:
pad ; xtop vi01
pad ; lq.xyzw vf30, 2(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; move.xy vf30, vf31
pad ; sq.xyzw vf30, 2(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0F60 — bulk 4-quad upload to mem[256..259].  Direct clone of
; sub_01D0 in program 1 (same vf18/19/16/17 destination order).
; -----------------------------------------------------------------------
sub_0F60:
pad ; xtop vi12
pad ; iaddiu vi13, vi00, 256
pad ; lqi.xyzw vf18, vi12
pad ; lqi.xyzw vf19, vi12
pad ; lqi.xyzw vf16, vi12
pad ; lqi.xyzw vf17, vi12
pad ; sqi.xyzw vf18, vi13
pad ; sqi.xyzw vf19, vi13
pad ; sqi.xyzw vf16, vi13
pad ; sqi.xyzw vf17, vi13
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; exit_0FC0 — shared "end immediately" stub for program 2.  Direct
; clone of exit_0230 in program 1.
; -----------------------------------------------------------------------
exit_0FC0:
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0FD0 — palette-indexed vertex transform with GS kick.  Direct
; clone of sub_0240 in program 1; same algorithm, fall-through into
; sub_10A8 for its terminator.
; -----------------------------------------------------------------------
sub_0FD0:
pad ; xtop vi12
pad ; iaddiu vi11, vi12, 1
pad ; ilwr.x vi10, vi12
pad ; lq.xyzw vf29, 0(vi12)
pad ; iaddiu vi13, vi00, 32767
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; sqi.xyzw vf29, vi09
pad ; iand vi10, vi13, vi10
pad ; iaddiu vi13, vi00, 1
pad ; lq.xyzw vf09, 0(vi11)
pad ; ilwr.w vi14, vi11
pad ; nop_swap
pad ; iand vi15, vi13, vi14

sub_0FD0_loop:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)
pad ; move.w vf09, vf00
pad ; iaddiu vi11, vi11, 1
pad ; ilwr.w vi14, vi11
pad ; iaddi vi10, vi10, -1
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09
pad ; lq.xyzw vf09, 0(vi11)
pad ; iand vi15, vi13, vi14
pad ; ibne vi10, vi00, sub_0FD0_loop
pad ; sqi.xyzw vf10, vi09                ; (branch delay slot)

pad ; nop_swap
pad ; xgkick vi07
pad ; nop_swap                           ; falls through into sub_10A8

; -----------------------------------------------------------------------
; sub_10A8 — final palette-step + exit.  Direct clone of sub_0318;
; reachable as own entry OR fall-through from sub_0FD0.
; -----------------------------------------------------------------------
sub_10A8:
add.xy vf16, vf16, vf17 ; nop_swap
pad ; b exit_0FC0                        ; → exit_0FC0 (END)
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_10C0 — I-register setup + 4-quad load.
;
; Loads two I-immediates into the VU0 I-register via the I-bit on a
; `pad`-upper bundle:
;   - 0x10C8: pad[I] + imm 0x4B7FFFFE (= IEEE-754 ~16777214.0;
;     used by `addi.w vf14, vf00` at 0x10D0 to set vf14.w).
;   - 0x10D8: pad[I] + imm 0x457FF000 (= IEEE-754 4094.0;
;     used by `addi.xy vf14, vf00` at 0x10E0 to set vf14.xy).
; Then loads vf01..vf04 from the vi13 stream.
;
; assemble_vu0.py has no I-bit `pad` suffix yet, so both I-bundles
; are emitted as two raw `.word`s.  disasm renders the lowers as
; `jalr vi31, vi31` (0x4B7FFFFE) and an op7=0x22 ".word" (0x457FF000)
; — both are immediate misreads.
; -----------------------------------------------------------------------
sub_10C0:
pad ; xtop vi13
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE (~16777214.0f)
addi.w vf14, vf00 ; move.xyzw vf13, vf00 ; vf14.w = vf00.w + I (= 16777214.0); vf13 = 0
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000 (= 4094.0f)
addi.xy vf14, vf00 ; nop_swap            ; vf14.xy = vf00.xy + I (= 4094.0)
pad ; lqi.xyzw vf01, vi13
pad ; lqi.xyzw vf02, vi13
pad ; lqi.xyzw vf03, vi13
pad ; lqi.xyzw vf04, vi13
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1118 — bulk 8-quad load into vf05..vf12.  Variant of sub_03B8
; (program 1) at a different destination-register block.
; -----------------------------------------------------------------------
sub_1118:
pad ; xtop vi13
pad ; lqi.xyzw vf05, vi13
pad ; lqi.xyzw vf06, vi13
pad ; lqi.xyzw vf07, vi13
pad ; lqi.xyzw vf08, vi13
pad ; lqi.xyzw vf09, vi13
pad ; lqi.xyzw vf10, vi13
pad ; lqi.xyzw vf11, vi13
pad ; lqi.xyzw vf12, vi13
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1170 — 4-bundle shared terminator (TPC=0xE0 in program 2's
; dispatch).  Same shape as sub_0A30: an extra `nop_swap` slot before
; the E-bit so the sub_1188 loop tail's `b L_1170` lands one bundle
; ahead of the END.
; -----------------------------------------------------------------------
sub_1170:
pad ; nop_swap                           ; do nothing (entry / branch delay slot)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1188 — program-2 skinned vertex transform (variant 4).
;
; Same overall algorithm as sub_0428 (see that routine for full docs)
; with the following differences:
;   * Uses vi04 as the count register (not vi06) and vi05 as a 3-slot
;     decimator (not vi07).
;   * Output-base offset is +252 quads (not +192): `iaddiu vi01, vi13,
;     252`.  vi01 = vi13 + 252; output cursor vi03 = vi01 + 1.
;   * Lighting/color registers shuffled: front-face marker vf19
;     (not vf26), back-face marker vf20 (not vf27).
;   * Bone-weight register vf16 (not vf21/22); per-vertex matrix
;     selection via vf15/vf16/vf17/vf18.
;   * Loop start label is sub_1188_loop (= L_1290), reached after a
;     full pre-loop matrix-mul prologue.
;   * `iaddiu vi07, vi00, 208` sets the clip-mask in vi07 (not vi09).
;   * Bundle 0x12C8 is the I-bit 255.0f trick (upper `mul.xyz vf22,
;     vf18, vf29` + I-bit; lower 0x437F0000 → I); disasm reads the
;     lower as `bal vi31, L_12D0`, which is a misread.
;   * Loop tail: `b L_1170` (into the 1-bundle pre-END at sub_1170).
; -----------------------------------------------------------------------
sub_1188:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13                 ; vi04 = count
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 252            ; output base = vi13 + 252
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00                  ; vf19.w = 0 (front-face marker)
pad ; mfir.w vf20, vi14                  ; vf20.w = 0x8000 (back-face marker)
pad ; iaddiu vi07, vi00, 208             ; vi07 = clip mask 0xD0
pad ; lqi.xyzw vf18, vi02
pad ; lq.xyzw vf23, 2(vi00)
sub.w       vf21, vf21, vf21 ; lq.xyzw vf16, 1(vi02)    ; vf21.w = 0; load weight quad
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; iaddiu vi02, vi02, 3

mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
add.xy      vf17, vf17, vf23 ; nop_swap
pad ; nop_swap
pad ; div Q, vf00.w, vf28.w
pad ; nop_swap
pad ; nop_swap

sub_1188_loop:
mulax.xyzw  vf09, vf29 ; lqi.xyzw vf15, vi02
madday.xyzw vf10, vf29 ; lqi.xyzw vf16, vi02
maddaz.xyzw vf11, vf29 ; nop_swap
maddw.xyzw  vf29, vf12, vf29 ; iaddi vi04, vi04, -1
mulq.xyz    vf28, vf28 ; waitq
mulq.xyz    vf21, vf17 ; nop_swap
mulax.xyzw  vf01, vf15 ; move.w vf22, vf18
; I-bit bundle: upper mul.xyz vf22,vf18,vf29 + I-bit; lower = 255.0f → I
.word 0x81DD95AA ; .word 0x437F0000
madday.xyzw vf02, vf15 ; lqi.xyzw vf17, vi02
ftoi4.xyz   vf19, vf28 ; sq.xyzw vf21, 0(vi03)
ftoi4.xyz   vf20, vf28 ; nop_swap
minii.xyzw  vf22, vf22 ; nop_swap
sub.xyw     vf00, vf13, vf28 ; nop_swap
sub.xyw     vf00, vf28, vf14 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
ftoi0.xyzw  vf22, vf22 ; iaddi vi05, vi05, -1
maddw.xyzw  vf28, vf04, vf00 ; fmand vi14, vi07
mulax.xyzw  vf05, vf16 ; fmand vi14, vi14
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; ibne vi14, vi07, L_1358
maddw.xyzw  vf29, vf08, vf16 ; sq.xyzw vf22, 1(vi03)
pad ; ibgtz vi05, L_1360
pad ; sq.xyzw vf19, 2(vi03)
pad ; b L_1368
pad ; nop_swap
L_1358:
pad ; iaddiu vi05, vi00, 3
L_1360:
pad ; sq.xyzw vf20, 2(vi03)
L_1368:
pad ; div Q, vf00.w, vf28.w
maxx.xyzw   vf29, vf29, vf00 ; ibne vi04, vi00, sub_1188_loop
pad ; iaddiu vi03, vi03, 3
pad ; xgkick vi01
pad ; b L_1170
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_1398 — 3-bundle shared terminator (TPC=0xE0 dispatch via 0x0E90;
; also `b L_1398` from sub_13B0).  Same shape as sub_0410.
; -----------------------------------------------------------------------
sub_1398:
pad ; nop_swap                           ; do nothing (entry)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_13B0 — program-2 skinned vertex transform (variant 5).
;
; Near-clone of sub_1188 with restructured loop body and a different
; placement of the I-bit immediate bundle (now at 0x1510 with the
; same `0x437F0000` = 255.0f I-immediate, upper `mul.xyz vf22, vf18,
; vf29` with I-bit).  Loop tail: `b L_1398`.
; -----------------------------------------------------------------------
sub_13B0:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 252
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; iaddiu vi07, vi00, 208
pad ; lqi.xyzw vf18, vi02
pad ; lq.xyzw vf23, 2(vi00)
sub.w       vf21, vf21, vf21 ; lq.xyzw vf16, 1(vi02)
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; iaddiu vi02, vi02, 3

mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
add.xy      vf17, vf17, vf23 ; nop_swap
pad ; nop_swap
pad ; div Q, vf00.w, vf28.w
pad ; nop_swap
pad ; nop_swap

sub_13B0_loop:
mulax.xyzw  vf09, vf29 ; iaddi vi04, vi04, -1
madday.xyzw vf10, vf29 ; lqi.xyzw vf15, vi02
maddaz.xyzw vf11, vf29 ; lqi.xyzw vf16, vi02
maddw.xyzw  vf29, vf12, vf29 ; nop_swap
mulq.xyz    vf28, vf28 ; waitq
mulq.xyz    vf21, vf17 ; nop_swap
mulax.xyzw  vf01, vf15 ; lqi.xyzw vf17, vi02
mul.xyz     vf29, vf29, vf29 ; nop_swap             ; vf29²
ftoi4.xyz   vf19, vf28 ; move.w vf22, vf18
ftoi4.xyz   vf20, vf28 ; sq.xyzw vf21, 0(vi03)
sub.xyw     vf00, vf13, vf28 ; nop_swap
; I-bit bundle: upper mul.xyz vf22,vf18,vf29 + I-bit; lower = 255.0f → I
.word 0x81DD95AA ; .word 0x437F0000
sub.xyw     vf00, vf28, vf14 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; fmand vi14, vi07
minii.xyzw  vf22, vf22 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; fmand vi14, vi14
mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
ftoi0.xyzw  vf22, vf22 ; iaddi vi05, vi05, -1
maddaz.xyzw vf07, vf16 ; div Q, vf00.w, vf28.w
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
add.xy      vf17, vf17, vf23 ; ibne vi14, vi07, L_1598
pad ; sq.xyzw vf22, 1(vi03)
pad ; ibgtz vi05, L_15A0
pad ; sq.xyzw vf19, 2(vi03)
pad ; b L_15A8
pad ; nop_swap
L_1598:
pad ; iaddiu vi05, vi00, 3
L_15A0:
pad ; sq.xyzw vf20, 2(vi03)
L_15A8:
maxx.xyzw   vf29, vf29, vf00 ; iaddiu vi03, vi03, 3
pad ; ibne vi04, vi00, sub_13B0_loop
pad ; nop_swap                           ; (branch delay slot)
pad ; xgkick vi01
pad ; b L_1398
.word 0x4A380100 ; nop                   ; upper: `add.w vf04,vf00,vf24` + flag bits (E/T/25-ish)

; -----------------------------------------------------------------------
; sub_15D8 — 4-bundle shared terminator with extra `nop_swap` at
; L_15E0 (so sub_15F8 can `b L_15E0` and hit the E-bit one bundle
; later).  Same shape as sub_0A30 / sub_1170.
; -----------------------------------------------------------------------
sub_15D8:
pad ; nop_swap                           ; do nothing (entry / branch delay slot)
L_15E0:
pad ; nop_swap                           ; sub_15F8's `b L_15E0` lands here
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_15F8 — program-2 skinned vertex transform (variant 6).
;
; Near-clone of sub_13B0 with one additional `move.w vf29, vf28` /
; `ftoi0.xyzw vf22, vf18` bundle at L_16D0, and a different loop-exit
; pattern that branches to L_15E0 (one bundle past sub_15D8 entry)
; for the END.
; -----------------------------------------------------------------------
sub_15F8:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 252
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; iaddiu vi07, vi00, 208
pad ; lqi.xyzw vf18, vi02
pad ; lq.xyzw vf23, 2(vi00)
sub.w       vf21, vf21, vf21 ; lqi.xyzw vf15, vi02
pad ; lqi.xyzw vf17, vi02
pad ; nop_swap
pad ; nop_swap

mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
pad ; lqi.xyzw vf15, vi02
pad ; nop_swap
pad ; nop_swap
add.xy      vf17, vf17, vf23 ; div Q, vf00.w, vf28.w

sub_15F8_loop:
ftoi0.xyzw  vf22, vf18 ; move.w vf29, vf28
mulq.xyz    vf29, vf28 ; waitq
mulq.xyz    vf21, vf17 ; iaddi vi05, vi05, -1
mulax.xyzw  vf01, vf15 ; lqi.xyzw vf17, vi02
madday.xyzw vf02, vf15 ; sq.xyzw vf22, 1(vi03)
sub.xyw     vf00, vf13, vf29 ; iaddi vi04, vi04, -1
sub.xyw     vf00, vf29, vf14 ; sq.xyzw vf21, 0(vi03)
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; lqi.xyzw vf15, vi02
ftoi4.xyz   vf19, vf29 ; fmand vi14, vi07
ftoi4.xyz   vf20, vf29 ; fmand vi14, vi14
add.xy      vf17, vf17, vf23 ; ibne vi14, vi07, L_1758
pad ; div Q, vf00.w, vf28.w
pad ; ibgtz vi05, L_1760
pad ; sq.xyzw vf19, 2(vi03)
pad ; b L_1768
pad ; nop_swap
L_1758:
pad ; iaddiu vi05, vi00, 3
L_1760:
pad ; sq.xyzw vf20, 2(vi03)
L_1768:
pad ; iaddiu vi03, vi03, 3
pad ; ibne vi04, vi00, sub_15F8_loop
pad ; nop_swap                           ; (branch delay slot)
pad ; xgkick vi01
pad ; b L_15E0
pad ; nop_swap                           ; (branch delay slot)

; =======================================================================
; THIRD VU0 PROGRAM begins here.  Same multi-program concatenation as
; the program-1 → program-2 transition at 0x0DB0.
; =======================================================================

; Program-3 pre-header filler (one bundle of true-zero halves) +
; control-flag prologue (parallels program 2's 0x0DB0..0x0DC8 with a
; different FCSET immediate).
nop ; nop                                ; 0x1798 — true-zero filler
nop ; .word 0x70000000                   ; 0x17A0 — lower op7=0x38
nop ; nop                                ; 0x17A8 — true-zero filler
nop ; .word 0x6000016C                   ; 0x17B0 — FCSET imm24=0x16C
.word 0x4A000000 ; nop                   ; 0x17B8 — upper FMAC-family + lower true-zero

; Program-3 entry-stub dispatch (continuous from here through 0x18E8).
pad ; b L_18F0                           ; 0x17C0 — entry → L_18F0
pad ; nop_swap                           ;        delay slot
pad ; b L_1978                           ; 0x17D0 — entry → L_1978
pad ; nop_swap                           ;        delay slot
pad ; nop_swap                           ; 0x17E0 — reserved slot
pad ; nop_swap                           ; 0x17E8 — reserved slot
pad ; nop_swap                           ; 0x17F0 — reserved slot
pad ; nop_swap                           ; 0x17F8 — reserved slot
pad ; b L_19B0                           ; 0x1800 — entry → L_19B0
pad ; nop_swap                           ;        delay slot
pad ; b L_1A20                           ; 0x1810 — entry → L_1A20
pad ; nop_swap                           ;        delay slot
pad ; b L_1AF8                           ; 0x1820 — entry → L_1AF8
pad ; nop_swap                           ;        delay slot
pad ; nop_swap                           ; 0x1830 — reserved slot
pad ; nop_swap                           ; 0x1838 — reserved slot
pad ; b L_1B10                           ; 0x1840 — entry → L_1B10
pad ; nop_swap                           ;        delay slot
pad ; b L_1BF8                           ; 0x1850 — entry → L_1BF8
pad ; nop_swap                           ;        delay slot
pad ; nop_swap                           ; 0x1860 — reserved slot
pad ; nop_swap                           ; 0x1868 — reserved slot
pad ; nop_swap                           ; 0x1870 — reserved slot
pad ; nop_swap                           ; 0x1878 — reserved slot
pad ; nop_swap                           ; 0x1880 — reserved slot
pad ; nop_swap                           ; 0x1888 — reserved slot
pad ; nop_swap                           ; 0x1890 — reserved slot
pad ; nop_swap                           ; 0x1898 — reserved slot
pad ; nop_swap                           ; 0x18A0 — reserved slot
pad ; nop_swap                           ; 0x18A8 — reserved slot
pad ; nop_swap                           ; 0x18B0 — reserved slot
pad ; nop_swap                           ; 0x18B8 — reserved slot
pad ; b L_1C90                           ; 0x18C0 — entry → L_1C90
pad ; nop_swap                           ;        delay slot
pad ; b L_1EA0                           ; 0x18D0 — entry → L_1EA0
pad ; nop_swap                           ;        delay slot
pad ; b L_2BB0                           ; 0x18E0 — entry → L_2BB0  (far target)
pad ; nop_swap                           ;        delay slot

; =======================================================================
; PROGRAM 3 SUBROUTINE BODIES.  Most are direct clones of program 1/2
; routines at new VRAM offsets; the new ones (sub_1B10 / sub_1BF8 /
; sub_1C90 / sub_1CC8) handle bulk-data uploads and another skinned
; transform variant.
; =======================================================================

; -----------------------------------------------------------------------
; sub_18F0 — copy-with-count + xgkick + END (clone of sub_0EA0).
; -----------------------------------------------------------------------
sub_18F0:
pad ; xtop vi12
pad ; ilwr.x vi10, vi12
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; lqi.xyzw vf29, vi12
pad ; iaddiu vi13, vi00, 32767
pad ; iand vi10, vi13, vi10
pad ; sqi.xyzw vf29, vi09
sub_18F0_loop:
pad ; lqi.xyzw vf28, vi12
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_18F0_loop
pad ; sqi.xyzw vf28, vi09                ; (branch delay slot)
pad ; nop_swap
pad ; xgkick vi07
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1978 — mem[2].xy patch (clone of sub_0F28).
; -----------------------------------------------------------------------
sub_1978:
pad ; xtop vi01
pad ; lq.xyzw vf30, 2(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; move.xy vf30, vf31
pad ; sq.xyzw vf30, 2(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_19B0 — 4-quad matrix upload to mem[256] (clone of sub_0F60).
; -----------------------------------------------------------------------
sub_19B0:
pad ; xtop vi12
pad ; iaddiu vi13, vi00, 256
pad ; lqi.xyzw vf18, vi12
pad ; lqi.xyzw vf19, vi12
pad ; lqi.xyzw vf16, vi12
pad ; lqi.xyzw vf17, vi12
pad ; sqi.xyzw vf18, vi13
pad ; sqi.xyzw vf19, vi13
pad ; sqi.xyzw vf16, vi13
pad ; sqi.xyzw vf17, vi13
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; exit_1A10 — shared E-bit-only stub (clone of exit_0FC0).
; -----------------------------------------------------------------------
exit_1A10:
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1A20 — palette-indexed vertex transform (clone of sub_0FD0).
; Falls through into sub_1AF8 for terminator.
; -----------------------------------------------------------------------
sub_1A20:
pad ; xtop vi12
pad ; iaddiu vi11, vi12, 1
pad ; ilwr.x vi10, vi12
pad ; lq.xyzw vf29, 0(vi12)
pad ; iaddiu vi13, vi00, 32767
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; sqi.xyzw vf29, vi09
pad ; iand vi10, vi13, vi10
pad ; iaddiu vi13, vi00, 1
pad ; lq.xyzw vf09, 0(vi11)
pad ; ilwr.w vi14, vi11
pad ; nop_swap
pad ; iand vi15, vi13, vi14

sub_1A20_loop:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)
pad ; move.w vf09, vf00
pad ; iaddiu vi11, vi11, 1
pad ; ilwr.w vi14, vi11
pad ; iaddi vi10, vi10, -1
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09
pad ; lq.xyzw vf09, 0(vi11)
pad ; iand vi15, vi13, vi14
pad ; ibne vi10, vi00, sub_1A20_loop
pad ; sqi.xyzw vf10, vi09                ; (branch delay slot)

pad ; nop_swap
pad ; xgkick vi07
pad ; nop_swap                           ; falls through into sub_1AF8

; -----------------------------------------------------------------------
; sub_1AF8 — final palette-step + `b exit_1A10` (clone of sub_10A8).
; -----------------------------------------------------------------------
sub_1AF8:
add.xy vf16, vf16, vf17 ; nop_swap
pad ; b exit_1A10
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_1B10 — bulk 13-quad copy from VIF input to mem[16..27], plus a
; final `lq mem[3]; sq mem[37]` constant-copy.
;
; The first four quads land in vf01..vf04 (then stored to mem[16..19]);
; the next nine quads all stream through vf31 (each lqi → sq pair),
; landing in mem[20..27].  At the tail, a fixed `lq vf31, 3(vi00)`
; reads mem[3] and writes it to mem[37].
; -----------------------------------------------------------------------
sub_1B10:
pad ; xtop vi01
pad ; lqi.xyzw vf01, vi01
pad ; sq.xyzw vf01, 16(vi00)
pad ; lqi.xyzw vf02, vi01
pad ; sq.xyzw vf02, 17(vi00)
pad ; lqi.xyzw vf03, vi01
pad ; sq.xyzw vf03, 18(vi00)
pad ; lqi.xyzw vf04, vi01
pad ; sq.xyzw vf04, 19(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 20(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 21(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 22(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 23(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 24(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 25(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 26(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 27(vi00)
pad ; lq.xyzw vf31, 3(vi00)              ; vf31 = mem[3]
pad ; sq.xyzw vf31, 37(vi00)             ; mem[37] = vf31
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1BF8 — bulk 8-quad copy from VIF input via vf31 to mem[28..35].
;
; Tail-half of sub_1B10's upload pattern; each lqi/sq pair streams
; one quad through vf31 to a fixed mem slot.
; -----------------------------------------------------------------------
sub_1BF8:
pad ; xtop vi01
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 28(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 29(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 30(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 31(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 32(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 33(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 34(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 35(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1C90 — I-register setup + small prologue.  Same I-bit pattern
; as sub_10C0 (two `pad[I]` bundles loading 0x4B7FFFFE and 0x457FF000),
; consumed by `addi.w/.xy vf14, vf00`.  Falls through into sub_1CC8.
; -----------------------------------------------------------------------
sub_1C90:
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE
addi.w vf14, vf00 ; move.xyzw vf13, vf00 ; vf14.w = I; vf13 = 0
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000 (= 4094.0f)
addi.xy vf14, vf00 ; nop_swap            ; vf14.xy = I
pad ; lq.xyzw vf23, 2(vi00)              ; vf23 = mem[2]
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1CC8 — program-3 skinned vertex transform (variant 7).
;
; Restructured variant of sub_1188 / sub_13B0:
;   * Output base is +192 (not +252).
;   * `move.z vf23, vf00` patches vf23.z = 0 mid-setup (mem[2].z mask).
;   * `add.xyz vf21, vf17, vf23` accumulator uses .xyz lanes (not the
;     usual .xy) plus a sub.w guard `sub.w vf00, vf17, vf00`.
;   * `mulw.xyzw vf15, vf24, vf00` / `mulw.xyzw vf28, vf29, vf00` in
;     the loop body (w-broadcast scaled by vf00.w=1).
;   * Two `ibne vi04, vi00, L_1DA8` exit-paths (post-front-face and
;     post-back-face) each kicked by `xgkick vi01` and `b L_1C90`
;     back into sub_1C90's pre-END E-bit.
;   * Uses `ibeq vi15, vi00, L_1DC8` to skip a reset of vi05 to 3.
; -----------------------------------------------------------------------
sub_1CC8:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192             ; output base = vi13 + 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddi vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; lq.xyzw vf15, 0(vi02)
sub.w       vf21, vf21, vf21 ; lq.xyzw vf17, 1(vi02)
pad ; lq.xyzw vf18, 2(vi02)
pad ; move.z vf23, vf00                  ; vf23.z = 0 (lane mask)
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
sub.w       vf00, vf17, vf00 ; lq.xyzw vf15, 3(vi02)
add.xyz     vf21, vf17, vf23 ; iaddiu vi07, vi00, 208 ; vi07 = 0xD0 clip mask
pad ; nop_swap
pad ; div Q, vf00.w, vf28.w
pad ; fsand vi15, 0x2
pad ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap

sub_1CC8_loop:
maddaz.xyzw vf03, vf15 ; lq.xyzw vf17, 4(vi02)
maddw.xyzw  vf29, vf04, vf00 ; ibeq vi15, vi00, L_1DC8
pad ; iaddi vi04, vi04, -1               ; (delay slot)
pad ; iaddiu vi05, vi00, 3
L_1DC8:
mulq.xyz    vf28, vf28 ; iaddi vi05, vi05, -1
mulq.xyz    vf21, vf21 ; iaddiu vi02, vi02, 3
ftoi0.xyzw  vf22, vf18 ; lq.xyzw vf24, 3(vi02)
sub.w       vf00, vf17, vf00 ; div Q, vf00.w, vf29.w
sub.xyw     vf00, vf13, vf28 ; lq.xyzw vf18, 2(vi02)
sub.xyw     vf00, vf28, vf14 ; sq.xyzw vf21, 0(vi03)
ftoi4.xyz   vf19, vf28 ; sq.xyzw vf22, 1(vi03)
ftoi4.xyz   vf20, vf28 ; fsand vi15, 0x2
mulw.xyzw   vf15, vf24, vf00 ; fmand vi14, vi07
mulw.xyzw   vf28, vf29, vf00 ; fmand vi14, vi14
add.xyz     vf21, vf17, vf23 ; ibne vi14, vi07, L_1E68
pad ; iaddiu vi03, vi03, 3
pad ; ibgtz vi05, L_1E70
pad ; nop_swap                           ; (delay slot)
mulax.xyzw  vf01, vf15 ; ibne vi04, vi00, sub_1CC8_loop
madday.xyzw vf02, vf15 ; sq.xyzw vf19, -1(vi03)
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_1C90                           ; → sub_1C90's E-bit
pad ; nop_swap                           ; (branch delay slot)
L_1E68:
pad ; iaddiu vi05, vi00, 3
L_1E70:
mulax.xyzw  vf01, vf15 ; ibne vi04, vi00, sub_1CC8_loop
madday.xyzw vf02, vf15 ; sq.xyzw vf20, -1(vi03)
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_1C90                           ; → sub_1C90's E-bit
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_1EA0 — second I-register setup (clone of sub_1C90), but only
; covers the first 4 bundles in this chunk; the routine extends past
; 0x1F00 into the next batch.  Stopping here at the natural seam.
; -----------------------------------------------------------------------
sub_1EA0:
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE
L_1EA8:
addi.w vf14, vf00 ; move.xyzw vf13, vf00
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000
addi.xy vf14, vf00 ; nop_swap
pad ; lq.xyzw vf23, 2(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot
; --- sub_1EA0 transform body (0x1ED8..0x2078) ---
; Reached directly when the EE sets VU0_TPC=0x1ED8 (or a wrapper jumps
; here).  The routine processes a vertex batch and at the loop tail
; branches `b L_1EA8` back into sub_1EA0's I-setup tail, which then
; hits the 0x1EC8 E-bit to terminate.  Same exit-via-branch-into-tail
; pattern as sub_1CC8 / sub_1C90 in this program.
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddi vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; lq.xyzw vf15, 0(vi02)
sub.w       vf21, vf21, vf21 ; lq.xyzw vf17, 1(vi02)
pad ; lq.xyzw vf18, 2(vi02)
pad ; move.z vf23, vf00
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
sub.w       vf00, vf17, vf00 ; lq.xyzw vf15, 3(vi02)
pad ; iaddiu vi07, vi00, 208
pad ; nop_swap
pad ; div Q, vf00.w, vf28.w
add.xyz     vf21, vf17, vf23 ; fsand vi15, 0x2
pad ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; lq.xyzw vf17, 4(vi02)

L_1FB8:
maddaz.xyzw vf03, vf15 ; ibeq vi15, vi00, L_1FD0
.word 0x4A000100 ; nop                   ; upper: `add vf04, vf00, vf00` + flag bits (E/T-ish)
maddw.xyzw  vf29, vf04, vf00 ; iaddiu vi02, vi02, 3
L_1FD0:
pad ; iaddiu vi05, vi00, 3
mulq.xyz    vf28, vf28 ; iaddi vi05, vi05, -1
mulq.xyz    vf21, vf21 ; lq.xyzw vf24, 3(vi02)
ftoi0.xyzw  vf22, vf18 ; iaddi vi04, vi04, -1
ftoi4.xyz   vf19, vf28 ; div Q, vf00.w, vf29.w
sub.w       vf00, vf17, vf00 ; lq.xyzw vf18, 2(vi02)
ftoi4.xyz   vf20, vf28 ; sqi.xyzw vf21, vi03
mulw.xyzw   vf15, vf24, vf00 ; sqi.xyzw vf22, vi03
mulw.xyzw   vf28, vf29, vf00 ; ibgtz vi05, L_2050
pad ; fsand vi15, 0x2
add.xyz     vf21, vf17, vf23 ; ibne vi04, vi00, L_1FB8
mulax.xyzw  vf01, vf15 ; sqi.xyzw vf19, vi03
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_1EA8                           ; → sub_1EA0's E-bit
pad ; nop_swap                           ; (branch delay slot)
L_2050:
add.xyz     vf21, vf17, vf23 ; ibne vi04, vi00, L_1FB8
mulax.xyzw  vf01, vf15 ; sqi.xyzw vf20, vi03
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_1EA8                           ; → sub_1EA0's E-bit
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_2080 — hierarchical LOD mesh subdivision driver.
;
; Top-level dispatcher that walks 6 LOD tiers, each running the same
; per-vertex transform inner loop with different bone-count and
; mip-step parameters.  The inner subroutines are:
;   L_25C0 — per-vertex blend + lit-color quantize (called via
;            `bal vi02` from every tier's inner loop).
;   L_2580 — 3-quad output flush (called via `bal vi02` at each
;            tier's end).
;   L_2570 — `jr vi15` early-out (taken when vi11 hasn't accumulated
;            anything).
;   L_2740 — front/back-face refinement (called via `bal vi01`).
;   L_27A0 — perspective-divide + clip-test continuation of L_2740.
;
; Setup (0x2080..0x2168):
;   - vi08 = mem[104] (input vertex buffer base)
;   - Initial L_2088 store-pattern: copies vf22 to slots {0,9},
;     vf23 to {3}, vf24 to {6}, then re-loads through stored vi03
;     offsets and applies vf17 .xy fixups before saving back.
;   - Re-loads three quads from vi07-relative slots and integerizes
;     via itof0 (no — actually IEEE float "int-to-float" cast).
;
; Tier loop body (repeats 6 times with different constants):
;   - vi05 = work-quad-count (2048 / 1024 / 512 / 256 / 128 / 64)
;   - vi06 = mip-step          (32 / 16 / 8 / 4 / 2 / 1)
;   - vi07 = bone-row-index    (2 / 2 / 1 / 1 / 0 / 0)
;   - vi10 = inner-loop counter (3) ; vi11 = output cursor (0 initial)
;   - 3 lqi prefetches (vf21/22/23) from vi08-stream
;   - Inner loop @ L_2XXX:  `bal L_25C0` ; isubiu vi10 ; ibne back
;   - `iaddiu vi08, 164 or 104` (swap input buffer)
;   - `bal L_2580` (flush output)
;   - `ibeq vi11, L_2570` (early-out if nothing accumulated)
;   - subw.x / addw.x toggles the sign of vf30.x for the next tier
;
; Final block (0x2540..0x2568):
;   `bal vi01, L_2818` — jumps to a save-context subroutine that
;   reads vi10=vi11 and lqi 3 quads, then xgkicks vi02 for output.
;
; L_2570: `jr vi15` — return-to-caller stub used by all early-out
;   `ibeq vi11, L_2570` paths.
;
; L_2580: 3-quad flush subroutine.  Reads 3 quads from vi08-relative
;   slots, sqi to vi09-stream, then `jr vi02` returns to caller.
;
; L_25C0: per-vertex blend + lit-color subroutine.  3 add.xyzw
;   bundles produce vf17/vf18/vf19 = vf31 + vfXX (lit-additive blend),
;   then two `.word`-emitted flag-bits-set FMACs at 0x25D8/0x25E0
;   (op6=0x3F .xyz, fd=7 fs=17/21 ft=17/21 — likely partial-mask
;   accumulator collapse), then fcget polls clip flags.  Based on
;   the masked flags, branches between three slot-store paths:
;     - L_2658: 3 sqi (vf25/26/27 only).
;     - L_2698 → 6 sqi (vf17..vf19 + vf25..vf27) + iaddiu vi11+=2.
;     - L_2710: 3 sqi (vf17..vf19) + iaddiu vi11+=1.
;   All converge at L_2730: `jr vi02` return.
;
; L_2740: refinement subroutine.  Computes `vf25 = mulx(vf17, vf30)`
;   and `vf26 = mulx(vf21, vf30)`, subtracts to get error vectors,
;   then loop-walks with `mr32` rotate-by-32 to swizzle lanes until
;   the per-bone error counter vi12 hits zero, dropping into L_27A0.
;
; L_27A0: perspective-divide path.  `div Q = vf25.x/vf27.x` then
;   `addq.x vf29` + `abs.x vf29` yields a magnitude.  Three
;   sub.xyzw bundles produce vf25/vf26/vf27 = (vf21..vf23)-(vf17..vf19),
;   each mulx'd by vf29, and finally added into vf17..vf19.  The
;   routine falls through past 0x27F8 into more code at 0x2800+.
; -----------------------------------------------------------------------
sub_2080:
pad ; iaddiu vi08, vi00, 104             ; vi08 = mem[104] (input vtx base)
L_2088:
pad ; sq.xyzw vf22, 0(vi08)              ; mem[104+0] = vf22
pad ; sq.xyzw vf22, 9(vi08)              ; mem[104+9] = vf22 (mirror)
pad ; sq.xyzw vf23, 3(vi08)              ; mem[104+3] = vf23
pad ; iaddiu vi09, vi00, 164             ; vi09 = mem[164] (output base)
pad ; sq.xyzw vf24, 6(vi08)              ; mem[104+6] = vf24
pad ; lq.xyzw vf22, -8(vi03)             ; reload from vi03 stream
add.xy vf22, vf22, vf17 ; lq.xyzw vf23, -5(vi03)
add.xy vf23, vf23, vf17 ; lq.xyzw vf24, -2(vi03)
add.xy vf24, vf24, vf17 ; nop_swap
pad ; sq.xyzw vf22, 2(vi08)
pad ; sq.xyzw vf22, 11(vi08)
pad ; sq.xyzw vf23, 5(vi08)
pad ; sq.xyzw vf24, 8(vi08)
pad ; lq.xyzw vf22, -5(vi07)
itof0.xyzw vf22, vf22 ; lq.xyzw vf23, -2(vi07)
itof0.xyzw vf23, vf23 ; lq.xyzw vf24, 1(vi07)
itof0.xyzw vf24, vf24 ; nop_swap
pad ; sq.xyzw vf22, 1(vi08)
pad ; sq.xyzw vf22, 10(vi08)
pad ; sq.xyzw vf23, 4(vi08)
pad ; sq.xyzw vf24, 7(vi08)

; --- LOD tier 1 ---
pad ; iaddiu vi05, vi00, 2048
pad ; iaddiu vi06, vi00, 32
pad ; iaddiu vi07, vi00, 2
pad ; iaddiu vi10, vi00, 3
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_2170:
pad ; bal vi02, L_25C0
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_2170
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_2580
pad ; nop_swap
.word 0x100002FF ; nop_swap              ; pad with M-bit flag (bit 28)
pad ; ibeq vi11, vi00, L_2570
pad ; nop_swap

; --- LOD tier 2 ---
pad ; iaddiu vi05, vi00, 1024
pad ; iaddiu vi06, vi00, 16
pad ; iaddiu vi07, vi00, 2
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11             ; vi10 = previous tier's vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_2228:
pad ; bal vi02, L_25C0
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_2228
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_2580
pad ; nop_swap
pad ; ibeq vi11, vi00, L_2570
pad ; nop_swap

; --- LOD tier 3 ---
pad ; iaddiu vi05, vi00, 128
pad ; iaddiu vi06, vi00, 2
pad ; iaddiu vi07, vi00, 0
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_22D8:
pad ; bal vi02, L_25C0
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_22D8
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_2580
pad ; nop_swap
pad ; ibeq vi11, vi00, L_2570
pad ; nop_swap

; --- LOD tier 4 ---
pad ; iaddiu vi05, vi00, 64
pad ; iaddiu vi06, vi00, 1
pad ; iaddiu vi07, vi00, 0
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_2388:
pad ; bal vi02, L_25C0
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_2388
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_2580
pad ; nop_swap
pad ; ibeq vi11, vi00, L_2570
pad ; nop_swap

; --- LOD tier 5 ---
pad ; iaddiu vi05, vi00, 512
pad ; iaddiu vi06, vi00, 8
pad ; iaddiu vi07, vi00, 1
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_2438:
pad ; bal vi02, L_25C0
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_2438
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_2580
pad ; nop_swap
pad ; ibeq vi11, vi00, L_2570
pad ; nop_swap

; --- LOD tier 6 ---
pad ; iaddiu vi05, vi00, 256
pad ; iaddiu vi06, vi00, 4
pad ; iaddiu vi07, vi00, 1
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_24E8:
pad ; bal vi02, L_25C0
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_24E8
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_2580
pad ; nop_swap
pad ; ibeq vi11, vi00, L_2570
pad ; nop_swap

; --- Final consolidation block: call save-context routine at L_2818 ---
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
pad ; bal vi01, L_2818                   ; call save-context routine
pad ; nop_swap

; -----------------------------------------------------------------------
; L_2570 — shared early-out return stub.  `jr vi15` jumps back to
; whatever caller set vi15 to (typically the EE-level VCALLMS).
; -----------------------------------------------------------------------
L_2570:
pad ; jr vi15
pad ; nop_swap

; -----------------------------------------------------------------------
; L_2580 — 3-quad flush subroutine.  Loads 3 quads from mem[vi08+0..2]
; and stores them post-increment into the vi09 output stream.
; Returns via `jr vi02`.
; -----------------------------------------------------------------------
L_2580:
pad ; lq.xyzw vf21, 0(vi08)
pad ; lq.xyzw vf22, 1(vi08)
pad ; lq.xyzw vf23, 2(vi08)
pad ; sqi.xyzw vf21, vi09
pad ; sqi.xyzw vf22, vi09
pad ; sqi.xyzw vf23, vi09
pad ; jr vi02
pad ; nop_swap

; -----------------------------------------------------------------------
; L_25C0 — per-vertex blend + clip-flag-driven output selection.
;
; First three FMACs add vf31 (a tier-shared base vertex) to the
; lqi'd vf21/vf22/vf23, producing vf17/vf18/vf19 as lit + position
; pairs (with output prefetch via lqi vf21/22/23 next-iter).
; Two flag-bits-set FMACs at 0x25D8/0x25E0 do partial-mask masked
; accumulator collapses (emitted as `.word`).
; fcget polls clip flags into vi01; two `iand`/`ibeq` tests select
; between three storage paths (front-face-only / both / back-face-only).
; -----------------------------------------------------------------------
L_25C0:
add.xyzw vf17, vf31, vf21 ; lqi.xyzw vf21, vi08
add.xyzw vf18, vf31, vf22 ; lqi.xyzw vf22, vi08
add.xyzw vf19, vf31, vf23 ; lqi.xyzw vf23, vi08
.word 0x01D189FF ; nop_swap              ; upper op6=0x3F .xyz fd=7 fs=17 ft=17 (FD-dispatch)
.word 0x01D5A9FF ; nop_swap              ; upper op6=0x3F .xyz fd=7 fs=21 ft=21 (FD-dispatch)
pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
pad ; fcget vi01                         ; vi01 = clip flag bits
pad ; iand vi04, vi01, vi05              ; vi04 = vi01 & tier-mask
pad ; nop_swap
pad ; ibeq vi04, vi00, L_2698
pad ; nop_swap
pad ; iand vi04, vi01, vi06              ; vi04 = vi01 & mip-mask
pad ; nop_swap
pad ; ibeq vi04, vi00, L_2658
pad ; nop_swap
pad ; b L_2730
pad ; nop_swap
L_2658:
pad ; bal vi01, L_2740                   ; refine via subroutine
pad ; nop_swap                           ; (delay slot)
pad ; sqi.xyzw vf25, vi09                ; store refined vf25/26/27
pad ; sqi.xyzw vf26, vi09
pad ; sqi.xyzw vf27, vi09
pad ; iaddiu vi11, vi11, 1
pad ; b L_2730
pad ; nop_swap
L_2698:
pad ; iand vi04, vi01, vi06
pad ; nop_swap
pad ; ibeq vi04, vi00, L_2710
pad ; nop_swap
pad ; bal vi01, L_2740                   ; refine (both-path variant)
pad ; nop_swap                           ; (delay slot)
pad ; sqi.xyzw vf17, vi09                ; store base vf17/18/19
pad ; sqi.xyzw vf18, vi09
pad ; sqi.xyzw vf19, vi09
pad ; sqi.xyzw vf25, vi09                ; + refined vf25/26/27
pad ; sqi.xyzw vf26, vi09
pad ; sqi.xyzw vf27, vi09
pad ; iaddiu vi11, vi11, 2
pad ; b L_2730
pad ; nop_swap
L_2710:
pad ; sqi.xyzw vf17, vi09                ; store base vf17/18/19 only
pad ; sqi.xyzw vf18, vi09
pad ; sqi.xyzw vf19, vi09
pad ; iaddiu vi11, vi11, 1
L_2730:
pad ; jr vi02                            ; return
pad ; nop_swap

; -----------------------------------------------------------------------
; L_2740 — per-bone refinement subroutine.
;
; Computes mulx-w broadcasts of vf17/vf21 by vf30, then subw.xyzw
; produces vf25/vf26 = vfXX - (vfXX*vf30.w) error vectors.  vi12 =
; vi07 + vi00 (= tier bone-row index from caller).  Loop walks vi12
; iterations, mr32-rotating vf25/vf26 each time (lane-shift trick),
; then falls into L_27A0 for the perspective-divide path.
; -----------------------------------------------------------------------
L_2740:
mulx.w vf25, vf17, vf30 ; iadd vi12, vi00, vi07
mulx.w vf26, vf21, vf30 ; nop_swap
subw.xyzw vf25, vf17, vf25 ; nop_swap
subw.xyzw vf26, vf21, vf26 ; nop_swap
pad ; nop_swap
L_2768:
pad ; ibeq vi12, vi00, L_27A0
pad ; nop_swap
pad ; mr32.xyzw vf25, vf25
pad ; mr32.xyzw vf26, vf26
pad ; isubiu vi12, vi12, 1
pad ; b L_2768
pad ; nop_swap

; -----------------------------------------------------------------------
; L_27A0 — perspective-divide + clip-test continuation.  Computes
; Q = vf25.x / vf27.x, |Q|, then mixes the per-axis differences by
; abs-Q to produce vf25/vf26/vf27 = vf17/vf18/vf19 + Q*(vfXX-vfYY).
; Bundle 0x27C8 is another flag-bits-set FMAC variant (`.word`).
; -----------------------------------------------------------------------
L_27A0:
sub.xyz vf27, vf26, vf25 ; nop_swap
pad ; div Q, vf25.x, vf27.x
addq.x vf29, vf00 ; waitq
abs.x vf29, vf29 ; nop_swap
sub.xyzw vf25, vf21, vf17 ; nop_swap
.word 0x4AD60200 ; nop                   ; upper: `add.yz vf08, vf00, vf22` + flag bits
sub.xyzw vf26, vf22, vf18 ; nop_swap
sub.xyzw vf27, vf23, vf19 ; nop_swap
mulx.xyzw vf25, vf25, vf29 ; nop_swap
mulx.xyzw vf26, vf26, vf29 ; nop_swap
mulx.xyzw vf27, vf27, vf29 ; nop_swap
add.xyzw vf25, vf25, vf17 ; nop_swap
add.xyzw vf26, vf26, vf18 ; nop_swap
add.xyzw vf27, vf27, vf19 ; nop_swap
pad ; jr vi01                            ; return to L_2740-call-site

; -----------------------------------------------------------------------
; sub_2818 (= L_2818) — save-context vertex output subroutine.
;
; Called by sub_2080's `bal vi01, L_2818`.  Builds a GIF packet via
; mem[vi02], applies matrix transform + perspective divide to vi03-
; stream vertices, ftoi-converts, stores via sq/sqi, then xgkicks the
; final packet.  Two xgkick stages: one with mem[8..11] matrix
; (initial), one with mem[16..19] matrix (post-transform).
; -----------------------------------------------------------------------
sub_2818:
pad ; nop_swap                           ; (entry — also delay slot from L_2818 caller)
pad ; iaddiu vi02, vi00, 37              ; vi02 = mem[37] (GIF tag slot)
pad ; iadd vi03, vi00, vi08              ; vi03 = vi08 (input cursor)
pad ; iaddiu vi07, vi02, 2               ; vi07 = vi02 + 2 (output cursor)
pad ; iaddiu vi11, vi00, 32767           ; vi11 = 0x7FFF
pad ; iaddiu vi11, vi11, 1               ; vi11 = 0x8000
pad ; isw.x vi11, 0(vi02)                ; mem[vi02].x = 0x8000 (count word)
pad ; lq.xyzw vf01, 8(vi00)              ; load matrix M0
pad ; lq.xyzw vf02, 9(vi00)              ; M1
pad ; lq.xyzw vf03, 10(vi00)             ; M2
pad ; lq.xyzw vf04, 11(vi00)             ; M3
pad ; xgkick vi02                        ; kick initial GIF packet
pad ; iaddiu vi11, vi10, 32767           ; vi11 = vi10 + 0x7FFF
pad ; iaddiu vi11, vi11, 1               ; vi11 = vi10 + 0x8000
pad ; isw.x vi11, 0(vi02)                ; mem[vi02].x = vi11 (count)

sub_2818_loop:
pad ; lq.xyzw vf20, 0(vi03)              ; vf20 = *vi03 (input vertex)
mulax.xyzw  vf01, vf20 ; nop_swap        ; ACC = vf01 * vf20.x
madday.xyzw vf02, vf20 ; nop_swap
maddaz.xyzw vf03, vf20 ; nop_swap
maddw.xyzw  vf25, vf04, vf20 ; nop_swap  ; vf25 = ACC + vf04*vf20.w
pad ; div Q, vf00.w, vf25.w              ; Q = 1/vf25.w
mulq.xyzw   vf25, vf25 ; waitq           ; vf25 *= Q (perspective)
ftoi4.xyzw  vf26, vf25 ; nop_swap        ; vf26 = ftoi4(vf25)
pad ; sq.xyzw vf26, 1(vi07)
pad ; lq.xyzw vf20, 2(vi03)              ; vf20 = mem[vi03+2]
mulq.xyz    vf28, vf20 ; nop_swap        ; vf28 = vf20 * Q
pad ; sq.xyzw vf28, -1(vi07)
pad ; lq.xyzw vf27, 1(vi03)              ; vf27 = mem[vi03+1]
ftoi0.xyzw  vf29, vf27 ; nop_swap        ; vf29 = ftoi0(vf27)
pad ; sq.xyzw vf29, 0(vi07)
pad ; iaddiu vi07, vi07, 3
pad ; iaddiu vi03, vi03, 3
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_2818_loop
pad ; nop_swap                           ; (branch delay slot)
pad ; xgkick vi02                        ; kick transformed GIF packet
pad ; lq.xyzw vf01, 16(vi00)             ; reload matrix M0 from mem[16..19]
pad ; lq.xyzw vf02, 17(vi00)
pad ; lq.xyzw vf03, 18(vi00)
pad ; lq.xyzw vf04, 19(vi00)
pad ; nop_swap
pad ; jr vi01                            ; return to sub_2080 caller
pad ; nop_swap                           ; (delay slot)

; -----------------------------------------------------------------------
; L_2978 — VU0 register-bank save routine.
;
; Stores all 15 float registers vf17..vf31 (via sqd post-decrement
; into the vi14 stack), then packs all 14 int registers vi02..vi15
; into 4 quads via iswr (one lane per int).  Used as an interrupt
; save / context-switch primitive.  Caller saves vi14 (= "stack top")
; before calling; this routine returns via `jr vi15`.
; -----------------------------------------------------------------------
L_2978:
pad ; sqd.xyzw vf17, vi14
pad ; sqd.xyzw vf18, vi14
pad ; sqd.xyzw vf19, vi14
pad ; sqd.xyzw vf20, vi14
pad ; sqd.xyzw vf21, vi14
pad ; sqd.xyzw vf22, vi14
pad ; sqd.xyzw vf23, vi14
pad ; sqd.xyzw vf24, vi14
pad ; sqd.xyzw vf25, vi14
pad ; sqd.xyzw vf26, vi14
pad ; sqd.xyzw vf27, vi14
pad ; sqd.xyzw vf28, vi14
pad ; sqd.xyzw vf29, vi14
pad ; sqd.xyzw vf30, vi14
pad ; sqd.xyzw vf31, vi14
pad ; isubiu vi14, vi14, 1               ; vi14--
pad ; iswr.x vi02, vi14                  ; pack vi02..vi05 → quad
pad ; iswr.y vi03, vi14
pad ; iswr.z vi04, vi14
pad ; iswr.w vi05, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi06, vi14                  ; vi06..vi09 → quad
pad ; iswr.y vi07, vi14
pad ; iswr.z vi08, vi14
pad ; iswr.w vi09, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi10, vi14                  ; vi10..vi13 → quad
pad ; iswr.y vi11, vi14
pad ; iswr.z vi12, vi14
pad ; iswr.w vi13, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi14, vi14                  ; vi14, vi15 → quad (vi00/vi01 omitted)
pad ; iswr.y vi15, vi14
pad ; nop_swap
pad ; jr vi15
pad ; nop_swap

; -----------------------------------------------------------------------
; L_2A98 — VU0 register-bank restore routine.
;
; Reverses L_2978: unpacks 4 int-saving quads via ilwr (one lane per
; int), then lqi 15 floats back into vf17..vf31 (in reverse order:
; vf31 first since save order is reverse).  Caller pre-loads vi14
; to the bottom-of-stack slot; routine returns via `jr vi01`.
; -----------------------------------------------------------------------
L_2A98:
pad ; iadd vi01, vi00, vi15              ; vi01 = vi15 (save return target)
pad ; iswr.x vi14, vi14                  ; ?? (write-back vi14/vi15 first)
pad ; iswr.y vi15, vi14
pad ; iaddiu vi14, vi14, 1               ; vi14++
pad ; ilwr.x vi10, vi14                  ; unpack vi10..vi13 from quad
pad ; ilwr.y vi11, vi14
pad ; ilwr.z vi12, vi14
pad ; ilwr.w vi13, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi06, vi14                  ; vi06..vi09
pad ; ilwr.y vi07, vi14
pad ; ilwr.z vi08, vi14
pad ; ilwr.w vi09, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi02, vi14                  ; vi02..vi05
pad ; ilwr.y vi03, vi14
pad ; ilwr.z vi04, vi14
pad ; ilwr.w vi05, vi14
pad ; iaddiu vi14, vi14, 1
pad ; lqi.xyzw vf31, vi14                ; restore vf17..vf31 (reverse)
pad ; lqi.xyzw vf30, vi14
pad ; lqi.xyzw vf29, vi14
pad ; lqi.xyzw vf28, vi14
pad ; lqi.xyzw vf27, vi14
pad ; lqi.xyzw vf26, vi14
pad ; lqi.xyzw vf25, vi14
pad ; lqi.xyzw vf24, vi14
pad ; lqi.xyzw vf23, vi14
pad ; lqi.xyzw vf22, vi14
pad ; lqi.xyzw vf21, vi14
pad ; lqi.xyzw vf20, vi14
pad ; lqi.xyzw vf19, vi14
pad ; lqi.xyzw vf18, vi14
pad ; lqi.xyzw vf17, vi14
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_2BB0 — `jr vi01` return stub.  Reachable as a dispatch-table
; entry (TPC=0xE0 → b L_2BB0 in program 3's table) and as a fall-
; through from L_2A98's context-restore tail.
; -----------------------------------------------------------------------
sub_2BB0:
pad ; jr vi01
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_2BC0 — vertex-buffer init / clear.  Sets up vf17/vf31 to known
; values, loads working matrix from mem[20..23], and initializes
; vi14 = 256 (heap base).  Terminates via E-bit.
; -----------------------------------------------------------------------
L_2BC0:
sub.xyzw vf31, vf00, vf00 ; lq.xyzw vf17, 2(vi00)   ; vf31 = 0; vf17 = mem[2]
pad ; lq.xyzw vf13, 20(vi00)
pad ; lq.xyzw vf14, 21(vi00)
pad ; lq.xyzw vf15, 22(vi00)
pad ; lq.xyzw vf16, 23(vi00)
mulw.w vf17, vf00, vf00 ; iaddiu vi14, vi00, 256
pad ; move.z vf17, vf00                  ; vf17.z = 0
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)

; -----------------------------------------------------------------------
; sub_2C00 — bone-blended vertex transform with clip-flag culling.
;
; Reads vi01 (VIF top), masks count in vi10, output base vi02 = vi01
; + 192.  Per-vertex loop blends two bones (vf18/vf21/vf20 source +
; vf04/vf03 dest), perspective-divides, ftoi4-converts, and stores
; one of two output paths based on clip-flag testing via fcand /
; fcor against a sequence of magic bit-masks at 0x2DB0..0x2E30.
;
; The clip-mask sequence (0xFDF7DF, 0xFEFBEF, 0xFF7DF7, 0xFFBEFB,
; 0xFFDF7D, 0xFFEFBE) progressively excludes one clip plane per
; iteration; if any of them indicate a fully-visible vertex (ibne
; fires), control falls into the L_2E40 path which `bal vi15`s to
; the L_2978 save-context, L_2088 hierarchical-driver, and L_2A98
; restore-context routines in sequence (effectively recursing into
; the LOD subdivider for that vertex), then `b L_2D70` continues
; the per-vertex loop.  Otherwise (no fall-through), branches to
; L_2D70 directly.
;
; Output kick: `xgkick vi02` + `b L_2BC0` returns to the init stub's
; E-bit at 0x2BF8.
;
; Bundles 0x2CD8, 0x2CE0, 0x2CF0 are flag-bits-set FMACs (FD-dispatch
; .xyz variants) emitted via `.word`.
; -----------------------------------------------------------------------
sub_2C00:
pad ; nop_swap                           ; (entry — also E-bit delay slot of L_2BC0)
pad ; xtop vi01                          ; vi01 = VIF top
pad ; ilwr.x vi10, vi01                  ; vi10 = *(int*)vi01 (count)
pad ; iaddiu vi11, vi00, 32767           ; vi11 = 0x7FFF
pad ; iand vi10, vi10, vi11              ; vi10 &= 0x7FFF
pad ; iaddi vi11, vi11, 1                ; vi11 = 0x8000
pad ; lq.xyzw vf25, 0(vi01)              ; vf25 = mem[vi01] (header quad)
pad ; iaddiu vi03, vi01, 1               ; vi03 = vi01 + 1 (input cursor)
pad ; iaddiu vi02, vi01, 192             ; vi02 = vi01 + 192 (output base)
pad ; sq.xyzw vf25, 0(vi02)              ; store header
pad ; iaddiu vi07, vi02, 1               ; vi07 = vi02 + 1 (output cursor)
mulw.xyzw   vf22, vf00, vf00 ; iaddi vi04, vi00, -2    ; vf22 = 0; vi04 = -2
mulw.xyzw   vf23, vf00, vf00 ; iaddi vi05, vi00, -2    ; vf23 = 0; vi05 = -2
mulw.xyzw   vf24, vf00, vf00 ; iaddi vi06, vi00, -2    ; vf24 = 0; vi06 = -2
pad ; lq.xyzw vf18, 0(vi03)              ; preload vf18
pad ; lq.xyzw vf21, 1(vi03)              ; preload vf21
pad ; lq.xyzw vf20, 2(vi03)              ; preload vf20
pad ; nop_swap

L_2C90:
mulax.xyzw  vf01, vf18 ; move.xyzw vf22, vf23
madday.xyzw vf02, vf18 ; move.xyzw vf23, vf24
maddaz.xyzw vf03, vf18 ; iaddiu vi03, vi03, 3
maddw.xyzw  vf25, vf04, vf18 ; iaddi vi10, vi10, -1
sub.w       vf00, vf21, vf00 ; iadd vi04, vi00, vi05
mulax.xyzw  vf13, vf18 ; iadd vi05, vi00, vi06
madday.xyzw vf14, vf18 ; nop_swap
maddaz.xyzw vf15, vf18 ; div Q, vf00.w, vf25.w
maddw.xyzw  vf24, vf16, vf18 ; fsand vi08, 0x2
.word 0x01D6B1FF ; lq.xyzw vf18, 0(vi03)       ; upper: op6=0x3F .xyz fd=7 fs=22 ft=22
.word 0x01D7B9FF ; nop_swap                     ; upper: op6=0x3F .xyz fd=7 fs=23 ft=23
add.xyz     vf28, vf21, vf17 ; nop_swap
.word 0x01D8C1FF ; lq.xyzw vf21, 1(vi03)        ; upper: op6=0x3F .xyz fd=7 fs=24 ft=24
ftoi0.xyzw  vf29, vf20 ; nop_swap
mulq.xyzw   vf27, vf25 ; lq.xyzw vf20, 2(vi03)
mulq.xyz    vf28, vf28 ; nop_swap
pad ; fcand vi01, 0x3F                  ; vi01 = clip-flag bits 0..5
pad ; sq.xyzw vf29, 1(vi07)             ; store vf29
ftoi4.xyzw  vf27, vf27 ; ibeq vi08, vi00, L_2D48
pad ; iadd vi06, vi00, vi01             ; (delay slot) vi06 = clip bits
pad ; iaddi vi04, vi00, 1
pad ; iaddi vi05, vi00, 1
pad ; iaddi vi09, vi00, 2
L_2D48:
pad ; iadd vi01, vi04, vi05
pad ; iadd vi01, vi01, vi06
pad ; sq.xyzw vf28, 0(vi07)
pad ; ibgtz vi01, L_2DA0
pad ; sq.xyzw vf27, 2(vi07)             ; (delay slot)
L_2D70:
pad ; ibne vi10, vi00, L_2C90           ; loop while count != 0
pad ; iaddiu vi07, vi07, 3              ; (delay slot)
pad ; xgkick vi02                        ; kick GIF packet
pad ; nop_swap
pad ; b L_2BC0                           ; → sub_2BC0's E-bit
pad ; nop_swap                           ; (branch delay slot)
L_2DA0:
pad ; iaddi vi09, vi09, -1
pad ; ibgtz vi09, L_2E70
pad ; fcor vi01, 0xFDF7DF
pad ; ibne vi01, vi00, L_2E70
pad ; nop_swap
pad ; fcor vi01, 0xFEFBEF
pad ; ibne vi01, vi00, L_2E70
pad ; nop_swap
pad ; fcor vi01, 0xFF7DF7
pad ; ibne vi01, vi00, L_2E70
pad ; nop_swap
pad ; fcor vi01, 0xFFBEFB
pad ; ibne vi01, vi00, L_2E70
pad ; nop_swap
pad ; fcor vi01, 0xFFDF7D
pad ; ibne vi01, vi00, L_2E70
pad ; nop_swap
pad ; fcor vi01, 0xFFEFBE
pad ; ibne vi01, vi00, L_2E70
pad ; nop_swap
pad ; bal vi15, L_2978                   ; save context
pad ; nop_swap
pad ; bal vi15, L_2088                   ; call LOD hierarchical driver
pad ; nop_swap
pad ; bal vi15, L_2A98                   ; restore context
pad ; nop_swap
L_2E70:
pad ; b L_2D70                           ; back into the per-vertex loop
pad ; isw.w vi11, 2(vi07)                ; (delay slot — also stores vi11.w)

; =======================================================================
; FOURTH VU0 PROGRAM begins here.  Same multi-program concatenation
; pattern as the program-1/2/3 transitions.  FCSET imm this time is
; 0x1C8.  Followed by an entry-stub table at 0x2EA0..0x2FD8 and the
; program-4 routine bodies starting at L_2FE0.
; =======================================================================

; Program-4 control-flag prologue (parallels 0x0000..0x0008 / 0x0DB0
; / 0x17A0 in earlier programs).
nop ; .word 0x70000000                  ; 0x2E80 — lower op7=0x38
nop ; nop                               ; 0x2E88 — true-zero filler
nop ; .word 0x600001C8                  ; 0x2E90 — FCSET imm24=0x1C8
.word 0x4A000000 ; nop                  ; 0x2E98 — upper FMAC-family + true-zero

; Program-4 entry-stub dispatch.
pad ; b L_2FE0                          ; 0x2EA0 — entry → L_2FE0
pad ; nop_swap
pad ; b L_3068                          ; 0x2EB0 — entry → L_3068
pad ; nop_swap
pad ; nop_swap                          ; 0x2EC0 — reserved
pad ; nop_swap                          ; 0x2EC8 — reserved
pad ; nop_swap                          ; 0x2ED0 — reserved
pad ; nop_swap                          ; 0x2ED8 — reserved
pad ; b L_30A0                          ; 0x2EE0 — entry → L_30A0
pad ; nop_swap
pad ; b L_3110                          ; 0x2EF0 — entry → L_3110
pad ; nop_swap
pad ; b L_31E8                          ; 0x2F00 — entry → L_31E8
pad ; nop_swap
pad ; nop_swap                          ; 0x2F10 — reserved
pad ; nop_swap                          ; 0x2F18 — reserved
pad ; b L_3200                          ; 0x2F20 — entry → L_3200
pad ; nop_swap
pad ; b L_32E8                          ; 0x2F30 — entry → L_32E8
pad ; nop_swap
pad ; nop_swap                          ; 0x2F40 — reserved
pad ; nop_swap                          ; 0x2F48 — reserved
pad ; nop_swap                          ; 0x2F50 — reserved
pad ; nop_swap                          ; 0x2F58 — reserved
pad ; nop_swap                          ; 0x2F60 — reserved
pad ; nop_swap                          ; 0x2F68 — reserved
pad ; nop_swap                          ; 0x2F70 — reserved
pad ; nop_swap                          ; 0x2F78 — reserved
pad ; nop_swap                          ; 0x2F80 — reserved
pad ; nop_swap                          ; 0x2F88 — reserved
pad ; nop_swap                          ; 0x2F90 — reserved
pad ; nop_swap                          ; 0x2F98 — reserved
pad ; b L_3380                          ; 0x2FA0 — entry → L_3380
pad ; nop_swap
pad ; b L_3620                          ; 0x2FB0 — entry → L_3620  (far target)
pad ; nop_swap
pad ; b L_4770                          ; 0x2FC0 — entry → L_4770  (far target)
pad ; nop_swap
pad ; b L_38C0                          ; 0x2FD0 — entry → L_38C0  (far target)
pad ; nop_swap

; =======================================================================
; PROGRAM 4 SUBROUTINE BODIES.  Direct clones of program-1/2/3 routines
; at fresh VRAM offsets.
; =======================================================================

; sub_2FE0 — copy-with-count + xgkick + END (clone of sub_0EA0).
sub_2FE0:
pad ; xtop vi12
pad ; ilwr.x vi10, vi12
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; lqi.xyzw vf29, vi12
pad ; iaddiu vi13, vi00, 32767
pad ; iand vi10, vi13, vi10
pad ; sqi.xyzw vf29, vi09
sub_2FE0_loop:
pad ; lqi.xyzw vf28, vi12
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_2FE0_loop
pad ; sqi.xyzw vf28, vi09                ; (branch delay slot)
pad ; nop_swap
pad ; xgkick vi07
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_3068 — mem[2].xy patch (clone of sub_0F28).
sub_3068:
pad ; xtop vi01
pad ; lq.xyzw vf30, 2(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; move.xy vf30, vf31
pad ; sq.xyzw vf30, 2(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_30A0 — 4-quad matrix upload to mem[256] (clone of sub_0F60).
sub_30A0:
pad ; xtop vi12
pad ; iaddiu vi13, vi00, 256
pad ; lqi.xyzw vf18, vi12
pad ; lqi.xyzw vf19, vi12
pad ; lqi.xyzw vf16, vi12
pad ; lqi.xyzw vf17, vi12
pad ; sqi.xyzw vf18, vi13
pad ; sqi.xyzw vf19, vi13
pad ; sqi.xyzw vf16, vi13
pad ; sqi.xyzw vf17, vi13
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; exit_3100 — shared E-bit stub (clone of exit_0FC0).
exit_3100:
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_3110 — palette-indexed vertex transform (clone of sub_0FD0);
; falls through into sub_31E8 for terminator.
sub_3110:
pad ; xtop vi12
pad ; iaddiu vi11, vi12, 1
pad ; ilwr.x vi10, vi12
pad ; lq.xyzw vf29, 0(vi12)
pad ; iaddiu vi13, vi00, 32767
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; sqi.xyzw vf29, vi09
pad ; iand vi10, vi13, vi10
pad ; iaddiu vi13, vi00, 1
pad ; lq.xyzw vf09, 0(vi11)
pad ; ilwr.w vi14, vi11
pad ; nop_swap
pad ; iand vi15, vi13, vi14

sub_3110_loop:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)
pad ; move.w vf09, vf00
pad ; iaddiu vi11, vi11, 1
pad ; ilwr.w vi14, vi11
pad ; iaddi vi10, vi10, -1
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09
pad ; lq.xyzw vf09, 0(vi11)
pad ; iand vi15, vi13, vi14
pad ; ibne vi10, vi00, sub_3110_loop
pad ; sqi.xyzw vf10, vi09                ; (branch delay slot)

pad ; nop_swap
pad ; xgkick vi07
pad ; nop_swap                           ; falls through into sub_31E8

; sub_31E8 — final palette-step + `b exit_3100` (clone of sub_10A8).
sub_31E8:
add.xy vf16, vf16, vf17 ; nop_swap
pad ; b exit_3100
pad ; nop_swap                           ; (branch delay slot)

; sub_3200 — bulk 13-quad upload to mem[16..27] + mem[3]→mem[37]
; (clone of sub_1B10).
sub_3200:
pad ; xtop vi01
pad ; lqi.xyzw vf01, vi01
pad ; sq.xyzw vf01, 16(vi00)
pad ; lqi.xyzw vf02, vi01
pad ; sq.xyzw vf02, 17(vi00)
pad ; lqi.xyzw vf03, vi01
pad ; sq.xyzw vf03, 18(vi00)
pad ; lqi.xyzw vf04, vi01
pad ; sq.xyzw vf04, 19(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 20(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 21(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 22(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 23(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 24(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 25(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 26(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 27(vi00)
pad ; lq.xyzw vf31, 3(vi00)
pad ; sq.xyzw vf31, 37(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_32E8 — bulk 8-quad upload via vf31 to mem[28..35] (clone of sub_1BF8).
sub_32E8:
pad ; xtop vi01
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 28(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 29(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 30(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 31(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 32(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 33(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 34(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 35(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_3380 — I-register setup with extended bulk load (variant of sub_1C90
; with 8 additional lq from mem[28..35] into vf05..vf12).
sub_3380:
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE
addi.w vf14, vf00 ; move.xyzw vf13, vf00
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000
addi.xy vf14, vf00 ; nop_swap
pad ; lq.xyzw vf23, 2(vi00)
pad ; lq.xyzw vf05, 28(vi00)
pad ; lq.xyzw vf06, 29(vi00)
pad ; lq.xyzw vf07, 30(vi00)
pad ; lq.xyzw vf08, 31(vi00)
pad ; lq.xyzw vf09, 32(vi00)
pad ; lq.xyzw vf10, 33(vi00)
pad ; lq.xyzw vf11, 34(vi00)
pad ; lq.xyzw vf12, 35(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot
pad ; xtop vi13

; --- sub_3380 transform body (0x3400..0x3618) ---
; Reached directly when EE sets VU0_TPC=0x3400.  Loop tail branches
; `b L_3380` to re-enter sub_3380's I-imm setup tail, which then hits
; the E-bit at 0x33E8 to terminate.  Same exit-via-branch-into-tail
; pattern as sub_1EA0 / sub_1C90 in program 3.
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddi vi03, vi01, -2               ; vi03 = vi01 - 2 (note: -2, not +1)
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; iaddiu vi07, vi00, 208
sub.w       vf21, vf21, vf21 ; lq.xyzw vf16, 1(vi02)
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; lq.xyzw vf18, 3(vi02)
mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
sub.w       vf00, vf17, vf00 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
maddaz.xyzw vf03, vf15 ; fsand vi15, 0x2
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
add.xy      vf17, vf17, vf23 ; nop_swap
pad ; nop_swap
mulax.xyzw  vf09, vf29 ; nop_swap
madday.xyzw vf10, vf29 ; div Q, vf00.w, vf28.w

L_34F0:
maddaz.xyzw vf11, vf29 ; iaddiu vi02, vi02, 4
maddw.xyzw  vf29, vf12, vf29 ; ibeq vi15, vi00, L_3510
pad ; lq.xyzw vf16, 1(vi02)
pad ; iaddiu vi05, vi00, 3
L_3510:
mulq.xyz    vf28, vf28 ; waitq
mulq.xyz    vf21, vf17 ; lq.xyzw vf15, 0(vi02)
maxx.xyzw   vf29, vf29, vf00 ; lq.xyzw vf17, 2(vi02)
mulax.xyzw  vf05, vf16 ; iaddi vi04, vi04, -1
sub.xyw     vf00, vf13, vf28 ; iaddiu vi03, vi03, 3
sub.xyw     vf00, vf28, vf14 ; sq.xyzw vf21, 0(vi03)
; I-bit bundle: upper mul.xyz vf18,vf18,vf29 + I-bit; lower = 255.0f → I
.word 0x81DD94AA ; .word 0x437F0000
madday.xyzw vf06, vf16 ; move.xyzw vf30, vf28
maddaz.xyzw vf07, vf16 ; fmand vi14, vi07
maddw.xyzw  vf29, vf08, vf16 ; fmand vi14, vi14
minii.xyzw  vf22, vf18 ; iaddi vi05, vi05, -1
mulax.xyzw  vf01, vf15 ; lq.xyzw vf18, 3(vi02)
sub.w       vf00, vf17, vf00 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
ftoi0.xyzw  vf22, vf22 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; fsand vi15, 0x2
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
ftoi4.xyz   vf20, vf30 ; sq.xyzw vf22, 1(vi03)
ftoi4.xyz   vf19, vf30 ; ibne vi14, vi07, L_35F0
add.xy      vf17, vf17, vf23 ; div Q, vf00.w, vf28.w
pad ; ibgtz vi05, L_35F8
pad ; nop_swap
mulax.xyzw  vf09, vf29 ; ibne vi04, vi00, L_34F0
madday.xyzw vf10, vf29 ; sq.xyzw vf19, 2(vi03)
pad ; xgkick vi01
pad ; b L_3380                           ; → sub_3380's E-bit
pad ; nop_swap                           ; (branch delay slot)
L_35F0:
pad ; iaddiu vi05, vi00, 3
L_35F8:
mulax.xyzw  vf09, vf29 ; ibne vi04, vi00, L_34F0
madday.xyzw vf10, vf29 ; sq.xyzw vf20, 2(vi03)
pad ; xgkick vi01
pad ; b L_3380                           ; → sub_3380's E-bit
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_3620 — I-register setup (clone of sub_3380's I-imm prologue).
; Transform body extends past 0x3690 (deferred to next batch).
; -----------------------------------------------------------------------
sub_3620:
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE
L_3628:
addi.w vf14, vf00 ; move.xyzw vf13, vf00
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000
addi.xy vf14, vf00 ; nop_swap
pad ; lq.xyzw vf23, 2(vi00)
pad ; lq.xyzw vf05, 28(vi00)
pad ; lq.xyzw vf06, 29(vi00)
pad ; lq.xyzw vf07, 30(vi00)
pad ; lq.xyzw vf08, 31(vi00)
pad ; lq.xyzw vf09, 32(vi00)
pad ; lq.xyzw vf10, 33(vi00)
pad ; lq.xyzw vf11, 34(vi00)
pad ; lq.xyzw vf12, 35(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; --- sub_3620 transform body (0x3698..0x38B8) ---
; Reached directly when EE sets VU0_TPC=0x3698.  Loop tail `b L_3628`
; re-enters sub_3620's I-setup-tail at 0x3628 (the addi.w bundle),
; which then falls through to the E-bit at 0x3688 and terminates.
; This routine adds a specular-power chain (mul.xyz vf30 squared
; twice) before quantizing, and has the I-bit 255.0f trick at 0x3810.
pad ; xtop vi13
.word 0x4A000100 ; nop                   ; upper: `add vf04, vf00, vf00` + flag bits (E/T/25-ish)
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; iaddiu vi07, vi00, 208
sub.w       vf21, vf21, vf21 ; lq.xyzw vf16, 1(vi02)
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; lq.xyzw vf18, 3(vi02)
mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
sub.w       vf00, vf17, vf00 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; fsand vi15, 0x2
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
add.xy      vf17, vf17, vf23 ; nop_swap
pad ; nop_swap

L_3788:
mulax.xyzw  vf09, vf29 ; div Q, vf00.w, vf28.w
madday.xyzw vf10, vf29 ; iaddiu vi02, vi02, 4
maddaz.xyzw vf11, vf29 ; ibeq vi15, vi00, L_37B0
maddw.xyzw  vf29, vf00, vf29 ; lq.xyzw vf16, 1(vi02)
pad ; iaddiu vi05, vi00, 3
L_37B0:
maxx.xyzw   vf29, vf29, vf00 ; waitq
mulq.xyz    vf28, vf28 ; nop_swap
mulq.xyz    vf21, vf17 ; lq.xyzw vf15, 0(vi02)
mulax.xyzw  vf05, vf16 ; lq.xyzw vf17, 2(vi02)
mul.xyz     vf30, vf29, vf29 ; iaddi vi04, vi04, -1
sub.xyw     vf00, vf13, vf28 ; nop_swap
sub.xyw     vf00, vf28, vf14 ; sq.xyzw vf21, 0(vi03)
madday.xyzw vf06, vf16 ; nop_swap
mul.xyz     vf30, vf30, vf30 ; nop_swap
maddaz.xyzw vf07, vf16 ; fmand vi14, vi07
maddw.xyzw  vf29, vf08, vf16 ; fmand vi14, vi14
sub.w       vf00, vf17, vf00 ; nop_swap
; I-bit bundle: upper mul.xyz vf18,vf18,vf30 + I-bit; lower = 255.0f → I
.word 0x81DE94AA ; .word 0x437F0000
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; fsand vi15, 0x2
minii.xyzw  vf22, vf18 ; nop_swap
ftoi4.xyz   vf19, vf28 ; iaddi vi05, vi05, -1
ftoi4.xyz   vf20, vf28 ; lq.xyzw vf18, 3(vi02)
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
ftoi0.xyzw  vf22, vf22 ; nop_swap
maxx.xyzw   vf29, vf29, vf00 ; ibne vi14, vi07, L_3890
add.xy      vf17, vf17, vf23 ; iaddiu vi03, vi03, 3
pad ; ibgtz vi05, L_3898
pad ; nop_swap
pad ; sq.xyzw vf19, -1(vi03)
pad ; b L_38A0
pad ; nop_swap
L_3890:
pad ; iaddiu vi05, vi00, 3
L_3898:
pad ; sq.xyzw vf20, -1(vi03)
L_38A0:
pad ; ibne vi04, vi00, L_3788
pad ; sq.xyzw vf22, -2(vi03)
pad ; xgkick vi01
pad ; b L_3628                           ; → sub_3620's E-bit

; -----------------------------------------------------------------------
; sub_38C0 — 1-bundle no-op entry (also delay slot of `b L_3628` above).
; Falls through into sub_38C8's I-register setup.
; -----------------------------------------------------------------------
sub_38C0:
pad ; nop_swap                           ; do nothing (entry / branch delay slot)
L_38C8:
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE
addi.w vf14, vf00 ; move.xyzw vf13, vf00
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000
addi.xy vf14, vf00 ; nop_swap
pad ; lq.xyzw vf23, 2(vi00)
pad ; lq.xyzw vf05, 24(vi00)
pad ; lq.xyzw vf06, 25(vi00)
pad ; lq.xyzw vf07, 26(vi00)
pad ; lq.xyzw vf08, 27(vi00)
pad ; lq.xyzw vf09, 12(vi00)
pad ; lq.xyzw vf10, 13(vi00)
pad ; lq.xyzw vf11, 14(vi00)
pad ; lq.xyzw vf12, 15(vi00)
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_3940 — full skinned vertex transform with rsqrt + per-vertex
; rotational refinement.  Largest single routine in the blob so far.
;
; Reached via VU0_TPC=0x3940 (entry from sub_38C0 path) OR directly.
; Loop tail `b L_38C8` returns to the I-imm setup tail, which then
; falls through to E-bit at 0x3930 to terminate.
;
; Distinctive features vs earlier transform routines:
;   - rsqrt Q computation for unit-vector normalization at 0x3A60.
;   - mulax.w/madday.w/maddz.w accumulator-form chains feeding a
;     squared-distance computation (vf27 = |vf29|²).
;   - mulaw.xyz/maddaw.xyz/maddw.xyz vf30 chain — a tri-add producing
;     a refined position vf30 from vf27 scaled by vf29.
;   - rinit R / rget.xyzw vf25 — captures the VU0 R-register state
;     (a hardware random-number lane).
;   - Two LOI immediate bundles at 0x3BA8 (= 0.125f) and 0x3BB0
;     (= 0.25f) carrying float constants in the lower-half opcode
;     position; the upper FMAC of those bundles is unaffected (no
;     I-bit) but the next-iter `mulai.xy` / `maddi.xy` consume the
;     last-loaded I value.
;   - Front-face / back-face / refined-position 3-way output store
;     (sq vf19 / vf20 / vf21 at -1(vi03), -1(vi03), -3(vi03)).
; -----------------------------------------------------------------------
sub_3940:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddi vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
sub.w       vf21, vf21, vf21 ; iaddiu vi07, vi00, 208
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf16, 1(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; lq.xyzw vf18, 3(vi02)

mulax.xyzw  vf05, vf15 ; nop_swap
madday.xyzw vf06, vf15 ; nop_swap
maddaz.xyzw vf07, vf15 ; nop_swap
maddw.xyzw  vf29, vf08, vf00 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
mul.xyz     vf27, vf29, vf29 ; nop_swap                 ; vf27 = vf29² (squared lights)
mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf30, vf00, vf16 ; nop_swap

L_3A30:
mulax.w     vf00, vf27 ; div Q, vf00.w, vf28.w          ; sum-of-squares init
madday.w    vf00, vf27 ; iaddiu vi02, vi02, 4
maddz.w     vf27, vf00, vf27 ; iaddi vi04, vi04, -1     ; vf27.w = sum-of-squared-lanes
ftoi0.xyzw  vf22, vf18 ; nop_swap
sub.w       vf00, vf17, vf00 ; nop_swap
addq.x      vf31, vf00 ; waitq                          ; vf31.x = vf00.x + Q
pad ; rsqrt Q, vf00.w, vf27.w                            ; Q = 1/sqrt(|vf29|²)
pad ; sq.xyzw vf22, 1(vi03)
pad ; fsand vi15, 0x2
pad ; ibeq vi15, vi00, L_3A90
pad ; nop_swap
pad ; iaddiu vi05, vi00, 3
L_3A90:
mulq.xyz    vf29, vf29 ; waitq                          ; vf29 = vf29 * Q (unit-length normalize)
mulx.xyz    vf28, vf28, vf31 ; nop_swap                 ; vf28.xyz *= vf31.x
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf16, 1(vi02)
mul.xyz     vf27, vf29, vf30 ; lq.xyzw vf18, 3(vi02)
sub.xyw     vf00, vf28, vf14 ; lq.xyzw vf17, 2(vi02)
sub.xyw     vf00, vf13, vf28 ; iaddi vi05, vi05, -1
ftoi4.xyz   vf19, vf28 ; nop_swap
mulax.w     vf00, vf27 ; nop_swap
madday.w    vf00, vf27 ; fmand vi14, vi07
maddz.w     vf27, vf00, vf27 ; fmand vi14, vi14
ftoi4.xyz   vf20, vf28 ; nop_swap
pad ; nop_swap
pad ; nop_swap
mulaw.xyz   vf30, vf27 ; nop_swap                       ; ACC = vf30 + ?
maddaw.xyz  vf30, vf27 ; nop_swap
maddw.xyz   vf30, vf29, vf27 ; nop_swap                 ; vf30 += vf29*vf27.w
mulax.xyzw  vf05, vf15 ; nop_swap
madday.xyzw vf06, vf15 ; nop_swap
maddaz.xyzw vf07, vf15 ; nop_swap
maddw.xyzw  vf29, vf08, vf00 ; nop_swap
mulax.xyzw  vf09, vf30 ; nop_swap
madday.xyzw vf10, vf30 ; nop_swap
maddaz.xyzw vf11, vf30 ; nop_swap
maddw.xyzw  vf26, vf00, vf00 ; nop_swap                 ; vf26 = ?
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
add.z       vf26, vf26, vf26 ; rinit R, vf00.w          ; R = vf00.w (sequence reset)
maddw.xyzw  vf28, vf04, vf00 ; rget.xyzw vf25           ; vf25 = R (sequence sample)
mul.xyz     vf27, vf29, vf29 ; nop_swap
mulax.xyzw  vf05, vf16 ; nop_swap
addz.xy     vf26, vf26, vf26 ; nop_swap
madday.xyzw vf06, vf16 ; mr32.z vf26, vf00              ; vf26.z = ?
maddaz.xyzw vf07, vf16 ; nop_swap
; LOI bundles: upper has I-bit set (bit 31); lower is the 32-bit
; float immediate loaded into the VU0 I-register.  The upper FMAC
; still executes normally; the I-load happens in parallel.
.word 0x81F0078B ; .word 0x3E000000        ; maddw.xyzw vf30,vf00,vf16 [I-bit]; I = 0.125f
.word 0x8180D1FE ; .word 0x3E800000        ; mulai.xy vf26 [I-bit];           I = 0.25f
maddi.xy    vf26, vf25 ; nop_swap                       ; vf26.xy += vf25 * I
pad ; nop_swap
pad ; nop_swap
pad ; ibne vi14, vi07, L_3C08
mulx.xyz    vf21, vf26, vf31 ; iaddiu vi03, vi03, 3     ; vf21.xyz = vf26 * vf31.x
pad ; ibgtz vi05, L_3C10
pad ; nop_swap
pad ; sq.xyzw vf19, -1(vi03)
pad ; b L_3C18
pad ; nop_swap
L_3C08:
pad ; iaddiu vi05, vi00, 3
L_3C10:
pad ; sq.xyzw vf20, -1(vi03)
L_3C18:
pad ; ibne vi04, vi00, L_3A30
pad ; sq.xyzw vf21, -3(vi03)                            ; (delay slot — also stores refined vf21)
pad ; xgkick vi01
pad ; b L_38C8                           ; → sub_38C8's I-setup tail/E-bit
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_3C40 — hierarchical LOD mesh subdivision driver (program-4 clone
; of sub_2080).  Same 6-tier dispatch structure as program-1's
; sub_2080, with refreshed targets:
;   L_4188 / L_4148 / L_4138 (jr vi15) / L_4308 (refinement) /
;   L_4368 (perspective-divide cont) / L_43E0 (save-context output).
; Two extra "landing slot" labels L_4130/4140/4180 sit one bundle
; before their respective subroutine entries (L_4138 / L_4148 /
; L_4188) so some callers can branch into the same routine one
; bundle later (skipping a leading nop_swap).
;
; sub_3C40's setup phase loads vf22/vf23/vf24 from mem[8/9/3/6]
; offsets and from vi03-relative stream, applies vf17 .xy fixups,
; itof0-casts integer fields to float, then runs the 6 LOD tiers.
; -----------------------------------------------------------------------
sub_3C40:
pad ; iaddiu vi08, vi00, 104
pad ; sq.xyzw vf22, 0(vi08)
L_3C50:
pad ; sq.xyzw vf22, 9(vi08)
pad ; sq.xyzw vf23, 3(vi08)
pad ; iaddiu vi09, vi00, 164
pad ; sq.xyzw vf24, 6(vi08)
pad ; lq.xyzw vf22, -10(vi03)
add.xy vf22, vf22, vf17 ; lq.xyzw vf23, -6(vi03)
add.xy vf23, vf23, vf17 ; lq.xyzw vf24, -2(vi03)
add.xy vf24, vf24, vf17 ; nop_swap
pad ; sq.xyzw vf22, 2(vi08)
pad ; sq.xyzw vf22, 11(vi08)
pad ; sq.xyzw vf23, 5(vi08)
pad ; sq.xyzw vf24, 8(vi08)
pad ; lq.xyzw vf22, -5(vi07)
itof0.xyzw vf22, vf22 ; lq.xyzw vf23, -2(vi07)
itof0.xyzw vf23, vf23 ; lq.xyzw vf24, 1(vi07)
itof0.xyzw vf24, vf24 ; nop_swap
pad ; sq.xyzw vf22, 1(vi08)
pad ; sq.xyzw vf22, 10(vi08)
pad ; sq.xyzw vf23, 4(vi08)
pad ; sq.xyzw vf24, 7(vi08)

; --- LOD tier 1 ---
pad ; iaddiu vi05, vi00, 2048
pad ; iaddiu vi06, vi00, 32
pad ; iaddiu vi07, vi00, 2
pad ; iaddiu vi10, vi00, 3
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_3D30:
pad ; bal vi02, L_4180
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_3D30
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_4140
pad ; nop_swap
.word 0x100002FF ; nop_swap              ; pad with M-bit flag
pad ; ibeq vi11, vi00, L_4130
pad ; nop_swap

; --- LOD tier 2 ---
pad ; iaddiu vi05, vi00, 1024
pad ; iaddiu vi06, vi00, 16
pad ; iaddiu vi07, vi00, 2
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_3DE8:
pad ; bal vi02, L_4180
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_3DE8
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_4140
pad ; nop_swap
pad ; ibeq vi11, vi00, L_4130
pad ; nop_swap

; --- LOD tier 3 ---
pad ; iaddiu vi05, vi00, 128
pad ; iaddiu vi06, vi00, 2
pad ; iaddiu vi07, vi00, 0
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
pad ; bal vi02, L_4180
L_3EA0:
pad ; nop_swap
.word 0x4A000200 ; nop                   ; upper: `add vf08, vf00, vf00` + flag bits
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_3EA0
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_4148
pad ; nop_swap
pad ; ibeq vi11, vi00, L_4138
pad ; nop_swap

; --- LOD tier 4 ---
pad ; iaddiu vi05, vi00, 64
pad ; iaddiu vi06, vi00, 1
pad ; iaddiu vi07, vi00, 0
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_3F50:
pad ; bal vi02, L_4188
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_3F50
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_4148
pad ; nop_swap
pad ; ibeq vi11, vi00, L_4138
pad ; nop_swap

; --- LOD tier 5 ---
pad ; iaddiu vi05, vi00, 512
pad ; iaddiu vi06, vi00, 8
pad ; iaddiu vi07, vi00, 1
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_4000:
pad ; bal vi02, L_4188
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_4000
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_4148
pad ; nop_swap
pad ; ibeq vi11, vi00, L_4138
pad ; nop_swap

; --- LOD tier 6 ---
pad ; iaddiu vi05, vi00, 256
pad ; iaddiu vi06, vi00, 4
pad ; iaddiu vi07, vi00, 1
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_40B0:
pad ; bal vi02, L_4188
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_40B0
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_4148
pad ; nop_swap
pad ; ibeq vi11, vi00, L_4138
pad ; nop_swap

; --- Final consolidation block: call save-context output at L_43E0 ---
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
pad ; bal vi01, L_43E0
L_4130:
pad ; nop_swap                           ; branch-landing slot before L_4138
L_4138:
pad ; jr vi15                            ; shared early-out return
L_4140:
pad ; nop_swap                           ; branch-landing slot before L_4148
L_4148:
pad ; lq.xyzw vf21, 0(vi08)
pad ; lq.xyzw vf22, 1(vi08)
pad ; lq.xyzw vf23, 2(vi08)
pad ; sqi.xyzw vf21, vi09
pad ; sqi.xyzw vf22, vi09
pad ; sqi.xyzw vf23, vi09
pad ; jr vi02
L_4180:
pad ; nop_swap                           ; branch-landing slot before L_4188
L_4188:
add.xyzw vf17, vf31, vf21 ; lqi.xyzw vf21, vi08
add.xyzw vf18, vf31, vf22 ; lqi.xyzw vf22, vi08
add.xyzw vf19, vf31, vf23 ; lqi.xyzw vf23, vi08
.word 0x01D189FF ; nop_swap              ; FD-dispatch FMAC variant
.word 0x01D5A9FF ; nop_swap
pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
pad ; fcget vi01
pad ; iand vi04, vi01, vi05
pad ; nop_swap
pad ; ibeq vi04, vi00, L_4260
pad ; nop_swap
pad ; iand vi04, vi01, vi06
pad ; nop_swap
pad ; ibeq vi04, vi00, L_4220
pad ; nop_swap
pad ; b L_42F8
pad ; nop_swap
L_4220:
pad ; bal vi01, L_4308
pad ; nop_swap
pad ; sqi.xyzw vf25, vi09
pad ; sqi.xyzw vf26, vi09
pad ; sqi.xyzw vf27, vi09
pad ; iaddiu vi11, vi11, 1
pad ; b L_42F8
pad ; nop_swap
L_4260:
pad ; iand vi04, vi01, vi06
pad ; nop_swap
pad ; ibeq vi04, vi00, L_42D8
pad ; nop_swap
pad ; bal vi01, L_4308
pad ; nop_swap
pad ; sqi.xyzw vf17, vi09
pad ; sqi.xyzw vf18, vi09
pad ; sqi.xyzw vf19, vi09
pad ; sqi.xyzw vf25, vi09
pad ; sqi.xyzw vf26, vi09
pad ; sqi.xyzw vf27, vi09
pad ; iaddiu vi11, vi11, 2
pad ; b L_42F8
pad ; nop_swap
L_42D8:
pad ; sqi.xyzw vf17, vi09
pad ; sqi.xyzw vf18, vi09
pad ; sqi.xyzw vf19, vi09
pad ; iaddiu vi11, vi11, 1
L_42F8:
pad ; jr vi02
pad ; nop_swap
L_4308:
mulx.w vf25, vf17, vf30 ; iadd vi12, vi00, vi07
mulx.w vf26, vf21, vf30 ; nop_swap
subw.xyzw vf25, vf17, vf25 ; nop_swap
subw.xyzw vf26, vf21, vf26 ; nop_swap
pad ; nop_swap
L_4330:
pad ; ibeq vi12, vi00, L_4368
pad ; nop_swap
pad ; mr32.xyzw vf25, vf25
pad ; mr32.xyzw vf26, vf26
pad ; isubiu vi12, vi12, 1
pad ; b L_4330
pad ; nop_swap
L_4368:
sub.xyz vf27, vf26, vf25 ; nop_swap
pad ; div Q, vf25.x, vf27.x
addq.x vf29, vf00 ; waitq
abs.x vf29, vf29 ; nop_swap
sub.xyzw vf25, vf21, vf17 ; nop_swap
sub.xyzw vf26, vf22, vf18 ; nop_swap
sub.xyzw vf27, vf23, vf19 ; nop_swap
mulx.xyzw vf25, vf25, vf29 ; nop_swap
mulx.xyzw vf26, vf26, vf29 ; nop_swap
mulx.xyzw vf27, vf27, vf29 ; nop_swap
add.xyzw vf25, vf25, vf17 ; nop_swap
add.xyzw vf26, vf26, vf18 ; nop_swap
add.xyzw vf27, vf27, vf19 ; nop_swap
pad ; jr vi01
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_43E0 — program-4 clone of sub_2818 (save-context vertex output).
; Two-stage GIF kick with matrix reload from mem[16..19].
; -----------------------------------------------------------------------
sub_43E0:
pad ; iaddiu vi02, vi00, 37
pad ; iadd vi03, vi00, vi08
pad ; iaddiu vi07, vi02, 2
pad ; iaddiu vi11, vi00, 32767
pad ; iaddiu vi11, vi11, 1
pad ; isw.x vi11, 0(vi02)
pad ; lq.xyzw vf01, 8(vi00)
pad ; lq.xyzw vf02, 9(vi00)
pad ; lq.xyzw vf03, 10(vi00)
pad ; lq.xyzw vf04, 11(vi00)
pad ; xgkick vi02
pad ; iaddiu vi11, vi10, 32767
pad ; iaddiu vi11, vi11, 1
pad ; isw.x vi11, 0(vi02)

sub_43E0_loop:
pad ; lq.xyzw vf20, 0(vi03)
mulax.xyzw  vf01, vf20 ; nop_swap
madday.xyzw vf02, vf20 ; nop_swap
maddaz.xyzw vf03, vf20 ; nop_swap
maddw.xyzw  vf25, vf04, vf20 ; nop_swap
pad ; div Q, vf00.w, vf25.w
mulq.xyzw   vf25, vf25 ; waitq
ftoi4.xyzw  vf26, vf25 ; nop_swap
pad ; sq.xyzw vf26, 1(vi07)
pad ; lq.xyzw vf20, 2(vi03)
mulq.xyz    vf28, vf20 ; nop_swap
pad ; sq.xyzw vf28, -1(vi07)
pad ; lq.xyzw vf27, 1(vi03)
ftoi0.xyzw  vf29, vf27 ; nop_swap
pad ; sq.xyzw vf29, 0(vi07)
pad ; iaddiu vi07, vi07, 3
pad ; iaddiu vi03, vi03, 3
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_43E0_loop
pad ; nop_swap
pad ; xgkick vi02
pad ; lq.xyzw vf01, 16(vi00)
pad ; lq.xyzw vf02, 17(vi00)
pad ; lq.xyzw vf03, 18(vi00)
pad ; lq.xyzw vf04, 19(vi00)
pad ; nop_swap
pad ; jr vi01
pad ; nop_swap
pad ; sqd.xyzw vf17, vi14                ; entry of L_4538/L_4540 save-context

; -----------------------------------------------------------------------
; L_4540 — VU0 register-bank save (program-4 clone of L_2978).
; sqd 15 floats + iswr 14 ints; `jr vi15` returns.
; -----------------------------------------------------------------------
L_4540:
pad ; sqd.xyzw vf18, vi14
pad ; sqd.xyzw vf19, vi14
pad ; sqd.xyzw vf20, vi14
pad ; sqd.xyzw vf21, vi14
pad ; sqd.xyzw vf22, vi14
pad ; sqd.xyzw vf23, vi14
pad ; sqd.xyzw vf24, vi14
pad ; sqd.xyzw vf25, vi14
pad ; sqd.xyzw vf26, vi14
pad ; sqd.xyzw vf27, vi14
pad ; sqd.xyzw vf28, vi14
pad ; sqd.xyzw vf29, vi14
pad ; sqd.xyzw vf30, vi14
pad ; sqd.xyzw vf31, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi02, vi14
pad ; iswr.y vi03, vi14
pad ; iswr.z vi04, vi14
pad ; iswr.w vi05, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi06, vi14
pad ; iswr.y vi07, vi14
pad ; iswr.z vi08, vi14
pad ; iswr.w vi09, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi10, vi14
pad ; iswr.y vi11, vi14
pad ; iswr.z vi12, vi14
pad ; iswr.w vi13, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi14, vi14
pad ; iswr.y vi15, vi14
pad ; nop_swap
pad ; jr vi15
pad ; nop_swap

; -----------------------------------------------------------------------
; L_4660 — VU0 register-bank restore (program-4 clone of L_2A98).
; Flag-bits-set FMAC at 0x46B0 (`.word 0x4A8D0300`) — `add.y vf12,
; vf00, vf13` with E/T/extra flag bits, emitted as `.word`.
; -----------------------------------------------------------------------
pad ; iadd vi01, vi00, vi15                ; (0x4658 — pre-L_4660 setup bundle)
L_4660:
pad ; iswr.x vi14, vi14
pad ; iswr.y vi15, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi10, vi14
pad ; ilwr.y vi11, vi14
pad ; ilwr.z vi12, vi14
pad ; ilwr.w vi13, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi06, vi14
pad ; ilwr.y vi07, vi14
.word 0x4A8D0300 ; nop                   ; upper: `add.y vf12, vf00, vf13` + flag bits
pad ; ilwr.z vi08, vi14
pad ; ilwr.w vi09, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi02, vi14
pad ; ilwr.y vi03, vi14
pad ; ilwr.z vi04, vi14
pad ; ilwr.w vi05, vi14
pad ; iaddiu vi14, vi14, 1
pad ; lqi.xyzw vf31, vi14
pad ; lqi.xyzw vf30, vi14
pad ; lqi.xyzw vf29, vi14
pad ; lqi.xyzw vf28, vi14
pad ; lqi.xyzw vf27, vi14
pad ; lqi.xyzw vf26, vi14
pad ; lqi.xyzw vf25, vi14
pad ; lqi.xyzw vf24, vi14
pad ; lqi.xyzw vf23, vi14
pad ; lqi.xyzw vf22, vi14
pad ; lqi.xyzw vf21, vi14
pad ; lqi.xyzw vf20, vi14
pad ; lqi.xyzw vf19, vi14
pad ; lqi.xyzw vf18, vi14
pad ; lqi.xyzw vf17, vi14
L_4770:
pad ; nop_swap                           ; `jr vi01` return stub
pad ; jr vi01
pad ; nop_swap

; -----------------------------------------------------------------------
; L_4788 — vertex-buffer init (program-4 clone of L_2BC0).
; Loads scratch matrix vf13..vf16 from mem[20..23], extended bulk
; load vf05..vf12 from mem[28..35] / mem[32..35].  Sets vi14 = 256.
; -----------------------------------------------------------------------
L_4788:
sub.xyzw vf31, vf00, vf00 ; lq.xyzw vf17, 2(vi00)
pad ; lq.xyzw vf13, 20(vi00)
pad ; lq.xyzw vf14, 21(vi00)
pad ; lq.xyzw vf15, 22(vi00)
pad ; lq.xyzw vf16, 23(vi00)
pad ; lq.xyzw vf05, 28(vi00)
pad ; lq.xyzw vf06, 29(vi00)
pad ; lq.xyzw vf07, 30(vi00)
pad ; lq.xyzw vf08, 31(vi00)
pad ; lq.xyzw vf09, 32(vi00)
pad ; lq.xyzw vf10, 33(vi00)
pad ; lq.xyzw vf11, 34(vi00)
pad ; lq.xyzw vf12, 35(vi00)
mulw.w vf17, vf00, vf00 ; iaddiu vi14, vi00, 256
pad ; move.z vf17, vf00
.word 0x400002FF ; nop_swap              ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_4810 — bone-blended vertex transform with clip-flag culling
; (program-4 clone of sub_2C00, but with subtle vf-register
; reshuffling: vf18/vf19/vf20/vf21 instead of vf18/vf21/vf20).
; -----------------------------------------------------------------------
sub_4810:
pad ; xtop vi01
pad ; ilwr.x vi10, vi01
pad ; iaddiu vi11, vi00, 32767
pad ; iand vi10, vi10, vi11
pad ; iaddi vi11, vi11, 1
pad ; lq.xyzw vf25, 0(vi01)
pad ; iaddiu vi03, vi01, 1
pad ; iaddiu vi02, vi01, 192
pad ; sq.xyzw vf25, 0(vi02)
pad ; iaddiu vi07, vi02, 1
mulw.xyzw   vf22, vf00, vf00 ; iaddi vi04, vi00, -2
mulw.xyzw   vf23, vf00, vf00 ; iaddi vi05, vi00, -2
mulw.xyzw   vf24, vf00, vf00 ; iaddi vi06, vi00, -2
pad ; lq.xyzw vf19, 1(vi03)              ; (different load order vs sub_2C00)
pad ; lq.xyzw vf18, 0(vi03)
pad ; lq.xyzw vf21, 2(vi03)
pad ; lq.xyzw vf20, 3(vi03)

L_4898:
mulax.xyzw  vf05, vf19 ; iaddiu vi03, vi03, 4
madday.xyzw vf06, vf19 ; iaddi vi10, vi10, -1
maddaz.xyzw vf07, vf19 ; iadd vi04, vi00, vi05
maddw.xyzw  vf26, vf08, vf19 ; iadd vi05, vi00, vi06
mulax.xyzw  vf01, vf18 ; move.xyzw vf22, vf23
madday.xyzw vf02, vf18 ; move.xyzw vf23, vf24
maddaz.xyzw vf03, vf18 ; lq.xyzw vf19, 1(vi03)
maxx.xyzw   vf26, vf26, vf00 ; nop_swap
pad ; nop_swap
pad ; nop_swap
maddw.xyzw  vf25, vf04, vf18 ; nop_swap
mulax.xyzw  vf09, vf26 ; nop_swap
madday.xyzw vf10, vf26 ; nop_swap
maddaz.xyzw vf11, vf26 ; nop_swap
maddw.xyzw  vf26, vf12, vf26 ; div Q, vf00.w, vf25.w
mulax.xyzw  vf13, vf18 ; nop_swap
madday.xyzw vf14, vf18 ; nop_swap
maddaz.xyzw vf15, vf18 ; nop_swap
maddw.xyzw  vf24, vf16, vf18 ; nop_swap
maxx.xyzw   vf26, vf26, vf00 ; lq.xyzw vf18, 0(vi03)
add.xy      vf21, vf21, vf17 ; nop_swap
mulq.xyzw   vf27, vf25 ; waitq
mulq.xyz    vf28, vf21 ; nop_swap
mul.xyz     vf20, vf20, vf26 ; nop_swap
; I-bit immediate bundle: upper sub.w vf00,vf21,vf00 + I-bit; lower = 255.0f → I.
; (disasm reads lower as `bal vi31, L_4960` — a misread; the next bundle is sequential.)
.word 0x8020A82C ; .word 0x437F0000

ftoi4.xyzw  vf27, vf27 ; lq.xyzw vf21, 2(vi03)
pad ; sq.xyzw vf28, 0(vi07)
minii.xyzw  vf20, vf20 ; nop_swap
.word 0x01D6B1FF ; fsand vi08, 0x2       ; flag-bit FD-dispatch FMAC
.word 0x01D7B9FF ; sq.xyzw vf27, 2(vi07)
.word 0x01D8C1FF ; nop_swap
pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
ftoi0.xyzw  vf29, vf20 ; fcand vi01, 0x3F
pad ; lq.xyzw vf20, 3(vi03)
pad ; iadd vi06, vi00, vi01
pad ; ibeq vi08, vi00, L_49E8
pad ; sq.xyzw vf29, 1(vi07)               ; (delay slot)
pad ; iaddi vi04, vi00, 1
pad ; iaddi vi05, vi00, 1
pad ; iaddi vi09, vi00, 2
L_49E8:
pad ; iadd vi01, vi04, vi05
pad ; iadd vi01, vi01, vi06
pad ; nop_swap
pad ; ibgtz vi01, L_4A40
pad ; nop_swap                           ; (delay slot)
L_4A10:
pad ; ibne vi10, vi00, L_4898
pad ; iaddiu vi07, vi07, 3                ; (delay slot)
pad ; xgkick vi02
pad ; nop_swap
pad ; b L_4788
pad ; nop_swap
L_4A40:
pad ; iaddi vi09, vi09, -1
pad ; ibgtz vi09, L_4B10
pad ; fcor vi01, 0xFDF7DF
pad ; ibne vi01, vi00, L_4B10
pad ; nop_swap
pad ; fcor vi01, 0xFEFBEF
pad ; ibne vi01, vi00, L_4B10
pad ; nop_swap
pad ; fcor vi01, 0xFF7DF7
pad ; ibne vi01, vi00, L_4B10
pad ; nop_swap
pad ; fcor vi01, 0xFFBEFB
pad ; ibne vi01, vi00, L_4B10
pad ; nop_swap
pad ; fcor vi01, 0xFFDF7D
pad ; ibne vi01, vi00, L_4B10
pad ; nop_swap
pad ; fcor vi01, 0xFFEFBE
pad ; ibne vi01, vi00, L_4B10
pad ; nop_swap
pad ; bal vi15, L_4540
pad ; nop_swap
pad ; bal vi15, L_3C50
pad ; nop_swap
pad ; bal vi15, L_4660
pad ; nop_swap
L_4B10:
pad ; b L_4A10
pad ; isw.w vi11, 2(vi07)                ; (delay slot)

; =======================================================================
; FIFTH VU0 PROGRAM begins here.  FCSET imm = 0x59 this time.
; Entry table at 0x4B40..0x4BE8 with targets L_4C40 / L_4CC8 /
; L_4D00 / L_4D70 / L_4E48 / L_4E60 / L_4EA8 / L_4EC0.
; =======================================================================

nop ; .word 0x70000000                  ; 0x4B20 — op7=0x38
nop ; nop                               ; 0x4B28 — true-zero filler
nop ; .word 0x60000059                  ; 0x4B30 — FCSET imm24=0x59
.word 0x4AB20000 ; nop                  ; 0x4B38 — upper FMAC-family (`add.yw vf00, vf00, vf18`+flags)

; Program-5 entry dispatch.
pad ; b L_4C40                          ; 0x4B40
pad ; nop_swap
pad ; b L_4CC8                          ; 0x4B50
pad ; nop_swap
pad ; nop_swap                          ; 0x4B60 — reserved
pad ; nop_swap                          ; 0x4B68 — reserved
pad ; nop_swap                          ; 0x4B70 — reserved
pad ; nop_swap                          ; 0x4B78 — reserved
pad ; b L_4D00                          ; 0x4B80
pad ; nop_swap
pad ; b L_4D70                          ; 0x4B90
pad ; nop_swap
pad ; b L_4E48                          ; 0x4BA0
pad ; nop_swap
pad ; nop_swap                          ; 0x4BB0 — reserved
pad ; nop_swap                          ; 0x4BB8 — reserved
pad ; b L_4E60                          ; 0x4BC0
pad ; nop_swap
pad ; b L_4EA8                          ; 0x4BD0
pad ; nop_swap
pad ; b L_4EC0                          ; 0x4BE0
pad ; nop_swap
pad ; nop_swap                          ; 0x4BF0 — reserved
pad ; nop_swap                          ; 0x4BF8 — reserved

.assert_pc 0x4C00
