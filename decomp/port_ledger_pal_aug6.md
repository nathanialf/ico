
# aug6 -> PAL body port (`tools/port_from_ntsc.py --source aug6`)

Bodies below were carried over from the `aug6` (Aug-6-2001 prototype)
checkout's matched clean-room C with every aug6 symbol rebound to its PAL
counterpart by the lockstep reloc-slot walk.  This pass runs AFTER the ntsc
pass and only ever attempts functions the ntsc pass left as
`INCLUDE_ASM`.  Nothing here was hand-tuned:
each function either reproduced the PAL instruction stream as-is (`PORTED`)
or went straight back to `INCLUDE_ASM` (`REVERTED`, with the first
divergence or compiler diagnostic recorded).  `SKIPPED` = deferred to the
jump-table queue.

Revert-reason classes: `unresolved-symbol` (a reloc slot the walk could not
bind) · `emits-data` (needs a data carve; the source TU's carve entries
are listed under `CARVES`) · `crutch` (the source body carries a banned
zero-code codegen pin — see CLAUDE.md; never kept) ·
`callee-sig-conflict` / `arity` · `undeclared` / `parse` ·
`missing-body` · `codegen` (compiles, wrong bytes — a genuine
source-vs-PAL source difference) · `jtbl`.

## Accounting

| wave | candidates | ported | reverted | skipped | pre-matched | unattempted |
|---|---|---|---|---|---|---|
| 1 | 1343 | 125 | 160 | 1 | 1057 | 0 |
| 2 | 447 | 24 | 23 | 2 | 398 | 0 |
| 3 | 337 | 0 | 251 | 1 | 85 | 0 |
| **all** | 2127 | 149 | 434 | 4 | 1540 | 0 |

### ios/cdvd
- REVERTED `inflate_cd_read_func` w3 @ 0x001356C8 — [codegen] insn 3: expected `lw	v0,316(a2)` built `lw	v0,312(a2)`
- PRE-MATCHED `iosCdvdBackGroundMgrDelete` w1 @ 0x001355A8 — already had a PAL body
- PRE-MATCHED `iosCdvdBackGroundMgrDeleteRequestGet` w1 @ 0x001355D8 — already had a PAL body
- PRE-MATCHED `iosCdvdBackGroundMgrEntryNum` w1 @ 0x00135620 — already had a PAL body
- PRE-MATCHED `iosCdvdBackGroundMgrGetRunning` w2 @ 0x00135660 — already had a PAL body
- PRE-MATCHED `iosCdvdBackGroundMgrInit` w1 @ 0x00135728 — already had a PAL body
- PRE-MATCHED `iosCdvdBackGroundMgrNotDiskReadyPauseSet` w1 @ 0x001355B8 — already had a PAL body
- PRE-MATCHED `iosCdvdBackGroundMgrSeek` w1 @ 0x00135658 — already had a PAL body
- PRE-MATCHED `iosCdvdChgFileName` w1 @ 0x00135370 — already had a PAL body
- PRE-MATCHED `iosCdvdDirectStRead` w1 @ 0x00135668 — already had a PAL body
- PRE-MATCHED `iosCdvdDiskStatusGet` w2 @ 0x001355A0 — already had a PAL body
- PRE-MATCHED `iosCdvdHandlerRead` w1 @ 0x001342E0 — already had a PAL body
- PRE-MATCHED `iosCdvdLoad` w1 @ 0x00134800 — already had a PAL body
- REVERTED `iosCdvdLoadPackFile` w3 @ 0x00135520 — [codegen] insn 14: expected `addiu	a0,s0,56` built `addiu	a0,s0,52`
- PRE-MATCHED `iosCdvdPackLoad` w1 @ 0x00134838 — already had a PAL body
- PRE-MATCHED `iosCdvdSync` w1 @ 0x001354F0 — already had a PAL body

### ios/inflate
- PORTED `close_inflate_handler` w1 @ 0x001376A8 <- aug6 fumi/ios/inflate:func_00135118 (5 syms rebound)
- PRE-MATCHED `huft_free` w1 @ 0x00137DA8 — already had a PAL body
- PRE-MATCHED `inflate_start` w1 @ 0x00137658 — already had a PAL body
- PORTED `open_inflate_handler` w1 @ 0x00137C38 <- aug6 fumi/ios/inflate:func_001356A8 (9 syms rebound)

### ios/mblock
- PRE-MATCHED `init_mblock` w1 @ 0x00138280 — already had a PAL body
- PRE-MATCHED `reuse_mblock` w1 @ 0x00138338 — already had a PAL body
- PRE-MATCHED `reuse_mblock1` w1 @ 0x00138258 — already had a PAL body

### ios/mcard
- PORTED `iosMcChdirProduct` w1 @ 0x0013A398 <- aug6 fumi/ios/mcdata:func_00137ED8 (3 syms rebound)
- PRE-MATCHED `iosMcDelete` w1 @ 0x0013A1E8 — already had a PAL body
- PRE-MATCHED `iosMcFormat` w1 @ 0x0013A110 — already had a PAL body
- PORTED `iosMcGetBlockSaveInfo` w1 @ 0x0013A3E0 <- aug6 fumi/ios/mcdata:func_00137F20 (3 syms rebound)
- PORTED `iosMcGetDir` w1 @ 0x0013A1A0 <- aug6 fumi/ios/mcdata:iosMcIconWriteIconsys (3 syms rebound)
- PRE-MATCHED `iosMcGetInfo` w1 @ 0x0013A0D0 — already had a PAL body
- PORTED `iosMcLoadGameBlock` w1 @ 0x0013A350 <- aug6 fumi/ios/mcdata:func_00137E90 (3 syms rebound)
- PORTED `iosMcLoadProductBlock` w1 @ 0x0013A2C0 <- aug6 fumi/ios/mcdata:func_00137E00 (3 syms rebound)
- PRE-MATCHED `iosMcMgrSaveProductBlock` w1 @ 0x001397C8 — already had a PAL body
- PORTED `iosMcSaveGameBlock` w1 @ 0x0013A308 <- aug6 fumi/ios/mcdata:func_00137E48 (3 syms rebound)
- PRE-MATCHED `iosMcSaveIconBlock` w1 @ 0x0013A230 — already had a PAL body
- PORTED `iosMcSaveProductBlock` w1 @ 0x0013A278 <- aug6 fumi/ios/mcdata:func_00137DB8 (3 syms rebound)
- PRE-MATCHED `iosMcSync` w1 @ 0x0013A0B8 — already had a PAL body
- PRE-MATCHED `iosMcTest` w2 @ 0x0013A0B0 — already had a PAL body
- PRE-MATCHED `iosMcUnformat` w1 @ 0x0013A158 — already had a PAL body
- REVERTED `product_read` w3 @ 0x0013A5A0 — [codegen] insn 1: expected `addiu	v1,zero,496` built `addiu	v1,zero,396`

### ios/memory
- PRE-MATCHED `_iosFreeWithFill` w1 @ 0x0013B778 — already had a PAL body
- PRE-MATCHED `iosFree` w3 @ 0x0013B820 — already had a PAL body
- PRE-MATCHED `iosMallocCheckLeak2` w3 @ 0x0013BEB8 — already had a PAL body
- PRE-MATCHED `iosMallocSetPartitionName` w1 @ 0x0013AE78 — already had a PAL body

### ios/message
- REVERTED `deq_mes_th` w1 @ 0x0013C4A8 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `func_0013C608` w1 @ 0x0013C608 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `func_0013C720` w1 @ 0x0013C720 — [codegen] insn 8: expected `bne	s2,zero,34 <func_0013C720+0x34>` built `bne	s2,zero,2a8 <func_0013C720+0x30>`
- PRE-MATCHED `iosMsgInit` w1 @ 0x0013C808 — already had a PAL body
- REVERTED `iosMsgQueueCreate` w1 @ 0x0013C4D8 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `iosMsgQueueDestroy` w1 @ 0x0013C580 — [callee-sig-conflict] ios/message.c:43: conflicting types for `iosMsgQueueDestroy'
- PRE-MATCHED `iosMsgQueueDestroyAll` w1 @ 0x0013CA50 — already had a PAL body
- REVERTED `iosMsgRecv` w1 @ 0x0013C948 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosMsgSend` w1 @ 0x0013C840 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PRE-MATCHED `signal_handler` w1 @ 0x0013CAA8 — already had a PAL body

### ios/pad
- PRE-MATCHED `func_0013DE08` w1 @ 0x0013DE08 — already had a PAL body
- PRE-MATCHED `iosPadActInit` w1 @ 0x0013DC60 — already had a PAL body
- PRE-MATCHED `iosPadActStop` w1 @ 0x0013DCD8 — already had a PAL body
- PRE-MATCHED `iosPadActStopAll` w1 @ 0x0013DD58 — already had a PAL body
- PRE-MATCHED `iosPadActVolumeSet` w1 @ 0x0013DDC0 — already had a PAL body
- PRE-MATCHED `iosPadConnect` w1 @ 0x0013DB20 — already had a PAL body
- PRE-MATCHED `iosPadDevRead` w1 @ 0x0013DA78 — already had a PAL body
- PRE-MATCHED `iosPadDisable` w2 @ 0x0013DC50 — already had a PAL body
- PRE-MATCHED `iosPadDisconWait` w2 @ 0x0013DF58 — already had a PAL body
- PRE-MATCHED `iosPadEnable` w2 @ 0x0013DC40 — already had a PAL body
- PRE-MATCHED `iosPadEnableGet` w2 @ 0x0013DC58 — already had a PAL body
- PRE-MATCHED `iosPadErrorWait` w2 @ 0x0013DF60 — already had a PAL body
- PRE-MATCHED `iosPadGetDevice` w1 @ 0x0013DAD8 — already had a PAL body
- PRE-MATCHED `iosPadGetPort` w1 @ 0x0013DAA8 — already had a PAL body
- PRE-MATCHED `iosPadGetSlot` w1 @ 0x0013DAC0 — already had a PAL body

### ios/shockdriver
- PRE-MATCHED `Get_ShockRequestStruct` w1 @ 0x0013F118 — already had a PAL body
- PRE-MATCHED `Init_Controler` w2 @ 0x0013F358 — already had a PAL body
- REVERTED `Init_Player` w1 @ 0x0013F320 — [codegen] insn 2: expected `addiu	v0,v0,0` built `addiu	v0,v0,4528`
- PRE-MATCHED `Init_ShockDriver` w1 @ 0x0013EE30 — already had a PAL body
- PRE-MATCHED `Init_ShockEmulator` w2 @ 0x0013F048 — already had a PAL body
- PRE-MATCHED `Init_ShockRequestAlloc` w1 @ 0x0013F0D0 — already had a PAL body
- REVERTED `Init_ShockRequestBox` w1 @ 0x0013E8F8 — [codegen] insn 5: expected `addiu	v0,v0,0` built `addiu	v0,v0,5400`
- PRE-MATCHED `Init_ShockVoiceSet` w1 @ 0x0013E870 — already had a PAL body
- PRE-MATCHED `Reset_ShockRequestStruct` w1 @ 0x0013F158 — already had a PAL body
- PRE-MATCHED `ShockDriver_GetShockVoice` w1 @ 0x0013EFE8 — already had a PAL body
- PRE-MATCHED `ShockDriver_GetShockVoiceMax` w1 @ 0x0013EF70 — already had a PAL body
- PRE-MATCHED `ShockDriver_GetShockVoiceSet` w1 @ 0x0013EFB8 — already had a PAL body
- PRE-MATCHED `ShockDriver_VoiceSet_NumberRegist` w1 @ 0x0013EE88 — already had a PAL body
- PRE-MATCHED `ShockDriver_VoiceSet_Regist` w1 @ 0x0013EEC0 — already had a PAL body
- PRE-MATCHED `ShockDriver_VoiceSet_Remove` w1 @ 0x0013EF38 — already had a PAL body
- PRE-MATCHED `ShockEmulator_EmulationShot` w1 @ 0x0013F058 — already had a PAL body
- PORTED `ShockEmulator_EmulationWave` w1 @ 0x0013F060 <- aug6 fumi/ios/thread:iosThreadMain (1 syms rebound)
- PRE-MATCHED `ShockRequestBox_Clear` w2 @ 0x0013E920 — already had a PAL body
- PRE-MATCHED `ShockRequestBox_EndRequestFree` w1 @ 0x0013EC08 — already had a PAL body
- PRE-MATCHED `ShockRequestBox_GetRequest` w1 @ 0x0013ED08 — already had a PAL body
- PRE-MATCHED `ShockRequestBox_Regst` w1 @ 0x0013E980 — already had a PAL body
- PRE-MATCHED `ShockRequestBox_RequestCancel` w1 @ 0x0013ED40 — already had a PAL body
- PRE-MATCHED `ShockRequestBox_RequestDirectCancel` w1 @ 0x0013EDC0 — already had a PAL body
- PRE-MATCHED `Shock_RequestClear` w2 @ 0x0013F368 — already had a PAL body
- PRE-MATCHED `Shock_SetMotor` w1 @ 0x0013E708 — already had a PAL body
- PRE-MATCHED `Shock_SetShockVoiceSet` w1 @ 0x0013F2F0 — already had a PAL body
- PRE-MATCHED `Vibration_SetDecodeData` w1 @ 0x0013E8A8 — already had a PAL body
- PRE-MATCHED `Vibration_SetDecodeEnd` w1 @ 0x0013F488 — already had a PAL body
- PRE-MATCHED `dumyAllocFunc` w2 @ 0x0013F480 — already had a PAL body

### ios/thread
- PORTED `iosGetIOSThreadFromId` w1 @ 0x0013FCC8 <- aug6 fumi/ios/thread:func_0013D3C8 (4 syms rebound)
- PORTED `iosSemaCreate` w1 @ 0x0013FDE8 <- aug6 fumi/ios/thread:func_0013D4E8 (8 syms rebound)
- PORTED `iosSemaDelete` w1 @ 0x0013FE70 <- aug6 fumi/ios/thread:func_0013D570 (8 syms rebound)
- PORTED `iosSemaReferStatus` w1 @ 0x0013FF98 <- aug6 fumi/ios/thread:func_0013D698 (8 syms rebound)
- PORTED `iosSemaSignal` w1 @ 0x0013FF48 <- aug6 fumi/ios/thread:func_0013D648 (4 syms rebound)
- PORTED `iosSemaWait` w1 @ 0x0013FEE8 <- aug6 fumi/ios/thread:func_0013D5E8 (5 syms rebound)
- PRE-MATCHED `iosThreadCancelWakeup` w1 @ 0x0013FDB0 — already had a PAL body
- PRE-MATCHED `iosThreadDestroy` w1 @ 0x0013F7E0 — already had a PAL body
- PRE-MATCHED `iosThreadGetPri` w1 @ 0x0013FC88 — already had a PAL body
- PORTED `iosThreadJoin` w1 @ 0x0013FD30 <- aug6 fumi/ios/thread:func_0013D430 (8 syms rebound)
- REVERTED `iosThreadMain` w1 @ 0x0013F528 — [codegen] insn 20: expected `j	0 <iosThreadMain>` built `j	300 <iosThreadSetPri>`
- PRE-MATCHED `iosThreadMessage` w1 @ 0x0013F880 — already had a PAL body
- PRE-MATCHED `iosThreadName` w2 @ 0x0013F920 — already had a PAL body
- PRE-MATCHED `iosThreadResume` w2 @ 0x0013F930 — already had a PAL body
- PRE-MATCHED `iosThreadSetPri` w1 @ 0x0013F828 — already had a PAL body
- PRE-MATCHED `iosThreadSleep` w2 @ 0x0013F7D8 — already had a PAL body
- PRE-MATCHED `iosThreadStart` w1 @ 0x0013F7B0 — already had a PAL body
- PRE-MATCHED `iosThreadStop` w1 @ 0x0013F7C0 — already had a PAL body
- PRE-MATCHED `iosThreadSuspend` w2 @ 0x0013F928 — already had a PAL body
- PRE-MATCHED `iosThreadWakeup` w1 @ 0x0013FD10 — already had a PAL body

### isys/gobj
- REVERTED `add_gobj_to_head` w1 @ 0x001404A8 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `add_gobj_to_tail` w1 @ 0x001403D8 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `cut_gobj_link` w1 @ 0x001401E0 — [codegen] insn 1: expected `bnel	a1,zero,18 <cut_gobj_link+0x18>` built `bnel	a1,zero,84 <cut_gobj_link+0x14>`
- PORTED `isysGObjActiveDlLink` w2 @ 0x00141160 <- aug6 fumi/isys/gobj_dl:isysGObjMoveObjDL (2 syms rebound)
- PRE-MATCHED `isysGObjActiveLink` w2 @ 0x00141128 — already had a PAL body
- REVERTED `isysGObjAdd` w1 @ 0x00140CC0 — [undeclared] isys/gobj.c:84: dereferencing pointer to incomplete type
- REVERTED `isysGObjAddAfterGObj` w1 @ 0x00140608 — [codegen] insn 20: expected `bne	a0,a2,6c <isysGObjAddAfterGObj+0x6c>` built `bne	a0,a2,500 <isysGObjAddAfterGObj+0x68>`
- REVERTED `isysGObjAddBeforeGObj` w1 @ 0x00140738 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGObjAddHead` w1 @ 0x00140DC8 — [undeclared] isys/gobj.c:85: dereferencing pointer to incomplete type
- REVERTED `isysGObjAlloc` w1 @ 0x001408B8 — [codegen] insn 3: expected `lui	a2,0x0` built `daddu	s0,a0,zero`
- PRE-MATCHED `isysGObjGetExist_begin` w1 @ 0x00141090 — already had a PAL body
- REVERTED `isysGObjGetExist_next` w1 @ 0x001410E0 — [undeclared] isys/gobj.c:105: dereferencing pointer to incomplete type
- REVERTED `isysGObjInit` w1 @ 0x00140188 — [codegen] insn 1: expected `lui	v1,0x0` built `lui	v0,0x0`
- REVERTED `isysGObjKindTableAdd` w3 @ 0x00140A30 — [codegen] insn 12: expected `jal	0 <isysGObjKindTableAdd>` built `jal	dc8 <isysGObjSearchFromObjKindID_begin>`
- REVERTED `isysGObjKindTableRemove` w3 @ 0x00140B10 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PRE-MATCHED `isysGObjMove` w1 @ 0x00140578 — already had a PAL body
- REVERTED `isysGObjMoveAfterGObj` w1 @ 0x00140BE0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `isysGObjMoveBeforeGObj` w1 @ 0x00140C50 — already had a PAL body
- REVERTED `isysGObjRemove` w3 @ 0x00140930 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `isysGObjRemoveAll` w3 @ 0x00140288 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGObjSearchFromLabelTypeID` w1 @ 0x00141038 — [undeclared] isys/gobj.c:91: dereferencing pointer to incomplete type
- REVERTED `isysGObjSearchFromObjKindID_begin` w3 @ 0x00140F38 — [undeclared] isys/gobj.c:93: dereferencing pointer to incomplete type
- REVERTED `isysGObjSearchFromObjKindID_next` w1 @ 0x00140FC8 — [undeclared] isys/gobj.c:94: dereferencing pointer to incomplete type
- PRE-MATCHED `isysGObjSearchFromObjLayoutID` w1 @ 0x00140ED0 — already had a PAL body
- PRE-MATCHED `isysGetNbAllocedGObjs` w1 @ 0x00140870 — already had a PAL body

### isys/gobj_cam_dl
- REVERTED `cut_gobj_camera_dl_link` w1 @ 0x0020BF58 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x78 (out-of-line helper or extra code)
- REVERTED `func_0020BFD8` w1 @ 0x0020BFD8 — [callee-sig-conflict] isys/gobj_cam_dl.c:84: conflicting types for `func_0020BFD8'
- PRE-MATCHED `isysGObjCameraDlInit` w2 @ 0x0020C260 — already had a PAL body
- REVERTED `isysGObjLinkCameraDL` w1 @ 0x0020C130 — [codegen] insn 5: expected `lui	a0,0x0` built `daddu	s4,a1,zero`
- PRE-MATCHED `isysGObjLinkCameraDLAfterGObj` w2 @ 0x0020C1B0 — already had a PAL body
- PRE-MATCHED `isysGObjLinkCameraDLBeforeGObj` w2 @ 0x0020C208 — already had a PAL body
- PRE-MATCHED `isysGObjMoveCameraDL` w1 @ 0x0020C0F8 — already had a PAL body
- PRE-MATCHED `isysGObjMoveCameraDLHead` w1 @ 0x0020C270 — already had a PAL body
- PRE-MATCHED `isysGObjRemoveCameraDL` w2 @ 0x0020BFD0 — already had a PAL body
- PRE-MATCHED `isysObjMoveCameraDLAfterGObj` w1 @ 0x0020C3F0 — already had a PAL body
- PORTED `isysObjMoveCameraDLBeforeGObj` w1 @ 0x0020C450 <- aug6 fumi/sound/adpcm_init:adpcmDataSet (3 syms rebound)

### isys/gobj_dl
- REVERTED `cut_gobj_dl_link` w1 @ 0x00141198 — [codegen] insn 1: expected `bnel	a1,zero,18 <cut_gobj_dl_link+0x18>` built `bnel	a1,zero,14 <cut_gobj_dl_link+0x14>`
- REVERTED `func_00141248` w1 @ 0x00141248 — [codegen] insn 5: expected `lui	a0,0x0` built `daddu	s2,a2,zero`
- PRE-MATCHED `func_001413B8` w1 @ 0x001413B8 — already had a PAL body
- PORTED `isysGObjDlInit` w1 @ 0x001416B0 <- aug6 fumi/isys/gobj_process:isysGObjProcessInit (3 syms rebound)
- REVERTED `isysGObjLinkObjDL` w1 @ 0x00141518 — [codegen] insn 5: expected `lui	a0,0x0` built `daddu	s4,a3,zero`
- PRE-MATCHED `isysGObjLinkObjDLAfterGObj` w2 @ 0x001415E0 — already had a PAL body
- PRE-MATCHED `isysGObjLinkObjDLBeforeGObj` w2 @ 0x00141648 — already had a PAL body
- PRE-MATCHED `isysGObjLinkObjDLHead` w1 @ 0x001415B8 — already had a PAL body
- PRE-MATCHED `isysGObjMoveObjDL` w2 @ 0x00141488 — already had a PAL body
- PRE-MATCHED `isysGObjMoveObjDLAfterGObj` w1 @ 0x001416F0 — already had a PAL body
- PRE-MATCHED `isysGObjMoveObjDLBeforeGObj` w1 @ 0x00141760 — already had a PAL body
- PRE-MATCHED `isysGObjMoveObjDLHead` w2 @ 0x001414D0 — already had a PAL body
- PRE-MATCHED `isysGObjRemoveObjDL` w2 @ 0x00141240 — already had a PAL body

### isys/gobj_process
- PRE-MATCHED `free_gobj_process_resource` w2 @ 0x00141D78 — already had a PAL body
- PRE-MATCHED `isysGObjProcActive` w1 @ 0x00141C60 — already had a PAL body
- PRE-MATCHED `isysGObjProcActiveAll` w1 @ 0x00141C70 — already had a PAL body
- PRE-MATCHED `isysGObjProcActivePtr` w1 @ 0x00141D48 — already had a PAL body
- PRE-MATCHED `isysGObjProcAdd` w1 @ 0x00141B60 — already had a PAL body
- PRE-MATCHED `isysGObjProcAddGOppArg` w1 @ 0x00141BC0 — already had a PAL body
- PRE-MATCHED `isysGObjProcAddS` w1 @ 0x00141B90 — already had a PAL body
- PRE-MATCHED `isysGObjProcAddSGOppArg` w1 @ 0x00141D18 — already had a PAL body
- PRE-MATCHED `isysGObjProcPause` w1 @ 0x00141BF0 — already had a PAL body
- PRE-MATCHED `isysGObjProcPauseAll` w1 @ 0x00141BF8 — already had a PAL body
- PRE-MATCHED `isysGObjProcPausePtr` w1 @ 0x00141C30 — already had a PAL body
- PRE-MATCHED `isysGObjProcRemove` w1 @ 0x00141AA0 — already had a PAL body
- PRE-MATCHED `isysGObjProcRemoveAll` w1 @ 0x00141CA8 — already had a PAL body
- PRE-MATCHED `isysGObjProcThreadSleep` w1 @ 0x00141CE0 — already had a PAL body
- PRE-MATCHED `isysGObjProcessAlloc` w1 @ 0x00141AE8 — already had a PAL body
- REVERTED `isysGObjProcessInit` w2 @ 0x001417D0 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)

### isys/isys
- PRE-MATCHED `isysInitialize` w2 @ 0x00141D80 — already had a PAL body

### isys/obj_manager
- PRE-MATCHED `iosOmBeforeFuncStandard` w2 @ 0x00142368 — already had a PAL body
- PRE-MATCHED `iosOmExeEachGObj` w1 @ 0x001420F8 — already had a PAL body
- PRE-MATCHED `iosOmExeEachGObjAll` w1 @ 0x00142160 — already had a PAL body
- PRE-MATCHED `iosOmGetGObjStatus` w1 @ 0x00142298 — already had a PAL body
- REVERTED `iosOmInit` w1 @ 0x00141D88 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- PRE-MATCHED `iosOmMain` w2 @ 0x00141FE0 — already had a PAL body
- PRE-MATCHED `iosOmSearchGObjId` w1 @ 0x001422C8 — already had a PAL body
- PRE-MATCHED `iosOmSearchGObjIdAll` w1 @ 0x00142308 — already had a PAL body
- PRE-MATCHED `iosOmSendMail` w1 @ 0x00142370 — already had a PAL body
- PRE-MATCHED `iosOmSendMailLink` w1 @ 0x001423B8 — already had a PAL body

### ito/mpeg/mv_audiodec
- REVERTED `audioDecEndPut` w1 @ 0x00257708 — [codegen] [§3.1] sltu+movz bool collapse
- PRE-MATCHED `audioDecIsPreset` w1 @ 0x00257F10 — already had a PAL body
- PRE-MATCHED `audioDecPause` w1 @ 0x00257FC0 — already had a PAL body
- PRE-MATCHED `audioDecReset` w1 @ 0x00257EB8 — already had a PAL body
- PORTED `audioDecResume` w2 @ 0x00257FF8 <- aug6 ito/mpeg/mv_sub:func_0023A888 (4 syms rebound)
- PRE-MATCHED `audioDecStart` w2 @ 0x00257F28 — already had a PAL body

### ito/mpeg/mv_disp
- PRE-MATCHED `dispDelete` w2 @ 0x00258B08 — already had a PAL body
- PRE-MATCHED `dispSwitch` w1 @ 0x00258948 — already had a PAL body
- PRE-MATCHED `endDisplay` w2 @ 0x00258BC8 — already had a PAL body
- PRE-MATCHED `handler_endimage` w1 @ 0x00258B50 — already had a PAL body
- PRE-MATCHED `loadImage` w1 @ 0x00258B10 — already had a PAL body
- PORTED `sendDispEnv` w1 @ 0x002583F8 <- aug6 ito/mpeg/mv_sub:func_0023ACA0 (4 syms rebound)
- PRE-MATCHED `setBITBLTBUF` w1 @ 0x00259260 — already had a PAL body
- PORTED `setCLAMP_1` w1 @ 0x002591E8 <- aug6 common/src/GobjProc:ResetGObjProc (1 syms rebound)
- PRE-MATCHED `setDMAscTag` w1 @ 0x00258BD8 — already had a PAL body
- PORTED `setFRAME_1` w1 @ 0x00258FA8 <- aug6 ito/mpeg/mv_vibuf:func_0023B970 (1 syms rebound)
- PRE-MATCHED `setGIFad` w1 @ 0x00258C88 — already had a PAL body
- PRE-MATCHED `setGIFtag` w1 @ 0x00258C30 — already had a PAL body
- PRE-MATCHED `setImageSize` w1 @ 0x002583E8 — already had a PAL body
- PRE-MATCHED `setPRIM` w1 @ 0x00258E10 — already had a PAL body
- PORTED `setPRMODE` w1 @ 0x00259158 <- aug6 ito/mpeg/mv_vibuf:func_0023BB20 (1 syms rebound)
- PRE-MATCHED `setPRMODECONT` w1 @ 0x00259128 — already had a PAL body
- PRE-MATCHED `setRGBAQ` w1 @ 0x00258EF0 — already had a PAL body
- PORTED `setSCISSOR_1` w1 @ 0x00259098 <- aug6 ito/mpeg/mv_vibuf:func_0023BA60 (1 syms rebound)
- PORTED `setTEST_1` w1 @ 0x00259008 <- aug6 ito/mpeg/mv_vibuf:func_0023B9D0 (1 syms rebound)
- PRE-MATCHED `setTEX0_1` w1 @ 0x00258D58 — already had a PAL body
- PRE-MATCHED `setTEX1_1` w1 @ 0x00258CD8 — already had a PAL body
- PRE-MATCHED `setTEXFLUSH` w1 @ 0x00258CB8 — already had a PAL body
- PORTED `setTRXDIR` w1 @ 0x00259308 <- aug6 common/src/GobjProc:PrintGObjID (1 syms rebound)
- PRE-MATCHED `setTRXPOS` w1 @ 0x00259298 — already had a PAL body
- PRE-MATCHED `setTRXREG` w1 @ 0x002592D0 — already had a PAL body
- PRE-MATCHED `setUV` w1 @ 0x00258EA8 — already had a PAL body
- PORTED `setXYOFFSET_1` w1 @ 0x002590F0 <- aug6 ito/mpeg/mv_vibuf:func_0023BAB8 (1 syms rebound)
- PORTED `setXYZ2` w1 @ 0x00258F58 <- aug6 ito/mpeg/mv_vibuf:func_0023B920 (1 syms rebound)
- PRE-MATCHED `startDisplay` w1 @ 0x00258B88 — already had a PAL body

### ito/mpeg/mv_main
- REVERTED `movie_proc` w1 @ 0x001A67A8 — [codegen] ito/mpeg/mv_main.c:3: mv_defs.h: No such file or directory
- PRE-MATCHED `proceedAudio` w2 @ 0x001A5DC0 — already had a PAL body
- REVERTED `switchThread` w2 @ 0x001A5DB8 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)

### ito/mpeg/mv_readbuf
- PRE-MATCHED `readBufBeginGet` w1 @ 0x001A6938 — already had a PAL body
- PRE-MATCHED `readBufBeginPut` w1 @ 0x001A68C8 — already had a PAL body
- REVERTED `readBufEndGet` w1 @ 0x001A6980 — [codegen] ito/mpeg/mv_readbuf.c:3: mv_defs.h: No such file or directory
- PRE-MATCHED `readBufEndPut` w1 @ 0x001A68F8 — already had a PAL body

### ito/mpeg/mv_strfile
- PRE-MATCHED `strFileClose` w2 @ 0x001A69D8 — already had a PAL body
- REVERTED `strFileOpen` w3 @ 0x001A69A0 — [codegen] ito/mpeg/mv_strfile.c:3: mv_defs.h: No such file or directory
- REVERTED `strFileRead` w2 @ 0x001A69F8 — [codegen] ito/mpeg/mv_strfile.c:3: mv_defs.h: No such file or directory

### ito/mpeg/mv_sub
- PRE-MATCHED `ErrMessage` w2 @ 0x00259338 — already had a PAL body
- PRE-MATCHED `copy2area` w1 @ 0x00259348 — already had a PAL body

### ito/mpeg/mv_vibuf
- REVERTED `func_00259480` w1 @ 0x00259480 — [codegen] insn 4: expected `jal	0 <func_00259480>` built `jal	1028 <func_0025A4A8>`
- PRE-MATCHED `func_0025A4A8` w2 @ 0x0025A4A8 — already had a PAL body
- PORTED `viBufAddDMA` w1 @ 0x00259948 <- aug6 common/src/GobjProc:func_0023C310 (6 syms rebound)
- PRE-MATCHED `viBufCount` w1 @ 0x0025A578 — already had a PAL body
- PORTED `viBufDelete` w1 @ 0x0025A4B8 <- aug6 common/src/GobjProc:func_0023CE80 (4 syms rebound)
- PORTED `viBufEndPut` w1 @ 0x002598F8 <- aug6 common/src/GobjProc:func_0023C2C0 (3 syms rebound)
- PORTED `viBufFlush` w1 @ 0x0025A158 <- aug6 common/src/GobjProc:func_0023CB20 (3 syms rebound)
- PORTED `viBufReset` w1 @ 0x00259678 <- aug6 common/src/GobjProc:func_0023C040 (2 syms rebound)
- PORTED `viBufRestartDMA` w1 @ 0x00259D70 <- aug6 common/src/GobjProc:func_0023C738 (4 syms rebound)
- PORTED `viBufStopDMA` w1 @ 0x00259BE8 <- aug6 common/src/GobjProc:func_0023C5B0 (4 syms rebound)

### ito/mpeg/mv_videodec
- PRE-MATCHED `Free` w2 @ 0x001A6F80 — already had a PAL body
- REVERTED `free_buf` w1 @ 0x001A6A18 — [codegen] ito/mpeg/mv_videodec.c: In function `videoDecIsFlushed':
- PRE-MATCHED `mpegError` w1 @ 0x001A70A8 — already had a PAL body
- PRE-MATCHED `mpegNodata` w1 @ 0x001A70D0 — already had a PAL body
- PRE-MATCHED `mpegRestartDMA` w2 @ 0x001A7120 — already had a PAL body
- PRE-MATCHED `mpegStopDMA` w2 @ 0x001A7100 — already had a PAL body
- PRE-MATCHED `mpegTS` w1 @ 0x001A7140 — already had a PAL body
- PRE-MATCHED `videoDecAbort` w1 @ 0x001A6FF0 — already had a PAL body
- PRE-MATCHED `videoDecBeginPut` w2 @ 0x001A6B68 — already had a PAL body
- REVERTED `videoDecCreate` w3 @ 0x001A6A20 — [codegen] ito/mpeg/mv_videodec.c: In function `videoDecIsFlushed':
- PRE-MATCHED `videoDecDelete` w1 @ 0x001A6F90 — already had a PAL body
- PRE-MATCHED `videoDecEndPut` w2 @ 0x001A6B70 — already had a PAL body
- PRE-MATCHED `videoDecGetState` w1 @ 0x001A7000 — already had a PAL body
- PRE-MATCHED `videoDecIsFlushed` w1 @ 0x001A7008 — already had a PAL body
- PRE-MATCHED `videoDecMain` w1 @ 0x001A7058 — already had a PAL body
- PRE-MATCHED `videoDecSetStream` w2 @ 0x001A6FD0 — already had a PAL body

### ito/mpeg/mv_vobuf
- PRE-MATCHED `func_001A7318` w2 @ 0x001A7318 — already had a PAL body
- PRE-MATCHED `voBufDecCount` w1 @ 0x001A7458 — already had a PAL body
- PRE-MATCHED `voBufDelete` w2 @ 0x001A7310 — already had a PAL body
- REVERTED `voBufGetData` w1 @ 0x001A73C8 — [codegen] insn 5: expected `lui	v0,0x19` built `lui	v0,0x15`
- REVERTED `voBufGetTag` w1 @ 0x001A7400 — [codegen] insn 5: expected `lui	a2,0xc` built `lui	a2,0xa`
- REVERTED `voBufIncCount` w1 @ 0x001A7350 — [codegen] insn 6: expected `lui	v0,0xc` built `lui	v0,0xa`
- PRE-MATCHED `voBufIsFull` w1 @ 0x001A7338 — already had a PAL body
- PRE-MATCHED `voBufReset` w1 @ 0x001A7328 — already had a PAL body

### sound/s_init
- PRE-MATCHED `Ee2Iop` w1 @ 0x00145EB8 — already had a PAL body
- PRE-MATCHED `debug_req` w1 @ 0x00146AD0 — already had a PAL body
- PRE-MATCHED `func_00146778` w1 @ 0x00146778 — already had a PAL body
- PRE-MATCHED `soundAllocIopFree` w2 @ 0x00143788 — already had a PAL body
- PRE-MATCHED `soundAllocIopHeap` w3 @ 0x00143728 — already had a PAL body
- PRE-MATCHED `soundBufAdpcmFree` w1 @ 0x00146098 — already had a PAL body
- PRE-MATCHED `soundBufSegFree` w3 @ 0x00143C50 — already had a PAL body
- PRE-MATCHED `soundDataAreaSearch` w1 @ 0x001460B8 — already had a PAL body
- REVERTED `soundDataOpen` w3 @ 0x00144010 — [codegen] insn 12: expected `addiu	a1,zero,623` built `addiu	a1,zero,605`
- PRE-MATCHED `soundDataSegAllClose` w1 @ 0x00144340 — already had a PAL body
- PRE-MATCHED `soundHDDataSet` w3 @ 0x00146248 — already had a PAL body
- PRE-MATCHED `soundOutputModeSet` w1 @ 0x001436A0 — already had a PAL body
- PRE-MATCHED `soundReverbDepthGet` w1 @ 0x00145F78 — already had a PAL body
- PRE-MATCHED `soundReverbDepthSet` w1 @ 0x001436B0 — already had a PAL body
- REVERTED `soundSQDataSet` w3 @ 0x001463A8 — [redefinition] sound/s_init.c:29: redefinition of `hd_search'
- PRE-MATCHED `soundSeDefPitchSet` w1 @ 0x00145638 — already had a PAL body
- PRE-MATCHED `soundSeDefPlay` w1 @ 0x00146508 — already had a PAL body
- PRE-MATCHED `soundSeDefPlayWithVolumeRate` w1 @ 0x00146560 — already had a PAL body
- PRE-MATCHED `soundSeDefStop` w2 @ 0x00145628 — already had a PAL body
- PRE-MATCHED `soundSeDefStopNoRelease` w1 @ 0x00145630 — already had a PAL body
- PRE-MATCHED `soundSeDefVolumeRateGet` w1 @ 0x001465B0 — already had a PAL body
- PRE-MATCHED `soundSeDefVolumeRateSet` w1 @ 0x001465F0 — already had a PAL body
- PRE-MATCHED `soundSeGroupGet` w1 @ 0x001466C8 — already had a PAL body
- PRE-MATCHED `soundSeGroupStop` w1 @ 0x00146628 — already had a PAL body
- REVERTED `soundSeKindBuild` w3 @ 0x001468E8 — [codegen] insn 1: expected `addiu	a1,zero,1419` built `addiu	a1,zero,1388`
- PRE-MATCHED `soundSePlayModeStop` w1 @ 0x001466F0 — already had a PAL body
- PRE-MATCHED `soundSeSemiCommonLoadChk` w2 @ 0x001469A8 — already had a PAL body
- PRE-MATCHED `soundVBlank` w1 @ 0x00146888 — already had a PAL body

