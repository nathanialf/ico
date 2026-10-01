; ico2/vusrc/vu1_common.h /* derived name */: the routines all five VU1
; programs carry alike after their entry tables (SET_GSREGISTER,
; SET_UVOFFSET, SET_FONT_OFFSET and the debug font), included by each
; program text (vusrc/<program>.vsm). No overlay starts inside it, so no
; section name records its path; it is named like the other VU sources.
;
; -----------------------------------------------------------------------
; SET_GSREGISTER - quad-copy loop with embedded count header.
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
SET_GSREGISTER:
	nop                              xtop vi12                              ; vi12 = VIF unpack top (input ptr)
	nop                              ilwr.x vi10, (vi12)                    ; vi10 = *(int*)vi12  (count word)
	nop                              iaddiu vi07, vi12, 191                 ; vi07 = vi12 + 191   (output base)
	nop                              iaddiu vi09, vi07, 0                   ; vi09 = vi07         (output cursor)
	nop                              lqi.xyzw vf29, (vi12++)                ; vf29 = *vi12++      (first quad)
	nop                              iaddiu vi13, vi00, 32767               ; vi13 = 0x7FFF       (count mask)
	nop                              iand vi10, vi13, vi10                  ; vi10 &= 0x7FFF
	nop                              sqi.xyzw vf29, (vi09++)                ; *vi09++ = vf29      (store first)

SET_GSREGISTER_LOOP:
	nop                              lqi.xyzw vf28, (vi12++)                ; vf28 = *vi12++
	nop                              iaddi vi10, vi10, -1                   ; --count
	nop                              nop
	nop                              ibne vi10, vi00, SET_GSREGISTER_LOOP   ; loop while count != 0
	nop                              sqi.xyzw vf28, (vi09++)                ; *vi09++ = vf28   (branch delay slot)
	nop                              nop

; -----------------------------------------------------------------------
; (SET_GSREGISTER, continued) - kick the GIF packet and end the program.
;
; xgkick at vi07 triggers the GS write of the GIF packet that previous
; routines built up at the mem[vi07] region.  The E-bit upper on the
; next bundle halts the VU0 after one more bundle (the implicit E-bit
; delay slot).
; -----------------------------------------------------------------------
	nop                              xgkick vi07                            ; kick GIF packet at mem[vi07]
	nop[e]                           nop                                    ; upper: E-bit pad (END)
	nop                              nop                                    ; E-bit delay slot - VU0 halts after

; -----------------------------------------------------------------------
; SET_UVOFFSET - patch the .xy lanes of VU mem[2] from a VIF input quad.
;
; Reads the persistent constant at mem[2] (likely a view-translate
; quad), copies the .xy lanes from the next VIF input over it, and
; writes the result back.  The .zw lanes of mem[2] are preserved.
; -----------------------------------------------------------------------
SET_UVOFFSET:
	nop                              xtop vi01                              ; vi01 = VIF top
	nop                              lq.xyzw vf30, 2(vi00)                  ; vf30 = mem[2]
	nop                              lqi.xyzw vf31, (vi01++)                ; vf31 = *vi01++
	nop                              move.xy vf30, vf31                     ; vf30.xy = vf31.xy
	nop                              sq.xyzw vf30, 2(vi00)                  ; mem[2] = vf30
	nop[e]                           nop                                    ; upper: E-bit pad (END)
	nop                              nop                                    ; E-bit delay slot

; -----------------------------------------------------------------------
; SET_FONT_OFFSET - bulk 4-quad upload to mem[256..259].
;
; Loads four quads from VIF unpack into vf18, vf19, vf16, vf17 (note
; non-sequential destination order) and writes them out to mem[256+]
; in the same order.  Looks like a 4-row matrix upload into the
; persistent matrix slot at mem[256].
; -----------------------------------------------------------------------
SET_FONT_OFFSET:
	nop                              xtop vi12                              ; vi12 = VIF top
	nop                              iaddiu vi13, vi00, 256                 ; vi13 = mem[256] base
	nop                              lqi.xyzw vf18, (vi12++)                ; vf18 = *vi12++   (row 0)
	nop                              lqi.xyzw vf19, (vi12++)                ; vf19 = *vi12++   (row 1)
	nop                              lqi.xyzw vf16, (vi12++)                ; vf16 = *vi12++   (row 2)
	nop                              lqi.xyzw vf17, (vi12++)                ; vf17 = *vi12++   (row 3)
	nop                              sqi.xyzw vf18, (vi13++)                ; mem[256] = vf18
	nop                              sqi.xyzw vf19, (vi13++)                ; mem[257] = vf19
	nop                              sqi.xyzw vf16, (vi13++)                ; mem[258] = vf16
	nop                              sqi.xyzw vf17, (vi13++)                ; mem[259] = vf17
	nop[e]                           nop                                    ; upper: E-bit pad (END)
	nop                              nop                                    ; E-bit delay slot

