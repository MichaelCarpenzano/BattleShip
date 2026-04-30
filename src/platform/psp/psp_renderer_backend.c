#include "psp_renderer_backend.h"
#include "psp_renderer_state.h"

void pspRendererBackendInit(void)
{
    pspRendererStateInit2DUIProfile();
}

void pspRendererBackendNotifyVideoInit(void *framebuffer0, void *framebuffer1, void *framebuffer2, void *zbuffer)
{
    (void)framebuffer0;
    (void)framebuffer1;
    (void)framebuffer2;
    (void)zbuffer;
}

void pspRendererBackendMarkEnqueue(const PSPRendererBoundaryState *boundary_state)
{
    (void)boundary_state;
}

void pspRendererBackendFlush(const PSPRendererBoundaryState *boundary_state, PSPRendererPassKind pass_kind)
{
    (void)boundary_state;
    (void)pass_kind;
}