### sound/soundManager
- REVERTED `sndBgmReadyNextStage` w1 @ 0x00146B68 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x60 (out-of-line helper or extra code)
- PRE-MATCHED `sndInit` w3 @ 0x00146BC8 — already had a PAL body

### src/Basic
- REVERTED `dma_init` w1 @ 0x00205DA8 — [codegen] insn 25: expected `<end>` built `sll	zero,zero,0x0`
- PRE-MATCHED `freeseki` w1 @ 0x00205F18 — already had a PAL body
- PRE-MATCHED `malloc_GetPartition` w2 @ 0x00205E30 — already had a PAL body
- PRE-MATCHED `malloc_MemCpy` w2 @ 0x00205E20 — already had a PAL body
- PRE-MATCHED `malloc_SetPartition` w2 @ 0x00205E28 — already had a PAL body
- REVERTED `mallocseki` w1 @ 0x00205E38 — [callee-sig-conflict] src/Basic.c:75: conflicting types for `iosMallocDebug'
- PRE-MATCHED `mallocsekistage` w1 @ 0x00205F40 — already had a PAL body
- PRE-MATCHED `matrix_init` w1 @ 0x00205E10 — already had a PAL body
- REVERTED `reallocseki` w1 @ 0x00205F88 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- PRE-MATCHED `resetmallocseki` w2 @ 0x00205F38 — already had a PAL body

### src/BgAnimation
- PRE-MATCHED `bga_GetCameraMatrix` w1 @ 0x0020A610 — already had a PAL body
- PRE-MATCHED `bga_GetZoom` w1 @ 0x0020AA88 — already had a PAL body
- PRE-MATCHED `bga_InitBGA` w2 @ 0x0020AA20 — already had a PAL body
- REVERTED `bga_InitSdfCamera` w3 @ 0x0020A658 — [codegen] insn 14: expected `addiu	a1,zero,1045` built `addiu	a1,zero,899`
- PORTED `bga_ResetAnimation` w1 @ 0x0020AA38 <- aug6 seki/src/DisplayFont:func_001F76C0 (5 syms rebound)
- PRE-MATCHED `bga_ResetCamera` w2 @ 0x0020A608 — already had a PAL body
- PRE-MATCHED `bga_SetCameraForceOff` w2 @ 0x0020AA10 — already had a PAL body
- PRE-MATCHED `bga_SetUniqAnimationFlag` w2 @ 0x0020AA30 — already had a PAL body
- REVERTED `bga_addLightning` w3 @ 0x00209E50 — [codegen] src/BgAnimation.c:82: invalid lvalue in increment

### src/DObj
- PRE-MATCHED `FreeDObj` w2 @ 0x001A8318 — already had a PAL body
- PORTED `LinkParentOfDObj` w1 @ 0x001A8320 <- aug6 common/src/DObj:func_0019CAA8 (2 syms rebound)
- PRE-MATCHED `UnlinkParentOfDObj` w3 @ 0x001A8368 — already had a PAL body
- REVERTED `initInitialInverseMatrix` w3 @ 0x001A7D40 — [codegen] insn 7: expected `addiu	a3,zero,333` built `addiu	a3,zero,332`

### src/DisplayFont
- PRE-MATCHED `font_GetHeight` w1 @ 0x0020B410 — already had a PAL body
- PRE-MATCHED `font_GetWidth` w1 @ 0x0020B408 — already had a PAL body
- PORTED `font_Init` w1 @ 0x0020B438 <- aug6 seki/src/DisplayList:dl_PushPriority (6 syms rebound)

### src/DisplayList
- PRE-MATCHED `dl_Clear` w1 @ 0x0020B570 — already had a PAL body
- PRE-MATCHED `dl_Debug` w1 @ 0x0020B810 — already had a PAL body
- PRE-MATCHED `dl_GetPri` w2 @ 0x0020BAD0 — already had a PAL body
- PRE-MATCHED `dl_OpenDma` w1 @ 0x0020BA38 — already had a PAL body
- PORTED `dl_Out` w1 @ 0x0020B988 <- aug6 seki/src/DisplayList:func_001F8660 (3 syms rebound)
- REVERTED `dl_PopPriority` w3 @ 0x0020B788 — [codegen] insn 10: expected `addiu	a1,zero,552` built `addiu	a1,zero,544`
- REVERTED `dl_PushPriority` w3 @ 0x0020B6F8 — [codegen] insn 11: expected `addiu	a1,zero,534` built `addiu	a1,zero,526`
- PRE-MATCHED `dl_SetDLPriority` w1 @ 0x0020BA10 — already had a PAL body
- PRE-MATCHED `dl_Swap` w1 @ 0x0020B5E8 — already had a PAL body

### src/DisplayP2O
- PRE-MATCHED `p2o_DispShadowVolume` w2 @ 0x0010EC28 — already had a PAL body
- PRE-MATCHED `p2o_DispVU1` w2 @ 0x0010EC80 — already had a PAL body
- PRE-MATCHED `p2o_DispVU1DObj` w2 @ 0x0010EC60 — already had a PAL body
- PRE-MATCHED `p2o_DispVU1DObjMulti` w2 @ 0x0010EC68 — already had a PAL body
- PRE-MATCHED `p2o_DispVU1Default` w2 @ 0x0010EC88 — already had a PAL body
- PRE-MATCHED `p2o_DispVU1Multi` w2 @ 0x0010EC70 — already had a PAL body
- PRE-MATCHED `p2o_DispVU1MultiDefault` w2 @ 0x0010EC78 — already had a PAL body
- PRE-MATCHED `p2o_HideDispVU1` w1 @ 0x0010EC30 — already had a PAL body
- REVERTED `p2o_MakePacket` w3 @ 0x0010EC18 — [codegen] insn 1: expected `lw	v1,2132(v0)` built `lw	v1,2064(v0)`
- PRE-MATCHED `p2o_SetDefaultEnviroment` w2 @ 0x0010ECA0 — already had a PAL body
- PRE-MATCHED `p2o_TransMicroProgram` w1 @ 0x0010EC90 — already had a PAL body

### src/DmaPacket
- PRE-MATCHED `dpk_CheckBufferSize` w1 @ 0x0020BBA8 — already had a PAL body
- REVERTED `dpk_Init` w1 @ 0x0020BAD8 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PRE-MATCHED `func_0020BB70` w1 @ 0x0020BB70 — already had a PAL body

### src/EnemyInit
- PRE-MATCHED `enemy_GetPositionTable` w1 @ 0x0020BF18 — already had a PAL body

### src/FileManager
- PORTED `file_LoadFile` w2 @ 0x0010F630 <- aug6 seki/src/FileManager:func_0010F958 (2 syms rebound)

### src/GifPacket
- PRE-MATCHED `_IsInScreen` w1 @ 0x001124F0 — already had a PAL body
- PRE-MATCHED `gif_CheckOpen` w2 @ 0x00111BD8 — already had a PAL body
- REVERTED `gif_EndPacket` w1 @ 0x0010F6A8 — [callee-sig-conflict] src/GifPacket.c:107: conflicting types for `D_004EE6F0__pn'
- PRE-MATCHED `gif_Init` w2 @ 0x00111B48 — already had a PAL body
- PRE-MATCHED `gif_SetAlpha` w1 @ 0x00112240 — already had a PAL body
- PRE-MATCHED `gif_SetGsReg` w1 @ 0x00111BB0 — already had a PAL body
- PRE-MATCHED `gif_SetZTest` w1 @ 0x001123E0 — already had a PAL body
- PRE-MATCHED `gif_SetZWrite` w3 @ 0x00112420 — already had a PAL body
- REVERTED `gif_StartPacket` w2 @ 0x0010F650 — [callee-sig-conflict] src/GifPacket.c:98: conflicting types for `D_004EE6F0__pn'
- REVERTED `gif_StartPacketPath1` w2 @ 0x0010F788 — [callee-sig-conflict] src/GifPacket.c:98: conflicting types for `D_004EE6F0__pn'
- PRE-MATCHED `gif_StartPacketPri` w2 @ 0x00111B50 — already had a PAL body
- PRE-MATCHED `gif_StartPacketPriPath1` w2 @ 0x00111B80 — already had a PAL body

### src/GobjProc
- PORTED `CreateGObj` w1 @ 0x0025A898 <- aug6 common/src/PObj:func_0023D260 (8 syms rebound)
- PRE-MATCHED `GetGObjId` w1 @ 0x0025A6E0 — already had a PAL body
- PRE-MATCHED `GetGObjP` w2 @ 0x0025A6C8 — already had a PAL body
- PRE-MATCHED `GetMaxGObj` w2 @ 0x0025A6C0 — already had a PAL body
- PRE-MATCHED `PrintGObjID` w1 @ 0x0025A728 — already had a PAL body
- REVERTED `ResetGObjProc` w2 @ 0x0025A6B8 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)

### src/GsBase
- PRE-MATCHED `gsb_GetBGColor` w1 @ 0x00116250 — already had a PAL body
- PRE-MATCHED `gsb_SetBGColor` w1 @ 0x001161F8 — already had a PAL body
- PRE-MATCHED `gsb_SetZoom` w1 @ 0x00116338 — already had a PAL body
- PRE-MATCHED `gsb_setNormalReg` w1 @ 0x00113BA0 — already had a PAL body
- PRE-MATCHED `gsb_setParticleReg` w1 @ 0x00113CF0 — already had a PAL body
- PRE-MATCHED `gsb_setSemitransReg` w1 @ 0x00113C08 — already had a PAL body
- PRE-MATCHED `gsb_setSpecularReg` w1 @ 0x00113C78 — already had a PAL body

### src/Light
- PRE-MATCHED `light_InitLight` w2 @ 0x00118E18 — already had a PAL body
- PRE-MATCHED `light_KillAllAmbient` w1 @ 0x00118E90 — already had a PAL body
- PORTED `light_KillAllFixLight` w1 @ 0x00118E30 <- aug6 seki/src/Light:func_00117B90 (4 syms rebound)

### src/Matrix
- PRE-MATCHED `_AddVector` w1 @ 0x00119B28 — already had a PAL body
- PRE-MATCHED `_AddVectorXYZ` w1 @ 0x00119B40 — already had a PAL body
- PRE-MATCHED `_ApplyCurrentMatrix` w1 @ 0x00119988 — already had a PAL body
- PRE-MATCHED `_ApplyMatrix` w1 @ 0x00119E00 — already had a PAL body
- PRE-MATCHED `_ClearTransCurrentMatrix` w1 @ 0x001195A8 — already had a PAL body
- PRE-MATCHED `_CopyIVector` w2 @ 0x00119C28 — already had a PAL body
- PRE-MATCHED `_CopyMatrix` w1 @ 0x00119D60 — already had a PAL body
- PRE-MATCHED `_CopyVector` w2 @ 0x00119C18 — already had a PAL body
- PRE-MATCHED `_FTOI0Vector` w1 @ 0x00119C00 — already had a PAL body
- PRE-MATCHED `_FTOI4Vector` w1 @ 0x00119BE8 — already had a PAL body
- PRE-MATCHED `_GetCurrentMatrix` w1 @ 0x00119888 — already had a PAL body
- PRE-MATCHED `_GetCurrentMatrixTrans` w1 @ 0x001198A0 — already had a PAL body
- PRE-MATCHED `_GetLength` w1 @ 0x00119CC8 — already had a PAL body
- PRE-MATCHED `_GetLengthXY` w1 @ 0x00119D00 — already had a PAL body
- PRE-MATCHED `_GetLengthXZ` w1 @ 0x00119D30 — already had a PAL body
- PRE-MATCHED `_GetNorm` w1 @ 0x00119C98 — already had a PAL body
- PRE-MATCHED `_GetRandom` w1 @ 0x0011A230 — already had a PAL body
- PRE-MATCHED `_GetRandomVector` w1 @ 0x0011A248 — already had a PAL body
- PRE-MATCHED `_GetRandomVector0` w1 @ 0x0011A268 — already had a PAL body
- PRE-MATCHED `_InitCurrentMatrix` w2 @ 0x00119508 — already had a PAL body
- PRE-MATCHED `_InitRandom` w1 @ 0x0011A210 — already had a PAL body
- PRE-MATCHED `_InnerProduct` w1 @ 0x00119AD8 — already had a PAL body
- PRE-MATCHED `_InterVector` w1 @ 0x00119C48 — already had a PAL body
- PRE-MATCHED `_InterVectorXYZ` w1 @ 0x00119C70 — already had a PAL body
- REVERTED `_InversMatrix` — [period-as-dialect] inline asm spells $ACC; the period assembler (ee-as 2.9-991111) rejects it (post-hoc, bisected from the chunk-1 ninja failure)
- PRE-MATCHED `_InverseCurrentMatrix` w1 @ 0x00119A58 — already had a PAL body
- PRE-MATCHED `_MakeLightColorMatrix` w1 @ 0x0011A1D8 — already had a PAL body
- REVERTED `_MakeNormalLightMatrix` w3 @ 0x0011A0F8 — [crutch] crutch: bare register-variable pin `register void *p2 __asm__("$`
- PRE-MATCHED `_MulCurrentMatrixL` w1 @ 0x00119930 — already had a PAL body
- PRE-MATCHED `_MulCurrentMatrixR` w1 @ 0x001198C8 — already had a PAL body
- PRE-MATCHED `_MulMatrix` w1 @ 0x00119D88 — already had a PAL body
- PRE-MATCHED `_NormalizeVector` w1 @ 0x00119AA8 — already had a PAL body
- PRE-MATCHED `_OuterProduct` w1 @ 0x00119B08 — already had a PAL body
- PRE-MATCHED `_PopCurrentMatrix` w1 @ 0x00119560 — already had a PAL body
- PRE-MATCHED `_PushCurrentMatrix` w1 @ 0x00119548 — already had a PAL body
- REVERTED `_RotCurrentMatrixX` — [period-as-dialect] inline asm spells $ACC; the period assembler (ee-as 2.9-991111) rejects it (post-hoc, bisected from the chunk-1 ninja failure)
- PRE-MATCHED `_RotCurrentMatrixY` w1 @ 0x00119678 — already had a PAL body
- PRE-MATCHED `_RotCurrentMatrixZ` w1 @ 0x00119738 — already had a PAL body
- PRE-MATCHED `_RotTransCurrentMatrix` w1 @ 0x0011A280 — already had a PAL body
- PRE-MATCHED `_RotTransPersCurrentMatrix` w1 @ 0x001199A8 — already had a PAL body
- PRE-MATCHED `_ScaleCurrentMatrix` w1 @ 0x001197F8 — already had a PAL body
- REVERTED `_ScaleMatrixV` w1 @ 0x00119F38 — [codegen] [§2.7] FP register letter swap ($fA ↔ $fB, otherwise identical)
- PRE-MATCHED `_ScaleVector` w1 @ 0x00119B88 — already had a PAL body
- PRE-MATCHED `_ScaleVector2XYZ` w1 @ 0x00119BC8 — already had a PAL body
- PRE-MATCHED `_ScaleVectorXYZ` w1 @ 0x00119BA8 — already had a PAL body
- REVERTED `_SetCameraMatrix` — [period-as-dialect] inline asm spells $ACC; the period assembler (ee-as 2.9-991111) rejects it (post-hoc, bisected from the chunk-1 ninja failure)
- PRE-MATCHED `_SetCurrentMatrix` w1 @ 0x001198B0 — already had a PAL body
- PRE-MATCHED `_SetTransCurrentMatrix` w1 @ 0x00119598 — already had a PAL body
- PRE-MATCHED `_Sqrt` w1 @ 0x001194E8 — already had a PAL body
- PRE-MATCHED `_SubVector` w1 @ 0x00119B58 — already had a PAL body
- PRE-MATCHED `_SubVectorXYZ` w1 @ 0x00119B70 — already had a PAL body
- PRE-MATCHED `_TransCurrentMatrix` w1 @ 0x00119578 — already had a PAL body
- PRE-MATCHED `_TransposeCurrentMatrix` w1 @ 0x001199D8 — already had a PAL body
- PRE-MATCHED `_TransposeMatrix` w1 @ 0x00119E80 — already had a PAL body
- PRE-MATCHED `_TransposeRotationCurrentMatrix` w1 @ 0x00119A28 — already had a PAL body
- PRE-MATCHED `_UnitCurrentMatrix` w2 @ 0x00119528 — already had a PAL body
- PRE-MATCHED `_UnitMatrix` w1 @ 0x00119E30 — already had a PAL body
- PRE-MATCHED `_UnitRotation` w1 @ 0x00119E58 — already had a PAL body
- PRE-MATCHED `_UnitVector` w1 @ 0x00119C38 — already had a PAL body

### src/MicroCode
- PORTED `mc_Init` w2 @ 0x0011A760 <- aug6 seki/src/Packet:pac_setVifCode (3 syms rebound)
- PRE-MATCHED `mc_Reset` w2 @ 0x0011A720 — already had a PAL body
- PRE-MATCHED `mc_TransMicroCode` w1 @ 0x0011A650 — already had a PAL body

### src/PObj
- PRE-MATCHED `FreePObj` w1 @ 0x0025B558 — already had a PAL body
- REVERTED `InitPObj` w3 @ 0x0025B3F8 — [codegen] insn 11: expected `jal	0 <InitPObj>` built `jal	428 <AllocPObj>`

### src/Packet
- SKIPPED `pac_DispQW` w2 @ 0x0011A7A0 — jtbl
- PRE-MATCHED `pac_DispVu1Memory` w1 @ 0x0011D788 — already had a PAL body
- PRE-MATCHED `pac_Dump` w1 @ 0x0011D728 — already had a PAL body
- PRE-MATCHED `pac_Init` w2 @ 0x0011D780 — already had a PAL body
- REVERTED `pac_MakePacket` w3 @ 0x0011D708 — [codegen] insn 0: expected `lw	v0,2132(a0)` built `lw	v0,2064(a0)`
- PORTED `pac_openDmaTag` w1 @ 0x0011BA00 <- aug6 seki/src/Packet:pac_setMaterialPacket (6 syms rebound)
- REVERTED `pac_setVifCode` w1 @ 0x0011BA70 — [codegen] insn 16: expected `j	0 <pac_setVifCode>` built `lw	a2,4(v0)`
- PRE-MATCHED `pac_setVifEndCode` w1 @ 0x0011BAB8 — already had a PAL body

### src/Primitive
- PRE-MATCHED `prim_DeleteParticle` w1 @ 0x0011F6A8 — already had a PAL body

### src/RegistPacket
- PRE-MATCHED `func_00121428` w1 @ 0x00121428 — already had a PAL body
- PRE-MATCHED `reg_DispObj2` w2 @ 0x00124440 — already had a PAL body
- PRE-MATCHED `reg_GetShinePri` w1 @ 0x00124488 — already had a PAL body
- PRE-MATCHED `reg_Init` w2 @ 0x00124480 — already had a PAL body
- PRE-MATCHED `reg_SetScissorSw` w2 @ 0x00124448 — already had a PAL body
- PRE-MATCHED `reg_TransTexturePacket` w1 @ 0x00124450 — already had a PAL body
- PRE-MATCHED `reg_chooseMicroCode` w1 @ 0x001205F8 — already had a PAL body
- PRE-MATCHED `reg_chooseReflectionMicroCode` w1 @ 0x00120638 — already had a PAL body
- PRE-MATCHED `reg_chooseSpecularMicroCode` w1 @ 0x00120620 — already had a PAL body
- PRE-MATCHED `reg_resetDissolve` w1 @ 0x00121730 — already had a PAL body
- PRE-MATCHED `reg_transMaterialPacket` w1 @ 0x001214D8 — already had a PAL body
- REVERTED `reg_transMicroCode` w3 @ 0x001205C0 — [codegen] insn 0: expected `lw	v0,2132(a0)` built `lw	v0,2064(a0)`

### src/Shadow
- PRE-MATCHED `__GetCameraPos` w1 @ 0x00125F40 — already had a PAL body
- REVERTED `shadow_DispCancel` w3 @ 0x00129DF8 — [codegen] insn 18: expected `lw	a1,2132(v0)` built `lw	a1,2064(v0)`
- PRE-MATCHED `shadow_KillShadow` w2 @ 0x00129DF0 — already had a PAL body
- PRE-MATCHED `shadow_Render` w1 @ 0x00125758 — already had a PAL body
- REVERTED `shadow_SetLength` w3 @ 0x00129EA0 — [codegen] insn 4: expected `lw	v0,2132(a0)` built `lw	v0,2064(a0)`
- REVERTED `shadow_getShadowVectorAverage` w3 @ 0x00125778 — [codegen] insn 1: expected `addiu	a1,a1,2144` built `addiu	a1,a1,2080`

### src/StageAnimation
- PORTED `stage_CheckAnimationFrame` w2 @ 0x0012C570 <- aug6 seki/src/StageAnimation:func_0012AA28 (5 syms rebound)
- PORTED `stage_CheckAnimationFrameIn` w2 @ 0x0012C860 <- aug6 seki/src/Texture:tex_setTexReg (5 syms rebound)
- PRE-MATCHED `stage_KillPlayBgAnimationIfOverMaxCount` w1 @ 0x0012C808 — already had a PAL body
- PRE-MATCHED `stage_SetCameraForceOff` w1 @ 0x0012C498 — already had a PAL body
- PRE-MATCHED `stage_SetFrameStep` w1 @ 0x0012C648 — already had a PAL body
- PRE-MATCHED `stage_SetLocalizeGeometry` w1 @ 0x0012C760 — already had a PAL body
- PRE-MATCHED `stage_SetLoopFlag` w1 @ 0x0012C600 — already had a PAL body
- PORTED `stage_SetParentOfGObj` w1 @ 0x0012C690 <- aug6 seki/src/StageAnimation:func_0012AB48 (3 syms rebound)
- PORTED `stage_SetParentOfGObjWithLocalRotationFlag` w1 @ 0x0012C6F8 <- aug6 seki/src/StageAnimation:func_0012ABB0 (3 syms rebound)

### src/StageManager
- PRE-MATCHED `CheckPoint` w1 @ 0x001A8E70 — already had a PAL body
- PRE-MATCHED `exit_stage` w1 @ 0x001A8590 — already had a PAL body
- REVERTED `stage_initialize` w1 @ 0x001A84E0 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- PRE-MATCHED `stgmgrForceSwitchWithFade` w1 @ 0x001A8DC8 — already had a PAL body
- PRE-MATCHED `stgmgrNextStagePreLoadDiskNotReady` w2 @ 0x001A8EC0 — already had a PAL body
- PRE-MATCHED `stgmgrNextStagePreLoadDistBoyMode` w2 @ 0x001A8E58 — already had a PAL body
- REVERTED `stgmgrNextStagePreLoadEntry` w3 @ 0x001A8960 — [codegen] insn 0: expected `addiu	v0,zero,404` built `addiu	v0,zero,400`
- PRE-MATCHED `stgmgrNextStagePreLoadForceNoCancel` w2 @ 0x001A8E68 — already had a PAL body
- PRE-MATCHED `stgmgrNextStagePreLoadForceStageSet` w1 @ 0x001A8E40 — already had a PAL body

### src/Texture
- PRE-MATCHED `tex_GetTWTH` w1 @ 0x001319C8 — already had a PAL body
- PRE-MATCHED `tex_GetTexExtData` w2 @ 0x00131B48 — already had a PAL body
- PRE-MATCHED `tex_GetTextureData` w2 @ 0x00131AF0 — already had a PAL body
- PRE-MATCHED `tex_GetTextureName` w2 @ 0x00131B08 — already had a PAL body
- PRE-MATCHED `tex_GetTextureNum` w2 @ 0x00131E88 — already had a PAL body
- PRE-MATCHED `tex_GetVramFreeAddress` w1 @ 0x00131B60 — already had a PAL body
- PRE-MATCHED `tex_InitTexture` w2 @ 0x00131A18 — already had a PAL body
- PRE-MATCHED `tex_LoadTexture` w2 @ 0x00131A38 — already had a PAL body
- PRE-MATCHED `tex_RemakeRegistersSampleMin` w1 @ 0x00132078 — already had a PAL body
- PRE-MATCHED `tex_SetSamplingType` w1 @ 0x00131B20 — already had a PAL body
- PRE-MATCHED `tex_transRegister` w1 @ 0x0012D608 — already had a PAL body

### src/a_p_1
- PRE-MATCHED `zAxisRotFitting` w1 @ 0x001C2BB8 — already had a PAL body

### src/access
- PRE-MATCHED `GetDataFileName` w3 @ 0x00257218 — already had a PAL body

### src/act
- REVERTED `ActSetStartBrainStatus` w3 @ 0x002148D8 — [codegen] insn 2: expected `sw	a1,1096(v0)` built `sw	a1,1080(v0)`
- PRE-MATCHED `ConvertStickToAbsCoord` w2 @ 0x00214860 — already had a PAL body
- PRE-MATCHED `_ACTRun` w1 @ 0x00214738 — already had a PAL body
- PRE-MATCHED `_ACTWait` w1 @ 0x00214780 — already had a PAL body
- REVERTED `actChangeActBrain` w1 @ 0x002129A8 — [codegen] insn 9: expected `jal	0 <actChangeActBrain>` built `jal	1e0 <actCreateSubThread>`
- PRE-MATCHED `actChangeActMain` w1 @ 0x00212A38 — already had a PAL body
- PRE-MATCHED `actCreateMotionThread` w1 @ 0x00212B00 — already had a PAL body
- PRE-MATCHED `actCreateSubThreadGOppArg` w1 @ 0x00214820 — already had a PAL body
- PRE-MATCHED `actInitialize_geo` w1 @ 0x002146E8 — already had a PAL body
- PRE-MATCHED `actSetInterrupt` w1 @ 0x00214858 — already had a PAL body
- PORTED `actWaitCondition` w1 @ 0x002148F0 <- aug6 fumi/src/act2:func_002013B0 (3 syms rebound)

### src/act-env
- PORTED `CheckWallAttributeEdegWall` w1 @ 0x002113E8 <- aug6 fumi/src/act-env:func_001FE2F8 (4 syms rebound)

