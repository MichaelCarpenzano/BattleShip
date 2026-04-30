#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PspResourceHandle PspResourceHandle;

/* File-style API used by relocation and asset fetch paths. */
PspResourceHandle* pspResourceOpen(const char* path, const char* mode);
size_t pspResourceRead(PspResourceHandle* handle, void* dst, size_t size);
int pspResourceSeek(PspResourceHandle* handle, long offset, int origin);
long pspResourceTell(PspResourceHandle* handle);
int pspResourceClose(PspResourceHandle* handle);

/* Archive/file-id helpers for relocation loaders. */
PspResourceHandle* pspResourceOpenRelocById(uint32_t file_id);
const char* pspResourceResolveRelocPath(uint32_t file_id);

#ifdef __cplusplus
}
#endif
