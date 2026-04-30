#include <sys/controller.h>

#include <pspctrl.h>

/*
 * PSP input adapter:
 * - maps PSP pad state into the existing SYController shape used by gameplay.
 * - keeps N64-facing semantics (button_hold/button_tap/stick_range) so no
 *   gameplay modules need direct PSP awareness.
 */

static u16 ssb64_psp_map_buttons(u32 buttons)
{
    u16 mapped = 0;

    if (buttons & PSP_CTRL_CROSS)    mapped |= A_BUTTON;
    if (buttons & PSP_CTRL_CIRCLE)   mapped |= B_BUTTON;
    if (buttons & PSP_CTRL_TRIANGLE) mapped |= Z_TRIG;
    if (buttons & PSP_CTRL_SQUARE)   mapped |= START_BUTTON;
    if (buttons & PSP_CTRL_LTRIGGER) mapped |= L_TRIG;
    if (buttons & PSP_CTRL_RTRIGGER) mapped |= R_TRIG;

    if (buttons & PSP_CTRL_UP)       mapped |= U_JPAD;
    if (buttons & PSP_CTRL_DOWN)     mapped |= D_JPAD;
    if (buttons & PSP_CTRL_LEFT)     mapped |= L_JPAD;
    if (buttons & PSP_CTRL_RIGHT)    mapped |= R_JPAD;

    return mapped;
}

void ssb64_psp_input_poll_into(SYController *out, const SYController *prev)
{
    SceCtrlData data;
    u16 hold;

    sceCtrlPeekBufferPositive(&data, 1);

    hold = ssb64_psp_map_buttons(data.Buttons);

    out->button_hold = hold;
    out->button_tap = (hold ^ prev->button_hold) & hold;
    out->button_release = (hold ^ prev->button_hold) & prev->button_hold;
    out->button_update = out->button_tap;

#if PORT_HAS_ANALOG_STICK
    out->stick_range.x = (s8)((s32)data.Lx - 128);
    out->stick_range.y = (s8)(128 - (s32)data.Ly);
#else
    out->stick_range.x = 0;
    out->stick_range.y = 0;
#endif
}