### src/act-game
- REVERTED `ACTCharctrl_Lock` w3 @ 0x0014CE48 — [codegen] insn 1: expected `lui	v1,0xfffe` built `addiu	v1,zero,-2049`
- REVERTED `ACTCharctrl_Unlock` w3 @ 0x0014CE90 — [codegen] insn 2: expected `dsll32	v1,v1,0x1` built `dsll	v1,v1,0x1c`
- PRE-MATCHED `ACTCheckCollis_CI` w1 @ 0x0014D510 — already had a PAL body
- PRE-MATCHED `ACTCheckCollis_W` w1 @ 0x0014D3E0 — already had a PAL body
- PRE-MATCHED `ACTGameViewSimple_Check` w1 @ 0x0014DB48 — already had a PAL body
- PRE-MATCHED `ACTGameView_Check` w1 @ 0x0014DB00 — already had a PAL body
- PRE-MATCHED `ACTGameView_Init` w1 @ 0x0014CE30 — already had a PAL body
- REVERTED `ACTGame_CheckPriInputFrame` w3 @ 0x0014DFC8 — [codegen] insn 2: expected `addiu	a0,zero,404` built `addiu	a0,zero,400`
- REVERTED `ACTGame_ConnectHand` w3 @ 0x0014CEB8 — [codegen] insn 5: expected `addiu	a2,zero,5` built `addiu	a2,zero,4`
- REVERTED `ACTGame_DeleteActorInformation` w1 @ 0x00146D10 — [codegen] insn 3: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `ACTGame_DisconnectHand` w3 @ 0x0014CF30 — [codegen] insn 5: expected `addiu	a2,zero,5` built `addiu	a2,zero,4`
- PRE-MATCHED `ACTGame_DisconnectHand_WithMail` w2 @ 0x00147218 — already had a PAL body
- PRE-MATCHED `ACTGame_GetMotOrientFromWeapon` w1 @ 0x0014DB90 — already had a PAL body
- PRE-MATCHED `ACTGame_GetNearestGObj` w1 @ 0x0014DC48 — already had a PAL body
- REVERTED `ACTGame_LwsEffectInit` w3 @ 0x0014E118 — [codegen] insn 8: expected `lw	a0,1664(v1)` built `lw	a0,1648(v1)`
- REVERTED `ACTGame_LwsEffectProcess` w3 @ 0x001476E8 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `ACTGame_NoWeapon` w3 @ 0x0014DBD8 — [codegen] insn 4: expected `lw	a0,336(v0)` built `lw	a0,304(v0)`
- REVERTED `ACTGame_SendSoundMail` w3 @ 0x0014E060 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `ACTGame_SetMotionPlaySpeedRatio_Clear` w3 @ 0x0014E770 — [codegen] insn 3: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `ACTGame_SetMotionPlaySpeedRatio_Exec` w3 @ 0x0014E790 — [codegen] insn 6: expected `lw	a3,1664(v0)` built `lw	a3,1648(v0)`
- REVERTED `ACTGame_SetMotionPlaySpeedRatio_Reserve` w3 @ 0x0014DEC0 — [codegen] insn 1: expected `lw	v1,1664(v1)` built `lw	v1,1648(v1)`
- PRE-MATCHED `ACTGame_StageChangeGObjDirect` w1 @ 0x0014CB48 — already had a PAL body
- PRE-MATCHED `ACTGame_StageChangeGObjID` w1 @ 0x0014CAC8 — already had a PAL body
- REVERTED `ACTGame_TryConnectHand` w3 @ 0x001471D8 — [codegen] insn 3: expected `addiu	a2,zero,5` built `addiu	a2,zero,4`
- REVERTED `ACTGame_TryDisconnectHand` w3 @ 0x001471F8 — [codegen] insn 2: expected `addiu	a2,zero,5` built `addiu	a2,zero,4`
- REVERTED `ACTGame_isHangChain` w3 @ 0x0014D248 — [codegen] insn 3: expected `lw	a0,52(a1)` built `lw	a0,48(a1)`
- PRE-MATCHED `ACTGame_isWeaponCombustible` w1 @ 0x0014DC20 — already had a PAL body
- PRE-MATCHED `ACTGame_isWeaponEnableCatchfire` w1 @ 0x0014D290 — already had a PAL body
- REVERTED `ACTLookTarget_Init` w3 @ 0x0014DCE0 — [codegen] insn 1: expected `sw	zero,172(v0)` built `sw	zero,140(v0)`
- REVERTED `ACTParaStatus_Clear` w3 @ 0x00147A20 — [codegen] insn 2: expected `j	0 <ACTParaStatus_Clear>` built `j	70a8 <_ACTParaStatus_Set>`
- PORTED `GetGirlPositionAtThisStage` w1 @ 0x0014E860 <- aug6 fumi/src/act-wish:func_0014A4D0 (4 syms rebound)
- PRE-MATCHED `GetSkeltonPosition` w1 @ 0x0014CC80 — already had a PAL body
- REVERTED `PAIR_GetPosition_BOY` w3 @ 0x0014CFB8 — [codegen] insn 2: expected `lwc1	$f0,1280(v0)` built `lwc1	$f0,1264(v0)`
- REVERTED `PAIR_GetPosition_BOY_DITCH` w3 @ 0x0014D150 — [codegen] insn 2: expected `lwc1	$f0,1296(v0)` built `lwc1	$f0,1280(v0)`
- REVERTED `PAIR_IsStatus_BOY_PULL` w3 @ 0x0014CFF8 — [codegen] insn 2: expected `lw	v1,52(v1)` built `lw	v1,48(v1)`
- REVERTED `PAIR_IsStatus_BOY_WAIT` w3 @ 0x0014D0F0 — [codegen] insn 2: expected `addiu	v1,zero,78` built `addiu	v1,zero,75`
- PRE-MATCHED `SetDirectRootPositionWithNodePointLimit` w1 @ 0x0014CCF8 — already had a PAL body
- REVERTED `_ACTCharStatus_Check` w3 @ 0x0014DE88 — [codegen] insn 3: expected `ld	v0,88(v1)` built `lw	v0,84(v1)`
- REVERTED `_ACTCharStatus_Clear` w3 @ 0x00147BE8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `_ACTCharStatus_Exec` w2 @ 0x0014DEA8 — already had a PAL body
- PRE-MATCHED `_ACTCharStatus_Init` w3 @ 0x0014DDF8 — already had a PAL body
- PRE-MATCHED `_ACTGame_GetParamF` w1 @ 0x0014DEE8 — already had a PAL body
- REVERTED `_ACTLookTarget_Set` w3 @ 0x0014DCF8 — [codegen] insn 4: expected `sw	zero,172(v1)` built `sw	zero,140(v1)`
- REVERTED `_ACTParaStatus_Check` w3 @ 0x0014DDE0 — [codegen] insn 1: expected `ld	v0,144(v1)` built `lw	v0,128(v1)`
- REVERTED `_ACTSetEnemyDisappearSpeed` w3 @ 0x0014DEB0 — [codegen] insn 1: expected `lw	v1,1672(v0)` built `lw	v1,1656(v0)`

### src/act-parallel-control
- PRE-MATCHED `ActPara_DebugOut` w2 @ 0x0014EA60 — already had a PAL body
- PRE-MATCHED `ActPara_GetDefTbl` w2 @ 0x0014EA38 — already had a PAL body
- REVERTED `ActPara_InitSystem` w3 @ 0x0014E9F8 — [codegen] insn 4: expected `addiu	a0,zero,85` built `addiu	a0,zero,70`
- PRE-MATCHED `ActPara_StatusToFlag` w1 @ 0x0014EA48 — already had a PAL body

### src/act2
- PRE-MATCHED `actDummy` w2 @ 0x00214B08 — already had a PAL body

### src/act_a_p_1
- REVERTED `GetAP1AIMode` w3 @ 0x001C56E0 — [unresolved-symbol] unresolved-symbol: insn 11 `D_004BA260`: pal symbol D_00645A30 (0x00645A30) undefined
- PRE-MATCHED `IsActCharDead` w1 @ 0x001C56A0 — already had a PAL body
- REVERTED `SetAP1DeadStatus` w3 @ 0x001C5258 — [codegen] insn 11: expected `sw	v1,52(a2)` built `sw	v1,48(a2)`
- REVERTED `SetAP1HostGObj` w3 @ 0x001C56C0 — [codegen] insn 2: expected `sw	a1,168(v0)` built `sw	a1,136(v0)`
- REVERTED `SetAP1PriorLevel` w3 @ 0x001C56D0 — [codegen] insn 2: expected `sw	a1,172(v0)` built `sw	a1,140(v0)`
- PRE-MATCHED `attackAI` w2 @ 0x001C5748 — already had a PAL body
- PRE-MATCHED `func_001C5250` w1 @ 0x001C5250 — already had a PAL body
- PRE-MATCHED `jumpAI` w2 @ 0x001C5720 — already had a PAL body
- PRE-MATCHED `subAP1Control` w2 @ 0x001C5770 — already had a PAL body

### src/act_bird
- PRE-MATCHED `BirdAI` w2 @ 0x001A00E8 — already had a PAL body
- PORTED `_ACTSendMailToBird` w2 @ 0x0019FE98 <- aug6 ito/src/act_bird:birdBeforeFunc (2 syms rebound)
- PRE-MATCHED `_ACTSendMailToBirdAll` w1 @ 0x001A00F0 — already had a PAL body
- REVERTED `func_0019FD30` w3 @ 0x0019FD30 — [codegen] 2026-08-05; it manufactured 8 false delay-slot matches).
- PRE-MATCHED `func_0019FE30` w2 @ 0x0019FE30 — already had a PAL body
- REVERTED `func_0019FE38` w3 @ 0x0019FE38 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `vector_angle_degree` w1 @ 0x0019FEA0 — already had a PAL body

### src/actressLight
- PORTED `SetActressLight` w1 @ 0x001C5780 <- aug6 sugipon/src/attackCheckBoundary:InitAttackCheckBoundaryGeo (7 syms rebound)

### src/attackCheckBoundary
- PRE-MATCHED `AttackCheckBoundaryGeo` w1 @ 0x001C5D50 — already had a PAL body
- PRE-MATCHED `AttackCheckBoundaryManagerDL` w2 @ 0x001C5CF8 — already had a PAL body
- REVERTED `AttackCheckBoundaryManagerGeo` w3 @ 0x001C5C88 — [codegen] insn 1: expected `lw	t1,2096(v1)` built `lw	t1,2032(v1)`
- REVERTED `CreateAttackCheckBoundary` w3 @ 0x001C5E90 — [codegen] src/attackCheckBoundary.c: In function `actAttackCheckBoundaryStart':
- REVERTED `GetAttackCheckBoundaryManagerStatus` w3 @ 0x001C5F38 — [codegen] src/attackCheckBoundary.c: In function `actAttackCheckBoundaryStart':
- PRE-MATCHED `InitAttackCheckBoundaryGeo` w1 @ 0x001C5D00 — already had a PAL body

### src/attackhit
- PRE-MATCHED `BoyAttackCenter` w2 @ 0x001893A0 — already had a PAL body
- REVERTED `CommonAttackCenter` w3 @ 0x001893A8 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PRE-MATCHED `EnemyAttackCenter` w2 @ 0x00189398 — already had a PAL body

### src/backStage
- PRE-MATCHED `backStageDebugTimeZero` w2 @ 0x001A9E50 — already had a PAL body
- PRE-MATCHED `backStageLoad` w2 @ 0x001A9D90 — already had a PAL body
- PRE-MATCHED `backStageProcessInit` w1 @ 0x001A9E38 — already had a PAL body
- PRE-MATCHED `backStageSave` w2 @ 0x001A9CE8 — already had a PAL body
- PRE-MATCHED `backStageTsuresariReturn` w2 @ 0x001A9E58 — already had a PAL body

### src/box
- REVERTED `BoxRideFunc` w3 @ 0x001CB250 — [codegen] insn 7: expected `lw	s0,2096(a2)` built `lw	s0,2032(a2)`
- REVERTED `ExecBoxMoveEndReaction` w3 @ 0x001CA798 — [codegen] src/box.c: In function `ExecBoxMoveEndReaction':
- REVERTED `ExecBoxMoveStartReaction` w3 @ 0x001CA730 — [codegen] src/box.c: In function `ExecBoxMoveStartReaction':
- REVERTED `FloorLeverTriStateGeo` w3 @ 0x001C5FE0 — [callee-sig-conflict] src/box.c:12: conflicting types for `BoxB1B95E0'
- PRE-MATCHED `GetBoxGlobalHoldPoint` w1 @ 0x001CA6D8 — already had a PAL body
- REVERTED `GetDistanceOfGObj` w1 @ 0x001CAED8 — [codegen] src/box.c:112: storage size of `buf2' isn't known
- REVERTED `GetFloorLeverGlobalHoldPoint` w3 @ 0x001C5F68 — [codegen] src/box.c:10: switch.c.inc: No such file or directory
- REVERTED `IsThisBoxTruck` w3 @ 0x001CA720 — [codegen] src/box.c:10: switch.c.inc: No such file or directory
- REVERTED `WallLeverDL` w3 @ 0x001C66A0 — [codegen] src/box.c:10: switch.c.inc: No such file or directory
- REVERTED `initLanding` w3 @ 0x001C8E08 — [codegen] src/box.c:73: storage size of `v2' isn't known
- REVERTED `moveXMinus` w1 @ 0x001CB000 — [codegen] src/box.c:10: switch.c.inc: No such file or directory
- REVERTED `moveXPlus` w1 @ 0x001CAF40 — [codegen] src/box.c:10: switch.c.inc: No such file or directory
- REVERTED `moveZMinus` w1 @ 0x001CB188 — [codegen] src/box.c:10: switch.c.inc: No such file or directory
- REVERTED `moveZPlus` w1 @ 0x001CB0C8 — [codegen] src/box.c:10: switch.c.inc: No such file or directory
- PRE-MATCHED `pullStartSE` w1 @ 0x001C6868 — already had a PAL body
- PRE-MATCHED `pushStartSE` w1 @ 0x001C6860 — already had a PAL body
- PRE-MATCHED `wallHitSE` w1 @ 0x001C6870 — already had a PAL body

### src/boy
- REVERTED `SetBoyStonizedVisual` w3 @ 0x001CC6F8 — [codegen] insn 7: expected `lw	s1,2096(v0)` built `lw	s1,2032(v0)`
- REVERTED `dispClothes` w3 @ 0x001CB2E0 — [codegen] insn 6: expected `lw	s0,2096(v0)` built `lw	s0,2032(v0)`

### src/boyact
- PRE-MATCHED `ACTSearchEnemy` w1 @ 0x00157EE8 — already had a PAL body
- PRE-MATCHED `ACTSearchGObj` w1 @ 0x001587A0 — already had a PAL body
- PRE-MATCHED `CorrectStickInfo` w1 @ 0x001577D0 — already had a PAL body
- REVERTED `GetBoyRootPositionForCamera` w3 @ 0x00158B38 — [codegen] insn 12: expected `addiu	s3,s0,272` built `addiu	s3,s0,240`
- PRE-MATCHED `GetEfStageCameraTargetID` w1 @ 0x00158528 — already had a PAL body
- REVERTED `GetSaveSofaLayoutID` w3 @ 0x00158360 — [codegen] insn 7: expected `lw	a0,52(a1)` built `lw	a0,48(a1)`
- PRE-MATCHED `GetbufpCharacterPacket` w2 @ 0x00158578 — already had a PAL body
- REVERTED `GetsizeCharacterPacket` w3 @ 0x00158588 — [codegen] insn 1: expected `addiu	v0,zero,32` built `addiu	v0,zero,24`
- PRE-MATCHED `IsGirlEscortedInCurrentStage` w1 @ 0x00158358 — already had a PAL body
- PRE-MATCHED `IsGirlEscortedInNextStage` w1 @ 0x00158340 — already had a PAL body
- PRE-MATCHED `OnGirlEscortFlag` w1 @ 0x001583B0 — already had a PAL body
- PRE-MATCHED `PrivInsCamChk_Control` w2 @ 0x00158568 — already had a PAL body
- REVERTED `ReadCharacterPacket` w3 @ 0x001586D8 — [codegen] insn 10: expected `lbu	a1,28(a2)` built `lbu	a1,20(a2)`
- PORTED `RequestStageChangeKidnapEnd` w1 @ 0x00158478 <- aug6 fumi/src/boyact:actBoyFall (6 syms rebound)
- PRE-MATCHED `afterBoyHangG3M` w2 @ 0x00158AB0 — already had a PAL body
- PORTED `func_00158B00` w1 @ 0x00158B00 <- aug6 fumi/src/boyact:func_001531E8 (2 syms rebound)

### src/brain
- REVERTED `brainAddLevel` w1 @ 0x0018A370 — [callee-sig-conflict] src/brain.c:75: conflicting types for `brainAddLevel'
- REVERTED `brainAddLevelGirl` w1 @ 0x00189738 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x20 (out-of-line helper or extra code)
- PRE-MATCHED `brainCheckView` w1 @ 0x0018A448 — already had a PAL body
- PRE-MATCHED `brainGetLevel` w1 @ 0x00189F50 — already had a PAL body
- PRE-MATCHED `brainInitGirlSet` w1 @ 0x0018A050 — already had a PAL body
- PRE-MATCHED `brainLockGirl` w2 @ 0x0018A350 — already had a PAL body
- PRE-MATCHED `brainSetLevel` w1 @ 0x0018A3C0 — already had a PAL body
- PRE-MATCHED `brainSetSpMode` w2 @ 0x0018A340 — already had a PAL body
- PRE-MATCHED `brainStatusDel` w2 @ 0x00189F48 — already had a PAL body
- PRE-MATCHED `brainUnlockGirl` w1 @ 0x0018A360 — already had a PAL body

### src/cage
- REVERTED `CageDL` w3 @ 0x001CD380 — [codegen] insn 5: expected `lw	s0,2096(v0)` built `lw	s0,2032(v0)`
- REVERTED `CageRideFunc` w3 @ 0x001CC740 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- REVERTED `GetCageChainPoint` w3 @ 0x001CD3B0 — [codegen] insn 8: expected `lw	s0,2096(v0)` built `lw	s0,2032(v0)`
- REVERTED `HotInitCageGeo` w3 @ 0x001CCCE8 — [codegen] insn 10: expected `lw	s0,2096(v0)` built `lw	s0,2032(v0)`
- REVERTED `SetCageChainHangableFlag` w3 @ 0x001CD498 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- REVERTED `SetCageFixGeometry` w3 @ 0x001CC878 — [codegen] insn 6: expected `lw	s0,2096(v1)` built `lw	s0,2032(v1)`
- REVERTED `SetCageVelocityFriction` w3 @ 0x001CD440 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- REVERTED `StabilizeAllLayoutedCage` w3 @ 0x001CD450 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/cageFix
- PRE-MATCHED `CageFixDL` w2 @ 0x001CD528 — already had a PAL body
- REVERTED `CageFixGeo` w3 @ 0x001CD4A8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `InitCageFixGeo` w2 @ 0x001CD570 — already had a PAL body

### src/camera-editor
- PRE-MATCHED `CameraEdit_BOX` w1 @ 0x0018F0E8 — already had a PAL body
- PRE-MATCHED `CameraEdit_BOX_NUMBER` w1 @ 0x0018F050 — already had a PAL body
- PRE-MATCHED `CameraEdit_DispBox` w2 @ 0x0018EA58 — already had a PAL body
- PRE-MATCHED `CameraEdit_DispBoxType2` w2 @ 0x0018CDB8 — already had a PAL body
- REVERTED `CameraEdit_DispPin` w1 @ 0x0018F128 — [callee-sig-conflict] src/camera-editor.c:15: conflicting types for `DrawLine'
- PRE-MATCHED `CameraEdit_DispPinType2` w1 @ 0x0018BFF8 — already had a PAL body
- PRE-MATCHED `CameraEdit_Enter` w2 @ 0x0018F978 — already had a PAL body
- PRE-MATCHED `CameraEdit_PIN` w1 @ 0x0018F100 — already had a PAL body
- PRE-MATCHED `CameraEdit_PIN_NUMBER` w1 @ 0x0018F060 — already had a PAL body
- PRE-MATCHED `CameraEdit_PIN_NUMBER_ALL` w1 @ 0x0018F0A8 — already had a PAL body
- PRE-MATCHED `CameraEdit_Reflect` w1 @ 0x0018EA60 — already had a PAL body
- PRE-MATCHED `CameraEdit_Save` w1 @ 0x0018EA70 — already had a PAL body
- PRE-MATCHED `CameraEdit_del_box` w1 @ 0x0018E9D8 — already had a PAL body
- PRE-MATCHED `CameraEdit_del_pin` w1 @ 0x0018EA10 — already had a PAL body
- PRE-MATCHED `CameraEdit_reflect_box` w1 @ 0x0018EDE0 — already had a PAL body
- PRE-MATCHED `CameraEdit_reflect_pin` w2 @ 0x0018EF38 — already had a PAL body
- PRE-MATCHED `CameraEdit_reset_box` w1 @ 0x0018EB70 — already had a PAL body
- PRE-MATCHED `CameraEdit_reset_pin` w2 @ 0x0018ECC8 — already had a PAL body
- REVERTED `EnterMenu` w1 @ 0x0018A478 — [codegen] insn 45: expected `<end>` built `sll	zero,zero,0x0`
- PRE-MATCHED `InitCameraEditor` w1 @ 0x0018EB08 — already had a PAL body
- PRE-MATCHED `StickToTrans` w1 @ 0x0018F418 — already had a PAL body
- PRE-MATCHED `_CameraEdit_PIN` w1 @ 0x0018F680 — already had a PAL body
- PRE-MATCHED `_CameraEdit_add_pin` w1 @ 0x0018F820 — already had a PAL body
- PRE-MATCHED `debug_Arrow` w1 @ 0x0018EB00 — already had a PAL body
- PRE-MATCHED `debug_CameraEditor` w1 @ 0x0018EB18 — already had a PAL body
- PRE-MATCHED `debug_NMarker` w1 @ 0x0018EA80 — already had a PAL body
- PRE-MATCHED `gif_test` w1 @ 0x0018A970 — already had a PAL body
- REVERTED `test_camedit` w1 @ 0x0018E150 — [codegen] insn 2: expected `addiu	a0,a0,0` built `addiu	a0,a0,10568`

### src/camera-ico2
- REVERTED `AddPluralCameraSet` w3 @ 0x00192D10 — [codegen] insn 15: expected `addiu	a1,zero,2045` built `addiu	a1,zero,1982`
- REVERTED `CameraSetCameraSet` w1 @ 0x0018F980 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x68 (out-of-line helper or extra code)
- PRE-MATCHED `CameraSetCameraSet_Default` w3 @ 0x0018F9E8 — already had a PAL body
- PRE-MATCHED `ChaseCamera` w1 @ 0x00190780 — already had a PAL body
- PRE-MATCHED `GetCameraGroupCurrent` w2 @ 0x00192B68 — already had a PAL body
- PRE-MATCHED `GetCameraGroupFromGObj` w1 @ 0x00192B70 — already had a PAL body
- PRE-MATCHED `GetCameraGroupFromPosition` w1 @ 0x00192C48 — already had a PAL body
- REVERTED `GetPluralCameraSet` w3 @ 0x00192DC8 — [codegen] insn 27: expected `addiu	a1,zero,2036` built `addiu	a1,zero,1973`
- PRE-MATCHED `GetRootPositionForCamera` w1 @ 0x0018FA08 — already had a PAL body
- PRE-MATCHED `GetSizeOfCameraSetBinary` w1 @ 0x001930E8 — already had a PAL body
- PRE-MATCHED `InitPluralCameraSet` w2 @ 0x00192DC0 — already had a PAL body
- PORTED `MakeCameraSetBinary` w1 @ 0x00192E70 <- aug6 omori/src/camera-ico2:func_00188888 (1 syms rebound)
- PORTED `SetCameraTargetPosition` w1 @ 0x00193130 <- aug6 omori/src/camera-ico2:func_00188B48 (5 syms rebound)
- PRE-MATCHED `SetCameraZoomOffsetRatio` w2 @ 0x00192B60 — already had a PAL body
- PRE-MATCHED `ico2camera_GetGroupNearest` w1 @ 0x0018FCA8 — already had a PAL body
- PRE-MATCHED `ico2camera_GetTargetPos` w1 @ 0x0018FA28 — already had a PAL body

### src/camera-root
- PRE-MATCHED `BackToGameCamera` w1 @ 0x00193AB0 — already had a PAL body
- PRE-MATCHED `Camctrl_ExitEveRock` w1 @ 0x00194870 — already had a PAL body
- PRE-MATCHED `Camctrl_SetTarget` w1 @ 0x001948A0 — already had a PAL body
- PRE-MATCHED `CameraChangeTargetParallel` w1 @ 0x00194918 — already had a PAL body
- PRE-MATCHED `CameraGetMode` w2 @ 0x00194A08 — already had a PAL body
- REVERTED `CameraGetOtherObjOffset` w1 @ 0x00194A10 — [callee-sig-conflict] src/camera-root.c:169: conflicting types for `CameraGetOtherObjOffset'
- PRE-MATCHED `CameraGetTarget` w2 @ 0x001949D8 — already had a PAL body
- PRE-MATCHED `CameraGetTargets` w1 @ 0x001949E0 — already had a PAL body
- PORTED `CameraSetCameraPosition` w1 @ 0x00194E78 <- aug6 omori/src/camera-set-manager:func_0018A3B0 (4 syms rebound)
- PRE-MATCHED `CameraSetMode` w1 @ 0x001949F8 — already had a PAL body
- PRE-MATCHED `CameraSetTargetGObj` w2 @ 0x00194908 — already had a PAL body
- PRE-MATCHED `CameraSetTargetPos` w2 @ 0x00194ED0 — already had a PAL body
- PRE-MATCHED `DebugCameraManual` w1 @ 0x001939B8 — already had a PAL body
- PRE-MATCHED `DebugCameraSemiAuto` w1 @ 0x001939F0 — already had a PAL body
- PRE-MATCHED `GetCameraDefaultTargetGObj` w1 @ 0x001948D0 — already had a PAL body
- PRE-MATCHED `GetCameraInfo_tmp` w1 @ 0x00194EF8 — already had a PAL body
- PRE-MATCHED `GetCameraInfomationFromGlobalPosition` w1 @ 0x00193BB8 — already had a PAL body
- PRE-MATCHED `GetCameraPos` w3 @ 0x00194ED8 — already had a PAL body
- PRE-MATCHED `GetCurrentCameraSet2` w2 @ 0x00194DA8 — already had a PAL body
- PRE-MATCHED `InsertCamera_isEnable` w1 @ 0x00194E68 — already had a PAL body
- PRE-MATCHED `SetCameraFlag_GamecamCutBack` w2 @ 0x00194DC8 — already had a PAL body
- PRE-MATCHED `SetCameraFlag_LwsCutBack` w2 @ 0x00194DB8 — already had a PAL body
- PORTED `SetMonitorCameraInitializeFlag` w2 @ 0x00194F58 <- aug6 omori/src/chain:chain_simulate_term_simple (2 syms rebound)
- REVERTED `SetWSMatrix` w1 @ 0x001931C8 — [codegen] insn 6: expected `jal	0 <SetWSMatrix>` built `jal	38 <ConvertCameraSet>`
- PRE-MATCHED `testcamerazoom` w2 @ 0x00194F48 — already had a PAL body

### src/camera-set-manager
- PRE-MATCHED `InitCameraSetManager` w2 @ 0x00194F68 — already had a PAL body

### src/candle
- PRE-MATCHED `CandleDL` w2 @ 0x001CD7F8 — already had a PAL body