; -----------------------------------------------------------------------
; BEGIN_DEBUG_FONT - shared "end immediately" stub.
;
; Branched-to by routines (e.g. SPACE_DEBUG_FONT) that need to bail out without
; doing further work.  The E-bit halts the VU0 program after the
; implicit delay slot.
; -----------------------------------------------------------------------
BEGIN_DEBUG_FONT:
	nop[e]                           nop                                    ; upper: E-bit pad (END)
	nop                              nop                                    ; E-bit delay slot

; -----------------------------------------------------------------------
; START_DEBUG_FONT - palette-indexed vertex transform with GS kick.
;
; Reads a 16-bit count from *(int*)vi12, then iterates `count` times:
;   - load vertex quad from the vi11 stream (vi11 = vi12 + 1)
;   - extract the .w lane as an int, mask bit 0 -> palette index 0/1
;   - load the chosen palette entry from mem[256 + idx]
;   - add palette to vf09.xy, zero vf09.w
;   - ftoi4 convert and store via sqi to the output cursor (vi09)
; After the loop, `xgkick` triggers GS output.  The routine then
; falls through into SPACE_DEBUG_FONT final-add tail, which branches to
; BEGIN_DEBUG_FONT to terminate.
; -----------------------------------------------------------------------
START_DEBUG_FONT:
	nop                              xtop vi12                              ; vi12 = VIF top
	nop                              iaddiu vi11, vi12, 1                   ; vi11 = vi12 + 1     (vertex stream)
	nop                              ilwr.x vi10, (vi12)                    ; vi10 = *(int*)vi12  (count)
	nop                              lq.xyzw vf29, 0(vi12)                  ; vf29 = *vi12        (header quad)
	nop                              iaddiu vi13, vi00, 32767               ; vi13 = 0x7FFF
	nop                              iaddiu vi07, vi12, 191                 ; vi07 = vi12 + 191   (output base)
	nop                              iaddiu vi09, vi07, 0                   ; vi09 = vi07
	nop                              sqi.xyzw vf29, (vi09++)                ; *vi09++ = vf29      (store header)
	nop                              iand vi10, vi13, vi10                  ; vi10 &= 0x7FFF
	nop                              iaddiu vi13, vi00, 1                   ; vi13 = 1            (palette bit mask)
	nop                              lq.xyzw vf09, 0(vi11)                  ; vf09 = *vi11        (first vertex)
	nop                              ilwr.w vi14, (vi11)                    ; vi14 = (int)vi11.w
	nop                              nop
	nop                              iand vi15, vi13, vi14                  ; vi15 = vi14 & 1

LOOP_DEBUG_FONT:
	add.xy vf09, vf09, vf16          lq.xyzw vf20, 256(vi15)                ; vf09.xy += palette; load palette[idx]
	nop                              move.w vf09, vf00                      ; vf09.w = 0
	nop                              iaddiu vi11, vi11, 1                   ; vi11++
	nop                              ilwr.w vi14, (vi11)                    ; vi14 = (int)vi11.w
	nop                              iaddi vi10, vi10, -1                   ; --count
	ftoi4.xyzw vf10, vf09            sqi.xyzw vf20, (vi09++)                ; ftoi4 vf09->vf10; *vi09++ = palette
	nop                              lq.xyzw vf09, 0(vi11)                  ; vf09 = next vertex
	nop                              iand vi15, vi13, vi14                  ; vi15 = vi14 & 1
	nop                              ibne vi10, vi00, LOOP_DEBUG_FONT       ; loop while count != 0
	nop                              sqi.xyzw vf10, (vi09++)                ; *vi09++ = vf10      (delay slot)

	nop                              nop                                    ; (0x300) post-loop pad
	nop                              xgkick vi07                            ; (0x308) kick GIF packet
	nop                              nop                                    ; (0x310) - falls through into SPACE_DEBUG_FONT

; -----------------------------------------------------------------------
; SPACE_DEBUG_FONT - final palette-step + exit.  Reachable as its own entry
; (TPC=0x70 -> b SPACE_DEBUG_FONT) OR by fall-through from START_DEBUG_FONT.  The single
; FMAC bumps vf16.xy by vf17.xy (i.e. advances the palette base by
; one palette stride), then branches to BEGIN_DEBUG_FONT to end the program.
; -----------------------------------------------------------------------
SPACE_DEBUG_FONT:
	add.xy vf16, vf16, vf17          nop                                    ; vf16.xy += vf17.xy
	nop                              b BEGIN_DEBUG_FONT                     ; -> BEGIN_DEBUG_FONT (END)
	nop                              nop                                    ; branch delay slot
