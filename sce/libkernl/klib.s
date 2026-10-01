# klib: libkernl.a(klib.o), the EE kernel's syscall entry points, assembled
# from klib.s with one source line per entry point (RFU000_FullReset at
# klib.s:33 through GetMemorySize at klib.s:186).  Each entry point is the
# four words `addiu $3,$0,NUM; syscall; jr $31; nop`: the kernel takes the
# call number in $3, and the `i` (interrupt-context) forms pass it negated.
# Each entry point below sits on its own line number in klib.s.
#
# The object's .text is 64-byte aligned: the ELF's .text carries alignment
# 64 and klib.o is the input that gives it, RFU000_FullReset sitting at
# 0x100100 after crt0's 0xC8 bytes and zero fill.
#
# Names and call numbers are klib.s's own; the macro's name is ours.

	.macro	KCALL name, num	/* derived name */
	.globl	\name
	.type	\name, @function
\name:
	addiu	$3, $0, \num
	syscall
	jr	$31
	nop
	.size	\name, . - \name
	.endm

	.text
	.set	noreorder
	.align	6





	KCALL	RFU000_FullReset, 0
	KCALL	ResetEE, 1
	KCALL	SetGsCrt, 2
	KCALL	RFU003, 3
	KCALL	Exit, 4
	KCALL	RFU005, 5
	KCALL	LoadExecPS2, 6
	KCALL	ExecPS2, 7
	KCALL	RFU008, 8
	KCALL	RFU009, 9
	KCALL	AddSbusIntcHandler, 10
	KCALL	RemoveSbusIntcHandler, 11
	KCALL	Interrupt2Iop, 12
	KCALL	SetVTLBRefillHandler, 13
	KCALL	SetVCommonHandler, 14
	KCALL	SetVInterruptHandler, 15


	KCALL	AddIntcHandler, 16
	KCALL	AddIntcHandler2, 16
	KCALL	RemoveIntcHandler, 17
	KCALL	AddDmacHandler, 18
	KCALL	AddDmacHandler2, 18
	KCALL	RemoveDmacHandler, 19
	KCALL	_EnableIntc, 20
	KCALL	_DisableIntc, 21
	KCALL	_EnableDmac, 22
	KCALL	_DisableDmac, 23
	KCALL	SetAlarm, 252
	KCALL	ReleaseAlarm, 253
	KCALL	_iEnableIntc, -26
	KCALL	_iDisableIntc, -27
	KCALL	_iEnableDmac, -28
	KCALL	_iDisableDmac, -29
	KCALL	iSetAlarm, -254
	KCALL	iReleaseAlarm, -255


	KCALL	CreateThread, 32
	KCALL	DeleteThread, 33
	KCALL	StartThread, 34
	KCALL	ExitThread, 35
	KCALL	ExitDeleteThread, 36
	KCALL	TerminateThread, 37
	KCALL	iTerminateThread, -38
	KCALL	DisableDispatchThread, 39
	KCALL	EnableDispatchThread, 40
	KCALL	ChangeThreadPriority, 41
	KCALL	iChangeThreadPriority, -42
	KCALL	RotateThreadReadyQueue, 43
	KCALL	_iRotateThreadReadyQueue, -44
	KCALL	ReleaseWaitThread, 45
	KCALL	iReleaseWaitThread, -46
	KCALL	GetThreadId, 47


	KCALL	ReferThreadStatus, 48
	KCALL	iReferThreadStatus, -49
	KCALL	SleepThread, 50
	KCALL	WakeupThread, 51
	KCALL	_iWakeupThread, -52
	KCALL	CancelWakeupThread, 53
	KCALL	iCancelWakeupThread, -54
	KCALL	SuspendThread, 55
	KCALL	_iSuspendThread, -56
	KCALL	ResumeThread, 57
	KCALL	iResumeThread, -58
	KCALL	JoinThread, 59
	KCALL	RFU060, 60
	KCALL	RFU061, 61
	KCALL	EndOfHeap, 62
	KCALL	RFU063, 63


	KCALL	CreateSema, 64
	KCALL	DeleteSema, 65
	KCALL	SignalSema, 66
	KCALL	iSignalSema, -67
	KCALL	WaitSema, 68
	KCALL	PollSema, 69
	KCALL	iPollSema, -70
	KCALL	ReferSemaStatus, 71
	KCALL	iReferSemaStatus, -72
	KCALL	RFU073, 73
	KCALL	SetOsdConfigParam, 74
	KCALL	GetOsdConfigParam, 75
	KCALL	GetGsHParam, 76
	KCALL	GetGsVParam, 77
	KCALL	SetGsHParam, 78
	KCALL	SetGsVParam, 79



	KCALL	RFU080_CreateEventFlag, 80
	KCALL	RFU081_DeleteEventFlag, 81
	KCALL	RFU082_SetEventFlag, 82
	KCALL	RFU083_iSetEventFlag, -83
	KCALL	RFU084_ClearEventFlag, 84
	KCALL	RFU085_iClearEventFlag, -85
	KCALL	RFU086_WaitEvnetFlag, 86
	KCALL	RFU087_PollEvnetFlag, 87
	KCALL	RFU088_iPollEvnetFlag, -88
	KCALL	RFU089_ReferEventFlagStatus, 89
	KCALL	RFU090_iReferEventFlagStatus, -90
	KCALL	RFU091, 91
	KCALL	EnableIntcHandler, 92
	KCALL	iEnableIntcHandler, -92
	KCALL	DisableIntcHandler, 93
	KCALL	iDisableIntcHandler, -93
	KCALL	EnableDmacHandler, 94
	KCALL	iEnableDmacHandler, -94
	KCALL	DisableDmacHandler, 95
	KCALL	iDisableDmacHandler, -95


	KCALL	KSeg0, 96
	KCALL	EnableCache, 97
	KCALL	DisableCache, 98
	KCALL	GetCop0, 99
	KCALL	FlushCache, 100

	KCALL	CpuConfig, 102
	KCALL	iGetCop0, -103
	KCALL	iFlushCache, -104

	KCALL	iCpuConfig, -106
	KCALL	sceSifStopDma, 107
	KCALL	SetCPUTimerHandler, 108
	KCALL	SetCPUTimer, 109
	KCALL	SetOsdConfigParam2, 110
	KCALL	GetOsdConfigParam2, 111


	KCALL	GsGetIMR, 112
	KCALL	iGsGetIMR, -112
	KCALL	GsPutIMR, 113
	KCALL	iGsPutIMR, -113
	KCALL	SetPgifHandler, 114
	KCALL	SetVSyncFlag, 115
	KCALL	RFU116, 116
	KCALL	_print, 117
	KCALL	sceSifDmaStat, 118
	KCALL	isceSifDmaStat, -118
	KCALL	sceSifSetDma, 119
	KCALL	isceSifSetDma, -119
	KCALL	sceSifSetDChain, 120
	KCALL	isceSifSetDChain, -120
	KCALL	sceSifSetReg, 121
	KCALL	sceSifGetReg, 122
	KCALL	ExecOSD, 123
	KCALL	Deci2Call, 124
	KCALL	PSMode, 125
	KCALL	MachineType, 126
	KCALL	GetMemorySize, 127

	.set	reorder

# The member's .data (0x10): the library stamp.  Its last
# four bytes are the version the SIF members compare against the IOP's.
	.data
	.globl	__ps2_klibinfo__
__ps2_klibinfo__:
	.ascii	"PsIIlibkernl2240"