### src/chain
- REVERTED `CheckChainClimbablePos` w3 @ 0x00198778 — [codegen] insn 1: expected `lw	a0,2096(a1)` built `lw	a0,2032(a1)`
- REVERTED `DecreasePdlChain` w3 @ 0x001986C8 — [codegen] insn 7: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- REVERTED `GetChainClimbCollision` w3 @ 0x001987A0 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- REVERTED `GetChainClimbOrient` w3 @ 0x00198750 — [codegen] insn 1: expected `lw	v0,2096(v1)` built `lw	v0,2032(v1)`
- REVERTED `GetChainDirCorrectVal` w3 @ 0x001987D8 — [codegen] insn 3: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- REVERTED `GetChainNearestNodePosition` w3 @ 0x00198E88 — [codegen] insn 15: expected `lw	s1,2096(v0)` built `lw	s1,2032(v0)`
- REVERTED `GetChainPendulum` w3 @ 0x00198670 — [codegen] insn 1: expected `lw	v0,2096(v0)` built `lw	v0,2032(v0)`
- PORTED `GetRootPositionHandExtra` w1 @ 0x00198810 <- aug6 omori/src/ebrain:eBrainProcess (2 syms rebound)
- REVERTED `HoldChain` w3 @ 0x00198630 — [codegen] insn 4: expected `jal	0 <HoldChain>` built `jal	108 <StartPendulum>`
- REVERTED `IncreasePdlChain` w3 @ 0x001986B0 — [codegen] insn 2: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- REVERTED `PlumbOrientUpdateChain` w3 @ 0x001986F8 — [codegen] insn 2: expected `lw	v0,2096(v1)` built `lw	v0,2032(v1)`
- REVERTED `ReleaseChain` w3 @ 0x00198660 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- REVERTED `SetChainParentGObj` w3 @ 0x001987C8 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- PORTED `chain_simulate_term` w1 @ 0x00195F68 <- aug6 omori/src/chain:InitChainGeo (6 syms rebound)
- PORTED `chain_sub_pendulum` w1 @ 0x00198DF8 <- aug6 omori/src/ebrain:func_0018E2B8 (2 syms rebound)
- REVERTED `isBottomOfChain` w3 @ 0x00198720 — [codegen] insn 1: expected `lw	a0,2096(v0)` built `lw	a0,2032(v0)`
- REVERTED `isStopChain` w3 @ 0x00198740 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`

### src/chandelier
- PRE-MATCHED `ChandelierDL` w2 @ 0x001CDA40 — already had a PAL body
- PRE-MATCHED `ChandelierGeo` w1 @ 0x001CD9A8 — already had a PAL body
- PRE-MATCHED `InitChandelierGeo` w2 @ 0x001CDA88 — already had a PAL body

### src/charFileManager
- PORTED `GetPObjAddress` w1 @ 0x001ABC20 <- aug6 common/src/debug:debug_Assert (2 syms rebound)
- REVERTED `InitCharFileManager` w3 @ 0x001A9E60 — [callee-sig-conflict] src/charFileManager.c:45: conflicting types for `D_006FAD00__pn'
- REVERTED `ReadCamerasetFile` w3 @ 0x001AB4D8 — [codegen] insn 16: expected `addiu	a3,zero,820` built `addiu	a3,zero,807`
- REVERTED `ReadEndCheckFile` w3 @ 0x001AB5A8 — [codegen] insn 1: expected `addiu	a3,zero,854` built `addiu	a3,zero,841`
- REVERTED `ReadParticleEffectFile` w3 @ 0x001AAFA0 — [codegen] insn 11: expected `addiu	a3,zero,552` built `addiu	a3,zero,539`
- REVERTED `ReadStageAnimationFile` w3 @ 0x001AAC50 — [codegen] insn 22: expected `addiu	a1,zero,487` built `addiu	a1,zero,474`
- REVERTED `ResetCharFileManager` w3 @ 0x001A9EE0 — [callee-sig-conflict] src/charFileManager.c:49: conflicting types for `D_006FAD00__pn'

### src/clipCollisionManager
- REVERTED `CreateClipCollisionManagerGObj` w2 @ 0x001CDCB0 — [codegen] insn 4: expected `addiu	t0,t0,0` built `addiu	t0,t0,672`
- PORTED `RequestClipCollision` w2 @ 0x001CDCF0 <- aug6 sugipon/src/chandelier:func_001C0990 (3 syms rebound)

### src/clothAnimation
- PRE-MATCHED `DeleteChainExtendedWeight` w1 @ 0x001D3CA0 — already had a PAL body
- PRE-MATCHED `DispClothMesh` w1 @ 0x001D0EE8 — already had a PAL body
- PRE-MATCHED `FSqrtInv` w1 @ 0x001D3F68 — already had a PAL body
- REVERTED `GetChainExWeightGlobalPos` w1 @ 0x001CDF40 — [codegen] insn 5: expected `<end>` built `sll	zero,zero,0x0`
- PRE-MATCHED `GetChainNodeGlobalQuaternion` w1 @ 0x001D3AD8 — already had a PAL body
- PRE-MATCHED `GetChainNodeID` w1 @ 0x001D3CC8 — already had a PAL body
- PRE-MATCHED `MoveChainExtendedWeight` w1 @ 0x001D3B80 — already had a PAL body
- PRE-MATCHED `ResetClothAnimation` w1 @ 0x001D3CE0 — already had a PAL body
- REVERTED `checkFrontAcross` w1 @ 0x001D4238 — [crutch] crutch: bare register-variable pin `register int result __asm__("$`
- PRE-MATCHED `checkOverThePlane` w1 @ 0x001D41F8 — already had a PAL body
- REVERTED `getCrossPoint` w1 @ 0x001D4138 — [crutch] crutch: bare register-variable pin `register float d1 __asm__("$`
- PRE-MATCHED `getXZInvLength` w1 @ 0x001D3FB0 — already had a PAL body
- PRE-MATCHED `getXZLength` w1 @ 0x001D3F88 — already had a PAL body
- PRE-MATCHED `getXZLengthSquare` w1 @ 0x001D3FD8 — already had a PAL body
- PRE-MATCHED `scaleAndAddVectorXYZ` w1 @ 0x001D4030 — already had a PAL body
- PRE-MATCHED `scaleVectorXZ` w1 @ 0x001D4058 — already had a PAL body
- PRE-MATCHED `subAndGetInvLength` w1 @ 0x001D3FF8 — already had a PAL body
- REVERTED `tensionMove` — [period-as-dialect] inline asm spells $Q; the period assembler (ee-as 2.9-991111) rejects it (post-hoc, bisected from the chunk-1 ninja failure)
- PRE-MATCHED `tensionMoveNoReduce` w1 @ 0x001D4078 — already had a PAL body

### src/clothTest
- PRE-MATCHED `ClothTestDL` w2 @ 0x001D44B0 — already had a PAL body
- PRE-MATCHED `ClothTestGeo` w2 @ 0x001D44A8 — already had a PAL body
- PORTED `InitClothTestGeo` w1 @ 0x001D4458 <- aug6 sugipon/src/clothTest:func_001C6548 (6 syms rebound)

### src/cod/vendor_25B680
- PRE-MATCHED `sceGsGetGParam` w2 @ 0x0025B790 — already had a PAL body
- PRE-MATCHED `sceGsGetIMR` w2 @ 0x0025D220 — already had a PAL body
- PRE-MATCHED `sceGsPutDispEnv` w1 @ 0x0025BA78 — already had a PAL body
- PRE-MATCHED `sceGsPutIMR` w1 @ 0x0025D158 — already had a PAL body
- PRE-MATCHED `sceGsResetPath` w1 @ 0x0025B7A0 — already had a PAL body
- PRE-MATCHED `sceGsSetDefAlphaEnv` w1 @ 0x0025C5C0 — already had a PAL body
- PRE-MATCHED `sceGsSetHalfOffset` w1 @ 0x0025D198 — already had a PAL body
- PRE-MATCHED `sceGsSwapDBuff` w1 @ 0x0025C0A0 — already had a PAL body

### src/cod/vendor_25D410
- PRE-MATCHED `func_0025D440` w1 @ 0x0025D440 — already had a PAL body
- PRE-MATCHED `func_0025D758` w1 @ 0x0025D758 — already had a PAL body
- PRE-MATCHED `func_0025D7D0` w1 @ 0x0025D7D0 — already had a PAL body
- PRE-MATCHED `func_0025D878` w1 @ 0x0025D878 — already had a PAL body
- PRE-MATCHED `func_0025D920` w1 @ 0x0025D920 — already had a PAL body
- PRE-MATCHED `func_0025DEB0` w1 @ 0x0025DEB0 — already had a PAL body
- PRE-MATCHED `func_0025DF08` w1 @ 0x0025DF08 — already had a PAL body
- PRE-MATCHED `func_0025E060` w1 @ 0x0025E060 — already had a PAL body
- PORTED `memclr` w1 @ 0x0025E150 <- aug6 common/src/PObj:func_00240B18 (1 syms rebound)
- PRE-MATCHED `sceVpu0Reset` w1 @ 0x0025E0F0 — already had a PAL body
- PRE-MATCHED `sceVu0AddVector` w1 @ 0x0025D628 — already had a PAL body
- PRE-MATCHED `sceVu0ApplyMatrix` w1 @ 0x0025D410 — already had a PAL body
- PRE-MATCHED `sceVu0CameraMatrix` w1 @ 0x0025DA40 — already had a PAL body
- PRE-MATCHED `sceVu0ClampVector` w1 @ 0x0025DA18 — already had a PAL body
- PRE-MATCHED `sceVu0ClipScreen` w1 @ 0x0025DFB8 — already had a PAL body
- PRE-MATCHED `sceVu0ClipScreen3` w1 @ 0x0025E000 — already had a PAL body
- PRE-MATCHED `sceVu0CopyMatrix` w1 @ 0x0025D6C8 — already had a PAL body
- PRE-MATCHED `sceVu0CopyVector` w1 @ 0x0025D6B8 — already had a PAL body
- PRE-MATCHED `sceVu0CopyVectorXYZ` w1 @ 0x0025DF50 — already had a PAL body
- PRE-MATCHED `sceVu0DivVector` w1 @ 0x0025D5C0 — already had a PAL body
- PRE-MATCHED `sceVu0DivVectorXYZ` w1 @ 0x0025D5E0 — already had a PAL body
- PRE-MATCHED `sceVu0FTOI0Vector` w1 @ 0x0025D700 — already had a PAL body
- PRE-MATCHED `sceVu0FTOI4Vector` w1 @ 0x0025D6F0 — already had a PAL body
- PRE-MATCHED `sceVu0ITOF0Vector` w1 @ 0x0025D720 — already had a PAL body
- PRE-MATCHED `sceVu0ITOF4Vector` w1 @ 0x0025D710 — already had a PAL body
- PRE-MATCHED `sceVu0InnerProduct` w1 @ 0x0025D4A8 — already had a PAL body
- PRE-MATCHED `sceVu0InterVector` w1 @ 0x0025D600 — already had a PAL body
- PRE-MATCHED `sceVu0InterVectorXYZ` w1 @ 0x0025DF70 — already had a PAL body
- PRE-MATCHED `sceVu0InversMatrix` w1 @ 0x0025D550 — already had a PAL body
- PRE-MATCHED `sceVu0LightColorMatrix` w1 @ 0x0025DBB0 — already had a PAL body
- PRE-MATCHED `sceVu0MulVector` w1 @ 0x0025D658 — already had a PAL body
- PRE-MATCHED `sceVu0NormalLightMatrix` w1 @ 0x0025DAF0 — already had a PAL body
- PRE-MATCHED `sceVu0Normalize` w1 @ 0x0025D4D0 — already had a PAL body
- PRE-MATCHED `sceVu0OuterProduct` w1 @ 0x0025D488 — already had a PAL body
- PRE-MATCHED `sceVu0RotMatrix` w1 @ 0x0025D9C8 — already had a PAL body
- PRE-MATCHED `sceVu0ScaleVector` w1 @ 0x0025D670 — already had a PAL body
- PRE-MATCHED `sceVu0ScaleVectorXYZ` w1 @ 0x0025DFA0 — already had a PAL body
- PRE-MATCHED `sceVu0SubVector` w1 @ 0x0025D640 — already had a PAL body
- PRE-MATCHED `sceVu0TransMatrix` w1 @ 0x0025D688 — already had a PAL body
- PRE-MATCHED `sceVu0TransposeMatrix` w1 @ 0x0025D508 — already had a PAL body
- PRE-MATCHED `sceVu0UnitMatrix` w1 @ 0x0025D730 — already had a PAL body

### src/cod/vendor_25E188
- PRE-MATCHED `sceDmaDebug` w1 @ 0x0025E290 — already had a PAL body
- PRE-MATCHED `sceDmaGetChan` w1 @ 0x0025E188 — already had a PAL body
- REVERTED `sceDmaGetEnv` w1 @ 0x0025E478 — [undeclared] src/cod/vendor_25E188.c:28: dereferencing pointer to incomplete type
- PRE-MATCHED `sceDmaPause` w2 @ 0x0025EBC0 — already had a PAL body
- REVERTED `sceDmaPutStallAddr` w1 @ 0x0025E4B0 — [codegen] insn 4: expected `beq	a0,v1,20 <sceDmaPutStallAddr+0x20>` built `lw	v0,0(v0)`
- PORTED `sceDmaRestart` w2 @ 0x0025EBE0 <- aug6 common/src/PObj:func_002415A8 (1 syms rebound)

### src/cod/vendor_25EC00
- PRE-MATCHED `sceVif1PkAddGsData` w1 @ 0x0025EEF0 — already had a PAL body
- PRE-MATCHED `sceVif1PkCloseDirectCode` w1 @ 0x0025ED80 — already had a PAL body
- REVERTED `sceVif1PkCnt` w2 @ 0x0025EC78 — [codegen] src/cod/vendor_25EC00.c:44: void value not ignored as it ought to be
- REVERTED `sceVif1PkEnd` w2 @ 0x0025ECD0 — [codegen] src/cod/vendor_25EC00.c:45: void value not ignored as it ought to be
- PRE-MATCHED `sceVif1PkInit` w1 @ 0x0025EC00 — already had a PAL body
- PRE-MATCHED `sceVif1PkOpenDirectCode` w1 @ 0x0025ED28 — already had a PAL body
- PRE-MATCHED `sceVif1PkOpenGifTag` w1 @ 0x0025EDB0 — already had a PAL body
- PRE-MATCHED `sceVif1PkReset` w1 @ 0x0025EC10 — already had a PAL body
- PRE-MATCHED `sceVif1PkTerminate` w1 @ 0x0025EC20 — already had a PAL body

### src/cod/vendor_25EF18
- PRE-MATCHED `ExpandScratchPad` w2 @ 0x00265020 — already had a PAL body
- PRE-MATCHED `GetTLBEntry` w2 @ 0x00264FE0 — already had a PAL body
- PRE-MATCHED `InitTLBFunctions` w1 @ 0x00264F50 — already had a PAL body
- PRE-MATCHED `ProbeTLBEntry` w1 @ 0x00265000 — already had a PAL body
- PRE-MATCHED `PutTLBEntry` w1 @ 0x00264FA0 — already had a PAL body
- PRE-MATCHED `QueueInit` w1 @ 0x0025F250 — already had a PAL body
- PRE-MATCHED `QueuePeekReadDone` w1 @ 0x0025F2B8 — already had a PAL body
- PRE-MATCHED `QueuePeekWriteDone` w1 @ 0x0025F278 — already had a PAL body
- REVERTED `SetDebugHandler` w1 @ 0x00264EB8 — [codegen] insn 21: expected `addiu	a1,a1,0` built `addiu	a1,a1,25448`
- PRE-MATCHED `SetTLBEntry` w2 @ 0x00264FC0 — already had a PAL body
- REVERTED `SetTLBHandler` w1 @ 0x00264E58 — [codegen] insn 5: expected `addiu	s0,s0,0` built `addiu	s0,s0,24872`
- REVERTED `VSync` w1 @ 0x0025EF28 — [codegen] insn 14: expected `jr	ra` built `sw	v0,-4096(at)`
- PRE-MATCHED `VSync2` w1 @ 0x0025EF68 — already had a PAL body
- PRE-MATCHED `_DumpTLB` w1 @ 0x00264AE8 — already had a PAL body
- PRE-MATCHED `_change_addr` w1 @ 0x002653C0 — already had a PAL body
- PRE-MATCHED `_fs_version` w2 @ 0x00260E10 — already had a PAL body
- PRE-MATCHED `_lf_bind` w1 @ 0x00263EA0 — already had a PAL body
- PRE-MATCHED `_lf_version` w2 @ 0x00263FA0 — already had a PAL body
- PRE-MATCHED `_request_call` w1 @ 0x0025FF20 — already had a PAL body
- PRE-MATCHED `_request_rdata` w1 @ 0x0025FB28 — already had a PAL body
- PRE-MATCHED `_sceFsSemInit` w1 @ 0x00260BE0 — already had a PAL body
- PRE-MATCHED `_sceFsSigSema` w2 @ 0x00260C60 — already had a PAL body
- PRE-MATCHED `_sceFsWaitS` w1 @ 0x00260C30 — already had a PAL body
- PRE-MATCHED `_sceRpcFreePacket` w1 @ 0x0025F9E0 — already had a PAL body
- PRE-MATCHED `_sceRpcGetFPacket` w1 @ 0x0025FA00 — already had a PAL body
- PRE-MATCHED `_sceRpcGetFPacket2` w1 @ 0x0025FA30 — already had a PAL body
- PRE-MATCHED `_sceSifCmdIntrHdlr` w1 @ 0x00265910 — already had a PAL body
- REVERTED `_sceSifLoadElfPart` w3 @ 0x00264518 — [unresolved-symbol] unresolved-symbol: insn 22 `D_0070F808`: pal symbol D_FFFDD788 (0xFFFDD788) undefined
- PRE-MATCHED `_search_svdata` w1 @ 0x0025FCE0 — already had a PAL body
- PRE-MATCHED `close` w2 @ 0x0025F0E8 — already had a PAL body
- PRE-MATCHED `fstat` w1 @ 0x0025F1B8 — already had a PAL body
- PRE-MATCHED `func_00260690` w1 @ 0x00260690 — already had a PAL body
- PRE-MATCHED `func_002606D0` w1 @ 0x002606D0 — already had a PAL body
- PRE-MATCHED `func_00264F40` w2 @ 0x00264F40 — already had a PAL body
- PRE-MATCHED `func_00265A38` w1 @ 0x00265A38 — already had a PAL body
- PRE-MATCHED `func_00265AE4` w1 @ 0x00265AE4 — already had a PAL body
- PRE-MATCHED `func_00265AEC` w1 @ 0x00265AEC — already had a PAL body
- PRE-MATCHED `get_iob` w3 @ 0x002607B8 — already had a PAL body
- PRE-MATCHED `getpid` w2 @ 0x0025F1D0 — already had a PAL body
- PRE-MATCHED `iGetTLBEntry` w1 @ 0x00264FF0 — already had a PAL body
- PRE-MATCHED `iProbeTLBEntry` w2 @ 0x00265010 — already had a PAL body
- PRE-MATCHED `iPutTLBEntry` w2 @ 0x00264FB0 — already had a PAL body
- PRE-MATCHED `iSetTLBEntry` w1 @ 0x00264FD0 — already had a PAL body
- PRE-MATCHED `ioctl` w2 @ 0x0025F0F0 — already had a PAL body
- PRE-MATCHED `isatty` w2 @ 0x0025F1B0 — already had a PAL body
- PRE-MATCHED `isceSifSendCmd` w1 @ 0x002658D0 — already had a PAL body
- PRE-MATCHED `kExpandScratchPad` w1 @ 0x00264D28 — already had a PAL body
- PRE-MATCHED `kGetTLBEntry` w1 @ 0x00264C88 — already had a PAL body
- PRE-MATCHED `kProbeTLBEntry` w1 @ 0x00264CD8 — already had a PAL body
- PRE-MATCHED `kPutTLBEntry` w1 @ 0x00264B80 — already had a PAL body
- PRE-MATCHED `kSetTLBEntry` w1 @ 0x00264C40 — already had a PAL body
- PRE-MATCHED `kill` w1 @ 0x0025F1D8 — already had a PAL body
- PRE-MATCHED `lseek` w2 @ 0x0025F0F8 — already had a PAL body
- PRE-MATCHED `new_iob` w1 @ 0x00260730 — already had a PAL body
- PRE-MATCHED `open` w2 @ 0x0025F0C0 — already had a PAL body
- PRE-MATCHED `sbrk` w1 @ 0x0025F100 — already had a PAL body
- PRE-MATCHED `sceChdir` w1 @ 0x00262FE8 — already had a PAL body
- PRE-MATCHED `sceDclose` w1 @ 0x00262758 — already had a PAL body
- PRE-MATCHED `sceDelDrv` w1 @ 0x00262698 — already had a PAL body
- PRE-MATCHED `sceDread` w1 @ 0x002628C0 — already had a PAL body
- PRE-MATCHED `sceFsReset` w1 @ 0x00260EA0 — already had a PAL body
- PRE-MATCHED `sceRemove` w1 @ 0x00262118 — already had a PAL body
- PRE-MATCHED `sceResetttyinit` w2 @ 0x0025EF18 — already had a PAL body
- PRE-MATCHED `sceRmdir` w1 @ 0x002622E8 — already had a PAL body
- PRE-MATCHED `sceSifAddCmdHandler` w1 @ 0x00265700 — already had a PAL body
- PRE-MATCHED `sceSifAllocIopHeap` w1 @ 0x00263CC8 — already had a PAL body
- REVERTED `sceSifBindRpc` w1 @ 0x0025FDE0 — [callee-sig-conflict] src/cod/vendor_25EF18.c:241: conflicting types for `_sceRpcGetPacket'
- PRE-MATCHED `sceSifCheckStatRpc` w1 @ 0x002601A0 — already had a PAL body
- PRE-MATCHED `sceSifExitCmd` w1 @ 0x00265698 — already had a PAL body
- PRE-MATCHED `sceSifExitRpc` w1 @ 0x0025F910 — already had a PAL body
- PRE-MATCHED `sceSifFreeIopHeap` w1 @ 0x00263D38 — already had a PAL body
- PRE-MATCHED `sceSifGetDataTable` w2 @ 0x00265408 — already had a PAL body
- PRE-MATCHED `sceSifGetIopAddr` w1 @ 0x00264668 — already had a PAL body
- PRE-MATCHED `sceSifGetNextRequest` w1 @ 0x00260470 — already had a PAL body
- REVERTED `sceSifGetOtherData` w1 @ 0x0025FB88 — [callee-sig-conflict] src/cod/vendor_25EF18.c:227: conflicting types for `_sceRpcGetPacket'
- PRE-MATCHED `sceSifGetSreg` w2 @ 0x002653D0 — already had a PAL body
- PRE-MATCHED `sceSifInitIopHeap` w1 @ 0x00263C40 — already had a PAL body
- PRE-MATCHED `sceSifIsAliveIop` w1 @ 0x00264968 — already had a PAL body
- PRE-MATCHED `sceSifLoadElf` w1 @ 0x00264640 — already had a PAL body
- PRE-MATCHED `sceSifLoadElfPart` w1 @ 0x00264620 — already had a PAL body
- PRE-MATCHED `sceSifLoadFileReset` w1 @ 0x00264030 — already had a PAL body
- PRE-MATCHED `sceSifLoadModule` w1 @ 0x002644D8 — already had a PAL body
- PRE-MATCHED `sceSifLoadModuleBuffer` w1 @ 0x00264270 — already had a PAL body
- PRE-MATCHED `sceSifLoadStartModule` w1 @ 0x002644F8 — already had a PAL body
- PRE-MATCHED `sceSifLoadStartModuleBuffer` w2 @ 0x00264290 — already had a PAL body
- PRE-MATCHED `sceSifRemoveCmdHandler` w1 @ 0x00265730 — already had a PAL body
- REVERTED `sceSifRemoveRpcQueue` w1 @ 0x002603E0 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- PRE-MATCHED `sceSifSendCmd` w1 @ 0x00265890 — already had a PAL body
- PRE-MATCHED `sceSifSetCmdBuffer` w1 @ 0x002656D0 — already had a PAL body
- PRE-MATCHED `sceSifSetSreg` w1 @ 0x002653E8 — already had a PAL body
- PRE-MATCHED `sceSifSetSysCmdBuffer` w1 @ 0x002656E8 — already had a PAL body
- PRE-MATCHED `sceSifSyncIop` w1 @ 0x00264990 — already had a PAL body
- PRE-MATCHED `sceUmount` w1 @ 0x00263410 — already had a PAL body
- PRE-MATCHED `stat` w2 @ 0x0025F200 — already had a PAL body
- PRE-MATCHED `unlink` w2 @ 0x0025F228 — already had a PAL body

### src/cod/vendor_265B10
- PRE-MATCHED `_sceCd_Poff_Intr` w1 @ 0x00266030 — already had a PAL body
- PRE-MATCHED `_send_to_iop` w1 @ 0x00267AD0 — already had a PAL body
- REVERTED `cdvd_exit` w1 @ 0x00265F40 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- PRE-MATCHED `sceCdCallback` w1 @ 0x00265B78 — already had a PAL body
- PRE-MATCHED `sceCdDelayThread` w1 @ 0x00265B10 — already had a PAL body
- PRE-MATCHED `sceCdNcmdDiskReady` w3 @ 0x00266668 — already had a PAL body
- PRE-MATCHED `sceCdPOffCallback` w1 @ 0x00265FC0 — already had a PAL body
- PRE-MATCHED `sceCdStInit` w1 @ 0x002675F0 — already had a PAL body
- PRE-MATCHED `sceCdStPause` w1 @ 0x00267878 — already had a PAL body
- PRE-MATCHED `sceCdStResume` w1 @ 0x002678C8 — already had a PAL body
- PRE-MATCHED `sceCdStSeek` w1 @ 0x00267688 — already had a PAL body
- PRE-MATCHED `sceCdStSeekF` w1 @ 0x00267658 — already had a PAL body
- PRE-MATCHED `sceCdStStart` w1 @ 0x00267620 — already had a PAL body
- PRE-MATCHED `sceCdStStat` w1 @ 0x00267920 — already had a PAL body
- PRE-MATCHED `sceCdStStop` w1 @ 0x002676B8 — already had a PAL body
- PRE-MATCHED `sceCdSyncS` w1 @ 0x002667A0 — already had a PAL body

### src/cod/vendor_267C00
- PRE-MATCHED `scePadEnd` w1 @ 0x00267DE0 — already had a PAL body
- PRE-MATCHED `scePadEnterPressMode` w1 @ 0x00268B58 — already had a PAL body
- PRE-MATCHED `scePadExitPressMode` w1 @ 0x00268BB0 — already had a PAL body
- PRE-MATCHED `scePadGetDmaStr` w1 @ 0x00268100 — already had a PAL body
- PRE-MATCHED `scePadGetFrameCount` w1 @ 0x00268160 — already had a PAL body
- PRE-MATCHED `scePadGetModVersion` w1 @ 0x00268DA8 — already had a PAL body
- PRE-MATCHED `scePadGetPortMax` w1 @ 0x00268CD8 — already had a PAL body
- PRE-MATCHED `scePadGetReqState` w1 @ 0x00268348 — already had a PAL body
- PRE-MATCHED `scePadGetSlotMax` w1 @ 0x00268D40 — already had a PAL body
- PRE-MATCHED `scePadGetState` w1 @ 0x00268230 — already had a PAL body
- PRE-MATCHED `scePadInfoMode` w1 @ 0x00268610 — already had a PAL body
- PRE-MATCHED `scePadInfoPressMode` w1 @ 0x00268AF8 — already had a PAL body
- REVERTED `scePadInit` w1 @ 0x00267C00 — [codegen] insn 29: expected `lui	v0,0x0` built `lui	v0,0x1`
- PRE-MATCHED `scePadRead` w1 @ 0x002681B0 — already had a PAL body
- REVERTED `scePadReqIntToStr` w3 @ 0x00268398 — [unresolved-symbol] unresolved-symbol: insn 10 `D_00628D28`: pal symbol D_00556C58 (0x00556C58) undefined
- PRE-MATCHED `scePadSetActAlign` w1 @ 0x002688B8 — already had a PAL body
- PRE-MATCHED `scePadSetButtonInfo` w1 @ 0x00268A48 — already had a PAL body
- PRE-MATCHED `scePadSetMainMode` w1 @ 0x00268748 — already had a PAL body
- PRE-MATCHED `scePadSetReqState` w1 @ 0x002682E0 — already had a PAL body
- PRE-MATCHED `scePadSetVrefParam` w1 @ 0x00268C08 — already had a PAL body
- PRE-MATCHED `scePadSetWarningLevel` w1 @ 0x00268E10 — already had a PAL body
- REVERTED `scePadStateIntToStr` w3 @ 0x002682A8 — [unresolved-symbol] unresolved-symbol: insn 10 `D_00628D28`: pal symbol D_00556C58 (0x00556C58) undefined

### src/cod/vendor_268E78
- PRE-MATCHED `_lmcGetClientPtr` w1 @ 0x00269030 — already had a PAL body
- REVERTED `mcDelayThread` w1 @ 0x00269830 — [codegen] insn 7: expected `addiu	s0,s0,0` built `addiu	s0,s0,2448`
- PRE-MATCHED `mcHearAlarm` w1 @ 0x00269808 — already had a PAL body
- PRE-MATCHED `mceGetInfoApdx` w1 @ 0x00269958 — already had a PAL body
- PRE-MATCHED `mceStorePwd` w1 @ 0x00269C90 — already had a PAL body
- PRE-MATCHED `sceMcChangeThreadPriority` w3 @ 0x00269060 — already had a PAL body
- REVERTED `sceMcChdir` w3 @ 0x00269D18 — [codegen] insn 58: expected `addiu	t3,t3,0` built `addiu	t3,t3,3608`
- PRE-MATCHED `sceMcClose` w3 @ 0x00269348 — already had a PAL body
- PRE-MATCHED `sceMcFlush` w3 @ 0x0026A058 — already had a PAL body
- PRE-MATCHED `sceMcFormat` w3 @ 0x00269E68 — already had a PAL body
- PRE-MATCHED `sceMcGetDir` w3 @ 0x00269B38 — already had a PAL body
- PRE-MATCHED `sceMcGetEntSpace` w3 @ 0x0026A518 — already had a PAL body
- PRE-MATCHED `sceMcGetSlotMax` w3 @ 0x00269118 — already had a PAL body
- PRE-MATCHED `sceMcMkdir` w1 @ 0x00269310 — already had a PAL body
- REVERTED `sceMcRead` w3 @ 0x00269568 — [codegen] insn 46: expected `addiu	t3,t3,0` built `addiu	t3,t3,1632`
- PRE-MATCHED `sceMcSeek` w3 @ 0x00269400 — already had a PAL body
- PRE-MATCHED `sceMcSync` w1 @ 0x00269878 — already had a PAL body
- PRE-MATCHED `sceMcUnformat` w3 @ 0x0026A450 — already had a PAL body

### src/cod/vendor_26A630
- PRE-MATCHED `_ErrMessage` w2 @ 0x0026C188 — already had a PAL body
- PRE-MATCHED `_Error` w1 @ 0x0026C1C8 — already had a PAL body
- PRE-MATCHED `_Error1` w1 @ 0x0026C198 — already had a PAL body
- PRE-MATCHED `_RefImageInit` w1 @ 0x0026C2F8 — already had a PAL body
- PRE-MATCHED `_alalcAlloc` w1 @ 0x0026BA88 — already had a PAL body
- PRE-MATCHED `_alalcFree` w1 @ 0x0026BA78 — already had a PAL body
- PRE-MATCHED `_alalcInit` w1 @ 0x0026BA50 — already had a PAL body
- PRE-MATCHED `_alalcRest` w1 @ 0x0026BAF0 — already had a PAL body
- PRE-MATCHED `_alalcSetDynamic` w1 @ 0x0026BA68 — already had a PAL body
- REVERTED `_ch3dmaCSC` w3 @ 0x00271A20 — [unresolved-symbol] unresolved-symbol: insn 53 `D_0054D140`: pal symbol D_0FFFCAC0 (0x0FFFCAC0) undefined (+1 more)
- REVERTED `_ch4dma` w1 @ 0x00271D28 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PRE-MATCHED `_clearOnce` w1 @ 0x0026C070 — already had a PAL body
- REVERTED `_copyAddRefImage` w1 @ 0x0026E878 — [codegen] insn 2: expected `addiu	t2,t2,0` built `addiu	t2,t2,17136`
- PRE-MATCHED `_decodeOrSkip` w1 @ 0x0026BDB8 — already had a PAL body
- REVERTED `_defRestartDMA` w2 @ 0x0026CBB8 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PRE-MATCHED `_defStopDMA` w2 @ 0x0026CBA8 — already had a PAL body
- PRE-MATCHED `_dispatchMpegCallback` w1 @ 0x0026B930 — already had a PAL body
- PRE-MATCHED `_dispatchMpegCbNodata` w1 @ 0x0026B980 — already had a PAL body
- REVERTED `_dmVector` w1 @ 0x0026EB48 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_doCSC` w1 @ 0x00271938 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_extrainfo` w1 @ 0x00270838 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PRE-MATCHED `_initSeqAgain` w1 @ 0x0026BFD8 — already had a PAL body
- REVERTED `_ipuSetMPEG1` w1 @ 0x0026E938 — [codegen] insn 8: expected `jr	ra` built `sw	v0,0(a1)`
- REVERTED `_isOutSizeOK` w1 @ 0x00271200 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PRE-MATCHED `_lastFrame` w1 @ 0x0026BFE8 — already had a PAL body
- REVERTED `_markOutput` w1 @ 0x00271490 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_mbAddressIncrement` w1 @ 0x0026ECF0 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_motionVector` w1 @ 0x0026FA50 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_nextHeader` w1 @ 0x00270360 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_nextStartCode` w1 @ 0x00270288 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PRE-MATCHED `_pack_header` w1 @ 0x0026ACC0 — already had a PAL body
- PRE-MATCHED `_pictureSpatialScalableExtension` w2 @ 0x0026CB88 — already had a PAL body
- PRE-MATCHED `_pictureTemporalScalableExtension` w2 @ 0x0026CB98 — already had a PAL body
- PRE-MATCHED `_ri0_000` w1 @ 0x0026DBE0 — already had a PAL body
- PRE-MATCHED `_ri0_001` w1 @ 0x0026DD30 — already had a PAL body
- PRE-MATCHED `_ri0_010` w1 @ 0x0026DEB0 — already had a PAL body
- PRE-MATCHED `_ri0_011` w1 @ 0x0026E060 — already had a PAL body
- PRE-MATCHED `_ri0_100` w1 @ 0x0026E208 — already had a PAL body
- PRE-MATCHED `_ri0_101` w1 @ 0x0026E3A0 — already had a PAL body
- PRE-MATCHED `_ri0_110` w1 @ 0x0026E568 — already had a PAL body
- PRE-MATCHED `_ri0_111` w1 @ 0x0026E760 — already had a PAL body
- PRE-MATCHED `_rix_000` w1 @ 0x0026DB68 — already had a PAL body
- PRE-MATCHED `_rix_001` w1 @ 0x0026DC78 — already had a PAL body
- PRE-MATCHED `_rix_010` w1 @ 0x0026DE00 — already had a PAL body
- PRE-MATCHED `_rix_011` w1 @ 0x0026DF68 — already had a PAL body
- REVERTED `_rix_100` w1 @ 0x0026E160 — [codegen] insn 31: expected `bgtz	a3,24 <_rix_100+0x24>` built `sll	zero,zero,0x0`
- PRE-MATCHED `_rix_101` w1 @ 0x0026E2B8 — already had a PAL body
- PRE-MATCHED `_rix_110` w1 @ 0x0026E488 — already had a PAL body
- PRE-MATCHED `_rix_111` w1 @ 0x0026E638 — already had a PAL body
- PRE-MATCHED `_sceMpegFlush` w1 @ 0x0026BF68 — already had a PAL body
- REVERTED `_sendIpuCommand` w1 @ 0x0026FB90 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PRE-MATCHED `_sequenceScalableExtension` w2 @ 0x0026CB68 — already had a PAL body
- REVERTED `_setDefaultQM` w1 @ 0x0026C8A0 — [codegen] insn 11: expected `jal	0 <_setDefaultQM>` built `jal	1300 <_dispatchMpegCallback>`
- REVERTED `_sliceA0` w1 @ 0x0026EF28 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sliceB` w1 @ 0x002702F0 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitGet` w1 @ 0x00272148 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitInit` w1 @ 0x00272058 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitJump` w1 @ 0x002721E0 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitMarker` w1 @ 0x00272198 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitNext` w1 @ 0x00272090 — [codegen] insn 5: expected `jr	ra` built `dsra32	v0,v0,0x0`
- REVERTED `_sysbitPtr` w1 @ 0x00272238 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PRE-MATCHED `_system_header` w1 @ 0x0026AE10 — already had a PAL body
- PRE-MATCHED `_unknown_extension` w2 @ 0x0026CB78 — already had a PAL body
- REVERTED `func_0026E8D8` w1 @ 0x0026E8D8 — [codegen] insn 1: expected `lui	t2,0x27` built `lui	t2,0x25`
- PRE-MATCHED `sceMpegAddBs` w1 @ 0x0026B6F0 — already had a PAL body
- PRE-MATCHED `sceMpegAddCallback` w1 @ 0x0026B908 — already had a PAL body
- PRE-MATCHED `sceMpegClearRefBuff` w1 @ 0x0026B8A0 — already had a PAL body
- PRE-MATCHED `sceMpegDelete` w2 @ 0x0026B6E8 — already had a PAL body
- PRE-MATCHED `sceMpegDemuxPss` w1 @ 0x0026ABA8 — already had a PAL body
- PRE-MATCHED `sceMpegDispCenterOffX` w2 @ 0x0026BA08 — already had a PAL body
- PRE-MATCHED `sceMpegDispCenterOffY` w2 @ 0x0026BA18 — already had a PAL body
- PRE-MATCHED `sceMpegDispHeight` w1 @ 0x0026B9F8 — already had a PAL body
- PRE-MATCHED `sceMpegDispWidth` w1 @ 0x0026B9E8 — already had a PAL body
- PRE-MATCHED `sceMpegGetDecodeMode` w1 @ 0x0026B820 — already had a PAL body
- PRE-MATCHED `sceMpegGetPicture` w1 @ 0x0026B728 — already had a PAL body
- PRE-MATCHED `sceMpegGetPictureRAW8` w1 @ 0x0026B770 — already had a PAL body
- PRE-MATCHED `sceMpegGetPictureRAW8xy` w1 @ 0x0026B7B8 — already had a PAL body
- PRE-MATCHED `sceMpegIsEnd` w1 @ 0x0026B840 — already had a PAL body
- PRE-MATCHED `sceMpegIsRefBuffEmpty` w1 @ 0x0026B850 — already had a PAL body
- PRE-MATCHED `sceMpegReset` w1 @ 0x0026B860 — already had a PAL body
- PRE-MATCHED `sceMpegResetDefaultPtsGap` w1 @ 0x0026B9C0 — already had a PAL body
- PRE-MATCHED `sceMpegSetDecodeMode` w1 @ 0x0026B808 — already had a PAL body
- PRE-MATCHED `sceMpegSetDefaultPtsGap` w1 @ 0x0026B9A8 — already had a PAL body
- PRE-MATCHED `sceMpegSetImageBuff` w1 @ 0x0026B9D0 — already had a PAL body
- PRE-MATCHED `sceSetBrokenLink` w1 @ 0x0026BA28 — already had a PAL body
- PRE-MATCHED `sceSetPtm` w1 @ 0x0026BA38 — already had a PAL body
- REVERTED `setD3_CHCR` w2 @ 0x00272268 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `setD4_CHCR` w2 @ 0x002722D0 — [codegen] tu-size: TU .text 0x7CFC != PAL span 0x7D08 (trailing pad word / extra code)

### src/cod/vendor_272338
- PRE-MATCHED `_SgContLoopCount` w1 @ 0x002763C8 — already had a PAL body
- PRE-MATCHED `_SgContPolta` w1 @ 0x00275948 — already had a PAL body
- PRE-MATCHED `_SgDeltaTime` w1 @ 0x00276698 — already had a PAL body
- PRE-MATCHED `_SgGetComContext` w2 @ 0x00273258 — already had a PAL body
- PRE-MATCHED `_SgGetHeadContext` w2 @ 0x002732C0 — already had a PAL body
- PRE-MATCHED `_SgGetIop2EeContext` w2 @ 0x002732D0 — already had a PAL body
- PRE-MATCHED `_SgGetPacketCntext` w1 @ 0x002732E0 — already had a PAL body
- PRE-MATCHED `_SgGetSeVolValue` w2 @ 0x00273298 — already had a PAL body
- PRE-MATCHED `_SgGetSeqContext` w1 @ 0x00273240 — already had a PAL body
- PRE-MATCHED `_SgGetSlotContext` w1 @ 0x00273228 — already had a PAL body
- PRE-MATCHED `_SgGetVabContext` w1 @ 0x00273268 — already had a PAL body
- PRE-MATCHED `_SgIntoKeyOn` w1 @ 0x00275180 — already had a PAL body
- PRE-MATCHED `_SgPitchTableVag` w1 @ 0x00275208 — already had a PAL body
- PRE-MATCHED `_SgProgChange` w1 @ 0x002755E0 — already had a PAL body
- PRE-MATCHED `_SgSeKeyOff` w1 @ 0x00274F30 — already had a PAL body
- PRE-MATCHED `_SgSeqKeyOnSlot` w1 @ 0x00274BC0 — already had a PAL body
- PRE-MATCHED `_SgSetSeContext` w2 @ 0x002732B0 — already had a PAL body
- PRE-MATCHED `_SgSetSeVolValue` w1 @ 0x00273280 — already had a PAL body
- PORTED `_SgSndn2Remote` w1 @ 0x00276A80 <- aug6 common/src/PObj:func_00258820 (3 syms rebound)
- PRE-MATCHED `_SgTempoChange` w1 @ 0x00275550 — already had a PAL body
- PRE-MATCHED `_SgfadeParam` w1 @ 0x002768B0 — already had a PAL body
- PRE-MATCHED `func_002725D8` w2 @ 0x002725D8 — already had a PAL body
- PRE-MATCHED `sceIpuStopDMA` w1 @ 0x00272338 — already had a PAL body
- PRE-MATCHED `sceIpuSync` w1 @ 0x00272570 — already had a PAL body

### src/cod/vendor_276AD0
- PRE-MATCHED `SgBgmClose` w1 @ 0x00277218 — already had a PAL body
- PRE-MATCHED `SgBgmOpen` w1 @ 0x002770B0 — already had a PAL body
- PRE-MATCHED `SgCalledTickProc` w1 @ 0x00276C28 — already had a PAL body
- PRE-MATCHED `SgDmaRead` w1 @ 0x00276CA0 — already had a PAL body
- PRE-MATCHED `SgDmaWrite` w1 @ 0x00276C70 — already had a PAL body
- PRE-MATCHED `SgGetBgmStatus` w1 @ 0x002779A0 — already had a PAL body
- PRE-MATCHED `SgGetBgmTempo` w1 @ 0x00277970 — already had a PAL body
- PRE-MATCHED `SgInit` w2 @ 0x00276BA8 — already had a PAL body
- PRE-MATCHED `SgInitHot` w1 @ 0x00276BB0 — already had a PAL body
- PRE-MATCHED `SgQuit` w1 @ 0x00276BB8 — already had a PAL body
- PRE-MATCHED `SgSeStop` w1 @ 0x00277DE0 — already had a PAL body
- PRE-MATCHED `SgSeStopAll` w1 @ 0x00277F10 — already had a PAL body
- PRE-MATCHED `SgSetBgmTempo` w1 @ 0x002778C8 — already had a PAL body
- PRE-MATCHED `SgSetBgmVol` w1 @ 0x00277480 — already had a PAL body
- PRE-MATCHED `SgSetDigitalOutputMode` w1 @ 0x00276C58 — already had a PAL body
- PRE-MATCHED `SgSetMasterVol` w1 @ 0x00277468 — already had a PAL body
- PRE-MATCHED `SgSetOutputMode` w1 @ 0x00277318 — already had a PAL body
- PRE-MATCHED `SgSetReverbDelaytime` w1 @ 0x002772E8 — already had a PAL body
- PRE-MATCHED `SgSetReverbDepth` w1 @ 0x002772D0 — already had a PAL body
- PRE-MATCHED `SgSetReverbEndAddr` w1 @ 0x002772A0 — already had a PAL body
- PRE-MATCHED `SgSetReverbFeedback` w1 @ 0x00277300 — already had a PAL body
- PRE-MATCHED `SgSetReverbType` w1 @ 0x002772B8 — already had a PAL body
- PRE-MATCHED `SgSetSeMasterVol` w1 @ 0x00277528 — already had a PAL body
- PRE-MATCHED `SgSetSePitchDirect` w1 @ 0x00278058 — already had a PAL body
- PRE-MATCHED `SgSetSeVolDirect` w1 @ 0x00277FB8 — already had a PAL body
- PRE-MATCHED `SgSetSpuSlotFree` w1 @ 0x002782A0 — already had a PAL body
- PRE-MATCHED `SgSetTickMode` w1 @ 0x00277340 — already had a PAL body
- PRE-MATCHED `SgSndn2RemoteSync` w1 @ 0x00276B60 — already had a PAL body
- PRE-MATCHED `SgStAdpcmChannelPitch` w1 @ 0x00278468 — already had a PAL body
- PRE-MATCHED `SgStAdpcmChannelVolume` w1 @ 0x002783E0 — already had a PAL body
- PRE-MATCHED `SgStAdpcmClose` w1 @ 0x002783A0 — already had a PAL body
- PRE-MATCHED `SgStAdpcmInit` w1 @ 0x002782E0 — already had a PAL body
- PRE-MATCHED `SgStAdpcmIopReadAddr` w1 @ 0x002785A0 — already had a PAL body
- PRE-MATCHED `SgStAdpcmPlay` w1 @ 0x002784E0 — already had a PAL body
- PRE-MATCHED `SgStAdpcmQuit` w1 @ 0x002782F8 — already had a PAL body
- PRE-MATCHED `SgStAdpcmStop` w1 @ 0x00278540 — already had a PAL body
- PORTED `SgStPcmBufMode` w1 @ 0x00278870 <- aug6 common/src/PObj:func_0025A610 (2 syms rebound)
- PRE-MATCHED `SgStPcmClose` w1 @ 0x002786B0 — already had a PAL body
- PRE-MATCHED `SgStPcmInit` w1 @ 0x00278610 — already had a PAL body
- PRE-MATCHED `SgStPcmIopReadAddr` w1 @ 0x00278828 — already had a PAL body
- PRE-MATCHED `SgStPcmLseek` w1 @ 0x00278788 — already had a PAL body
- PRE-MATCHED `SgStPcmOpen` w1 @ 0x00278640 — already had a PAL body
- PRE-MATCHED `SgStPcmPlay` w1 @ 0x00278708 — already had a PAL body
- PRE-MATCHED `SgStPcmQuit` w1 @ 0x00278628 — already had a PAL body
- PRE-MATCHED `SgStPcmSetEffect` w1 @ 0x002786F0 — already had a PAL body
- PRE-MATCHED `SgStPcmStop` w1 @ 0x00278748 — already had a PAL body
- PRE-MATCHED `SgStPcmVolume` w1 @ 0x002787D8 — already had a PAL body
- PRE-MATCHED `SgVabClose` w1 @ 0x00276F50 — already had a PAL body
- PRE-MATCHED `SgVabOpen` w1 @ 0x00276DE8 — already had a PAL body

### src/cod/vendor_2788D8
- PRE-MATCHED `__ieee754_sqrtf` w1 @ 0x00279F18 — already had a PAL body
- PRE-MATCHED `__kernel_cosf` w1 @ 0x0027A050 — already had a PAL body
- PRE-MATCHED `copysignf` w1 @ 0x0027B160 — already had a PAL body
- PRE-MATCHED `fabsf` w1 @ 0x0027AED0 — already had a PAL body
- REVERTED `fmodf` w1 @ 0x00278CF0 — [callee-sig-conflict] src/cod/vendor_2788D8.c:51: conflicting types for `__ieee754_fmodf'
- PRE-MATCHED `isnanf` w1 @ 0x0027AFD8 — already had a PAL body
- PRE-MATCHED `matherr` w1 @ 0x0027AC00 — already had a PAL body
- PRE-MATCHED `sinf` w1 @ 0x002788D8 — already had a PAL body

### src/cod/vendor_27B190
- REVERTED `__do_global_dtors` w3 @ 0x0027B190 — [unresolved-symbol] unresolved-symbol: insn 8 `D_0054D210`: no pal lui partner for %lo (+2 more)
- PRE-MATCHED `__fpcmp_parts_d` w1 @ 0x0027D5E8 — already had a PAL body
- PRE-MATCHED `__fpcmp_parts_f` w1 @ 0x0027E1F0 — already had a PAL body
- REVERTED `__main` w1 @ 0x0027B298 — [unresolved-symbol] unresolved-symbol: D_007181E8 undefined on the PAL side (unrebindable raw-constant reference)
- PRE-MATCHED `__make_dp` w1 @ 0x0027D978 — already had a PAL body
- PRE-MATCHED `__make_fp` w1 @ 0x0027E570 — already had a PAL body
- PRE-MATCHED `__negdf2` w1 @ 0x0027D940 — already had a PAL body
- PRE-MATCHED `__negsf2` w1 @ 0x0027E538 — already had a PAL body
- PRE-MATCHED `dpadd` w1 @ 0x0027D118 — already had a PAL body
- PRE-MATCHED `dpcmp` w1 @ 0x0027D700 — already had a PAL body
- PRE-MATCHED `dpdiv` w1 @ 0x0027D480 — already had a PAL body
- PRE-MATCHED `dpsub` w1 @ 0x0027D170 — already had a PAL body
- PRE-MATCHED `dptofp` w1 @ 0x0027D9A8 — already had a PAL body
- PRE-MATCHED `fpadd` w1 @ 0x0027DDD8 — already had a PAL body
- PRE-MATCHED `fpcmp` w1 @ 0x0027E308 — already had a PAL body
- REVERTED `fpdiv` w1 @ 0x0027E090 — [parse] src/cod/vendor_27B190.c:7: parse error before `*'
- PRE-MATCHED `fpsub` w1 @ 0x0027DE30 — already had a PAL body
- PRE-MATCHED `fptodp` w1 @ 0x0027E5A0 — already had a PAL body

### src/cod/vendor_27E5E0
- PRE-MATCHED `_Bfree` w1 @ 0x00286588 — already had a PAL body
- PRE-MATCHED `__assert` w1 @ 0x0027E5E0 — already had a PAL body
- PRE-MATCHED `__errno` w2 @ 0x0027E640 — already had a PAL body
- PRE-MATCHED `__malloc_lock` w2 @ 0x002864D0 — already had a PAL body
- PRE-MATCHED `__malloc_unlock` w2 @ 0x002864D8 — already had a PAL body
- PRE-MATCHED `__mcmp` w1 @ 0x00286E40 — already had a PAL body
- PRE-MATCHED `__sclose` w1 @ 0x00287C98 — already had a PAL body
- PRE-MATCHED `__sfmoreglue` w1 @ 0x00284A80 — already had a PAL body
- PRE-MATCHED `__sigtramp` w2 @ 0x00287AA0 — already had a PAL body
- REVERTED `__sinit` w1 @ 0x00284BF0 — [codegen] insn 3: expected `addiu	v0,v0,0` built `addiu	v0,v0,26096`
- PRE-MATCHED `__sprint` w2 @ 0x00280118 — already had a PAL body
- PRE-MATCHED `__sread` w1 @ 0x00287B48 — already had a PAL body
- PRE-MATCHED `__sseek` w1 @ 0x00287C30 — already had a PAL body
- PRE-MATCHED `__swrite` w1 @ 0x00287BB0 — already had a PAL body
- PRE-MATCHED `_cleanup` w2 @ 0x00284BE0 — already had a PAL body
- REVERTED `_cleanup_r` w2 @ 0x00284BD0 — [codegen] insn 1: expected `j	0 <_cleanup_r>` built `j	7028 <_fwalk>`
- PRE-MATCHED `_close_r` w1 @ 0x00289200 — already had a PAL body
- PRE-MATCHED `_fstat_r` w2 @ 0x00289258 — already had a PAL body
- PRE-MATCHED `_getpid_r` w2 @ 0x00287B28 — already had a PAL body
- PRE-MATCHED `_hi0bits` w1 @ 0x00286818 — already had a PAL body
- PRE-MATCHED `_i2b` w1 @ 0x00286960 — already had a PAL body
- PRE-MATCHED `_init_signal` w2 @ 0x00287A78 — already had a PAL body
- PRE-MATCHED `_kill_r` w2 @ 0x00287AC8 — already had a PAL body
- PRE-MATCHED `_lo0bits` w1 @ 0x002868A0 — already had a PAL body
- PRE-MATCHED `_localeconv_r` w2 @ 0x00285728 — already had a PAL body
- PRE-MATCHED `_lseek_r` w2 @ 0x002892B8 — already had a PAL body
- PRE-MATCHED `_malloc_trim_r` w1 @ 0x002850C0 — already had a PAL body
- PRE-MATCHED `_mbtowc_r` w1 @ 0x002862B0 — already had a PAL body
- PRE-MATCHED `_mprec_log10` w1 @ 0x00287490 — already had a PAL body
- PRE-MATCHED `_printf_r` w1 @ 0x0027E888 — already had a PAL body
- PRE-MATCHED `_read_r` w2 @ 0x00289318 — already had a PAL body
- PRE-MATCHED `_s2b` w1 @ 0x002866D0 — already had a PAL body
- PRE-MATCHED `_sbrk_r` w1 @ 0x00287718 — already had a PAL body
- PRE-MATCHED `_setlocale_r` w1 @ 0x002856A0 — already had a PAL body
- PRE-MATCHED `_signal_r` w1 @ 0x002877E8 — already had a PAL body
- PRE-MATCHED `_sprintf_r` w1 @ 0x0027F380 — already had a PAL body
- PRE-MATCHED `_write_r` w2 @ 0x002890E0 — already had a PAL body
- PRE-MATCHED `atoi` w1 @ 0x0027E618 — already had a PAL body
- PRE-MATCHED `eofread` w2 @ 0x0027F458 — already had a PAL body
- REVERTED `fiprintf` w1 @ 0x0027E650 — [callee-sig-conflict] src/cod/vendor_27E5E0.c:40: conflicting types for `fiprintf'
- PRE-MATCHED `fread` w1 @ 0x00284C80 — already had a PAL body
- PRE-MATCHED `func_00280E60` w2 @ 0x00280E60 — already had a PAL body
- PRE-MATCHED `func_002834F8` w1 @ 0x002834F8 — already had a PAL body
- PRE-MATCHED `func_00283518` w2 @ 0x00283518 — already had a PAL body
- PRE-MATCHED `isinf` w1 @ 0x00287698 — already had a PAL body
- PRE-MATCHED `isnan` w1 @ 0x002876E0 — already had a PAL body
- PRE-MATCHED `lflush` w2 @ 0x00287500 — already had a PAL body
- PRE-MATCHED `localeconv` w2 @ 0x00285768 — already had a PAL body
- PRE-MATCHED `memset` w1 @ 0x0027E7C8 — already had a PAL body
- PRE-MATCHED `printf` w1 @ 0x0027E8C8 — already had a PAL body
- PRE-MATCHED `raise` w2 @ 0x00287A20 — already had a PAL body
- PRE-MATCHED `rand` w1 @ 0x0027F350 — already had a PAL body
- PRE-MATCHED `setlocale` w2 @ 0x00285738 — already had a PAL body
- PRE-MATCHED `signal` w2 @ 0x00287A48 — already had a PAL body
- PRE-MATCHED `sprintf` w1 @ 0x0027F3E8 — already had a PAL body
- PRE-MATCHED `srand` w1 @ 0x0027F340 — already had a PAL body
- REVERTED `std` w1 @ 0x00284A28 — [codegen] insn 0: expected `lui	v0,0x0` built `lui	v0,0x1`
- PRE-MATCHED `strcat` w1 @ 0x0027F4E8 — already had a PAL body
- PRE-MATCHED `strrchr` w1 @ 0x0027FD20 — already had a PAL body
- PRE-MATCHED `strtodf` w1 @ 0x00288BE8 — already had a PAL body
- PRE-MATCHED `strtok` w1 @ 0x0027FDE0 — already had a PAL body
- PRE-MATCHED `strtol` w2 @ 0x002800E0 — already had a PAL body
- PRE-MATCHED `strtoul` w2 @ 0x00288E30 — already had a PAL body
- PRE-MATCHED `vsprintf` w1 @ 0x00283390 — already had a PAL body

### src/cod/vendor_2898E8
- PRE-MATCHED `InvalidDCache` w2 @ 0x00289AD0 — already had a PAL body
- PRE-MATCHED `SyncDCache` w2 @ 0x00289990 — already had a PAL body
- PRE-MATCHED `_sceIDC` w1 @ 0x00289A28 — already had a PAL body
- PRE-MATCHED `_sceSDC` w1 @ 0x002898E8 — already had a PAL body
- PORTED `iInvalidDCache` w2 @ 0x00289B50 <- aug6 common/src/PObj:func_0026B8F0 (2 syms rebound)
- PRE-MATCHED `iSyncDCache` w2 @ 0x00289A10 — already had a PAL body

### src/cod/vendor_289B68
- REVERTED `__fixdfdi` w1 @ 0x00289B68 — [codegen] insn 8: expected `bgez	v0,40 <__fixdfdi+0x40>` built `bgez	v0,50 <__fixdfdi+0x50>`

### src/commonact
- PRE-MATCHED `ACTAdjustPlane` w1 @ 0x00161AE0 — already had a PAL body
- REVERTED `ACTMotDirToWall` w3 @ 0x00163A78 — [codegen] insn 9: expected `addiu	a1,a1,1200` built `addiu	a1,a1,1184`
- PRE-MATCHED `ACTSetPositionNoFitting` w2 @ 0x00158C90 — already had a PAL body
- PRE-MATCHED `ACTSetPositionNodeWithFitting` w2 @ 0x00158C98 — already had a PAL body
- REVERTED `ACTSetPositionWithFitting` w2 @ 0x00158C88 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)
- PRE-MATCHED `ControlMotionOrient` w1 @ 0x001639C8 — already had a PAL body
- PRE-MATCHED `SetCorrectOrientOfChain` w1 @ 0x00163AC0 — already had a PAL body
- PRE-MATCHED `SetDirectRootPositionXZ` w1 @ 0x0015BD48 — already had a PAL body
- PRE-MATCHED `_ACTMotDir_V` w1 @ 0x00163A38 — already had a PAL body
- PRE-MATCHED `actAfterSlip` w2 @ 0x00163CC8 — already had a PAL body
- PRE-MATCHED `afterCommonBox` w1 @ 0x00163D38 — already had a PAL body
- PRE-MATCHED `afterCommonCling` w2 @ 0x00163CA0 — already had a PAL body
- PRE-MATCHED `afterCommonOneWall` w2 @ 0x00163EF8 — already had a PAL body
- PRE-MATCHED `afterCommonRevive` w2 @ 0x00163CD8 — already had a PAL body
- REVERTED `afterCommonStone` w3 @ 0x00163D00 — [codegen] insn 6: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- PRE-MATCHED `debugDispSphere` w1 @ 0x0015E388 — already had a PAL body
- PRE-MATCHED `func_0015BD00` w1 @ 0x0015BD00 — already had a PAL body
- PORTED `func_0015BF40` w1 @ 0x0015BF40 <- aug6 fumi/src/commonact:func_001561E8 (2 syms rebound)
- PORTED `func_001631F0` w2 @ 0x001631F0 <- aug6 fumi/src/commonact:func_0015CB20 (4 syms rebound)
- PORTED `func_00163220` w2 @ 0x00163220 <- aug6 fumi/src/commonact:funcCommonBeginReady (4 syms rebound)

### src/darkVolume
- PRE-MATCHED `DarkVolumeDL` w2 @ 0x001D6F78 — already had a PAL body
- PRE-MATCHED `ExecGameOverEffect` w2 @ 0x001D6F80 — already had a PAL body
- PRE-MATCHED `GetGameOverEffectCenterPosition` w2 @ 0x001D6D20 — already had a PAL body
- PORTED `ResetGameOverEffect` w2 @ 0x001D7078 <- aug6 sugipon/src/effectTool:dispXZYZCircle (3 syms rebound)
- PRE-MATCHED `SetDarkVolumeEffect` w1 @ 0x001D6AA8 — already had a PAL body
- PRE-MATCHED `StartQueenAttackEffect` w1 @ 0x001D7020 — already had a PAL body

### src/debug
- PRE-MATCHED `CloseVif1DirectPacket` w1 @ 0x001B3E20 — already had a PAL body
- REVERTED `RestoreNormalDrawEnvironment` w1 @ 0x001B3EB8 — [codegen] insn 1: expected `lui	v0,0x0` built `lui	v0,0x2000`
- PRE-MATCHED `SendVif1DirectPacket` w1 @ 0x001B3E60 — already had a PAL body
- PRE-MATCHED `debugCdvdLoadInfoSegAdd` w1 @ 0x001B3078 — already had a PAL body
- PRE-MATCHED `debugCdvdLoadInfoSegCls` w1 @ 0x001B30A8 — already had a PAL body
- REVERTED `debugCdvdLoadInfoSegDisp` w1 @ 0x001B3AE0 — [codegen] insn 30: expected `addiu	t2,t2,0` built `addiu	t2,t2,23408`
- PRE-MATCHED `debugCdvdLoadInfoSegInit` w1 @ 0x001B3030 — already had a PAL body
- PRE-MATCHED `debugSceClose` w1 @ 0x001B2FC0 — already had a PAL body
- PRE-MATCHED `debugSceCloseFdNew` w1 @ 0x001B2FF0 — already had a PAL body
- PORTED `debugSceOpen` w1 @ 0x001B2F60 <- aug6 common/src/debug_menu:func_001A7A88 (7 syms rebound)
- REVERTED `debug_AdpcmTest` w3 @ 0x001B3A50 — [codegen] insn 6: expected `addiu	v0,zero,105` built `addiu	v0,zero,96`
- REVERTED `debug_Assert` w3 @ 0x001ABC40 — [codegen] insn 15: expected `addiu	a1,zero,1392` built `addiu	a1,zero,1268`
- PRE-MATCHED `debug_BackStageTest` w1 @ 0x001B3C18 — already had a PAL body
- PRE-MATCHED `debug_BeginTimer` w1 @ 0x001B2800 — already had a PAL body
- PRE-MATCHED `debug_CallbackGsFinish` w2 @ 0x001B3110 — already had a PAL body
- PRE-MATCHED `debug_ClearFontWindow` w1 @ 0x001B2958 — already had a PAL body
- PRE-MATCHED `debug_DispMatrix` w1 @ 0x001B2C80 — already had a PAL body
- SKIPPED `debug_DispQW` w2 @ 0x001AF2B8 — jtbl
- PRE-MATCHED `debug_EndingDemo` w2 @ 0x001B3BF8 — already had a PAL body
- PRE-MATCHED `debug_FlushFont` w2 @ 0x001AD380 — already had a PAL body
- PRE-MATCHED `debug_FreeCamera` w1 @ 0x001B3DE0 — already had a PAL body
- PRE-MATCHED `debug_GameOver` w2 @ 0x001B3BD8 — already had a PAL body
- PORTED `debug_GetTimerCount` w1 @ 0x001B28F8 <- aug6 common/src/debug_menu:func_001A7420 (1 syms rebound)
- PORTED `debug_GetTimerSec` w1 @ 0x001B2828 <- aug6 common/src/debug_menu:func_001A7350 (2 syms rebound)
- PORTED `debug_Init` w1 @ 0x001AC258 <- aug6 common/src/debug:debug_Load (10 syms rebound)
- PRE-MATCHED `debug_LogPrintf` w1 @ 0x001ABCF0 — already had a PAL body
- PRE-MATCHED `debug_Menu_off` w2 @ 0x001B27F8 — already had a PAL body
- PRE-MATCHED `debug_PrintFont` w1 @ 0x001AD058 — already had a PAL body
- PRE-MATCHED `debug_PrintFontWindowDummy` w1 @ 0x001AF870 — already had a PAL body
- PORTED `debug_PrintMatrix` w1 @ 0x001AFA78 <- aug6 common/src/debug_exception:debug_SetExceptionMessage (5 syms rebound)
- PRE-MATCHED `debug_Printf` w2 @ 0x001AF4A0 — already had a PAL body
- PRE-MATCHED `debug_Printf2` w2 @ 0x001AF510 — already had a PAL body
- PRE-MATCHED `debug_PrintfDummy` w1 @ 0x001AF850 — already had a PAL body
- PRE-MATCHED `debug_ResetBar` w1 @ 0x001B2B08 — already had a PAL body
- PRE-MATCHED `debug_ResizeFontWindowHeight` w2 @ 0x001B2990 — already had a PAL body
- PRE-MATCHED `debug_SETest_color` w1 @ 0x001B3970 — already had a PAL body
- PRE-MATCHED `debug_STAFFROLLTest` w1 @ 0x001B3948 — already had a PAL body
- PORTED `debug_SelectCsvWindowVal` w1 @ 0x001B0128 <- aug6 common/src/debug_exception:func_001A4C58 (8 syms rebound)
- PRE-MATCHED `debug_SetBarDummy` w2 @ 0x001B2CC8 — already had a PAL body
- REVERTED `debug_SetDmaCallback` w1 @ 0x001AC088 — [codegen] insn 9: expected `addiu	a1,a1,0` built `addiu	a1,a1,29904`
- PRE-MATCHED `debug_StdPrintfDummy` w1 @ 0x001AF898 — already had a PAL body
- PRE-MATCHED `debug_TryToGetStartStage` w2 @ 0x001B2F58 — already had a PAL body
- PRE-MATCHED `debug_closeLog` w2 @ 0x001B3028 — already had a PAL body
- PRE-MATCHED `debug_mcTest` w2 @ 0x001B3928 — already had a PAL body
- PRE-MATCHED `debug_openLog` w1 @ 0x001ABCD8 — already had a PAL body
- PRE-MATCHED `debug_saveNumFunc` w3 @ 0x001B38F8 — already had a PAL body
- PRE-MATCHED `debug_tsuresariTimeZero` w2 @ 0x001B3C40 — already had a PAL body
- PRE-MATCHED `getBuffer` w2 @ 0x001B02A8 — already had a PAL body
- PRE-MATCHED `getLineBuffer` w1 @ 0x001B0290 — already had a PAL body
- PRE-MATCHED `gsResetFunc` w1 @ 0x001B30D0 — already had a PAL body
- PRE-MATCHED `resetGS` w2 @ 0x001B4A40 — already had a PAL body
- PRE-MATCHED `resetPath` w1 @ 0x001B49A0 — already had a PAL body
- PRE-MATCHED `saveBack` w1 @ 0x001B4DE8 — already had a PAL body
- PORTED `syncGS` w1 @ 0x001B4F20 <- aug6 common/src/gamesys:func_001A99D0 (12 syms rebound)

### src/debug_exception
- REVERTED `debugExceptionInit` w1 @ 0x001B61B0 — [codegen] src/debug_exception.c:21: request for member `x' in something not a structure or union
- PRE-MATCHED `debugIOPExceptionInit` w2 @ 0x001B6228 — already had a PAL body

### src/debug_menu
- PORTED `debug_TargetGObj_Func` w1 @ 0x001B6670 <- aug6 common/src/haveParentSimpleObj:func_001AB120 (3 syms rebound)
- PRE-MATCHED `init_debug_menu` w1 @ 0x001B6658 — already had a PAL body

### src/delayFreeManager
- REVERTED `InitDelayFree` w3 @ 0x00102640 — [codegen] insn 1: expected `addiu	v1,zero,383` built `addiu	v1,zero,127`

### src/e3
- PRE-MATCHED `actE3CageFallReadyChk` w1 @ 0x0021B660 — already had a PAL body
- REVERTED `actE3DoorUp` w3 @ 0x0021B528 — [codegen] insn 5: expected `addiu	a0,zero,55` built `addiu	a0,zero,51`
- PRE-MATCHED `actE3Floor` w2 @ 0x0021AF10 — already had a PAL body
- REVERTED `actE3St01bGene1` w3 @ 0x0021AFB8 — [codegen] insn 17: expected `addiu	a0,zero,362` built `addiu	a0,zero,329`
- REVERTED `actE3St01bGene2` w3 @ 0x0021B070 — [codegen] insn 17: expected `addiu	a0,zero,362` built `addiu	a0,zero,329`
- REVERTED `actE3St01bGene3` w3 @ 0x0021B120 — [codegen] insn 17: expected `addiu	a0,zero,362` built `addiu	a0,zero,329`
- REVERTED `actE3St13cIntroChk` w3 @ 0x0021B5E0 — [codegen] insn 4: expected `addiu	a0,zero,55` built `addiu	a0,zero,51`

### src/ebrain
- REVERTED `GetStageFromLabel` w3 @ 0x00199EE0 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PRE-MATCHED `eBrainInit` w1 @ 0x00199CE8 — already had a PAL body
- PORTED `eBrainStatusSet` w1 @ 0x00199D30 <- aug6 omori/src/ebrain:func_0018F1F0 (4 syms rebound)

### src/effectTool
- PRE-MATCHED `exitEffectTool` w1 @ 0x001D8690 — already had a PAL body
- PRE-MATCHED `setQ` w1 @ 0x001D7C70 — already had a PAL body

### src/end
- REVERTED `actConte14_11` w3 @ 0x0021EC68 — [codegen] insn 7: expected `addiu	a0,zero,852` built `addiu	a0,zero,777`
- REVERTED `actConte14_12` w3 @ 0x0021ED20 — [codegen] insn 6: expected `addiu	a0,zero,853` built `addiu	a0,zero,778`
- REVERTED `actEndDemo11Chk` w3 @ 0x0021EC38 — [codegen] insn 4: expected `addiu	a0,zero,349` built `addiu	a0,zero,317`
- REVERTED `actEndDemo12Chk` w3 @ 0x0021ECF0 — [codegen] insn 4: expected `addiu	a0,zero,350` built `addiu	a0,zero,318`
- REVERTED `actEndDemo13Chk` w3 @ 0x0021EDA8 — [codegen] insn 4: expected `addiu	a0,zero,351` built `addiu	a0,zero,319`
- REVERTED `actStaff1Chk` w2 @ 0x0021EDD8 — [codegen] insn 6: expected `addiu	a0,a0,0` built `addiu	a0,a0,4744`
- REVERTED `actStaff2Chk` w1 @ 0x0021EE00 — [codegen] insn 10: expected `addiu	a0,a0,0` built `addiu	a0,a0,5560`

### src/enemy
- PRE-MATCHED `EnemyAI` w2 @ 0x001D9A28 — already had a PAL body
- PRE-MATCHED `EnemyDL` w1 @ 0x001D98E8 — already had a PAL body
- REVERTED `EnemySetfAppearAll` w3 @ 0x001D9A40 — [codegen] insn 6: expected `lw	a0,2096(v0)` built `lw	a0,2032(v0)`
- REVERTED `EnemySetfDisappearAll` w3 @ 0x001D9A90 — [codegen] insn 9: expected `lw	a0,2096(v0)` built `lw	a0,2032(v0)`
- REVERTED `SetEnemyFootPrintSwitch` w3 @ 0x001D9A30 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- PRE-MATCHED `SetEnemyStonizedVisual` w1 @ 0x001DA050 — already had a PAL body
- PRE-MATCHED `enemySetParticleDie` w1 @ 0x001D9BB8 — already had a PAL body

### src/enemy-control
- REVERTED `EnemyCtrlBeforeFunc` w1 @ 0x0019A0C0 — [codegen] insn 33: expected `<end>` built `sll	zero,zero,0x0`
- PRE-MATCHED `InitEnemyCtrlGeo` w1 @ 0x0019A148 — already had a PAL body
- PORTED `IsSelectID_EnemyCtrl` w1 @ 0x0019A160 <- aug6 omori/src/enemy-control:EnemyCtrlBeforeFunc (4 syms rebound)

### src/enemyParts
- PRE-MATCHED `DispEnemyFootPrints` w1 @ 0x001DAA98 — already had a PAL body
- PRE-MATCHED `DispPointBlur` w1 @ 0x001DABF8 — already had a PAL body
- REVERTED `ExecEnemyFootPrints` w3 @ 0x001DA870 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- REVERTED `InitPointBlur` w3 @ 0x001DAAB8 — [codegen] insn 18: expected `addiu	a3,zero,16` built `addiu	a3,zero,15`
- PRE-MATCHED `ResetEnemyEye` w1 @ 0x001DAD48 — already had a PAL body
- PORTED `UpdateEnemyEye` w1 @ 0x001DAC58 <- aug6 sugipon/src/enemyParts:func_001CCBC0 (5 syms rebound)

### src/enemy_act
- REVERTED `ACTEnemyForceSwitchToCarry` w3 @ 0x0016A2E0 — [codegen] insn 4: expected `jal	0 <ACTEnemyForceSwitchToCarry>` built `jal	14f8 <actEnemyForceSwitchToCarry>`
- REVERTED `EnemyBrainStatus_Boy` w3 @ 0x0016A238 — [codegen] insn 1: expected `lw	v0,1088(v1)` built `lw	v0,1072(v1)`
- REVERTED `EnemyBrainStatus_Girl` w3 @ 0x0016A250 — [codegen] insn 1: expected `lw	v0,1088(v1)` built `lw	v0,1072(v1)`
- PRE-MATCHED `FlyMail` w1 @ 0x0016ACF8 — already had a PAL body
- PRE-MATCHED `GetEnemyType` w2 @ 0x0016A470 — already had a PAL body
- REVERTED `GetEnemyTypeFromGObj` w3 @ 0x0016A460 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `IsEnemyBrainToBoy` w3 @ 0x0016A420 — [codegen] insn 4: expected `addiu	a0,zero,111` built `addiu	a0,zero,107`
- REVERTED `IsEnemyBrainToGenerator` w3 @ 0x0016A3B0 — [codegen] insn 5: expected `lw	v1,1664(a2)` built `lw	v1,1648(a2)`
- REVERTED `_ApproachTarget` w3 @ 0x0016AFC8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `_MustChase` w1 @ 0x001644F8 — already had a PAL body
- PRE-MATCHED `actEnemyFlagCheckActive` w1 @ 0x0016A290 — already had a PAL body
- PRE-MATCHED `actEnemyFlagCheckDead` w1 @ 0x0016A268 — already had a PAL body
- PRE-MATCHED `actEnemyFlagOnDead` w1 @ 0x0016A208 — already had a PAL body
- PRE-MATCHED `actEnemyFlagOnFree` w1 @ 0x0016A178 — already had a PAL body
- PORTED `actEnemyHyde` w1 @ 0x0016A128 <- aug6 fumi/src/enemy_act:actEnemyWalk (5 syms rebound)
- REVERTED `actEnemy_GetClingTarget` w3 @ 0x0016A338 — [codegen] insn 1: expected `lw	a0,1664(v1)` built `lw	a0,1648(v1)`
- REVERTED `actEnemy_isLargeEnemy` w3 @ 0x0016A380 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `actEnemy_isNormalEnemy` w3 @ 0x0016A368 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `actEnemy_isSmallEnemy` w3 @ 0x0016A398 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `afterEnemyBodylift` w3 @ 0x0016B010 — [codegen] insn 4: expected `sw	zero,1360(v1)` built `sw	zero,1344(v1)`
- PRE-MATCHED `isEnemyHyde` w1 @ 0x0016AF98 — already had a PAL body

### src/fieldCollision
- REVERTED `ChangeFieldCollisionDebugMode` w1 @ 0x0016D660 — [callee-sig-conflict] src/fieldCollision.c:383: conflicting types for `D_0063A840__pn'
- PRE-MATCHED `ClipCollision` w1 @ 0x0016D5F0 — already had a PAL body
- PRE-MATCHED `ClipFloor` w1 @ 0x0016D548 — already had a PAL body
- PRE-MATCHED `ClipFloorCheckCB` w1 @ 0x0016D5C8 — already had a PAL body
- PRE-MATCHED `ClipFloorE` w1 @ 0x0016D568 — already had a PAL body
- PRE-MATCHED `ClipFloorIH` w1 @ 0x0016D5A8 — already had a PAL body
- PRE-MATCHED `ClipFloorR` w1 @ 0x0016D588 — already had a PAL body
- PRE-MATCHED `ClipPlane` w1 @ 0x0016D7C8 — already had a PAL body
- PRE-MATCHED `ClipWall` w1 @ 0x0016D3D8 — already had a PAL body
- PRE-MATCHED `ClipWallAdjustPos` w1 @ 0x0016D4B8 — already had a PAL body
- PRE-MATCHED `ClipWallBoxStop` w1 @ 0x0016D498 — already had a PAL body
- PRE-MATCHED `ClipWallCheckCB` w1 @ 0x0016D4F8 — already had a PAL body
- PRE-MATCHED `ClipWallDebug` w1 @ 0x0016D3B8 — already had a PAL body
- PRE-MATCHED `ClipWallE` w1 @ 0x0016D4D8 — already had a PAL body
- PRE-MATCHED `ClipWallEField` w1 @ 0x0016D478 — already had a PAL body
- PRE-MATCHED `ClipWallField` w1 @ 0x0016D458 — already had a PAL body
- PRE-MATCHED `ClipWallFieldCheckCB` w1 @ 0x0016D520 — already had a PAL body
- PRE-MATCHED `ClipWallFuchiHangWalkStop` w1 @ 0x0016D438 — already had a PAL body
- PRE-MATCHED `ClipWallR` w1 @ 0x0016D3F8 — already had a PAL body
- PRE-MATCHED `ClipWallRD` w1 @ 0x0016F140 — already had a PAL body
- PRE-MATCHED `ClipWallVector` w1 @ 0x0016F168 — already had a PAL body
- PRE-MATCHED `ClipWallWaveForce` w1 @ 0x0016D418 — already had a PAL body
- PRE-MATCHED `CompareAttribute` w1 @ 0x0016DA90 — already had a PAL body
- PRE-MATCHED `DBG_VECTOR` w1 @ 0x0016C770 — already had a PAL body
- REVERTED `GetDistanceFromPlane` w1 @ 0x0016DBB0 — [callee-sig-conflict] src/fieldCollision.c:300: conflicting types for `GetDistanceFromPlane'
- PRE-MATCHED `GetFloorAttribute` w1 @ 0x0016DA70 — already had a PAL body
- PRE-MATCHED `GetOrientOfWall` w3 @ 0x0016D8F0 — already had a PAL body
- PRE-MATCHED `GetReflectionElement` w1 @ 0x0016B128 — already had a PAL body
- PRE-MATCHED `GetWallAttribute` w1 @ 0x0016DA50 — already had a PAL body
- PRE-MATCHED `GetYDistanceFromPlane` w1 @ 0x0016DBE0 — already had a PAL body
- PRE-MATCHED `GetYProjectionOfPlane` w1 @ 0x0016DC28 — already had a PAL body
- PRE-MATCHED `LoadCollision` w1 @ 0x0016D6A0 — already had a PAL body
- PRE-MATCHED `MakeExitAttributeIndex` w1 @ 0x0016D068 — already had a PAL body
- PORTED `MapCollisionData` w1 @ 0x0016F1C8 <- aug6 fumi/src/fuzio:func_00167FE8 (1 syms rebound)
- PRE-MATCHED `PositionOfExit` w1 @ 0x0016DC98 — already had a PAL body
- PRE-MATCHED `ResetCollisionPC` w1 @ 0x0016DC68 — already had a PAL body
- PRE-MATCHED `SetSimplePlane` w1 @ 0x0016DA38 — already had a PAL body
- PRE-MATCHED `__ClipFloor` w3 @ 0x0016C268 — already had a PAL body
- PRE-MATCHED `__ClipWall` w3 @ 0x0016C240 — already had a PAL body
- PORTED `_clipW` w1 @ 0x0016DEE0 <- aug6 fumi/src/fuzio:func_00166D00 (5 syms rebound)
- PORTED `_clipWBoxStop` w1 @ 0x0016E810 <- aug6 fumi/src/fuzio:func_00167630 (5 syms rebound)
- PORTED `_clipWEField` w1 @ 0x0016E1A0 <- aug6 fumi/src/fuzio:func_00166FC0 (5 syms rebound)

### src/fightSound
- PRE-MATCHED `fightSoundClose` w1 @ 0x0019A490 — already had a PAL body
- PORTED `fightSoundPlayChk` w2 @ 0x0019A4D8 <- aug6 omori/src/fightSound:fightSoundClose (2 syms rebound)
- PRE-MATCHED `fightSoundProcessRequestPause` w2 @ 0x0019A480 — already had a PAL body
- PRE-MATCHED `fightSoundProcessRequestStart` w2 @ 0x0019A4C8 — already had a PAL body
- PRE-MATCHED `fightSoundProcessRequestStatus` w2 @ 0x0019A4D0 — already had a PAL body

### src/flyManager
- REVERTED `DispFlyInfo` w1 @ 0x001DBBE0 — [codegen] insn 9: expected `<end>` built `sll	zero,zero,0x0`
- PRE-MATCHED `InitFlyInfo` w1 @ 0x001DBC08 — already had a PAL body
- PRE-MATCHED `InitFlyManager` w2 @ 0x001DBC20 — already had a PAL body

### src/frameDependSequence
- PRE-MATCHED `ExecuteSEPackage` w1 @ 0x001DCC88 — already had a PAL body
- REVERTED `ExecuteSEPackageWithGroupVariation` w1 @ 0x001DCC68 — [callee-sig-conflict] src/frameDependSequence.c:24: conflicting types for `ExecuteSEPackageWithGroupVariation'
- PRE-MATCHED `ExecuteSEPackageWithVolumeRate` w1 @ 0x001DCC90 — already had a PAL body
- PRE-MATCHED `StopSEPackage` w2 @ 0x001DCCB8 — already had a PAL body
- PRE-MATCHED `StopSEPackageWithGroupVariation` w3 @ 0x001DCCA0 — already had a PAL body
- PRE-MATCHED `checkModelDataID` w1 @ 0x001DD010 — already had a PAL body
- PRE-MATCHED `checkWaterDepth` w3 @ 0x001DCFF8 — already had a PAL body
- PRE-MATCHED `execSE` w1 @ 0x001DCF90 — already had a PAL body

### src/fuzio
- PRE-MATCHED `fzMagnitude2f` w1 @ 0x0016F2B0 — already had a PAL body
- REVERTED `fzMagnitude2fv` w1 @ 0x0016F330 — [codegen] src/fuzio.c:51: storage size of `diff' isn't known
- PRE-MATCHED `fzMagnitude3f` w1 @ 0x0016F2D8 — already had a PAL body
- PRE-MATCHED `fzMagnitudeByLineSeg` w1 @ 0x0016F470 — already had a PAL body
- PRE-MATCHED `fzMagnitudefv` w1 @ 0x0016F308 — already had a PAL body
- PORTED `fzShowM` w1 @ 0x0016F250 <- aug6 fumi/src/fuzio:func_00168070 (4 syms rebound)
- PORTED `fzShowV` w1 @ 0x0016F1E8 <- aug6 fumi/src/fuzio:func_00168008 (5 syms rebound)

### src/gamesys
- PRE-MATCHED `func_001B6CA0` w1 @ 0x001B6CA0 — already had a PAL body
- REVERTED `func_001B6CF8` w2 @ 0x001B6CF8 — [callee-sig-conflict] src/gamesys.c:207: conflicting types for `func_001B6CA0__pn'
- PRE-MATCHED `func_001B6D40` w2 @ 0x001B6D40 — already had a PAL body
- REVERTED `func_001B6DA8` w2 @ 0x001B6DA8 — [callee-sig-conflict] src/gamesys.c:207: conflicting types for `func_001B6CA0__pn'
- PRE-MATCHED `func_001B6DF0` w2 @ 0x001B6DF0 — already had a PAL body
- REVERTED `gamesysBackStageProcess` w3 @ 0x001B6C70 — [codegen] insn 1: expected `addiu	a0,zero,148` built `addiu	a0,zero,130`
- PRE-MATCHED `gamesysGetGirlStageIDAndPosition` w3 @ 0x001B73C8 — already had a PAL body
- PRE-MATCHED `gamesysGirlStageGet` w1 @ 0x001B73A0 — already had a PAL body
- PRE-MATCHED `gamesysMemoryHandlerRead` w1 @ 0x001B7438 — already had a PAL body
- REVERTED `gamesysMemoryLoad` w3 @ 0x001B74E0 — [codegen] insn 18: expected `addiu	a0,zero,394` built `addiu	a0,zero,360`
- PORTED `gamesysMemorySave` w1 @ 0x001B7488 <- aug6 common/src/icoMisc:func_001ABE88 (1 syms rebound)
- PRE-MATCHED `gamesysNObjInfoInit` w1 @ 0x001B6F08 — already had a PAL body
- REVERTED `gamesysObjInfoInit` w3 @ 0x001B66A8 — [codegen] insn 17: expected `addiu	a2,zero,424` built `addiu	a2,zero,416`
- REVERTED `gamesysObjInfoLoad` w3 @ 0x001B6798 — [callee-sig-conflict] src/gamesys.c:190: conflicting types for `gamesysMemoryHandlerRead__pn'
- PRE-MATCHED `gamesysObjInfoPosSetStage` w1 @ 0x001B6FB8 — already had a PAL body
- PRE-MATCHED `gamesysObjInfoStageInitFlagCls` w1 @ 0x001B6F48 — already had a PAL body
- PRE-MATCHED `gamesysObjInfoStageInitPosSaveUnlock` w1 @ 0x001B6F80 — already had a PAL body
- PORTED `gamesysObjInfoUniqDataSet` w1 @ 0x001B6FF8 <- aug6 common/src/haveParentSimpleObj:func_001AB9F8 (4 syms rebound)
- PRE-MATCHED `gamesysStageExitTimeSet` w1 @ 0x001B7418 — already had a PAL body
- PORTED `gamesysVersionLoad` w1 @ 0x001B7540 <- aug6 common/src/icoMisc:func_001ABF40 (5 syms rebound)
- PORTED `gamesysVersionSave` w1 @ 0x001B7588 <- aug6 common/src/icoMisc:func_001ABF88 (5 syms rebound)

### src/gather_effect
- PORTED `GatherEffect_InqEnd` w1 @ 0x001A0560 <- aug6 ito/src/gather_effect:GatherEffect_Set (2 syms rebound)
- REVERTED `GatherEffect_SetGoal` w3 @ 0x001A0160 — [codegen] insn 10: expected `addiu	a0,v0,80` built `addiu	a0,v0,64`

### src/generator
- PRE-MATCHED `GetbufpGeneratorPacket` w1 @ 0x0019BEB0 — already had a PAL body
- REVERTED `GetsizeGeneratorPacket` w3 @ 0x0019BEC0 — [codegen] insn 1: expected `addiu	v0,zero,11277` built `addiu	v0,zero,10251`
- PRE-MATCHED `IsEnableCallEnemyByTargetGObj` w1 @ 0x0019C4E8 — already had a PAL body
- PRE-MATCHED `LockEnemyGenerate` w1 @ 0x0019C1D0 — already had a PAL body
- REVERTED `MemoryGenerator` w3 @ 0x0019BF40 — [codegen] insn 2: expected `lw	a2,2096(a3)` built `lw	a2,2032(a3)`
- REVERTED `RestoreGeneratorExtGeo` w3 @ 0x0019BEE8 — [codegen] insn 6: expected `lw	a2,2096(v0)` built `lw	a2,2032(v0)`
- PRE-MATCHED `RestoreGeneratorGeo` w1 @ 0x0019BEC8 — already had a PAL body
- PRE-MATCHED `ReturnEnemyToGenerator` w1 @ 0x0019C330 — already had a PAL body
- PRE-MATCHED `SetInfoSpKidnapGenerator` w1 @ 0x0019C450 — already had a PAL body
- PRE-MATCHED `UnlockEnemyGenerate` w1 @ 0x0019C218 — already had a PAL body

### src/geometryManager
- PRE-MATCHED `GetCharGObjList` w2 @ 0x00104A80 — already had a PAL body
- PRE-MATCHED `GetGlobalDirectionOrient` w1 @ 0x00102FE8 — already had a PAL body
- PRE-MATCHED `GetProjectionOfPlane` w1 @ 0x00104988 — already had a PAL body
- PRE-MATCHED `GetProjectionOfPlaneWithKeepAway` w1 @ 0x00104A08 — already had a PAL body
- PRE-MATCHED `GetProjectionPosOfPlane` w1 @ 0x00104910 — already had a PAL body
- PRE-MATCHED `GetRootMatrix` w3 @ 0x00104188 — already had a PAL body
- PRE-MATCHED `GetRootMatrixByDObj` w3 @ 0x00104108 — already had a PAL body
- PRE-MATCHED `GetRootMatrixRotOffset` w2 @ 0x00102A00 — already had a PAL body
- PRE-MATCHED `GetRootMatrixRotOffsetByDObj` w1 @ 0x001029C0 — already had a PAL body
- PRE-MATCHED `GetRootMatrixTransOffset` w1 @ 0x00104738 — already had a PAL body
- PRE-MATCHED `GetRootMatrixTransOffsetByDObj` w1 @ 0x001046E0 — already had a PAL body
- PRE-MATCHED `GetRootMotionMatrix` w3 @ 0x00104860 — already had a PAL body
- PRE-MATCHED `GetRootMotionOrient` w3 @ 0x00104790 — already had a PAL body
- PRE-MATCHED `GetRootOrient` w3 @ 0x001045D8 — already had a PAL body
- PRE-MATCHED `GetRootPosition` w3 @ 0x00104550 — already had a PAL body
- PRE-MATCHED `GetRootPositionByDObj` w3 @ 0x00104208 — already had a PAL body
- PRE-MATCHED `GetRootQuaternion` w2 @ 0x00102898 — already had a PAL body
- REVERTED `GetRootQuaternionByDObj` w1 @ 0x001027D8 — [callee-sig-conflict] src/geometryManager.c:22: conflicting types for `GetRootQuaternionByDObj'
- PRE-MATCHED `GetRootVelocity` w3 @ 0x00103158 — already had a PAL body
- PRE-MATCHED `LocalizeDirectionOrient` w3 @ 0x00103B18 — already had a PAL body
- PRE-MATCHED `SetDirectRootPositionWithNodePoint` w2 @ 0x00102E28 — already had a PAL body
- PRE-MATCHED `SetRootBaseQuaternion` w1 @ 0x001028A8 — already had a PAL body
- PRE-MATCHED `SetRootMatrixRotOffset` w2 @ 0x00102A80 — already had a PAL body
- PRE-MATCHED `SetRootMatrixRotOffsetByDObj` w1 @ 0x00102A08 — already had a PAL body
- PRE-MATCHED `SetRootMatrixWithTransOffset` w2 @ 0x001029B8 — already had a PAL body
- PRE-MATCHED `SetRootMatrixWithTransOffsetByDObj` w1 @ 0x00102938 — already had a PAL body
- PORTED `SetRootQuaternion` w1 @ 0x001028B8 <- aug6 sugipon/src/delayFreeManager:func_00102840 (3 syms rebound)
- PRE-MATCHED `UpdateRootMatrix` w2 @ 0x001028A0 — already had a PAL body
- REVERTED `UpdateRootMatrixByDObj` w3 @ 0x00102810 — [codegen] insn 22: expected `lwc1	$f1,192(s2)` built `lwc1	$f1,176(s2)`

### src/gflag
- PRE-MATCHED `gflagChk` w1 @ 0x00181A48 — already had a PAL body
- PRE-MATCHED `gflagOff` w1 @ 0x00181AA0 — already had a PAL body
- PRE-MATCHED `gflagOn` w1 @ 0x00181A70 — already had a PAL body

### src/girl
- PRE-MATCHED `GirlDL` w1 @ 0x001DDC48 — already had a PAL body

### src/girlForceField
- PRE-MATCHED `GirlForceFieldGeo` w1 @ 0x001DDF18 — already had a PAL body

### src/girl_act
- PRE-MATCHED `HandMgr_Judge` w1 @ 0x00179300 — already had a PAL body
- REVERTED `SetTurnSpeedInEscape` w3 @ 0x0016FC30 — [codegen] insn 3: expected `lw	a0,52(v1)` built `lw	a0,48(v1)`
- REVERTED `actGirlJump` w3 @ 0x0017C8A0 — [codegen] insn 12: expected `sw	v0,52(s0)` built `sw	v0,48(s0)`
- PRE-MATCHED `afterGirlPulledGo` w3 @ 0x0017C880 — already had a PAL body
- PRE-MATCHED `afterGirlSupportBGBegin` w2 @ 0x0017C8E8 — already had a PAL body
- PRE-MATCHED `enemy_list_compare` w1 @ 0x0017C6B0 — already had a PAL body
- PORTED `funcGirlHandDisconnect` w2 @ 0x0016F688 <- aug6 fumi/src/girl_act:GirlBrainClearTarget (4 syms rebound)
- PRE-MATCHED `func_0016FC20` w2 @ 0x0016FC20 — already had a PAL body
- REVERTED `girlBrainHide_GoalTurn` w3 @ 0x001746F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `girlBrainMain_PositionUpdate` w1 @ 0x00171030 — already had a PAL body
- PORTED `isEnterHideadv` w1 @ 0x00177898 <- aug6 fumi/src/girl_act:actGirlSupportGBLoop (8 syms rebound)

### src/gv
- PRE-MATCHED `AlignDegGV` w1 @ 0x0019CEF8 — already had a PAL body
- PORTED `GetCorrectDistance` w1 @ 0x0019CE30 <- aug6 omori/src/hand-camera:func_001920F0 (3 syms rebound)
- PRE-MATCHED `RoundDegGV` w1 @ 0x0019CEA0 — already had a PAL body
- PRE-MATCHED `SwapGV` w1 @ 0x0019CDE8 — already had a PAL body
- PRE-MATCHED `_AbsRotyGV` w1 @ 0x0019CAD0 — already had a PAL body
- PORTED `_ApplyRyGV` w1 @ 0x0019CAF8 <- aug6 omori/src/hand-camera:func_00191DB8 (4 syms rebound)
- PRE-MATCHED `_DistGV` w1 @ 0x0019C908 — already had a PAL body
- PRE-MATCHED `_DistSqGV` w1 @ 0x0019C8D8 — already had a PAL body
- PRE-MATCHED `_DistxzGV` w1 @ 0x0019C940 — already had a PAL body
- PRE-MATCHED `_DistxzSqGV` w1 @ 0x0019C8A0 — already had a PAL body
- PORTED `_FrontGV` w1 @ 0x0019CD80 <- aug6 omori/src/hand-camera:func_00192040 (4 syms rebound)
- PORTED `_GetDirection` w1 @ 0x0019CB70 <- aug6 omori/src/hand-camera:func_00191E30 (3 syms rebound)
- REVERTED `_InterGV` w1 @ 0x0019C560 — [callee-sig-conflict] src/gv.c:42: conflicting types for `_InterGV'
- PRE-MATCHED `_MoveGV` w1 @ 0x0019C980 — already had a PAL body
- PRE-MATCHED `_OrientGV` w1 @ 0x0019CD48 — already had a PAL body
- PRE-MATCHED `_OrientXZGV` w1 @ 0x0019CD10 — already had a PAL body
- PORTED `_RotGV` w1 @ 0x0019CBB8 <- aug6 omori/src/hand-camera:func_00191E78 (4 syms rebound)
- REVERTED `_RotGVF` w1 @ 0x0019CC58 — [callee-sig-conflict] src/gv.c:13: conflicting types for `sceVu0Normalize__pn'

### src/hand-camera
- PRE-MATCHED `ClearHandCameraCorrect` w1 @ 0x0019D528 — already had a PAL body
- PRE-MATCHED `InitHandCameraCorrect` w1 @ 0x0019D590 — already had a PAL body
- PORTED `SetLimitHandCameraCorrect` w1 @ 0x0019D610 <- aug6 omori/src/mail-add-data:func_001926A8 (2 syms rebound)

### src/haveParentSimpleObj
- PRE-MATCHED `InitParentSimpleObjGeo` w2 @ 0x001B75F8 — already had a PAL body
- PRE-MATCHED `ParentSimpleObjDL` w2 @ 0x001B75F0 — already had a PAL body
- PRE-MATCHED `ParentSimpleObjGeo` w2 @ 0x001B75E8 — already had a PAL body

### src/icoMisc
- PRE-MATCHED `ExitIcoMisc` w2 @ 0x001B8730 — already had a PAL body
- PORTED `disp_memory_partition` w1 @ 0x001B7BE8 <- aug6 common/src/icoMisc:func_001AC5E8 (8 syms rebound)

### src/item
- PRE-MATCHED `avoidInsideOfWall` w1 @ 0x001DE900 — already had a PAL body
- REVERTED `bombSparkStartSE` w1 @ 0x001DE7E8 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)

