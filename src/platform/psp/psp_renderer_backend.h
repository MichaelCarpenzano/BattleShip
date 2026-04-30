#ifndef _PSP_RENDERER_BACKEND_H_
#define _PSP_RENDERER_BACKEND_H_

#include <PR/gbi.h>
#include <ssb_types.h>

typedef enum PSPRendererPassKind
{
    nPSPRendererPassUI2D = 0,
    nPSPRendererPassScene3D = 1
} PSPRendererPassKind;

typedef struct PSPRendererBoundaryState
{
    Gfx *dl_heads[4];
    Gfx *dl_branches[4];
    s32 active_task_id;
} PSPRendererBoundaryState;

void pspRendererBackendInit(void);
void pspRendererBackendNotifyVideoInit(void *framebuffer0, void *framebuffer1, void *framebuffer2, void *zbuffer);
void pspRendererBackendMarkEnqueue(const PSPRendererBoundaryState *boundary_state);
void pspRendererBackendFlush(const PSPRendererBoundaryState *boundary_state, PSPRendererPassKind pass_kind);

#endif
