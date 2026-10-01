/*
 * sce/libsndn2/sound.h  (derived name: named after the member, sound.o)
 *
 * The declarations sound.c needs ahead of their definitions: the Sg reverb
 * entry points the parameter controller calls, the _Sg DMA helper, the
 * fake-body vab opener, the _Sg event handlers and realtime pass the tick
 * calls; and the stream PCM calls the movie player's audio decoder makes.
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

#endif /* SCE_LIBSNDN2_SOUND_H */