### src/itou_boss
- PRE-MATCHED `CapsuleGhostBossStart` w1 @ 0x001A10F0 — already had a PAL body
- REVERTED `InqCapsuleGhostBossEnd` w3 @ 0x001A1100 — [codegen] insn 1: expected `addiu	a0,zero,65` built `addiu	a0,zero,63`
- PRE-MATCHED `itou_boss_gflag_init` w1 @ 0x001A0DB0 — already had a PAL body

### src/itou_gflag
- PRE-MATCHED `itouGflagLoad` w1 @ 0x001A11F0 — already had a PAL body
- PRE-MATCHED `itouGflagSave` w2 @ 0x001A11F8 — already had a PAL body

### src/itou_sub
- PRE-MATCHED `apply_matrix_w1` w1 @ 0x001A1470 — already had a PAL body
- PRE-MATCHED `ico_m33_to_quat` w1 @ 0x001A14A0 — already had a PAL body
- PRE-MATCHED `lw_pos_to_ico_pos` w1 @ 0x001A1440 — already had a PAL body
- REVERTED `m33_to_quat` w1 @ 0x001A1200 — [callee-sig-conflict] src/itou_sub.c:57: conflicting types for `m33_to_quat'
- PRE-MATCHED `pbga_start` w1 @ 0x001A14D8 — already had a PAL body

### src/jimaku
- PRE-MATCHED `iosCdvdBackGroundReadJimaku` w1 @ 0x0017CB20 — already had a PAL body
- PRE-MATCHED `jimakuBegin` w1 @ 0x0017D2D8 — already had a PAL body
- REVERTED `jimakuDisp` w3 @ 0x0017D3B8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `jimakuEnd` w2 @ 0x0017D3A8 — already had a PAL body
- PORTED `jimakuJump` w1 @ 0x0017D328 <- aug6 fumi/src/way_sys:_FUNC_GetWay_begin (5 syms rebound)
- PRE-MATCHED `jimakuMgrEnd` w1 @ 0x0017D290 — already had a PAL body
- PORTED `jimakuMgrJump` w1 @ 0x0017D1C0 <- aug6 fumi/src/jimaku:func_00174580 (4 syms rebound)
- REVERTED `jimakuMgrNext` w3 @ 0x0017CFF8 — [undeclared] src/jimaku.c:74: `D_006C1E80' undeclared (first use in this function)
- PRE-MATCHED `jimakuNext` w1 @ 0x0017D2F8 — already had a PAL body

