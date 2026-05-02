#include <stddef.h>
#include <stdint.h>

#include <pspaudio.h>

/*
 * PSP audio adapter:
 * Bridges mixed PCM output from existing sequence/synth paths to PSP's audio
 * output channel API without changing gameplay or n_audio call chains.
 */

static int sSSB64PspAudioChannel = -1;

void ssb64_psp_audio_init(void)
{
    if (sSSB64PspAudioChannel < 0)
    {
        sSSB64PspAudioChannel = sceAudioChReserve(-1, PSP_AUDIO_SAMPLE_ALIGN(640), PSP_AUDIO_FORMAT_STEREO);
    }
}

void ssb64_psp_audio_submit(const int16_t *interleaved_pcm)
{
    if ((sSSB64PspAudioChannel >= 0) && (interleaved_pcm != NULL))
    {
        (void)sceAudioOutputBlocking(sSSB64PspAudioChannel, PSP_AUDIO_VOLUME_MAX, (void*)interleaved_pcm);
    }
}

void ssb64_psp_audio_shutdown(void)
{
    if (sSSB64PspAudioChannel >= 0)
    {
        sceAudioChRelease(sSSB64PspAudioChannel);
        sSSB64PspAudioChannel = -1;
    }
}
