/*
 * sce/libsndn2/sound.h  (derived name: named after the member, sound.o)
 *
 * The declarations sound.c needs ahead of their definitions: the Sg reverb
 * entry points the parameter controller calls, the _Sg DMA helper, the
 * fake-body vab opener, the _Sg event handlers and realtime pass the tick
 * calls, the _Sg voice, packet and remote helpers called above their
 * definitions; the library's entry points the game's sound, I/O and debug
 * code calls; and the stream PCM calls the movie player's audio decoder makes.
 * Each prototype is the signature of its definition in sound.c, which
 * includes this header.
 */
#ifndef SCE_LIBSNDN2_SOUND_H
#define SCE_LIBSNDN2_SOUND_H

void SgSetReverbType(int a0, int a1);
void SgSetReverbDepth(int a0, int a1, int a2);
void SgSetReverbDelaytime(int a0, int a1);
void SgSetReverbFeedback(int a0, int a1);
void _SgDmaCommon(int cmd, int a1, void *a2, void *a3);
int SgVabOpenFakeBody(int *a0, int a1);
int _SgSetPkAdd(int a0, int a1, int a2, int a3);
int _SgSeMain(int *a0);
int _SgBgmMain(int *a0);
int _SgSetRealtimeVolume(int *a0);
int _SgTableEnvAdd(int *a0);
int _SgSeqKeyOnSlot(int a0);
int _SgSeKeyOnSlot(int a0, int a1, int a2);
int _SgSeKeyOff(char *a0);
int _SgSeqKeyOff(int *a0);
int _SgIntoKeyOn(int a0, int a1, int a2);
int _SgPitchTableVag(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
int _SgSeqSeVolume(int a0, int *a1);
int _SgPan(int a0, int a1);
int _SgfadeParam(int a0, int a1, int a2, int a3);
int _SgSndn2Remote(int a0, int a1, void *a2, void *a3, int a4, int a5);
void _SgSeqSeRrEnd(int *a0);
void _SgEndSeq(int *a0);
void _SgTempoChange(int *a0);
void _SgProgChange(int *a0);
void _SgContMod(int *a0);
void _SgContModLoop(int *a0);
void _SgContParam(int *a0);
void _SgContVol(int *a0);
void _SgContPan(int *a0);
void _SgContDump(int *a0);
void _SgContPolta(char *a0);
void _SgContSeLoop(int *a0);
void _SgContLoopCount(void *a0);
void _SgContLoop(int *a0);
void _SgBendForm(int *a0);
void _SgSetRealtimeTickProc(void);
void _SgDeltaTime(char *s);
int SgSndn2RemoteInit(void);
int SgSndn2RemoteSync(void);
void SgInit(void);
void SgInitHot(void);
void SgQuit(void);
void SgCalledTickProc(void);
void SgSetDigitalOutputMode(int a0);
int SgDmaWrite(int a0, void *a1, void *a2);
int SgDmaRead(void *a0, int a1, void *a2);
int SgGetDmaTransferStatus(int mode);
int SgVabOpen(int a0, int *a1, int a2);
int SgVabClose(int a0);
int SgBgmOpen(int a0, void *a1);
int SgBgmClose(int a0);
void SgSetReverbEndAddr(int a0, int a1);
void SgSetOutputMode(int a0);
void SgSetTickMode(int a0);
int SgGetSlotStatus(int kind, int slot);
void SgSetMasterVol(int a0, int a1, int a2);
int SgSetBgmVol(unsigned int a0, int a1, int a2);
int SgSetSeMasterVol(int a0, int a1);
void SgBgmPlay(unsigned int a0);
void SgBgmStop(unsigned int a0, int a1);
void SgSetBgmTempo(unsigned int a0, int a1);
int SgGetBgmTempo(unsigned int a0);
int SgGetBgmStatus(int a0);
int SgGetBgmChStatus(unsigned int a0, int a1, int a2);
int SgSetBgmPanpot(unsigned int a0, int a1);
int SgSePlay(int a0, int a1, int a2);
void SgSeStop(int a0);
void SgSeStopAll(int a0);
void SgSetSeVolDirect(unsigned int a0, int a1, int a2);
int SgGetSpuSlotMalloc(int a0);
int SgSetSpuSlotFree(unsigned int a0);
void SgStAdpcmInit(void);
void SgStAdpcmQuit(void);
int SgStAdpcmOpen(void *a0);
int SgStAdpcmClose(unsigned int a0);
int SgStAdpcmChannelVolume(unsigned long long a0, unsigned int a1, int a2);
int SgStAdpcmChannelPitch(unsigned long long a0, int a1);
int SgStAdpcmPlay(unsigned long long a0);
int SgStAdpcmStop(unsigned long long a0);
int SgStAdpcmIopReadAddr(int a0);
void SgStPcmInit(void);
void SgStPcmQuit(void);
int SgStPcmOpen(int *a0);
int SgStPcmClose(unsigned int a0);
void SgStPcmSetEffect(int a0);
int SgStPcmPlay(unsigned long long a0);
int SgStPcmStop(unsigned long long a0);
int SgStPcmLseek(unsigned int a0, unsigned int a1);
void SgStPcmVolume(unsigned long long a0, unsigned int a1, int a2);
int SgStPcmIopReadAddr(unsigned int a0);
int SgStPcmBufMode(int a0, long a1, int a2);

#endif /* SCE_LIBSNDN2_SOUND_H */