### src/kanban
- PORTED `kanbanExec` w1 @ 0x001B91A0 <- aug6 common/src/kanban:func_001ADB38 (10 syms rebound)
- PRE-MATCHED `kanbanReqAllDel` w1 @ 0x001B9130 — already had a PAL body
- PRE-MATCHED `kanbanReqAllDelFade` w1 @ 0x001B9168 — already had a PAL body
- PRE-MATCHED `kanbanReqDel` w1 @ 0x001B90D8 — already had a PAL body
- PRE-MATCHED `kanbanReqDelFade` w1 @ 0x001B9110 — already had a PAL body

### src/kanbanBoot
- PRE-MATCHED `kanbanBootInit` w1 @ 0x001B9A78 — already had a PAL body
- PORTED `kanbanBootStart` w2 @ 0x001B9A98 <- aug6 common/src/kanban:func_001ADFE8 (2 syms rebound)

### src/layout_action
- REVERTED `CUR_SE` w3 @ 0x001B9AD8 — [codegen] insn 1: expected `addiu	a0,zero,411` built `addiu	a0,zero,399`
- REVERTED `NEGATIVE_SE` w3 @ 0x001B9AC0 — [codegen] insn 1: expected `addiu	a0,zero,413` built `addiu	a0,zero,401`
- REVERTED `POSITIVE_SE` w3 @ 0x001B9AA8 — [codegen] insn 1: expected `addiu	a0,zero,412` built `addiu	a0,zero,400`
- PRE-MATCHED `PSH_POSITIVE_OR_NEGATIVE` w1 @ 0x001BEC40 — already had a PAL body
- PRE-MATCHED `keyconfig_reset` w1 @ 0x001BEC80 — already had a PAL body
- PORTED `la_TESTFUNCTION` w2 @ 0x001B9AF0 <- aug6 common/src/kanbanBoot:kanbanBootInit (3 syms rebound)
- PRE-MATCHED `la_boot_confirm_memory_card` w1 @ 0x001BE238 — already had a PAL body
- PRE-MATCHED `la_boot_no_free_area` w2 @ 0x001BE208 — already had a PAL body
- PRE-MATCHED `la_boot_no_memory_card` w2 @ 0x001BE1D8 — already had a PAL body
- REVERTED `la_delete_confirm` w3 @ 0x001BE930 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `la_delete_confirm_complete` w3 @ 0x001BE988 — [codegen] insn 10: expected `addiu	v0,zero,30` built `addiu	v0,zero,26`
- PRE-MATCHED `la_delete_confirm_fail` w2 @ 0x001BE9C8 — already had a PAL body
- PRE-MATCHED `la_format_confirm_fail` w2 @ 0x001BE878 — already had a PAL body
- PRE-MATCHED `la_game_loading` w1 @ 0x001BE9D0 — already had a PAL body
- PRE-MATCHED `la_general_mc_confirm` w1 @ 0x001BE478 — already had a PAL body
- PRE-MATCHED `la_mc_preview_info` w1 @ 0x001BE2E0 — already had a PAL body
- PRE-MATCHED `la_save_confirm_fail` w2 @ 0x001BE870 — already had a PAL body
- PRE-MATCHED `la_save_confirm_yesno` w1 @ 0x001BEC08 — already had a PAL body
- REVERTED `la_scei_logo` w3 @ 0x001BE270 — [codegen] insn 16: expected `addiu	a0,zero,386` built `addiu	a0,zero,352`
- PRE-MATCHED `la_switching_stage` w1 @ 0x001BEBC8 — already had a PAL body
- PRE-MATCHED `la_title_demo` w2 @ 0x001BE2D8 — already had a PAL body

