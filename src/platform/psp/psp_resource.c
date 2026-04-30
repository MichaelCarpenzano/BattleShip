#include "psp_resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "resource/RelocFileTable.h"

extern void port_log(const char *fmt, ...);

enum {
    PSP_RESOURCE_PATH_MAX = 512,
};

struct PspResourceHandle {
    FILE* fp;
    char path[PSP_RESOURCE_PATH_MAX];
};

static const char* sPspArchiveRoots[] = {
    "assets/",           /* host/dev layout */
    "ms0:/PSP/GAME/SSB64/assets/", /* PSP media layout */
    "./",                /* fallback to cwd */
};

static int pspResourceBuildCandidatePath(char* out, size_t out_size, const char* root, const char* rel)
{
    size_t root_len;
    size_t rel_len;

    if ((out == NULL) || (root == NULL) || (rel == NULL) || (out_size == 0)) {
        return -1;
    }

    root_len = strlen(root);
    rel_len = strlen(rel);

    if ((root_len + rel_len + 1) > out_size) {
        return -1;
    }

    memcpy(out, root, root_len);
    memcpy(out + root_len, rel, rel_len + 1);
    return 0;
}

const char* pspResourceResolveRelocPath(uint32_t file_id)
{
    if ((file_id >= RELOC_FILE_COUNT) || (gRelocFileTable[file_id] == NULL)) {
        port_log("[psp_resource] invalid reloc file id=%u", (unsigned)file_id);
        return NULL;
    }
    return gRelocFileTable[file_id];
}

PspResourceHandle* pspResourceOpen(const char* path, const char* mode)
{
    PspResourceHandle* handle;

    if ((path == NULL) || (mode == NULL)) {
        return NULL;
    }

    handle = (PspResourceHandle*)calloc(1, sizeof(*handle));
    if (handle == NULL) {
        port_log("[psp_resource] alloc failed opening %s", path);
        return NULL;
    }

    /*
     * Scaffolding note:
     * LUS auto-mounts .o2r archives and resolves logical resource paths.
     * PSP backend currently probes explicit filesystem roots instead.
     */
    for (size_t i = 0; i < (sizeof(sPspArchiveRoots) / sizeof(sPspArchiveRoots[0])); i++) {
        if (pspResourceBuildCandidatePath(handle->path, sizeof(handle->path), sPspArchiveRoots[i], path) != 0) {
            continue;
        }
        handle->fp = fopen(handle->path, mode);
        if (handle->fp != NULL) {
            return handle;
        }
    }

    /* Allow direct/open-absolute paths as final fallback. */
    strncpy(handle->path, path, sizeof(handle->path) - 1);
    handle->path[sizeof(handle->path) - 1] = '\0';
    handle->fp = fopen(handle->path, mode);
    if (handle->fp != NULL) {
        return handle;
    }

    port_log("[psp_resource] missing resource '%s' (checked roots: assets/, ms0:/PSP/GAME/SSB64/assets/, ./)", path);
    free(handle);
    return NULL;
}

PspResourceHandle* pspResourceOpenRelocById(uint32_t file_id)
{
    const char* path = pspResourceResolveRelocPath(file_id);

    if (path == NULL) {
        return NULL;
    }

    return pspResourceOpen(path, "rb");
}

size_t pspResourceRead(PspResourceHandle* handle, void* dst, size_t size)
{
    if ((handle == NULL) || (handle->fp == NULL) || (dst == NULL)) {
        return 0;
    }
    return fread(dst, 1, size, handle->fp);
}

int pspResourceSeek(PspResourceHandle* handle, long offset, int origin)
{
    if ((handle == NULL) || (handle->fp == NULL)) {
        return -1;
    }
    return fseek(handle->fp, offset, origin);
}

long pspResourceTell(PspResourceHandle* handle)
{
    if ((handle == NULL) || (handle->fp == NULL)) {
        return -1;
    }
    return ftell(handle->fp);
}

int pspResourceClose(PspResourceHandle* handle)
{
    int rc = 0;

    if (handle == NULL) {
        return -1;
    }

    if (handle->fp != NULL) {
        rc = fclose(handle->fp);
    }

    /* Ownership semantics: caller owns handle lifetime and must close exactly once. */
    free(handle);
    return rc;
}
