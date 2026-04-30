#ifndef _PSP_RENDERER_STATE_H_
#define _PSP_RENDERER_STATE_H_

/*
 * High-frequency RDP -> GU mapping notes for the initial 2D/UI correctness path:
 * - gDPSetCycleType:      cycle policy maps to GU blend/texturing toggles.
 * - gDPSetRenderMode:     render mode maps to GU alpha/depth/blend state.
 * - gDPFillRectangle:     fill rect maps to GU sprite/rect primitive emission.
 * - gDPSetScissor:        scissor box maps to GU_SCISSOR_TEST + guScissor.
 * - gSPViewport:          viewport matrix maps to GU viewport + offset.
 *
 * 3D parity is intentionally deferred; the boundary currently prioritizes menus,
 * overlays, fills, and sprite-heavy code paths before full scene fidelity.
 */

void pspRendererStateInit2DUIProfile(void);

#endif