### src/layout_texture
- PRE-MATCHED `lt_current_property_item` w2 @ 0x001C0D28 — already had a PAL body
- PRE-MATCHED `lt_fade_status` w2 @ 0x001C0F90 — already had a PAL body
- REVERTED `lt_mask_property` w3 @ 0x001C0F20 — [codegen] insn 0: expected `addiu	v0,zero,112` built `addiu	v0,zero,108`
- PRE-MATCHED `lt_set_fade_mode` w2 @ 0x001C0FA0 — already had a PAL body
- PRE-MATCHED `lt_set_item_select_func` w2 @ 0x001C0F98 — already had a PAL body

### src/lightning
- PRE-MATCHED `DrawLightning` w1 @ 0x001A2580 — already had a PAL body
- PRE-MATCHED `apply_m34` w1 @ 0x001A2558 — already had a PAL body
- PRE-MATCHED `cmpr` w1 @ 0x001A2760 — already had a PAL body
- REVERTED `lightning_test` w1 @ 0x001A2688 — [codegen] src/lightning.c:46: invalid initializer

### src/lineManager
- REVERTED `Draw2DLine` w1 @ 0x001E0840 — [codegen] insn 71: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `Draw2DLineSeg_Loop` w1 @ 0x001E0970 <- aug6 sugipon/src/lodManager:func_001D16F0 (2 syms rebound)
- PRE-MATCHED `Draw2DLineSeg_Start` w1 @ 0x001E0960 — already had a PAL body
- PRE-MATCHED `DrawLine` w1 @ 0x001E0FD8 — already had a PAL body
- PORTED `DrawLineG` w1 @ 0x001E1070 <- aug6 sugipon/src/lodManager:func_001D1DF0 (5 syms rebound)

### src/main
- REVERTED `main` w1 @ 0x00102548 — [unresolved-symbol] unresolved-symbol: insn 18 `D_0062BF08`: pal symbol D_0063C108 (0x0063C108) undefined
- PRE-MATCHED `movie_abort_check` w1 @ 0x00102500 — already had a PAL body

### src/matrixDrive
- PRE-MATCHED `AddVectorXYZ` w1 @ 0x00105FC0 — already had a PAL body
- PRE-MATCHED `CopyIVector` w2 @ 0x00105F58 — already had a PAL body
- PRE-MATCHED `CopyMatrix` w1 @ 0x00105F68 — already had a PAL body
- PRE-MATCHED `CopyMatrixUncached` w1 @ 0x00105F90 — already had a PAL body
- PRE-MATCHED `CopyVector` w2 @ 0x00105F48 — already had a PAL body
- PRE-MATCHED `FSqrt` w1 @ 0x00106028 — already had a PAL body
- REVERTED `GetPointDistance` w1 @ 0x00106090 — [crutch] crutch: bare register-variable pin `register float ret __asm__("$`
- REVERTED `InitMatrixDrive` w1 @ 0x00104F38 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- PRE-MATCHED `MatrixDrive_GetLastMatrix` w2 @ 0x001052D8 — already had a PAL body
- PRE-MATCHED `MatrixDrive_GetMatrix` w2 @ 0x001052C0 — already had a PAL body
- PRE-MATCHED `MatrixDrive_GetTurnYEAngleXZ` w1 @ 0x00105B10 — already had a PAL body
- PRE-MATCHED `MatrixDrive_PopMatrix` w1 @ 0x001052B0 — already had a PAL body
- PRE-MATCHED `MatrixDrive_PushMatrix` w1 @ 0x00104F68 — already had a PAL body
- PRE-MATCHED `MatrixDrive_PushMatrixWithNoCopy` w1 @ 0x001052A0 — already had a PAL body
- PRE-MATCHED `MatrixDrive_RotMatrixX` w1 @ 0x00104F90 — already had a PAL body
- PRE-MATCHED `MatrixDrive_RotMatrixY` w1 @ 0x00105008 — already had a PAL body
- PRE-MATCHED `MatrixDrive_RotMatrixZ` w1 @ 0x00105080 — already had a PAL body
- PRE-MATCHED `MatrixDrive_ScaleMatrix` w1 @ 0x001050F8 — already had a PAL body
- PRE-MATCHED `MatrixDrive_TransMatrix` w1 @ 0x00105350 — already had a PAL body
- PRE-MATCHED `MatrixDrive_TransMatrixV` w1 @ 0x001052F0 — already had a PAL body
- PRE-MATCHED `SubVectorXYZ` w1 @ 0x00105FD8 — already had a PAL body
- PRE-MATCHED `UnitRotation` w1 @ 0x00105FF0 — already had a PAL body
- PRE-MATCHED `VectorLength` w1 @ 0x00106048 — already had a PAL body
- PRE-MATCHED `VectorLengthSquare` w1 @ 0x00106070 — already had a PAL body

### src/motionFileManager
- PRE-MATCHED `AddMotionMemorySize` w1 @ 0x001E13F0 — already had a PAL body
- PRE-MATCHED `CheckMotionIncludeFacialData` w1 @ 0x001E14B8 — already had a PAL body
- PRE-MATCHED `GetMotionMemorySize` w1 @ 0x001E1418 — already had a PAL body
- PRE-MATCHED `InitMotionMemorySize` w2 @ 0x001E13E0 — already had a PAL body
- REVERTED `ResetDynamicMotionManager` w3 @ 0x001E1430 — [codegen] insn 6: expected `addiu	a0,zero,1146` built `addiu	a0,zero,1087`
- REVERTED `ResetStatic2MotionManager` w3 @ 0x001E1478 — [codegen] insn 5: expected `addiu	a1,zero,1146` built `addiu	a1,zero,1087`

### src/motionManager
- PRE-MATCHED `GetWallVector` w1 @ 0x001ED610 — already had a PAL body
- REVERTED `ResetMotionProgramInterpInfo` w3 @ 0x001ED390 — [codegen] insn 8: expected `lw	v1,2060(a1)` built `lw	v1,1996(a1)`
- REVERTED `SetDirectMotionProgramInterpInfo` w3 @ 0x001ED400 — [codegen] insn 10: expected `lw	v1,2060(a1)` built `lw	v1,1996(a1)`
- PRE-MATCHED `SetHitCollisionDisplay` w2 @ 0x001ED380 — already had a PAL body
- PORTED `SkelTest` w1 @ 0x001ED268 <- aug6 sugipon/src/motionManager:func_001DDB10 (6 syms rebound)
- PORTED `SkelTestGeo` w1 @ 0x001ED2C0 <- aug6 sugipon/src/motionManager:func_001DDB68 (10 syms rebound)
- PORTED `_calcNaturalGeometry` w1 @ 0x001E5140 <- aug6 sugipon/src/motionFileManager:func_001D5C50 (12 syms rebound)
- PRE-MATCHED `checkCliffAndWallStateAtJump` w3 @ 0x001E6518 — already had a PAL body
- PRE-MATCHED `checkCliffAndWallStateOfLastPlane` w3 @ 0x001E6478 — already had a PAL body
- PRE-MATCHED `checkUpperWallState` w1 @ 0x001E54C8 — already had a PAL body
- PRE-MATCHED `checkWallUpperWall` w1 @ 0x001E92A8 — already had a PAL body
- REVERTED `dispLastNode` w3 @ 0x001E66D0 — [arity] src/motionManager.c:146: too many arguments to function `dispSquare2'
- PORTED `dispSkelton` w1 @ 0x001ED210 <- aug6 sugipon/src/motionManager:func_001DDAB8 (9 syms rebound)
- REVERTED `dispSquare2` w1 @ 0x001E14D0 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0xB8 (out-of-line helper or extra code)
- PRE-MATCHED `forceFallDown` w3 @ 0x001E9248 — already had a PAL body
- REVERTED `forceReset` w3 @ 0x001E9278 — [codegen] insn 3: expected `addiu	a1,zero,259` built `addiu	a1,zero,240`
- REVERTED `getGeometryOfMotion` w3 @ 0x001ED6A0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `pursueNaturalGeometry` w1 @ 0x001ED560 — already had a PAL body
- REVERTED `rootUpdateDirectPlay` w3 @ 0x001EAE08 — [codegen] insn 51: expected `addiu	a0,a0,336` built `addiu	a0,a0,320`
- PRE-MATCHED `upperFieldCheck` w1 @ 0x001ED640 — already had a PAL body

### src/motionManager2
- PRE-MATCHED `AdjustMotionHeightToField` w3 @ 0x00106BA8 — already had a PAL body
- PRE-MATCHED `AdjustRootPositionToVerticalSidePlaneOfWall` w1 @ 0x0010ABD0 — already had a PAL body
- PRE-MATCHED `CheckFloorAttribute` w3 @ 0x0010A040 — already had a PAL body
- PRE-MATCHED `CheckPureCliffAttribute` w3 @ 0x0010A0A0 — already had a PAL body
- PRE-MATCHED `CheckPureWallAttribute` w3 @ 0x0010A080 — already had a PAL body
- PRE-MATCHED `CheckWallAttribute` w3 @ 0x0010A060 — already had a PAL body
- REVERTED `ClearMotionBlendlessNode` w3 @ 0x00109E40 — [codegen] insn 4: expected `lw	a2,2080(v1)` built `lw	a2,2016(v1)`
- PRE-MATCHED `ClearMotionGeometryInfo` w3 @ 0x0010A4E8 — already had a PAL body
- PRE-MATCHED `CopyMotion` w1 @ 0x0010A550 — already had a PAL body
- PRE-MATCHED `DisableChangeRootUpdateMode` w3 @ 0x0010A2D8 — already had a PAL body
- PRE-MATCHED `DisableMotionOrientUpdate` w3 @ 0x0010A030 — already had a PAL body
- REVERTED `DispSkelton` w1 @ 0x001075B8 — [unresolved-symbol] unresolved-symbol: insn 6 `D_0062BF0C`: pal symbol D_0063C10C (0x0063C10C) undefined
- PRE-MATCHED `EnableChangeRootUpdateMode` w3 @ 0x0010A2E8 — already had a PAL body
- PRE-MATCHED `EnableMotionOrientUpdate` w3 @ 0x0010A020 — already had a PAL body
- PRE-MATCHED `ForMotionViewer_GetCurrentAnimationFrame` w3 @ 0x0010A000 — already had a PAL body
- PRE-MATCHED `ForMotionViewer_GetCurrentMotion` w3 @ 0x0010A010 — already had a PAL body
- PRE-MATCHED `GetBlendedMotionRootPos` w1 @ 0x0010ACC0 — already had a PAL body
- PRE-MATCHED `GetHeightOfCliffFromGObj` w3 @ 0x0010A388 — already had a PAL body
- PRE-MATCHED `GetHeightOfFieldPlaneDifference` w3 @ 0x0010A328 — already had a PAL body
- PRE-MATCHED `GetHeightOfWallFromGObj` w3 @ 0x0010A378 — already had a PAL body
- PRE-MATCHED `GetLowerPlaneCollision` w2 @ 0x00106BE8 — already had a PAL body
- PRE-MATCHED `GetMotionFrameFlag1` w3 @ 0x0010A308 — already had a PAL body
- PRE-MATCHED `GetMotionFrameFlag2` w3 @ 0x0010A318 — already had a PAL body
- PRE-MATCHED `GetMotionRootPos` w1 @ 0x0010A590 — already had a PAL body
- PRE-MATCHED `GetOrientOfCliffOfGObj` w3 @ 0x001068E8 — already had a PAL body
- PRE-MATCHED `GetOrientOfWallOfGObj` w3 @ 0x001068D8 — already had a PAL body
- PRE-MATCHED `GetOutOutsideOfWall` w3 @ 0x0010AB20 — already had a PAL body
- PRE-MATCHED `GetRootPosOfNextFrame` w3 @ 0x00106B60 — already had a PAL body
- PRE-MATCHED `GetRootProjectionPosOfGObj` w3 @ 0x0010A490 — already had a PAL body
- PRE-MATCHED `GetRopeHangablePos` w3 @ 0x0010A2F8 — already had a PAL body
- PRE-MATCHED `GetShapeMotion` w1 @ 0x0010AA98 — already had a PAL body
- PRE-MATCHED `GetStreamShapeMotion` w1 @ 0x0010A0C0 — already had a PAL body
- PRE-MATCHED `InitMotionRotElem` w1 @ 0x0010A398 — already had a PAL body
- PRE-MATCHED `InitMotionStateInfo` w1 @ 0x00109E80 — already had a PAL body
- PRE-MATCHED `LockForceGroundParent` w2 @ 0x0010AB10 — already had a PAL body
- PRE-MATCHED `MakeMirrorMotion` w1 @ 0x001095E0 — already had a PAL body
- PRE-MATCHED `SetMotionDirection` w3 @ 0x001068F8 — already had a PAL body
- PRE-MATCHED `SetMotionPlaySpeedRatio` w3 @ 0x0010A4D8 — already had a PAL body
- PRE-MATCHED `SetRootUpdateMode` w3 @ 0x00109FF0 — already had a PAL body
- PRE-MATCHED `SetSkeltonDispSwitch` w2 @ 0x0010A548 — already had a PAL body
- PRE-MATCHED `UnlockForceGroundParent` w2 @ 0x0010AB18 — already had a PAL body
- PRE-MATCHED `_GetMotionDirection` w3 @ 0x001069B0 — already had a PAL body
- PRE-MATCHED `fitYToPlane` w1 @ 0x0010AC80 — already had a PAL body
- PRE-MATCHED `getLowerPlaneCollisionE` w2 @ 0x00106C30 — already had a PAL body
- PRE-MATCHED `getVerticalElementOfWallNormal` w1 @ 0x00107C18 — already had a PAL body

### src/motionOrientManager
- PRE-MATCHED `ForTest_ForceShiftMotion` w1 @ 0x001EEDA8 — already had a PAL body
- REVERTED `GetMotionPlaySpeedRatio` w3 @ 0x001EDAF8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `GetNbMotionFrames` w3 @ 0x001ED9F0 — [unresolved-symbol] unresolved-symbol: insn 19 `D_006169D8`: pal symbol D_004F3470 (0x004F3470) undefined
- SKIPPED `orientDebug` w3 @ 0x001ED758 — jtbl

### src/motionViewer
- PRE-MATCHED `setMotionSpeed` w2 @ 0x001F1800 — already had a PAL body
- REVERTED `setRootUpdateMode` w1 @ 0x001F17F0 — [codegen] insn 3: expected `<end>` built `sll	zero,zero,0x0`

### src/moveColTest
- PORTED `InitMoveColTestGeo` w1 @ 0x001F3848 <- aug6 sugipon/src/moveColTest:func_001E3BE8 (5 syms rebound)
- PRE-MATCHED `MoveColTestDL` w2 @ 0x001F3840 — already had a PAL body

### src/multiBgaManager
- PRE-MATCHED `DispMultiBgaManager` w1 @ 0x001F3A50 — already had a PAL body
- REVERTED `InitMultiBgaManager` w1 @ 0x001F38B8 — [codegen] src/multiBgaManager.c:32: incompatible types in assignment

### src/objact
- REVERTED `ObjAction_CorrectGeo` w3 @ 0x00257318 — [callee-sig-conflict] src/objact.c:45: conflicting types for `ObjAction_CorrectGeo'
- PORTED `ObjAction_Init` w1 @ 0x002574F8 <- aug6 ito/mpeg/mv_sub:ErrMessage (4 syms rebound)
- PRE-MATCHED `ObjAction_Mail` w1 @ 0x00257398 — already had a PAL body
- REVERTED `ObjAction_MailCenter` w3 @ 0x00257400 — [codegen] insn 49: expected `slti	v0,s1,33` built `slti	v0,s1,31`
- PRE-MATCHED `ObjectBeforeFunc` w2 @ 0x00257310 — already had a PAL body

### src/op
- REVERTED `actSt26aConte01_1_newgame` w3 @ 0x00220F38 — [codegen] insn 13: expected `addiu	a0,zero,382` built `addiu	a0,zero,348`
- PRE-MATCHED `actSubMpegReturnPreload` w1 @ 0x00220EB8 — already had a PAL body

### src/particleEffect
- REVERTED `DeleteParticleEffectsByID` w3 @ 0x001F5558 — [codegen] insn 12: expected `addiu	s2,s0,3584` built `addiu	s2,s0,3072`
- REVERTED `DisableParticleEffectGeometryControl` w3 @ 0x001F5620 — [codegen] insn 0: expected `addiu	v1,zero,28` built `addiu	v1,zero,24`
- REVERTED `GetParticleEffectData` w3 @ 0x001F5600 — [codegen] insn 0: expected `addiu	v0,zero,28` built `addiu	v0,zero,24`
- PRE-MATCHED `GetParticleEffectPackage` w1 @ 0x001F54A8 — already had a PAL body
- REVERTED `GetParticleIDWithName` w3 @ 0x001F5640 — [codegen] insn 17: expected `slti	v0,s0,61` built `slti	v0,s0,53`
- PRE-MATCHED `GetParticleLoopFlag` w1 @ 0x001F56B0 — already had a PAL body
- REVERTED `SetParticleEffectGeometry` w3 @ 0x001F4E48 — [codegen] insn 1: expected `addiu	v0,zero,28` built `addiu	v0,zero,24`
- PRE-MATCHED `SetParticleEffectPackage` w1 @ 0x001F51A0 — already had a PAL body
- REVERTED `SetParticleEffectUpperLimit` w3 @ 0x001F4E88 — [codegen] insn 2: expected `addiu	a0,zero,28` built `addiu	a0,zero,24`
- REVERTED `setParticleEffectGeometry` w1 @ 0x001F3C48 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x38 (out-of-line helper or extra code)

### src/particleLayout
- REVERTED `InitParticleLayoutGeo` w1 @ 0x001F57E0 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- PRE-MATCHED `ParticleLayoutDL` w2 @ 0x001F5850 — already had a PAL body

### src/poly-flat
- PRE-MATCHED `DrawPolygon` w1 @ 0x0019E138 — already had a PAL body
- PRE-MATCHED `IsPointIsInScreen` w1 @ 0x0019E2C8 — already had a PAL body
- REVERTED `_IsInScreen2` w1 @ 0x0019DFF0 — [callee-sig-conflict] src/poly-flat.c:86: conflicting types for `_IsInScreen2'
- PRE-MATCHED `after_DrawLine` w2 @ 0x0019E130 — already had a PAL body
- PRE-MATCHED `after_DrawPolygon` w2 @ 0x0019DFE8 — already had a PAL body
- PRE-MATCHED `before_DrawLine` w1 @ 0x0019E108 — already had a PAL body
- REVERTED `before_DrawPolygon` w1 @ 0x0019DFC0 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x28 (out-of-line helper or extra code)

### src/pool
- REVERTED `CheckPoolHasGridMesh` w3 @ 0x0010D148 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`
- REVERTED `GetPoolGlobalDrainVector` w3 @ 0x0010B2B8 — [codegen] insn 1: expected `lw	a1,2096(v0)` built `lw	a1,2032(v0)`
- PRE-MATCHED `PoolGeo` w2 @ 0x0010D038 — already had a PAL body
- REVERTED `falldownSE` w3 @ 0x0010ADC0 — [codegen] insn 1: expected `addiu	a1,zero,86` built `addiu	a1,zero,81`
- PRE-MATCHED `flushWork` w1 @ 0x0010AF40 — already had a PAL body
- REVERTED `poolRideFunc` w3 @ 0x0010D300 — [codegen] insn 5: expected `lw	v1,2096(a0)` built `lw	v1,2032(a0)`
- PRE-MATCHED `setNodePursueParticleEffectWithUpperLimit` w1 @ 0x0010B038 — already had a PAL body

