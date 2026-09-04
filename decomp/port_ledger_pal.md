
# ntsc -> PAL body port (`tools/port_from_ntsc.py`)

Bodies below were carried over from the `ntsc` (USA retail SCUS-971.13)
checkout's matched clean-room C with every US symbol rebound to its PAL
counterpart by the lockstep reloc-slot walk.  Nothing here was hand-tuned:
each function either reproduced the PAL instruction stream as-is (`PORTED`)
or went straight back to `INCLUDE_ASM` (`REVERTED`, with the first
divergence or compiler diagnostic recorded).  `SKIPPED` = deferred to the
jump-table queue.

Revert-reason classes: `unresolved-symbol` (a reloc slot the walk could not
bind) · `emits-data` (needs a data carve; the TU's US carve entries are
listed under `CARVES`) · `callee-sig-conflict` / `arity` · `undeclared` /
`parse` · `missing-body` · `codegen` (compiles, wrong bytes — a genuine
PAL-vs-USA source difference) · `jtbl`.

## Accounting

| wave | candidates | ported | reverted | skipped | pre-matched | unattempted |
|---|---|---|---|---|---|---|
| 1 | 1294 | 1174 | 120 | 0 | 0 | 0 |
| 2 | 518 | 476 | 40 | 2 | 0 | 0 |
| 3 | 306 | 26 | 280 | 0 | 0 | 0 |
| **all** | 2118 | 1676 | 440 | 2 | 0 | 0 |

Data-carve phase 1 (2026-09-04) re-attempted the 32 `emits-data` reverts
behind the PAL data carves recorded in `decomp/carve_ledger.md` §"PAL phase
1": all 32 landed, so the running totals are **1676 ported / 440 reverted**
(wave 1 1174/120, wave 2 476/40, wave 3 26/280).  The per-function lines in
the sections below are updated in place; see the phase-1 section at the end
of this file for the mechanism.

### ios/cdvd
- REVERTED `inflate_cd_read_func` w3 @ 0x001356C8 — [codegen] insn 3: expected `lw	v0,316(a2)` built `lw	v0,312(a2)`
- PORTED `iosCdvdBackGroundMgrDelete` w1 @ 0x001355A8 <- ntsc ios/cdvd:iosCdvdBackGroundMgrEntryNum (1 syms rebound)
- PORTED `iosCdvdBackGroundMgrDeleteRequestGet` w1 @ 0x001355D8 <- ntsc ios/cdvd:iosCdvdBackGroundRead (2 syms rebound)
- PORTED `iosCdvdBackGroundMgrEntryNum` w1 @ 0x00135620 <- ntsc ios/cdvd:iosCdvdBackGroundReadIOPm (2 syms rebound)
- PORTED `iosCdvdBackGroundMgrGetRunning` w2 @ 0x00135660 <- ntsc ios/cdvd:func_00133508 (2 syms rebound)
- PORTED `iosCdvdBackGroundMgrInit` w1 @ 0x00135728 <- ntsc ios/inflate:inflate (3 syms rebound)
- PORTED `iosCdvdBackGroundMgrNotDiskReadyPauseSet` w1 @ 0x001355B8 <- ntsc ios/cdvd:iosCdvdBackGroundMgrSeek (1 syms rebound)
- PORTED `iosCdvdBackGroundMgrSeek` w1 @ 0x00135658 <- ntsc ios/cdvd:func_00133500 (1 syms rebound)
- PORTED `iosCdvdChgFileName` w1 @ 0x00135370 <- ntsc ios/cdvd:iosCdvdLoadPackFile (5 syms rebound)
- REVERTED `iosCdvdDirectStClose` w3 @ 0x00135330 — [codegen] insn 7: expected `lw	a0,356(s0)` built `lw	a0,352(s0)`
- PORTED `iosCdvdDirectStRead` w1 @ 0x00135668 <- ntsc ios/inflate:inflate_start (4 syms rebound)
- PORTED `iosCdvdDiskStatusGet` w2 @ 0x001355A0 <- ntsc ios/cdvd:iosCdvdBackGroundMgrDeleteRequestGet (2 syms rebound)
- PORTED `iosCdvdHandlerRead` w1 @ 0x001342E0 <- ntsc ios/cdvd:iosCdvdLoad (4 syms rebound)
- PORTED `iosCdvdLoad` w1 @ 0x00134800 <- ntsc ios/cdvd:iosCdvdBackGroundMgr (3 syms rebound)
- REVERTED `iosCdvdLoadPackFile` w3 @ 0x00135520 — [codegen] insn 14: expected `addiu	a0,s0,56` built `addiu	a0,s0,52`
- PORTED `iosCdvdPackLoad` w1 @ 0x00134838 <- ntsc ios/cdvd:iosCdvdDirectStOpen (3 syms rebound)
- PORTED `iosCdvdSync` w1 @ 0x001354F0 <- ntsc ios/cdvd:iosCdvdBackGroundMgrDelete (3 syms rebound)

### ios/inflate
- PORTED `huft_free` w1 @ 0x00137DA8 <- ntsc ios/ios:ios_init_plus (2 syms rebound)
- PORTED `inflate_start` w1 @ 0x00137658 <- ntsc ios/inflate:func_00135468 (2 syms rebound)

### ios/mblock
- PORTED `init_mblock` w1 @ 0x00138280 <- ntsc ios/mblock:new_segment (1 syms rebound)
- PORTED `reuse_mblock` w1 @ 0x00138338 <- ntsc ios/mblock:strdup_mblock (2 syms rebound)
- PORTED `reuse_mblock1` w1 @ 0x00138258 <- ntsc ios/mblock:init_mblock (3 syms rebound)

### ios/mcard
- PORTED `iosMcDelete` w1 @ 0x0013A1E8 <- ntsc ios/mcdata:iosMcIconWriteIcon (3 syms rebound)
- PORTED `iosMcFormat` w1 @ 0x0013A110 <- ntsc ios/mcard:iosMcSync (3 syms rebound)
- PORTED `iosMcGetInfo` w1 @ 0x0013A0D0 <- ntsc ios/mcard:iosMcTest (3 syms rebound)
- PORTED `iosMcMgrLoadProductBlock` w2 @ 0x001397D8 <- ntsc ios/mcard:iosMcMgrSaveProductBlock (2 syms rebound)
- PORTED `iosMcMgrSaveProductBlock` w2 @ 0x001397C8 <- ntsc ios/mcard:iosMcMgrLoadSeg (2 syms rebound)
- PORTED `iosMcSaveIconBlock` w1 @ 0x0013A230 <- ntsc ios/mcdata:_iosMcIconWriteIconsys (3 syms rebound)
- PORTED `iosMcSync` w1 @ 0x0013A0B8 <- ntsc ios/mcard:iosMcMgrSync (1 syms rebound)
- PORTED `iosMcTest` w2 @ 0x0013A0B0 <- ntsc ios/mcard:iosMcManager (1 syms rebound)
- PORTED `iosMcUnformat` w1 @ 0x0013A158 <- ntsc ios/mcard:iosMcGetInfo (3 syms rebound)
- REVERTED `product_read` w3 @ 0x0013A5A0 — [codegen] insn 1: expected `addiu	v1,zero,496` built `addiu	v1,zero,396`

### ios/memory
- PORTED `_iosFreeWithFill` w1 @ 0x0013B778 <- ntsc ios/memory:iosMallocCheckLeak (5 syms rebound)
- PORTED `iosFree` w3 @ 0x0013B820 <- ntsc ios/memory:iosMallocCheckLeak2 (23 syms rebound)
- PORTED `iosMallocCheckLeak2` w3 @ 0x0013BEB8 <- ntsc ios/memory:iosMallocInitPartition (13 syms rebound)
- REVERTED `iosMallocDebugNoAssert` w2 @ 0x0013C488 — [codegen] tu-size: TU .text 0x1A2C != PAL span 0x1A30 (trailing pad word / extra code)
- PORTED `iosMallocSetPartitionName` w1 @ 0x0013AE78 <- ntsc ios/memory:iosMallocDebug (7 syms rebound)

### ios/message
- REVERTED `deq_mes_th` w1 @ 0x0013C4A8 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `iosMsgInit` w1 @ 0x0013C808 <- ntsc ios/message:iosMsgInit (1 syms rebound)
- PORTED `iosMsgQueueDestroyAll` w1 @ 0x0013CA50 <- ntsc ios/message:iosMsgQueueDestroyAll (2 syms rebound)
- PORTED `signal_handler` w1 @ 0x0013CAA8 <- ntsc ios/pad:controler_stable_check (4 syms rebound)

### ios/pad
- PORTED `func_0013DE08` w1 @ 0x0013DE08 <- ntsc ios/shockdriver:Shock_SetMotor (6 syms rebound)
- PORTED `iosPadActInit` w1 @ 0x0013DC60 <- ntsc ios/pad:iosPadActStop (9 syms rebound)
- PORTED `iosPadActStop` w1 @ 0x0013DCD8 <- ntsc ios/shockdriver:Vibration_ShotDecode (3 syms rebound)
- PORTED `iosPadActStopAll` w1 @ 0x0013DD58 <- ntsc ios/shockdriver:Vibration_WaveDecode (3 syms rebound)
- PORTED `iosPadActVolumeSet` w1 @ 0x0013DDC0 <- ntsc ios/shockdriver:Shock_Request (2 syms rebound)
- PORTED `iosPadConnect` w1 @ 0x0013DB20 <- ntsc ios/pad:iosPadStickCameraCoord (2 syms rebound)
- PORTED `iosPadDevRead` w1 @ 0x0013DA78 <- ntsc ios/pad:iosPadGetPort (3 syms rebound)
- PORTED `iosPadDisable` w2 @ 0x0013DC50 <- ntsc ios/pad:iosPadEnableGet (2 syms rebound)
- PORTED `iosPadDisconWait` w2 @ 0x0013DF58 <- ntsc ios/shockdriver:Init_ShockVoiceSet (1 syms rebound)
- PORTED `iosPadEnable` w2 @ 0x0013DC40 <- ntsc ios/pad:iosPadDisable (2 syms rebound)
- PORTED `iosPadEnableGet` w2 @ 0x0013DC58 <- ntsc ios/pad:iosPadActInit (2 syms rebound)
- PORTED `iosPadErrorWait` w2 @ 0x0013DF60 <- ntsc ios/shockdriver:Vibration_SetDecodeData (1 syms rebound)
- PORTED `iosPadGetDevice` w1 @ 0x0013DAD8 <- ntsc ios/pad:iosPadConnect (2 syms rebound)
- PORTED `iosPadGetPort` w1 @ 0x0013DAA8 <- ntsc ios/pad:iosPadGetSlot (2 syms rebound)
- PORTED `iosPadGetSlot` w1 @ 0x0013DAC0 <- ntsc ios/pad:iosPadGetDevice (2 syms rebound)

### ios/shockdriver
- PORTED `Get_ShockRequestStruct` w1 @ 0x0013F118 <- ntsc ios/thread:iosThreadStart (1 syms rebound)
- PORTED `Init_Controler` w2 @ 0x0013F358 <- ntsc ios/thread:iosThreadName (1 syms rebound)
- PORTED `Init_ShockDriver` w1 @ 0x0013EE30 <- ntsc ios/shockdriver:ShockDriver_GetShockVoice (2 syms rebound)
- PORTED `Init_ShockEmulator` w2 @ 0x0013F048 <- ntsc ios/shockdriver:ShockRevice_Wave (1 syms rebound)
- PORTED `Init_ShockRequestAlloc` w1 @ 0x0013F0D0 <- ntsc ios/thread:iosThreadCreateS (1 syms rebound)
- REVERTED `Init_ShockRequestBox` w1 @ 0x0013E8F8 — [codegen] insn 5: expected `addiu	v0,v0,0` built `addiu	v0,v0,5400`
- PORTED `Init_ShockVoiceSet` w1 @ 0x0013E870 <- ntsc ios/shockdriver:ShockRequestBox_DecodeRequest (1 syms rebound)
- PORTED `Reset_ShockRequestStruct` w1 @ 0x0013F158 <- ntsc ios/thread:iosThreadStop (1 syms rebound)
- PORTED `ShockDriver_GetShockVoice` w1 @ 0x0013EFE8 <- ntsc ios/shockdriver:Reset_ShockRequestStruct (2 syms rebound)
- PORTED `ShockDriver_GetShockVoiceMax` w1 @ 0x0013EF70 <- ntsc ios/shockdriver:Init_ShockRequestAlloc (2 syms rebound)
- PORTED `ShockDriver_GetShockVoiceSet` w1 @ 0x0013EFB8 <- ntsc ios/shockdriver:Get_ShockRequestStruct (2 syms rebound)
- PORTED `ShockDriver_VoiceSet_NumberRegist` w1 @ 0x0013EE88 <- ntsc ios/shockdriver:Init_ShockEmulator (2 syms rebound)
- PORTED `ShockDriver_VoiceSet_Regist` w1 @ 0x0013EEC0 <- ntsc ios/shockdriver:ShockEmulator_EmulationShot (2 syms rebound)
- PORTED `ShockDriver_VoiceSet_Remove` w1 @ 0x0013EF38 <- ntsc ios/shockdriver:ShockEmulator_EmulationWave (2 syms rebound)
- PORTED `ShockEmulator_EmulationShot` w1 @ 0x0013F058 <- ntsc ios/shockdriver:Init_Shock (1 syms rebound)
- PORTED `ShockRequestBox_Clear` w2 @ 0x0013E920 <- ntsc ios/shockdriver:ShockRequestBox_GetRequest (1 syms rebound)
- PORTED `ShockRequestBox_EndRequestFree` w1 @ 0x0013EC08 <- ntsc ios/shockdriver:ShockDriver_VoiceSet_NumberRegist (2 syms rebound)
- PORTED `ShockRequestBox_GetRequest` w1 @ 0x0013ED08 <- ntsc ios/shockdriver:ShockDriver_VoiceSet_Remove (1 syms rebound)
- PORTED `ShockRequestBox_Regst` w1 @ 0x0013E980 <- ntsc ios/shockdriver:ShockRequestBox_RequestCancel (1 syms rebound)
- PORTED `ShockRequestBox_RequestCancel` w1 @ 0x0013ED40 <- ntsc ios/shockdriver:ShockDriver_GetShockVoiceMax (2 syms rebound)
- PORTED `ShockRequestBox_RequestDirectCancel` w1 @ 0x0013EDC0 <- ntsc ios/shockdriver:ShockDriver_GetShockVoiceSet (1 syms rebound)
- PORTED `Shock_RequestClear` w2 @ 0x0013F368 <- ntsc ios/thread:iosThreadSuspend (1 syms rebound)
- PORTED `Shock_SetMotor` w1 @ 0x0013E708 <- ntsc ios/shockdriver:ShockRequestBox_Request (2 syms rebound)
- PORTED `Shock_SetShockVoiceSet` w1 @ 0x0013F2F0 <- ntsc ios/thread:iosThreadSetPri (2 syms rebound)
- PORTED `Vibration_SetDecodeData` w1 @ 0x0013E8A8 <- ntsc ios/shockdriver:ShockRequestBox_EndRequestFree (1 syms rebound)
- PORTED `Vibration_SetDecodeEnd` w1 @ 0x0013F488 <- ntsc ios/thread:iosThreadCreate (1 syms rebound)
- PORTED `dumyAllocFunc` w2 @ 0x0013F480 <- ntsc ios/thread:iosThreadInit (1 syms rebound)

### ios/thread
- PORTED `iosThreadCancelWakeup` w1 @ 0x0013FDB0 <- ntsc ios/thread:func_0013D9C8 (3 syms rebound)
- PORTED `iosThreadDestroy` w1 @ 0x0013F7E0 <- ntsc ios/thread:iosSemaDelete (5 syms rebound)
- PORTED `iosThreadGetPri` w1 @ 0x0013FC88 <- ntsc ios/thread:func_0013D8A0 (3 syms rebound)
- REVERTED `iosThreadMain` w1 @ 0x0013F528 — [codegen] insn 20: expected `j	0 <iosThreadMain>` built `j	300 <iosThreadSetPri>`
- PORTED `iosThreadMessage` w1 @ 0x0013F880 <- ntsc ios/thread:iosSemaSignal (10 syms rebound)
- PORTED `iosThreadName` w2 @ 0x0013F920 <- ntsc ios/thread:iosSemaReferStatus (2 syms rebound)
- PORTED `iosThreadResume` w2 @ 0x0013F930 <- ntsc ios/thread:iosThreadAllQuit (2 syms rebound)
- PORTED `iosThreadSetPri` w1 @ 0x0013F828 <- ntsc ios/thread:iosSemaWait (4 syms rebound)
- PORTED `iosThreadSleep` w2 @ 0x0013F7D8 <- ntsc ios/thread:iosSemaCreate (2 syms rebound)
- PORTED `iosThreadStart` w1 @ 0x0013F7B0 <- ntsc ios/thread:iosThreadJoin (2 syms rebound)
- PORTED `iosThreadStop` w1 @ 0x0013F7C0 <- ntsc ios/thread:iosThreadCancelWakeup (3 syms rebound)
- PORTED `iosThreadSuspend` w2 @ 0x0013F928 <- ntsc ios/thread:iosThreadDestroyMgr (2 syms rebound)
- PORTED `iosThreadWakeup` w1 @ 0x0013FD10 <- ntsc ios/thread:func_0013D928 (2 syms rebound)

### isys/gobj
- REVERTED `isysGObjActiveDlLink` w2 @ 0x00141160 — [codegen] tu-size: TU .text 0x1024 != PAL span 0x1028 (trailing pad word / extra code)
- PORTED `isysGObjActiveLink` w2 @ 0x00141128 <- ntsc isys/gobj_dl:func_0013ED40 (2 syms rebound)
- PORTED `isysGObjGetExist_begin` w1 @ 0x00141090 <- ntsc isys/gobj_dl:isysGObjRemoveObjDL (3 syms rebound)
- REVERTED `isysGObjKindTableAdd` w3 @ 0x00140A30 — [codegen] insn 12: expected `jal	0 <isysGObjKindTableAdd>` built `jal	dc8 <isysGObjSearchFromObjKindID_begin>`
- REVERTED `isysGObjKindTableRemove` w3 @ 0x00140B10 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `isysGObjMove` w2 @ 0x00140578 <- ntsc isys/gobj:add_gobj_to_head (3 syms rebound)
- PORTED `isysGObjMoveBeforeGObj` w1 @ 0x00140C50 <- ntsc isys/gobj:isysGObjMoveAfterGObj (3 syms rebound)
- PORTED `isysGObjMoveHead` w2 @ 0x001405C0 <- ntsc isys/gobj:isysGObjMove (3 syms rebound)
- REVERTED `isysGObjRemove` w3 @ 0x00140930 — [codegen] insn 10: expected `sltiu	v0,v0,69` built `sltiu	v0,v0,67`
- REVERTED `isysGObjRemoveAll` w3 @ 0x00140288 — [codegen] insn 26: expected `sltiu	v0,v0,69` built `sltiu	v0,v0,67`
- REVERTED `isysGObjSearchFromObjKindID_begin` w3 @ 0x00140F38 — [undeclared] isys/gobj.c:93: dereferencing pointer to incomplete type
- REVERTED `isysGObjSearchFromObjKindID_next` w1 @ 0x00140FC8 — [undeclared] isys/gobj.c:94: dereferencing pointer to incomplete type
- PORTED `isysGObjSearchFromObjLayoutID` w1 @ 0x00140ED0 <- ntsc isys/gobj:isysGObjAddHead (3 syms rebound)
- PORTED `isysGetNbAllocedGObjs` w1 @ 0x00140870 <- ntsc isys/gobj:isysGObjAddBeforeGObj (3 syms rebound)

### isys/gobj_cam_dl
- PORTED `isysGObjCameraDlInit` w2 @ 0x0020C260 <- ntsc isys/gobj_cam_dl:isysGObjLinkCameraDLAfterGObj (3 syms rebound)
- PORTED `isysGObjLinkCameraDLAfterGObj` w2 @ 0x0020C1B0 <- ntsc isys/gobj_cam_dl:isysGObjMoveCameraDL (4 syms rebound)
- PORTED `isysGObjLinkCameraDLBeforeGObj` w2 @ 0x0020C208 <- ntsc isys/gobj_cam_dl:isysGObjLinkCameraDL (4 syms rebound)
- PORTED `isysGObjMoveCameraDL` w1 @ 0x0020C0F8 <- ntsc isys/gobj_cam_dl:isysGObjRemoveCameraDL (3 syms rebound)
- PORTED `isysGObjMoveCameraDLHead` w1 @ 0x0020C270 <- ntsc isys/gobj_cam_dl:isysGObjLinkCameraDLBeforeGObj (4 syms rebound)
- PORTED `isysGObjRemoveCameraDL` w2 @ 0x0020BFD0 <- ntsc src/EnemyInit:func_001FC040 (2 syms rebound)
- PORTED `isysObjMoveCameraDLAfterGObj` w1 @ 0x0020C3F0 <- ntsc isys/gobj_cam_dl:adpcmTickProc2 (3 syms rebound)
- REVERTED `isysObjMoveCameraDLBeforeGObj` w1 @ 0x0020C450 — [codegen] tu-size: TU .text 0x554 != PAL span 0x558 (trailing pad word / extra code)

### isys/gobj_dl
- PORTED `func_001413B8` w1 @ 0x001413B8 <- ntsc isys/gobj_dl:isysGObjLinkObjDLAfterGObj (3 syms rebound)
- PORTED `isysGObjLinkObjDLAfterGObj` w2 @ 0x001415E0 <- ntsc isys/gobj_dl:func_0013F1F8 (4 syms rebound)
- PORTED `isysGObjLinkObjDLBeforeGObj` w2 @ 0x00141648 <- ntsc isys/gobj_dl:func_0013F260 (4 syms rebound)
- PORTED `isysGObjLinkObjDLHead` w1 @ 0x001415B8 <- ntsc isys/gobj_dl:isysGObjMoveObjDLBeforeGObj (2 syms rebound)
- PORTED `isysGObjMoveObjDL` w2 @ 0x00141488 <- ntsc isys/gobj_dl:isysGObjLinkObjDLBeforeGObj (3 syms rebound)
- PORTED `isysGObjMoveObjDLAfterGObj` w1 @ 0x001416F0 <- ntsc isys/gobj_process:isysGObjProcAdd_ (3 syms rebound)
- PORTED `isysGObjMoveObjDLBeforeGObj` w1 @ 0x00141760 <- ntsc isys/gobj_process:cut_gobj_process_link (3 syms rebound)
- PORTED `isysGObjMoveObjDLHead` w2 @ 0x001414D0 <- ntsc isys/gobj_dl:isysGObjDlInit (3 syms rebound)
- PORTED `isysGObjRemoveObjDL` w2 @ 0x00141240 <- ntsc isys/gobj_dl:isysGObjLinkObjDL (2 syms rebound)

### isys/gobj_process
- PORTED `free_gobj_process_resource` w2 @ 0x00141D78 <- ntsc isys/isys:func_0013F990 (1 syms rebound)
- PORTED `isysGObjProcActive` w1 @ 0x00141C60 <- ntsc isys/isys:func_0013F878 (1 syms rebound)
- PORTED `isysGObjProcActiveAll` w1 @ 0x00141C70 <- ntsc isys/isys:func_0013F888 (1 syms rebound)
- PORTED `isysGObjProcActivePtr` w1 @ 0x00141D48 <- ntsc isys/isys:func_0013F960 (1 syms rebound)
- PORTED `isysGObjProcAdd` w1 @ 0x00141B60 <- ntsc isys/gobj_process:isysGObjProcPause (2 syms rebound)
- PORTED `isysGObjProcAddGOppArg` w1 @ 0x00141BC0 <- ntsc isys/gobj_process:isysGObjProcPausePtr (2 syms rebound)
- PORTED `isysGObjProcAddS` w1 @ 0x00141B90 <- ntsc isys/gobj_process:isysGObjProcPauseAll (2 syms rebound)
- PORTED `isysGObjProcAddSGOppArg` w1 @ 0x00141D18 <- ntsc isys/isys:func_0013F930 (2 syms rebound)
- PORTED `isysGObjProcPause` w1 @ 0x00141BF0 <- ntsc isys/gobj_process:isysGObjProcActive (1 syms rebound)
- PORTED `isysGObjProcPauseAll` w1 @ 0x00141BF8 <- ntsc isys/gobj_process:isysGObjProcActiveAll (1 syms rebound)
- PORTED `isysGObjProcPausePtr` w1 @ 0x00141C30 <- ntsc isys/isys:isysInitialize (1 syms rebound)
- PORTED `isysGObjProcRemove` w1 @ 0x00141AA0 <- ntsc isys/gobj_process:isysGObjProcAddS (3 syms rebound)
- PORTED `isysGObjProcRemoveAll` w1 @ 0x00141CA8 <- ntsc isys/isys:func_0013F8C0 (2 syms rebound)
- PORTED `isysGObjProcThreadSleep` w1 @ 0x00141CE0 <- ntsc isys/isys:func_0013F8F8 (2 syms rebound)
- PORTED `isysGObjProcessAlloc` w1 @ 0x00141AE8 <- ntsc isys/gobj_process:isysGObjProcAddGOppArg (6 syms rebound)
- REVERTED `isysGObjProcessInit` w2 @ 0x001417D0 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)

### isys/isys
- PORTED `isysInitialize` w2 @ 0x00141D80 <- ntsc isys/isys:func_0013F998 (2 syms rebound)

### isys/obj_manager
- PORTED `iosOmBeforeFuncStandard` w2 @ 0x00142368 <- ntsc isys/obj_manager:iosOmSearchGObjIdAll (1 syms rebound)
- PORTED `iosOmExeEachGObj` w1 @ 0x001420F8 <- ntsc isys/obj_manager:iosOmCreateDL (2 syms rebound)
- PORTED `iosOmExeEachGObjAll` w1 @ 0x00142160 <- ntsc isys/obj_manager:iosOmExeEachGObj (2 syms rebound)
- PORTED `iosOmGetGObjStatus` w1 @ 0x00142298 <- ntsc isys/obj_manager:iosOmReturnExeEachGObj (2 syms rebound)
- REVERTED `iosOmInit` w1 @ 0x00141D88 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `iosOmMain` w2 @ 0x00141FE0 <- ntsc isys/obj_manager:_iosOmMain (2 syms rebound)
- PORTED `iosOmReturnExeEachGObj` w1 @ 0x00142200 <- ntsc isys/obj_manager:iosOmExeEachGObjAll (2 syms rebound)
- PORTED `iosOmSearchGObjId` w1 @ 0x001422C8 <- ntsc isys/obj_manager:iosOmGetGObjStatus (2 syms rebound)
- PORTED `iosOmSearchGObjIdAll` w1 @ 0x00142308 <- ntsc isys/obj_manager:iosOmSearchGObjId (2 syms rebound)
- PORTED `iosOmSendMail` w1 @ 0x00142370 <- ntsc isys/obj_manager:iosOmBeforeFuncStandard (1 syms rebound)
- PORTED `iosOmSendMailLink` w1 @ 0x001423B8 <- ntsc isys/obj_manager:soundInit (2 syms rebound)

### ito/mpeg/mv_audiodec
- PORTED `audioDecIsPreset` w1 @ 0x00257F10 <- ntsc ito/mpeg/mv_sub:func_0023E280 (1 syms rebound)
- PORTED `audioDecPause` w1 @ 0x00257FC0 <- ntsc ito/mpeg/mv_sub:func_0023E330 (3 syms rebound)
- PORTED `audioDecReset` w1 @ 0x00257EB8 <- ntsc ito/mpeg/mv_sub:func_0023E228 (3 syms rebound)
- REVERTED `audioDecResume` w2 @ 0x00257FF8 — [codegen] tu-size: TU .text 0xB3C != PAL span 0xB40 (trailing pad word / extra code)
- PORTED `audioDecStart` w2 @ 0x00257F28 <- ntsc ito/mpeg/mv_sub:func_0023E298 (4 syms rebound)

### ito/mpeg/mv_disp
- PORTED `dispDelete` w2 @ 0x00258B08 <- ntsc ito/mpeg/mv_vibuf:func_0023EFB0 (1 syms rebound)
- PORTED `dispSwitch` w1 @ 0x00258948 <- ntsc ito/mpeg/mv_sub:func_0023EDF0 (2 syms rebound)
- PORTED `endDisplay` w2 @ 0x00258BC8 <- ntsc ito/mpeg/mv_vibuf:viBufEndPut (3 syms rebound)
- PORTED `handler_endimage` w1 @ 0x00258B50 <- ntsc ito/mpeg/mv_vibuf:viBufReset (4 syms rebound)
- PORTED `loadImage` w1 @ 0x00258B10 <- ntsc ito/mpeg/mv_vibuf:viBufCreate (1 syms rebound)
- PORTED `setBITBLTBUF` w1 @ 0x00259260 <- ntsc src/GobjProc:GetMaxGObj (1 syms rebound)
- PORTED `setDMAscTag` w1 @ 0x00258BD8 <- ntsc ito/mpeg/mv_vibuf:viBufAddDMA (1 syms rebound)
- PORTED `setGIFad` w1 @ 0x00258C88 <- ntsc ito/mpeg/mv_vibuf:viBufRestartDMA (1 syms rebound)
- PORTED `setGIFtag` w1 @ 0x00258C30 <- ntsc ito/mpeg/mv_vibuf:viBufStopDMA (1 syms rebound)
- PORTED `setImageSize` w1 @ 0x002583E8 <- ntsc ito/mpeg/mv_sub:func_0023E770 (2 syms rebound)
- PORTED `setPRIM` w1 @ 0x00258E10 <- ntsc ito/mpeg/mv_vibuf:viBufDelete (1 syms rebound)
- PORTED `setPRMODECONT` w1 @ 0x00259128 <- ntsc ito/mpeg/mv_vibuf:func_0023F5D0 (1 syms rebound)
- PORTED `setRGBAQ` w1 @ 0x00258EF0 <- ntsc ito/mpeg/mv_vibuf:viBufPutTs (1 syms rebound)
- PORTED `setTEX0_1` w1 @ 0x00258D58 <- ntsc ito/mpeg/mv_vibuf:viBufGetTs (1 syms rebound)
- PORTED `setTEX1_1` w1 @ 0x00258CD8 <- ntsc ito/mpeg/mv_vibuf:viBufModifyPts (1 syms rebound)
- PORTED `setTEXFLUSH` w1 @ 0x00258CB8 <- ntsc ito/mpeg/mv_vibuf:viBufFlush (1 syms rebound)
- REVERTED `setTRXDIR` w1 @ 0x00259308 — [codegen] tu-size: TU .text 0x12A4 != PAL span 0x12A8 (trailing pad word / extra code)
- PORTED `setTRXPOS` w1 @ 0x00259298 <- ntsc src/GobjProc:GetGObjP (1 syms rebound)
- PORTED `setTRXREG` w1 @ 0x002592D0 <- ntsc src/GobjProc:GetGObjId (1 syms rebound)
- PORTED `setUV` w1 @ 0x00258EA8 <- ntsc ito/mpeg/mv_vibuf:viBufCount (1 syms rebound)
- PORTED `startDisplay` w1 @ 0x00258B88 <- ntsc ito/mpeg/mv_vibuf:viBufBeginPut (5 syms rebound)

### ito/mpeg/mv_main
- PORTED `proceedAudio` w2 @ 0x001A5DC0 <- ntsc src/stage_orient:StageOrientGet2 (3 syms rebound)
- REVERTED `switchThread` w2 @ 0x001A5DB8 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)

### ito/mpeg/mv_readbuf
- PORTED `readBufBeginGet` w1 @ 0x001A6938 <- ntsc ito/mpeg/mv_main:movie_proc (1 syms rebound)
- PORTED `readBufBeginPut` w1 @ 0x001A68C8 <- ntsc ito/mpeg/mv_main:movie_init (1 syms rebound)
- REVERTED `readBufEndGet` w1 @ 0x001A6980 — [codegen] tu-size: TU .text 0x18C != PAL span 0x190 (trailing pad word / extra code)
- PORTED `readBufEndPut` w1 @ 0x001A68F8 <- ntsc ito/mpeg/mv_main:movie_end (1 syms rebound)

### ito/mpeg/mv_strfile
- PORTED `strFileClose` w2 @ 0x001A69D8 <- ntsc ito/mpeg/mv_readbuf:readBufCreate (2 syms rebound)
- REVERTED `strFileOpen` w3 @ 0x001A69A0 — [codegen] insn 5: expected `addiu	a0,s0,56` built `addiu	a0,s0,52`
- REVERTED `strFileRead` w2 @ 0x001A69F8 — [codegen] tu-size: TU .text 0x74 != PAL span 0x78 (trailing pad word / extra code)

### ito/mpeg/mv_sub
- PORTED `ErrMessage` w2 @ 0x00259338 <- ntsc src/GobjProc:InitCameraGObjs (3 syms rebound)
- PORTED `copy2area` w1 @ 0x00259348 <- ntsc src/GobjProc:CreateGObj (2 syms rebound)

### ito/mpeg/mv_vibuf
- REVERTED `func_00259480` w1 @ 0x00259480 — [codegen] insn 4: expected `jal	0 <func_00259480>` built `jal	1028 <func_0025A4A8>`
- PORTED `func_0025A4A8` w2 @ 0x0025A4A8 <- ntsc src/GobjProc:func_00240950 (2 syms rebound)
- PORTED `viBufCount` w1 @ 0x0025A578 <- ntsc src/GobjProc:func_00240A20 (3 syms rebound)

### ito/mpeg/mv_videodec
- PORTED `Free` w2 @ 0x001A6F80 <- ntsc ito/mpeg/mv_strfile:func_0019E150 (2 syms rebound)
- REVERTED `free_buf` w1 @ 0x001A6A18 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)
- PORTED `mpegError` w1 @ 0x001A70A8 <- ntsc ito/mpeg/mv_videodec:videoDecEndPut (3 syms rebound)
- PORTED `mpegNodata` w1 @ 0x001A70D0 <- ntsc ito/mpeg/mv_videodec:videoDecFlush (3 syms rebound)
- PORTED `mpegRestartDMA` w2 @ 0x001A7120 <- ntsc ito/mpeg/mv_videodec:decBitStrm0 (2 syms rebound)
- PORTED `mpegStopDMA` w2 @ 0x001A7100 <- ntsc ito/mpeg/mv_videodec:videoCallback (2 syms rebound)
- PORTED `mpegTS` w1 @ 0x001A7140 <- ntsc ito/mpeg/mv_vobuf:func_0019E310 (2 syms rebound)
- PORTED `videoDecAbort` w1 @ 0x001A6FF0 <- ntsc ito/mpeg/mv_strfile:func_0019E1C0 (1 syms rebound)
- PORTED `videoDecBeginPut` w2 @ 0x001A6B68 <- ntsc ito/mpeg/mv_readbuf:readBufEndGet (2 syms rebound)
- PORTED `videoDecDelete` w1 @ 0x001A6F90 <- ntsc ito/mpeg/mv_strfile:func_0019E160 (4 syms rebound)
- PORTED `videoDecEndPut` w2 @ 0x001A6B70 <- ntsc ito/mpeg/mv_strfile:strFileOpen (2 syms rebound)
- PORTED `videoDecGetState` w1 @ 0x001A7000 <- ntsc ito/mpeg/mv_videodec:free_buf (1 syms rebound)
- PORTED `videoDecIsFlushed` w1 @ 0x001A7008 <- ntsc ito/mpeg/mv_videodec:videoDecCreate (3 syms rebound)
- PORTED `videoDecMain` w1 @ 0x001A7058 <- ntsc ito/mpeg/mv_videodec:videoDecBeginPut (4 syms rebound)
- PORTED `videoDecSetStream` w2 @ 0x001A6FD0 <- ntsc ito/mpeg/mv_strfile:func_0019E1A0 (2 syms rebound)

### ito/mpeg/mv_vobuf
- PORTED `func_001A7318` w2 @ 0x001A7318 <- ntsc ito/mpeg/mv_vobuf:voBufIsFull (2 syms rebound)
- PORTED `voBufDecCount` w1 @ 0x001A7458 <- ntsc src/DObj:allocObjectData (1 syms rebound)
- PORTED `voBufDelete` w2 @ 0x001A7310 <- ntsc ito/mpeg/mv_vobuf:voBufReset (2 syms rebound)
- REVERTED `voBufGetData` w1 @ 0x001A73C8 — [codegen] insn 5: expected `lui	v0,0x19` built `lui	v0,0x15`
- REVERTED `voBufGetTag` w1 @ 0x001A7400 — [codegen] insn 5: expected `lui	a2,0xc` built `lui	a2,0xa`
- REVERTED `voBufIncCount` w1 @ 0x001A7350 — [codegen] insn 6: expected `lui	v0,0xc` built `lui	v0,0xa`
- PORTED `voBufIsFull` w1 @ 0x001A7338 <- ntsc ito/mpeg/mv_vobuf:voBufGetData (1 syms rebound)
- PORTED `voBufReset` w1 @ 0x001A7328 <- ntsc ito/mpeg/mv_vobuf:voBufIncCount (1 syms rebound)

### sound/adpcm_init
- PORTED `AdpcmFadeCloseAll` w1 @ 0x001432D0 <- ntsc sound/adpcm_init:AdpcmInterStereoVolumeSetAll (2 syms rebound)
- PORTED `AdpcmFreeAreaGet` w1 @ 0x00143340 <- ntsc sound/adpcm_init:AdpcmVolumeGet (2 syms rebound)
- PORTED `AdpcmInterLeaveVolumeGet` w1 @ 0x00143408 <- ntsc sound/adpcm_init:DebugActOrientFlag (1 syms rebound)
- PORTED `AdpcmInterLeaveVolumeSet` w1 @ 0x00142F18 <- ntsc sound/adpcm_init:AdpcmIopBuffAlloc (2 syms rebound)
- PORTED `AdpcmInterStereoVolumeSetAll` w1 @ 0x00143378 <- ntsc sound/adpcm_init:GetDitchPosition (3 syms rebound)
- PORTED `AdpcmIopBuffAlloc` w1 @ 0x001430C8 <- ntsc sound/adpcm_init:AdpcmUseAreaGet (5 syms rebound)
- PORTED `AdpcmOpenSync` w1 @ 0x00143230 <- ntsc sound/adpcm_init:AdpcmFreeAreaGet (7 syms rebound)
- PORTED `AdpcmPlay` w1 @ 0x00142AF8 <- ntsc sound/adpcm_init:AdpcmClose (4 syms rebound)
- PORTED `AdpcmStop` w1 @ 0x00142B28 <- ntsc sound/adpcm_init:AdpcmInterStereoVolumeSet (2 syms rebound)
- REVERTED `AdpcmStreamFree` w2 @ 0x00142518 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)
- PORTED `AdpcmUseAreaGet` w1 @ 0x00143308 <- ntsc sound/adpcm_init:AdpcmInterLeaveVolumeGet (2 syms rebound)
- PORTED `AdpcmVolumeGet` w1 @ 0x00143420 <- ntsc sound/adpcm_init:ACTGetEnvironment (1 syms rebound)
- PORTED `AdpcmVolumeSet` w1 @ 0x00142F48 <- ntsc sound/adpcm_init:AdpcmOpenSync (2 syms rebound)
- PORTED `adpcmDiskNotReady` w2 @ 0x00143510 <- ntsc sound/adpcm_init:GetSofaPosition (1 syms rebound)
- PORTED `adpcmDiskReturnReady` w2 @ 0x00143518 <- ntsc sound/adpcm_init:GetCollisCenterPositionSimple (1 syms rebound)
- PORTED `adpcmOpenDiskNotReady` w2 @ 0x00143548 <- ntsc sound/adpcm_init:func_00141160 (1 syms rebound)
- PORTED `adpcmOpenProc` w1 @ 0x00143520 <- ntsc sound/adpcm_init:CheckWallAttributeEdegWall (2 syms rebound)
- PORTED `adpcmPauseRequest` w2 @ 0x00142F58 <- ntsc sound/adpcm_init:AdpcmFadeCloseAll (2 syms rebound)

### sound/s_init
- PORTED `Ee2Iop` w1 @ 0x00145EB8 <- ntsc sound/s_init:soundOutputModeGet (8 syms rebound)
- PORTED `debug_req` w1 @ 0x00146AD0 <- ntsc sound/soundManager:sndInit (5 syms rebound)
- PORTED `func_00146778` w1 @ 0x00146778 <- ntsc sound/s_init:soundSeKindBuild (7 syms rebound)
- PORTED `soundAllocIopFree` w2 @ 0x00143788 <- ntsc sound/s_init:soundBufAlloc (3 syms rebound)
- PORTED `soundAllocIopHeap` w1 @ 0x00143728 <- ntsc sound/s_init:soundDataOpenChk (7 syms rebound)
- PORTED `soundBufAdpcmFree` w1 @ 0x00146098 <- ntsc sound/s_init:soundDataAreaSearch (2 syms rebound)
- PORTED `soundBufSegFree` w3 @ 0x00143C50 <- ntsc sound/s_init:soundDataOpen (9 syms rebound)
- PORTED `soundDataAreaSearch` w1 @ 0x001460B8 <- ntsc sound/s_init:soundDataAreaGet (2 syms rebound)
- REVERTED `soundDataOpen` w3 @ 0x00144010 — [codegen] insn 12: expected `addiu	a1,zero,623` built `addiu	a1,zero,618`
- PORTED `soundDataSegAllClose` w1 @ 0x00144340 <- ntsc sound/s_init:debug_DispSEInfo (4 syms rebound)
- PORTED `soundHDDataSet` w1 @ 0x00146248 <- ntsc sound/s_init:soundSQDataSet (8 syms rebound)
- PORTED `soundOutputModeGet` w2 @ 0x00145F70 <- ntsc sound/s_init:soundReverbDepthGet (2 syms rebound)
- PORTED `soundOutputModeSet` w1 @ 0x001436A0 <- ntsc sound/s_init:soundAllocIopHeap (3 syms rebound)
- PORTED `soundReverbDepthGet` w2 @ 0x00145F78 <- ntsc sound/s_init:soundBufAdpcmChAlloc (2 syms rebound)
- PORTED `soundReverbDepthSet` w1 @ 0x001436B0 <- ntsc sound/s_init:soundAllocIopFree (4 syms rebound)
- REVERTED `soundSQDataSet` w1 @ 0x001463A8 — [redefinition] sound/s_init.c:29: redefinition of `hd_search'
- PORTED `soundSeDefPitchSet` w1 @ 0x00145638 <- ntsc sound/s_init:soundSeEnvPlay (3 syms rebound)
- PORTED `soundSeDefPlay` w1 @ 0x00146508 <- ntsc sound/s_init:soundSeDefPlayWithVolumeRate (4 syms rebound)
- PORTED `soundSeDefPlayWithVolumeRate` w1 @ 0x00146560 <- ntsc sound/s_init:soundSeDefVolumeRateGet (4 syms rebound)
- PORTED `soundSeDefStop` w2 @ 0x00145628 <- ntsc sound/s_init:soundSeDefPitchSet (2 syms rebound)
- PORTED `soundSeDefStopNoRelease` w1 @ 0x00145630 <- ntsc sound/s_init:soundReqTickProc (2 syms rebound)
- PORTED `soundSeDefVolumeRateGet` w1 @ 0x001465B0 <- ntsc sound/s_init:soundSeDefVolumeRateSet (2 syms rebound)
- PORTED `soundSeDefVolumeRateSet` w1 @ 0x001465F0 <- ntsc sound/s_init:soundSeGroupStop (2 syms rebound)
- PORTED `soundSeGroupGet` w1 @ 0x001466C8 <- ntsc sound/s_init:soundSePlayModeStop (2 syms rebound)
- PORTED `soundSeGroupStop` w1 @ 0x00146628 <- ntsc sound/s_init:soundSeGroupGet (3 syms rebound)
- REVERTED `soundSeKindBuild` w3 @ 0x001468E8 — [codegen] insn 1: expected `addiu	a1,zero,1419` built `addiu	a1,zero,1388`
- PORTED `soundSePlayModeStop` w1 @ 0x001466F0 <- ntsc sound/s_init:soundVBlank (3 syms rebound)
- PORTED `soundSeSemiCommonLoadChk` w2 @ 0x001469A8 <- ntsc sound/s_init:debug_req (2 syms rebound)
- PORTED `soundVBlank` w1 @ 0x00146888 <- ntsc sound/s_init:soundSeSemiCommonLoadChk (3 syms rebound)

### sound/soundManager
- REVERTED `sndBgmReadyNextStage` w1 @ 0x00146B68 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x60 (out-of-line helper or extra code)
- PORTED `sndInit` w1 @ 0x00146BC8 <- ntsc sound/soundManager:func_001447E0 (5 syms rebound)

### src/Basic
- REVERTED `dma_init` w1 @ 0x00205DA8 — [codegen] insn 25: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `freeseki` w1 @ 0x00205F18 <- ntsc src/Basic:resetmallocseki (2 syms rebound)
- PORTED `malloc_GetPartition` w2 @ 0x00205E30 <- ntsc src/Basic:mallocseki (2 syms rebound)
- PORTED `malloc_MemCpy` w2 @ 0x00205E20 <- ntsc src/Basic:malloc_SetPartition (2 syms rebound)
- PORTED `malloc_SetPartition` w2 @ 0x00205E28 <- ntsc src/Basic:malloc_GetPartition (2 syms rebound)
- PORTED `mallocsekistage` w1 @ 0x00205F40 <- ntsc src/Basic:reallocseki (5 syms rebound)
- PORTED `matrix_init` w1 @ 0x00205E10 <- ntsc src/Basic:malloc_MemCpy (3 syms rebound)
- REVERTED `reallocseki` w1 @ 0x00205F88 — [codegen] tu-size: TU .text 0x204 != PAL span 0x208 (trailing pad word / extra code)
- PORTED `resetmallocseki` w2 @ 0x00205F38 <- ntsc src/Basic:mallocsekistage (1 syms rebound)

### src/BgAnimation
- PORTED `bga_GetCameraMatrix` w1 @ 0x0020A610 <- ntsc src/BgAnimation:bga_ResetCamera (6 syms rebound)
- PORTED `bga_GetZoom` w1 @ 0x0020AA88 <- ntsc src/DisplayFont:func_001FAAA8 (2 syms rebound)
- PORTED `bga_InitBGA` w2 @ 0x0020AA20 <- ntsc src/DisplayFont:font_GetHeight (3 syms rebound)
- REVERTED `bga_InitSdfCamera` w3 @ 0x0020A658 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PORTED `bga_ResetCamera` w2 @ 0x0020A608 <- ntsc src/BgAnimation:bga_DispLightning (2 syms rebound)
- PORTED `bga_SetCameraForceOff` w2 @ 0x0020AA10 <- ntsc src/DisplayFont:font_GetWidth (2 syms rebound)
- PORTED `bga_SetUniqAnimationFlag` w2 @ 0x0020AA30 <- ntsc src/DisplayFont:font_Init (2 syms rebound)
- REVERTED `bga_addLightning` w3 @ 0x00209E50 — [codegen] src/BgAnimation.c:82: invalid lvalue in increment

### src/DObj
- PORTED `FreeDObj` w2 @ 0x001A8318 <- ntsc src/DObj:func_0019F4E0 (1 syms rebound)
- PORTED `UnlinkParentOfDObj` w3 @ 0x001A8368 <- ntsc src/DObj:func_0019F530 (4 syms rebound)
- REVERTED `initInitialInverseMatrix` w3 @ 0x001A7D40 — [codegen] insn 7: expected `addiu	a3,zero,333` built `addiu	a3,zero,332`

### src/DisplayFont
- PORTED `font_GetHeight` w1 @ 0x0020B410 <- ntsc src/DisplayList:dl_Swap (2 syms rebound)
- PORTED `font_GetWidth` w1 @ 0x0020B408 <- ntsc src/DisplayList:dl_Clear (1 syms rebound)
- REVERTED `font_Init` w1 @ 0x0020B438 — [codegen] tu-size: TU .text 0x9C4 != PAL span 0x9C8 (trailing pad word / extra code)

### src/DisplayList
- PORTED `dl_Clear` w1 @ 0x0020B570 <- ntsc src/DisplayList:dl_Debug (8 syms rebound)
- PORTED `dl_Debug` w1 @ 0x0020B810 <- ntsc src/DisplayList:dl_OpenDma (5 syms rebound)
- PORTED `dl_GetPri` w2 @ 0x0020BAD0 <- ntsc src/DmaPacket:dpk_CheckBufferSize (2 syms rebound)
- PORTED `dl_OpenDma` w1 @ 0x0020BA38 <- ntsc src/DmaPacket:dpk_Init (4 syms rebound)
- REVERTED `dl_PopPriority` w3 @ 0x0020B788 — [codegen] insn 10: expected `addiu	a1,zero,552` built `addiu	a1,zero,544`
- REVERTED `dl_PushPriority` w3 @ 0x0020B6F8 — [codegen] insn 11: expected `addiu	a1,zero,534` built `addiu	a1,zero,526`
- PORTED `dl_SetDLPriority` w1 @ 0x0020BA10 <- ntsc src/DmaPacket:dpk_SwapBuffer (2 syms rebound)
- PORTED `dl_Swap` w1 @ 0x0020B5E8 <- ntsc src/DisplayList:dl_CloseDma (10 syms rebound)

### src/DisplayP2O
- PORTED `p2o_DispShadowVolume` w2 @ 0x0010EC28 <- ntsc src/DisplayP2O:func_0010EC60 (2 syms rebound)
- PORTED `p2o_DispVU1` w2 @ 0x0010EC80 <- ntsc src/FileManager:func_0010ECB8 (2 syms rebound)
- PORTED `p2o_DispVU1DObj` w2 @ 0x0010EC60 <- ntsc src/FileManager:file_Init (2 syms rebound)
- PORTED `p2o_DispVU1DObjMulti` w2 @ 0x0010EC68 <- ntsc src/FileManager:file_LoadCDFile (2 syms rebound)
- PORTED `p2o_DispVU1Default` w2 @ 0x0010EC88 <- ntsc src/FileManager:func_0010ECC0 (2 syms rebound)
- PORTED `p2o_DispVU1Multi` w2 @ 0x0010EC70 <- ntsc src/FileManager:file_LoadFile (2 syms rebound)
- PORTED `p2o_DispVU1MultiDefault` w2 @ 0x0010EC78 <- ntsc src/FileManager:func_0010ECB0 (2 syms rebound)
- PORTED `p2o_HideDispVU1` w1 @ 0x0010EC30 <- ntsc src/DisplayP2O:func_0010EC68 (5 syms rebound)
- REVERTED `p2o_MakePacket` w3 @ 0x0010EC18 — [codegen] insn 1: expected `lw	v1,2132(v0)` built `lw	v1,2080(v0)`
- PORTED `p2o_SetDefaultEnviroment` w2 @ 0x0010ECA0 <- ntsc src/FileManager:func_0010ECD8 (1 syms rebound)
- PORTED `p2o_TransMicroProgram` w1 @ 0x0010EC90 <- ntsc src/FileManager:func_0010ECC8 (4 syms rebound)

### src/DmaPacket
- PORTED `dpk_CheckBufferSize` w1 @ 0x0020BBA8 <- ntsc src/EnemyInit:enemy_Initialize (2 syms rebound)
- PORTED `func_0020BB70` w1 @ 0x0020BB70 <- ntsc src/DmaPacket:func_001FBBE0 (2 syms rebound)

### src/EnemyInit
- PORTED `enemy_GetPositionTable` w1 @ 0x0020BF18 <- ntsc src/EnemyInit:func_001FBF88 (3 syms rebound)

### src/FileManager
- REVERTED `file_LoadFile` w2 @ 0x0010F630 — [codegen] tu-size: TU .text 0x9A4 != PAL span 0x9A8 (trailing pad word / extra code)

### src/GifPacket
- PORTED `_IsInScreen` w1 @ 0x001124F0 <- ntsc src/GsBase:gsb_scissorOnDemo (1 syms rebound)
- PORTED `gif_CheckOpen` w2 @ 0x00111BD8 <- ntsc src/GifPacket:gif_SpriteSensitiveOrg (2 syms rebound)
- PORTED `gif_Init` w2 @ 0x00111B48 <- ntsc src/GifPacket:gif_SpriteSensitive (2 syms rebound)
- PORTED `gif_SetAlpha` w1 @ 0x00112240 <- ntsc src/GsBase:gsb_SetFrame (3 syms rebound)
- PORTED `gif_SetGsReg` w1 @ 0x00111BB0 <- ntsc src/GifPacket:gif_SpriteOrg (2 syms rebound)
- PORTED `gif_SetZTest` w1 @ 0x001123E0 <- ntsc src/GsBase:gsb_Reduction (2 syms rebound)
- PORTED `gif_SetZWrite` w3 @ 0x00112420 <- ntsc src/GsBase:gsb_KeepFrameBuffer (2 syms rebound)
- REVERTED `gif_StartPacketPath1` w2 @ 0x0010F788 — [callee-sig-conflict] src/GifPacket.c:89: conflicting types for `D_004EE6F0__pn'
- PORTED `gif_StartPacketPri` w2 @ 0x00111B50 <- ntsc src/GifPacket:gif_SpriteOffset (4 syms rebound)
- PORTED `gif_StartPacketPriPath1` w2 @ 0x00111B80 <- ntsc src/GifPacket:gif_SpriteSensitiveOffset (4 syms rebound)

### src/GobjProc
- PORTED `GetGObjId` w1 @ 0x0025A6E0 <- ntsc src/PObj:InitPObj (3 syms rebound)
- PORTED `GetGObjP` w2 @ 0x0025A6C8 <- ntsc src/PObj:AllocPObj (2 syms rebound)
- PORTED `GetMaxGObj` w2 @ 0x0025A6C0 <- ntsc src/PObj:MakePacket (2 syms rebound)
- PORTED `PrintGObjID` w1 @ 0x0025A728 <- ntsc src/PObj:FreePObj (5 syms rebound)
- REVERTED `ResetGObjProc` w2 @ 0x0025A6B8 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)

### src/GsBase
- PORTED `gsb_ClearFrameBuffer` w1 @ 0x00116500 <- ntsc src/Light:light_InitLight (1 syms rebound)
- PORTED `gsb_GetBGColor` w1 @ 0x00116250 <- ntsc src/Light:light_MakeLightMatrix (2 syms rebound)
- REVERTED `gsb_LoadStageSettings` w3 @ 0x001163B0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `gsb_SetBGColor` w1 @ 0x001161F8 <- ntsc src/Light:light_getAmbientLight (2 syms rebound)
- PORTED `gsb_SetZoom` w1 @ 0x00116338 <- ntsc src/Light:light_DispVolume (3 syms rebound)
- PORTED `gsb_setNormalReg` w1 @ 0x00113BA0 <- ntsc src/GsBase:gsb_PostEffect (6 syms rebound)
- PORTED `gsb_setParticleReg` w1 @ 0x00113CF0 <- ntsc src/GsBase:gsb_ResetGSSystem (6 syms rebound)
- PORTED `gsb_setSemitransReg` w1 @ 0x00113C08 <- ntsc src/GsBase:gsb_InitGSSystem (6 syms rebound)
- PORTED `gsb_setSpecularReg` w1 @ 0x00113C78 <- ntsc src/GsBase:gsb_UpdateGSSystem (6 syms rebound)

### src/Light
- PORTED `light_InitLight` w2 @ 0x00118E18 <- ntsc src/Light:func_00117750 (4 syms rebound)
- PORTED `light_KillAllAmbient` w1 @ 0x00118E90 <- ntsc src/Light:func_001177C8 (3 syms rebound)
- PORTED `light_ResetLight` w2 @ 0x00118E28 <- ntsc src/Light:func_00117760 (1 syms rebound)

### src/Matrix
- PORTED `_AddVector` w1 @ 0x00119B28 <- ntsc src/Matrix:_ApplyCurrentMatrix (1 syms rebound)
- PORTED `_AddVectorXYZ` w1 @ 0x00119B40 <- ntsc src/Matrix:_RotTransPersCurrentMatrix (1 syms rebound)
- PORTED `_ApplyCurrentMatrix` w1 @ 0x00119988 <- ntsc src/Matrix:_ClearTransCurrentMatrix (1 syms rebound)
- PORTED `_ApplyMatrix` w1 @ 0x00119E00 <- ntsc src/MicroCode:func_00118648 (1 syms rebound)
- PORTED `_ClearTransCurrentMatrix` w1 @ 0x001195A8 <- ntsc src/Light:func_00117CE0 (1 syms rebound)
- PORTED `_CopyIVector` w2 @ 0x00119C28 <- ntsc src/MicroCode:mc_Reset (1 syms rebound)
- PORTED `_CopyMatrix` w1 @ 0x00119D60 <- ntsc src/MicroCode:func_001185A8 (1 syms rebound)
- PORTED `_CopyVector` w2 @ 0x00119C18 <- ntsc src/MicroCode:mc_TransMicroCode (1 syms rebound)
- PORTED `_FTOI0Vector` w1 @ 0x00119C00 <- ntsc src/MicroCode:mc_SetMicroCode (1 syms rebound)
- PORTED `_FTOI4Vector` w1 @ 0x00119BE8 <- ntsc src/MicroCode:mc_setBaseOffset (1 syms rebound)
- PORTED `_GetCurrentMatrix` w1 @ 0x00119888 <- ntsc src/Matrix:_UnitCurrentMatrix (1 syms rebound)
- PORTED `_GetCurrentMatrixTrans` w1 @ 0x001198A0 <- ntsc src/Matrix:_PushCurrentMatrix (1 syms rebound)
- PORTED `_GetLength` w1 @ 0x00119CC8 <- ntsc src/MicroCode:func_00118510 (1 syms rebound)
- PORTED `_GetLengthXY` w1 @ 0x00119D00 <- ntsc src/MicroCode:func_00118548 (1 syms rebound)
- PORTED `_GetLengthXZ` w1 @ 0x00119D30 <- ntsc src/MicroCode:func_00118578 (1 syms rebound)
- PORTED `_GetNorm` w1 @ 0x00119C98 <- ntsc src/MicroCode:func_001184E0 (1 syms rebound)
- PORTED `_GetRandom` w1 @ 0x0011A230 <- ntsc src/Packet:pac_DispQW (1 syms rebound)
- PORTED `_GetRandomVector` w1 @ 0x0011A248 <- ntsc src/Packet:pac_DumpPac (1 syms rebound)
- PORTED `_GetRandomVector0` w1 @ 0x0011A268 <- ntsc src/Packet:pac_makeBoundingBox (1 syms rebound)
- PORTED `_InitCurrentMatrix` w2 @ 0x00119508 <- ntsc src/Light:func_00117C40 (1 syms rebound)
- PORTED `_InitRandom` w1 @ 0x0011A210 <- ntsc src/MicroCode:func_00118A48 (1 syms rebound)
- PORTED `_InnerProduct` w1 @ 0x00119AD8 <- ntsc src/Matrix:_MulCurrentMatrixR (1 syms rebound)
- PORTED `_InterVector` w1 @ 0x00119C48 <- ntsc src/MicroCode:func_00118490 (1 syms rebound)
- PORTED `_InterVectorXYZ` w1 @ 0x00119C70 <- ntsc src/MicroCode:func_001184B8 (1 syms rebound)
- PORTED `_InverseCurrentMatrix` w1 @ 0x00119A58 <- ntsc src/Matrix:_ScaleCurrentMatrix (1 syms rebound)
- PORTED `_MakeLightColorMatrix` w1 @ 0x0011A1D8 <- ntsc src/MicroCode:func_00118A10 (1 syms rebound)
- PORTED `_MulCurrentMatrixL` w1 @ 0x00119930 <- ntsc src/Matrix:_SetTransCurrentMatrix (1 syms rebound)
- PORTED `_MulCurrentMatrixR` w1 @ 0x001198C8 <- ntsc src/Matrix:_TransCurrentMatrix (1 syms rebound)
- PORTED `_MulMatrix` w1 @ 0x00119D88 <- ntsc src/MicroCode:func_001185D0 (1 syms rebound)
- PORTED `_NormalizeVector` w1 @ 0x00119AA8 <- ntsc src/Matrix:_SetCurrentMatrix (1 syms rebound)
- PORTED `_OuterProduct` w1 @ 0x00119B08 <- ntsc src/Matrix:_MulCurrentMatrixL (1 syms rebound)
- PORTED `_PopCurrentMatrix` w1 @ 0x00119560 <- ntsc src/Light:func_00117C98 (1 syms rebound)
- PORTED `_PushCurrentMatrix` w1 @ 0x00119548 <- ntsc src/Light:func_00117C80 (1 syms rebound)
- PORTED `_RotCurrentMatrixY` w1 @ 0x00119678 <- ntsc src/Matrix:_RemakeNormal (3 syms rebound)
- PORTED `_RotCurrentMatrixZ` w1 @ 0x00119738 <- ntsc src/Matrix:_Sqrt (3 syms rebound)
- PORTED `_RotTransCurrentMatrix` w1 @ 0x0011A280 <- ntsc src/Packet:pac_error (1 syms rebound)
- PORTED `_RotTransPersCurrentMatrix` w1 @ 0x001199A8 <- ntsc src/Matrix:_RotCurrentMatrixX (1 syms rebound)
- PORTED `_ScaleCurrentMatrix` w1 @ 0x001197F8 <- ntsc src/Matrix:_InitCurrentMatrix (1 syms rebound)
- PORTED `_ScaleVector` w1 @ 0x00119B88 <- ntsc src/Matrix:_InverseCurrentMatrix (1 syms rebound)
- PORTED `_ScaleVector2XYZ` w1 @ 0x00119BC8 <- ntsc src/Matrix:_PopVu0Registers (1 syms rebound)
- PORTED `_ScaleVectorXYZ` w1 @ 0x00119BA8 <- ntsc src/Matrix:_PushVu0Registers (1 syms rebound)
- PORTED `_SetCurrentMatrix` w1 @ 0x001198B0 <- ntsc src/Matrix:_PopCurrentMatrix (1 syms rebound)
- PORTED `_SetTransCurrentMatrix` w1 @ 0x00119598 <- ntsc src/Light:func_00117CD0 (1 syms rebound)
- PORTED `_Sqrt` w1 @ 0x001194E8 <- ntsc src/Light:func_00117C20 (1 syms rebound)
- PORTED `_SubVector` w1 @ 0x00119B58 <- ntsc src/Matrix:_TransposeCurrentMatrix (1 syms rebound)
- PORTED `_SubVectorXYZ` w1 @ 0x00119B70 <- ntsc src/Matrix:_TransposeRotationCurrentMatrix (1 syms rebound)
- PORTED `_TransCurrentMatrix` w1 @ 0x00119578 <- ntsc src/Light:func_00117CB0 (1 syms rebound)
- PORTED `_TransposeCurrentMatrix` w1 @ 0x001199D8 <- ntsc src/Matrix:_RotCurrentMatrixY (1 syms rebound)
- PORTED `_TransposeMatrix` w1 @ 0x00119E80 <- ntsc src/MicroCode:func_001186C8 (1 syms rebound)
- PORTED `_TransposeRotationCurrentMatrix` w1 @ 0x00119A28 <- ntsc src/Matrix:_RotCurrentMatrixZ (1 syms rebound)
- PORTED `_UnitCurrentMatrix` w2 @ 0x00119528 <- ntsc src/Light:func_00117C60 (1 syms rebound)
- PORTED `_UnitMatrix` w1 @ 0x00119E30 <- ntsc src/MicroCode:func_00118678 (1 syms rebound)
- PORTED `_UnitRotation` w1 @ 0x00119E58 <- ntsc src/MicroCode:func_001186A0 (1 syms rebound)
- PORTED `_UnitVector` w1 @ 0x00119C38 <- ntsc src/MicroCode:mc_Init (1 syms rebound)

### src/MicroCode
- REVERTED `mc_Init` w2 @ 0x0011A760 — [codegen] tu-size: TU .text 0x4BC != PAL span 0x4C0 (trailing pad word / extra code)
- PORTED `mc_Reset` w2 @ 0x0011A720 <- ntsc src/Packet:pac_openDmaTag (3 syms rebound)
- PORTED `mc_TransMicroCode` w1 @ 0x0011A650 <- ntsc src/Packet:pac_makeClusterStrip (8 syms rebound)

### src/PObj
- PORTED `FreePObj` w1 @ 0x0025B558 <- ntsc src/cod/vendor_2418A0:func_00241A00 (3 syms rebound)
- REVERTED `InitPObj` w3 @ 0x0025B3F8 — [codegen] insn 11: expected `jal	0 <InitPObj>` built `jal	428 <AllocPObj>`

### src/Packet
- SKIPPED `pac_DispQW` w2 @ 0x0011A7A0 — jtbl
- PORTED `pac_DispVu1Memory` w1 @ 0x0011D788 <- ntsc src/Primitive:prim_SetFan2D (2 syms rebound)
- PORTED `pac_Dump` w1 @ 0x0011D728 <- ntsc src/Packet:func_0011BF60 (2 syms rebound)
- PORTED `pac_Init` w2 @ 0x0011D780 <- ntsc src/Primitive:prim_InitFan2D (2 syms rebound)
- REVERTED `pac_MakePacket` w3 @ 0x0011D708 — [codegen] insn 0: expected `lw	v0,2132(a0)` built `lw	v0,2080(a0)`
- REVERTED `pac_openDmaTag` w1 @ 0x0011BA00 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `pac_setVifCode` w1 @ 0x0011BA70 — [codegen] insn 1: expected `daddu	t0,a0,zero` built `lui	v1,0x6c00`
- PORTED `pac_setVifEndCode` w1 @ 0x0011BAB8 <- ntsc src/Packet:pac_makeMaterialTableLine (3 syms rebound)

### src/Primitive
- PORTED `prim_DeleteParticle` w1 @ 0x0011F6A8 <- ntsc src/Primitive:prim_DispWireYCylinder (2 syms rebound)
- PORTED `prim_InitParticle` w1 @ 0x0011FED0 <- ntsc src/RegistPacket:func_0011E708 (3 syms rebound)

### src/RegistPacket
- PORTED `func_00121428` w1 @ 0x00121428 <- ntsc src/RegistPacket:reg_dispSObj (8 syms rebound)
- PORTED `reg_DispObj2` w2 @ 0x00124440 <- ntsc src/Shadow:func_00122C40 (2 syms rebound)
- PORTED `reg_GetShinePri` w1 @ 0x00124488 <- ntsc src/Shadow:shadow_SetLength (1 syms rebound)
- PORTED `reg_Init` w2 @ 0x00124480 <- ntsc src/Shadow:shadow_DispCancel (2 syms rebound)
- PORTED `reg_SetScissorSw` w2 @ 0x00124448 <- ntsc src/Shadow:func_00122C48 (2 syms rebound)
- PORTED `reg_TransTexturePacket` w1 @ 0x00124450 <- ntsc src/Shadow:shadow_KillShadow (3 syms rebound)
- PORTED `reg_chooseMicroCode` w1 @ 0x001205F8 <- ntsc src/RegistPacket:func_0011EE30 (2 syms rebound)
- PORTED `reg_chooseReflectionMicroCode` w1 @ 0x00120638 <- ntsc src/RegistPacket:reg_setNMatrixPacket (2 syms rebound)
- PORTED `reg_chooseSpecularMicroCode` w1 @ 0x00120620 <- ntsc src/RegistPacket:func_0011EE58 (2 syms rebound)
- PORTED `reg_resetDissolve` w1 @ 0x00121730 <- ntsc src/RegistPacket:reg_dispLine (5 syms rebound)
- PORTED `reg_transMaterialPacket` w1 @ 0x001214D8 <- ntsc src/RegistPacket:reg_dispCObj (3 syms rebound)
- REVERTED `reg_transMicroCode` w3 @ 0x001205C0 — [codegen] insn 0: expected `lw	v0,2132(a0)` built `lw	v0,2080(a0)`

### src/Shadow
- PORTED `__GetCameraPos` w1 @ 0x00125F40 <- ntsc src/StageAnimation:stage_ApplyData (9 syms rebound)
- REVERTED `shadow_DispCancel` w3 @ 0x00129DF8 — [codegen] insn 18: expected `lw	a1,2132(v0)` built `lw	a1,2080(v0)`
- REVERTED `shadow_Init` w3 @ 0x00129ED0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `shadow_KillShadow` w2 @ 0x00129DF0 <- ntsc src/StageAnimation:stage_CalcAnimationNoParent (2 syms rebound)
- PORTED `shadow_Render` w1 @ 0x00125758 <- ntsc src/Shadow:func_00123C00 (3 syms rebound)
- REVERTED `shadow_SetLength` w3 @ 0x00129EA0 — [codegen] insn 4: expected `lw	v0,2132(a0)` built `lw	v0,2080(a0)`
- REVERTED `shadow_getShadowVectorAverage` w3 @ 0x00125778 — [codegen] insn 1: expected `addiu	a1,a1,2144` built `addiu	a1,a1,2096`

### src/StageAnimation
- REVERTED `stage_CheckAnimationFinish` w3 @ 0x0012C4A0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `stage_CheckAnimationFrameIn` w2 @ 0x0012C860 — [codegen] tu-size: TU .text 0x299C != PAL span 0x29A0 (trailing pad word / extra code)
- REVERTED `stage_ContinueAnimation` w3 @ 0x0012B080 — [codegen] insn 28: expected `beq	zero,zero,f0 <stage_ContinueAnimation+0xf0>` built `beq	zero,zero,121c <stage_ContinueAnimation+0xec>`
- PORTED `stage_KillPlayBgAnimation` w1 @ 0x0012BEE0 <- ntsc src/StageAnimation:stage_KillPlayBgAnimationIfOverMaxCount (3 syms rebound)
- PORTED `stage_KillPlayBgAnimationIfOverMaxCount` w1 @ 0x0012C808 <- ntsc src/Texture:tex_loadImage (2 syms rebound)
- PORTED `stage_ResetAnimation` w1 @ 0x0012B188 <- ntsc src/StageAnimation:stage_SetCameraForceOff (4 syms rebound)
- PORTED `stage_SetCameraForceOff` w2 @ 0x0012C498 <- ntsc src/StageAnimation:func_0012AA78 (2 syms rebound)
- PORTED `stage_SetFrameStep` w1 @ 0x0012C648 <- ntsc src/StageAnimation:func_0012AC28 (3 syms rebound)
- PORTED `stage_SetLocalizeGeometry` w1 @ 0x0012C760 <- ntsc src/Texture:tex_AllocVramAuto (5 syms rebound)
- PORTED `stage_SetLoopFlag` w1 @ 0x0012C600 <- ntsc src/StageAnimation:func_0012ABE0 (3 syms rebound)

### src/StageManager
- PORTED `CheckPoint` w1 @ 0x001A8E70 <- ntsc src/backStage:backStageProcessMain (5 syms rebound)
- PORTED `exit_stage` w1 @ 0x001A8590 <- ntsc src/StageManager:stage_initialize (8 syms rebound)
- PORTED `stgmgrForceSwitchWithFade` w1 @ 0x001A8DC8 <- ntsc src/StageManager:StageManager (2 syms rebound)
- PORTED `stgmgrNextStagePreLoadDiskNotReady` w2 @ 0x001A8EC0 <- ntsc src/backStage:routeSetPos (4 syms rebound)
- PORTED `stgmgrNextStagePreLoadDistBoyMode` w2 @ 0x001A8E58 <- ntsc src/StageManager:stgmgrForceSwitchWithFadeColor (3 syms rebound)
- REVERTED `stgmgrNextStagePreLoadEntry` w1 @ 0x001A8960 — [codegen] insn 53: expected `addiu	a1,a1,0` built `addiu	a1,a1,904`
- PORTED `stgmgrNextStagePreLoadForceNoCancel` w2 @ 0x001A8E68 <- ntsc src/backStage:backStageProcessOutStage (2 syms rebound)
- PORTED `stgmgrNextStagePreLoadForceStageSet` w1 @ 0x001A8E40 <- ntsc src/StageManager:stgmgrForceSwitchWithFade (4 syms rebound)

### src/Texture
- PORTED `tex_GetTWTH` w1 @ 0x001319C8 <- ntsc src/ZFog:fog_FogTool (1 syms rebound)
- PORTED `tex_GetTexExtData` w2 @ 0x00131B48 <- ntsc src/ZFog:func_0012FE60 (2 syms rebound)
- PORTED `tex_GetTextureData` w2 @ 0x00131AF0 <- ntsc src/ZFog:func_0012FE08 (2 syms rebound)
- PORTED `tex_GetTextureName` w2 @ 0x00131B08 <- ntsc src/ZFog:func_0012FE20 (2 syms rebound)
- PORTED `tex_GetTextureNum` w2 @ 0x00131E88 <- ntsc src/ZFog:func_0012FFE8 (2 syms rebound)
- PORTED `tex_GetVramFreeAddress` w1 @ 0x00131B60 <- ntsc src/ZFog:func_0012FE78 (2 syms rebound)
- PORTED `tex_InitTexture` w2 @ 0x00131A18 <- ntsc src/ZFog:func_0012FD30 (2 syms rebound)
- PORTED `tex_LoadTexture` w2 @ 0x00131A38 <- ntsc src/ZFog:func_0012FD50 (2 syms rebound)
- PORTED `tex_RemakeRegistersSampleMin` w1 @ 0x00132078 <- ntsc ios/cdvd:iosCdvdMgrSearchFile (4 syms rebound)
- PORTED `tex_SetSamplingType` w1 @ 0x00131B20 <- ntsc src/ZFog:func_0012FE38 (1 syms rebound)
- PORTED `tex_transRegister` w1 @ 0x0012D608 <- ntsc src/Texture:tex_setRegisters (3 syms rebound)

### src/a_p_1
- REVERTED `AP1DL` w3 @ 0x001C4308 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `AP1JumpReq` w3 @ 0x001C44C8 — [codegen] insn 6: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `AP1MotReq` w3 @ 0x001C4488 — [codegen] insn 3: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `AP1Turn` w3 @ 0x001C43B8 — [codegen] insn 7: expected `lw	v0,2096(v1)` built `lw	v0,2048(v1)`
- REVERTED `GetAP1Mode` w3 @ 0x001C4598 — [codegen] insn 2: expected `lw	v0,2096(a1)` built `lw	v0,2048(a1)`
- REVERTED `GetAP1SpecType` w3 @ 0x001C4398 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `SetAP1VisualState` w3 @ 0x001C43A8 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `attackMotInit` w3 @ 0x001C4658 — [codegen] insn 11: expected `lw	s0,2096(v0)` built `lw	s0,2048(v0)`
- REVERTED `resetPositionInfo` w3 @ 0x001C40B8 — [codegen] insn 7: expected `lw	s1,2096(v0)` built `lw	s1,2048(v0)`
- REVERTED `rollingMot` w3 @ 0x001C4610 — [codegen] insn 4: expected `jal	0 <rollingMot>` built `jal	f18 <rolling>`
- REVERTED `standMot` w3 @ 0x001C45C0 — [codegen] insn 5: expected `jal	0 <standMot>` built `jal	790 <fitToCol>`
- PORTED `yAxisRotFitting` w2 @ 0x001C2AD0 <- ntsc src/a_p_1:zAxisRotFitting (12 syms rebound)
- PORTED `zAxisRotFitting` w2 @ 0x001C2BB8 <- ntsc src/a_p_1:fitToCol (12 syms rebound)

### src/access
- PORTED `GetDataFileName` w1 @ 0x00257218 <- ntsc ito/mpeg/mv_disp:endDisplay (4 syms rebound)

### src/act
- REVERTED `ActSetStartBrainStatus` w3 @ 0x002148D8 — [codegen] insn 2: expected `sw	a1,1096(v0)` built `sw	a1,1080(v0)`
- PORTED `ConvertStickToAbsCoord` w2 @ 0x00214860 <- ntsc src/act2:BeforeFunc2 (4 syms rebound)
- PORTED `_ACTRun` w1 @ 0x00214738 <- ntsc src/act:_ACTRun (1 syms rebound)
- PORTED `_ACTWait` w1 @ 0x00214780 <- ntsc src/act:_ACTWait (2 syms rebound)
- PORTED `actChangeActMain` w1 @ 0x00212A38 <- ntsc src/act:actChangeActMain (7 syms rebound)
- PORTED `actCreateMotionThread` w1 @ 0x00212B00 <- ntsc src/act:actCreateMotionThread (6 syms rebound)
- PORTED `actCreateSubThreadGOppArg` w1 @ 0x00214820 <- ntsc src/act:actCreateSubThreadGOppArg (2 syms rebound)
- PORTED `actInitialize_geo` w2 @ 0x002146E8 <- ntsc src/act:actInitialize_geo (0 syms rebound)
- PORTED `actSetInterrupt` w1 @ 0x00214858 <- ntsc src/act:actSetInterrupt (0 syms rebound)

### src/act-env
- REVERTED `CheckWallAttributeEdegWall` w1 @ 0x002113E8 — [codegen] tu-size: TU .text 0x4F74 != PAL span 0x4F78 (trailing pad word / extra code)
- PORTED `GetCollisCenterPositionSimple` w1 @ 0x00211340 <- ntsc src/act-env:func_002009F0 (4 syms rebound)
- REVERTED `GetSofaPosition` w3 @ 0x002112C0 — [codegen] insn 10: expected `lwc1	$f0,1200(v1)` built `lwc1	$f0,1184(v1)`

### src/act-game
- REVERTED `ACTCharctrl_Lock` w3 @ 0x0014CE48 — [codegen] insn 1: expected `lui	v1,0xfffe` built `addiu	v1,zero,-2049`
- REVERTED `ACTCharctrl_Unlock` w3 @ 0x0014CE90 — [codegen] insn 2: expected `dsll32	v1,v1,0x1` built `dsll	v1,v1,0x1c`
- PORTED `ACTCheckCollis_CI` w1 @ 0x0014D510 <- ntsc src/act-game:ACTGame_StageChangeGObjID (4 syms rebound)
- PORTED `ACTCheckCollis_W` w1 @ 0x0014D3E0 <- ntsc src/act-game:ACTGame_CheckHandMotion (5 syms rebound)
- PORTED `ACTGameCollisionOff` w1 @ 0x0014CA20 <- ntsc src/act-game:ACTParaStatus_Exec (1 syms rebound)
- PORTED `ACTGameCollisionOn` w1 @ 0x0014C9F8 <- ntsc src/act-game:ACTParaStatus_Clear (1 syms rebound)
- PORTED `ACTGameViewSimple_Check` w1 @ 0x0014DB48 <- ntsc src/act-game:ACTCharctrl_Lock (2 syms rebound)
- PORTED `ACTGameView_Check` w1 @ 0x0014DB00 <- ntsc src/act-game:ACTGameView_Init (2 syms rebound)
- PORTED `ACTGameView_Init` w1 @ 0x0014CE30 <- ntsc src/act-game:hand_able_connect (2 syms rebound)
- REVERTED `ACTGame_CheckHandMotion` w3 @ 0x0014CA78 — [codegen] insn 1: expected `addiu	a3,zero,404` built `addiu	a3,zero,400`
- REVERTED `ACTGame_CheckItemMotion` w3 @ 0x0014CA48 — [codegen] insn 2: expected `addiu	a0,zero,404` built `addiu	a0,zero,400`
- REVERTED `ACTGame_ConnectHand` w3 @ 0x0014CEB8 — [codegen] insn 5: expected `addiu	a2,zero,5` built `addiu	a2,zero,4`
- REVERTED `ACTGame_DeleteActorInformation` w1 @ 0x00146D10 — [codegen] insn 3: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `ACTGame_DisconnectHand` w3 @ 0x0014CF30 — [codegen] insn 5: expected `addiu	a2,zero,5` built `addiu	a2,zero,4`
- PORTED `ACTGame_DisconnectHand_WithMail` w2 @ 0x00147218 <- ntsc sound/soundManager:func_00144E30 (4 syms rebound)
- PORTED `ACTGame_GetMotOrientFromWeapon` w1 @ 0x0014DB90 <- ntsc src/act-game:ACTCharctrl_Unlock (3 syms rebound)
- PORTED `ACTGame_GetNearestGObj` w1 @ 0x0014DC48 <- ntsc src/act-game:PAIR_GetPosition_BOY (6 syms rebound)
- REVERTED `ACTGame_LwsEffectInit` w3 @ 0x0014E118 — [codegen] insn 8: expected `lw	a0,1664(v1)` built `lw	a0,1648(v1)`
- REVERTED `ACTGame_LwsEffectProcess` w3 @ 0x001476E8 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `ACTGame_NoWeapon` w3 @ 0x0014DBD8 — [codegen] insn 4: expected `lw	a0,336(v0)` built `lw	a0,320(v0)`
- REVERTED `ACTGame_SetMotionPlaySpeedRatio_Clear` w3 @ 0x0014E770 — [codegen] insn 3: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `ACTGame_SetMotionPlaySpeedRatio_Reserve` w3 @ 0x0014DEC0 — [codegen] insn 1: expected `lw	v1,1664(v1)` built `lw	v1,1648(v1)`
- PORTED `ACTGame_StageChangeGObjDirect` w1 @ 0x0014CB48 <- ntsc src/act-game:ACTGame_BeforeFunc (5 syms rebound) — unblocked by the PAL phase-1 `lit4 src/act-game` carve
- PORTED `ACTGame_StageChangeGObjID` w1 @ 0x0014CAC8 <- ntsc src/act-game:ACTGame_InnerVelocityUpdate (4 syms rebound)
- REVERTED `ACTGame_TryConnectHand` w3 @ 0x001471D8 — [codegen] insn 3: expected `addiu	a2,zero,5` built `addiu	a2,zero,4`
- REVERTED `ACTGame_TryDisconnectHand` w3 @ 0x001471F8 — [codegen] insn 2: expected `addiu	a2,zero,5` built `addiu	a2,zero,4`
- REVERTED `ACTGame_isHangChain` w3 @ 0x0014D248 — [codegen] insn 3: expected `lw	a0,52(a1)` built `lw	a0,48(a1)`
- PORTED `ACTGame_isWeaponCombustible` w1 @ 0x0014DC20 <- ntsc src/act-game:ACTGame_DisconnectHand (2 syms rebound)
- PORTED `ACTGame_isWeaponEnableCatchfire` w1 @ 0x0014D290 <- ntsc src/act-game:ACTGameCollisionOff (3 syms rebound)
- REVERTED `ACTItemForceDrop` w3 @ 0x0014E300 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `ACTLookTarget_Init` w3 @ 0x0014DCE0 — [codegen] insn 1: expected `sw	zero,172(v0)` built `sw	zero,156(v0)`
- REVERTED `ACTParaStatus_Clear` w3 @ 0x00147A20 — [codegen] insn 2: expected `j	0 <ACTParaStatus_Clear>` built `j	70a8 <_ACTParaStatus_Set>`
- REVERTED `GetGirlPositionAtThisStage` w1 @ 0x0014E860 — [codegen] tu-size: TU .text 0x7B8C != PAL span 0x7B90 (trailing pad word / extra code)
- PORTED `GetSkeltonPosition` w1 @ 0x0014CC80 <- ntsc src/act-game:ActOrientTest (2 syms rebound)
- REVERTED `PAIR_GetPosition_BOY` w3 @ 0x0014CFB8 — [codegen] insn 2: expected `lwc1	$f0,1280(v0)` built `lwc1	$f0,1264(v0)`
- REVERTED `PAIR_GetPosition_BOY_DITCH` w3 @ 0x0014D150 — [codegen] insn 2: expected `lwc1	$f0,1296(v0)` built `lwc1	$f0,1280(v0)`
- REVERTED `PAIR_IsStatus_BOY_PULL` w3 @ 0x0014CFF8 — [codegen] insn 2: expected `lw	v1,52(v1)` built `lw	v1,48(v1)`
- REVERTED `PAIR_IsStatus_BOY_WAIT` w3 @ 0x0014D0F0 — [codegen] insn 2: expected `addiu	v1,zero,78` built `addiu	v1,zero,75`
- PORTED `SetDirectRootPositionWithNodePointLimit` w1 @ 0x0014CCF8 <- ntsc src/act-game:GetGirlHandlinkClInfo (8 syms rebound)
- PORTED `_ACTCharStatus_Exec` w2 @ 0x0014DEA8 <- ntsc src/act-parallel-control:func_0014B318 (1 syms rebound)
- PORTED `_ACTCharStatus_Init` w1 @ 0x0014DDF8 <- ntsc src/act-parallel-control:ActPara_DebugOut (1 syms rebound)
- PORTED `_ACTGame_GetParamF` w1 @ 0x0014DEE8 <- ntsc src/act-parallel-control:func_0014B358 (2 syms rebound)
- REVERTED `_ACTLookTarget_Set` w3 @ 0x0014DCF8 — [codegen] insn 4: expected `sw	zero,172(v1)` built `sw	zero,156(v1)`
- REVERTED `_ACTParaStatus_Check` w3 @ 0x0014DDE0 — [codegen] insn 1: expected `ld	v0,144(v1)` built `lw	v0,144(v1)`
- REVERTED `_ACTSetEnemyDisappearSpeed` w3 @ 0x0014DEB0 — [codegen] insn 1: expected `lw	v1,1672(v0)` built `lw	v1,1656(v0)`
- CARVES `src/act-game` — 1 US carve entry to translate:
    - - [0x530AEC, .lit4, src/act-game]      # carved D_00630AEC/AF0/AF4 (22500f, pi, 25000000f), VMA 0x630AEC..0x630AF8

### src/act-parallel-control
- PORTED `ActPara_DebugOut` w2 @ 0x0014EA60 <- ntsc src/boyact:findChainInJump (1 syms rebound)
- PORTED `ActPara_GetDefTbl` w2 @ 0x0014EA38 <- ntsc src/act-wish:func_0014BDC8 (2 syms rebound)
- REVERTED `ActPara_InitSystem` w3 @ 0x0014E9F8 — [codegen] insn 4: expected `addiu	a0,zero,85` built `addiu	a0,zero,70`
- PORTED `ActPara_StatusToFlag` w1 @ 0x0014EA48 <- ntsc src/act-wish:func_0014BDD8 (1 syms rebound)

### src/act2
- PORTED `actDummy` w2 @ 0x00214B08 <- ntsc src/act2:func_00203EE8 (3 syms rebound)

### src/act_a_p_1
- REVERTED `GetAP1AIMode` w3 @ 0x001C56E0 — [unresolved-symbol] unresolved-symbol: insn 11 `D_004BEF60`: pal symbol D_00645A30 (0x00645A30) undefined
- PORTED `IsActCharDead` w1 @ 0x001C56A0 <- ntsc src/actressLight:func_001BB7E0 (1 syms rebound)
- REVERTED `SetAP1HostGObj` w3 @ 0x001C56C0 — [codegen] insn 2: expected `sw	a1,168(v0)` built `sw	a1,152(v0)`
- REVERTED `SetAP1PriorLevel` w3 @ 0x001C56D0 — [codegen] insn 2: expected `sw	a1,172(v0)` built `sw	a1,156(v0)`
- PORTED `attackAI` w2 @ 0x001C5748 <- ntsc src/attackCheckBoundary:AttackCheckBoundaryManagerGeo (2 syms rebound)
- PORTED `func_001C5250` w1 @ 0x001C5250 <- ntsc src/actressLight:func_001BB390 (2 syms rebound)
- REVERTED `hehehe` w3 @ 0x001C4CD0 — [codegen] insn 3: expected `lw	v0,52(a1)` built `lw	v0,48(a1)`
- PORTED `jumpAI` w2 @ 0x001C5720 <- ntsc src/attackCheckBoundary:InitAttackCheckBoundaryManagerGeo (2 syms rebound)
- PORTED `subAP1Control` w2 @ 0x001C5770 <- ntsc src/attackCheckBoundary:AttackCheckBoundaryManagerDL (1 syms rebound)

### src/act_bird
- PORTED `BirdAI` w2 @ 0x001A00E8 <- ntsc src/act_bird:Debug_StickControl (1 syms rebound)
- PORTED `_ACTSendMailToBirdAll` w1 @ 0x001A00F0 <- ntsc src/act_bird:BirdGeo (4 syms rebound)
- PORTED `func_0019FE30` w2 @ 0x0019FE30 <- ntsc src/poly-flat:func_00197078 (2 syms rebound)
- REVERTED `func_0019FE38` w3 @ 0x0019FE38 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `vector_angle_degree` w1 @ 0x0019FEA0 <- ntsc src/act_bird:trans_bird (5 syms rebound) — unblocked by the PAL phase-1 `lit4 src/act_bird` carve
- CARVES `src/act_bird` — 1 US carve entry to translate:
    - - [0x531038, .lit4, src/act_bird]    # carved D_00631038 (6.2831855f, trans_bird), VMA 0x631038..0x63103C

### src/actressLight
- REVERTED `SetActressLight` w1 @ 0x001C5780 — [codegen] tu-size: TU .text 0xC4 != PAL span 0xC8 (trailing pad word / extra code)

### src/attackCheckBoundary
- REVERTED `AttackCheckBoundaryDL` w3 @ 0x001C5D78 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `AttackCheckBoundaryGeo` w1 @ 0x001C5D50 <- ntsc src/attackCheckBoundary:GetAttackCheckBoundaryManagerStatus (1 syms rebound)
- PORTED `AttackCheckBoundaryManagerDL` w2 @ 0x001C5CF8 <- ntsc src/attackCheckBoundary:GetAttackCheckBoundaryRadius (1 syms rebound)
- REVERTED `AttackCheckBoundaryManagerGeo` w3 @ 0x001C5C88 — [codegen] insn 1: expected `lw	t1,2096(v1)` built `lw	t1,2048(v1)`
- REVERTED `GetAttackCheckBoundaryManagerStatus` w3 @ 0x001C5F38 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `GetAttackCheckBoundaryRadius` w3 @ 0x001C5E80 — [codegen] insn 1: expected `lw	v1,2160(v0)` built `lw	v1,2112(v0)`
- PORTED `InitAttackCheckBoundaryGeo` w1 @ 0x001C5D00 <- ntsc src/attackCheckBoundary:CreateAttackCheckBoundary (4 syms rebound)
- REVERTED `SetAttackCheckBoundaryAttribute` w3 @ 0x001C5F48 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- PORTED `actAttackCheckBoundaryStart` w1 @ 0x001C5E28 <- ntsc src/attackCheckBoundary:switchReleaseSE (4 syms rebound)

### src/attackhit
- PORTED `BoyAttackCenter` w2 @ 0x001893A0 <- ntsc src/attackhit:func_00181BC0 (1 syms rebound)
- REVERTED `CommonAttackCenter` w3 @ 0x001893A8 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PORTED `EnemyAttackCenter` w2 @ 0x00189398 <- ntsc src/attackhit:func_00181BB8 (1 syms rebound)

### src/backStage
- PORTED `backStageDebugTimeZero` w2 @ 0x001A9E50 <- ntsc src/charFileManager:InitCharFileManager (2 syms rebound)
- PORTED `backStageLoad` w2 @ 0x001A9D90 <- ntsc src/backStage:backStageTsuresariReturn (11 syms rebound)
- PORTED `backStageProcessInit` w1 @ 0x001A9E38 <- ntsc src/backStage:func_001A1008 (5 syms rebound)
- PORTED `backStageSave` w2 @ 0x001A9CE8 <- ntsc src/backStage:backStageDebugTimeZero (11 syms rebound)
- PORTED `backStageTsuresariReturn` w2 @ 0x001A9E58 <- ntsc src/charFileManager:ResetCharFileManager (1 syms rebound)

### src/box
- PORTED `BoxExtGeoRestore` w2 @ 0x001CA8C8 <- ntsc src/switch:SetSwitchState (1 syms rebound)
- PORTED `BoxMemoryFunc` w2 @ 0x001CA8D0 <- ntsc src/switch:SetFloorLeverWithNodePoint (1 syms rebound)
- REVERTED `BoxRideFunc` w3 @ 0x001CB250 — [codegen] insn 7: expected `lw	s0,2096(a2)` built `lw	s0,2048(a2)`
- REVERTED `CanFloorLeverPull` w3 @ 0x001CAA40 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `CanHoldBox` w3 @ 0x001CA648 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `CanWallLeverPull` w3 @ 0x001CAC70 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `ExecBoxMoveEndReaction` w3 @ 0x001CA798 — [codegen] insn 6: expected `lw	s1,2096(v0)` built `lw	s1,2048(v0)`
- REVERTED `ExecBoxMoveStartReaction` w3 @ 0x001CA730 — [codegen] insn 4: expected `lw	s0,2096(v0)` built `lw	s0,2048(v0)`
- PORTED `GetBoxGlobalHoldPoint` w1 @ 0x001CA6D8 <- ntsc src/box:ExecBoxMoveStartReaction (3 syms rebound)
- REVERTED `GetBoxMode` w3 @ 0x001CA638 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `GetFloorLeverAngle` w3 @ 0x001CAB68 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `GetWallLeverAngle` w3 @ 0x001CADE0 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `InitFloorLeverGeo` w3 @ 0x001CAA58 — [codegen] insn 44: expected `lw	v0,2116(v1)` built `lw	v0,2068(v1)`
- PORTED `InitSwitchGeo` w2 @ 0x001CA8D8 <- ntsc src/switch:CanFloorLeverPull (1 syms rebound)
- REVERTED `IsThisBoxTruck` w3 @ 0x001CA720 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `IsWallLeverStatus` w3 @ 0x001CAC88 — [codegen] insn 1: expected `lw	v1,2096(v1)` built `lw	v1,2048(v1)`
- REVERTED `SetFloorLeverWithNodePoint` w3 @ 0x001CA948 — [codegen] insn 13: expected `lw	s4,2096(v0)` built `lw	s4,2048(v0)`
- REVERTED `SetSwitchState` w3 @ 0x001CA900 — [codegen] insn 6: expected `lw	s0,2096(v0)` built `lw	s0,2048(v0)`
- REVERTED `SetSwitchTriggerFunc` w3 @ 0x001CA8F0 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- PORTED `SwitchDL` w2 @ 0x001CA8E8 <- ntsc src/switch:GetFloorLeverAngle (1 syms rebound)
- PORTED `SwitchGeo` w2 @ 0x001CA8E0 <- ntsc src/switch:InitFloorLeverGeo (1 syms rebound)
- PORTED `fallDownStartSE` w1 @ 0x001C6858 <- ntsc src/attackCheckBoundary:func_001BC9A8 (2 syms rebound)
- REVERTED `initLanding` w3 @ 0x001C8E08 — [codegen] src/box.c:66: storage size of `v2' isn't known
- PORTED `landingSE` w1 @ 0x001C6850 <- ntsc src/attackCheckBoundary:func_001BC9A0 (2 syms rebound)
- PORTED `pullStartSE` w1 @ 0x001C6868 <- ntsc src/attackCheckBoundary:func_001BC9B8 (2 syms rebound)
- PORTED `pushStartSE` w1 @ 0x001C6860 <- ntsc src/attackCheckBoundary:func_001BC9B0 (2 syms rebound)
- REVERTED `switchOnSE` w3 @ 0x001C5F58 — [codegen] insn 1: expected `addiu	a1,zero,63` built `addiu	a1,zero,61`
- REVERTED `switchReleaseSE` w3 @ 0x001C5F60 — [codegen] insn 1: expected `addiu	a1,zero,64` built `addiu	a1,zero,62`
- PORTED `wallHitSE` w1 @ 0x001C6870 <- ntsc src/attackCheckBoundary:func_001BC9C0 (2 syms rebound)

### src/boy
- REVERTED `SetBoyStonizedVisual` w3 @ 0x001CC6F8 — [codegen] insn 7: expected `lw	s1,2096(v0)` built `lw	s1,2048(v0)`
- REVERTED `dispClothes` w3 @ 0x001CB2E0 — [codegen] insn 6: expected `lw	s0,2096(v0)` built `lw	s0,2048(v0)`

### src/boyact
- PORTED `ACTSearchEnemy` w1 @ 0x00157EE8 <- ntsc src/boyact:actBoyBelift (8 syms rebound)
- PORTED `ACTSearchGObj` w1 @ 0x001587A0 <- ntsc src/boyact:actBoyBeslam (8 syms rebound)
- PORTED `CorrectStickInfo` w1 @ 0x001577D0 <- ntsc src/boyact:actBoyRun (3 syms rebound)
- REVERTED `GetBoyRootPositionForCamera` w3 @ 0x00158B38 — [codegen] insn 12: expected `addiu	s3,s0,272` built `addiu	s3,s0,256`
- PORTED `GetEfStageCameraTargetID` w1 @ 0x00158528 <- ntsc src/boyact:actBoyCall (2 syms rebound)
- REVERTED `GetSaveSofaLayoutID` w3 @ 0x00158360 — [codegen] insn 7: expected `lw	a0,52(a1)` built `lw	a0,48(a1)`
- PORTED `GetbufpCharacterPacket` w2 @ 0x00158578 <- ntsc src/boyact:func_001547A0 (2 syms rebound)
- REVERTED `GetsizeCharacterPacket` w3 @ 0x00158588 — [codegen] insn 1: expected `addiu	v0,zero,32` built `addiu	v0,zero,24`
- PORTED `IsGirlEscortedInCurrentStage` w2 @ 0x00158358 <- ntsc src/boyact:actBoyStand (2 syms rebound)
- PORTED `IsGirlEscortedInNextStage` w1 @ 0x00158340 <- ntsc src/boyact:GetBoyWeaponGObj (2 syms rebound)
- PORTED `OnGirlEscortFlag` w1 @ 0x001583B0 <- ntsc src/boyact:func_00154648 (2 syms rebound)
- PORTED `PrivInsCamChk_Control` w2 @ 0x00158568 <- ntsc src/boyact:actBoyItem (2 syms rebound)
- REVERTED `ReadCharacterPacket` w3 @ 0x001586D8 — [codegen] insn 10: expected `lbu	a1,28(a2)` built `lbu	a1,20(a2)`
- PORTED `afterBoyHangG3M` w2 @ 0x00158AB0 <- ntsc src/boyact:actBoySupportGBLoop (1 syms rebound)
- PORTED `afterBoySwim` w1 @ 0x00158908 <- ntsc src/boyact:actBoyRescueSrc (5 syms rebound)
- PORTED `func_00158AE0` w2 @ 0x00158AE0 <- ntsc src/boyact:actBoySupportGBEnd (2 syms rebound)
- REVERTED `func_00158B00` w1 @ 0x00158B00 — [undeclared] src/boyact.c:203: `D_006AAAE0u' undeclared (first use in this function)

### src/brain
- REVERTED `brainAddLevel` w1 @ 0x0018A370 — [callee-sig-conflict] src/brain.c:73: conflicting types for `brainAddLevel'
- REVERTED `brainAddLevelGirl` w1 @ 0x00189738 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x20 (out-of-line helper or extra code)
- PORTED `brainCheckView` w1 @ 0x0018A448 <- ntsc src/camera-editor:DebugDispBox (2 syms rebound)
- PORTED `brainGetLevel` w1 @ 0x00189F50 <- ntsc src/brain:brainStatusDefaultSet (1 syms rebound)
- PORTED `brainInitGirlSet` w1 @ 0x0018A050 <- ntsc src/brain:brainGetTarget (3 syms rebound)
- PORTED `brainLockGirl` w2 @ 0x0018A350 <- ntsc src/camera-editor:EnterMenu (2 syms rebound)
- PORTED `brainSetLevel` w1 @ 0x0018A3C0 <- ntsc src/camera-editor:gif_test (2 syms rebound)
- PORTED `brainSetSpMode` w2 @ 0x0018A340 <- ntsc src/brain:brainInitGirlSet (2 syms rebound)
- PORTED `brainStatusDel` w2 @ 0x00189F48 <- ntsc src/brain:OverrideBrainStatusByGObj (1 syms rebound)
- PORTED `brainUnlockGirl` w1 @ 0x0018A360 <- ntsc src/camera-editor:saveEditedDataBinary (2 syms rebound)

### src/cage
- REVERTED `CageDL` w3 @ 0x001CD380 — [codegen] insn 5: expected `lw	s0,2096(v0)` built `lw	s0,2048(v0)`
- REVERTED `CageRideFunc` w3 @ 0x001CC740 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- REVERTED `GetCageChainPoint` w3 @ 0x001CD3B0 — [codegen] insn 8: expected `lw	s0,2096(v0)` built `lw	s0,2048(v0)`
- REVERTED `HotInitCageGeo` w3 @ 0x001CCCE8 — [codegen] insn 10: expected `lw	s0,2096(v0)` built `lw	s0,2048(v0)`
- REVERTED `SetCageChainHangableFlag` w3 @ 0x001CD498 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `SetCageFixGeometry` w3 @ 0x001CC878 — [codegen] insn 6: expected `lw	s0,2096(v1)` built `lw	s0,2048(v1)`
- REVERTED `SetCageVelocityFriction` w3 @ 0x001CD440 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `StabilizeAllLayoutedCage` w3 @ 0x001CD450 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/cageFix
- PORTED `CageFixDL` w2 @ 0x001CD528 <- ntsc src/candle:InitCandleGeo (3 syms rebound)
- REVERTED `CageFixGeo` w3 @ 0x001CD4A8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `InitCageFixGeo` w2 @ 0x001CD570 <- ntsc src/candle:CandleDL (1 syms rebound)

### src/camera-editor
- PORTED `CameraEdit_BOX` w1 @ 0x0018F0E8 <- ntsc src/camera-ico2:CameraMove (2 syms rebound)
- PORTED `CameraEdit_BOX_NUMBER` w1 @ 0x0018F050 <- ntsc src/camera-ico2:initMonitorCamera (2 syms rebound)
- PORTED `CameraEdit_DispBox` w2 @ 0x0018EA58 <- ntsc src/camera-editor:CameraEdit_Reflect (2 syms rebound)
- PORTED `CameraEdit_DispBoxType2` w2 @ 0x0018CDB8 <- ntsc src/camera-editor:wakeup_cameraedit (2 syms rebound)
- PORTED `CameraEdit_DispPinType2` w1 @ 0x0018BFF8 <- ntsc src/camera-editor:menuGroupSelect (2 syms rebound)
- PORTED `CameraEdit_Enter` w2 @ 0x0018F978 <- ntsc src/camera-ico2:GetCameraGroupFromPosition (1 syms rebound)
- PORTED `CameraEdit_PIN` w1 @ 0x0018F100 <- ntsc src/camera-ico2:ReflectCameraSetBinary (2 syms rebound)
- PORTED `CameraEdit_PIN_NUMBER` w1 @ 0x0018F060 <- ntsc src/camera-ico2:monitorMonitorCamera (2 syms rebound)
- PORTED `CameraEdit_PIN_NUMBER_ALL` w1 @ 0x0018F0A8 <- ntsc src/camera-ico2:ChaseCamera (1 syms rebound)
- PORTED `CameraEdit_Reflect` w1 @ 0x0018EA60 <- ntsc src/camera-editor:CameraEdit_Save (3 syms rebound)
- PORTED `CameraEdit_Save` w1 @ 0x0018EA70 <- ntsc src/camera-editor:debug_NMarker (3 syms rebound)
- PORTED `CameraEdit_del_box` w1 @ 0x0018E9D8 <- ntsc src/camera-editor:CameraEdit_del_pin (4 syms rebound)
- PORTED `CameraEdit_del_pin` w1 @ 0x0018EA10 <- ntsc src/camera-editor:CameraEdit_DispBox (4 syms rebound)
- PORTED `CameraEdit_reflect_box` w1 @ 0x0018EDE0 <- ntsc src/camera-ico2:ico2camera_GetTargetPos (5 syms rebound)
- PORTED `CameraEdit_reflect_pin` w2 @ 0x0018EF38 <- ntsc src/camera-ico2:ico2camera_GetGroupNearest (3 syms rebound)
- PORTED `CameraEdit_reset_box` w1 @ 0x0018EB70 <- ntsc src/camera-ico2:CameraSetCameraSet_Default (5 syms rebound)
- PORTED `CameraEdit_reset_pin` w2 @ 0x0018ECC8 <- ntsc src/camera-ico2:GetRootPositionForCamera (3 syms rebound)
- PORTED `ConvertCameraSetBuffer` w1 @ 0x0018F2A8 <- ntsc src/camera-ico2:GetTargetOffset (8 syms rebound)
- REVERTED `EnterMenu` w1 @ 0x0018A478 — [codegen] insn 45: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `InitCameraEditor` w1 @ 0x0018EB08 <- ntsc src/camera-editor:debug_CameraEditor (3 syms rebound)
- PORTED `StickToTrans` w1 @ 0x0018F418 <- ntsc src/camera-ico2:SetCameraMatrix_Ico2 (8 syms rebound)
- PORTED `_CameraEdit_PIN` w1 @ 0x0018F680 <- ntsc src/camera-ico2:SetCameraZoomOffsetRatio (1 syms rebound)
- PORTED `_CameraEdit_add_box` w1 @ 0x0018F6A8 <- ntsc src/camera-ico2:GetCameraGroupCurrent (3 syms rebound)
- PORTED `_CameraEdit_add_pin` w1 @ 0x0018F820 <- ntsc src/camera-ico2:GetCameraGroupFromGObj (3 syms rebound)
- PORTED `debug_Arrow` w2 @ 0x0018EB00 <- ntsc src/camera-editor:InitCameraEditor (1 syms rebound)
- PORTED `debug_CameraEditor` w1 @ 0x0018EB18 <- ntsc src/camera-ico2:CameraSetCameraSet (8 syms rebound)
- PORTED `debug_Marker` w2 @ 0x0018EAF8 <- ntsc src/camera-editor:debug_Arrow (1 syms rebound)
- PORTED `debug_NMarker` w1 @ 0x0018EA80 <- ntsc src/camera-editor:debug_Marker (3 syms rebound)
- PORTED `gif_test` w1 @ 0x0018A970 <- ntsc src/camera-editor:dispCameraPinType2 (2 syms rebound)
- REVERTED `test_camedit` w1 @ 0x0018E150 — [codegen] insn 2: expected `addiu	a0,a0,0` built `addiu	a0,a0,10568`

### src/camera-ico2
- REVERTED `AddPluralCameraSet` w3 @ 0x00192D10 — [codegen] insn 15: expected `addiu	a1,zero,2045` built `addiu	a1,zero,1984`
- REVERTED `CameraSetCameraSet` w1 @ 0x0018F980 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x68 (out-of-line helper or extra code)
- PORTED `CameraSetCameraSet_Default` w1 @ 0x0018F9E8 <- ntsc src/camera-ico2:InitPluralCameraSet (4 syms rebound)
- PORTED `ChaseCamera` w1 @ 0x00190780 <- ntsc src/camera-ico2:func_00188C98 (13 syms rebound)
- PORTED `GetCameraGroupCurrent` w2 @ 0x00192B68 <- ntsc src/camera-ico2:func_0018B0A0 (2 syms rebound)
- PORTED `GetCameraGroupFromGObj` w1 @ 0x00192B70 <- ntsc src/camera-ico2:func_0018B0A8 (5 syms rebound)
- PORTED `GetCameraGroupFromPosition` w1 @ 0x00192C48 <- ntsc src/camera-ico2:func_0018B180 (4 syms rebound)
- REVERTED `GetPluralCameraSet` w3 @ 0x00192DC8 — [codegen] insn 27: expected `addiu	a1,zero,2036` built `addiu	a1,zero,1975`
- PORTED `GetRootPositionForCamera` w1 @ 0x0018FA08 <- ntsc src/camera-ico2:GetPluralCameraSet (4 syms rebound)
- PORTED `GetSizeOfCameraSetBinary` w1 @ 0x001930E8 <- ntsc src/camera-ico2:func_0018B620 (1 syms rebound)
- PORTED `InitPluralCameraSet` w2 @ 0x00192DC0 <- ntsc src/camera-ico2:func_0018B2F8 (2 syms rebound)
- REVERTED `SetCameraTargetPosition` w1 @ 0x00193130 — [codegen] tu-size: TU .text 0x3844 != PAL span 0x3848 (trailing pad word / extra code)
- PORTED `SetCameraZoomOffsetRatio` w2 @ 0x00192B60 <- ntsc src/camera-ico2:func_0018B098 (2 syms rebound)
- PORTED `ico2camera_GetGroupNearest` w1 @ 0x0018FCA8 <- ntsc src/camera-ico2:GetSizeOfCameraSetBinary (5 syms rebound)
- PORTED `ico2camera_GetTargetPos` w1 @ 0x0018FA28 <- ntsc src/camera-ico2:MakeCameraSetBinary (10 syms rebound)
- PORTED `initMonitorCamera` w1 @ 0x0018FE28 <- ntsc src/camera-ico2:SetCameraTargetPosition (3 syms rebound)

### src/camera-root
- PORTED `BackToGameCamera` w1 @ 0x00193AB0 <- ntsc src/camera-root:CameraEditManual (13 syms rebound)
- PORTED `Camctrl_ExitEveRock` w1 @ 0x00194870 <- ntsc src/camera-root:GetCameraInfomationFromGlobalPosition (3 syms rebound)
- PORTED `Camctrl_SetTarget` w1 @ 0x001948A0 <- ntsc src/camera-root:InitCamera (2 syms rebound)
- PORTED `CameraChangeTargetParallel` w1 @ 0x00194918 <- ntsc src/camera-root:Camctrl_SetTarget (6 syms rebound)
- PORTED `CameraGetMode` w2 @ 0x00194A08 <- ntsc src/camera-set-manager:func_0018CC10 (2 syms rebound)
- PORTED `CameraGetTarget` w2 @ 0x001949D8 <- ntsc src/camera-root:GetCameraDefaultTargetGObj (2 syms rebound)
- PORTED `CameraGetTargets` w1 @ 0x001949E0 <- ntsc src/camera-set-manager:InitCameraSetManager (3 syms rebound)
- PORTED `CameraSetMode` w1 @ 0x001949F8 <- ntsc src/camera-set-manager:func_0018CC00 (3 syms rebound)
- PORTED `CameraSetTargetGObj` w2 @ 0x00194908 <- ntsc src/camera-root:Camctrl_ExitEveRock (3 syms rebound)
- PORTED `CameraSetTargetPos` w2 @ 0x00194ED0 <- ntsc src/camera-set-manager:func_0018CF58 (1 syms rebound)
- PORTED `DebugCameraManual` w1 @ 0x001939B8 <- ntsc src/camera-root:ConvertCameraSet (4 syms rebound)
- PORTED `DebugCameraSemiAuto` w1 @ 0x001939F0 <- ntsc src/camera-root:MakeCameraMatrix (9 syms rebound)
- PORTED `GetCameraDefaultTargetGObj` w1 @ 0x001948D0 <- ntsc src/camera-root:SetCameraMatrix (4 syms rebound)
- PORTED `GetCameraInfo_tmp` w1 @ 0x00194EF8 <- ntsc src/chain:StartPendulum (3 syms rebound)
- PORTED `GetCameraInfomationFromGlobalPosition` w1 @ 0x00193BB8 <- ntsc src/camera-root:DebugCameraManual (4 syms rebound)
- PORTED `GetCameraPos` w3 @ 0x00194ED8 <- ntsc src/chain:UpdateRootPosition (3 syms rebound)
- PORTED `GetCurrentCameraSet2` w2 @ 0x00194DA8 <- ntsc src/camera-set-manager:func_0018CEC0 (2 syms rebound)
- PORTED `InsertCamera_isEnable` w1 @ 0x00194E68 <- ntsc src/camera-set-manager:func_0018CEF0 (2 syms rebound)
- PORTED `SetCameraFlag_GamecamCutBack` w2 @ 0x00194DC8 <- ntsc src/camera-set-manager:func_0018CEE0 (2 syms rebound)
- PORTED `SetCameraFlag_LwsCutBack` w2 @ 0x00194DB8 <- ntsc src/camera-set-manager:func_0018CED0 (2 syms rebound)
- REVERTED `SetMonitorCameraInitializeFlag` w2 @ 0x00194F58 — [codegen] tu-size: TU .text 0x1D9C != PAL span 0x1DA0 (trailing pad word / extra code)
- REVERTED `SetWSMatrix` w1 @ 0x001931C8 — [codegen] insn 6: expected `jal	0 <SetWSMatrix>` built `jal	38 <ConvertCameraSet>`
- PORTED `testcamerazoom` w2 @ 0x00194F48 <- ntsc src/chain:collisionCheck (2 syms rebound)

### src/camera-set-manager
- PORTED `InitCameraSetManager` w2 @ 0x00194F68 <- ntsc src/chain:chain_simulate_term_loop (2 syms rebound)

### src/candle
- PORTED `CandleDL` w2 @ 0x001CD7F8 <- ntsc src/candle:DeleteLayoutedCandleParticleEffect (3 syms rebound)

### src/chain
- REVERTED `chain_simulate_term` w1 @ 0x00195F68 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

### src/chandelier
- PORTED `ChandelierDL` w2 @ 0x001CDA40 <- ntsc src/chandelier:InitChandelierGeo (3 syms rebound)
- PORTED `ChandelierGeo` w1 @ 0x001CD9A8 <- ntsc src/chandelier:ChandelierDL (6 syms rebound)
- PORTED `InitChandelierGeo` w2 @ 0x001CDA88 <- ntsc src/chandelier:func_001C34B8 (1 syms rebound)

### src/charFileManager
- REVERTED `GetPObjAddress` w1 @ 0x001ABC20 — [codegen] tu-size: TU .text 0x1DDC != PAL span 0x1DE0 (trailing pad word / extra code)
- REVERTED `InitCharFileManager` w3 @ 0x001A9E60 — [codegen] insn 1: expected `dli	v1,0x9978` built `dli	v1,0x9450`
- REVERTED `ReadCamerasetFile` w3 @ 0x001AB4D8 — [codegen] insn 16: expected `addiu	a3,zero,820` built `addiu	a3,zero,807`
- REVERTED `ReadEndCheckFile` w3 @ 0x001AB5A8 — [codegen] insn 1: expected `addiu	a3,zero,854` built `addiu	a3,zero,841`
- REVERTED `ReadParticleEffectFile` w3 @ 0x001AAFA0 — [codegen] insn 11: expected `addiu	a3,zero,552` built `addiu	a3,zero,539`
- REVERTED `ReadStageAnimationFile` w3 @ 0x001AAC50 — [codegen] insn 22: expected `addiu	a1,zero,487` built `addiu	a1,zero,474`
- REVERTED `ResetCharFileManager` w3 @ 0x001A9EE0 — [codegen] insn 1: expected `dli	v1,0x9978` built `dli	v1,0x9450`

### src/clipCollisionManager
- REVERTED `CreateClipCollisionManagerGObj` w2 @ 0x001CDCB0 — [codegen] insn 4: expected `addiu	t0,t0,0` built `addiu	t0,t0,672`

### src/clothAnimation
- PORTED `DeleteChainExtendedWeight` w1 @ 0x001D3CA0 <- ntsc src/clothAnimation:getCloth4D_postProcess (1 syms rebound)
- PORTED `DispClothMesh` w1 @ 0x001D0EE8 <- ntsc src/clothAnimation:GetChainAnimation (13 syms rebound)
- PORTED `FSqrtInv` w1 @ 0x001D3F68 <- ntsc src/clothAnimation:InitChainVelocity (1 syms rebound)
- REVERTED `GetChainExWeightGlobalPos` w1 @ 0x001CDF40 — [codegen] insn 5: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `GetChainNodeGlobalQuaternion` w1 @ 0x001D3AD8 <- ntsc src/clothAnimation:getCloth4D_preProcess (6 syms rebound)
- PORTED `GetChainNodeID` w1 @ 0x001D3CC8 <- ntsc src/clothAnimation:GetCloth4D (1 syms rebound)
- PORTED `MoveChainExtendedWeight` w1 @ 0x001D3B80 <- ntsc src/clothAnimation:proc (1 syms rebound)
- PORTED `ResetClothAnimation` w1 @ 0x001D3CE0 <- ntsc src/clothAnimation:InitCloth4D (3 syms rebound)
- REVERTED `__main` — unresolved-symbol: D_0071EB68 has no PAL definition (post-hoc, bisected)
- PORTED `checkOverThePlane` w1 @ 0x001D41F8 <- ntsc src/clothTest:func_001C9078 (1 syms rebound)
- REVERTED `func_00265AE4` — asm-block .align 3 inserted a pad word the ROM lacks (func is 4-mod-8 aligned); superseded by the vma-aware .align (post-hoc, bisected)
- PORTED `getXZInvLength` w1 @ 0x001D3FB0 <- ntsc src/clothAnimation:GetChainNodeID (1 syms rebound)
- PORTED `getXZLength` w1 @ 0x001D3F88 <- ntsc src/clothAnimation:DeleteChainExtendedWeight (1 syms rebound)
- PORTED `getXZLengthSquare` w1 @ 0x001D3FD8 <- ntsc src/clothTest:InitClothTestGeo (1 syms rebound)
- PORTED `scaleAndAddVectorXYZ` w1 @ 0x001D4030 <- ntsc src/clothTest:ClothTestDL (1 syms rebound)
- PORTED `scaleVectorXZ` w1 @ 0x001D4058 <- ntsc src/clothTest:func_001C8ED8 (1 syms rebound)
- PORTED `subAndGetInvLength` w1 @ 0x001D3FF8 <- ntsc src/clothTest:ClothTestGeo (1 syms rebound)
- PORTED `tensionMoveNoReduce` w1 @ 0x001D4078 <- ntsc src/clothTest:func_001C8EF8 (1 syms rebound)

### src/clothTest
- PORTED `ClothTestDL` w2 @ 0x001D44B0 <- ntsc src/clothTest:func_001C9330 (1 syms rebound)
- PORTED `ClothTestGeo` w2 @ 0x001D44A8 <- ntsc src/clothTest:func_001C9328 (1 syms rebound)

### src/cod/vendor_100110
- PORTED `DisableDmac` w2 @ 0x00100AD8 <- ntsc src/cod/vendor_100110:func_00100AD8 (4 syms rebound)
- PORTED `DisableIntc` w2 @ 0x00100A08 <- ntsc src/cod/vendor_100110:func_00100A08 (4 syms rebound)
- PORTED `EIntr` w1 @ 0x00101A88 <- ntsc src/cod/vendor_100C90:func_00101A88 (1 syms rebound)
- PORTED `EnableDmac` w2 @ 0x00100B40 <- ntsc src/cod/vendor_100110:func_00100B40 (4 syms rebound)
- PORTED `EnableIntc` w2 @ 0x00100A70 <- ntsc src/cod/vendor_100110:func_00100A70 (4 syms rebound)
- PORTED `InitSysCall` w1 @ 0x001009A0 <- ntsc src/cod/vendor_100110:func_001009A0 (2 syms rebound)
- PORTED `_DisableDmac` w1 @ 0x00100290 <- ntsc src/cod/vendor_100110:func_00100290 (1 syms rebound)
- PORTED `_DisableIntc` w1 @ 0x00100270 <- ntsc src/cod/vendor_100110:func_00100270 (1 syms rebound)
- PORTED `_EnableDmac` w1 @ 0x00100280 <- ntsc src/cod/vendor_100110:func_00100280 (1 syms rebound)
- REVERTED `_EnableIntc` w1 @ 0x00100260 — [unresolved-symbol] unresolved-symbol: func_00100110, func_00100120, func_00100130, func_00100140, func_00100150, func_00100160, func_00100170, func_00100180, func_00100190, func_001001A0, func_001001B0, func_001001C0, func_001001D0, func_001001E0, func_001001F0, func_00100200, func_00100210, func_00100220, func_00100230, func_00100240, func_00100250 undefined on the PAL side (unrebindable raw-constant reference)
- PORTED `_InitSys` w1 @ 0x001009E0 <- ntsc src/cod/vendor_100110:func_001009E0 (4 syms rebound)
- PORTED `iDisableDmac` w2 @ 0x00100C08 <- ntsc src/cod/vendor_100110:func_00100C08 (2 syms rebound)
- PORTED `iDisableIntc` w2 @ 0x00100BC8 <- ntsc src/cod/vendor_100110:func_00100BC8 (2 syms rebound)
- PORTED `iEnableDmac` w2 @ 0x00100BE8 <- ntsc src/cod/vendor_100110:func_00100BE8 (2 syms rebound)
- PORTED `iEnableIntc` w2 @ 0x00100BA8 <- ntsc src/cod/vendor_100110:func_00100BA8 (2 syms rebound)
- PORTED `iRotateThreadReadyQueue` w1 @ 0x00100FB0 <- ntsc src/cod/vendor_100C90:func_00100FB0 (5 syms rebound)
- PORTED `iSuspendThread` w1 @ 0x00101030 <- ntsc src/cod/vendor_100C90:func_00101030 (6 syms rebound)
- PORTED `iWakeupThread` w1 @ 0x00100F18 <- ntsc src/cod/vendor_100C90:func_00100F18 (6 syms rebound)
- REVERTED `kCopy` w1 @ 0x00100C48 — [unresolved-symbol] unresolved-symbol: func_00100C38 undefined on the PAL side (unrebindable raw-constant reference)
- PORTED `kprintf` w1 @ 0x001019A8 <- ntsc src/cod/vendor_100C90:func_001019A8 (2 syms rebound)
- PORTED `kputchar` w1 @ 0x001010C8 <- ntsc src/cod/vendor_100C90:func_001010C8 (1 syms rebound)
- PORTED `kputs` w1 @ 0x00101C58 <- ntsc src/cod/vendor_100C90:func_00101C58 (2 syms rebound)
- PORTED `sceDeci2Close` w1 @ 0x00101AE8 <- ntsc src/cod/vendor_100C90:func_00101AE8 (2 syms rebound)
- PORTED `sceDeci2ExLock` w1 @ 0x00101C08 <- ntsc src/cod/vendor_100C90:func_00101C08 (2 syms rebound)
- PORTED `sceDeci2ExRecv` w1 @ 0x00101B68 <- ntsc src/cod/vendor_100C90:func_00101B68 (2 syms rebound)
- PORTED `sceDeci2ExReqSend` w1 @ 0x00101BD8 <- ntsc src/cod/vendor_100C90:func_00101BD8 (2 syms rebound)
- PORTED `sceDeci2ExSend` w1 @ 0x00101BA0 <- ntsc src/cod/vendor_100C90:func_00101BA0 (2 syms rebound)
- PORTED `sceDeci2ExUnLock` w1 @ 0x00101C30 <- ntsc src/cod/vendor_100C90:func_00101C30 (2 syms rebound)
- PORTED `sceDeci2Poll` w1 @ 0x00101B40 <- ntsc src/cod/vendor_100C90:func_00101B40 (2 syms rebound)
- PORTED `sceDeci2ReqSend` w1 @ 0x00101B10 <- ntsc src/cod/vendor_100C90:func_00101B10 (2 syms rebound)
- PORTED `serialPutchar` w1 @ 0x001011B0 <- ntsc src/cod/vendor_100C90:func_001011B0 (2 syms rebound)
- REVERTED `setup` w2 @ 0x00100990 — [unresolved-symbol] unresolved-symbol: func_001002A0, func_001002B0, func_001002C0, func_001002D0, func_001002E0, func_001002F0, func_00100300, func_00100310, func_00100320, func_00100330, func_00100340, func_00100350, func_00100360, func_00100370, func_00100380, func_00100390, func_001003A0, func_001003B0, func_001003C0, func_001003D0, func_001003E0, func_001003F0, func_00100400, func_00100410, func_00100420, func_00100430, func_00100440, func_00100450, func_00100460, func_00100470, func_00100480, func_00100490, func_001004A0, func_001004B0, func_001004C0, func_001004D0, func_001004E0, func_001004F0, func_00100500, func_00100510, func_00100520, func_00100530, func_00100540, func_00100550, func_00100560, func_00100570, func_00100580, func_00100590, func_001005A0, func_001005B0, func_001005C0, func_001005D0, func_001005E0, func_001005F0, func_00100600, func_00100610, func_00100620, func_00100630, func_00100640, func_00100650, func_00100660, func_00100670, func_00100680, func_00100690, func_001006A0, func_001006B0, func_001006C0, func_001006D0, func_001006E0, func_001006F0, func_00100700, func_00100710, func_00100720, func_00100730, func_00100740, func_00100750, func_00100760, func_00100770, func_00100780, func_00100790, func_001007A0, func_001007B0, func_001007C0, func_001007D0, func_001007E0, func_001007F0, func_00100800, func_00100810, func_00100820, func_00100830, func_00100840, func_00100850, func_00100860, func_00100870, func_00100880, func_00100890, func_001008A0, func_001008B0, func_001008C0, func_001008D0, func_001008E0, func_001008F0, func_00100900, func_00100910, func_00100920, func_00100930, func_00100940, func_00100950, func_00100960, func_00100970, func_00100980 undefined on the PAL side (unrebindable raw-constant reference)

### src/cod/vendor_25B680
- PORTED `sceGsGetGParam` w2 @ 0x0025B790 <- ntsc src/cod/vendor_2418A0:func_00241C38 (2 syms rebound)
- PORTED `sceGsGetIMR` w2 @ 0x0025D220 <- ntsc src/cod/vendor_2418A0:func_002436C8 (2 syms rebound)
- PORTED `sceGsPutDispEnv` w1 @ 0x0025BA78 <- ntsc src/cod/vendor_2418A0:func_00241F20 (2 syms rebound)
- PORTED `sceGsPutIMR` w1 @ 0x0025D158 <- ntsc src/cod/vendor_2418A0:func_00243600 (3 syms rebound)
- PORTED `sceGsResetPath` w1 @ 0x0025B7A0 <- ntsc src/cod/vendor_2418A0:func_00241C48 (2 syms rebound)
- PORTED `sceGsSetDefAlphaEnv` w1 @ 0x0025C5C0 <- ntsc src/cod/vendor_2418A0:func_00242A68 (1 syms rebound)
- PORTED `sceGsSetHalfOffset` w1 @ 0x0025D198 <- ntsc src/cod/vendor_2418A0:func_00243640 (1 syms rebound)
- PORTED `sceGsSwapDBuff` w1 @ 0x0025C0A0 <- ntsc src/cod/vendor_2418A0:func_00242548 (3 syms rebound)

### src/cod/vendor_25D410
- PORTED `func_0025D440` w1 @ 0x0025D440 <- ntsc src/cod/vendor_2418A0:func_002438E8 (1 syms rebound)
- PORTED `func_0025D758` w1 @ 0x0025D758 <- ntsc src/cod/vendor_2418A0:func_00243C00 (2 syms rebound)
- PORTED `func_0025D7D0` w1 @ 0x0025D7D0 <- ntsc src/cod/vendor_2418A0:func_00243C78 (3 syms rebound)
- PORTED `func_0025D878` w1 @ 0x0025D878 <- ntsc src/cod/vendor_2418A0:func_00243D20 (3 syms rebound)
- PORTED `func_0025D920` w1 @ 0x0025D920 <- ntsc src/cod/vendor_2418A0:func_00243DC8 (3 syms rebound)
- PORTED `func_0025DEB0` w1 @ 0x0025DEB0 <- ntsc src/cod/vendor_2418A0:func_00244358 (1 syms rebound)
- PORTED `func_0025DF08` w1 @ 0x0025DF08 <- ntsc src/cod/vendor_2418A0:func_002443B0 (1 syms rebound)
- PORTED `func_0025E060` w1 @ 0x0025E060 <- ntsc src/cod/vendor_2418A0:func_00244508 (1 syms rebound)
- REVERTED `memclr` w1 @ 0x0025E150 — [codegen] tu-size: TU .text 0xD74 != PAL span 0xD78 (trailing pad word / extra code)
- PORTED `sceVpu0Reset` w1 @ 0x0025E0F0 <- ntsc src/cod/vendor_2418A0:func_00244598 (2 syms rebound)
- PORTED `sceVu0AddVector` w1 @ 0x0025D628 <- ntsc src/cod/vendor_2418A0:func_00243AD0 (1 syms rebound)
- PORTED `sceVu0ApplyMatrix` w1 @ 0x0025D410 <- ntsc src/cod/vendor_2418A0:func_002438B8 (1 syms rebound)
- PORTED `sceVu0CameraMatrix` w1 @ 0x0025DA40 <- ntsc src/cod/vendor_2418A0:func_00243EE8 (6 syms rebound)
- PORTED `sceVu0ClampVector` w1 @ 0x0025DA18 <- ntsc src/cod/vendor_2418A0:func_00243EC0 (1 syms rebound)
- PORTED `sceVu0ClipScreen` w1 @ 0x0025DFB8 <- ntsc src/cod/vendor_2418A0:func_00244460 (1 syms rebound)
- PORTED `sceVu0ClipScreen3` w1 @ 0x0025E000 <- ntsc src/cod/vendor_2418A0:func_002444A8 (1 syms rebound)
- PORTED `sceVu0CopyMatrix` w1 @ 0x0025D6C8 <- ntsc src/cod/vendor_2418A0:func_00243B70 (1 syms rebound)
- PORTED `sceVu0CopyVector` w1 @ 0x0025D6B8 <- ntsc src/cod/vendor_2418A0:func_00243B60 (1 syms rebound)
- PORTED `sceVu0CopyVectorXYZ` w1 @ 0x0025DF50 <- ntsc src/cod/vendor_2418A0:func_002443F8 (1 syms rebound)
- PORTED `sceVu0DivVector` w1 @ 0x0025D5C0 <- ntsc src/cod/vendor_2418A0:func_00243A68 (1 syms rebound)
- PORTED `sceVu0DivVectorXYZ` w1 @ 0x0025D5E0 <- ntsc src/cod/vendor_2418A0:func_00243A88 (1 syms rebound)
- PORTED `sceVu0FTOI0Vector` w1 @ 0x0025D700 <- ntsc src/cod/vendor_2418A0:func_00243BA8 (1 syms rebound)
- PORTED `sceVu0FTOI4Vector` w1 @ 0x0025D6F0 <- ntsc src/cod/vendor_2418A0:func_00243B98 (1 syms rebound)
- PORTED `sceVu0ITOF0Vector` w1 @ 0x0025D720 <- ntsc src/cod/vendor_2418A0:func_00243BC8 (1 syms rebound)
- PORTED `sceVu0ITOF4Vector` w1 @ 0x0025D710 <- ntsc src/cod/vendor_2418A0:func_00243BB8 (1 syms rebound)
- PORTED `sceVu0InnerProduct` w1 @ 0x0025D4A8 <- ntsc src/cod/vendor_2418A0:func_00243950 (1 syms rebound)
- PORTED `sceVu0InterVector` w1 @ 0x0025D600 <- ntsc src/cod/vendor_2418A0:func_00243AA8 (1 syms rebound)
- PORTED `sceVu0InterVectorXYZ` w1 @ 0x0025DF70 <- ntsc src/cod/vendor_2418A0:func_00244418 (1 syms rebound)
- PORTED `sceVu0InversMatrix` w1 @ 0x0025D550 <- ntsc src/cod/vendor_2418A0:func_002439F8 (1 syms rebound)
- PORTED `sceVu0LightColorMatrix` w1 @ 0x0025DBB0 <- ntsc src/cod/vendor_2418A0:func_00244058 (2 syms rebound)
- PORTED `sceVu0MulVector` w1 @ 0x0025D658 <- ntsc src/cod/vendor_2418A0:func_00243B00 (1 syms rebound)
- PORTED `sceVu0NormalLightMatrix` w1 @ 0x0025DAF0 <- ntsc src/cod/vendor_2418A0:func_00243F98 (4 syms rebound)
- PORTED `sceVu0Normalize` w1 @ 0x0025D4D0 <- ntsc src/cod/vendor_2418A0:func_00243978 (1 syms rebound)
- PORTED `sceVu0OuterProduct` w1 @ 0x0025D488 <- ntsc src/cod/vendor_2418A0:func_00243930 (1 syms rebound)
- PORTED `sceVu0RotMatrix` w1 @ 0x0025D9C8 <- ntsc src/cod/vendor_2418A0:func_00243E70 (4 syms rebound)
- PORTED `sceVu0ScaleVector` w1 @ 0x0025D670 <- ntsc src/cod/vendor_2418A0:func_00243B18 (1 syms rebound)
- PORTED `sceVu0ScaleVectorXYZ` w1 @ 0x0025DFA0 <- ntsc src/cod/vendor_2418A0:func_00244448 (1 syms rebound)
- PORTED `sceVu0SubVector` w1 @ 0x0025D640 <- ntsc src/cod/vendor_2418A0:func_00243AE8 (1 syms rebound)
- PORTED `sceVu0TransMatrix` w1 @ 0x0025D688 <- ntsc src/cod/vendor_2418A0:func_00243B30 (1 syms rebound)
- PORTED `sceVu0TransposeMatrix` w1 @ 0x0025D508 <- ntsc src/cod/vendor_2418A0:func_002439B0 (1 syms rebound)
- PORTED `sceVu0UnitMatrix` w1 @ 0x0025D730 <- ntsc src/cod/vendor_2418A0:func_00243BD8 (1 syms rebound)

### src/cod/vendor_25E188
- PORTED `sceDmaDebug` w1 @ 0x0025E290 <- ntsc src/cod/vendor_2418A0:func_00244738 (2 syms rebound)
- PORTED `sceDmaGetChan` w1 @ 0x0025E188 <- ntsc src/cod/vendor_2418A0:func_00244630 (2 syms rebound)
- REVERTED `sceDmaGetEnv` w1 @ 0x0025E478 — [undeclared] src/cod/vendor_25E188.c:28: dereferencing pointer to incomplete type
- PORTED `sceDmaPause` w2 @ 0x0025EBC0 <- ntsc src/cod/vendor_2418A0:func_00245068 (1 syms rebound)
- REVERTED `sceDmaRestart` w2 @ 0x0025EBE0 — [codegen] tu-size: TU .text 0xA74 != PAL span 0xA78 (trailing pad word / extra code)

### src/cod/vendor_25EC00
- PORTED `sceVif1PkAddGsData` w1 @ 0x0025EEF0 <- ntsc src/cod/vendor_2418A0:func_00245398 (1 syms rebound)
- PORTED `sceVif1PkCloseDirectCode` w1 @ 0x0025ED80 <- ntsc src/cod/vendor_2418A0:func_00245228 (1 syms rebound)
- REVERTED `sceVif1PkCnt` w2 @ 0x0025EC78 — [codegen] src/cod/vendor_25EC00.c:44: void value not ignored as it ought to be
- REVERTED `sceVif1PkEnd` w2 @ 0x0025ECD0 — [codegen] src/cod/vendor_25EC00.c:45: void value not ignored as it ought to be
- PORTED `sceVif1PkInit` w1 @ 0x0025EC00 <- ntsc src/cod/vendor_2418A0:func_002450A8 (1 syms rebound)
- PORTED `sceVif1PkOpenDirectCode` w1 @ 0x0025ED28 <- ntsc src/cod/vendor_2418A0:func_002451D0 (2 syms rebound)
- PORTED `sceVif1PkOpenGifTag` w1 @ 0x0025EDB0 <- ntsc src/cod/vendor_2418A0:func_00245258 (1 syms rebound)
- PORTED `sceVif1PkReset` w1 @ 0x0025EC10 <- ntsc src/cod/vendor_2418A0:func_002450B8 (1 syms rebound)
- PORTED `sceVif1PkTerminate` w1 @ 0x0025EC20 <- ntsc src/cod/vendor_2418A0:func_002450C8 (1 syms rebound)

### src/cod/vendor_25EF18
- PORTED `ExpandScratchPad` w2 @ 0x00265020 <- ntsc src/cod/vendor_24AAC8:func_0024B4C8 (1 syms rebound)
- PORTED `GetTLBEntry` w2 @ 0x00264FE0 <- ntsc src/cod/vendor_24AAC8:func_0024B488 (1 syms rebound)
- PORTED `InitTLBFunctions` w1 @ 0x00264F50 <- ntsc src/cod/vendor_24AAC8:func_0024B3F8 (3 syms rebound)
- PORTED `ProbeTLBEntry` w1 @ 0x00265000 <- ntsc src/cod/vendor_24AAC8:func_0024B4A8 (1 syms rebound)
- PORTED `PutTLBEntry` w1 @ 0x00264FA0 <- ntsc src/cod/vendor_24AAC8:func_0024B448 (1 syms rebound)
- PORTED `QueueInit` w1 @ 0x0025F250 <- ntsc src/cod/vendor_2453C0:func_002456F8 (2 syms rebound)
- PORTED `QueuePeekReadDone` w1 @ 0x0025F2B8 <- ntsc src/cod/vendor_2453C0:func_00245760 (1 syms rebound)
- PORTED `QueuePeekWriteDone` w1 @ 0x0025F278 <- ntsc src/cod/vendor_2453C0:func_00245720 (1 syms rebound)
- REVERTED `SetDebugHandler` w1 @ 0x00264EB8 — [codegen] insn 21: expected `addiu	a1,a1,0` built `addiu	a1,a1,25448`
- PORTED `SetTLBEntry` w2 @ 0x00264FC0 <- ntsc src/cod/vendor_24AAC8:func_0024B468 (1 syms rebound)
- REVERTED `SetTLBHandler` w1 @ 0x00264E58 — [codegen] insn 5: expected `addiu	s0,s0,0` built `addiu	s0,s0,24872`
- PORTED `VSync2` w1 @ 0x0025EF68 <- ntsc src/cod/vendor_2453C0:func_00245410 (2 syms rebound)
- PORTED `_DumpTLB` w1 @ 0x00264AE8 <- ntsc src/cod/vendor_24AAC8:func_0024AF90 (4 syms rebound)
- PORTED `_change_addr` w1 @ 0x002653C0 <- ntsc src/cod/vendor_24AAC8:func_0024B880 (1 syms rebound)
- PORTED `_fs_version` w2 @ 0x00260E10 <- ntsc src/cod/vendor_2453C0:func_002472B8 (5 syms rebound)
- PORTED `_lf_bind` w1 @ 0x00263EA0 <- ntsc src/cod/vendor_2453C0:func_0024A348 (8 syms rebound)
- PORTED `_lf_version` w2 @ 0x00263FA0 <- ntsc src/cod/vendor_2453C0:func_0024A448 (5 syms rebound)
- PORTED `_request_call` w1 @ 0x0025FF20 <- ntsc src/cod/vendor_2453C0:func_002463C8 (2 syms rebound)
- PORTED `_request_rdata` w1 @ 0x0025FB28 <- ntsc src/cod/vendor_2453C0:func_00245FD0 (3 syms rebound)
- PORTED `_sceFsSemInit` w1 @ 0x00260BE0 <- ntsc src/cod/vendor_2453C0:func_00247088 (3 syms rebound)
- PORTED `_sceFsSigSema` w2 @ 0x00260C60 <- ntsc src/cod/vendor_2453C0:func_00247108 (3 syms rebound)
- PORTED `_sceFsWaitS` w1 @ 0x00260C30 <- ntsc src/cod/vendor_2453C0:func_002470D8 (4 syms rebound)
- PORTED `_sceRpcFreePacket` w1 @ 0x0025F9E0 <- ntsc src/cod/vendor_2453C0:func_00245E88 (1 syms rebound)
- PORTED `_sceRpcGetFPacket` w1 @ 0x0025FA00 <- ntsc src/cod/vendor_2453C0:func_00245EA8 (1 syms rebound)
- PORTED `_sceRpcGetFPacket2` w1 @ 0x0025FA30 <- ntsc src/cod/vendor_2453C0:func_00245ED8 (2 syms rebound)
- PORTED `_sceSifCmdIntrHdlr` w1 @ 0x00265910 <- ntsc src/cod/vendor_24AAC8:func_0024BDD0 (4 syms rebound)
- PORTED `_search_svdata` w1 @ 0x0025FCE0 <- ntsc src/cod/vendor_2453C0:func_00246188 (1 syms rebound)
- PORTED `close` w2 @ 0x0025F0E8 <- ntsc src/cod/vendor_2453C0:func_00245590 (1 syms rebound)
- PORTED `fstat` w1 @ 0x0025F1B8 <- ntsc src/cod/vendor_2453C0:func_00245660 (1 syms rebound)
- PORTED `func_00260690` w1 @ 0x00260690 <- ntsc src/cod/vendor_2453C0:func_00246B38 (4 syms rebound)
- PORTED `func_002606D0` w1 @ 0x002606D0 <- ntsc src/cod/vendor_2453C0:func_00246B78 (4 syms rebound)
- PORTED `func_00264F40` w2 @ 0x00264F40 <- ntsc src/cod/vendor_24AAC8:func_0024B3E8 (1 syms rebound)
- PORTED `func_00265A38` w1 @ 0x00265A38 <- ntsc src/cod/vendor_24AAC8:func_0024BEF8 (1 syms rebound)
- PORTED `func_00265AE4` w1 @ 0x00265AE4 <- ntsc src/cod/vendor_24AAC8:func_0024BFA4 (1 syms rebound)
- PORTED `func_00265AEC` w1 @ 0x00265AEC <- ntsc src/cod/vendor_24AAC8:func_0024BFAC (2 syms rebound)
- PORTED `get_iob` w3 @ 0x002607B8 <- ntsc src/cod/vendor_2453C0:func_00246C60 (6 syms rebound)
- PORTED `getpid` w2 @ 0x0025F1D0 <- ntsc src/cod/vendor_2453C0:func_00245678 (1 syms rebound)
- PORTED `iGetTLBEntry` w1 @ 0x00264FF0 <- ntsc src/cod/vendor_24AAC8:func_0024B498 (1 syms rebound)
- PORTED `iProbeTLBEntry` w2 @ 0x00265010 <- ntsc src/cod/vendor_24AAC8:func_0024B4B8 (1 syms rebound)
- PORTED `iPutTLBEntry` w2 @ 0x00264FB0 <- ntsc src/cod/vendor_24AAC8:func_0024B458 (1 syms rebound)
- PORTED `iSetTLBEntry` w1 @ 0x00264FD0 <- ntsc src/cod/vendor_24AAC8:func_0024B478 (1 syms rebound)
- PORTED `ioctl` w2 @ 0x0025F0F0 <- ntsc src/cod/vendor_2453C0:func_00245598 (1 syms rebound)
- PORTED `isatty` w2 @ 0x0025F1B0 <- ntsc src/cod/vendor_2453C0:func_00245658 (1 syms rebound)
- PORTED `isceSifSendCmd` w1 @ 0x002658D0 <- ntsc src/cod/vendor_24AAC8:func_0024BD90 (2 syms rebound)
- PORTED `kExpandScratchPad` w1 @ 0x00264D28 <- ntsc src/cod/vendor_24AAC8:func_0024B1D0 (2 syms rebound)
- PORTED `kGetTLBEntry` w1 @ 0x00264C88 <- ntsc src/cod/vendor_24AAC8:func_0024B130 (1 syms rebound)
- PORTED `kProbeTLBEntry` w1 @ 0x00264CD8 <- ntsc src/cod/vendor_24AAC8:func_0024B180 (1 syms rebound)
- PORTED `kPutTLBEntry` w1 @ 0x00264B80 <- ntsc src/cod/vendor_24AAC8:func_0024B028 (1 syms rebound)
- PORTED `kSetTLBEntry` w1 @ 0x00264C40 <- ntsc src/cod/vendor_24AAC8:func_0024B0E8 (1 syms rebound)
- PORTED `kill` w1 @ 0x0025F1D8 <- ntsc src/cod/vendor_2453C0:func_00245680 (2 syms rebound)
- PORTED `lseek` w2 @ 0x0025F0F8 <- ntsc src/cod/vendor_2453C0:func_002455A0 (1 syms rebound)
- PORTED `new_iob` w1 @ 0x00260730 <- ntsc src/cod/vendor_2453C0:func_00246BD8 (6 syms rebound)
- PORTED `open` w2 @ 0x0025F0C0 <- ntsc src/cod/vendor_2453C0:func_00245568 (2 syms rebound)
- PORTED `sbrk` w1 @ 0x0025F100 <- ntsc src/cod/vendor_2453C0:func_002455A8 (4 syms rebound)
- PORTED `sceChdir` w1 @ 0x00262FE8 <- ntsc src/cod/vendor_2453C0:func_00249490 (2 syms rebound)
- PORTED `sceDclose` w1 @ 0x00262758 <- ntsc src/cod/vendor_2453C0:func_00248C00 (12 syms rebound)
- PORTED `sceDelDrv` w1 @ 0x00262698 <- ntsc src/cod/vendor_2453C0:func_00248B40 (2 syms rebound)
- PORTED `sceDread` w1 @ 0x002628C0 <- ntsc src/cod/vendor_2453C0:func_00248D68 (12 syms rebound)
- PORTED `sceFsReset` w1 @ 0x00260EA0 <- ntsc src/cod/vendor_2453C0:func_00247348 (4 syms rebound)
- PORTED `sceRemove` w1 @ 0x00262118 <- ntsc src/cod/vendor_2453C0:func_002485C0 (2 syms rebound)
- PORTED `sceResetttyinit` w2 @ 0x0025EF18 <- ntsc src/cod/vendor_2453C0:func_002453C0 (3 syms rebound)
- PORTED `sceRmdir` w1 @ 0x002622E8 <- ntsc src/cod/vendor_2453C0:func_00248790 (2 syms rebound)
- PORTED `sceSifAddCmdHandler` w1 @ 0x00265700 <- ntsc src/cod/vendor_24AAC8:func_0024BBC0 (3 syms rebound)
- PORTED `sceSifAllocIopHeap` w1 @ 0x00263CC8 <- ntsc src/cod/vendor_2453C0:func_0024A170 (6 syms rebound)
- REVERTED `sceSifBindRpc` w1 @ 0x0025FDE0 — [callee-sig-conflict] src/cod/vendor_25EF18.c:241: conflicting types for `_sceRpcGetPacket'
- PORTED `sceSifCheckStatRpc` w1 @ 0x002601A0 <- ntsc src/cod/vendor_2453C0:func_00246648 (1 syms rebound)
- PORTED `sceSifExitCmd` w1 @ 0x00265698 <- ntsc src/cod/vendor_24AAC8:func_0024BB58 (5 syms rebound)
- PORTED `sceSifExitRpc` w1 @ 0x0025F910 <- ntsc src/cod/vendor_2453C0:func_00245DB8 (3 syms rebound)
- PORTED `sceSifFreeIopHeap` w1 @ 0x00263D38 <- ntsc src/cod/vendor_2453C0:func_0024A1E0 (6 syms rebound)
- PORTED `sceSifGetDataTable` w2 @ 0x00265408 <- ntsc src/cod/vendor_24AAC8:func_0024B8C8 (2 syms rebound)
- PORTED `sceSifGetIopAddr` w1 @ 0x00264668 <- ntsc src/cod/vendor_24AAC8:func_0024AB10 (5 syms rebound)
- PORTED `sceSifGetNextRequest` w1 @ 0x00260470 <- ntsc src/cod/vendor_2453C0:func_00246918 (3 syms rebound)
- REVERTED `sceSifGetOtherData` w1 @ 0x0025FB88 — [callee-sig-conflict] src/cod/vendor_25EF18.c:227: conflicting types for `_sceRpcGetPacket'
- PORTED `sceSifGetSreg` w2 @ 0x002653D0 <- ntsc src/cod/vendor_24AAC8:func_0024B890 (2 syms rebound)
- PORTED `sceSifInitIopHeap` w1 @ 0x00263C40 <- ntsc src/cod/vendor_2453C0:func_0024A0E8 (5 syms rebound)
- PORTED `sceSifIsAliveIop` w1 @ 0x00264968 <- ntsc src/cod/vendor_24AAC8:func_0024AE10 (2 syms rebound)
- PORTED `sceSifLoadElf` w1 @ 0x00264640 <- ntsc src/cod/vendor_24AAC8:func_0024AAE8 (3 syms rebound)
- PORTED `sceSifLoadElfPart` w1 @ 0x00264620 <- ntsc src/cod/vendor_24AAC8:func_0024AAC8 (2 syms rebound)
- PORTED `sceSifLoadFileReset` w1 @ 0x00264030 <- ntsc src/cod/vendor_2453C0:func_0024A4D8 (4 syms rebound)
- PORTED `sceSifLoadModule` w1 @ 0x002644D8 <- ntsc src/cod/vendor_2453C0:func_0024A980 (2 syms rebound)
- PORTED `sceSifLoadModuleBuffer` w1 @ 0x00264270 <- ntsc src/cod/vendor_2453C0:func_0024A718 (2 syms rebound)
- PORTED `sceSifLoadStartModule` w1 @ 0x002644F8 <- ntsc src/cod/vendor_2453C0:func_0024A9A0 (2 syms rebound)
- PORTED `sceSifLoadStartModuleBuffer` w2 @ 0x00264290 <- ntsc src/cod/vendor_2453C0:func_0024A738 (2 syms rebound)
- PORTED `sceSifRemoveCmdHandler` w1 @ 0x00265730 <- ntsc src/cod/vendor_24AAC8:func_0024BBF0 (3 syms rebound)
- PORTED `sceSifSendCmd` w1 @ 0x00265890 <- ntsc src/cod/vendor_24AAC8:func_0024BD50 (2 syms rebound)
- PORTED `sceSifSetCmdBuffer` w1 @ 0x002656D0 <- ntsc src/cod/vendor_24AAC8:func_0024BB90 (2 syms rebound)
- PORTED `sceSifSetSreg` w1 @ 0x002653E8 <- ntsc src/cod/vendor_24AAC8:func_0024B8A8 (2 syms rebound)
- PORTED `sceSifSetSysCmdBuffer` w1 @ 0x002656E8 <- ntsc src/cod/vendor_24AAC8:func_0024BBA8 (2 syms rebound)
- PORTED `sceSifSyncIop` w1 @ 0x00264990 <- ntsc src/cod/vendor_24AAC8:func_0024AE38 (4 syms rebound)
- PORTED `sceUmount` w1 @ 0x00263410 <- ntsc src/cod/vendor_2453C0:func_002498B8 (2 syms rebound)
- PORTED `stat` w2 @ 0x0025F200 <- ntsc src/cod/vendor_2453C0:func_002456A8 (2 syms rebound)
- PORTED `unlink` w2 @ 0x0025F228 <- ntsc src/cod/vendor_2453C0:func_002456D0 (2 syms rebound)

### src/cod/vendor_265B10
- PORTED `_sceCd_Poff_Intr` w1 @ 0x00266030 <- ntsc src/cod/vendor_24AAC8:func_0024C4F0 (4 syms rebound)
- PORTED `_send_to_iop` w1 @ 0x00267AD0 <- ntsc src/cod/vendor_24AAC8:func_0024DE98 (8 syms rebound)
- PORTED `sceCdCallback` w1 @ 0x00265B78 <- ntsc src/cod/vendor_24AAC8:func_0024C038 (5 syms rebound)
- PORTED `sceCdDelayThread` w1 @ 0x00265B10 <- ntsc src/cod/vendor_24AAC8:func_0024BFD0 (6 syms rebound)
- PORTED `sceCdNcmdDiskReady` w3 @ 0x00266668 <- ntsc src/cod/vendor_24AAC8:func_0024CB28 (7 syms rebound)
- PORTED `sceCdPOffCallback` w1 @ 0x00265FC0 <- ntsc src/cod/vendor_24AAC8:func_0024C480 (7 syms rebound)
- PORTED `sceCdStInit` w1 @ 0x002675F0 <- ntsc src/cod/vendor_24AAC8:func_0024D9B8 (4 syms rebound)
- PORTED `sceCdStPause` w1 @ 0x00267878 <- ntsc src/cod/vendor_24AAC8:func_0024DC40 (7 syms rebound)
- PORTED `sceCdStResume` w1 @ 0x002678C8 <- ntsc src/cod/vendor_24AAC8:func_0024DC90 (7 syms rebound)
- PORTED `sceCdStSeek` w1 @ 0x00267688 <- ntsc src/cod/vendor_24AAC8:func_0024DA50 (3 syms rebound)
- PORTED `sceCdStSeekF` w1 @ 0x00267658 <- ntsc src/cod/vendor_24AAC8:func_0024DA20 (3 syms rebound)
- PORTED `sceCdStStart` w1 @ 0x00267620 <- ntsc src/cod/vendor_24AAC8:func_0024D9E8 (3 syms rebound)
- PORTED `sceCdStStat` w1 @ 0x00267920 <- ntsc src/cod/vendor_24AAC8:func_0024DCE8 (6 syms rebound)
- PORTED `sceCdStStop` w1 @ 0x002676B8 <- ntsc src/cod/vendor_24AAC8:func_0024DA80 (4 syms rebound)
- PORTED `sceCdSyncS` w1 @ 0x002667A0 <- ntsc src/cod/vendor_24AAC8:func_0024CC60 (7 syms rebound)

### src/cod/vendor_267C00
- PORTED `scePadEnd` w1 @ 0x00267DE0 <- ntsc src/cod/vendor_24AAC8:func_0024E1A8 (5 syms rebound)
- PORTED `scePadEnterPressMode` w1 @ 0x00268B58 <- ntsc src/cod/vendor_24E9D8:func_0024EF20 (3 syms rebound)
- PORTED `scePadExitPressMode` w1 @ 0x00268BB0 <- ntsc src/cod/vendor_24E9D8:func_0024EF78 (3 syms rebound)
- PORTED `scePadGetDmaStr` w1 @ 0x00268100 <- ntsc src/cod/vendor_24AAC8:func_0024E4C8 (3 syms rebound)
- PORTED `scePadGetFrameCount` w1 @ 0x00268160 <- ntsc src/cod/vendor_24AAC8:func_0024E528 (3 syms rebound)
- PORTED `scePadGetModVersion` w1 @ 0x00268DA8 <- ntsc src/cod/vendor_24E9D8:func_0024F170 (4 syms rebound)
- PORTED `scePadGetPortMax` w1 @ 0x00268CD8 <- ntsc src/cod/vendor_24E9D8:func_0024F0A0 (4 syms rebound)
- PORTED `scePadGetReqState` w1 @ 0x00268348 <- ntsc src/cod/vendor_24AAC8:func_0024E710 (3 syms rebound)
- PORTED `scePadGetSlotMax` w1 @ 0x00268D40 <- ntsc src/cod/vendor_24E9D8:func_0024F108 (4 syms rebound)
- PORTED `scePadGetState` w1 @ 0x00268230 <- ntsc src/cod/vendor_24AAC8:func_0024E5F8 (3 syms rebound)
- PORTED `scePadInfoMode` w1 @ 0x00268610 <- ntsc src/cod/vendor_24E9D8:func_0024E9D8 (3 syms rebound)
- PORTED `scePadInfoPressMode` w1 @ 0x00268AF8 <- ntsc src/cod/vendor_24E9D8:func_0024EEC0 (3 syms rebound)
- REVERTED `scePadInit` w1 @ 0x00267C00 — [codegen] insn 29: expected `lui	v0,0x0` built `lui	v0,0x1`
- PORTED `scePadRead` w1 @ 0x002681B0 <- ntsc src/cod/vendor_24AAC8:func_0024E578 (4 syms rebound)
- REVERTED `scePadReqIntToStr` w3 @ 0x00268398 — [unresolved-symbol] unresolved-symbol: insn 10 `D_0062EB68`: pal symbol D_00556C58 (0x00556C58) undefined
- PORTED `scePadSetActAlign` w1 @ 0x002688B8 <- ntsc src/cod/vendor_24E9D8:func_0024EC80 (5 syms rebound)
- PORTED `scePadSetButtonInfo` w1 @ 0x00268A48 <- ntsc src/cod/vendor_24E9D8:func_0024EE10 (5 syms rebound)
- PORTED `scePadSetMainMode` w1 @ 0x00268748 <- ntsc src/cod/vendor_24E9D8:func_0024EB10 (5 syms rebound)
- PORTED `scePadSetReqState` w1 @ 0x002682E0 <- ntsc src/cod/vendor_24AAC8:func_0024E6A8 (3 syms rebound)
- PORTED `scePadSetVrefParam` w1 @ 0x00268C08 <- ntsc src/cod/vendor_24E9D8:func_0024EFD0 (5 syms rebound)
- PORTED `scePadSetWarningLevel` w1 @ 0x00268E10 <- ntsc src/cod/vendor_24E9D8:func_0024F1D8 (4 syms rebound)
- REVERTED `scePadStateIntToStr` w3 @ 0x002682A8 — [unresolved-symbol] unresolved-symbol: insn 10 `D_0062EB68`: pal symbol D_00556C58 (0x00556C58) undefined

### src/cod/vendor_268E78
- PORTED `_lmcGetClientPtr` w1 @ 0x00269030 <- ntsc src/cod/vendor_24E9D8:func_0024F3F8 (5 syms rebound)
- REVERTED `mcDelayThread` w1 @ 0x00269830 — [codegen] insn 7: expected `addiu	s0,s0,0` built `addiu	s0,s0,2448`
- PORTED `mcHearAlarm` w1 @ 0x00269808 <- ntsc src/cod/vendor_24E9D8:func_0024FBD0 (2 syms rebound)
- PORTED `mceGetInfoApdx` w1 @ 0x00269958 <- ntsc src/cod/vendor_24E9D8:func_0024FD20 (4 syms rebound)
- PORTED `mceStorePwd` w1 @ 0x00269C90 <- ntsc src/cod/vendor_24E9D8:func_00250058 (4 syms rebound)
- PORTED `sceMcChangeThreadPriority` w3 @ 0x00269060 <- ntsc src/cod/vendor_24E9D8:func_0024F428 (9 syms rebound)
- REVERTED `sceMcChdir` w3 @ 0x00269D18 — [codegen] insn 58: expected `addiu	t3,t3,0` built `addiu	t3,t3,3608`
- PORTED `sceMcClose` w3 @ 0x00269348 <- ntsc src/cod/vendor_24E9D8:func_0024F710 (9 syms rebound)
- REVERTED `sceMcDelete` w3 @ 0x00269F30 — [codegen] insn 36: expected `addiu	s0,s0,0` built `addiu	s0,s0,20`
- PORTED `sceMcFlush` w3 @ 0x0026A058 <- ntsc src/cod/vendor_24E9D8:func_00250420 (9 syms rebound)
- PORTED `sceMcFormat` w3 @ 0x00269E68 <- ntsc src/cod/vendor_24E9D8:func_00250230 (9 syms rebound)
- PORTED `sceMcGetDir` w3 @ 0x00269B38 <- ntsc src/cod/vendor_24E9D8:func_0024FF00 (11 syms rebound)
- PORTED `sceMcGetEntSpace` w3 @ 0x0026A518 <- ntsc src/cod/vendor_24E9D8:func_002508E0 (10 syms rebound)
- PORTED `sceMcGetSlotMax` w3 @ 0x00269118 <- ntsc src/cod/vendor_24E9D8:func_0024F4E0 (8 syms rebound)
- PORTED `sceMcMkdir` w1 @ 0x00269310 <- ntsc src/cod/vendor_24E9D8:func_0024F6D8 (3 syms rebound)
- REVERTED `sceMcOpen` w3 @ 0x002691D8 — [codegen] insn 38: expected `addiu	s0,s0,0` built `addiu	s0,s0,20`
- REVERTED `sceMcRead` w3 @ 0x00269568 — [codegen] insn 46: expected `addiu	t3,t3,0` built `addiu	t3,t3,1632`
- REVERTED `sceMcRename` w3 @ 0x0026A2E8 — [codegen] insn 50: expected `addiu	s0,s0,0` built `addiu	s0,s0,32`
- PORTED `sceMcSeek` w3 @ 0x00269400 <- ntsc src/cod/vendor_24E9D8:func_0024F7C8 (9 syms rebound)
- PORTED `sceMcSetFileInfo` w3 @ 0x0026A110 <- ntsc src/cod/vendor_24E9D8:func_002504D8 (12 syms rebound)
- PORTED `sceMcSync` w1 @ 0x00269878 <- ntsc src/cod/vendor_24E9D8:func_0024FC40 (8 syms rebound)
- PORTED `sceMcUnformat` w3 @ 0x0026A450 <- ntsc src/cod/vendor_24E9D8:func_00250818 (9 syms rebound)

### src/cod/vendor_26A630
- PORTED `_ErrMessage` w2 @ 0x0026C188 <- ntsc src/cod/vendor_2517D0:func_00252550 (3 syms rebound)
- PORTED `_Error` w1 @ 0x0026C1C8 <- ntsc src/cod/vendor_2517D0:func_00252590 (4 syms rebound)
- PORTED `_Error1` w1 @ 0x0026C198 <- ntsc src/cod/vendor_2517D0:func_00252560 (3 syms rebound)
- PORTED `_RefImageInit` w1 @ 0x0026C2F8 <- ntsc src/cod/vendor_2517D0:func_002526C0 (1 syms rebound)
- PORTED `_alalcAlloc` w1 @ 0x0026BA88 <- ntsc src/cod/vendor_2517D0:func_00251E50 (3 syms rebound)
- PORTED `_alalcFree` w1 @ 0x0026BA78 <- ntsc src/cod/vendor_2517D0:func_00251E40 (1 syms rebound)
- PORTED `_alalcInit` w1 @ 0x0026BA50 <- ntsc src/cod/vendor_2517D0:func_00251E18 (1 syms rebound)
- PORTED `_alalcRest` w1 @ 0x0026BAF0 <- ntsc src/cod/vendor_2517D0:func_00251EB8 (1 syms rebound)
- PORTED `_alalcSetDynamic` w1 @ 0x0026BA68 <- ntsc src/cod/vendor_2517D0:func_00251E30 (1 syms rebound)
- REVERTED `_ch4dma` w1 @ 0x00271D28 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PORTED `_clearOnce` w1 @ 0x0026C070 <- ntsc src/cod/vendor_2517D0:func_00252438 (4 syms rebound)
- REVERTED `_copyAddRefImage` w1 @ 0x0026E878 — [codegen] insn 2: expected `addiu	t2,t2,0` built `addiu	t2,t2,17136`
- PORTED `_decodeOrSkip` w1 @ 0x0026BDB8 <- ntsc src/cod/vendor_2517D0:func_00252180 (4 syms rebound)
- REVERTED `_defRestartDMA` w2 @ 0x0026CBB8 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PORTED `_defStopDMA` w2 @ 0x0026CBA8 <- ntsc src/cod/vendor_2517D0:func_00252F70 (2 syms rebound)
- PORTED `_dispatchMpegCallback` w1 @ 0x0026B930 <- ntsc src/cod/vendor_2517D0:func_00251CF8 (1 syms rebound)
- PORTED `_dispatchMpegCbNodata` w1 @ 0x0026B980 <- ntsc src/cod/vendor_2517D0:func_00251D48 (2 syms rebound)
- REVERTED `_dmVector` w1 @ 0x0026EB48 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_doCSC` w1 @ 0x00271938 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_extrainfo` w1 @ 0x00270838 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PORTED `_initSeqAgain` w1 @ 0x0026BFD8 <- ntsc src/cod/vendor_2517D0:func_002523A0 (3 syms rebound)
- REVERTED `_ipuSetMPEG1` w1 @ 0x0026E938 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_isOutSizeOK` w1 @ 0x00271200 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PORTED `_lastFrame` w1 @ 0x0026BFE8 <- ntsc src/cod/vendor_2517D0:func_002523B0 (10 syms rebound)
- REVERTED `_markOutput` w1 @ 0x00271490 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_mbAddressIncrement` w1 @ 0x0026ECF0 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_motionVector` w1 @ 0x0026FA50 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_nextHeader` w1 @ 0x00270360 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_nextStartCode` w1 @ 0x00270288 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PORTED `_pack_header` w1 @ 0x0026ACC0 <- ntsc src/cod/vendor_24E9D8:func_00251088 (5 syms rebound)
- PORTED `_pictureSpatialScalableExtension` w2 @ 0x0026CB88 <- ntsc src/cod/vendor_2517D0:func_00252F50 (3 syms rebound)
- PORTED `_pictureTemporalScalableExtension` w2 @ 0x0026CB98 <- ntsc src/cod/vendor_2517D0:func_00252F60 (3 syms rebound)
- PORTED `_ri0_000` w1 @ 0x0026DBE0 <- ntsc src/cod/vendor_2517D0:func_00253FA0 (1 syms rebound)
- PORTED `_ri0_001` w1 @ 0x0026DD30 <- ntsc src/cod/vendor_2517D0:func_002540F0 (1 syms rebound)
- PORTED `_ri0_010` w1 @ 0x0026DEB0 <- ntsc src/cod/vendor_2517D0:func_00254270 (1 syms rebound)
- PORTED `_ri0_011` w1 @ 0x0026E060 <- ntsc src/cod/vendor_2517D0:func_00254420 (1 syms rebound)
- PORTED `_ri0_100` w1 @ 0x0026E208 <- ntsc src/cod/vendor_2517D0:func_002545C8 (1 syms rebound)
- PORTED `_ri0_101` w1 @ 0x0026E3A0 <- ntsc src/cod/vendor_2517D0:func_00254760 (1 syms rebound)
- PORTED `_ri0_110` w1 @ 0x0026E568 <- ntsc src/cod/vendor_2517D0:func_00254928 (1 syms rebound)
- PORTED `_ri0_111` w1 @ 0x0026E760 <- ntsc src/cod/vendor_2517D0:func_00254B20 (1 syms rebound)
- PORTED `_rix_000` w1 @ 0x0026DB68 <- ntsc src/cod/vendor_2517D0:func_00253F28 (1 syms rebound)
- PORTED `_rix_001` w1 @ 0x0026DC78 <- ntsc src/cod/vendor_2517D0:func_00254038 (1 syms rebound)
- PORTED `_rix_010` w1 @ 0x0026DE00 <- ntsc src/cod/vendor_2517D0:func_002541C0 (1 syms rebound)
- PORTED `_rix_011` w1 @ 0x0026DF68 <- ntsc src/cod/vendor_2517D0:func_00254328 (1 syms rebound)
- REVERTED `_rix_100` w1 @ 0x0026E160 — [codegen] insn 31: expected `bgtz	a3,24 <_rix_100+0x24>` built `sll	zero,zero,0x0`
- PORTED `_rix_101` w1 @ 0x0026E2B8 <- ntsc src/cod/vendor_2517D0:func_00254678 (1 syms rebound)
- PORTED `_rix_110` w1 @ 0x0026E488 <- ntsc src/cod/vendor_2517D0:func_00254848 (1 syms rebound)
- PORTED `_rix_111` w1 @ 0x0026E638 <- ntsc src/cod/vendor_2517D0:func_002549F8 (1 syms rebound)
- PORTED `_sceMpegFlush` w1 @ 0x0026BF68 <- ntsc src/cod/vendor_2517D0:func_00252330 (3 syms rebound)
- REVERTED `_sendIpuCommand` w1 @ 0x0026FB90 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PORTED `_sequenceScalableExtension` w2 @ 0x0026CB68 <- ntsc src/cod/vendor_2517D0:func_00252F30 (3 syms rebound)
- REVERTED `_sliceA0` w1 @ 0x0026EF28 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sliceB` w1 @ 0x002702F0 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitGet` w1 @ 0x00272148 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitInit` w1 @ 0x00272058 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitJump` w1 @ 0x002721E0 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitMarker` w1 @ 0x00272198 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `_sysbitPtr` w1 @ 0x00272238 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- PORTED `_system_header` w1 @ 0x0026AE10 <- ntsc src/cod/vendor_24E9D8:func_002511D8 (3 syms rebound)
- PORTED `_unknown_extension` w2 @ 0x0026CB78 <- ntsc src/cod/vendor_2517D0:func_00252F40 (3 syms rebound)
- PORTED `sceMpegAddBs` w1 @ 0x0026B6F0 <- ntsc src/cod/vendor_2517D0:func_00251AB8 (4 syms rebound)
- PORTED `sceMpegAddCallback` w1 @ 0x0026B908 <- ntsc src/cod/vendor_2517D0:func_00251CD0 (1 syms rebound)
- PORTED `sceMpegClearRefBuff` w1 @ 0x0026B8A0 <- ntsc src/cod/vendor_2517D0:func_00251C68 (7 syms rebound)
- PORTED `sceMpegDelete` w2 @ 0x0026B6E8 <- ntsc src/cod/vendor_2517D0:func_00251AB0 (1 syms rebound)
- PORTED `sceMpegDemuxPss` w1 @ 0x0026ABA8 <- ntsc src/cod/vendor_24E9D8:func_00250F70 (2 syms rebound)
- PORTED `sceMpegDispCenterOffX` w2 @ 0x0026BA08 <- ntsc src/cod/vendor_2517D0:func_00251DD0 (1 syms rebound)
- PORTED `sceMpegDispCenterOffY` w2 @ 0x0026BA18 <- ntsc src/cod/vendor_2517D0:func_00251DE0 (1 syms rebound)
- PORTED `sceMpegDispHeight` w1 @ 0x0026B9F8 <- ntsc src/cod/vendor_2517D0:func_00251DC0 (1 syms rebound)
- PORTED `sceMpegDispWidth` w1 @ 0x0026B9E8 <- ntsc src/cod/vendor_2517D0:func_00251DB0 (1 syms rebound)
- PORTED `sceMpegGetDecodeMode` w1 @ 0x0026B820 <- ntsc src/cod/vendor_2517D0:func_00251BE8 (1 syms rebound)
- PORTED `sceMpegGetPicture` w1 @ 0x0026B728 <- ntsc src/cod/vendor_2517D0:func_00251AF0 (2 syms rebound)
- PORTED `sceMpegGetPictureRAW8` w1 @ 0x0026B770 <- ntsc src/cod/vendor_2517D0:func_00251B38 (2 syms rebound)
- PORTED `sceMpegGetPictureRAW8xy` w1 @ 0x0026B7B8 <- ntsc src/cod/vendor_2517D0:func_00251B80 (2 syms rebound)
- PORTED `sceMpegIsEnd` w1 @ 0x0026B840 <- ntsc src/cod/vendor_2517D0:func_00251C08 (1 syms rebound)
- PORTED `sceMpegIsRefBuffEmpty` w1 @ 0x0026B850 <- ntsc src/cod/vendor_2517D0:func_00251C18 (1 syms rebound)
- PORTED `sceMpegReset` w1 @ 0x0026B860 <- ntsc src/cod/vendor_2517D0:func_00251C28 (4 syms rebound)
- PORTED `sceMpegResetDefaultPtsGap` w1 @ 0x0026B9C0 <- ntsc src/cod/vendor_2517D0:func_00251D88 (1 syms rebound)
- PORTED `sceMpegSetDecodeMode` w1 @ 0x0026B808 <- ntsc src/cod/vendor_2517D0:func_00251BD0 (1 syms rebound)
- PORTED `sceMpegSetDefaultPtsGap` w1 @ 0x0026B9A8 <- ntsc src/cod/vendor_2517D0:func_00251D70 (1 syms rebound)
- PORTED `sceMpegSetImageBuff` w1 @ 0x0026B9D0 <- ntsc src/cod/vendor_2517D0:func_00251D98 (2 syms rebound)
- PORTED `sceSetBrokenLink` w1 @ 0x0026BA28 <- ntsc src/cod/vendor_2517D0:func_00251DF0 (1 syms rebound)
- PORTED `sceSetPtm` w1 @ 0x0026BA38 <- ntsc src/cod/vendor_2517D0:func_00251E00 (1 syms rebound)
- REVERTED `setD3_CHCR` w2 @ 0x00272268 — [codegen] tu-size: TU .text 0x7D00 != PAL span 0x7D08 (trailing pad word / extra code)
- REVERTED `setD4_CHCR` w2 @ 0x002722D0 — [codegen] tu-size: TU .text 0x7CFC != PAL span 0x7D08 (trailing pad word / extra code)

### src/cod/vendor_272338
- PORTED `_SgContLoopCount` w1 @ 0x002763C8 <- ntsc src/cod/vendor_258CC0:func_0025BDD8 (2 syms rebound)
- PORTED `_SgContPolta` w1 @ 0x00275948 <- ntsc src/cod/vendor_258CC0:func_0025B358 (4 syms rebound)
- PORTED `_SgDeltaTime` w1 @ 0x00276698 <- ntsc src/cod/vendor_258CC0:func_0025C0A8 (1 syms rebound)
- PORTED `_SgGetComContext` w2 @ 0x00273258 <- ntsc src/cod/vendor_2575C0:func_00258C68 (2 syms rebound)
- PORTED `_SgGetHeadContext` w2 @ 0x002732C0 <- ntsc src/cod/vendor_258CC0:func_00258CD0 (2 syms rebound)
- PORTED `_SgGetIop2EeContext` w2 @ 0x002732D0 <- ntsc src/cod/vendor_258CC0:func_00258CE0 (2 syms rebound)
- PORTED `_SgGetPacketCntext` w1 @ 0x002732E0 <- ntsc src/cod/vendor_258CC0:func_00258CF0 (2 syms rebound)
- PORTED `_SgGetSeVolValue` w2 @ 0x00273298 <- ntsc src/cod/vendor_2575C0:func_00258CA8 (2 syms rebound)
- PORTED `_SgGetSeqContext` w1 @ 0x00273240 <- ntsc src/cod/vendor_2575C0:func_00258C50 (2 syms rebound)
- PORTED `_SgGetSlotContext` w1 @ 0x00273228 <- ntsc src/cod/vendor_2575C0:func_00258C38 (2 syms rebound)
- PORTED `_SgGetVabContext` w1 @ 0x00273268 <- ntsc src/cod/vendor_2575C0:func_00258C78 (2 syms rebound)
- PORTED `_SgIntoKeyOn` w1 @ 0x00275180 <- ntsc src/cod/vendor_258CC0:func_0025AB90 (2 syms rebound)
- PORTED `_SgPitchTableVag` w1 @ 0x00275208 <- ntsc src/cod/vendor_258CC0:func_0025AC18 (2 syms rebound)
- PORTED `_SgProgChange` w1 @ 0x002755E0 <- ntsc src/cod/vendor_258CC0:func_0025AFF0 (2 syms rebound)
- PORTED `_SgSeKeyOff` w1 @ 0x00274F30 <- ntsc src/cod/vendor_258CC0:func_0025A940 (4 syms rebound)
- PORTED `_SgSeqKeyOnSlot` w1 @ 0x00274BC0 <- ntsc src/cod/vendor_258CC0:func_0025A5D0 (3 syms rebound)
- PORTED `_SgSetSeContext` w2 @ 0x002732B0 <- ntsc src/cod/vendor_258CC0:func_00258CC0 (2 syms rebound)
- PORTED `_SgSetSeVolValue` w1 @ 0x00273280 <- ntsc src/cod/vendor_2575C0:func_00258C90 (2 syms rebound)
- REVERTED `_SgSndn2Remote` w1 @ 0x00276A80 — [codegen] tu-size: TU .text 0x4794 != PAL span 0x4798 (trailing pad word / extra code)
- PORTED `_SgTempoChange` w1 @ 0x00275550 <- ntsc src/cod/vendor_258CC0:func_0025AF60 (2 syms rebound)
- PORTED `_SgfadeParam` w1 @ 0x002768B0 <- ntsc src/cod/vendor_258CC0:func_0025C2C0 (1 syms rebound)
- PORTED `func_002725D8` w2 @ 0x002725D8 <- ntsc src/cod/vendor_2575C0:func_00258998 (3 syms rebound)
- PORTED `sceIpuStopDMA` w1 @ 0x00272338 <- ntsc src/cod/vendor_2575C0:func_002586F8 (3 syms rebound)
- PORTED `sceIpuSync` w1 @ 0x00272570 <- ntsc src/cod/vendor_2575C0:func_00258930 (1 syms rebound)

### src/cod/vendor_276AD0
- PORTED `SgBgmClose` w1 @ 0x00277218 <- ntsc src/cod/vendor_258CC0:func_0025CC28 (3 syms rebound)
- PORTED `SgBgmOpen` w1 @ 0x002770B0 <- ntsc src/cod/vendor_258CC0:func_0025CAC0 (4 syms rebound)
- PORTED `SgCalledTickProc` w1 @ 0x00276C28 <- ntsc src/cod/vendor_258CC0:func_0025C638 (3 syms rebound)
- PORTED `SgDmaRead` w1 @ 0x00276CA0 <- ntsc src/cod/vendor_258CC0:func_0025C6B0 (2 syms rebound)
- PORTED `SgDmaWrite` w1 @ 0x00276C70 <- ntsc src/cod/vendor_258CC0:func_0025C680 (2 syms rebound)
- PORTED `SgGetBgmStatus` w1 @ 0x002779A0 <- ntsc src/cod/vendor_258CC0:func_0025D3B0 (2 syms rebound)
- PORTED `SgGetBgmTempo` w1 @ 0x00277970 <- ntsc src/cod/vendor_258CC0:func_0025D380 (2 syms rebound)
- PORTED `SgInit` w2 @ 0x00276BA8 <- ntsc src/cod/vendor_258CC0:func_0025C5B8 (2 syms rebound)
- PORTED `SgInitHot` w1 @ 0x00276BB0 <- ntsc src/cod/vendor_258CC0:func_0025C5C0 (2 syms rebound)
- PORTED `SgQuit` w1 @ 0x00276BB8 <- ntsc src/cod/vendor_258CC0:func_0025C5C8 (2 syms rebound)
- PORTED `SgSeStop` w1 @ 0x00277DE0 <- ntsc src/cod/vendor_258CC0:func_0025D7F0 (5 syms rebound)
- PORTED `SgSeStopAll` w1 @ 0x00277F10 <- ntsc src/cod/vendor_258CC0:func_0025D920 (3 syms rebound)
- PORTED `SgSetBgmTempo` w1 @ 0x002778C8 <- ntsc src/cod/vendor_258CC0:func_0025D2D8 (3 syms rebound)
- PORTED `SgSetBgmVol` w1 @ 0x00277480 <- ntsc src/cod/vendor_258CC0:func_0025CE90 (2 syms rebound)
- PORTED `SgSetDigitalOutputMode` w1 @ 0x00276C58 <- ntsc src/cod/vendor_258CC0:func_0025C668 (2 syms rebound)
- PORTED `SgSetMasterVol` w1 @ 0x00277468 <- ntsc src/cod/vendor_258CC0:func_0025CE78 (2 syms rebound)
- PORTED `SgSetOutputMode` w1 @ 0x00277318 <- ntsc src/cod/vendor_258CC0:func_0025CD28 (2 syms rebound)
- PORTED `SgSetReverbDelaytime` w1 @ 0x002772E8 <- ntsc src/cod/vendor_258CC0:func_0025CCF8 (2 syms rebound)
- PORTED `SgSetReverbDepth` w1 @ 0x002772D0 <- ntsc src/cod/vendor_258CC0:func_0025CCE0 (2 syms rebound)
- PORTED `SgSetReverbEndAddr` w1 @ 0x002772A0 <- ntsc src/cod/vendor_258CC0:func_0025CCB0 (2 syms rebound)
- PORTED `SgSetReverbFeedback` w1 @ 0x00277300 <- ntsc src/cod/vendor_258CC0:func_0025CD10 (2 syms rebound)
- PORTED `SgSetReverbType` w1 @ 0x002772B8 <- ntsc src/cod/vendor_258CC0:func_0025CCC8 (2 syms rebound)
- PORTED `SgSetSeMasterVol` w1 @ 0x00277528 <- ntsc src/cod/vendor_258CC0:func_0025CF38 (4 syms rebound)
- PORTED `SgSetSePitchDirect` w1 @ 0x00278058 <- ntsc src/cod/vendor_258CC0:func_0025DA68 (2 syms rebound)
- PORTED `SgSetSeVolDirect` w1 @ 0x00277FB8 <- ntsc src/cod/vendor_258CC0:func_0025D9C8 (2 syms rebound)
- PORTED `SgSetSpuSlotFree` w1 @ 0x002782A0 <- ntsc src/cod/vendor_258CC0:func_0025DCB0 (2 syms rebound)
- PORTED `SgSetTickMode` w1 @ 0x00277340 <- ntsc src/cod/vendor_258CC0:func_0025CD50 (2 syms rebound)
- PORTED `SgSndn2RemoteSync` w1 @ 0x00276B60 <- ntsc src/cod/vendor_258CC0:func_0025C570 (4 syms rebound)
- PORTED `SgStAdpcmChannelPitch` w1 @ 0x00278468 <- ntsc src/cod/vendor_258CC0:func_0025DE78 (2 syms rebound)
- PORTED `SgStAdpcmChannelVolume` w1 @ 0x002783E0 <- ntsc src/cod/vendor_258CC0:func_0025DDF0 (2 syms rebound)
- PORTED `SgStAdpcmClose` w1 @ 0x002783A0 <- ntsc src/cod/vendor_258CC0:func_0025DDB0 (2 syms rebound)
- PORTED `SgStAdpcmInit` w1 @ 0x002782E0 <- ntsc src/cod/vendor_258CC0:func_0025DCF0 (2 syms rebound)
- PORTED `SgStAdpcmIopReadAddr` w1 @ 0x002785A0 <- ntsc src/cod/vendor_258CC0:func_0025DFB0 (2 syms rebound)
- PORTED `SgStAdpcmPlay` w1 @ 0x002784E0 <- ntsc src/cod/vendor_258CC0:func_0025DEF0 (2 syms rebound)
- PORTED `SgStAdpcmQuit` w1 @ 0x002782F8 <- ntsc src/cod/vendor_258CC0:func_0025DD08 (2 syms rebound)
- PORTED `SgStAdpcmStop` w1 @ 0x00278540 <- ntsc src/cod/vendor_258CC0:func_0025DF50 (2 syms rebound)
- REVERTED `SgStPcmBufMode` w1 @ 0x00278870 — [codegen] tu-size: TU .text 0x1E04 != PAL span 0x1E08 (trailing pad word / extra code)
- PORTED `SgStPcmClose` w1 @ 0x002786B0 <- ntsc src/cod/vendor_258CC0:func_0025E0C0 (2 syms rebound)
- PORTED `SgStPcmInit` w1 @ 0x00278610 <- ntsc src/cod/vendor_258CC0:func_0025E020 (2 syms rebound)
- PORTED `SgStPcmIopReadAddr` w1 @ 0x00278828 <- ntsc src/cod/vendor_25E1E8:func_0025E238 (2 syms rebound)
- PORTED `SgStPcmLseek` w1 @ 0x00278788 <- ntsc src/cod/vendor_258CC0:func_0025E198 (2 syms rebound)
- PORTED `SgStPcmOpen` w1 @ 0x00278640 <- ntsc src/cod/vendor_258CC0:func_0025E050 (2 syms rebound)
- PORTED `SgStPcmPlay` w1 @ 0x00278708 <- ntsc src/cod/vendor_258CC0:func_0025E118 (2 syms rebound)
- PORTED `SgStPcmQuit` w1 @ 0x00278628 <- ntsc src/cod/vendor_258CC0:func_0025E038 (2 syms rebound)
- PORTED `SgStPcmSetEffect` w1 @ 0x002786F0 <- ntsc src/cod/vendor_258CC0:func_0025E100 (2 syms rebound)
- PORTED `SgStPcmStop` w1 @ 0x00278748 <- ntsc src/cod/vendor_258CC0:func_0025E158 (2 syms rebound)
- PORTED `SgStPcmVolume` w1 @ 0x002787D8 <- ntsc src/cod/vendor_25E1E8:func_0025E1E8 (2 syms rebound)
- PORTED `SgVabClose` w1 @ 0x00276F50 <- ntsc src/cod/vendor_258CC0:func_0025C960 (6 syms rebound)
- PORTED `SgVabOpen` w1 @ 0x00276DE8 <- ntsc src/cod/vendor_258CC0:func_0025C7F8 (3 syms rebound)

### src/cod/vendor_2788D8
- PORTED `__ieee754_sqrtf` w1 @ 0x00279F18 <- ntsc src/cod/vendor_25E1E8:func_0025F928 (1 syms rebound)
- PORTED `__kernel_cosf` w1 @ 0x0027A050 <- ntsc src/cod/vendor_25E1E8:func_0025FA60 (1 syms rebound)
- PORTED `copysignf` w1 @ 0x0027B160 <- ntsc src/cod/vendor_25E1E8:func_00260B70 (1 syms rebound)
- PORTED `fabsf` w1 @ 0x0027AED0 <- ntsc src/cod/vendor_25E1E8:func_002608E0 (1 syms rebound)
- REVERTED `fmodf` w1 @ 0x00278CF0 — [callee-sig-conflict] src/cod/vendor_2788D8.c:51: conflicting types for `__ieee754_fmodf'
- PORTED `isnanf` w1 @ 0x0027AFD8 <- ntsc src/cod/vendor_25E1E8:func_002609E8 (1 syms rebound)
- PORTED `matherr` w1 @ 0x0027AC00 <- ntsc src/cod/vendor_25E1E8:func_00260610 (2 syms rebound)
- PORTED `sinf` w1 @ 0x002788D8 <- ntsc src/cod/vendor_25E1E8:func_0025E2E8 (4 syms rebound)

### src/cod/vendor_27B190
- PORTED `__fpcmp_parts_d` w1 @ 0x0027D5E8 <- ntsc src/cod/vendor_25E1E8:func_00262FF8 (1 syms rebound)
- PORTED `__fpcmp_parts_f` w1 @ 0x0027E1F0 <- ntsc src/cod/vendor_25E1E8:func_00263C00 (1 syms rebound)
- REVERTED `__main` w1 @ 0x0027B298 — [unresolved-symbol] unresolved-symbol: D_0071EB68 undefined on the PAL side (unrebindable raw-constant reference)
- PORTED `__make_dp` w1 @ 0x0027D978 <- ntsc src/cod/vendor_25E1E8:func_00263388 (2 syms rebound)
- PORTED `__make_fp` w1 @ 0x0027E570 <- ntsc src/cod/vendor_25E1E8:func_00263F80 (2 syms rebound)
- PORTED `__negdf2` w1 @ 0x0027D940 <- ntsc src/cod/vendor_25E1E8:func_00263350 (3 syms rebound)
- PORTED `__negsf2` w1 @ 0x0027E538 <- ntsc src/cod/vendor_25E1E8:func_00263F48 (3 syms rebound)
- PORTED `dpadd` w1 @ 0x0027D118 <- ntsc src/cod/vendor_25E1E8:func_00262B28 (4 syms rebound)
- PORTED `dpcmp` w1 @ 0x0027D700 <- ntsc src/cod/vendor_25E1E8:func_00263110 (3 syms rebound)
- PORTED `dpdiv` w1 @ 0x0027D480 <- ntsc src/cod/vendor_25E1E8:func_00262E90 (4 syms rebound)
- PORTED `dpsub` w1 @ 0x0027D170 <- ntsc src/cod/vendor_25E1E8:func_00262B80 (4 syms rebound)
- PORTED `dptofp` w1 @ 0x0027D9A8 <- ntsc src/cod/vendor_25E1E8:func_002633B8 (3 syms rebound)
- PORTED `fpadd` w1 @ 0x0027DDD8 <- ntsc src/cod/vendor_25E1E8:func_002637E8 (4 syms rebound)
- PORTED `fpcmp` w1 @ 0x0027E308 <- ntsc src/cod/vendor_25E1E8:func_00263D18 (3 syms rebound)
- REVERTED `fpdiv` w1 @ 0x0027E090 — [parse] src/cod/vendor_27B190.c:7: parse error before `*'
- PORTED `fpsub` w1 @ 0x0027DE30 <- ntsc src/cod/vendor_25E1E8:func_00263840 (4 syms rebound)
- PORTED `fptodp` w1 @ 0x0027E5A0 <- ntsc src/cod/vendor_25E1E8:func_00263FB0 (3 syms rebound)

### src/cod/vendor_27E5E0
- PORTED `_Bfree` w1 @ 0x00286588 <- ntsc src/cod/vendor_2668B8:func_0026BF98 (1 syms rebound)
- PORTED `__assert` w1 @ 0x0027E5E0 <- ntsc src/cod/vendor_25E1E8:func_00263FF0 (5 syms rebound)
- PORTED `__errno` w2 @ 0x0027E640 <- ntsc src/cod/vendor_25E1E8:func_00264050 (2 syms rebound)
- PORTED `__malloc_lock` w2 @ 0x002864D0 <- ntsc src/cod/vendor_2668B8:func_0026BEE0 (1 syms rebound)
- PORTED `__malloc_unlock` w2 @ 0x002864D8 <- ntsc src/cod/vendor_2668B8:func_0026BEE8 (1 syms rebound)
- PORTED `__mcmp` w1 @ 0x00286E40 <- ntsc src/cod/vendor_2668B8:func_0026C850 (1 syms rebound)
- PORTED `__sclose` w1 @ 0x00287C98 <- ntsc src/cod/vendor_2668B8:func_0026D6A8 (2 syms rebound)
- PORTED `__sfmoreglue` w1 @ 0x00284A80 <- ntsc src/cod/vendor_2668B8:func_0026A490 (3 syms rebound)
- PORTED `__sigtramp` w2 @ 0x00287AA0 <- ntsc src/cod/vendor_2668B8:func_0026D4B0 (3 syms rebound)
- REVERTED `__sinit` w1 @ 0x00284BF0 — [codegen] insn 3: expected `addiu	v0,v0,0` built `addiu	v0,v0,26096`
- PORTED `__sprint` w2 @ 0x00280118 <- ntsc src/cod/vendor_25E1E8:func_00265B28 (2 syms rebound)
- PORTED `__sread` w1 @ 0x00287B48 <- ntsc src/cod/vendor_2668B8:func_0026D558 (2 syms rebound)
- PORTED `__sseek` w1 @ 0x00287C30 <- ntsc src/cod/vendor_2668B8:func_0026D640 (2 syms rebound)
- PORTED `__swrite` w1 @ 0x00287BB0 <- ntsc src/cod/vendor_2668B8:func_0026D5C0 (3 syms rebound)
- PORTED `_cleanup` w2 @ 0x00284BE0 <- ntsc src/cod/vendor_2668B8:func_0026A5F0 (3 syms rebound)
- REVERTED `_cleanup_r` w2 @ 0x00284BD0 — [codegen] insn 1: expected `j	0 <_cleanup_r>` built `j	7028 <_fwalk>`
- PORTED `_close_r` w1 @ 0x00289200 <- ntsc src/cod/vendor_2668B8:func_0026EC10 (3 syms rebound)
- PORTED `_fstat_r` w2 @ 0x00289258 <- ntsc src/cod/vendor_2668B8:func_0026EC68 (3 syms rebound)
- PORTED `_getpid_r` w2 @ 0x00287B28 <- ntsc src/cod/vendor_2668B8:func_0026D538 (2 syms rebound)
- PORTED `_hi0bits` w1 @ 0x00286818 <- ntsc src/cod/vendor_2668B8:func_0026C228 (1 syms rebound)
- PORTED `_i2b` w1 @ 0x00286960 <- ntsc src/cod/vendor_2668B8:func_0026C370 (2 syms rebound)
- PORTED `_init_signal` w2 @ 0x00287A78 <- ntsc src/cod/vendor_2668B8:func_0026D488 (3 syms rebound)
- PORTED `_kill_r` w2 @ 0x00287AC8 <- ntsc src/cod/vendor_2668B8:func_0026D4D8 (3 syms rebound)
- PORTED `_lo0bits` w1 @ 0x002868A0 <- ntsc src/cod/vendor_2668B8:func_0026C2B0 (1 syms rebound)
- PORTED `_localeconv_r` w2 @ 0x00285728 <- ntsc src/cod/vendor_2668B8:func_0026B138 (2 syms rebound)
- PORTED `_lseek_r` w2 @ 0x002892B8 <- ntsc src/cod/vendor_2668B8:func_0026ECC8 (3 syms rebound)
- PORTED `_malloc_trim_r` w1 @ 0x002850C0 <- ntsc src/cod/vendor_2668B8:func_0026AAD0 (9 syms rebound)
- PORTED `_mbtowc_r` w1 @ 0x002862B0 <- ntsc src/cod/vendor_2668B8:func_0026BCC0 (1 syms rebound)
- PORTED `_mprec_log10` w1 @ 0x00287490 <- ntsc src/cod/vendor_2668B8:func_0026CEA0 (3 syms rebound)
- PORTED `_printf_r` w1 @ 0x0027E888 <- ntsc src/cod/vendor_25E1E8:func_00264298 (2 syms rebound)
- PORTED `_read_r` w2 @ 0x00289318 <- ntsc src/cod/vendor_2668B8:func_0026ED28 (3 syms rebound)
- PORTED `_s2b` w1 @ 0x002866D0 <- ntsc src/cod/vendor_2668B8:func_0026C0E0 (3 syms rebound)
- PORTED `_sbrk_r` w1 @ 0x00287718 <- ntsc src/cod/vendor_2668B8:func_0026D128 (3 syms rebound)
- PORTED `_setlocale_r` w1 @ 0x002856A0 <- ntsc src/cod/vendor_2668B8:func_0026B0B0 (4 syms rebound)
- PORTED `_signal_r` w1 @ 0x002877E8 <- ntsc src/cod/vendor_2668B8:func_0026D1F8 (2 syms rebound)
- PORTED `_sprintf_r` w1 @ 0x0027F380 <- ntsc src/cod/vendor_25E1E8:func_00264D90 (2 syms rebound)
- PORTED `_write_r` w2 @ 0x002890E0 <- ntsc src/cod/vendor_2668B8:func_0026EAF0 (3 syms rebound)
- PORTED `atoi` w1 @ 0x0027E618 <- ntsc src/cod/vendor_25E1E8:func_00264028 (2 syms rebound)
- PORTED `eofread` w2 @ 0x0027F458 <- ntsc src/cod/vendor_25E1E8:func_00264E68 (1 syms rebound)
- REVERTED `fiprintf` w1 @ 0x0027E650 — [callee-sig-conflict] src/cod/vendor_27E5E0.c:40: conflicting types for `fiprintf'
- PORTED `fread` w1 @ 0x00284C80 <- ntsc src/cod/vendor_2668B8:func_0026A690 (3 syms rebound)
- PORTED `func_0027FE08` w1 @ 0x0027FE08 <- ntsc src/cod/vendor_25E1E8:func_00265818 (1 syms rebound)
- PORTED `func_00280E60` w2 @ 0x00280E60 <- ntsc src/cod/vendor_25E1E8:func_00266870 (2 syms rebound)
- PORTED `func_002834F8` w1 @ 0x002834F8 <- ntsc src/cod/vendor_2668B8:func_00268F08 (3 syms rebound)
- PORTED `func_00283518` w2 @ 0x00283518 <- ntsc src/cod/vendor_2668B8:func_00268F28 (2 syms rebound)
- PORTED `isinf` w1 @ 0x00287698 <- ntsc src/cod/vendor_2668B8:func_0026D0A8 (1 syms rebound)
- PORTED `isnan` w1 @ 0x002876E0 <- ntsc src/cod/vendor_2668B8:func_0026D0F0 (1 syms rebound)
- PORTED `lflush` w2 @ 0x00287500 <- ntsc src/cod/vendor_2668B8:func_0026CF10 (2 syms rebound)
- PORTED `localeconv` w2 @ 0x00285768 <- ntsc src/cod/vendor_2668B8:func_0026B178 (3 syms rebound)
- PORTED `memset` w1 @ 0x0027E7C8 <- ntsc src/cod/vendor_25E1E8:func_002641D8 (1 syms rebound)
- PORTED `printf` w1 @ 0x0027E8C8 <- ntsc src/cod/vendor_25E1E8:func_002642D8 (3 syms rebound)
- PORTED `raise` w2 @ 0x00287A20 <- ntsc src/cod/vendor_2668B8:func_0026D430 (3 syms rebound)
- PORTED `rand` w1 @ 0x0027F350 <- ntsc src/cod/vendor_25E1E8:func_00264D60 (2 syms rebound)
- PORTED `setlocale` w2 @ 0x00285738 <- ntsc src/cod/vendor_2668B8:func_0026B148 (3 syms rebound)
- PORTED `signal` w2 @ 0x00287A48 <- ntsc src/cod/vendor_2668B8:func_0026D458 (3 syms rebound)
- PORTED `sprintf` w1 @ 0x0027F3E8 <- ntsc src/cod/vendor_25E1E8:func_00264DF8 (3 syms rebound)
- PORTED `srand` w1 @ 0x0027F340 <- ntsc src/cod/vendor_25E1E8:func_00264D50 (2 syms rebound)
- REVERTED `std` w1 @ 0x00284A28 — [codegen] insn 0: expected `lui	v0,0x0` built `lui	v0,0x1`
- PORTED `strcat` w1 @ 0x0027F4E8 <- ntsc src/cod/vendor_25E1E8:func_00264EF8 (2 syms rebound)
- PORTED `strrchr` w1 @ 0x0027FD20 <- ntsc src/cod/vendor_25E1E8:func_00265730 (1 syms rebound)
- PORTED `strtodf` w1 @ 0x00288BE8 <- ntsc src/cod/vendor_2668B8:func_0026E5F8 (3 syms rebound)
- PORTED `strtok` w1 @ 0x0027FDE0 <- ntsc src/cod/vendor_25E1E8:func_002657F0 (3 syms rebound)
- PORTED `strtol` w2 @ 0x002800E0 <- ntsc src/cod/vendor_25E1E8:func_00265AF0 (3 syms rebound)
- PORTED `strtoul` w2 @ 0x00288E30 <- ntsc src/cod/vendor_2668B8:func_0026E840 (3 syms rebound)
- PORTED `vsprintf` w1 @ 0x00283390 <- ntsc src/cod/vendor_2668B8:func_00268DA0 (3 syms rebound)

### src/cod/vendor_2898E8
- PORTED `InvalidDCache` w2 @ 0x00289AD0 <- ntsc src/cod/vendor_2668B8:func_0026F4E0 (4 syms rebound)
- PORTED `SyncDCache` w2 @ 0x00289990 <- ntsc src/cod/vendor_2668B8:func_0026F3A0 (4 syms rebound)
- PORTED `_sceIDC` w1 @ 0x00289A28 <- ntsc src/cod/vendor_2668B8:func_0026F438 (1 syms rebound)
- PORTED `_sceSDC` w1 @ 0x002898E8 <- ntsc src/cod/vendor_2668B8:func_0026F2F8 (1 syms rebound)
- REVERTED `iInvalidDCache` w2 @ 0x00289B50 — [codegen] tu-size: TU .text 0x27C != PAL span 0x280 (trailing pad word / extra code)
- PORTED `iSyncDCache` w2 @ 0x00289A10 <- ntsc src/cod/vendor_2668B8:func_0026F420 (2 syms rebound)

### src/commonact
- PORTED `ACTAdjustPlane` w1 @ 0x00161AE0 <- ntsc src/commonact:funcCommonJumpDircorrect (2 syms rebound)
- REVERTED `ACTMotDirToWall` w3 @ 0x00163A78 — [codegen] insn 9: expected `addiu	a1,a1,1200` built `addiu	a1,a1,1184`
- PORTED `ACTSetPositionNoFitting` w2 @ 0x00158C90 <- ntsc src/boyact:IsAbleBoyControl (2 syms rebound)
- PORTED `ACTSetPositionNodeWithFitting` w2 @ 0x00158C98 <- ntsc src/boyact:ACTChkAttackIgnore_BOY (2 syms rebound)
- REVERTED `ACTSetPositionWithFitting` w2 @ 0x00158C88 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)
- PORTED `ControlMotionOrient` w1 @ 0x001639C8 <- ntsc src/commonact:actCommonSlowrun (2 syms rebound)
- PORTED `E3_LeverCheck` w1 @ 0x00160A68 <- ntsc src/commonact:_boxbar_set_sound (5 syms rebound) — unblocked by the PAL phase-1 `lit4 src/commonact` carve
- PORTED `FloorIsTruck` w1 @ 0x001639E8 <- ntsc src/commonact:func_0015F248 (2 syms rebound)
- PORTED `SetCorrectOrientOfChain` w1 @ 0x00163AC0 <- ntsc src/commonact:_ACTMotDirSmzDirect (3 syms rebound)
- PORTED `SetDirectRootPositionXZ` w1 @ 0x0015BD48 <- ntsc src/commonact:WithMailFunc_WayBeginPosError (3 syms rebound)
- PORTED `_ACTMotDir_V` w1 @ 0x00163A38 <- ntsc src/commonact:ACT_LAYOUT_GAMEOVER (3 syms rebound)
- PORTED `actAfterSlip` w2 @ 0x00163CC8 <- ntsc src/commonact:actCommonReviveAir (1 syms rebound)
- PORTED `afterCommonBar` w1 @ 0x00163D60 <- ntsc src/commonact:func_0015F578 (5 syms rebound) — unblocked by the PAL phase-1 `sdata src/commonact` carve
- PORTED `afterCommonBox` w1 @ 0x00163D38 <- ntsc src/commonact:actCommonDelete (2 syms rebound)
- PORTED `afterCommonCling` w2 @ 0x00163CA0 <- ntsc src/commonact:actCommonRevive (2 syms rebound)
- PORTED `afterCommonOneWall` w2 @ 0x00163EF8 <- ntsc src/enemy_act:boss_effect_process (1 syms rebound)
- PORTED `afterCommonRevive` w2 @ 0x00163CD8 <- ntsc src/commonact:actCommonPlay (2 syms rebound)
- REVERTED `afterCommonStone` w3 @ 0x00163D00 — [codegen] insn 6: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- PORTED `debugDispSphere` w1 @ 0x0015E388 <- ntsc src/commonact:actCommonLever (9 syms rebound)
- PORTED `func_0015BD00` w1 @ 0x0015BD00 <- ntsc src/commonact:func_00157BB0 (3 syms rebound)
- REVERTED `func_001631F0` w2 @ 0x001631F0 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `func_00163220` w2 @ 0x00163220 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- CARVES `src/commonact` — 4 US carve entries to translate:
    - - [0x182390, .data, src/commonact]  # carved D_00282390..D_002823F0 (VMA 0x282390..0x282400, 112 bytes, 5 syms)
    - - [0x458848, .rodata, src/commonact]  # full commonact .rodata run (starts at "common rope after func\n" + src/commonact.c __FILE__ string; ends before the 5 enemy-mode name strings whose owning .data table is unattributed), VMA 0x558848..0x558DC0
    - - [0x530C28, .lit4, src/commonact]     # carved D_00630C28..D_00630CDC (46 slots, _boxbar_set_sound + func_0015DF88 + 44 asm), VMA 0x630C28..0x630CE0
    - - [0x5322F0, .sdata, src/commonact]  # carved D_006322F0..D_00632308 (VMA 0x6322F0..0x632310, 32 bytes); D_006322F0 is func_0015F578's "reset\n" string literal, the other 4 are sidecar objects

### src/darkVolume
- PORTED `DarkVolumeDL` w2 @ 0x001D6F78 <- ntsc src/darkVolume:GetGameOverEffectCenterPosition (1 syms rebound)
- PORTED `ExecGameOverEffect` w2 @ 0x001D6F80 <- ntsc src/darkVolume:InitGameOverEffect (1 syms rebound)
- PORTED `GetGameOverEffectCenterPosition` w2 @ 0x001D6D20 <- ntsc src/darkVolume:darkVolume (3 syms rebound)
- REVERTED `ResetGameOverEffect` w2 @ 0x001D7078 — [codegen] tu-size: TU .text 0x2BCC != PAL span 0x2BD0 (trailing pad word / extra code)
- PORTED `SetDarkVolumeEffect` w1 @ 0x001D6AA8 <- ntsc src/darkVolume:renderViewCoordZSphere (4 syms rebound)
- PORTED `StartQueenAttackEffect` w1 @ 0x001D7020 <- ntsc src/effectTool:editParam (8 syms rebound)

### src/debug
- PORTED `CloseVif1DirectPacket` w1 @ 0x001B3E20 <- ntsc src/gamesys:gamesysObjInfoPosNewStageSet (5 syms rebound)
- PORTED `SendVif1DirectPacket` w1 @ 0x001B3E60 <- ntsc src/gamesys:gamesysObjInfoGet (4 syms rebound)
- PORTED `debugCdvdLoadInfoSegAdd` w1 @ 0x001B3078 <- ntsc src/debug_menu:func_001AA608 (2 syms rebound)
- PORTED `debugCdvdLoadInfoSegCls` w1 @ 0x001B30A8 <- ntsc src/debug_menu:func_001AA638 (2 syms rebound)
- REVERTED `debugCdvdLoadInfoSegDisp` w1 @ 0x001B3AE0 — [codegen] insn 30: expected `addiu	t2,t2,0` built `addiu	t2,t2,23408`
- PORTED `debugCdvdLoadInfoSegInit` w1 @ 0x001B3030 <- ntsc src/debug_menu:func_001AA5C0 (2 syms rebound)
- PORTED `debugSceClose` w1 @ 0x001B2FC0 <- ntsc src/debug_menu:func_001AA550 (3 syms rebound)
- PORTED `debugSceCloseFdNew` w1 @ 0x001B2FF0 <- ntsc src/debug_menu:func_001AA580 (3 syms rebound)
- REVERTED `debugSceOpen` w1 @ 0x001B2F60 — [codegen] insn 3: expected `lui	a2,0x0` built `sd	s0,0(sp)`
- REVERTED `debug_AdpcmTest` w3 @ 0x001B3A50 — [codegen] insn 6: expected `addiu	v0,zero,105` built `addiu	v0,zero,96`
- REVERTED `debug_Assert` w3 @ 0x001ABC40 — [codegen] insn 15: expected `addiu	a1,zero,1392` built `addiu	a1,zero,1283`
- PORTED `debug_BackStageTest` w1 @ 0x001B3C18 <- ntsc src/gamesys:gamesysObjInfoStageInitFlagCls (3 syms rebound) — unblocked by the PAL phase-1 `lit4 src/debug` carve
- PORTED `debug_BeginTimer` w1 @ 0x001B2800 <- ntsc src/debug_menu:debug_TargetGObj_Func (1 syms rebound)
- PORTED `debug_CallbackGsFinish` w2 @ 0x001B3110 <- ntsc src/debug_menu:func_001AA688 (2 syms rebound)
- PORTED `debug_ClearFontWindow` w1 @ 0x001B2958 <- ntsc src/debug_menu:func_001A9EE8 (3 syms rebound)
- PORTED `debug_DispMatrix` w1 @ 0x001B2C80 <- ntsc src/debug_menu:func_001AA210 (2 syms rebound)
- SKIPPED `debug_DispQW` w2 @ 0x001AF2B8 — jtbl
- PORTED `debug_EndingDemo` w2 @ 0x001B3BF8 <- ntsc src/gamesys:gamesysNObjInfoInit (2 syms rebound)
- PORTED `debug_FlushFont` w2 @ 0x001AD380 <- ntsc src/debug:draw_batsu (2 syms rebound)
- PORTED `debug_FreeCamera` w1 @ 0x001B3DE0 <- ntsc src/gamesys:gamesysObjInfoUniqDataSet (3 syms rebound)
- PORTED `debug_GameOver` w2 @ 0x001B3BD8 <- ntsc src/gamesys:gamesysCharacterInfoLoad (2 syms rebound)
- PORTED `debug_LogPrintf` w1 @ 0x001ABCF0 <- ntsc src/debug:func_001A2E28 (5 syms rebound)
- PORTED `debug_Menu_off` w2 @ 0x001B27F8 <- ntsc src/debug_menu:init_debug_menu (2 syms rebound)
- PORTED `debug_PrintFont` w1 @ 0x001AD058 <- ntsc src/debug:debug_FlushFontWindow (12 syms rebound)
- PORTED `debug_PrintFontWindowDummy` w1 @ 0x001AF870 <- ntsc src/debug_exception:debugIOPExceptionMain (1 syms rebound)
- REVERTED `debug_PrintMatrix` w1 @ 0x001AFA78 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PORTED `debug_Printf` w2 @ 0x001AF4A0 <- ntsc src/debug_exception:traceLine (3 syms rebound)
- PORTED `debug_Printf2` w2 @ 0x001AF510 <- ntsc src/debug_exception:dispSource (3 syms rebound)
- PORTED `debug_PrintfDummy` w1 @ 0x001AF850 <- ntsc src/debug_exception:debugEEExceptionMain (1 syms rebound)
- PORTED `debug_ResetBar` w1 @ 0x001B2B08 <- ntsc src/debug_menu:func_001AA098 (8 syms rebound)
- PORTED `debug_ResizeFontWindowHeight` w2 @ 0x001B2990 <- ntsc src/debug_menu:func_001A9F20 (2 syms rebound)
- PORTED `debug_SETest_color` w1 @ 0x001B3970 <- ntsc src/gamesys:gamesysObjInfoEmptyAreaSearch (3 syms rebound)
- PORTED `debug_STAFFROLLTest` w1 @ 0x001B3948 <- ntsc src/gamesys:gamesysObjInfoLoad (2 syms rebound)
- PORTED `debug_SetBarDummy` w2 @ 0x001B2CC8 <- ntsc src/debug_menu:func_001AA258 (1 syms rebound)
- REVERTED `debug_SetDmaCallback` w1 @ 0x001AC088 — [codegen] insn 9: expected `addiu	a1,a1,0` built `addiu	a1,a1,29904`
- PORTED `debug_StdPrintfDummy` w1 @ 0x001AF898 <- ntsc src/debug_exception:debug_assertMessage (1 syms rebound)
- PORTED `debug_TryToGetStartStage` w2 @ 0x001B2F58 <- ntsc src/debug_menu:func_001AA4E8 (1 syms rebound)
- PORTED `debug_closeLog` w2 @ 0x001B3028 <- ntsc src/debug_menu:func_001AA5B8 (1 syms rebound)
- PORTED `debug_mcTest` w2 @ 0x001B3928 <- ntsc src/gamesys:gamesysObjInfoSave (2 syms rebound)
- PORTED `debug_openLog` w1 @ 0x001ABCD8 <- ntsc src/debug:debug_LogPrintf (2 syms rebound)
- PORTED `debug_saveNumFunc` w3 @ 0x001B38F8 <- ntsc src/gamesys:gamesysObjInfoInit (3 syms rebound)
- PORTED `debug_tsuresariTimeZero` w2 @ 0x001B3C40 <- ntsc src/gamesys:gamesysObjInfoStageInitPosSaveUnlock (2 syms rebound)
- PORTED `getBuffer` w2 @ 0x001B02A8 <- ntsc src/debug_exception:func_001A7838 (3 syms rebound)
- PORTED `getLineBuffer` w1 @ 0x001B0290 <- ntsc src/debug_exception:func_001A7820 (3 syms rebound)
- PORTED `gsResetFunc` w1 @ 0x001B30D0 <- ntsc src/debug_menu:func_001AA660 (3 syms rebound)
- PORTED `resetGS` w2 @ 0x001B4A40 <- ntsc src/gamesys:gamesysVersionLoad (4 syms rebound)
- PORTED `resetPath` w1 @ 0x001B49A0 <- ntsc src/gamesys:gamesysMemoryLoad (5 syms rebound)
- PORTED `saveBack` w1 @ 0x001B4DE8 <- ntsc src/gamesys:gamesysGeneratorInfoSave (3 syms rebound)
- CARVES `src/debug` — 3 US carve entries to translate:
    - - [0x3B30F8, .data, src/debug]  # carved D_004B30F8..D_004B30F8 (VMA 0x4B30F8..0x4B3108, 16 bytes, 1 syms)
    - - [0x514F10, .rodata, src/debug]  # gcc-emitted jtbl_00614F10 (func_001A3398 switch, 11 entries 0x2C), VMA 0x614F10..0x614F3C
    - - [0x532A18, .sdata, src/debug]  # carved D_00632A18..D_00632A28 (VMA 0x632A18..0x632A30, 24 bytes, 4 syms)

### src/debug_exception
- PORTED `debugIOPExceptionInit` w2 @ 0x001B6228 <- ntsc src/haveParentSimpleObj:func_001AD740 (1 syms rebound)

### src/debug_menu
- REVERTED `debug_TargetGObj_Func` w1 @ 0x001B6670 — [codegen] tu-size: TU .text 0x1B4 != PAL span 0x1B8 (trailing pad word / extra code)
- PORTED `init_debug_menu` w1 @ 0x001B6658 <- ntsc src/haveParentSimpleObj:func_001ADB70 (4 syms rebound)

### src/delayFreeManager
- REVERTED `InitDelayFree` w3 @ 0x00102640 — [codegen] insn 1: expected `addiu	v1,zero,383` built `addiu	v1,zero,255`

### src/e3
- PORTED `actE3CageFallReadyChk` w1 @ 0x0021B660 <- ntsc src/e3:actE3St09aSekizo (7 syms rebound)
- REVERTED `actE3DoorUp` w3 @ 0x0021B528 — [codegen] insn 5: expected `addiu	a0,zero,55` built `addiu	a0,zero,51`
- PORTED `actE3Floor` w2 @ 0x0021AF10 <- ntsc src/e3:actE3TitleChk (3 syms rebound)
- REVERTED `actE3St01bGene1` w3 @ 0x0021AFB8 — [codegen] insn 17: expected `addiu	a0,zero,362` built `addiu	a0,zero,330`
- REVERTED `actE3St01bGene2` w3 @ 0x0021B070 — [codegen] insn 17: expected `addiu	a0,zero,362` built `addiu	a0,zero,330`
- REVERTED `actE3St01bGene3` w3 @ 0x0021B120 — [codegen] insn 17: expected `addiu	a0,zero,362` built `addiu	a0,zero,330`
- REVERTED `actE3St13cIntroChk` w3 @ 0x0021B5E0 — [codegen] insn 4: expected `addiu	a0,zero,55` built `addiu	a0,zero,51`

### src/ebrain
- PORTED `eBrainInit` w1 @ 0x00199CE8 <- ntsc src/ebrain:func_001918A8 (6 syms rebound)

### src/effectTool
- PORTED `exitEffectTool` w1 @ 0x001D8690 <- ntsc src/enemy:EnemyCheckHit (8 syms rebound)
- PORTED `setQ` w1 @ 0x001D7C70 <- ntsc src/effectTool:saveEffectData (6 syms rebound)

### src/end
- REVERTED `actEndDemo11Chk` w3 @ 0x0021EC38 — [codegen] insn 4: expected `addiu	a0,zero,349` built `addiu	a0,zero,318`
- REVERTED `actEndDemo12Chk` w3 @ 0x0021ECF0 — [codegen] insn 4: expected `addiu	a0,zero,350` built `addiu	a0,zero,319`
- REVERTED `actEndDemo13Chk` w3 @ 0x0021EDA8 — [codegen] insn 4: expected `addiu	a0,zero,351` built `addiu	a0,zero,320`
- REVERTED `actStaff1Chk` w2 @ 0x0021EDD8 — [codegen] insn 6: expected `addiu	a0,a0,0` built `addiu	a0,a0,4744`
- REVERTED `actStaff2Chk` w1 @ 0x0021EE00 — [codegen] insn 10: expected `addiu	a0,a0,0` built `addiu	a0,a0,5560`

### src/enemy
- PORTED `DemoMotionGeo` w1 @ 0x001D9948 <- ntsc src/enemy:EnemySetfDisappearAll (2 syms rebound)
- PORTED `EnemyAI` w2 @ 0x001D9A28 <- ntsc src/enemy:enemySetParticleDie (1 syms rebound)
- PORTED `EnemyDL` w1 @ 0x001D98E8 <- ntsc src/enemy:EnemySetfAppearAll (4 syms rebound)
- REVERTED `EnemyGetNSafeParts` w3 @ 0x001D9C80 — [codegen] insn 4: expected `lw	v0,2096(v0)` built `lw	v0,2048(v0)`
- REVERTED `EnemySetfAppearAll` w3 @ 0x001D9A40 — [codegen] insn 6: expected `lw	a0,2096(v0)` built `lw	a0,2048(v0)`
- REVERTED `EnemySetfDisappearAll` w3 @ 0x001D9A90 — [codegen] insn 9: expected `lw	a0,2096(v0)` built `lw	a0,2048(v0)`
- REVERTED `ReviveEnemyParticle` w3 @ 0x001D9C40 — [codegen] insn 2: expected `lw	v0,2096(a2)` built `lw	v0,2048(a2)`
- REVERTED `SetEnemyFootPrintSwitch` w3 @ 0x001D9A30 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- PORTED `SetEnemyStonizedVisual` w1 @ 0x001DA050 <- ntsc src/enemyParts:moveDataElements (4 syms rebound)
- PORTED `enemySetParticleDie` w1 @ 0x001D9BB8 <- ntsc src/enemy:SetEnemyHitGeometryAction (6 syms rebound)
- REVERTED `isExistEnemyParticle` w3 @ 0x001D9C60 — [codegen] insn 2: expected `lw	v0,2096(a2)` built `lw	v0,2048(a2)`

### src/enemy-control
- PORTED `InitEnemyCtrlGeo` w1 @ 0x0019A148 <- ntsc src/ebrain:func_00191D08 (4 syms rebound)

### src/enemyParts
- PORTED `DispEnemyEye` w1 @ 0x001DACC0 <- ntsc src/flag:InitFlagGeo (7 syms rebound)
- PORTED `DispEnemyFootPrints` w1 @ 0x001DAA98 <- ntsc src/enemyParts:func_001CF770 (2 syms rebound)
- PORTED `DispPointBlur` w1 @ 0x001DABF8 <- ntsc src/enemyParts:func_001CF8D0 (5 syms rebound)
- PORTED `ResetEnemyEye` w1 @ 0x001DAD48 <- ntsc src/flag:FlagGeo (1 syms rebound)

### src/enemy_act
- REVERTED `ACTEnemyForceSwitchToCarry` w3 @ 0x0016A2E0 — [codegen] insn 4: expected `jal	0 <ACTEnemyForceSwitchToCarry>` built `jal	14f8 <actEnemyForceSwitchToCarry>`
- REVERTED `EnemyBrainStatus_Boy` w3 @ 0x0016A238 — [codegen] insn 1: expected `lw	v0,1088(v1)` built `lw	v0,1072(v1)`
- REVERTED `EnemyBrainStatus_Girl` w3 @ 0x0016A250 — [codegen] insn 1: expected `lw	v0,1088(v1)` built `lw	v0,1072(v1)`
- PORTED `FlyMail` w1 @ 0x0016ACF8 <- ntsc src/enemy_act:IsEnemyBrainToBoy (2 syms rebound)
- PORTED `GetEnemyType` w2 @ 0x0016A470 <- ntsc src/enemy_act:ACTEnemyForceSwitchToCarry (1 syms rebound)
- REVERTED `GetEnemyTypeFromGObj` w3 @ 0x0016A460 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `IsEnemyBrainToBoy` w3 @ 0x0016A420 — [codegen] insn 4: expected `addiu	a0,zero,111` built `addiu	a0,zero,107`
- REVERTED `IsEnemyBrainToGenerator` w3 @ 0x0016A3B0 — [codegen] insn 5: expected `lw	v1,1664(a2)` built `lw	v1,1648(a2)`
- REVERTED `_ApproachTarget` w3 @ 0x0016AFC8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `_MustChase` w1 @ 0x001644F8 <- ntsc src/enemy_act:actEnemyForceSwitchToCarry (5 syms rebound) — unblocked by the PAL phase-1 `lit4 src/enemy_act` carve
- PORTED `actEnemyFlagCheckActive` w1 @ 0x0016A290 <- ntsc src/enemy_act:funcEnemyCarryFail (2 syms rebound)
- PORTED `actEnemyFlagCheckDead` w1 @ 0x0016A268 <- ntsc src/enemy_act:func_001652D0 (2 syms rebound)
- PORTED `actEnemyFlagOnDead` w1 @ 0x0016A208 <- ntsc src/enemy_act:actEnemyCarry (2 syms rebound)
- PORTED `actEnemyFlagOnFree` w1 @ 0x0016A178 <- ntsc src/enemy_act:actEnemyRun (2 syms rebound)
- REVERTED `actEnemyHyde` w1 @ 0x0016A128 — [codegen] insn 0: expected `lui	v0,0x0` built `addiu	sp,sp,-48`
- REVERTED `actEnemy_GetClingTarget` w3 @ 0x0016A338 — [codegen] insn 1: expected `lw	a0,1664(v1)` built `lw	a0,1648(v1)`
- REVERTED `actEnemy_isLargeEnemy` w3 @ 0x0016A380 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `actEnemy_isNormalEnemy` w3 @ 0x0016A368 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `actEnemy_isSmallEnemy` w3 @ 0x0016A398 — [codegen] insn 1: expected `lw	v1,1664(v0)` built `lw	v1,1648(v0)`
- REVERTED `afterEnemyBodylift` w1 @ 0x0016B010 — [codegen] tu-size: TU .text 0x709C != PAL span 0x70A0 (trailing pad word / extra code)
- PORTED `isEnemyHyde` w1 @ 0x0016AF98 <- ntsc src/fieldCollision:clip_floor_1 (2 syms rebound)
- CARVES `src/enemy_act` — 2 US carve entries to translate:
    - - [0x458E10, .rodata, src/enemy_act]  # full enemy_act .rodata run (anchors: jtbl_00558E40/559000/559130/559150 + D_00558E10..D_005591D8; interior fieldCollision block 0x558F50..0x558F80 is a cross-TU extern), VMA 0x558E10..0x5591F0
    - - [0x530CE0, .lit4, src/enemy_act]     # carved D_00630CE0..D_00630D48 (27 slots, actEnemyForceSwitchToCarry + 26 asm), VMA 0x630CE0..0x630D4C

### src/fieldCollision
- REVERTED `ChangeFieldCollisionDebugMode` w1 @ 0x0016D660 — [codegen] insn 2: expected `addiu	v0,v0,0` built `addiu	v0,v0,4616`
- PORTED `ClipCollision` w1 @ 0x0016D5F0 <- ntsc src/fieldCollision:SetSimplePlane (4 syms rebound)
- PORTED `ClipFloor` w1 @ 0x0016D548 <- ntsc src/fieldCollision:ChangeFieldCollisionDebugMode (2 syms rebound)
- PORTED `ClipFloorCheckCB` w1 @ 0x0016D5C8 <- ntsc src/fieldCollision:GetOrientOfWall (3 syms rebound)
- PORTED `ClipFloorE` w1 @ 0x0016D568 <- ntsc src/fieldCollision:LoadCollision (2 syms rebound)
- PORTED `ClipFloorIH` w1 @ 0x0016D5A8 <- ntsc src/fieldCollision:ClipPlane (2 syms rebound)
- PORTED `ClipFloorR` w1 @ 0x0016D588 <- ntsc src/fieldCollision:DrawCollision (2 syms rebound)
- PORTED `ClipPlane` w1 @ 0x0016D7C8 <- ntsc src/fuzio:fzMagnitude3f (3 syms rebound)
- PORTED `ClipWall` w1 @ 0x0016D3D8 <- ntsc src/fieldCollision:ClipWallBoxStop (2 syms rebound)
- PORTED `ClipWallAdjustPos` w1 @ 0x0016D4B8 <- ntsc src/fieldCollision:ClipFloorR (2 syms rebound)
- PORTED `ClipWallBoxStop` w1 @ 0x0016D498 <- ntsc src/fieldCollision:ClipFloorE (2 syms rebound)
- PORTED `ClipWallCheckCB` w1 @ 0x0016D4F8 <- ntsc src/fieldCollision:ClipFloorCheckCB (3 syms rebound)
- PORTED `ClipWallDebug` w1 @ 0x0016D3B8 <- ntsc src/fieldCollision:ClipWallEField (2 syms rebound)
- PORTED `ClipWallE` w1 @ 0x0016D4D8 <- ntsc src/fieldCollision:ClipFloorIH (2 syms rebound)
- PORTED `ClipWallEField` w1 @ 0x0016D478 <- ntsc src/fieldCollision:ClipFloor (2 syms rebound)
- PORTED `ClipWallField` w1 @ 0x0016D458 <- ntsc src/fieldCollision:ClipWallFieldCheckCB (2 syms rebound)
- PORTED `ClipWallFieldCheckCB` w1 @ 0x0016D520 <- ntsc src/fieldCollision:ClipCollision (3 syms rebound)
- PORTED `ClipWallFuchiHangWalkStop` w1 @ 0x0016D438 <- ntsc src/fieldCollision:ClipWallCheckCB (2 syms rebound)
- PORTED `ClipWallR` w1 @ 0x0016D3F8 <- ntsc src/fieldCollision:ClipWallAdjustPos (2 syms rebound)
- PORTED `ClipWallRD` w1 @ 0x0016F140 <- ntsc src/fuzio:func_0016A130 (3 syms rebound)
- PORTED `ClipWallVector` w1 @ 0x0016F168 <- ntsc src/fuzio:func_0016A158 (3 syms rebound)
- PORTED `ClipWallWaveForce` w1 @ 0x0016D418 <- ntsc src/fieldCollision:ClipWallE (2 syms rebound)
- PORTED `CompareAttribute` w1 @ 0x0016DA90 <- ntsc src/fuzio:func_00168A80 (1 syms rebound)
- PORTED `DBG_VECTOR` w1 @ 0x0016C770 <- ntsc src/fieldCollision:ClipWall (4 syms rebound)
- REVERTED `GetDistanceFromPlane` w1 @ 0x0016DBB0 — [callee-sig-conflict] src/fieldCollision.c:301: conflicting types for `GetDistanceFromPlane'
- PORTED `GetFloorAttribute` w1 @ 0x0016DA70 <- ntsc src/fuzio:fzMagnitudeByLineSeg (1 syms rebound)
- PORTED `GetOrientOfWall` w3 @ 0x0016D8F0 <- ntsc src/fuzio:fzMagnitudefv (8 syms rebound)
- PORTED `GetReflectionElement` w1 @ 0x0016B128 <- ntsc src/fieldCollision:__ClipWall (8 syms rebound)
- PORTED `GetWallAttribute` w1 @ 0x0016DA50 <- ntsc src/fuzio:fzMagnitudeByLine (1 syms rebound)
- PORTED `GetYDistanceFromPlane` w1 @ 0x0016DBE0 <- ntsc src/fuzio:func_00168BD0 (1 syms rebound)
- PORTED `GetYProjectionOfPlane` w1 @ 0x0016DC28 <- ntsc src/fuzio:func_00168C18 (1 syms rebound)
- PORTED `LoadCollision` w1 @ 0x0016D6A0 <- ntsc src/fuzio:fzShowM (2 syms rebound)
- PORTED `MakeExitAttributeIndex` w1 @ 0x0016D068 <- ntsc src/fieldCollision:ClipWallFuchiHangWalkStop (10 syms rebound)
- REVERTED `MapCollisionData` w1 @ 0x0016F1C8 — [codegen] tu-size: TU .text 0x41AC != PAL span 0x41B0 (trailing pad word / extra code)
- PORTED `PositionOfExit` w1 @ 0x0016DC98 <- ntsc src/fuzio:func_00168C88 (3 syms rebound)
- PORTED `ResetCollisionPC` w1 @ 0x0016DC68 <- ntsc src/fuzio:func_00168C58 (10 syms rebound)
- PORTED `SetSimplePlane` w1 @ 0x0016DA38 <- ntsc src/fuzio:fzMagnitude2fv (1 syms rebound)
- PORTED `__ClipFloor` w3 @ 0x0016C268 <- ntsc src/fieldCollision:MakeExitAttributeIndex (4 syms rebound)
- PORTED `__ClipWall` w3 @ 0x0016C240 <- ntsc src/fieldCollision:DrawCollisionRay (4 syms rebound)

### src/fightSound
- PORTED `fightSoundClose` w1 @ 0x0019A490 <- ntsc src/fightSound:fightSoundProcessMain (3 syms rebound)
- REVERTED `fightSoundPlayChk` w2 @ 0x0019A4D8 — [codegen] tu-size: TU .text 0x334 != PAL span 0x338 (trailing pad word / extra code)
- PORTED `fightSoundProcessRequestPause` w2 @ 0x0019A480 <- ntsc src/enemy-control:func_00192040 (2 syms rebound)
- PORTED `fightSoundProcessRequestStart` w2 @ 0x0019A4C8 <- ntsc src/fightSound:fightSoundProcess (2 syms rebound)
- PORTED `fightSoundProcessRequestStatus` w2 @ 0x0019A4D0 <- ntsc src/fightSound:fightSoundProcessRequestPause (2 syms rebound)

### src/flyManager
- REVERTED `DispFlyInfo` w1 @ 0x001DBBE0 — [codegen] insn 9: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `InitFlyInfo` w1 @ 0x001DBC08 <- ntsc src/flag:func_001D03C8 (2 syms rebound)
- PORTED `InitFlyManager` w2 @ 0x001DBC20 <- ntsc src/flyManager:DispFlyInfo (2 syms rebound)

### src/frameDependSequence
- PORTED `ExecuteSEPackage` w1 @ 0x001DCC88 <- ntsc src/frameDependSequence:playSEConditionID (2 syms rebound)
- PORTED `ExecuteSEPackageWithVolumeRate` w1 @ 0x001DCC90 <- ntsc src/frameDependSequence:playEff (3 syms rebound)
- PORTED `StopSEPackage` w2 @ 0x001DCCB8 <- ntsc src/frameDependSequence:ExecFrameDependSequence (2 syms rebound)
- PORTED `StopSEPackageWithGroupVariation` w1 @ 0x001DCCA0 <- ntsc src/frameDependSequence:execEff (2 syms rebound)
- PORTED `checkModelDataID` w1 @ 0x001DD010 <- ntsc src/frameDependSequence:ExecuteSEPackage (1 syms rebound)
- PORTED `checkWaterDepth` w1 @ 0x001DCFF8 <- ntsc src/frameDependSequence:ExecuteSEPackageWithGroupVariation (1 syms rebound)
- PORTED `execSE` w1 @ 0x001DCF90 <- ntsc src/frameDependSequence:executeSEPackageWithNoGObj (4 syms rebound)
- PORTED `execWeaponLightOff` w1 @ 0x001DD0D8 <- ntsc src/girl:func_001D1468 (4 syms rebound)

### src/fuzio
- PORTED `fzMagnitude2f` w1 @ 0x0016F2B0 <- ntsc src/fuzio:func_0016A2A0 (2 syms rebound)
- PORTED `fzMagnitude3f` w1 @ 0x0016F2D8 <- ntsc src/fuzio:func_0016A2C8 (2 syms rebound)
- PORTED `fzMagnitudeByLineSeg` w1 @ 0x0016F470 <- ntsc src/girl_act:GetEyeDirection (3 syms rebound)
- PORTED `fzMagnitudefv` w1 @ 0x0016F308 <- ntsc src/fuzio:func_0016A2F8 (3 syms rebound)

### src/gamesys
- PORTED `func_001B6CA0` w1 @ 0x001B6CA0 <- ntsc src/haveParentSimpleObj:func_001AE1B8 (4 syms rebound)
- PORTED `func_001B6D40` w2 @ 0x001B6D40 <- ntsc src/haveParentSimpleObj:func_001AE258 (5 syms rebound)
- PORTED `func_001B6DF0` w2 @ 0x001B6DF0 <- ntsc src/haveParentSimpleObj:func_001AE308 (5 syms rebound)
- REVERTED `gamesysBackStageProcess` w3 @ 0x001B6C70 — [codegen] insn 1: expected `addiu	a0,zero,148` built `addiu	a0,zero,131`
- PORTED `gamesysGetGirlStageIDAndPosition` w3 @ 0x001B73C8 <- ntsc src/icoMisc:DispIcoMisc (4 syms rebound)
- PORTED `gamesysGirlStageGet` w1 @ 0x001B73A0 <- ntsc src/icoMisc:InitIcoMisc (2 syms rebound)
- PORTED `gamesysMemoryHandlerRead` w1 @ 0x001B7438 <- ntsc src/icoMisc:func_001AE8A0 (2 syms rebound)
- PORTED `gamesysNObjInfoInit` w1 @ 0x001B6F08 <- ntsc src/haveParentSimpleObj:func_001AE370 (2 syms rebound)
- REVERTED `gamesysObjInfoInit` w3 @ 0x001B66A8 — [codegen] insn 17: expected `addiu	a2,zero,424` built `addiu	a2,zero,416`
- REVERTED `gamesysObjInfoLoad` w3 @ 0x001B6798 — [codegen] insn 5: expected `jal	0 <gamesysObjInfoLoad>` built `jal	d90 <gamesysMemoryHandlerRead>`
- PORTED `gamesysObjInfoPosSetStage` w1 @ 0x001B6FB8 <- ntsc src/haveParentSimpleObj:func_001AE420 (2 syms rebound)
- PORTED `gamesysObjInfoStageInitFlagCls` w1 @ 0x001B6F48 <- ntsc src/haveParentSimpleObj:func_001AE3B0 (2 syms rebound)
- PORTED `gamesysObjInfoStageInitPosSaveUnlock` w1 @ 0x001B6F80 <- ntsc src/haveParentSimpleObj:func_001AE3E8 (2 syms rebound)
- PORTED `gamesysStageExitTimeSet` w1 @ 0x001B7418 <- ntsc src/icoMisc:ExitIcoMisc (3 syms rebound)

### src/gather_effect
- REVERTED `GatherEffect_InqEnd` w1 @ 0x001A0560 — [codegen] tu-size: TU .text 0x46C != PAL span 0x470 (trailing pad word / extra code)
- REVERTED `GatherEffect_SetGoal` w3 @ 0x001A0160 — [codegen] insn 10: expected `addiu	a0,v0,80` built `addiu	a0,v0,64`

### src/generator
- REVERTED `GeneratorWorkEnd` w3 @ 0x0019C3B0 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- PORTED `GetbufpGeneratorPacket` w2 @ 0x0019BEB0 <- ntsc src/generator:GetbufpGeneratorPacket (1 syms rebound)
- REVERTED `GetsizeGeneratorPacket` w3 @ 0x0019BEC0 — [codegen] insn 1: expected `addiu	v0,zero,11277` built `addiu	v0,zero,10365`
- PORTED `IsEnableCallEnemyByTargetGObj` w1 @ 0x0019C4E8 <- ntsc src/gv:_RotGVF (2 syms rebound)
- PORTED `LockEnemyGenerate` w1 @ 0x0019C1D0 <- ntsc src/gv:_DistGV (3 syms rebound)
- REVERTED `MemoryGenerator` w3 @ 0x0019BF40 — [codegen] insn 2: expected `lw	a2,2096(a3)` built `lw	a2,2048(a3)`
- PORTED `ResetReviveCountEnemy` w1 @ 0x0019C430 <- ntsc src/gv:func_00193F48 (2 syms rebound)
- REVERTED `RestoreGeneratorExtGeo` w3 @ 0x0019BEE8 — [codegen] insn 6: expected `lw	a2,2096(v0)` built `lw	a2,2048(v0)`
- PORTED `RestoreGeneratorGeo` w1 @ 0x0019BEC8 <- ntsc src/gv:_InterGV (1 syms rebound)
- PORTED `ReturnEnemyToGenerator` w1 @ 0x0019C330 <- ntsc src/gv:_RotyGV (2 syms rebound)
- REVERTED `SearchActiveGenerator` w3 @ 0x0019C3C8 — [codegen] insn 12: expected `lw	v0,2096(v0)` built `lw	v0,2048(v0)`
- PORTED `SetInfoSpKidnapEnemy` w1 @ 0x0019C460 <- ntsc src/gv:_RotGV (2 syms rebound)
- PORTED `SetInfoSpKidnapGenerator` w1 @ 0x0019C450 <- ntsc src/gv:_GetDirection (1 syms rebound)
- PORTED `UnlockEnemyGenerate` w1 @ 0x0019C218 <- ntsc src/gv:_DistxzGV (4 syms rebound)

### src/geometryManager
- PORTED `GetCharGObjList` w2 @ 0x00104A80 <- ntsc src/keyInput:func_00104A38 (2 syms rebound)
- PORTED `GetGlobalDirectionOrient` w1 @ 0x00102FE8 <- ntsc src/geometryManager:GetRootMatrixRotOffset (4 syms rebound)
- PORTED `GetProjectionOfPlane` w1 @ 0x00104988 <- ntsc src/keyInput:func_00104940 (3 syms rebound)
- PORTED `GetProjectionOfPlaneWithKeepAway` w1 @ 0x00104A08 <- ntsc src/keyInput:func_001049C0 (3 syms rebound)
- PORTED `GetProjectionPosOfPlane` w1 @ 0x00104910 <- ntsc src/keyInput:func_001048C8 (3 syms rebound)
- PORTED `GetRootMatrix` w1 @ 0x00104188 <- ntsc src/geometryManager:LocalizeDirectionOrient (3 syms rebound)
- PORTED `GetRootMatrixByDObj` w1 @ 0x00104108 <- ntsc src/geometryManager:cylinderCollisionCheck (3 syms rebound)
- PORTED `GetRootMatrixRotOffset` w2 @ 0x00102A00 <- ntsc src/geometryManager:UpdateRootMatrix (2 syms rebound)
- PORTED `GetRootMatrixRotOffsetByDObj` w1 @ 0x001029C0 <- ntsc src/geometryManager:GetRootQuaternion (3 syms rebound)
- PORTED `GetRootMatrixTransOffset` w1 @ 0x00104738 <- ntsc src/keyInput:func_001046F0 (4 syms rebound)
- PORTED `GetRootMatrixTransOffsetByDObj` w1 @ 0x001046E0 <- ntsc src/keyInput:func_00104698 (4 syms rebound)
- PORTED `GetRootMotionMatrix` w1 @ 0x00104860 <- ntsc src/keyInput:func_00104818 (4 syms rebound)
- PORTED `GetRootMotionOrient` w1 @ 0x00104790 <- ntsc src/keyInput:func_00104748 (6 syms rebound)
- PORTED `GetRootOrient` w1 @ 0x001045D8 <- ntsc src/keyInput:InitKeyInput (6 syms rebound)
- PORTED `GetRootPosition` w1 @ 0x00104550 <- ntsc src/geometryManager:GetRootMatrixByDObj (3 syms rebound)
- PORTED `GetRootPositionByDObj` w1 @ 0x00104208 <- ntsc src/geometryManager:GetCylinderCollision (3 syms rebound)
- PORTED `GetRootQuaternion` w2 @ 0x00102898 <- ntsc src/delayFreeManager:func_00102850 (2 syms rebound)
- REVERTED `GetRootQuaternionByDObj` w1 @ 0x001027D8 — [codegen] insn 13: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `GetRootVelocity` w1 @ 0x00103158 <- ntsc src/geometryManager:SetRootMatrixRotOffset (2 syms rebound)
- PORTED `LocalizeDirectionOrient` w1 @ 0x00103B18 <- ntsc src/geometryManager:GetRootVelocity (5 syms rebound)
- PORTED `SetDirectRootPositionWithNodePoint` w2 @ 0x00102E28 <- ntsc src/geometryManager:SetRootMatrixWithTransOffset (3 syms rebound)
- PORTED `SetRootBaseQuaternion` w1 @ 0x001028A8 <- ntsc src/delayFreeManager:func_00102860 (2 syms rebound)
- PORTED `SetRootMatrixRotOffset` w2 @ 0x00102A80 <- ntsc src/geometryManager:SetRootQuaternion (2 syms rebound)
- PORTED `SetRootMatrixRotOffsetByDObj` w1 @ 0x00102A08 <- ntsc src/geometryManager:SetRootBaseQuaternion (7 syms rebound)
- PORTED `SetRootMatrixWithTransOffset` w2 @ 0x001029B8 <- ntsc src/geometryManager:UpdateRootMatrixByDObj (2 syms rebound)
- PORTED `SetRootMatrixWithTransOffsetByDObj` w1 @ 0x00102938 <- ntsc src/geometryManager:GetRootQuaternionByDObj (6 syms rebound)
- PORTED `UpdateRootMatrix` w2 @ 0x001028A0 <- ntsc src/delayFreeManager:func_00102858 (2 syms rebound)

### src/gflag
- PORTED `gflagChk` w1 @ 0x00181A48 <- ntsc src/way_util:func_0017B230 (2 syms rebound)
- PORTED `gflagOff` w1 @ 0x00181AA0 <- ntsc src/way_util:func_0017B288 (2 syms rebound)
- PORTED `gflagOn` w1 @ 0x00181A70 <- ntsc src/way_util:func_0017B258 (2 syms rebound)

### src/girl
- PORTED `GirlDL` w1 @ 0x001DDC48 <- ntsc src/girl:SetGirlClothDispSwitch (5 syms rebound)

### src/girlForceField
- PORTED `GirlForceFieldGeo` w2 @ 0x001DDF18 <- ntsc src/girlForceField:GirlForceFieldGeo (0 syms rebound)

### src/girl_act
- PORTED `HandMgr_Judge` w1 @ 0x00179300 <- ntsc src/girl_act:actGirlStand (3 syms rebound)
- REVERTED `SetTurnSpeedInEscape` w3 @ 0x0016FC30 — [codegen] insn 3: expected `lw	a0,52(v1)` built `lw	a0,48(v1)`
- REVERTED `actGirlJump` w3 @ 0x0017C8A0 — [codegen] insn 12: expected `sw	v0,52(s0)` built `sw	v0,48(s0)`
- PORTED `afterGirlHand` w1 @ 0x0017C840 <- ntsc src/jimaku:jimakuManager (6 syms rebound)
- PORTED `afterGirlPulledGo` w1 @ 0x0017C880 <- ntsc src/jimaku:jimakuUndisp (1 syms rebound)
- PORTED `afterGirlSupportBGBegin` w2 @ 0x0017C8E8 <- ntsc src/jimaku:func_00176198 (2 syms rebound)
- PORTED `enemy_list_compare` w1 @ 0x0017C6B0 <- ntsc src/jimaku:jimakuEnd (1 syms rebound)
- REVERTED `funcGirlHandDisconnect` w2 @ 0x0016F688 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- PORTED `func_0016FC20` w2 @ 0x0016FC20 <- ntsc src/girl_act:func_0016AC10 (3 syms rebound)
- REVERTED `girlBrainHide_GoalTurn` w3 @ 0x001746F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `girlBrainMain_PositionUpdate` w1 @ 0x00171030 <- ntsc src/girl_act:subGirlControl (6 syms rebound)

### src/gv
- PORTED `AlignDegGV` w1 @ 0x0019CEF8 <- ntsc src/mail-add-data:InitMailAdditionalData (1 syms rebound)
- PORTED `RoundDegGV` w1 @ 0x0019CEA0 <- ntsc src/hand-camera:func_00194960 (1 syms rebound)
- PORTED `SwapGV` w1 @ 0x0019CDE8 <- ntsc src/hand-camera:func_001948A8 (1 syms rebound)
- PORTED `_AbsRotyGV` w1 @ 0x0019CAD0 <- ntsc src/hand-camera:func_00194590 (2 syms rebound)
- PORTED `_DistGV` w1 @ 0x0019C908 <- ntsc src/hand-camera:ClearHandCameraCorrect (4 syms rebound)
- PORTED `_DistSqGV` w1 @ 0x0019C8D8 <- ntsc src/hand-camera:HandyCamera_TargetMoveType (3 syms rebound)
- PORTED `_DistxzGV` w1 @ 0x0019C940 <- ntsc src/hand-camera:InitHandCameraCorrect (4 syms rebound)
- PORTED `_DistxzSqGV` w1 @ 0x0019C8A0 <- ntsc src/hand-camera:RotateAccordingToStick_PatternThree (3 syms rebound)
- REVERTED `_InterGV` w1 @ 0x0019C560 — [callee-sig-conflict] src/gv.c:42: conflicting types for `_InterGV'
- PORTED `_MoveGV` w1 @ 0x0019C980 <- ntsc src/hand-camera:SetLimitHandCameraCorrect (4 syms rebound)
- PORTED `_OrientGV` w1 @ 0x0019CD48 <- ntsc src/hand-camera:func_00194808 (3 syms rebound)
- PORTED `_OrientXZGV` w1 @ 0x0019CD10 <- ntsc src/hand-camera:func_001947D0 (3 syms rebound)

### src/hand-camera
- PORTED `ClearHandCameraCorrect` w1 @ 0x0019D528 <- ntsc src/mail-add-data:ClearMailAdditionalData (4 syms rebound)
- PORTED `InitHandCameraCorrect` w1 @ 0x0019D590 <- ntsc src/mail-add-data:func_00194E28 (4 syms rebound)
- REVERTED `SetLimitHandCameraCorrect` w1 @ 0x0019D610 — [codegen] tu-size: TU .text 0x6DC != PAL span 0x6E0 (trailing pad word / extra code)

### src/haveParentSimpleObj
- PORTED `InitParentSimpleObjGeo` w2 @ 0x001B75F8 <- ntsc src/icoMisc:func_001AEA60 (1 syms rebound)
- PORTED `ParentSimpleObjDL` w2 @ 0x001B75F0 <- ntsc src/icoMisc:func_001AEA58 (2 syms rebound)
- PORTED `ParentSimpleObjGeo` w2 @ 0x001B75E8 <- ntsc src/icoMisc:func_001AEA50 (2 syms rebound)

### src/icoMisc
- PORTED `ExitIcoMisc` w2 @ 0x001B8730 <- ntsc src/kanban:init_textures_of_specified_property (1 syms rebound)

### src/item
- PORTED `avoidInsideOfWall` w1 @ 0x001DE900 <- ntsc src/item:HoldItem (5 syms rebound)
- REVERTED `bombSparkStartSE` w1 @ 0x001DE7E8 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x8 (out-of-line helper or extra code)

### src/itou_boss
- PORTED `CapsuleGhostBossStart` w1 @ 0x001A10F0 <- ntsc src/itou_boss:BossCtrlGeo (2 syms rebound)
- PORTED `InitBossCtrlGeo` w1 @ 0x001A0FE0 <- ntsc src/itou_boss:gene_enemy (13 syms rebound)
- REVERTED `InqCapsuleGhostBossStage` w3 @ 0x001A0ED8 — [codegen] insn 1: expected `addiu	v0,zero,86` built `addiu	v0,zero,84`
- REVERTED `actBossCtrlStart` w1 @ 0x001A0F08 — [codegen] insn 41: expected `addiu	a0,s1,0` built `addiu	a0,s1,808`
- REVERTED `gene_eff_end_func` w3 @ 0x001A11C0 — [codegen] insn 4: expected `lw	v1,112(v0)` built `lw	v1,96(v0)`
- PORTED `itou_boss_gflag_init` w1 @ 0x001A0DB0 <- ntsc src/itou_boss:effect_end_func (3 syms rebound)

### src/itou_gflag
- PORTED `itouGFlagInit` w2 @ 0x001A11E8 <- ntsc src/itou_gflag:itouGflagLoad (2 syms rebound)
- PORTED `itouGflagLoad` w2 @ 0x001A11F0 <- ntsc src/itou_gflag:itouGflagSave (2 syms rebound)
- PORTED `itouGflagSave` w2 @ 0x001A11F8 <- ntsc src/itou_gflag:func_00198430 (1 syms rebound)

### src/itou_sub
- PORTED `apply_matrix_w1` w1 @ 0x001A1470 <- ntsc src/itou_sub:lw_pos_to_ico_pos (1 syms rebound)
- PORTED `ico_m33_to_quat` w1 @ 0x001A14A0 <- ntsc src/itou_sub:apply_matrix_w1 (3 syms rebound)
- PORTED `lw_pos_to_ico_pos` w1 @ 0x001A1440 <- ntsc src/itou_sub:m33_to_quat (1 syms rebound)
- PORTED `pbga_start` w1 @ 0x001A14D8 <- ntsc src/itou_sub:ico_m33_to_quat (3 syms rebound)

### src/jimaku
- PORTED `iosCdvdBackGroundReadJimaku` w1 @ 0x0017CB20 <- ntsc src/jimaku:func_00176398 (3 syms rebound)
- PORTED `jimakuBegin` w1 @ 0x0017D2D8 <- ntsc src/jimaku:func_00176AE8 (3 syms rebound)
- PORTED `jimakuEnd` w2 @ 0x0017D3A8 <- ntsc src/way_sys:avoid_obstacle2 (3 syms rebound)
- PORTED `jimakuMgrEnd` w1 @ 0x0017D290 <- ntsc src/jimaku:func_00176AA0 (6 syms rebound)
- PORTED `jimakuNext` w1 @ 0x0017D2F8 <- ntsc src/jimaku:func_00176B08 (4 syms rebound)

### src/kanban
- PORTED `kanbanReqAllDel` w1 @ 0x001B9130 <- ntsc src/kanban:kanbanExec (4 syms rebound)
- PORTED `kanbanReqAllDelFade` w1 @ 0x001B9168 <- ntsc src/kanban:func_001B0570 (2 syms rebound)
- PORTED `kanbanReqDel` w1 @ 0x001B90D8 <- ntsc src/kanban:kanbanReqAllDel (2 syms rebound)
- PORTED `kanbanReqDelFade` w1 @ 0x001B9110 <- ntsc src/kanban:kanbanReqAllDelFade (2 syms rebound)

### src/kanbanBoot
- PORTED `kanbanBootInit` w1 @ 0x001B9A78 <- ntsc src/kanban:func_001B0A38 (6 syms rebound)
- REVERTED `kanbanBootStart` w2 @ 0x001B9A98 — [codegen] tu-size: TU .text 0x7D4 != PAL span 0x7D8 (trailing pad word / extra code)

### src/layout_action
- REVERTED `CUR_SE` w3 @ 0x001B9AD8 — [codegen] insn 1: expected `addiu	a0,zero,411` built `addiu	a0,zero,399`
- REVERTED `NEGATIVE_SE` w3 @ 0x001B9AC0 — [codegen] insn 1: expected `addiu	a0,zero,413` built `addiu	a0,zero,401`
- REVERTED `POSITIVE_SE` w3 @ 0x001B9AA8 — [codegen] insn 1: expected `addiu	a0,zero,412` built `addiu	a0,zero,400`
- PORTED `PSH_POSITIVE_OR_NEGATIVE` w1 @ 0x001BEC40 <- ntsc src/layout_texture:func_001B59D0 (2 syms rebound)
- PORTED `keyconfig_reset` w1 @ 0x001BEC80 <- ntsc src/layout_texture:display_primary_texture_layout (3 syms rebound)
- REVERTED `la_TESTFUNCTION` w2 @ 0x001B9AF0 — [codegen] insn 0: expected `lui	a0,0x0` built `j	0 <POSITIVE_SE>`
- PORTED `la_boot_confirm_memory_card` w1 @ 0x001BE238 <- ntsc src/layout_action:la_vibe_select (3 syms rebound)
- PORTED `la_boot_no_free_area` w2 @ 0x001BE208 <- ntsc src/layout_action:_la_set_current_port_new (3 syms rebound)
- PORTED `la_boot_no_memory_card` w2 @ 0x001BE1D8 <- ntsc src/layout_action:_la_set_current_port_lock_2 (3 syms rebound)
- REVERTED `la_delete_confirm` w3 @ 0x001BE930 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `la_delete_confirm_complete` w3 @ 0x001BE988 — [codegen] insn 10: expected `addiu	v0,zero,30` built `addiu	v0,zero,26`
- PORTED `la_delete_confirm_fail` w2 @ 0x001BE9C8 <- ntsc src/layout_action:la_format_confirm (1 syms rebound)
- PORTED `la_format_confirm_fail` w2 @ 0x001BE878 <- ntsc src/layout_action:progressive_bar (1 syms rebound)
- REVERTED `la_game_demo_pause` w3 @ 0x001BEAD0 — [codegen] insn 14: expected `addiu	v0,zero,55` built `addiu	v0,zero,51`
- PORTED `la_game_loading` w1 @ 0x001BE9D0 <- ntsc src/layout_action:la_system_save_processing (2 syms rebound)
- PORTED `la_general_mc_confirm` w1 @ 0x001BE478 <- ntsc src/layout_action:la_load_confirm_no_memory_card (3 syms rebound)
- PORTED `la_mc_preview_info` w1 @ 0x001BE2E0 <- ntsc src/layout_action:la_load_game_memory_card_check (4 syms rebound)
- REVERTED `la_playtime_count` w3 @ 0x001BE9E8 — [codegen] insn 5: expected `lw	v0,8(v1)` built `lw	v0,4(v1)`
- PORTED `la_save_confirm_fail` w2 @ 0x001BE870 <- ntsc src/layout_action:la_save_game_memory_card_check (1 syms rebound)
- PORTED `la_save_confirm_yesno` w1 @ 0x001BEC08 <- ntsc src/layout_texture:texture_fading (3 syms rebound)
- REVERTED `la_scei_logo` w3 @ 0x001BE270 — [codegen] insn 16: expected `addiu	a0,zero,386` built `addiu	a0,zero,353`
- PORTED `la_switching_stage` w1 @ 0x001BEBC8 <- ntsc src/layout_texture:default_item_select (5 syms rebound) — unblocked by the PAL phase-1 `lit4 src/layout_action` carve
- PORTED `la_title_demo` w2 @ 0x001BE2D8 <- ntsc src/layout_action:la_title_new_game_only (1 syms rebound)
- CARVES `src/layout_action` — 1 US carve entry to translate:
    - - [0x517170, .rodata, src/layout_action]  # full layout_action .rodata run (D_00617170..D_00617198 + gcc-emitted jtbl_006171B0, la_load_processing switch, 5 entries 0x14), VMA 0x617170..0x6171C4

### src/layout_texture
- PORTED `lt_current_property_item` w2 @ 0x001C0D28 <- ntsc src/layout_texture:lt_set_item_select_func (2 syms rebound)
- PORTED `lt_fade_status` w2 @ 0x001C0F90 <- ntsc src/sceneManager:InitStageLight (2 syms rebound)
- REVERTED `lt_mask_property` w3 @ 0x001C0F20 — [codegen] insn 0: expected `addiu	v0,zero,112` built `addiu	v0,zero,108`
- PORTED `lt_set_fade_mode` w2 @ 0x001C0FA0 <- ntsc src/sceneManager:initParentLink (2 syms rebound)
- PORTED `lt_set_item_select_func` w2 @ 0x001C0F98 <- ntsc src/sceneManager:initSceneGObj (2 syms rebound)

### src/lightning
- PORTED `DrawLightning` w1 @ 0x001A2580 <- ntsc src/lightning:DrawLightning2 (3 syms rebound)
- PORTED `apply_m34` w1 @ 0x001A2558 <- ntsc src/lightning:set_vertex (1 syms rebound)
- PORTED `cmpr` w1 @ 0x001A2760 <- ntsc src/lightning:apply_m34 (1 syms rebound)

### src/lineManager
- PORTED `Draw2DLineSeg_Start` w1 @ 0x001E0960 <- ntsc src/lodManager:SetLodLevel (3 syms rebound)
- PORTED `DrawLine` w1 @ 0x001E0FD8 <- ntsc src/lodManager:func_001D49C0 (4 syms rebound)

### src/main
- PORTED `movie_abort_check` w1 @ 0x00102500 <- ntsc src/delayFreeManager:func_001024B8 (5 syms rebound)

### src/matrixDrive
- PORTED `AddVectorXYZ` w1 @ 0x00105FC0 <- ntsc src/matrixDrive:MatrixDrive_TurnZObjectMatrixXY (1 syms rebound)
- PORTED `CopyIVector` w2 @ 0x00105F58 <- ntsc src/matrixDrive:MatrixDrive_TurnXObjectMatrixZY (1 syms rebound)
- PORTED `CopyMatrix` w1 @ 0x00105F68 <- ntsc src/matrixDrive:MatrixDrive_TurnXObjectMatrixYZ (1 syms rebound)
- PORTED `CopyMatrixUncached` w1 @ 0x00105F90 <- ntsc src/matrixDrive:MatrixDrive_TurnYObjectMatrixXZ (1 syms rebound)
- PORTED `CopyVector` w2 @ 0x00105F48 <- ntsc src/matrixDrive:MatrixDrive_TurnObjectMatrix (1 syms rebound)
- PORTED `FSqrt` w1 @ 0x00106028 <- ntsc src/matrixDrive:MatrixDrive_GetTurnYAngleXZ (1 syms rebound)
- REVERTED `GetPointDistance` w1 @ 0x00106090 — [codegen] tu-size: TU .text 0x119C != PAL span 0x11A0 (trailing pad word / extra code)
- REVERTED `InitMatrixDrive` w1 @ 0x00104F38 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `MatrixDrive_GetLastMatrix` w2 @ 0x001052D8 <- ntsc src/keyInput:func_00105290 (3 syms rebound)
- PORTED `MatrixDrive_GetMatrix` w2 @ 0x001052C0 <- ntsc src/keyInput:func_00105278 (3 syms rebound)
- PORTED `MatrixDrive_GetTurnYEAngleXZ` w1 @ 0x00105B10 <- ntsc src/matrixDrive:MatrixDrive_PopMatrix (4 syms rebound) — unblocked by the PAL phase-1 `lit4 src/matrixDrive` carve
- PORTED `MatrixDrive_PopMatrix` w1 @ 0x001052B0 <- ntsc src/keyInput:func_00105268 (2 syms rebound)
- PORTED `MatrixDrive_PushMatrix` w1 @ 0x00104F68 <- ntsc src/keyInput:func_00104F20 (4 syms rebound)
- PORTED `MatrixDrive_PushMatrixWithNoCopy` w1 @ 0x001052A0 <- ntsc src/keyInput:func_00105258 (2 syms rebound)
- PORTED `MatrixDrive_RotMatrixX` w1 @ 0x00104F90 <- ntsc src/keyInput:func_00104F48 (7 syms rebound)
- PORTED `MatrixDrive_RotMatrixY` w1 @ 0x00105008 <- ntsc src/keyInput:func_00104FC0 (7 syms rebound)
- PORTED `MatrixDrive_RotMatrixZ` w1 @ 0x00105080 <- ntsc src/keyInput:func_00105038 (7 syms rebound)
- PORTED `MatrixDrive_ScaleMatrix` w1 @ 0x001050F8 <- ntsc src/keyInput:func_001050B0 (5 syms rebound)
- PORTED `MatrixDrive_TransMatrix` w1 @ 0x00105350 <- ntsc src/keyInput:func_00105308 (5 syms rebound)
- PORTED `MatrixDrive_TransMatrixV` w1 @ 0x001052F0 <- ntsc src/keyInput:func_001052A8 (5 syms rebound)
- PORTED `SubVectorXYZ` w1 @ 0x00105FD8 <- ntsc src/matrixDrive:MatrixDrive_GetTurnXAngleZY (1 syms rebound)
- PORTED `UnitRotation` w1 @ 0x00105FF0 <- ntsc src/matrixDrive:MatrixDrive_GetTurnXAngleYZ (2 syms rebound)
- PORTED `VectorLength` w1 @ 0x00106048 <- ntsc src/matrixDrive:MatrixDrive_GetTurnYEAngleXZ (1 syms rebound)
- PORTED `VectorLengthSquare` w1 @ 0x00106070 <- ntsc src/matrixDrive:MatrixDrive_GetTurnZAngleXY (1 syms rebound)
- CARVES `src/matrixDrive` — 1 US carve entry to translate:
    - - [0x53090C, .lit4, src/matrixDrive]    # carved D_0063090C..D_00630940 (14 slots, MatrixDrive_PopMatrix + 13 asm), VMA 0x63090C..0x630944

### src/motionFileManager
- PORTED `AddMotionMemorySize` w1 @ 0x001E13F0 <- ntsc src/lodManager:func_001D4DA8 (3 syms rebound)
- PORTED `CheckMotionIncludeFacialData` w1 @ 0x001E14B8 <- ntsc src/motionFileManager:InitMotionFile (1 syms rebound)
- PORTED `GetMotionMemorySize` w1 @ 0x001E1418 <- ntsc src/lodManager:func_001D4DD0 (3 syms rebound)
- PORTED `InitMotionMemorySize` w2 @ 0x001E13E0 <- ntsc src/lodManager:func_001D4D98 (3 syms rebound)
- REVERTED `ResetStatic2MotionManager` w3 @ 0x001E1478 — [codegen] insn 5: expected `addiu	a1,zero,1146` built `addiu	a1,zero,1085`

### src/motionManager
- PORTED `GetWallVector` w1 @ 0x001ED610 <- ntsc src/motionOrientManager:UpdateFrameCounter (2 syms rebound)
- REVERTED `ResetMotionProgramInterpInfo` w3 @ 0x001ED390 — [codegen] insn 8: expected `lw	v1,2060(a1)` built `lw	v1,2012(a1)`
- REVERTED `SetDirectMotionProgramInterpInfo` w3 @ 0x001ED400 — [codegen] insn 10: expected `lw	v1,2060(a1)` built `lw	v1,2012(a1)`
- PORTED `SetHitCollisionDisplay` w2 @ 0x001ED380 <- ntsc src/motionManager:func_001E0978 (3 syms rebound)
- REVERTED `avoidSideAdjustWall` w1 @ 0x001E9FD8 — [undeclared] src/motionManager.c:10: `D_0063C490' undeclared (first use in this function)
- PORTED `checkCliffAndWallStateAtJump` w1 @ 0x001E6518 <- ntsc src/motionManager:_checkCliffAndWall (7 syms rebound)
- PORTED `checkCliffAndWallStateOfLastPlane` w1 @ 0x001E6478 <- ntsc src/motionManager:checkCliffState (12 syms rebound)
- PORTED `checkSideWall` w3 @ 0x001E9090 <- ntsc src/motionManager:SkelTest (11 syms rebound)
- PORTED `checkUpperWallState` w1 @ 0x001E54C8 <- ntsc src/motionManager:checkActPointWithHeight (13 syms rebound)
- PORTED `checkWallUpperWall` w1 @ 0x001E92A8 <- ntsc src/motionManager:GetWallVector (10 syms rebound)
- REVERTED `dispLastNode` w1 @ 0x001E66D0 — [arity] src/motionManager.c:122: too many arguments to function `dispSquare2'
- REVERTED `dispSquare2` w1 @ 0x001E14D0 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0xB8 (out-of-line helper or extra code)
- PORTED `forceFallDown` w1 @ 0x001E9248 <- ntsc src/motionManager:SkelTestGeo (5 syms rebound)
- REVERTED `forceReset` w3 @ 0x001E9278 — [codegen] insn 3: expected `addiu	a1,zero,259` built `addiu	a1,zero,243`
- REVERTED `getGeometryOfMotion` w1 @ 0x001ED6A0 — [codegen] tu-size: TU .text 0xC284 != PAL span 0xC288 (trailing pad word / extra code)
- PORTED `pursueNaturalGeometry` w1 @ 0x001ED560 <- ntsc src/motionOrientManager:execFrameTrigger (8 syms rebound)
- PORTED `upperFieldCheck` w1 @ 0x001ED640 <- ntsc src/motionOrientManager:sendStateMail (3 syms rebound)

### src/motionManager2
- PORTED `AdjustMotionHeightToField` w1 @ 0x00106BA8 <- ntsc src/motionManager2:_GetMotionDirection (4 syms rebound)
- PORTED `AdjustRootPositionToVerticalSidePlaneOfWall` w1 @ 0x0010ABD0 <- ntsc src/pool:setNodePursueParticleEffectWithUpperLimit (8 syms rebound)
- PORTED `CheckFloorAttribute` w1 @ 0x0010A040 <- ntsc src/motionManager2:ForMotionViewer_GetCurrentAnimationFrame (2 syms rebound)
- PORTED `CheckPureCliffAttribute` w1 @ 0x0010A0A0 <- ntsc src/motionManager2:DisableMotionOrientUpdate (2 syms rebound)
- PORTED `CheckPureWallAttribute` w1 @ 0x0010A080 <- ntsc src/motionManager2:EnableMotionOrientUpdate (2 syms rebound)
- PORTED `CheckWallAttribute` w1 @ 0x0010A060 <- ntsc src/motionManager2:ForMotionViewer_GetCurrentMotion (2 syms rebound)
- REVERTED `ClearMotionBlendlessNode` w3 @ 0x00109E40 — [codegen] insn 4: expected `lw	a2,2080(v1)` built `lw	a2,2032(v1)`
- PORTED `ClearMotionGeometryInfo` w1 @ 0x0010A4E8 <- ntsc src/motionManager2:InitMotionRotElem (4 syms rebound)
- PORTED `CopyMotion` w1 @ 0x0010A550 <- ntsc src/motionManager2:GetRootProjectionPosOfGObj (1 syms rebound)
- PORTED `DisableChangeRootUpdateMode` w1 @ 0x0010A2D8 <- ntsc src/motionManager2:GetDifferenceFromLastField (1 syms rebound)
- PORTED `DisableMotionOrientUpdate` w1 @ 0x0010A030 <- ntsc src/motionManager2:SetRootUpdateMode (1 syms rebound)
- PORTED `EnableChangeRootUpdateMode` w1 @ 0x0010A2E8 <- ntsc src/motionManager2:GetDifferenceFromLowerField (1 syms rebound)
- PORTED `EnableMotionOrientUpdate` w1 @ 0x0010A020 <- ntsc src/motionManager2:AdjustMotionHeightToNearestField (1 syms rebound)
- REVERTED `FeedbackWallWorkInfoToBrainSystem` w3 @ 0x00109998 — [codegen] insn 11: expected `sdl	a0,1575(v1)` built `sdl	a0,1559(v1)`
- PORTED `ForMotionViewer_GetCurrentAnimationFrame` w1 @ 0x0010A000 <- ntsc src/motionManager2:InitMotionStateInfo (1 syms rebound)
- PORTED `ForMotionViewer_GetCurrentMotion` w1 @ 0x0010A010 <- ntsc src/motionManager2:GetSkeltonFocusNode (1 syms rebound)
- PORTED `GetBlendedMotionRootPos` w1 @ 0x0010ACC0 <- ntsc src/pool:GetPoolGlobalDrainVector (1 syms rebound)
- PORTED `GetCollisionOfLastActiveField` w1 @ 0x001099E8 <- ntsc src/motionManager2:MakeMirrorMotion (1 syms rebound)
- REVERTED `GetDifferenceFromLastField` w3 @ 0x0010A158 — [codegen] insn 3: expected `lw	v1,2112(v0)` built `lw	v1,2064(v0)`
- REVERTED `GetDifferenceFromLowerField` w3 @ 0x0010A198 — [codegen] insn 4: expected `lw	v1,2112(v0)` built `lw	v1,2064(v0)`
- REVERTED `GetDifferenceFromWallUpperField` w3 @ 0x0010A118 — [codegen] insn 3: expected `lw	v1,2112(v0)` built `lw	v1,2064(v0)`
- PORTED `GetHeightOfCliffFromGObj` w1 @ 0x0010A388 <- ntsc src/motionManager2:GetMotionFrameFlag1 (1 syms rebound)
- PORTED `GetHeightOfFieldPlaneDifference` w1 @ 0x0010A328 <- ntsc src/motionManager2:EnableChangeRootUpdateMode (2 syms rebound)
- PORTED `GetHeightOfWallFromGObj` w1 @ 0x0010A378 <- ntsc src/motionManager2:GetRopeHangablePos (1 syms rebound)
- PORTED `GetLowerPlaneCollision` w2 @ 0x00106BE8 <- ntsc src/motionManager2:SetMotionDirectionWithLimit (4 syms rebound) — unblocked by the PAL phase-1 `lit4 src/motionManager2` carve
- PORTED `GetMotionFrameFlag1` w1 @ 0x0010A308 <- ntsc src/motionManager2:GetDifferenceFromWallUpperPlane (1 syms rebound)
- PORTED `GetMotionFrameFlag2` w1 @ 0x0010A318 <- ntsc src/motionManager2:DisableChangeRootUpdateMode (1 syms rebound)
- PORTED `GetMotionPointer` w1 @ 0x001099D8 <- ntsc src/motionManager2:GetFloatingMotion (1 syms rebound)
- PORTED `GetMotionRootPos` w1 @ 0x0010A590 <- ntsc src/motionManager2:SetMotionPlaySpeedRatio (1 syms rebound)
- PORTED `GetOrientOfCliffOfGObj` w1 @ 0x001068E8 <- ntsc src/motionManager2:CheckFieldContact (2 syms rebound)
- PORTED `GetOrientOfWallOfGObj` w1 @ 0x001068D8 <- ntsc src/motionManager2:GetWaterReaction (2 syms rebound)
- PORTED `GetOutOutsideOfWall` w1 @ 0x0010AB20 <- ntsc src/pool:flushWork (5 syms rebound)
- PORTED `GetRootPosOfNextFrame` w1 @ 0x00106B60 <- ntsc src/motionManager2:SetMotionDirection (3 syms rebound)
- PORTED `GetRootProjectionPosOfGObj` w1 @ 0x0010A490 <- ntsc src/motionManager2:GetHeightOfWallFromGObj (2 syms rebound)
- PORTED `GetRopeHangablePos` w1 @ 0x0010A2F8 <- ntsc src/motionManager2:GetDifferenceFromWallLowerPlane (1 syms rebound)
- PORTED `GetShapeMotion` w1 @ 0x0010AA98 <- ntsc src/motionManager2:GetMotionRootPos (1 syms rebound)
- REVERTED `GetSkeltonFocusNode` w3 @ 0x00109F08 — [codegen] insn 1: expected `lw	v1,2112(v0)` built `lw	v1,2064(v0)`
- PORTED `GetStreamShapeMotion` w1 @ 0x0010A0C0 <- ntsc src/motionManager2:CheckFloorAttribute (1 syms rebound)
- PORTED `InitMotionRotElem` w1 @ 0x0010A398 <- ntsc src/motionManager2:GetMotionFrameFlag2 (2 syms rebound)
- PORTED `InitMotionStateInfo` w1 @ 0x00109E80 <- ntsc src/motionManager2:DebugDisp1Collision (3 syms rebound)
- PORTED `LockForceGroundParent` w2 @ 0x0010AB10 <- ntsc src/pool:falldownSE (1 syms rebound)
- PORTED `MakeMirrorMotion` w1 @ 0x001095E0 <- ntsc src/motionManager2:GetStreamMotion (4 syms rebound)
- PORTED `SetMotionDirection` w1 @ 0x001068F8 <- ntsc src/motionManager2:dispPlane (4 syms rebound)
- PORTED `SetMotionPlaySpeedRatio` w1 @ 0x0010A4D8 <- ntsc src/motionManager2:GetHeightOfCliffFromGObj (1 syms rebound)
- PORTED `SetRootUpdateMode` w1 @ 0x00109FF0 <- ntsc src/motionManager2:ClearMotionBlendlessNode (1 syms rebound)
- PORTED `SetSkeltonDispSwitch` w2 @ 0x0010A548 <- ntsc src/motionManager2:SetMotionNodeFixModeParameter (2 syms rebound)
- PORTED `UnlockForceGroundParent` w2 @ 0x0010AB18 <- ntsc src/pool:copyToWork (1 syms rebound)
- PORTED `_GetMotionDirection` w1 @ 0x001069B0 <- ntsc src/motionManager2:GetOrientOfWallOfGObj (2 syms rebound)
- PORTED `fitYToPlane` w1 @ 0x0010AC80 <- ntsc src/pool:SetFallDownSplash (2 syms rebound)
- PORTED `getLowerPlaneCollisionE` w2 @ 0x00106C30 <- ntsc src/motionManager2:GetRootPosOfNextFrame (4 syms rebound) — unblocked by the PAL phase-1 `lit4 src/motionManager2` carve
- PORTED `getVerticalElementOfWallNormal` w1 @ 0x00107C18 <- ntsc src/motionManager2:DispSkelton (3 syms rebound)
- CARVES `src/motionManager2` — 2 US carve entries to translate:
    - - [0x453DB0, .rodata, src/motionManager2]  # gcc-emitted jtbl_00553DB0 (AdjustVerticalSidePlaneOfWall switch, 6 entries 0x18), VMA 0x553DB0..0x553DC8
    - - [0x530944, .lit4, src/motionManager2]# carved D_00630944..D_00630980 (16 slots, SetMotionDirectionWithLimit + GetRootPosOfNextFrame + 14 asm), VMA 0x630944..0x630984

### src/motionOrientManager
- REVERTED `ExecutePauseSlipProc` w1 @ 0x001F17B8 — [codegen] tu-size: TU .text 0x4094 != PAL span 0x4098 (trailing pad word / extra code)
- REVERTED `ExecuteSlipProc` w3 @ 0x001F16E8 — [codegen] insn 16: expected `addiu	a1,zero,114` built `addiu	a1,zero,109`
- PORTED `ForTest_ForceShiftMotion` w1 @ 0x001EEDA8 <- ntsc src/motionOrientManager:getStreamMotionGeometry (2 syms rebound)
- REVERTED `GetMotionPlaySpeedRatio` w3 @ 0x001EDAF8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- PORTED `SetParallelMotionTableWithNoRequest` w1 @ 0x001F1588 <- ntsc src/motionOrientManager:func_001E4700 (1 syms rebound)

### src/motionViewer
- PORTED `setMotionSpeed` w2 @ 0x001F1800 <- ntsc src/motionViewer:dispMotFrameProgress (3 syms rebound)
- REVERTED `setRootUpdateMode` w1 @ 0x001F17F0 — [codegen] insn 3: expected `<end>` built `sll	zero,zero,0x0`

### src/moveColTest
- PORTED `MoveColTestDL` w2 @ 0x001F3840 <- ntsc src/moveColTest:InitMoveColTestGeo (2 syms rebound)

### src/multiBgaManager
- PORTED `DispMultiBgaManager` w1 @ 0x001F3A50 <- ntsc src/multiBgaManager:DispMultiBgaManager (3 syms rebound)

### src/objact
- REVERTED `ObjAction_CorrectGeo` w3 @ 0x00257318 — [codegen] insn 21: expected `addiu	v0,zero,972` built `addiu	v0,zero,815`
- PORTED `ObjAction_Mail` w1 @ 0x00257398 <- ntsc ito/mpeg/mv_disp:setPRIM (4 syms rebound)
- REVERTED `ObjAction_MailCenter` w3 @ 0x00257400 — [codegen] insn 49: expected `slti	v0,s1,33` built `slti	v0,s1,31`
- PORTED `ObjectBeforeFunc` w2 @ 0x00257310 <- ntsc ito/mpeg/mv_disp:setTEX1_1 (2 syms rebound)

### src/op
- REVERTED `actSt26aConte01_1_newgame` w3 @ 0x00220F38 — [codegen] insn 13: expected `addiu	a0,zero,382` built `addiu	a0,zero,349`
- PORTED `actSubMpegReturnPreload` w1 @ 0x00220EB8 <- ntsc src/st00a:actSt00aStair (5 syms rebound)

### src/particleEffect
- REVERTED `DeleteParticleEffectsByID` w3 @ 0x001F5558 — [codegen] insn 12: expected `addiu	s2,s0,3584` built `addiu	s2,s0,3072`
- REVERTED `DisableParticleEffectGeometryControl` w3 @ 0x001F5620 — [codegen] insn 0: expected `addiu	v1,zero,28` built `addiu	v1,zero,24`
- REVERTED `GetParticleEffectData` w3 @ 0x001F5600 — [codegen] insn 0: expected `addiu	v0,zero,28` built `addiu	v0,zero,24`
- PORTED `GetParticleEffectPackage` w1 @ 0x001F54A8 <- ntsc src/particleEffect:DeleteParticleEffectsByID (2 syms rebound)
- REVERTED `GetParticleIDWithName` w3 @ 0x001F5640 — [codegen] insn 17: expected `slti	v0,s0,61` built `slti	v0,s0,53`
- PORTED `GetParticleLoopFlag` w1 @ 0x001F56B0 <- ntsc src/particleLayout:func_001E8DE0 (2 syms rebound)
- PORTED `SetParticleEffect` w1 @ 0x001F5418 <- ntsc src/particleEffect:func_001E8B48 (3 syms rebound)
- REVERTED `SetParticleEffectGeometry` w3 @ 0x001F4E48 — [codegen] insn 1: expected `addiu	v0,zero,28` built `addiu	v0,zero,24`
- PORTED `SetParticleEffectPackage` w1 @ 0x001F51A0 <- ntsc src/particleEffect:InitParticleEffects (6 syms rebound)
- REVERTED `SetParticleEffectUpperLimit` w3 @ 0x001F4E88 — [codegen] insn 2: expected `addiu	a0,zero,28` built `addiu	a0,zero,24`
- REVERTED `setParticleEffectGeometry` w1 @ 0x001F3C48 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x38 (out-of-line helper or extra code)

### src/particleLayout
- PORTED `ParticleLayoutDL` w2 @ 0x001F5850 <- ntsc src/particleLayout:func_001E8F28 (1 syms rebound)

### src/poly-flat
- PORTED `DrawPolygon` w1 @ 0x0019E138 <- ntsc src/poly-flat:after_DrawPolygon (4 syms rebound)
- PORTED `IsPointIsInScreen` w1 @ 0x0019E2C8 <- ntsc src/poly-flat:before_DrawLine (6 syms rebound)
- PORTED `after_DrawLine` w2 @ 0x0019E130 <- ntsc src/poly-flat:before_DrawPolygon (2 syms rebound)
- PORTED `after_DrawPolygon` w2 @ 0x0019DFE8 <- ntsc src/mail-add-data:func_00195230 (2 syms rebound)
- PORTED `before_DrawLine` w1 @ 0x0019E108 <- ntsc src/mail-add-data:func_00195350 (4 syms rebound)
- REVERTED `before_DrawPolygon` w1 @ 0x0019DFC0 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x28 (out-of-line helper or extra code)

### src/pool
- REVERTED `CheckPoolHasGridMesh` w3 @ 0x0010D148 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `GetPoolGlobalDrainVector` w3 @ 0x0010B2B8 — [codegen] insn 1: expected `lw	a1,2096(v0)` built `lw	a1,2048(v0)`
- REVERTED `GetPoolGlobalHeight` w3 @ 0x0010D040 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- PORTED `PoolGeo` w2 @ 0x0010D038 <- ntsc src/pool:func_0010D070 (1 syms rebound)
- REVERTED `falldownSE` w3 @ 0x0010ADC0 — [codegen] insn 1: expected `addiu	a1,zero,86` built `addiu	a1,zero,81`
- PORTED `flushWork` w1 @ 0x0010AF40 <- ntsc src/pool:PoolDL (12 syms rebound)
- REVERTED `poolRideFunc` w3 @ 0x0010D300 — [codegen] insn 5: expected `lw	v1,2096(a0)` built `lw	v1,2048(a0)`
- PORTED `setNodePursueParticleEffectWithUpperLimit` w1 @ 0x0010B038 <- ntsc src/pool:InitLimitedPoolReflactionMesh (5 syms rebound)

### src/quaternion
- PORTED `DivQuaternion` w1 @ 0x0010DDC0 <- ntsc src/tableSin:func_0010DDF8 (3 syms rebound)
- PORTED `GetCurrentQuaternion` w2 @ 0x0010DA68 <- ntsc src/quaternion:GetLastQuaternion (3 syms rebound)
- PORTED `GetInverseQuaternion` w1 @ 0x0010D800 <- ntsc src/quaternion:RegularizeQuaternion (3 syms rebound)
- PORTED `GetLastQuaternion` w2 @ 0x0010DA80 <- ntsc src/tableSin:GetTableSin (3 syms rebound)
- PORTED `GetMatrixFromQuaternion` w1 @ 0x0010D508 <- ntsc src/quaternion:getQuaternionFromMatrix (4 syms rebound)
- PORTED `GetMatrixFromQuaternionPos` w1 @ 0x0010DE88 <- ntsc src/tableSin:func_0010DEC0 (3 syms rebound)
- PORTED `GetMatrixFromQuaternionRotElem` w1 @ 0x0010DE08 <- ntsc src/tableSin:func_0010DE40 (2 syms rebound)
- PORTED `GetQuaternionCosRadian` w1 @ 0x0010E8F0 <- ntsc src/DisplayP2O:p2o_TransMicroProgram (1 syms rebound)
- PORTED `GetQuaternionFromMatrix` w1 @ 0x0010D7C0 <- ntsc src/quaternion:CopyQuaternion (3 syms rebound)
- REVERTED `GetQuaternionMagnitude` w1 @ 0x0010E6D0 — [codegen] insn 12: expected `ld	ra,0(sp)` built `trunc.w.s	$f1,$f0`
- PORTED `GetSlerpQuaternion` w2 @ 0x0010DA40 <- ntsc src/quaternion:GetCurrentQuaternion (3 syms rebound)
- PORTED `InitQuaternionDrive` w2 @ 0x0010D4E8 <- ntsc src/quaternion:SetIdentityQuaternion (4 syms rebound)
- PORTED `InvertCurrentQuaternion` w1 @ 0x0010D3D0 <- ntsc src/quaternion:SetCurrentQuaternion (4 syms rebound)
- REVERTED `MultiCurrentQuaternion` w1 @ 0x0010D3A8 — [codegen] insn 7: expected `j	0 <MultiCurrentQuaternion>` built `j	9d8 <MultiQuaternion>`
- PORTED `MultiMatrixByQuaternion` w1 @ 0x0010DF38 <- ntsc src/tableSin:func_0010DF70 (4 syms rebound)
- PORTED `MultiQuaternion` w1 @ 0x0010DD80 <- ntsc src/tableSin:func_0010DDB8 (1 syms rebound)
- PORTED `PopQuaternion` w1 @ 0x0010DAF0 <- ntsc src/tableSin:InitTableSin (4 syms rebound)
- PORTED `PushQuaternion` w1 @ 0x0010D470 <- ntsc src/quaternion:InitQuaternionDrive (8 syms rebound)
- PORTED `PushQuaternionWithNoCopy` w1 @ 0x0010DA98 <- ntsc src/tableSin:GetTableCos (6 syms rebound)
- PORTED `RegularizeQuaternion` w1 @ 0x0010D840 <- ntsc src/quaternion:GetSlerpQuaternionNoRegularize (3 syms rebound)
- PORTED `RotCurrentQuaternionX` w2 @ 0x0010D410 <- ntsc src/quaternion:RotCurrentQuaternionY (4 syms rebound)
- PORTED `RotCurrentQuaternionY` w2 @ 0x0010D430 <- ntsc src/quaternion:RotCurrentQuaternionZ (4 syms rebound)
- PORTED `RotCurrentQuaternionZ` w2 @ 0x0010D450 <- ntsc src/quaternion:PushQuaternion (4 syms rebound)
- PORTED `RotQuaternionEAX` w1 @ 0x0010E260 <- ntsc src/tableSin:func_0010E298 (3 syms rebound)
- PORTED `RotQuaternionX` w2 @ 0x0010E080 <- ntsc src/tableSin:func_0010E0B8 (5 syms rebound)
- PORTED `RotQuaternionY` w2 @ 0x0010E120 <- ntsc src/tableSin:func_0010E158 (5 syms rebound)
- PORTED `RotQuaternionZ` w2 @ 0x0010E1C0 <- ntsc src/tableSin:func_0010E1F8 (5 syms rebound)
- PORTED `SetCurrentQuaternion` w1 @ 0x0010D3F0 <- ntsc src/quaternion:RotCurrentQuaternionX (4 syms rebound)
- REVERTED `SetIdentityQuaternion` w2 @ 0x0010D4F8 — [callee-sig-conflict] src/quaternion.c:75: conflicting types for `SetIdentityQuaternion'
- PORTED `SetQuaternionByAxisRotateEAngle` w1 @ 0x0010DC00 <- ntsc src/tableSin:GetTableArcTan2 (3 syms rebound)
- PORTED `SetQuaternionByAxisRotateV` w1 @ 0x0010DCC0 <- ntsc src/tableSin:func_0010DCF8 (5 syms rebound)
- PORTED `SetQuaternionByAxisRotateVEAngle` w1 @ 0x0010E830 <- ntsc src/DisplayP2O:p2o_DispVU1Default (3 syms rebound)
- PORTED `SetQuaternionByAxisRotateVWithNoRegularize` w1 @ 0x0010DD20 <- ntsc src/tableSin:func_0010DD58 (4 syms rebound)
- PORTED `SetQuaternionByAxisRotateWithNoRegularize` w1 @ 0x0010DB98 <- ntsc src/tableSin:GetTableArcCos (4 syms rebound)
- PORTED `SetQuaternionByCosineAxisRotateV` w1 @ 0x0010E7A0 <- ntsc src/DisplayP2O:p2o_DispVU1 (4 syms rebound)
- PORTED `SetQuaternionByCosineAxisRotateVWithNoRegularize` w1 @ 0x0010E710 <- ntsc src/DisplayP2O:p2o_DispVU1MultiDefault (3 syms rebound)

### src/queen
- REVERTED `scale_m34` w1 @ 0x001A2770 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x60 (out-of-line helper or extra code)

### src/queen_barrier_disp
- PORTED `queen_barrier_anim` w1 @ 0x001A55E0 <- ntsc src/queen_barrier_disp:makeRefractST (4 syms rebound)
- REVERTED `queen_barrier_set_damage` w1 @ 0x001A4E48 — [codegen] insn 5: expected `<end>` built `sll	zero,zero,0x0`

### src/rope
- PORTED `ReleaseRope` w2 @ 0x001F6FB8 <- ntsc src/rope:InitRopeGeo (1 syms rebound)

### src/ropeFix
- PORTED `InitRopeFixGeo` w2 @ 0x001F70C0 <- ntsc src/ropeFix:func_001E9910 (1 syms rebound)
- PORTED `RopeFixGeo` w1 @ 0x001F7038 <- ntsc src/ropeFix:InitRopeFixGeo (3 syms rebound)

### src/rotObject
- PORTED `ExecRotObjectMoveEndReaction` w2 @ 0x001F75B0 <- ntsc src/rotObject:func_001E9DF0 (2 syms rebound)
- PORTED `ExecRotObjectMoveStartReaction` w2 @ 0x001F75A8 <- ntsc src/rotObject:func_001E9DE8 (2 syms rebound)
- PORTED `GetRotObjectHoldPoint` w1 @ 0x001F7130 <- ntsc src/rotObject:moveStartSE (9 syms rebound)
- PORTED `RestoreRotObjectGeo` w2 @ 0x001F7A40 <- ntsc src/rotObject:func_001EA220 (1 syms rebound)
- REVERTED `RotObjectGeo` w3 @ 0x001F7100 — [codegen] insn 1: expected `lw	a1,2096(v0)` built `lw	a1,2048(v0)`
- REVERTED `SetRotObjectLockFlag` w3 @ 0x001F7A88 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `moveEndSE` w3 @ 0x001F70D0 — [arity] src/rotObject.c:49: too many arguments to function `moveEndSE'
- REVERTED `moveStartSE` w3 @ 0x001F70C8 — [arity] src/rotObject.c:41: too many arguments to function `moveStartSE'

### src/sceneManager
- PORTED `ChangeStageStartInfo` w1 @ 0x001C1D68 <- ntsc src/sceneManager:GetStageStartInfo (4 syms rebound)
- PORTED `GetStageStartInfo` w1 @ 0x001C1EC0 <- ntsc src/staffroll:staffRollScroll (5 syms rebound)
- PORTED `HotInitSceneObjects` w1 @ 0x001C1CC0 <- ntsc src/sceneManager:test_nextstage_firstwalk_set (5 syms rebound)
- PORTED `MoveNextStage_Clear` w1 @ 0x001C1F48 <- ntsc src/staffroll:staffRollNameOut (3 syms rebound)
- PORTED `initWayData` w2 @ 0x001C1A70 <- ntsc src/sceneManager:CreateLayoutedGObj (2 syms rebound)
- PORTED `test_nextstage_firstwalk_set` w1 @ 0x001C1EB0 <- ntsc src/staffroll:staffRollStart (4 syms rebound)

### src/script
- PORTED `InitStageChange` w2 @ 0x00185170 <- ntsc src/st25a:actSt25aQueenTalk (2 syms rebound)
- PORTED `RequestStageChange` w1 @ 0x00185178 <- ntsc src/st25a:actSt25aQueenDead (2 syms rebound)
- PORTED `RequestStageChangeDirect` w1 @ 0x00185338 <- ntsc src/st25a:actSwordEffXL (6 syms rebound)
- PORTED `RequestStageChangeSimple` w1 @ 0x001852E8 <- ntsc src/st25a:actSwordEff (4 syms rebound)
- PORTED `ScpCallCameraGetTarget` w1 @ 0x00185838 <- ntsc src/warpGirl:warpGirlInit (2 syms rebound)
- REVERTED `ScpCallCameraOn` w3 @ 0x00185890 — [codegen] insn 2: expected `lui	v1,0x80` built `addiu	v1,zero,4096`
- REVERTED `_SCPCharacterStop` w3 @ 0x00184FA8 — [codegen] insn 2: expected `sw	v1,824(v0)` built `sw	v1,808(v0)`
- PORTED `preload` w1 @ 0x00183698 <- ntsc src/gflag:func_0017C9B0 (6 syms rebound)
- PORTED `scpActivateAllWithKind` w1 @ 0x00183788 <- ntsc src/gflag:func_0017CAA0 (3 syms rebound)
- PORTED `scpCheckReadyAllObjects` w2 @ 0x001857A0 <- ntsc src/warpGirl:warpGirlOutStage (2 syms rebound)
- PORTED `scpDisActivateAllWithKind` w1 @ 0x001837C8 <- ntsc src/gflag:func_0017CAE0 (3 syms rebound)
- PORTED `scpDispOffAllWithKind` w1 @ 0x00183700 <- ntsc src/gflag:func_0017CA18 (3 syms rebound)
- PORTED `scpDispOnAllWithKind` w1 @ 0x00183740 <- ntsc src/gflag:func_0017CA58 (3 syms rebound)
- PORTED `scpEffectStart` w1 @ 0x00184AD8 <- ntsc src/script:scpDispOffAllWithKind (3 syms rebound)
- PORTED `scpFadeChk` w1 @ 0x001853D0 <- ntsc src/st25a:actSt25aQueenDeadEvent (2 syms rebound)
- PORTED `scpFadeIn` w1 @ 0x001853B8 <- ntsc src/st25a:actConte11Jimaku (4 syms rebound)
- PORTED `scpFadeOut` w1 @ 0x00185398 <- ntsc src/st25a:actSt25aQueenBeforeChk (7 syms rebound)
- REVERTED `scpGameStat_BoyWeaponkind` w3 @ 0x001853F8 — [codegen] insn 4: expected `lw	a0,336(v1)` built `lw	a0,320(v1)`
- PORTED `scpGetRotObjectRotCount` w3 @ 0x00184110 <- ntsc src/script:scpSekizou (5 syms rebound)
- PORTED `scpIsBombExplode` w1 @ 0x001840B8 <- ntsc src/script:scpSubAdpcmPlay (4 syms rebound)
- PORTED `scpIsHangChain` w2 @ 0x00185448 <- ntsc src/st25a:func_0017E600 (2 syms rebound)
- PORTED `scpIsHangChainOptional` w1 @ 0x00185468 <- ntsc src/st25a:func_0017E620 (2 syms rebound)
- PORTED `scpIsRotObjectZPlusDirInclude` w3 @ 0x00184150 <- ntsc src/script:_SCPBoySupportGirl (5 syms rebound)
- PORTED `scpIsTorchLightOn` w1 @ 0x00184078 <- ntsc src/script:scpDoorTypeUpUp (3 syms rebound)
- PORTED `scpIsWallLever2On` w2 @ 0x00185428 <- ntsc src/st25a:func_0017E5E0 (2 syms rebound)
- PORTED `scpKillEnemyOne` w1 @ 0x00184D28 <- ntsc src/st25a:actConte11 (4 syms rebound)
- PORTED `scpKillSpiderGroup` w1 @ 0x00183678 <- ntsc src/gflag:func_0017C990 (3 syms rebound)
- PORTED `scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag` w2 @ 0x00183968 <- ntsc src/script:scpPlayMotDir (6 syms rebound)
- PORTED `scpLinkBGAtoLayoutedTargetSkelton` w1 @ 0x00183848 <- ntsc src/script:scpTorchLightOff (6 syms rebound)
- PORTED `scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag` w2 @ 0x001838D0 <- ntsc src/script:scpSetCageVelocityFriction (6 syms rebound)
- PORTED `scpMaskGeneratorAll` w1 @ 0x00184CE0 <- ntsc src/st25a:actSt25aQueenAppearChk (4 syms rebound)
- PORTED `scpPlayEnd` w1 @ 0x00181D88 <- ntsc src/gflag:func_0017B568 (3 syms rebound)
- REVERTED `scpPlayJump` w3 @ 0x00181D00 — [codegen] insn 11: expected `lw	v0,1664(v1)` built `lw	v0,1648(v1)`
- REVERTED `scpPlayMot` w3 @ 0x00181C18 — [codegen] insn 13: expected `addiu	s1,zero,1281` built `addiu	s1,zero,1214`
- PORTED `scpPlayMotDir` w1 @ 0x00181B70 <- ntsc src/gflag:gflagChk (3 syms rebound)
- PORTED `scpPlayMotNode` w1 @ 0x00184FF0 <- ntsc src/st25a:actConte13Jimaku (4 syms rebound)
- REVERTED `scpPlayMotReq` w3 @ 0x00185088 — [codegen] insn 5: expected `addiu	a2,s0,1568` built `addiu	a2,s0,1552`
- PORTED `scpPlayPosSet` w1 @ 0x001850B8 <- ntsc src/st25a:actSt25aGenerator (4 syms rebound)
- PORTED `scpPlayStart` w1 @ 0x00181D48 <- ntsc src/gflag:func_0017B528 (4 syms rebound)
- REVERTED `scpPlayWaitMotEnd` w3 @ 0x00185130 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `scpSearchGobj` w2 @ 0x00184FD0 <- ntsc src/st25a:actSt25aQueenDeadChk (2 syms rebound)
- PORTED `scpSetBoyWeaponGObj` w2 @ 0x001836F8 <- ntsc src/gflag:func_0017CA10 (2 syms rebound)
- PORTED `scpSetCageVelocityFriction` w1 @ 0x00181B30 <- ntsc src/gflag:gflagLoad (5 syms rebound)
- PORTED `scpSetStreamMotionRootOffset` w1 @ 0x001856B8 <- ntsc src/st25a:func_0017E838 (2 syms rebound)
- REVERTED `scpSleepEnemyAll` w3 @ 0x00184B20 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `scpSleepEnemyOne` w1 @ 0x001835E0 <- ntsc src/gflag:func_0017C8F8 (3 syms rebound)
- PORTED `scpSleepSpiderGroupOne` w2 @ 0x00183618 <- ntsc src/gflag:func_0017C930 (3 syms rebound)
- PORTED `scpTorchLightOff` w2 @ 0x00181B00 <- ntsc src/gflag:gflagSave (3 syms rebound)
- REVERTED `scpTorchLightOn` w2 @ 0x00181AD0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `scpTrans` w1 @ 0x00181DC0 <- ntsc src/gflag:func_0017B5A0 (2 syms rebound)
- REVERTED `scpWakeupEnemyAll` w3 @ 0x00184BA8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `scpWakeupEnemyOne` w1 @ 0x001835A8 <- ntsc src/gflag:func_0017C8C0 (3 syms rebound)
- PORTED `scpWakeupSpiderGroupOne` w2 @ 0x00183648 <- ntsc src/gflag:func_0017C960 (3 syms rebound)

### src/seMail
- REVERTED `setMailTarget` w1 @ 0x00214B38 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x30 (out-of-line helper or extra code)

### src/spider
- REVERTED `DeleteSpiderFromLayoutGroup` w3 @ 0x001F8690 — [codegen] insn 2: expected `lw	v0,2096(a2)` built `lw	v0,2048(a2)`
- PORTED `RestoreSpiderLayoutGeo` w2 @ 0x001F88D8 <- ntsc src/spider:func_001EB0B8 (1 syms rebound)
- REVERTED `SetSpiderGroupReviveStatus` w3 @ 0x001F8508 — [codegen] insn 6: expected `lw	v0,2096(v1)` built `lw	v0,2048(v1)`

### src/spiderGroupManager
- PORTED `DispAllSpiderGroups` w1 @ 0x001F9260 <- ntsc src/spiderGroupManager:func_001EBA40 (8 syms rebound)
- PORTED `EntryRevivedSpiderGroupManager` w1 @ 0x001F9238 <- ntsc src/spiderGroupManager:func_001EBA18 (3 syms rebound)
- PORTED `EntryToSpiderGroupManagerForReviveMaster` w1 @ 0x001F9308 <- ntsc src/spiderGroupManager:func_001EBAE8 (4 syms rebound)
- PORTED `InitSpiderGroupManager` w1 @ 0x001F9210 <- ntsc src/spiderGroupManager:func_001EB9F0 (9 syms rebound)
- PORTED `getReviveEnemyGObj` w1 @ 0x001F9330 <- ntsc src/spiderGroupManager:func_001EBB10 (3 syms rebound)

### src/st00a
- REVERTED `actSt00aDoor1DownEffect` w2 @ 0x00222630 — [codegen] tu-size: TU .text 0x14D4 != PAL span 0x14D8 (trailing pad word / extra code)
- PORTED `actSt00aDoor1Event` w2 @ 0x00222540 <- ntsc src/st01b:actSt01bSekizoEvent (1 syms rebound)
- PORTED `actSt00aDoor1UpEffect` w2 @ 0x00222550 <- ntsc src/st01b:actSt01bFloorEvent (5 syms rebound)
- PORTED `actSt00aDoor2DownEffect` w2 @ 0x00222460 <- ntsc src/st01b:actSt01bEnd (5 syms rebound)
- PORTED `actSt00aDoor2Event` w2 @ 0x00222370 <- ntsc src/st01b:actSt01bFloor (1 syms rebound)
- PORTED `actSt00aDoor2UpEffect` w2 @ 0x00222380 <- ntsc src/st01b:actSt01bWay (5 syms rebound)

### src/st01b
- PORTED `actSt01bEnd` w2 @ 0x00223190 <- ntsc src/st02a:actSt02aGondola (1 syms rebound)
- PORTED `actSt01bFloorEvent` w2 @ 0x002231A8 <- ntsc src/st02a:actSt02aWaterFall (1 syms rebound)
- PORTED `actSt01bSekizoEvent` w2 @ 0x00223198 <- ntsc src/st02a:actSt02aFence (1 syms rebound)

### src/st02a
- PORTED `actSt02WaterFallBoySplashCheck` w1 @ 0x00223930 <- ntsc src/st02a:actSt02aTakiWay (8 syms rebound)
- PORTED `actSt02aDoorDownEffect` w2 @ 0x002247D0 <- ntsc src/st03t:actSt03tGirlCamEvent (5 syms rebound)
- PORTED `actSt02aDoorEvent` w2 @ 0x002246E0 <- ntsc src/st03t:actSt03tEne (1 syms rebound)
- PORTED `actSt02aDoorUpEffect` w2 @ 0x002246F0 <- ntsc src/st03t:actSt03tGene (5 syms rebound)
- PORTED `actSt02aSekizoEvent` w2 @ 0x00224B18 <- ntsc src/st03t:actSt03tWayOnChk (1 syms rebound)

### src/st03t
- PORTED `actSt03tGirlCamEvent` w2 @ 0x00225DF0 <- ntsc src/st04a:actSt04aGateR (1 syms rebound)
- REVERTED `actSt03tGirlCamStartChk` w3 @ 0x00225E00 — [codegen] insn 23: expected `addiu	v1,zero,202` built `addiu	v1,zero,198`
- PORTED `actSt03tSekizoEvent` w2 @ 0x00225F98 <- ntsc src/st04a:actSt04aGateOpen3 (1 syms rebound)

### src/st04a
- REVERTED `actSt04aGateOpen2ReadyChk` w3 @ 0x0022AA18 — [codegen] insn 38: expected `addiu	a0,zero,32` built `addiu	a0,zero,31`
- REVERTED `finishCallBackFunc` w3 @ 0x0022A948 — [codegen] insn 20: expected `lw	v0,2060(v1)` built `lw	v0,2012(v1)`

### src/st04b
- PORTED `actSt04bSekizoEvent` w2 @ 0x0022B970 <- ntsc src/st04d:actSt04dDoor1DownChk (1 syms rebound)

### src/st04c
- PORTED `actSt04cDoorDownEvent` w2 @ 0x0022C2A8 <- ntsc src/st04d:func_002194C8 (1 syms rebound)
- PORTED `actSt04lDoorEvent` w2 @ 0x0022C498 <- ntsc src/st04d:func_00219728 (1 syms rebound)

### src/st04d
- PORTED `actSt04dDoor1Event` w2 @ 0x0022CC18 <- ntsc src/st04e:func_00219EA8 (1 syms rebound)
- REVERTED `actSt04dDoor1UpChk` w3 @ 0x0022C5B0 — [codegen] insn 27: expected `addiu	a0,s2,0` built `addiu	a0,s2,1920`
- REVERTED `actSt04dDoor2` w3 @ 0x0022C860 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- REVERTED `actSt04dDoor2DownChk` w3 @ 0x0022CAC0 — [codegen] insn 27: expected `addiu	a0,s2,0` built `addiu	a0,s2,2608`
- PORTED `actSt04dDoor2Event` w2 @ 0x0022CDE8 <- ntsc src/st04e:func_0021A078 (1 syms rebound)

### src/st04l
- PORTED `actSt04lBrg1Event` w2 @ 0x00233278 <- ntsc src/st05c:func_0021F2C8 (1 syms rebound)
- PORTED `actSt04lBrg2Event` w2 @ 0x00233360 <- ntsc src/st05c:func_0021F2F8 (1 syms rebound)
- PORTED `actSt04lMonyou01Event` w2 @ 0x00233640 <- ntsc src/st05d:actSt05dDoor2DownChk (1 syms rebound)
- PORTED `actSt04lMonyou02Event` w2 @ 0x00233650 <- ntsc src/st05d:actSt05dEne (1 syms rebound)
- PORTED `actSt04lMonyou03Event` w2 @ 0x00233660 <- ntsc src/st05d:actSt05dEnemy1 (1 syms rebound)
- PORTED `actSt04lMonyou04Event` w2 @ 0x00233670 <- ntsc src/st05d:actSt05dEnemy2 (1 syms rebound)
- PORTED `actSt04lMonyou05Event` w2 @ 0x00233680 <- ntsc src/st05d:actSt05dDoor2Event (1 syms rebound)
- PORTED `actSt04lMonyou06Event` w2 @ 0x00233690 <- ntsc src/st05d:actSt05dDoor2UpEffect (1 syms rebound)
- PORTED `actSt04lMonyou07Event` w2 @ 0x002336A0 <- ntsc src/st05d:actSt05dDoor2DownEffect (1 syms rebound)
- PORTED `actSt04lOri2Event` w2 @ 0x002336C0 <- ntsc src/st05d:func_0021F578 (1 syms rebound)
- PORTED `actSt04lOriEvent` w2 @ 0x002336B0 <- ntsc src/st05d:actSt05dEneChk (1 syms rebound)
- PORTED `actSt04lRope1Event` w2 @ 0x00233258 <- ntsc src/st05c:actSt05cDoorDownEffect (1 syms rebound)
- PORTED `actSt04lRope2Event` w2 @ 0x00233268 <- ntsc src/st05c:actSt05cEneChk (1 syms rebound)
- PORTED `actSt04lRope3Event` w2 @ 0x00233340 <- ntsc src/st05c:func_0021F2D8 (1 syms rebound)
- PORTED `actSt04lRope4Event` w2 @ 0x00233350 <- ntsc src/st05c:func_0021F2E8 (1 syms rebound)
- REVERTED `actSt04lSwordChk` w3 @ 0x002336D0 — [codegen] insn 4: expected `addiu	a0,zero,1122` built `addiu	a0,zero,1034`
- REVERTED `actSt04lTuriChk` w3 @ 0x002334E0 — [codegen] insn 20: expected `addiu	a0,zero,55` built `addiu	a0,zero,51`
- PORTED `actSt04lTuriEvent` w2 @ 0x002334D0 <- ntsc src/st05c:func_0021F3A8 (1 syms rebound)

### src/st04r
- REVERTED `actSt04rBarricade` w3 @ 0x00236F98 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rBarricadeEvent` w2 @ 0x00238408 <- ntsc src/st08b:actSt08bKurenRight (1 syms rebound)
- PORTED `actSt04rBrg1Event` w2 @ 0x00238090 <- ntsc src/st08a:actSt08aIntro (1 syms rebound)
- REVERTED `actSt04rBrg1Way` w3 @ 0x00236B70 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rBrg2` w3 @ 0x00236AF8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rBrg2Event` w2 @ 0x00238240 <- ntsc src/st08a:actSt08aDoorSwitch (1 syms rebound)
- REVERTED `actSt04rBrg2Way` w3 @ 0x00236BE8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rC2Ball` w3 @ 0x00236870 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rC3Ball` w3 @ 0x00236928 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rC3BallXL` w3 @ 0x00237290 — [codegen] insn 10: expected `addiu	a0,zero,252` built `addiu	a0,zero,226`
- REVERTED `actSt04rCrest02XL` w3 @ 0x00237158 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rCrest03` w3 @ 0x00236718 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rCrest03XL` w3 @ 0x002371B8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rMonyou01Event` w2 @ 0x00238398 <- ntsc src/st08a:func_00223EF0 (1 syms rebound)
- REVERTED `actSt04rMonyou02` w3 @ 0x002378F0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rMonyou02Event` w2 @ 0x002383A8 <- ntsc src/st08a:func_00223F00 (1 syms rebound)
- REVERTED `actSt04rMonyou03` w3 @ 0x00237988 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rMonyou03Event` w2 @ 0x002383B8 <- ntsc src/st08a:func_00223F10 (1 syms rebound)
- REVERTED `actSt04rMonyou04` w3 @ 0x00237A20 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rMonyou04Event` w2 @ 0x002383C8 <- ntsc src/st08a:func_00223F20 (1 syms rebound)
- REVERTED `actSt04rMonyou05` w3 @ 0x00237AB8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rMonyou05Event` w2 @ 0x002383D8 <- ntsc src/st08a:func_00223F30 (1 syms rebound)
- REVERTED `actSt04rMonyou06` w3 @ 0x00237B50 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rMonyou06Event` w2 @ 0x002383E8 <- ntsc src/st08b:actSt08bKurenSwitch (1 syms rebound)
- REVERTED `actSt04rMonyou07` w3 @ 0x00237BE8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rMonyou07Event` w2 @ 0x002383F8 <- ntsc src/st08b:actSt08bKurenLeft (1 syms rebound)
- PORTED `actSt04rRope1Event` w2 @ 0x00238070 <- ntsc src/st08a:actSt08aEnemy3 (1 syms rebound)
- REVERTED `actSt04rRope2` w3 @ 0x00236D08 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rRope2Event` w2 @ 0x00238080 <- ntsc src/st08a:actSt08aEnemy4 (1 syms rebound)
- REVERTED `actSt04rRope3` w3 @ 0x00236DB0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rRope3Event` w2 @ 0x00238220 <- ntsc src/st08a:actSt08aInit (1 syms rebound)
- REVERTED `actSt04rRope4` w3 @ 0x00236E58 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt04rRope4Event` w2 @ 0x00238230 <- ntsc src/st08a:actSt08aDoorMain (1 syms rebound)
- PORTED `actSt04rStairEvent` w2 @ 0x00238060 <- ntsc src/st08a:actSt08aEnemy2 (1 syms rebound)
- REVERTED `actSt04rTorch2_2` w3 @ 0x002374D0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rTorch3_2` w3 @ 0x002375F0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rTorch3_2XL` w3 @ 0x00237810 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05cInit` w3 @ 0x002339F0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05eInit` w3 @ 0x00233EC8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/st05b
- PORTED `actSt05bSekizoEvent` w2 @ 0x00238DD0 <- ntsc src/st08b:func_00224960 (1 syms rebound)

### src/st05c
- PORTED `actSt05cDoorDownEvent` w2 @ 0x00239848 <- ntsc src/st09a:actSt09aBrgMain (1 syms rebound)

### src/st05d
- PORTED `actSt05dDoor2DownEffect` w2 @ 0x0023A2B0 <- ntsc src/st10l:actSt10lFloorLeft (5 syms rebound)
- PORTED `actSt05dDoor2Event` w2 @ 0x0023A1C0 <- ntsc src/st09a:func_002258E0 (1 syms rebound)
- PORTED `actSt05dDoor2UpEffect` w2 @ 0x0023A1D0 <- ntsc src/st10l:actSt10lInit (5 syms rebound)

### src/st06a
- PORTED `actSt06aDoorDownEffect` w2 @ 0x0023CC30 <- ntsc src/st10r:actSt10rSekizo (5 syms rebound)
- PORTED `actSt06aDoorEvent` w2 @ 0x0023CB40 <- ntsc src/st10r:actSt10rExit (1 syms rebound)
- PORTED `actSt06aDoorUpEffect` w2 @ 0x0023CB50 <- ntsc src/st10r:actSt10rChain (5 syms rebound)
- PORTED `actSt06aSuimonEvent` w2 @ 0x0023C8F8 <- ntsc src/st10r:actSt10rFloor (1 syms rebound)

### src/st07a
- PORTED `actSt07ChanEvent` w2 @ 0x0023FA60 <- ntsc src/st13b:actSt13bElevDown (1 syms rebound)
- PORTED `actSt07TsuroEvent` w2 @ 0x0023FC10 <- ntsc src/st13b:actSt13bBossAfter (1 syms rebound)
- PORTED `actSt07aCamera2` w2 @ 0x0023FCF8 <- ntsc src/st13b:actSt13bElev (1 syms rebound)
- REVERTED `actSt07aChanMot` w3 @ 0x0023FB08 — [codegen] insn 1: expected `addiu	a1,zero,474` built `addiu	a1,zero,464`
- PORTED `actSt07aChanWay1` w2 @ 0x0023FB60 <- ntsc src/st13b:actSt13bSekizo (5 syms rebound)
- PORTED `actSt07aChanWay2` w2 @ 0x0023FBB8 <- ntsc src/st13b:actSt13bSekizo2 (5 syms rebound)
- PORTED `actSt07aGirlWay` w2 @ 0x0023FCA0 <- ntsc src/st13b:actSt13bExit (5 syms rebound)
- REVERTED `actSt07aIntroChk` w3 @ 0x0023FD08 — [codegen] insn 16: expected `addiu	a0,zero,55` built `addiu	a0,zero,51`
- PORTED `actSt07aSekizoEvent` w2 @ 0x0023FDB8 <- ntsc src/st13b:actBossTest (1 syms rebound)
- REVERTED `actSt07aTsuroConte` w3 @ 0x0023FC20 — [codegen] insn 6: expected `addiu	a0,zero,357` built `addiu	a0,zero,323`

### src/st08b
- PORTED `actSt08bDoorDownEffect` w2 @ 0x00241F90 <- ntsc src/st13c:actSt13cConte04Jimaku (5 syms rebound)
- PORTED `actSt08bDoorEvent` w2 @ 0x00241EA0 <- ntsc src/st13c:actSt13cBmg1Chk (1 syms rebound)
- PORTED `actSt08bDoorUpEffect` w2 @ 0x00241EB0 <- ntsc src/st13c:actSt13cConte04 (5 syms rebound)

### src/st09a
- PORTED `actSt09aSekizoEvent` w2 @ 0x00242890 <- ntsc src/st13c:actSt13cSleep (1 syms rebound)

### src/st10l
- REVERTED `actSt10lBoxChk` w3 @ 0x00244380 — [codegen] insn 13: expected `addiu	a0,zero,988` built `addiu	a0,zero,902`
- PORTED `actSt10lSekizoEvent` w2 @ 0x002443E0 <- ntsc src/st17a:actSt17aSekizo (1 syms rebound)

### src/st10r
- PORTED `actSt10rGirlWay` w2 @ 0x00246208 <- ntsc src/st17b:func_0022ED40 (5 syms rebound)
- PORTED `actSt10rSekizoEvent` w2 @ 0x00246458 <- ntsc src/st17b:func_0022EEF0 (1 syms rebound)

### src/st13b
- PORTED `actSt13bSekizo2Event` w2 @ 0x00249BA0 <- ntsc src/st19a:actSt19aOri (1 syms rebound)

### src/st13b2
- PORTED `actSt13b2Generator` w1 @ 0x00249F88 <- ntsc src/st19a:actSt19aChainSwitch (3 syms rebound)

### src/st13c
- PORTED `actE3St13cSekizoEvent` w2 @ 0x0024CFB0 <- ntsc src/st22a:func_00234448 (1 syms rebound)
- PORTED `actSt13cBmg1Event` w2 @ 0x0024CD40 <- ntsc src/st22a:actSt22aIntro (1 syms rebound)
- PORTED `actSt13cBukiEvent` w2 @ 0x0024D368 <- ntsc src/st22a:func_002347C8 (1 syms rebound)
- REVERTED `actSt13cCageFall` w3 @ 0x0024AA70 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt13cCageFallEvent` w2 @ 0x0024CFA0 <- ntsc src/st22a:func_00234438 (1 syms rebound)
- REVERTED `actSt13cConte04` w3 @ 0x0024A428 — [codegen] insn 7: expected `addiu	a0,zero,625` built `addiu	a0,zero,554`
- REVERTED `actSt13cEnd` w3 @ 0x00249FE8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt13cInit` w3 @ 0x00249FB8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt13cSleepEvent` w2 @ 0x0024CD50 <- ntsc src/st22a:actSt22aIntroChk (1 syms rebound)

### src/st13d
- PORTED `actSt13dInit` w2 @ 0x0024D650 <- ntsc src/st22a:func_00234AB0 (1 syms rebound)

### src/st17a
- PORTED `actLinkTestChk` w1 @ 0x0024E510 <- ntsc src/st24a:func_002356D0 (4 syms rebound)
- PORTED `actSt17aDoorDownEffect` w2 @ 0x0024E658 <- ntsc src/st24a:func_00235818 (5 syms rebound)
- PORTED `actSt17aDoorEvent` w2 @ 0x0024E568 <- ntsc src/st24a:func_00235728 (1 syms rebound)
- PORTED `actSt17aDoorUpEffect` w2 @ 0x0024E578 <- ntsc src/st24a:func_00235738 (5 syms rebound)
- PORTED `actSt17aGirlWay` w1 @ 0x0024E7F8 <- ntsc src/st24a:func_002359C8 (4 syms rebound)
- PORTED `actSt17aHasiEvent` w2 @ 0x0024E738 <- ntsc src/st24a:func_002358F8 (1 syms rebound)
- PORTED `actSt17aSekizoEvent` w2 @ 0x0024E500 <- ntsc src/st24a:func_002356C0 (1 syms rebound)

### src/st17b
- REVERTED `actSt17bTest` w2 @ 0x0024E928 — [codegen] tu-size: body is 0x0 bytes, ROM function is 0x30 (out-of-line helper or extra code)

### src/st18a
- PORTED `actSt18aCamera` w2 @ 0x0024FC70 <- ntsc src/st47a:actSt47aExit (1 syms rebound)

### src/st25a
- PORTED `BoySekikaTexScroll` w1 @ 0x001874A0 <- ntsc src/warpGirl:func_00180550 (4 syms rebound) — unblocked by the PAL phase-1 `lit4 src/st25a` carve
- PORTED `actSt25aGenerator` w2 @ 0x00187770 <- ntsc src/warpGirl:func_00180580 (2 syms rebound)
- PORTED `actSt25aQueenDeadEvent` w2 @ 0x00187DE0 <- ntsc src/attackhit:AttackCheckSameGroup (1 syms rebound)
- CARVES `src/st25a` — none in ntsc's ico.us.yaml

### src/st47a
- PORTED `actSt47aBarricadeEvent` w2 @ 0x00254BC0 <- ntsc src/access:func_0023AD58 (1 syms rebound)
- PORTED `actSt47aHane2Girl` w2 @ 0x00254AC0 <- ntsc src/access:func_0023AD08 (4 syms rebound)
- PORTED `actSt47aSekizo1Event` w2 @ 0x002547C8 <- ntsc src/access:func_0023A9E0 (1 syms rebound)
- PORTED `actSt47aSekizo2Event` w2 @ 0x00254860 <- ntsc src/access:func_0023AA88 (1 syms rebound)
- PORTED `func_00254948` w2 @ 0x00254948 <- ntsc src/access:func_0023AB90 (4 syms rebound)
- PORTED `func_00254998` w2 @ 0x00254998 <- ntsc src/access:func_0023ABE0 (4 syms rebound)

### src/st99a
- REVERTED `actDevilLightning` w3 @ 0x00254F68 — [codegen] insn 9: expected `addiu	a0,zero,3513` built `addiu	a0,zero,3242`
- REVERTED `actExplode` w3 @ 0x00254D40 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,920`
- REVERTED `actExplodeChk` w3 @ 0x002550D8 — [codegen] insn 4: expected `addiu	a0,zero,3014` built `addiu	a0,zero,2791`
- REVERTED `actQueenLightning` w3 @ 0x00254FB0 — [codegen] insn 9: expected `addiu	a0,zero,3512` built `addiu	a0,zero,3241`
- REVERTED `actSpider` w3 @ 0x00254EE0 — [codegen] insn 11: expected `addiu	a0,zero,160` built `addiu	a0,zero,139`
- REVERTED `actSplash1` w3 @ 0x00254DA8 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,1096`
- REVERTED `actSplash1Chk` w3 @ 0x00255188 — [codegen] insn 4: expected `addiu	a0,zero,3015` built `addiu	a0,zero,2792`
- REVERTED `actSplash2` w3 @ 0x00254E10 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,1272`
- REVERTED `actSplash2Chk` w3 @ 0x00255238 — [codegen] insn 4: expected `addiu	a0,zero,3016` built `addiu	a0,zero,2793`
- REVERTED `actSt17aTest` w3 @ 0x00254FF8 — [codegen] insn 12: expected `addiu	a0,zero,132` built `addiu	a0,zero,112`
- REVERTED `actSt27aWave` w3 @ 0x00255070 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,1624`
- REVERTED `actWave` w3 @ 0x00254E78 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,1448`
- REVERTED `actWaveChk` w2 @ 0x002552E8 — [codegen] insn 6: expected `addiu	a0,a0,0` built `addiu	a0,a0,1488`

### src/staffroll
- PORTED `staffRollWide` w1 @ 0x001C24B0 <- ntsc src/a_p_1:InitAP1 (7 syms rebound)

### src/stageSEProc
- REVERTED `stageSE02ataki` w3 @ 0x00255E88 — [codegen] insn 7: expected `addiu	a0,zero,106` built `addiu	a0,zero,95`
- REVERTED `stageSE02atakib` w3 @ 0x00255EE0 — [codegen] insn 6: expected `addiu	a0,zero,106` built `addiu	a0,zero,95`
- PORTED `stageSE03tnotSuiro` w1 @ 0x00255F78 <- ntsc src/objact:func_0023C180 (2 syms rebound)
- PORTED `stageSE03tsuiro` w1 @ 0x00255F40 <- ntsc src/objact:func_0023C148 (2 syms rebound)
- PORTED `stageSE04bstrong` w2 @ 0x00256088 <- ntsc src/objact:func_0023C290 (6 syms rebound)
- PORTED `stageSE06abirdIn` w1 @ 0x00256338 <- ntsc ito/mpeg/mv_audiodec:audioDecEndPut (2 syms rebound)
- PORTED `stageSE06abirdOut` w1 @ 0x00256390 <- ntsc ito/mpeg/mv_audiodec:sendToIOP2area (2 syms rebound)
- PORTED `stageSE06ataimatsu` w1 @ 0x002563E8 <- ntsc ito/mpeg/mv_audiodec:audioDecSendToIOP (3 syms rebound)
- PORTED `stageSE08anoise3` w1 @ 0x00256600 <- ntsc ito/mpeg/mv_audiodec:audioDecReset (6 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE08ataimatsu` w1 @ 0x00256688 <- ntsc ito/mpeg/mv_audiodec:audioDecIsPreset (6 syms rebound)
- PORTED `stageSE08bcrane` w1 @ 0x00256700 <- ntsc ito/mpeg/mv_audiodec:audioDecStart (9 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE09asea` w1 @ 0x00256800 <- ntsc ito/mpeg/mv_audiodec:audioDecResume (3 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE13arain` w1 @ 0x00256A70 <- ntsc ito/mpeg/mv_audiodec:func_0023CC78 (1 syms rebound)
- PORTED `stageSE13cNoise` w1 @ 0x00256AB0 <- ntsc ito/mpeg/mv_audiodec:func_0023CCB8 (3 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE13dterrace` w1 @ 0x00256AD8 <- ntsc ito/mpeg/mv_audiodec:func_0023CCE0 (2 syms rebound)
- PORTED `stageSE17btaki` w2 @ 0x00256E28 <- ntsc ito/mpeg/mv_disp:setDispEnv (3 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE19arain` w1 @ 0x00256EC0 <- ntsc ito/mpeg/mv_disp:sendDispEnv (4 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE19astrong` w1 @ 0x00256E48 <- ntsc ito/mpeg/mv_disp:setImageSize (7 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE20astrong` w1 @ 0x00256EE8 <- ntsc ito/mpeg/mv_disp:dispCreate (8 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE20astrong2` w2 @ 0x00256F68 <- ntsc ito/mpeg/mv_disp:dispSetTags (6 syms rebound)
- PORTED `stageSE22astrong` w1 @ 0x00256FC8 <- ntsc ito/mpeg/mv_disp:dispSwitch (6 syms rebound)
- PORTED `stageSE24arain` w1 @ 0x00257140 <- ntsc ito/mpeg/mv_disp:loadImage (3 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE24ariver` w2 @ 0x00257168 <- ntsc ito/mpeg/mv_disp:handler_endimage (3 syms rebound) — unblocked by the PAL phase-1 `lit4 src/stageSEProc` carve
- PORTED `stageSE24astrong` w2 @ 0x002570E0 <- ntsc ito/mpeg/mv_disp:dispDelete (6 syms rebound)
- CARVES `src/stageSEProc` — none in ntsc's ico.us.yaml

### src/staticBlur
- PORTED `GetSunWorldPos` w2 @ 0x001FCA50 <- ntsc src/staticBlur:subWork1ToCurrentFB (3 syms rebound)
- PORTED `InitializeStaticBlur` w2 @ 0x001FD570 <- ntsc src/stormTest:StormTestDL (2 syms rebound)
- PORTED `SetAuraEffect` w2 @ 0x001FD5F0 <- ntsc src/stormTest:func_001EFA58 (1 syms rebound)
- PORTED `SetAuraInspireParam` w2 @ 0x001FD568 <- ntsc src/stormTest:StormTestGeo (2 syms rebound)
- PORTED `SetDepthFadeParam` w1 @ 0x001FD540 <- ntsc src/stormTest:DispStormPackage (2 syms rebound)
- PORTED `SetMotionBlur` w2 @ 0x001FD528 <- ntsc src/stormTest:ClipStormByCamera (2 syms rebound)
- PORTED `SetStaticBlur` w1 @ 0x001FD530 <- ntsc src/stormTest:UpdateStormPackage (2 syms rebound)
- PORTED `StaticBlur` w2 @ 0x001FD518 <- ntsc src/stormTest:InitStormPackage (1 syms rebound)
- PORTED `StaticBlurDL` w2 @ 0x001FD520 <- ntsc src/stormTest:ClipStormByVolume (1 syms rebound)
- PORTED `_initStaticBlur` w1 @ 0x001FD578 <- ntsc src/stormTest:InitStormTestGeo (5 syms rebound)
- PORTED `calcSun` w1 @ 0x001FCC60 <- ntsc src/staticBlur:cleanUpFB (13 syms rebound) — unblocked by the PAL phase-1 `lit4 src/staticBlur` carve
- CARVES `src/staticBlur` — 2 US carve entries to translate:
    - - [0x3C61A0, .data, src/staticBlur]  # carved D_004C61A0..D_004C61E0 (VMA 0x4C61A0..0x4C61F0, 80 bytes, 5 syms)
    - - [0x5313D8, .lit4, src/staticBlur]    # carved D_006313D8/13DC (0.9f, 1000000f), VMA 0x6313D8..0x6313E0

### src/stormTest
- REVERTED `StormTestDL` w3 @ 0x001FE0E8 — [codegen] insn 1: expected `lw	a1,2096(v0)` built `lw	a1,2048(v0)`
- REVERTED `StormTestGeo` w3 @ 0x001FE0D8 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`

### src/streamMotionManager
- PORTED `CheckReadyStreamMotion` w1 @ 0x001FF090 <- ntsc src/streamMotionManager:DeleteStreamMotionManager (3 syms rebound)
- PORTED `DisableStreamMotionManagerAutomaticDelete` w2 @ 0x001FE860 <- ntsc src/stormTest:func_001F0A28 (4 syms rebound)
- PORTED `FreeStreamMotionBuffer` w1 @ 0x001FF0F0 <- ntsc src/sugiTree:func_001F1168 (5 syms rebound)
- PORTED `InitStreamMotionManager` w2 @ 0x001FF080 <- ntsc src/streamMotionManager:StopStreamMotion (4 syms rebound)
- PORTED `PlayStreamMotion` w1 @ 0x001FE680 <- ntsc src/stormTest:func_001F0858 (5 syms rebound)
- REVERTED `SetStreamMotionFinishCallBackFunc` w3 @ 0x001FF0D0 — [codegen] insn 0: expected `addiu	v1,zero,28` built `addiu	v1,zero,24`
- PORTED `StopStreamMotion` w2 @ 0x001FEE88 <- ntsc src/streamMotionManager:GetStreamMotionData (2 syms rebound)
- PORTED `_closeHander` w2 @ 0x001FF1C8 <- ntsc src/sugiTree:InitSugiLeafGeo (2 syms rebound)
- PORTED `_transRingBuf` w1 @ 0x001FEA18 <- ntsc src/streamMotionManager:PlayStreamMotion (2 syms rebound)

### src/tableSin
- REVERTED `GetTableArcTan2` w1 @ 0x0010EBD0 — [codegen] tu-size: TU .text 0x2FC != PAL span 0x300 (trailing pad word / extra code)
- REVERTED `GetTableSin` w1 @ 0x0010E918 — [codegen] insn 19: expected `<end>` built `sll	zero,zero,0x0`

### src/torch
- REVERTED `IsTorchLightOn` w3 @ 0x00200230 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `SetTorchChainReactionFlag` w3 @ 0x00200348 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- PORTED `TorchDL` w2 @ 0x00200228 <- ntsc src/torch:CheckTorchChainReactionReverse (1 syms rebound)
- PORTED `UpdateRealTimeGeometryValue` w1 @ 0x00200358 <- ntsc src/waySystemManager:CreateWaySystemManagerGObj (4 syms rebound)

### src/vobj
- REVERTED `SetVObjRT` w1 @ 0x0025B640 — [codegen] tu-size: TU .text 0x104 != PAL span 0x108 (trailing pad word / extra code)

### src/warpGirl
- PORTED `warpGirlInit` w2 @ 0x00188278 <- ntsc src/attackhit:AttackGenerate (2 syms rebound)

### src/waySystemManager
- REVERTED `CreateWaySystemManagerGObj` w2 @ 0x00200AD0 — [codegen] insn 4: expected `addiu	t0,t0,0` built `addiu	t0,t0,208`
- REVERTED `RequestGetWayBegin` w2 @ 0x00200B10 — [codegen] insn 7: expected `addiu	a0,a0,0` built `addiu	a0,a0,128`
- PORTED `actWaySystemCore` w1 @ 0x00200B50 <- ntsc src/waySystemManager:func_001F2320 (2 syms rebound)

### src/way_kidnap
- PORTED `NumOfWpPos` w2 @ 0x00215AB0 <- ntsc src/seMail:seMailTargetDistCheck (2 syms rebound)
- PORTED `func_00215C68` w2 @ 0x00215C68 <- ntsc src/seMail:func_00205048 (1 syms rebound)

### src/way_llf
- PORTED `AddWayPointTop` w1 @ 0x00216248 <- ntsc src/way_kidnap:WayPointWithRangeFromPos (3 syms rebound)
- PORTED `CheckWayGroupActive` w1 @ 0x00216770 <- ntsc src/way_llf:InsertWayPointAfter (2 syms rebound)
- PORTED `CloseWayGroup` w1 @ 0x00216138 <- ntsc src/seMail:func_00205518 (2 syms rebound)
- PORTED `CreateWayPoint` w1 @ 0x00216168 <- ntsc src/way_kidnap:add_wp_pos (3 syms rebound)
- PORTED `InsertWayPointAfter` w1 @ 0x00216290 <- ntsc src/way_kidnap:WayPointWithRangeFromPos2 (2 syms rebound)
- PORTED `SetWayGroupActive` w1 @ 0x00216750 <- ntsc src/way_llf:AddWayPointTop (2 syms rebound)
- PORTED `WayBridgeAll_begin` w1 @ 0x002164D8 <- ntsc src/way_kidnap:WayPointWithRangeFromGObj (2 syms rebound)
- PORTED `WayBridgeVar_begin` w2 @ 0x00216568 <- ntsc src/way_llf:InitWayPointSystem (2 syms rebound)
- PORTED `WayBridgeVar_next` w2 @ 0x002165C0 <- ntsc src/way_llf:CreateWayGroup (2 syms rebound)
- PORTED `WayBridge_begin` w2 @ 0x00216428 <- ntsc src/way_kidnap:WayLengthOfGObj_Pos (2 syms rebound)
- PORTED `WayBridge_next` w2 @ 0x00216480 <- ntsc src/way_kidnap:WayLengthOfGObj_GObj (2 syms rebound)
- PORTED `WayGroup_begin` w1 @ 0x002163A8 <- ntsc src/way_kidnap:NumOfWpPos (2 syms rebound)
- PORTED `WayGroup_next` w1 @ 0x002163E8 <- ntsc src/way_kidnap:CopyWpPos (2 syms rebound)
- PORTED `WayPointList_begin` w1 @ 0x00216698 <- ntsc src/way_llf:CloseWayGroup (2 syms rebound)
- PORTED `WayPointList_next` w1 @ 0x002166B8 <- ntsc src/way_llf:CreateWayPoint (2 syms rebound)
- PORTED `WayPoint_begin` w1 @ 0x00216618 <- ntsc src/way_llf:CreateTempWayGroup (2 syms rebound)
- PORTED `WayPoint_next` w1 @ 0x00216658 <- ntsc src/way_llf:DeleteWayGroup (2 syms rebound)
- PORTED `waypoint_bidirectional_list` w1 @ 0x002166F8 <- ntsc src/way_llf:AddWayPoint (3 syms rebound)

### src/way_sys
- PORTED `BridgeBox` w2 @ 0x0017F118 <- ntsc src/way_util:visible_waypoint_of_all_except_temp (1 syms rebound)
- REVERTED `DeleteGuideWay` w1 @ 0x0017F120 — [codegen] tu-size: TU .text 0x172C != PAL span 0x1730 (trailing pad word / extra code)
- PORTED `GetWay_begin` w1 @ 0x0017F0F8 <- ntsc src/way_util:visible_waypoint_of_all_except_gid_ThreadVersion (2 syms rebound)

### src/way_tool
- PORTED `point_insert` w1 @ 0x00216D08 <- ntsc src/way_llf:WayBridge_begin (15 syms rebound)
- PORTED `point_nige` w1 @ 0x00217C38 <- ntsc src/way_tool:draw_way_group (8 syms rebound)
- PORTED `quick_save_wpfile` w1 @ 0x00217CD0 <- ntsc src/way_tool:way_toolDL (11 syms rebound)

### src/way_util
- PORTED `NearestWgFromTarget` w1 @ 0x00181870 <- ntsc src/way_util:func_0017B080 (2 syms rebound)
- PORTED `WayUtilWorkAlloc` w1 @ 0x0017FC28 <- ntsc src/way_util:GetWgAll (4 syms rebound)
- PORTED `WayUtilWorkFree` w1 @ 0x0017FD48 <- ntsc src/way_util:set_check_wp (2 syms rebound)
- PORTED `bridge_waypoint_side_bridge` w1 @ 0x00181778 <- ntsc src/way_util:func_0017AF88 (4 syms rebound)
- PORTED `bridge_waypoint_side_me` w1 @ 0x00181688 <- ntsc src/way_util:NearestWgFromTarget (4 syms rebound)
- PORTED `direction_across_bridge` w1 @ 0x00181558 <- ntsc src/way_util:bridge_waypoint_side_bridge (8 syms rebound)
- PORTED `ez_circle` w2 @ 0x0017F840 <- ntsc src/way_util:WayUtilWorkFree (1 syms rebound)
- PORTED `ez_line` w2 @ 0x0017F830 <- ntsc src/way_util:WayUtilWorkAlloc (1 syms rebound)
- PORTED `get_wp_nearest_bridge_side_bridge` w1 @ 0x001814C8 <- ntsc src/way_util:waypoint_connect_group_side_me (3 syms rebound)
- PORTED `get_wp_nearest_bridge_side_me` w1 @ 0x00181438 <- ntsc src/way_util:bridge_waypoint_side_me (3 syms rebound)
- PORTED `nearest_waypoint` w1 @ 0x00180AB8 <- ntsc src/way_util:nearest_waypoint_by_lineseg_of_group_from_gobj (7 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- PORTED `nearest_waypoint_by_lineseg` w1 @ 0x00180CB0 <- ntsc src/way_util:nearest_waypoint_of_all_except_group (5 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- PORTED `nearest_waypoint_by_lineseg_from_gobj` w1 @ 0x00180E28 <- ntsc src/way_util:nearest_waypoint_of_all (6 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- PORTED `nearest_waypoint_by_lineseg_of_group` w1 @ 0x00180C00 <- ntsc src/way_util:waypoint_with_range (4 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- PORTED `nearest_waypoint_by_lineseg_of_group_from_gobj` w1 @ 0x00180D68 <- ntsc src/way_util:nearest_waypoint_of_all_not_bridge_except_group (5 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- REVERTED `nearest_waypoint_from_gobj` w1 @ 0x00180B58 — [callee-sig-conflict] src/way_util.c:6: conflicting types for `fzMagnitudefv'
- PORTED `nearest_waypoint_of_all` w1 @ 0x00181100 <- ntsc src/way_util:visible_waypoint_from_gobj (6 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- PORTED `nearest_waypoint_of_all_except_group` w1 @ 0x00180F78 <- ntsc src/way_util:visible_waypoint_of_all_from_gobj (6 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- PORTED `nearest_waypoint_of_all_not_bridge_except_group` w1 @ 0x00181020 <- ntsc src/way_util:visible_waypoint (7 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- PORTED `nearest_waypoint_of_group` w1 @ 0x00180A20 <- ntsc src/way_util:nearest_waypoint_by_lineseg (6 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- PORTED `visible_waypoint` w1 @ 0x001811F8 <- ntsc src/way_util:func_0017AA08 (8 syms rebound) — unblocked by the PAL phase-1 `lit4 src/way_util` carve
- REVERTED `visible_waypoint_from_gobj` w1 @ 0x00181310 — [callee-sig-conflict] src/way_util.c:15: conflicting types for `fzMagnitudefv'
- PORTED `visible_waypoint_of_all` w1 @ 0x001811A8 <- ntsc src/way_util:get_wp_nearest_bridge_side_me (2 syms rebound)
- REVERTED `visible_waypoint_of_all_except_gid` w1 @ 0x0017F180 — [callee-sig-conflict] src/way_util.c:16: conflicting types for `fzMagnitudefv'
- REVERTED `visible_waypoint_of_all_except_temp` w1 @ 0x0017F4B8 — [callee-sig-conflict] src/way_util.c:16: conflicting types for `fzMagnitudefv'
- PORTED `visible_waypoint_of_all_from_gobj` w1 @ 0x001811C8 <- ntsc src/way_util:func_0017A9D8 (3 syms rebound)
- PORTED `waybridge_between_group` w1 @ 0x001815E8 <- ntsc src/way_util:waypoint_connect_group_side_bridge (4 syms rebound)
- PORTED `waypoint_connect_group_side_bridge` w1 @ 0x00181828 <- ntsc src/way_util:func_0017B038 (2 syms rebound)
- PORTED `waypoint_connect_group_side_me` w1 @ 0x00181730 <- ntsc src/way_util:wpsort_compfnc (2 syms rebound)
- PORTED `waypoint_with_range` w1 @ 0x00180EE8 <- ntsc src/way_util:visible_waypoint_of_all (6 syms rebound)
- REVERTED `wpsort_compfnc` w2 @ 0x001818C8 — [codegen] tu-size: TU .text 0x277C != PAL span 0x2780 (trailing pad word / extra code)
- CARVES `src/way_util` — 1 US carve entry to translate:
    - - [0x530E3C, .lit4, src/way_util]    # carved D_00630E3C..D_00630E68 (12x 100000f, one per waypoint-search func); the 8 slots whose owners are still INCLUDE_ASM are emitted by ASM_LIT4_SLOT in way_util.c, VMA 0x630E3C..0x630E6C

### src/weapon
- PORTED `ExecWeaponHitReaction` w2 @ 0x00201BC0 <- ntsc src/weapon:weaponFumbleSE (2 syms rebound)

### src/windField
- PORTED `GetWindVector` w1 @ 0x00203BF0 <- ntsc src/windField:drawSenpuuki (2 syms rebound)
- REVERTED `StopWindField` w1 @ 0x00203DE8 — [codegen] insn 1: expected `addiu	v0,v0,0` built `addiu	v0,v0,1824`
- PORTED `drawLines` w1 @ 0x00203DF8 <- ntsc src/windField:getRadiateWindVector (3 syms rebound)
- PORTED `drawSenpuukiBase` w2 @ 0x00203F78 <- ntsc src/windManager:SetWindManager (4 syms rebound)
- PORTED `drawSenpuukiHane` w2 @ 0x00203E78 <- ntsc src/windManager:ExecWindManager (4 syms rebound)
- PORTED `drawSenpuukiUnit` w2 @ 0x00203EF8 <- ntsc src/windManager:ReinitWindManager (4 syms rebound)
- PORTED `dummyGetWindVector` w1 @ 0x00203C10 <- ntsc src/windField:ExecWindField (2 syms rebound)

### src/windManager
- REVERTED `ExecWindManager` w1 @ 0x00203FF8 — [codegen] insn 31: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `ReinitWindManager` w1 @ 0x00204078 — [undeclared] src/windManager.c:7: `D_0063BC64' undeclared (first use in this function)

### src/wireLetter
- PORTED `ChangeColorWireString` w1 @ 0x00204790 <- ntsc src/wireLetter:Draw2DBox (2 syms rebound)
- PORTED `DefaultColorWireString` w1 @ 0x00204760 <- ntsc src/wireLetter:ChangeColorWireString (3 syms rebound)

### src/worm
- PORTED `GetWormCaptureVector` w1 @ 0x00205828 <- ntsc src/worm:GetWormRoute (4 syms rebound)
- REVERTED `SetWormReduceRatio` w3 @ 0x00205C18 — [codegen] insn 1: expected `lw	v1,2096(v0)` built `lw	v1,2048(v0)`
- REVERTED `TraceWormRoute` w3 @ 0x00205C28 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- PORTED `WormDL` w2 @ 0x00205B38 <- ntsc src/worm:GetWormCaptureVector (2 syms rebound)

## Data-carve phase 1 — the 32 `emits-data` reverts (2026-09-04)

Every `emits-data` revert in this ledger was one shape: the ported body
contains a float constant (or, once, a `<=8`-byte string constant), and
ee-as interns it into the TU object's own anonymous `.lit4` (`.sdata` for the
string).  With no carve, those bytes are appended to a section the PAL yaml
still owns as one whole-section blob, so the layout shifts and the SHA-1 gate
fails — which is exactly what `port_from_ntsc.py`'s growth check caught.

Fix: 12 `.lit4` carves + 1 `.sdata` carve in `config/ico.pal.yaml`, plus
`ASM_LIT4_SLOT()` lines for every pool word whose owner is still
`INCLUDE_ASM` (see `include/include_asm.h` and `tools/preprocess_old_as.py`).
The carve makes the TU's object own its whole pool run; porting a body then
swaps one `ASM_LIT4_SLOT` for the body's own literal, so the object's data
size never changes and the growth check passes untouched.  Byte-level
evidence, run boundaries and the MAIN.MAP cross-check are in
`decomp/carve_ledger.md` §"PAL phase 1".

Two driver notes worth keeping:

- **The `ntsc` reference tree moved under the port cache.**  `.port_cache/`
  was built at 03:34; a concurrent `rename ntsc from PAL` pass in
  `/primary/dev/ico-ntsc` renamed C bodies and regenerated
  `asm/matchings/**` at 04:54, after which the cached `us_name`s resolved to
  nothing (`missing-body`, `map-error`).  Re-running the ports against a
  read-only snapshot of `ntsc` **HEAD** (`PORT_NTSC_ROOT=<snapshot>`) fixed
  every one of them.  Any future `port` run must pin `PORT_NTSC_ROOT` to a
  stable ntsc revision rather than reading that worktree live.
- **`quick_diff` cleared `E3_LeverCheck` while the ELF diverged.**  The
  first attempt bound the body's second callee to PAL `HandCameraCorrect`
  (0x19D4A8) where the ROM calls `_RotyGV` (0x19CA48): `ntsc` names that
  function `HandCameraCorrect` in C but `_RotyGV` in its own splat baseline,
  so the driver's lockstep slot walk produced an identity map and left the
  body's call unbound.  Only `ninja`'s SHA-1 gate caught it (the per-function
  differ shows in-TU relocs as unresolved, the known false negative).  Fixed
  by making the ntsc baseline agree with the ntsc C before the walk.
