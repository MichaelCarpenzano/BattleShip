/*
 * PSP runtime stubs for symbols historically provided by the desktop
 * libultraship-backed port layer.
 */

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void ssb64_psp_runtime_stub_anchor(void) {}

void port_log_init(const char* path) {
    (void)path;
}

void port_log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void port_coroutine_yield(void) {}
void port_dump_backtrace(void) {}

void port_aobj_event32_unhalfswap_stream(void* head) {
    (void)head;
}

void port_aobj_register_halfswapped_range(void* base, unsigned long size) {
    (void)base;
    (void)size;
}

void port_aobj_event32_unhalfswap_reset(void) {}

int port_aobj_is_in_halfswapped_range(const void* p) {
    (void)p;
    return 0;
}

int port_aobj_unhalfswap_visit(const void* p) {
    (void)p;
    return 0;
}

void* portAudioDmaNew(void** state) {
    (void)state;
    return NULL;
}

void portAudioPushSilence(void) {}

void portAudioSubmitFrame(const void* buf, int sampleCount) {
    (void)buf;
    (void)sampleCount;
}

void portAudioLoadAssets(void) {}
void portAudioShutdownAssets(void) {}

void* portRelocResolvePointerDebug(unsigned int token, const char* file, int line) {
    (void)token;
    (void)file;
    (void)line;
    return NULL;
}

int portParticleLoadBank(uintptr_t scripts_lo, int bank_id) {
    (void)scripts_lo;
    (void)bank_id;
    return 0;
}

size_t lbRelocGetFileSize(unsigned int id) {
    (void)id;
    return 0;
}

void* lbRelocGetExternHeapFile(unsigned int id, void* heap) {
    (void)id;
    return heap;
}

void acmd_trace_log_cmd(uint32_t w0, uint32_t w1) {
    (void)w0;
    (void)w1;
}

void aClearBufferImpl(uint16_t addr, int nbytes) {
    (void)addr;
    (void)nbytes;
}
void aLoadBufferImpl(uintptr_t source_addr) { (void)source_addr; }
void aSaveBufferImpl(uintptr_t dest_addr) { (void)dest_addr; }
void aLoadADPCMImpl(int count, uintptr_t book_addr) { (void)count; (void)book_addr; }
void aSetBufferImpl(uint8_t flags, uint16_t in, uint16_t out, uint16_t nbytes) {
    (void)flags; (void)in; (void)out; (void)nbytes;
}
void aInterleaveImpl(uint16_t left, uint16_t right) { (void)left; (void)right; }
void aDMEMMoveImpl(uint16_t in_addr, uint16_t out_addr, int nbytes) {
    (void)in_addr; (void)out_addr; (void)nbytes;
}
void aSetLoopImpl(uintptr_t adpcm_loop_state) { (void)adpcm_loop_state; }
void aADPCMdecImpl(uint8_t flags, int16_t* state) { (void)flags; (void)state; }
void aResampleImpl(uint8_t flags, uint16_t pitch, int16_t* state) { (void)flags; (void)pitch; (void)state; }
void aSetVolumeImpl(uint16_t flags, uint16_t vol, uint16_t voltgt, uint16_t volrate) {
    (void)flags; (void)vol; (void)voltgt; (void)volrate;
}
void aEnvMixerImpl(uint8_t flags, int16_t* state) { (void)flags; (void)state; }
void aMixImpl(uint8_t flags, int16_t gain, uint16_t in_addr, uint16_t out_addr) {
    (void)flags; (void)gain; (void)in_addr; (void)out_addr;
}
void aPoleFilterImpl(uint8_t flags, uint16_t gain, int16_t* state) { (void)flags; (void)gain; (void)state; }

uint32_t osVirtualToPhysical(void* vaddr) {
    return (uint32_t)(uintptr_t)vaddr;
}

uint32_t osSetIntMask(uint32_t mask) {
    return mask;
}

void alCopy(void* src, void* dest, int len) {
    if ((src != NULL) && (dest != NULL) && (len > 0)) {
        memcpy(dest, src, (size_t)len);
    }
}