### src/quaternion
- REVERTED `CopyQuaternion` w2 @ 0x0010D7F8 — [callee-sig-conflict] src/quaternion.c:319: conflicting types for `CopyVector__pn'
- PRE-MATCHED `DivQuaternion` w1 @ 0x0010DDC0 — already had a PAL body
- PRE-MATCHED `GetInverseQuaternion` w1 @ 0x0010D800 — already had a PAL body
- PRE-MATCHED `GetLastQuaternion` w1 @ 0x0010DA80 — already had a PAL body
- PRE-MATCHED `GetMatrixFromQuaternion` w1 @ 0x0010D508 — already had a PAL body
- PRE-MATCHED `GetMatrixFromQuaternionPos` w1 @ 0x0010DE88 — already had a PAL body
- PRE-MATCHED `GetMatrixFromQuaternionRotElem` w1 @ 0x0010DE08 — already had a PAL body
- SKIPPED `GetMirrorQuaternion` w1 @ 0x0010DF80 — jtbl
- PRE-MATCHED `GetQuaternionCosRadian` w1 @ 0x0010E8F0 — already had a PAL body
- PRE-MATCHED `GetQuaternionFromMatrix` w1 @ 0x0010D7C0 — already had a PAL body
- REVERTED `GetQuaternionMagnitude` w1 @ 0x0010E6D0 — [crutch] crutch: bare register-variable pin `register float arg __asm__("$`
- PRE-MATCHED `GetSlerpQuaternion` w2 @ 0x0010DA40 — already had a PAL body
- PRE-MATCHED `InitQuaternionDrive` w2 @ 0x0010D4E8 — already had a PAL body
- PRE-MATCHED `InvertCurrentQuaternion` w1 @ 0x0010D3D0 — already had a PAL body
- REVERTED `MultiCurrentQuaternion` w1 @ 0x0010D3A8 — [codegen] insn 7: expected `j	0 <MultiCurrentQuaternion>` built `j	9d8 <MultiQuaternion>`
- PRE-MATCHED `MultiMatrixByQuaternion` w1 @ 0x0010DF38 — already had a PAL body
- PRE-MATCHED `MultiQuaternion` w1 @ 0x0010DD80 — already had a PAL body
- PRE-MATCHED `PopQuaternion` w1 @ 0x0010DAF0 — already had a PAL body
- PRE-MATCHED `PushQuaternion` w1 @ 0x0010D470 — already had a PAL body
- PRE-MATCHED `PushQuaternionWithNoCopy` w1 @ 0x0010DA98 — already had a PAL body
- PRE-MATCHED `RegularizeQuaternion` w1 @ 0x0010D840 — already had a PAL body
- PRE-MATCHED `RotCurrentQuaternionY` w1 @ 0x0010D430 — already had a PAL body
- PRE-MATCHED `RotCurrentQuaternionZ` w1 @ 0x0010D450 — already had a PAL body
- PRE-MATCHED `SetCurrentQuaternion` w1 @ 0x0010D3F0 — already had a PAL body
- PORTED `SetIdentityQuaternion` w2 @ 0x0010D4F8 <- aug6 sugipon/src/quaternion:GetMatrixFromQuaternion (3 syms rebound)
- PRE-MATCHED `SetQuaternionByAxisRotateEAngle` w1 @ 0x0010DC00 — already had a PAL body
- PRE-MATCHED `SetQuaternionByAxisRotateV` w1 @ 0x0010DCC0 — already had a PAL body
- PRE-MATCHED `SetQuaternionByAxisRotateVEAngle` w1 @ 0x0010E830 — already had a PAL body
- PRE-MATCHED `SetQuaternionByAxisRotateVWithNoRegularize` w1 @ 0x0010DD20 — already had a PAL body
- PRE-MATCHED `SetQuaternionByAxisRotateWithNoRegularize` w1 @ 0x0010DB98 — already had a PAL body
- PRE-MATCHED `SetQuaternionByCosineAxisRotateV` w1 @ 0x0010E7A0 — already had a PAL body
- PRE-MATCHED `SetQuaternionByCosineAxisRotateVWithNoRegularize` w1 @ 0x0010E710 — already had a PAL body

### src/queen
- REVERTED `scale_m34` w1 @ 0x001A2770 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x60 (out-of-line helper or extra code)

### src/queen_barrier_disp
- PRE-MATCHED `queen_barrier_anim` w1 @ 0x001A55E0 — already had a PAL body
- REVERTED `queen_barrier_set_damage` w1 @ 0x001A4E48 — [codegen] insn 5: expected `<end>` built `sll	zero,zero,0x0`

### src/rope
- PRE-MATCHED `ReleaseRope` w2 @ 0x001F6FB8 — already had a PAL body

### src/ropeFix
- PRE-MATCHED `InitRopeFixGeo` w2 @ 0x001F70C0 — already had a PAL body
- PORTED `RopeFixDL` w2 @ 0x001F7078 <- aug6 sugipon/src/ropeFix:func_001E6B28 (3 syms rebound)
- PRE-MATCHED `RopeFixGeo` w1 @ 0x001F7038 — already had a PAL body

### src/rotObject
- PRE-MATCHED `ExecRotObjectMoveEndReaction` w2 @ 0x001F75B0 — already had a PAL body
- PRE-MATCHED `ExecRotObjectMoveStartReaction` w2 @ 0x001F75A8 — already had a PAL body
- PRE-MATCHED `GetRotObjectHoldPoint` w1 @ 0x001F7130 — already had a PAL body
- PRE-MATCHED `RestoreRotObjectGeo` w2 @ 0x001F7A40 — already had a PAL body
- REVERTED `SetRotObjectLockFlag` w3 @ 0x001F7A88 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`

### src/sceneManager
- PRE-MATCHED `ChangeStageStartInfo` w1 @ 0x001C1D68 — already had a PAL body
- PRE-MATCHED `GetStageStartInfo` w1 @ 0x001C1EC0 — already had a PAL body
- PRE-MATCHED `HotInitSceneObjects` w3 @ 0x001C1CC0 — already had a PAL body
- PRE-MATCHED `MoveNextStage_Clear` w1 @ 0x001C1F48 — already had a PAL body
- PORTED `MoveNextStage_Set` w1 @ 0x001C1E50 <- aug6 common/src/sceneManager:func_001B55D8 (8 syms rebound)
- PRE-MATCHED `initWayData` w2 @ 0x001C1A70 — already had a PAL body
- PRE-MATCHED `test_nextstage_firstwalk_set` w1 @ 0x001C1EB0 — already had a PAL body

### src/script
- PRE-MATCHED `InitStageChange` w2 @ 0x00185170 — already had a PAL body
- PRE-MATCHED `RequestStageChange` w1 @ 0x00185178 — already had a PAL body
- PRE-MATCHED `RequestStageChangeDirect` w1 @ 0x00185338 — already had a PAL body
- PRE-MATCHED `RequestStageChangeSimple` w1 @ 0x001852E8 — already had a PAL body
- PRE-MATCHED `ScpCallCameraGetTarget` w1 @ 0x00185838 — already had a PAL body
- REVERTED `ScpCallCameraOn` w3 @ 0x00185890 — [codegen] insn 2: expected `lui	v1,0x80` built `addiu	v1,zero,512`
- REVERTED `_SCPCharacterStop` w3 @ 0x00184FA8 — [codegen] insn 2: expected `sw	v1,824(v0)` built `sw	v1,808(v0)`
- PRE-MATCHED `scpActivateAllWithKind` w1 @ 0x00183788 — already had a PAL body
- PORTED `scpBornSpider` w1 @ 0x001854A8 <- aug6 script/src/st25a:func_0017BD40 (8 syms rebound)
- PRE-MATCHED `scpCheckReadyAllObjects` w2 @ 0x001857A0 — already had a PAL body
- PRE-MATCHED `scpDisActivateAllWithKind` w1 @ 0x001837C8 — already had a PAL body
- PRE-MATCHED `scpDispOffAllWithKind` w1 @ 0x00183700 — already had a PAL body
- PRE-MATCHED `scpDispOnAllWithKind` w1 @ 0x00183740 — already had a PAL body
- PRE-MATCHED `scpEffectStart` w1 @ 0x00184AD8 — already had a PAL body
- PORTED `scpExplodeSecretItem` w1 @ 0x00185968 <- aug6 script/src/warpGirl:func_0017C1B0 (6 syms rebound)
- PRE-MATCHED `scpFadeChk` w1 @ 0x001853D0 — already had a PAL body
- PRE-MATCHED `scpFadeIn` w1 @ 0x001853B8 — already had a PAL body
- PRE-MATCHED `scpFadeOut` w1 @ 0x00185398 — already had a PAL body
- REVERTED `scpGameStat_BoyWeaponkind` w3 @ 0x001853F8 — [codegen] insn 4: expected `lw	a0,336(v1)` built `lw	a0,304(v1)`
- PRE-MATCHED `scpGetRotObjectRotCount` w3 @ 0x00184110 — already had a PAL body
- PRE-MATCHED `scpIsBombExplode` w1 @ 0x001840B8 — already had a PAL body
- PRE-MATCHED `scpIsHangChain` w2 @ 0x00185448 — already had a PAL body
- PRE-MATCHED `scpIsHangChainOptional` w1 @ 0x00185468 — already had a PAL body
- PRE-MATCHED `scpIsRotObjectZPlusDirInclude` w3 @ 0x00184150 — already had a PAL body
- PRE-MATCHED `scpIsTorchLightOn` w1 @ 0x00184078 — already had a PAL body
- PRE-MATCHED `scpIsWallLever2On` w2 @ 0x00185428 — already had a PAL body
- PRE-MATCHED `scpKillEnemyOne` w1 @ 0x00184D28 — already had a PAL body
- PRE-MATCHED `scpKillSpiderGroup` w1 @ 0x00183678 — already had a PAL body
- PRE-MATCHED `scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag` w2 @ 0x00183968 — already had a PAL body
- PORTED `scpLinkBGAtoLayoutedTarget` w1 @ 0x00183808 <- aug6 script/src/script:scpTorchLightOn (3 syms rebound)
- PRE-MATCHED `scpLinkBGAtoLayoutedTargetSkelton` w1 @ 0x00183848 — already had a PAL body
- PRE-MATCHED `scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag` w2 @ 0x001838D0 — already had a PAL body
- PRE-MATCHED `scpMaskGeneratorAll` w1 @ 0x00184CE0 — already had a PAL body
- PRE-MATCHED `scpPlayEnd` w3 @ 0x00181D88 — already had a PAL body
- REVERTED `scpPlayJump` w3 @ 0x00181D00 — [codegen] insn 10: expected `addiu	a1,zero,45` built `addiu	a1,zero,44`
- REVERTED `scpPlayMot` w3 @ 0x00181C18 — [codegen] insn 13: expected `addiu	s1,zero,1281` built `addiu	s1,zero,1193`
- PRE-MATCHED `scpPlayMotDir` w1 @ 0x00181B70 — already had a PAL body
- PRE-MATCHED `scpPlayMotNode` w1 @ 0x00184FF0 — already had a PAL body
- REVERTED `scpPlayMotReq` w3 @ 0x00185088 — [codegen] insn 5: expected `addiu	a2,s0,1568` built `addiu	a2,s0,1552`
- PRE-MATCHED `scpPlayPosSet` w1 @ 0x001850B8 — already had a PAL body
- PRE-MATCHED `scpPlayStart` w3 @ 0x00181D48 — already had a PAL body
- REVERTED `scpPlayWaitMotEnd` w3 @ 0x00185130 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `scpSearchGobj` w2 @ 0x00184FD0 — already had a PAL body
- PRE-MATCHED `scpSetCageVelocityFriction` w1 @ 0x00181B30 — already had a PAL body
- PRE-MATCHED `scpSetStreamMotionRootOffset` w3 @ 0x001856B8 — already had a PAL body
- REVERTED `scpSleepEnemyAll` w3 @ 0x00184B20 — [callee-sig-conflict] src/script.c:561: conflicting types for `isysGObjSearchFromObjKindID_begin__pn'
- PRE-MATCHED `scpSleepEnemyOne` w1 @ 0x001835E0 — already had a PAL body
- PRE-MATCHED `scpSleepSpiderGroupOne` w2 @ 0x00183618 — already had a PAL body
- PRE-MATCHED `scpTorchLightOff` w2 @ 0x00181B00 — already had a PAL body
- REVERTED `scpTorchLightOn` w2 @ 0x00181AD0 — [callee-sig-conflict] src/script.c:202: conflicting types for `scpSearchGobj__pn'
- PRE-MATCHED `scpTrans` w1 @ 0x00181DC0 — already had a PAL body
- PORTED `scpTransGObj` w1 @ 0x001858E8 <- aug6 script/src/warpGirl:func_0017C130 (3 syms rebound)
- REVERTED `scpWakeupEnemyAll` w3 @ 0x00184BA8 — [callee-sig-conflict] src/script.c:561: conflicting types for `isysGObjSearchFromObjKindID_begin__pn'
- PRE-MATCHED `scpWakeupEnemyOne` w1 @ 0x001835A8 — already had a PAL body
- PRE-MATCHED `scpWakeupSpiderGroupOne` w2 @ 0x00183648 — already had a PAL body

### src/seMail
- PORTED `seMailTargetDistCheck` w1 @ 0x00214CE0 <- aug6 fumi/src/act2:func_002017A0 (4 syms rebound)
- REVERTED `setMailTarget` w1 @ 0x00214B38 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x30 (out-of-line helper or extra code)

### src/spider
- PRE-MATCHED `RestoreSpiderLayoutGeo` w2 @ 0x001F88D8 — already had a PAL body

### src/spiderGroupManager
- PRE-MATCHED `DispAllSpiderGroups` w1 @ 0x001F9260 — already had a PAL body
- PRE-MATCHED `EntryRevivedSpiderGroupManager` w1 @ 0x001F9238 — already had a PAL body
- PRE-MATCHED `EntryToSpiderGroupManagerForReviveMaster` w1 @ 0x001F9308 — already had a PAL body
- PRE-MATCHED `InitSpiderGroupManager` w1 @ 0x001F9210 — already had a PAL body
- PRE-MATCHED `getReviveEnemyGObj` w1 @ 0x001F9330 — already had a PAL body

### src/st00a
- PRE-MATCHED `actSt00aDoor2DownEffect` w2 @ 0x00222460 — already had a PAL body
- PRE-MATCHED `actSt00aDoor2Event` w2 @ 0x00222370 — already had a PAL body
- PRE-MATCHED `actSt00aDoor2UpEffect` w2 @ 0x00222380 — already had a PAL body

### src/st01b
- PRE-MATCHED `actSt01bFloorEvent` w2 @ 0x002231A8 — already had a PAL body
- PRE-MATCHED `actSt01bSekizoEvent` w1 @ 0x00223198 — already had a PAL body

### src/st02a
- PRE-MATCHED `actSt02WaterFallBoySplashCheck` w1 @ 0x00223930 — already had a PAL body
- REVERTED `actSt02aBox` w3 @ 0x00224028 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt02aBoxEvent2` w3 @ 0x002242D8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `actSt02aDoorDownEffect` w2 @ 0x002247D0 — already had a PAL body
- PRE-MATCHED `actSt02aDoorEvent` w2 @ 0x002246E0 — already had a PAL body
- PRE-MATCHED `actSt02aDoorUpEffect` w2 @ 0x002246F0 — already had a PAL body
- REVERTED `actSt02aEne` w3 @ 0x00224328 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt02aEnemy1` w3 @ 0x002243A0 — [codegen] insn 17: expected `addiu	a0,zero,122` built `addiu	a0,zero,109`
- REVERTED `actSt02aFence` w3 @ 0x002241C0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt02aGondola` w3 @ 0x00224110 — [codegen] insn 12: expected `addiu	a0,zero,119` built `addiu	a0,zero,106`
- REVERTED `actSt02aSecretItem` w3 @ 0x00224668 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt02aSekizo` w3 @ 0x002244E0 — [codegen] insn 10: expected `addiu	a1,zero,123` built `addiu	a1,zero,110`
- PRE-MATCHED `actSt02aSekizoEvent` w2 @ 0x00224B18 — already had a PAL body
- REVERTED `actSt02aTakiWay` w3 @ 0x002245F0 — [codegen] insn 12: expected `addiu	a0,zero,106` built `addiu	a0,zero,95`
- REVERTED `actSt02aWaterFall` w3 @ 0x00224238 — [codegen] insn 12: expected `addiu	a0,zero,106` built `addiu	a0,zero,95`
- REVERTED `actSt02aWay` w3 @ 0x00224548 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/st03t
- PRE-MATCHED `actSt03tGirlCamEvent` w2 @ 0x00225DF0 — already had a PAL body
- REVERTED `actSt03tGirlCamStartChk` w3 @ 0x00225E00 — [codegen] insn 23: expected `addiu	v1,zero,202` built `addiu	v1,zero,198`
- PRE-MATCHED `actSt03tSekizoEvent` w2 @ 0x00225F98 — already had a PAL body

### src/st04a
- REVERTED `actSt04aGateOpen2ReadyChk` w3 @ 0x0022AA18 — [codegen] insn 38: expected `addiu	a0,zero,32` built `addiu	a0,zero,31`
- REVERTED `finishCallBackFunc` w3 @ 0x0022A948 — [codegen] insn 14: expected `addiu	a0,a0,1312` built `addiu	a0,a0,1296`

### src/st04b
- PRE-MATCHED `actSt04bSekizoEvent` w2 @ 0x0022B970 — already had a PAL body

### src/st04c
- PRE-MATCHED `actSt04cDoorDownEvent` w2 @ 0x0022C2A8 — already had a PAL body
- REVERTED `actSt04cEneChk` w3 @ 0x0022C3D0 — [codegen] insn 18: expected `addiu	a0,zero,391` built `addiu	a0,zero,357`
- PRE-MATCHED `actSt04lDoorEvent` w2 @ 0x0022C498 — already had a PAL body

### src/st04d
- REVERTED `actSt04dDoor1` w3 @ 0x0022C4A8 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- PRE-MATCHED `actSt04dDoor1Event` w2 @ 0x0022CC18 — already had a PAL body
- REVERTED `actSt04dDoor1UpChk` w3 @ 0x0022C5B0 — [codegen] insn 27: expected `addiu	a0,s2,0` built `addiu	a0,s2,1920`
- REVERTED `actSt04dDoor2` w3 @ 0x0022C860 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- REVERTED `actSt04dDoor2DownChk` w3 @ 0x0022CAC0 — [codegen] insn 27: expected `addiu	a0,s2,0` built `addiu	a0,s2,2608`
- PORTED `actSt04dDoor2DownEffect` w2 @ 0x0022CED8 <- aug6 script/src/st04e:func_00217458 (5 syms rebound)
- PRE-MATCHED `actSt04dDoor2Event` w2 @ 0x0022CDE8 — already had a PAL body
- PORTED `actSt04dDoor2UpEffect` w2 @ 0x0022CDF8 <- aug6 script/src/st04e:func_00217378 (5 syms rebound)

### src/st04l
- PRE-MATCHED `actSt04lMonyou01Event` w2 @ 0x00233640 — already had a PAL body
- PRE-MATCHED `actSt04lMonyou02Event` w2 @ 0x00233650 — already had a PAL body
- PRE-MATCHED `actSt04lMonyou03Event` w2 @ 0x00233660 — already had a PAL body
- PRE-MATCHED `actSt04lMonyou04Event` w2 @ 0x00233670 — already had a PAL body
- PRE-MATCHED `actSt04lMonyou05Event` w2 @ 0x00233680 — already had a PAL body
- PRE-MATCHED `actSt04lMonyou06Event` w2 @ 0x00233690 — already had a PAL body
- PRE-MATCHED `actSt04lMonyou07Event` w2 @ 0x002336A0 — already had a PAL body

### src/st04r
- PRE-MATCHED `actSt04rBrg1Event` w2 @ 0x00238090 — already had a PAL body
- PRE-MATCHED `actSt04rRope1Event` w2 @ 0x00238070 — already had a PAL body
- PRE-MATCHED `actSt04rRope2Event` w2 @ 0x00238080 — already had a PAL body
- PRE-MATCHED `actSt04rStairEvent` w2 @ 0x00238060 — already had a PAL body

### src/st05d
- PRE-MATCHED `actSt05dDoor2Event` w1 @ 0x0023A1C0 — already had a PAL body

### src/st06a
- PRE-MATCHED `actSt06aDoorDownEffect` w2 @ 0x0023CC30 — already had a PAL body
- PRE-MATCHED `actSt06aDoorEvent` w2 @ 0x0023CB40 — already had a PAL body
- PRE-MATCHED `actSt06aDoorUpEffect` w2 @ 0x0023CB50 — already had a PAL body
- PRE-MATCHED `actSt06aSuimonEvent` w2 @ 0x0023C8F8 — already had a PAL body

### src/st07a
- PRE-MATCHED `actSt07ChanEvent` w2 @ 0x0023FA60 — already had a PAL body
- PRE-MATCHED `actSt07TsuroEvent` w2 @ 0x0023FC10 — already had a PAL body
- PRE-MATCHED `actSt07aCamera2` w2 @ 0x0023FCF8 — already had a PAL body
- REVERTED `actSt07aChanMot` w3 @ 0x0023FB08 — [codegen] insn 1: expected `addiu	a1,zero,474` built `addiu	a1,zero,464`
- PRE-MATCHED `actSt07aChanWay1` w2 @ 0x0023FB60 — already had a PAL body
- PRE-MATCHED `actSt07aChanWay2` w2 @ 0x0023FBB8 — already had a PAL body
- PRE-MATCHED `actSt07aGirlWay` w2 @ 0x0023FCA0 — already had a PAL body
- REVERTED `actSt07aIntroChk` w3 @ 0x0023FD08 — [codegen] insn 16: expected `addiu	a0,zero,55` built `addiu	a0,zero,51`
- PRE-MATCHED `actSt07aSekizoEvent` w2 @ 0x0023FDB8 — already had a PAL body
- REVERTED `actSt07aTsuroConte` w3 @ 0x0023FC20 — [codegen] insn 6: expected `addiu	a0,zero,357` built `addiu	a0,zero,322`

### src/st08b
- PRE-MATCHED `actSt08bDoorDownEffect` w2 @ 0x00241F90 — already had a PAL body
- PRE-MATCHED `actSt08bDoorEvent` w2 @ 0x00241EA0 — already had a PAL body
- PRE-MATCHED `actSt08bDoorUpEffect` w2 @ 0x00241EB0 — already had a PAL body

### src/st09a
- PRE-MATCHED `actSt09aSekizoEvent` w2 @ 0x00242890 — already had a PAL body

### src/st10l
- PRE-MATCHED `actSt10lSekizoEvent` w2 @ 0x002443E0 — already had a PAL body

### src/st10r
- REVERTED `actSt10rExitChk` w3 @ 0x00246260 — [codegen] insn 20: expected `addiu	a0,zero,309` built `addiu	a0,zero,281`
- PRE-MATCHED `actSt10rGirlWay` w2 @ 0x00246208 — already had a PAL body
- PRE-MATCHED `actSt10rSekizoEvent` w2 @ 0x00246458 — already had a PAL body

### src/st13b
- PRE-MATCHED `actSt13bSekizo2Event` w2 @ 0x00249BA0 — already had a PAL body

### src/st13b2
- PRE-MATCHED `actSt13b2Generator` w1 @ 0x00249F88 — already had a PAL body

### src/st13c
- PRE-MATCHED `actE3St13cSekizoEvent` w2 @ 0x0024CFB0 — already had a PAL body
- PRE-MATCHED `actSt13cBmg1Event` w2 @ 0x0024CD40 — already had a PAL body
- REVERTED `actSt13cBukiChk` w3 @ 0x0024D378 — [codegen] insn 3: expected `addiu	s0,zero,231` built `addiu	s0,zero,227`
- PRE-MATCHED `actSt13cBukiEvent` w2 @ 0x0024D368 — already had a PAL body
- REVERTED `actSt13cCageFall` w3 @ 0x0024AA70 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `actSt13cCageFallEvent` w2 @ 0x0024CFA0 — already had a PAL body
- REVERTED `actSt13cConte04` w3 @ 0x0024A428 — [codegen] insn 7: expected `addiu	a0,zero,625` built `addiu	a0,zero,553`
- REVERTED `actSt13cInit` w3 @ 0x00249FB8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PRE-MATCHED `actSt13cSleepEvent` w2 @ 0x0024CD50 — already had a PAL body

### src/st13d
- PRE-MATCHED `actSt13dInit` w2 @ 0x0024D650 — already had a PAL body

### src/st17a
- PRE-MATCHED `actLinkTestChk` w3 @ 0x0024E510 — already had a PAL body
- PRE-MATCHED `actSt17aDoorDownEffect` w2 @ 0x0024E658 — already had a PAL body
- PRE-MATCHED `actSt17aDoorEvent` w2 @ 0x0024E568 — already had a PAL body
- REVERTED `actSt17aDoorUpChk` w3 @ 0x0024D7A8 — [codegen] insn 27: expected `addiu	a0,s2,0` built `addiu	a0,s2,3872`
- PRE-MATCHED `actSt17aDoorUpEffect` w2 @ 0x0024E578 — already had a PAL body
- PRE-MATCHED `actSt17aGirlWay` w1 @ 0x0024E7F8 — already had a PAL body
- PRE-MATCHED `actSt17aHasiEvent` w2 @ 0x0024E738 — already had a PAL body
- PRE-MATCHED `actSt17aSekizoEvent` w2 @ 0x0024E500 — already had a PAL body

### src/st17b
- REVERTED `actSt17bTest` w2 @ 0x0024E928 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x30 (out-of-line helper or extra code)

### src/st18a
- PRE-MATCHED `actSt18aCamera` w2 @ 0x0024FC70 — already had a PAL body

### src/st25a
- PRE-MATCHED `BoySekikaTexScroll` w1 @ 0x001874A0 — already had a PAL body
- PRE-MATCHED `actSt25aGenerator` w2 @ 0x00187770 — already had a PAL body
- PRE-MATCHED `actSt25aQueenDeadEvent` w2 @ 0x00187DE0 — already had a PAL body

### src/st47a
- PRE-MATCHED `actSt47aBarricadeEvent` w2 @ 0x00254BC0 — already had a PAL body
- PRE-MATCHED `actSt47aHane2Girl` w2 @ 0x00254AC0 — already had a PAL body
- PRE-MATCHED `actSt47aSekizo1Event` w2 @ 0x002547C8 — already had a PAL body
- PRE-MATCHED `actSt47aSekizo2Event` w2 @ 0x00254860 — already had a PAL body
- PRE-MATCHED `func_00254948` w2 @ 0x00254948 — already had a PAL body
- PRE-MATCHED `func_00254998` w2 @ 0x00254998 — already had a PAL body

### src/st99a
- REVERTED `actWaveChk` w2 @ 0x002552E8 — [codegen] insn 6: expected `addiu	a0,a0,0` built `addiu	a0,a0,1488`

### src/staffroll
- PRE-MATCHED `staffRollWide` w1 @ 0x001C24B0 — already had a PAL body

### src/stageSEProc
- REVERTED `stageSE02ataki` w3 @ 0x00255E88 — [codegen] 2026-08-05; it manufactured 8 false delay-slot matches).
- REVERTED `stageSE02atakib` w3 @ 0x00255EE0 — [codegen] 2026-08-05; it manufactured 8 false delay-slot matches).
- PRE-MATCHED `stageSE03tnotSuiro` w1 @ 0x00255F78 — already had a PAL body
- PRE-MATCHED `stageSE03tsuiro` w1 @ 0x00255F40 — already had a PAL body
- PRE-MATCHED `stageSE04bstrong` w2 @ 0x00256088 — already had a PAL body
- REVERTED `stageSE04ewind` w1 @ 0x002560E8 — [codegen] 2026-08-05; it manufactured 8 false delay-slot matches).
- PRE-MATCHED `stageSE06abirdIn` w1 @ 0x00256338 — already had a PAL body
- PRE-MATCHED `stageSE06abirdOut` w1 @ 0x00256390 — already had a PAL body
- PRE-MATCHED `stageSE06ataimatsu` w1 @ 0x002563E8 — already had a PAL body
- PRE-MATCHED `stageSE08anoise3` w1 @ 0x00256600 — already had a PAL body
- PRE-MATCHED `stageSE08ataimatsu` w1 @ 0x00256688 — already had a PAL body
- PRE-MATCHED `stageSE08bcrane` w1 @ 0x00256700 — already had a PAL body
- PRE-MATCHED `stageSE09asea` w1 @ 0x00256800 — already had a PAL body
- REVERTED `stageSE10rstrong` w1 @ 0x00256978 — [arity] src/stageSEProc.c:203: too many arguments to function `GetCameraPos__pn'
- PORTED `stageSE10rstrong2` w2 @ 0x00256A10 <- aug6 ito/mpeg/mv_audiodec:func_00239188 (6 syms rebound)
- PRE-MATCHED `stageSE13arain` w1 @ 0x00256A70 — already had a PAL body
- PRE-MATCHED `stageSE13cNoise` w1 @ 0x00256AB0 — already had a PAL body
- PRE-MATCHED `stageSE13dterrace` w1 @ 0x00256AD8 — already had a PAL body
- REVERTED `stageSE17astrong` w1 @ 0x00256BD0 — [arity] src/stageSEProc.c:229: too many arguments to function `GetCameraPos__pn'
- PRE-MATCHED `stageSE17btaki` w2 @ 0x00256E28 — already had a PAL body
- PRE-MATCHED `stageSE19arain` w1 @ 0x00256EC0 — already had a PAL body
- PRE-MATCHED `stageSE19astrong` w1 @ 0x00256E48 — already had a PAL body
- PRE-MATCHED `stageSE20astrong` w1 @ 0x00256EE8 — already had a PAL body
- PRE-MATCHED `stageSE20astrong2` w2 @ 0x00256F68 — already had a PAL body
- PRE-MATCHED `stageSE22astrong` w1 @ 0x00256FC8 — already had a PAL body
- PRE-MATCHED `stageSE24arain` w1 @ 0x00257140 — already had a PAL body
- PRE-MATCHED `stageSE24ariver` w2 @ 0x00257168 — already had a PAL body
- PRE-MATCHED `stageSE24astrong` w2 @ 0x002570E0 — already had a PAL body
- REVERTED `stageSE47anoise` w1 @ 0x00257188 — [arity] src/stageSEProc.c:365: too many arguments to function `GetCameraPos__pn'

### src/stage_orient
- REVERTED `StageOrientInit` w3 @ 0x001A5B98 — [codegen] insn 7: expected `addiu	s7,zero,404` built `addiu	s7,zero,400`

### src/staticBlur
- PRE-MATCHED `GetSunWorldPos` w2 @ 0x001FCA50 — already had a PAL body
- PRE-MATCHED `InitializeStaticBlur` w2 @ 0x001FD570 — already had a PAL body
- PRE-MATCHED `SetAuraEffect` w2 @ 0x001FD5F0 — already had a PAL body
- PRE-MATCHED `SetAuraInspireParam` w2 @ 0x001FD568 — already had a PAL body
- PRE-MATCHED `SetDepthFadeParam` w1 @ 0x001FD540 — already had a PAL body
- PRE-MATCHED `SetMotionBlur` w2 @ 0x001FD528 — already had a PAL body
- PRE-MATCHED `SetStaticBlur` w1 @ 0x001FD530 — already had a PAL body
- PRE-MATCHED `StaticBlur` w2 @ 0x001FD518 — already had a PAL body
- PRE-MATCHED `StaticBlurDL` w2 @ 0x001FD520 — already had a PAL body
- PRE-MATCHED `_initStaticBlur` w1 @ 0x001FD578 — already had a PAL body
- PRE-MATCHED `calcSun` w1 @ 0x001FCC60 — already had a PAL body

### src/stormTest
- PORTED `InitStormTestGeo` w1 @ 0x001FE100 <- aug6 sugipon/src/stormTest:func_001ED718 (5 syms rebound)
- REVERTED `StormTestDL` w3 @ 0x001FE0E8 — [codegen] insn 1: expected `lw	a1,2096(v0)` built `lw	a1,2032(v0)`
- REVERTED `StormTestGeo` w3 @ 0x001FE0D8 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2032(v0)`

### src/streamMotionManager
- PRE-MATCHED `CheckReadyStreamMotion` w1 @ 0x001FF090 — already had a PAL body
- PRE-MATCHED `PlayStreamMotion` w1 @ 0x001FE680 — already had a PAL body
- PRE-MATCHED `StopStreamMotion` w2 @ 0x001FEE88 — already had a PAL body
- PRE-MATCHED `_closeHander` w2 @ 0x001FF1C8 — already had a PAL body
- PRE-MATCHED `_transRingBuf` w1 @ 0x001FEA18 — already had a PAL body

### src/sugiTree
- PORTED `InitSugiLeafGeo` w1 @ 0x001FF628 <- aug6 sugipon/src/sugiTree:func_001EE7E0 (5 syms rebound)

### src/tableSin
- REVERTED `GetTableArcCos` w1 @ 0x0010EB28 — [callee-sig-conflict] src/tableSin.c:90: conflicting types for `GetTableArcCos'
- PORTED `GetTableArcSin` w1 @ 0x0010EA98 <- aug6 seki/src/DisplayP2O:func_0010EE60 (2 syms rebound)
- PORTED `GetTableArcTan2` w1 @ 0x0010EBD0 <- aug6 seki/src/DisplayP2O:func_0010EF98 (2 syms rebound)
- PORTED `GetTableCos` w1 @ 0x0010E968 <- aug6 seki/src/DisplayP2O:func_0010ED30 (2 syms rebound)
- REVERTED `GetTableSin` w1 @ 0x0010E918 — [codegen] insn 19: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `InitTableSin` w1 @ 0x0010E9C0 <- aug6 seki/src/DisplayP2O:func_0010ED88 (9 syms rebound)

### src/torch
- PRE-MATCHED `TorchDL` w2 @ 0x00200228 — already had a PAL body

### src/vobj
- PORTED `SetVObjRT` w1 @ 0x0025B640 <- aug6 common/src/PObj:func_0023E008 (4 syms rebound)

### src/warpGirl
- PRE-MATCHED `warpGirlInit` w2 @ 0x00188278 — already had a PAL body

### src/waySystemManager
- REVERTED `CreateWaySystemManagerGObj` w2 @ 0x00200AD0 — [codegen] insn 4: expected `addiu	t0,t0,0` built `addiu	t0,t0,208`
- REVERTED `RequestGetWayBegin` w2 @ 0x00200B10 — [codegen] insn 7: expected `addiu	a0,a0,0` built `addiu	a0,a0,128`
- PRE-MATCHED `actWaySystemCore` w1 @ 0x00200B50 — already had a PAL body
- REVERTED `func_00200BA0` w3 @ 0x00200BA0 — [codegen] insn 6: expected `j	0 <func_00200BA0>` built `<end>`

### src/way_kidnap
- REVERTED `NearestEnemyFromGirl` w1 @ 0x00215990 — [callee-sig-conflict] src/way_kidnap.c:8: conflicting types for `GetRootPosition'
- PRE-MATCHED `NumOfWpPos` w2 @ 0x00215AB0 — already had a PAL body
- REVERTED `WayLengthOfGObj_GObj` w1 @ 0x00215BC8 — [callee-sig-conflict] src/way_kidnap.c:8: conflicting types for `GetRootPosition'
- PORTED `WayLengthOfGObj_Pos` w1 @ 0x00215B78 <- aug6 fumi/src/seMail:func_00202638 (3 syms rebound)
- PORTED `WayPointWithRangeFromGObj` w1 @ 0x00215C20 <- aug6 fumi/src/seMail:func_002026E0 (3 syms rebound)
- PRE-MATCHED `func_00215C68` w2 @ 0x00215C68 — already had a PAL body

### src/way_llf
- REVERTED `AddWayPoint` w1 @ 0x002161E0 — [parse] src/way_llf.c:3: parse error before `Nd'
- PRE-MATCHED `AddWayPointTop` w1 @ 0x00216248 — already had a PAL body
- PRE-MATCHED `CheckWayGroupActive` w1 @ 0x00216770 — already had a PAL body
- PRE-MATCHED `CloseWayGroup` w1 @ 0x00216138 — already had a PAL body
- PRE-MATCHED `CreateWayPoint` w3 @ 0x00216168 — already had a PAL body
- REVERTED `DeleteWayGroup` w1 @ 0x002160B8 — [callee-sig-conflict] src/way_llf.c:231: conflicting types for `D_004F1EC0__pn'
- REVERTED `DeleteWayPoint` w1 @ 0x002162C8 — [parse] src/way_llf.c:3: parse error before `Nd'
- PRE-MATCHED `InsertWayPointAfter` w1 @ 0x00216290 — already had a PAL body
- PRE-MATCHED `SetWayGroupActive` w1 @ 0x00216750 — already had a PAL body
- PRE-MATCHED `WayBridgeAll_begin` w3 @ 0x002164D8 — already had a PAL body
- PORTED `WayBridgeAll_next` w1 @ 0x00216520 <- aug6 fumi/src/way_kidnap:func_00202D68 (2 syms rebound)
- PRE-MATCHED `WayBridgeVar_begin` w3 @ 0x00216568 — already had a PAL body
- PRE-MATCHED `WayBridgeVar_next` w2 @ 0x002165C0 — already had a PAL body
- PRE-MATCHED `WayBridge_begin` w3 @ 0x00216428 — already had a PAL body
- PRE-MATCHED `WayBridge_next` w2 @ 0x00216480 — already had a PAL body
- PRE-MATCHED `WayGroup_begin` w3 @ 0x002163A8 — already had a PAL body
- PRE-MATCHED `WayGroup_next` w1 @ 0x002163E8 — already had a PAL body
- PRE-MATCHED `WayPointList_begin` w1 @ 0x00216698 — already had a PAL body
- PRE-MATCHED `WayPointList_next` w1 @ 0x002166B8 — already had a PAL body
- PRE-MATCHED `WayPoint_begin` w3 @ 0x00216618 — already had a PAL body
- PRE-MATCHED `WayPoint_next` w1 @ 0x00216658 — already had a PAL body
- PRE-MATCHED `waypoint_bidirectional_list` w1 @ 0x002166F8 — already had a PAL body

### src/way_sys
- PRE-MATCHED `BridgeBox` w2 @ 0x0017F118 — already had a PAL body
- PORTED `DeleteGuideWay` w1 @ 0x0017F120 <- aug6 fumi/src/way_util:visible_waypoint_of_all_except_temp_ThreadVersion (5 syms rebound)
- PRE-MATCHED `GetWay_begin` w1 @ 0x0017F0F8 — already had a PAL body

### src/way_tool
- PRE-MATCHED `point_insert` w1 @ 0x00216D08 — already had a PAL body
- PRE-MATCHED `point_nige` w1 @ 0x00217C38 — already had a PAL body
- REVERTED `quick_load_wpfile` w1 @ 0x00216E28 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PRE-MATCHED `quick_save_wpfile` w1 @ 0x00217CD0 — already had a PAL body

### src/way_util
- PRE-MATCHED `NearestWgFromTarget` w1 @ 0x00181870 — already had a PAL body
- PRE-MATCHED `WayUtilWorkFree` w1 @ 0x0017FD48 — already had a PAL body
- PRE-MATCHED `bridge_waypoint_side_bridge` w1 @ 0x00181778 — already had a PAL body
- PRE-MATCHED `bridge_waypoint_side_me` w1 @ 0x00181688 — already had a PAL body
- PRE-MATCHED `direction_across_bridge` w1 @ 0x00181558 — already had a PAL body
- PRE-MATCHED `ez_circle` w2 @ 0x0017F840 — already had a PAL body
- PRE-MATCHED `ez_line` w2 @ 0x0017F830 — already had a PAL body
- PRE-MATCHED `get_wp_nearest_bridge_side_bridge` w3 @ 0x001814C8 — already had a PAL body
- PRE-MATCHED `get_wp_nearest_bridge_side_me` w3 @ 0x00181438 — already had a PAL body
- PRE-MATCHED `nearest_waypoint` w1 @ 0x00180AB8 — already had a PAL body
- PRE-MATCHED `nearest_waypoint_of_all` w1 @ 0x00181100 — already had a PAL body
- PRE-MATCHED `nearest_waypoint_of_all_except_group` w1 @ 0x00180F78 — already had a PAL body
- PRE-MATCHED `nearest_waypoint_of_group` w1 @ 0x00180A20 — already had a PAL body
- PRE-MATCHED `visible_waypoint_of_all` w1 @ 0x001811A8 — already had a PAL body
- PRE-MATCHED `visible_waypoint_of_all_from_gobj` w1 @ 0x001811C8 — already had a PAL body
- PRE-MATCHED `waybridge_between_group` w1 @ 0x001815E8 — already had a PAL body
- PRE-MATCHED `waypoint_connect_group_side_bridge` w1 @ 0x00181828 — already had a PAL body
- PRE-MATCHED `waypoint_connect_group_side_me` w1 @ 0x00181730 — already had a PAL body
- PRE-MATCHED `waypoint_with_range` w1 @ 0x00180EE8 — already had a PAL body
- PORTED `wpsort_compfnc` w2 @ 0x001818C8 <- aug6 fumi/src/way_util:func_00178C58 (1 syms rebound)

### src/weapon
- PRE-MATCHED `ExecWeaponHitReaction` w2 @ 0x00201BC0 — already had a PAL body
- REVERTED `ReleaseWeaponWithFumbleTargetPos` w3 @ 0x00200C08 — [codegen] insn 12: expected `lw	s0,2096(a0)` built `lw	s0,2032(a0)`
- REVERTED `WeaponCurPos` w3 @ 0x00201B40 — [codegen] insn 9: expected `lw	s0,2096(v0)` built `lw	s0,2032(v0)`
- REVERTED `WeaponHitEffect` w3 @ 0x00201BA0 — [codegen] insn 2: expected `lw	a2,2096(v0)` built `lw	a2,2032(v0)`
- REVERTED `torchOffOfWeaponSE` w3 @ 0x00200BC0 — [codegen] insn 8: expected `addiu	a1,zero,67` built `addiu	a1,zero,65`
- REVERTED `weaponFumbleSE` w3 @ 0x00200BF8 — [codegen] insn 1: expected `addiu	a1,zero,92` built `addiu	a1,zero,87`
- REVERTED `weaponHitReactionSE` w3 @ 0x00200BF0 — [arity] src/weapon.c:22: too many arguments to function `weaponHitReactionSE'
- REVERTED `weaponStickSE` w3 @ 0x00200C00 — [codegen] insn 1: expected `addiu	a1,zero,93` built `addiu	a1,zero,88`

### src/windField
- PRE-MATCHED `GetWindVector` w1 @ 0x00203BF0 — already had a PAL body
- REVERTED `StopWindField` w1 @ 0x00203DE8 — [codegen] insn 1: expected `addiu	v0,v0,0` built `addiu	v0,v0,1824`
- PRE-MATCHED `drawLines` w1 @ 0x00203DF8 — already had a PAL body
- PORTED `drawSenpuuki` w1 @ 0x00203810 <- aug6 sugipon/src/windField:InitWindField (10 syms rebound)
- PRE-MATCHED `drawSenpuukiBase` w2 @ 0x00203F78 — already had a PAL body
- PRE-MATCHED `drawSenpuukiHane` w2 @ 0x00203E78 — already had a PAL body
- PRE-MATCHED `drawSenpuukiUnit` w2 @ 0x00203EF8 — already had a PAL body
- PRE-MATCHED `dummyGetWindVector` w1 @ 0x00203C10 — already had a PAL body

### src/windManager
- REVERTED `ExecWindManager` w1 @ 0x00203FF8 — [codegen] insn 31: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `InitWindManager` w3 @ 0x002041D0 — [undeclared] src/windManager.c:7: `D_0063BC64' undeclared (first use in this function)
- REVERTED `ReinitWindManager` w3 @ 0x00204078 — [undeclared] src/windManager.c:7: `D_0063BC64' undeclared (first use in this function)
- PORTED `SetWindManager` w1 @ 0x00204150 <- aug6 sugipon/src/windManager:func_001F2130 (8 syms rebound)

### src/wireLetter
- PRE-MATCHED `ChangeColorWireString` w1 @ 0x00204790 — already had a PAL body
- PRE-MATCHED `DefaultColorWireString` w1 @ 0x00204760 — already had a PAL body
- PORTED `Draw2DBox` w1 @ 0x002047A8 <- aug6 sugipon/src/wireLetter:func_001F2610 (5 syms rebound)

### src/worm
- PRE-MATCHED `GetWormCaptureVector` w1 @ 0x00205828 — already had a PAL body
- REVERTED `SetWormReduceRatio` w3 @ 0x00205C18 — [callee-sig-conflict] src/worm.c:59: conflicting types for `SetWormReduceRatio'
- REVERTED `TraceWormRoute` w3 @ 0x00205C28 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- PRE-MATCHED `WormDL` w2 @ 0x00205B38 — already had a PAL body
- REVERTED `outerProcess` w1 @ 0x00204888 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x128 (out-of-line helper or extra code)
